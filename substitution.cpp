#include "substitution.h"

Substitution::Substitution(unsigned numberOfThreads) : Crack<map>(numberOfThreads)
{
    srand(time(NULL));
    s1 = new Score("../" MONOGRAMS);
    s2 = new Score("../" BIGRAMS);
    s3 = new Score("../" TRIGRAMS);
    s4 = new Score("../" QUADGRAMS);
}

map Substitution::createNewKey()
{
    // a key for substitution cipher is mapping between letters {A-Z} to letters {A-Z}
    map result;
    for (char c = 'A'; c <= 'Z'; c++)
    {
        result[c] = c;
    }
    return result;
}

map Substitution::randomChangeKey(map oldkey)
{
    // randomly swap two mappings in current key
    map result = oldkey;
    char l1 = (random() % 26) + 'A';
    char l2 = (random() % 26) + 'A';
    result[l1] = oldkey[l2];
    result[l2] = oldkey[l1];
    return result;
}

string Substitution::decrypt(string cipher, map &key)
{
    // for each character, change it to the mapped character in key
    for (unsigned long i = 0; i < cipher.length(); i++)
    {
        cipher[i] = key[cipher[i]];
    }
    return cipher;
}

string Substitution::keyToString(map &key)
{
    string result = "===key===\n";
    for (auto p : key)
    {
        result.push_back(p.first);
        result += " -> ";
        result.push_back(p.second);
        result.push_back('\n');
    }
    return result;
}

double Substitution::evaluateScore(string plain)
{
    return s1->evaluate(plain) + s2->evaluate(plain) + s3->evaluate(plain) + s4->evaluate(plain);
}