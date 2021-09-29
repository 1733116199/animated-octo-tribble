#include "substitution.h"

int main()
{
    string cipher;
    ifstream file("../q1.txt");
    if (!getline(file, cipher))
    {
        file.close();
        exit(1);
    }

    Substitution s(1);
    s.run(cipher);
}