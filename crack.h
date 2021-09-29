#ifndef CRACK_H
#define CRACK_H

#include <string>
#include <random>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <float.h>
#include <functional>

#define TEMP 20
#define STEP 0.2
#define ITER_STEP 300

using namespace std;

template <typename T>
class Crack
{
public:
    Crack(unsigned numberOfThreads)
    {
        numThreads = numberOfThreads;
    }
    void run(string cipher)
    {
        // start N threads, all of which executes internal_run() with different iterations.
        start = std::chrono::steady_clock::now();
        vector<thread *> threads;

        // This monitoring thread prints current global best results across all threads.
        auto monitor_thread = new thread(&Crack::logResult, this);

        // create the individual threads
        for (unsigned i = 0; i < numThreads; i++)
        {
            threads.push_back(new thread(&Crack::internal_run, this, cipher, (i + 1) * ITER_STEP));
        }

        // wait for threads to finish
        for (auto t : threads)
        {
            t->join();
        }

        // terminates monitoring thread
        lock.lock();
        done = true;
        lock.unlock();

        monitor_thread->join();
    }

    void internal_run(string cipher, unsigned long iterations)
    {

        // create a new key, then
        // randomly change it a little bit
        // if the score improves, keep the score
        // otherwise revert the change

        T last_key = createNewKey();
        string last_plain = decrypt(cipher, last_key);
        double last_score = evaluateScore(last_plain);

        T best_key = last_key;
        double best_score = last_score;
        string best_plain = last_plain;

        for (double temp = TEMP; temp > STEP; temp -= STEP)
        {
            for (unsigned long i = 0; i < iterations; i++)
            {
                auto key = randomChangeKey(last_key);
                string plain = decrypt(cipher, key);
                double score = evaluateScore(plain);

                if (score > last_score)
                {
                    // if the current change improves score, use it
                    last_key = key;
                    last_plain = plain;
                    last_score = score;
                }
                else
                {
                    // otherwise if the difference is not terrible, we have some chance of using it
                    double prob = exp((score - last_score) / temp);
                    double b = ((double)rd()) / rd.max();
                    if (prob > b)
                    {
                        last_key = key;
                        last_plain = plain;
                        last_score = score;
                    }
                }

                // always record best score
                if (last_score > best_score)
                {
                    best_score = last_score;
                    best_key = last_key;
                    best_plain = last_plain;
                }
            }

            // Compare local best (best in the current thread) against global best (best in all threads)
            internal_update_result(best_score, best_key, best_plain);
        }
    };

    void internal_update_result(double score, T key, string plaintext)
    {
        lock.lock();
        // if score improves, record new result and duration.

        if (score > best_global_score)
        {
            auto end = std::chrono::steady_clock::now();
            best_duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

            best_global_score = score;
            best_global_key = key;
            best_global_plaintext = plaintext;
            hasChanged = true;
        }
        lock.unlock();
    }

    void logResult()
    {
        // the monitoring thread
        // for every 2 seconds, check if global best result is updated,
        // if it was, print the new global best result and duration
        while (!done)
        {

            std::this_thread::sleep_for(2000ms);

            lock.lock();
            if (hasChanged)
            {
                hasChanged = false;
                cout << "Score: " << best_global_score << endl;
                cout << "Calculated " << best_duration << " seconds since the programs starts" << endl;
                cout << keyToString(best_global_key) << endl;
                cout << best_global_plaintext << endl
                     << endl;
            }
            lock.unlock();
        }
        cout << "Done." << endl;
    }

private:
    // to be implemented by subclasses
    virtual T createNewKey() = 0;
    virtual T randomChangeKey(T) = 0;
    virtual string decrypt(string cipher, T &key) = 0;
    virtual double evaluateScore(string plain) = 0;
    virtual string keyToString(T &key) = 0;

    random_device rd;
    unsigned numThreads = 10;
    std::chrono::steady_clock::time_point start;
    mutex lock;
    double best_global_score = -DBL_MAX;
    T best_global_key;
    string best_global_plaintext;
    unsigned long best_duration;

    bool hasChanged = false;
    bool done = false;
};

#endif