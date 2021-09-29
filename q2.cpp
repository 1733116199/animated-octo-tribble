#include <iostream>
#include <float.h>
#include <chrono>
#include "playfair.h"

int main()
{
    auto start = chrono::system_clock::now();
    string cipher;
    // read ciphertext
    ifstream file("../q2.txt");
    if (!getline(file, cipher))
    {
        file.close();
        exit(1);
    }

    // decryption progress will be written in q2log.txt
    Playfair s("q2log.txt");

    vec best_key;
    string best_plaintext;
    double best_score = -DBL_MAX;
    auto best_end = start;

    // run decryption
    for(int i = 0; i < 10000; i++){
        cout << "Round " << i << endl;
        vec key;
        string plaintext;
        double score;
        s.run(cipher, plaintext, key, score, true);
        auto end = chrono::system_clock::now();
        if(score > best_score) {
            best_score = score;
            best_plaintext = plaintext;
            best_key = key;
            best_end = end;
        }
        chrono::duration<double> elapsed_seconds = best_end - start;
        cout << "Current best result is calculated " << elapsed_seconds.count() << " seconds after program starts." << endl;
        cout << "Score of the best result: " << best_score << endl;
        cout << s.keyToString(best_key) << endl;
        cout << best_plaintext << endl << endl;
    }

    // write results to stdout
    cout << "===ciphertext===" << endl;
    cout << cipher << endl;
    cout << "Score: " << best_score << endl;

    cout << "===key===" << endl;
    cout << s.keyToString(best_key) << endl;

    cout << "===plaintext===" << endl;
    cout << best_plaintext << endl;
}