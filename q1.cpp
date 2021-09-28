#include <math.h>
#include <random>
#include <vector>
#include <fstream>
#include "substitution.h"

int main()
{
    string cipher;
    // read ciphertext
    ifstream file("../q1.txt");
    if (!getline(file, cipher))
    {
        file.close();
        exit(1);
    }

    // decryption progress will be written in q1log.txt
    Substitution s("q1log.txt");
    map key;
    string plaintext;
    double score;

    // run decryption
    s.run(cipher, plaintext, key, score, true);

    // write results to stdout
    cout << endl
         << "===ciphertext===" << endl;
    cout << cipher << endl
         << endl;

    cout << "===key===" << endl;
    for (auto p : key)
    {
        cout << p.first << " -> " << p.second << endl;
    }
    cout << endl;

    cout << "===plaintext===" << endl;
    cout << plaintext << endl
         << endl;
}