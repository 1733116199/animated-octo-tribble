#include "playfair.h"

int main()
{
    string cipher;
    ifstream file("../q2.txt");
    if (!getline(file, cipher))
    {
        file.close();
        exit(1);
    }

    Playfair p(20);
    p.run(cipher);
}