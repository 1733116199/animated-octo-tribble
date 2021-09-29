#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <random>

#include "crack.h"
#include "score.h"

using namespace std;

typedef vector<char> vec;

class Playfair : public Crack<vec>
{
public:
    Playfair(unsigned numberOfThreads);
    vec createNewKey();
    vec randomChangeKey(vec);
    string decrypt(string cipher, vec &key);
    double evaluateScore(string plain);
    string keyToString(vec &key);

private:
    Score *s1 = nullptr;
    Score *s2 = nullptr;
    Score *s3 = nullptr;
    Score *s4 = nullptr;
    random_device rd;
};

#endif