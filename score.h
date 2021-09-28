#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <math.h>

typedef unsigned long uint64;

#define MONOGRAMS "english_monograms.txt", 1
#define BIGRAMS "english_bigrams.txt", 2
#define TRIGRAMS "english_trigrams.txt", 3
#define QUADGRAMS "english_quadgrams.txt", 4

using namespace std;

class Score
{
public:
    Score(string file, int n);
    double evaluate(string text);

private:
    int n;
    unsigned long total;
    unordered_map<string, uint64> ngrams;
};

#endif