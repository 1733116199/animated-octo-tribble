#ifndef CRACK_H
#define CRACK_H

#include <string>
#include <random>
#include <iostream>

#define TEMP 10
#define STEP 0.2
#define COUNT 1000

using namespace std;

template <typename T>
class Crack
{
public:
    Crack(string logFilename)
    {
        log.open(logFilename + std::to_string(rd()));
        if (!log.is_open())
        {
            exit(1);
        }
    }
    void run(string cipher, string &result_plaintext, T &result_key, double &result_score, bool logProgress)
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

        for (double temp = TEMP; temp > 0; temp-=STEP)
        {

            for (int i = 0; i < COUNT; i++)
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
                    if (logProgress)
                    {
                        log << "Score: " << best_score << endl;
                        log << keyToString(best_key) << endl;
                        log << best_plain << endl << endl;
                    }
                }
            }
        }

        // set results
        result_key = best_key;
        result_score = best_score;
        result_plaintext = best_plain;
    };

private:
    virtual T createNewKey() = 0;
    virtual T randomChangeKey(T) = 0;
    virtual string decrypt(string cipher, T &key) = 0;
    virtual double evaluateScore(string plain) = 0;
    virtual string keyToString(T &key) = 0;
    ofstream log;
    random_device rd;
};

#endif