
#include <iostream>
#include <string>
using namespace std;
#ifndef UNTITLED2_ADRESNAFUNKCIJA_H
#define UNTITLED2_ADRESNAFUNKCIJA_H


class AdresnaFunkcija {
public:
    virtual int getAddress(int kljuc, int adresa, int pokusaj) const = 0;
    virtual ~AdresnaFunkcija() {}

};


#endif
