#include "playfair.h"

#define ROW(I) ((I) / 5)
#define COL(I) ((I) % 5)
#define INDEX(R, C) ((R)*5 + (C))
#define PREV(I) (((I)-1 + 5) % 5)

Playfair::Playfair(unsigned numberOfThreads) : Crack<vec>(numberOfThreads)
{
    s1 = new Score("../" MONOGRAMS);
    s2 = new Score("../" BIGRAMS);
    s3 = new Score("../" TRIGRAMS);
    s4 = new Score("../" QUADGRAMS);
}

vec Playfair::createNewKey()
{
    // a key for playfair cipher is a 5x5 matrix
    // represented by a vector of 25 characters
    vec result;
    for (char c = 'A'; c <= 'Z'; c++)
    {
        if (c != 'J')
        {
            result.push_back(c);
        }
    }

    if (result.size() != 25)
    {
        exit(1);
    }

    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(result), std::end(result), rng);

    return result;
}

vec Playfair::randomChangeKey(vec oldkey)
{
    vec result = oldkey;

    int dice = rd() % 40;

    switch (dice)
    {
    case 39:
    {
        std::reverse(result.begin(), result.end());
        break;
    }
    case 38:
    {
        int c1 = rd() % 5;
        int c2 = rd() % 5;
        for (int r = 0; r < 5; r++)
        {
            result[INDEX(r, c1)] = oldkey[INDEX(r, c2)];
            result[INDEX(r, c2)] = oldkey[INDEX(r, c1)];
        }
        break;
    }
    case 37:
    {
        int r1 = rd() % 5;
        int r2 = rd() % 5;
        for (int c = 0; c < 5; c++)
        {
            result[INDEX(r1, c)] = oldkey[INDEX(r2, c)];
            result[INDEX(r2, c)] = oldkey[INDEX(r1, c)];
        }
        break;
    }
    case 36:
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                result[INDEX(i, j)] = oldkey[INDEX(4 - i, j)];
            }
        }
        break;
    }
    case 35:
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                result[INDEX(i, j)] = oldkey[INDEX(i, 4 - j)];
            }
        }
        break;
    }
    default:
    {
        int l1 = rd() % 25;
        int l2 = rd() % 25;
        result[l1] = oldkey[l2];
        result[l2] = oldkey[l1];
        break;
    }
    }
    return result;
}

string Playfair::decrypt(string cipher, vec &key)
{
    for (unsigned long i = 0; i < cipher.length() / 2; i++)
    {
        int curr = 2 * i;
        int next = 2 * i + 1;

        // find position of 2 letters in matrix
        int p1 = std::find(key.begin(), key.end(), cipher[curr]) - key.begin();
        int p2 = std::find(key.begin(), key.end(), cipher[next]) - key.begin();

        if (p1 >= 25)
        {
            exit(1);
        }
        if (p2 >= 25)
        {
            exit(1);
        }

        if (ROW(p1) == ROW(p2))
        {
            // same row: move both characters up
            cipher[curr] = key[INDEX(ROW(p1), PREV(COL(p1)))];
            cipher[next] = key[INDEX(ROW(p2), PREV(COL(p2)))];
        }
        else if (COL(p1) == COL(p2))
        {
            // same col: move both characters to the left
            cipher[curr] = key[INDEX(PREV(ROW(p1)), COL(p1))];
            cipher[next] = key[INDEX(PREV(ROW(p2)), COL(p2))];
        }
        else
        {
            // a rectangle: move to opposite corners
            cipher[curr] = key[INDEX(ROW(p1), COL(p2))];
            cipher[next] = key[INDEX(ROW(p2), COL(p1))];
        }
    }

    return cipher;
}

string Playfair::keyToString(vec &key)
{
    string result = "===key===\n";
    result += string(key.begin(), key.end());
    return result;
}

double Playfair::evaluateScore(string plain)
{
    string s = "";
    s.push_back(plain[0]);
    for (size_t i = 1; i < plain.length() - 1; i++)
    {
        if ((plain[i - 1] == plain[i + 1]) && plain[i] == 'X')
        {
            continue;
        }
        s.push_back(plain[i]);
    }
    s.push_back(plain[plain.length() - 1]);
    return (s1->evaluate(s) + s2->evaluate(s) + s3->evaluate(s) + s4->evaluate(s)) / 8;
}