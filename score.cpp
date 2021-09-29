#include "score.h"

Score::Score(string filename, int n) : n(n)
{
    ifstream file(filename);
    string line;
    total = 0;
    // read line, split by space ("ngram frequency"), store in map
    // calculate total frequency
    while (getline(file, line))
    {
        size_t i = line.find(' ');
        if (i != string::npos)
        {
            string ngram = line.substr(0, i);
            std::transform(ngram.begin(), ngram.end(), ngram.begin(), ::toupper);
            uint64 freq = stoul(line.substr(i + 1), nullptr, 0);
            ngrams[ngram] = freq;
            total += freq;
        }
    }
    file.close();
}

double Score::evaluate(string text)
{
    std::transform(text.begin(), text.end(), text.begin(), ::toupper);
    unordered_map<string, uint64> freq;

    int my_total = text.length() - n;

    double score = 0;

    // traverse all ngrams in this string
    // for each ngram found in dictionary
    // add some score according to the frequency in dictionary
    for (int i = 0; i < my_total; i++)
    {

        string ngram = text.substr(i, n);

        if (ngrams.find(ngram) != ngrams.end())
        {
            score += log10(((double)ngrams[ngram]) / total);
        }
        else
        {
            // if our dictionary does not have the ngram,
            // it must be very infrequent ngram, so give it very little score
            score += log10(0.01 / total);
        }
    }

    return score;
}