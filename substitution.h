#ifndef SUBSTITUTION_H
#define SUBSTITUTION_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <string>
#include <algorithm>

#include "crack.h"
#include "score.h"

using namespace std;

typedef unordered_map<char, char> map;

class Substitution : public Crack<map>
{
public:
    Substitution(unsigned numberOfThreads);
    map createNewKey();
    map randomChangeKey(map);
    string decrypt(string cipher, map &key);
    double evaluateScore(string plain);
    string keyToString(map &key);

private:
    Score *s1 = nullptr;
    Score *s2 = nullptr;
    Score *s3 = nullptr;
    Score *s4 = nullptr;
};

#endif