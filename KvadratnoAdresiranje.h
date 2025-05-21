
#include "AdresnaFunkcija.h"
#ifndef UNTITLED2_KVADRATNOADRESIRANJE_H
#define UNTITLED2_KVADRATNOADRESIRANJE_H


class KvadratnoAdresiranje:public AdresnaFunkcija {
private:
    int c1, c2;
public:
    KvadratnoAdresiranje(int c1, int c2): c1(c1), c2(c2) {}
    int getAddress(int kljuc, int adresa, int pokusaj) const{
        return (adresa+pokusaj*c1+pokusaj*pokusaj*c2);
    }

};


#endif
