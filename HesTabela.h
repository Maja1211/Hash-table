#include <iostream>
#include <string>
#include <vector>
#include "AdresnaFunkcija.h"
using namespace std;

#ifndef UNTITLED2_HESTABELA_H
#define UNTITLED2_HESTABELA_H


class HesTabela {
private:
    struct Node{
        int kljuc;
        string vrijednost;
        bool zauzet;
        bool obrisan;
        Node(): kljuc(-1), vrijednost(""), zauzet(false), obrisan(false){}
    };

    vector<Node> tabela;
    AdresnaFunkcija* adresnaFunkcija;
    int brUspjesnihPristupa;
    int brNeuspjesnihPristupa;
    int brNepronadjenihKljuceva;
    int brNadjenih;
    int performanseNenadjenih;
    bool adaptivno;

public:
    HesTabela(int size, AdresnaFunkcija* adresnaFunkcija): tabela(size), adresnaFunkcija(adresnaFunkcija),brUspjesnihPristupa(0), brNeuspjesnihPristupa(0)
    , brNepronadjenihKljuceva(0),adaptivno(false), brNadjenih(0){}
     string findKey(int k)  {
        int adresa = k % tabela.size();
        int pocetnaAdresa= k%tabela.size();
        int pokusaj = 0;
        while (pokusaj < tabela.size()) {
            if (tabela[adresa].kljuc == k) {
                return tabela[adresa].vrijednost;
            }
            if(!tabela[adresa].zauzet && !tabela[adresa].obrisan){
                break;
            }
            pokusaj++;
            adresa = adresnaFunkcija->getAddress(k, pocetnaAdresa,pokusaj) % tabela.size();
        }
         brNepronadjenihKljuceva++;
         brNeuspjesnihPristupa+=pokusaj+1;
         return "0";
    }
    bool insertKey(int k, string s, bool adaptivno) {
        if (adaptivno && (keyCount() >= tableSize() * 0.7 || avgAccessUnsuccess()>tableSize()/4 || avgAccessSuccess()>tableSize()/4)) {
            int novaVelicina = tableSize() * 2;
            vector<Node> novaTabela(novaVelicina);
            for (int i = 0; i < tabela.size(); i++) {
                if (tabela[i].zauzet) {
                    int adresa = tabela[i].kljuc % novaVelicina;
                    int pokusaj = 0;

                    while (novaTabela[adresa].zauzet) {
                        pokusaj++;
                        adresa = adresnaFunkcija->getAddress(tabela[i].kljuc, tabela[i].kljuc, pokusaj) % novaVelicina;
                    }

                    novaTabela[adresa] = tabela[i];
                }
            }
            tabela = novaTabela;
        }
        int adresa = k % tabela.size();
        int pocetnaAdresa= k%tabela.size();
        int pokusaj = 0;
        while (pokusaj < tabela.size() && tabela[adresa].zauzet) {
            if (tabela[adresa].kljuc == k) {
                return false;
            }
            pokusaj++;
            adresa = adresnaFunkcija->getAddress(k, pocetnaAdresa, pokusaj) % tabela.size();
        }
        if (!tabela[adresa].zauzet) {
            tabela[adresa].kljuc = k;
            tabela[adresa].vrijednost = s;
            tabela[adresa].zauzet = true;
            tabela[adresa].obrisan = false;
            brUspjesnihPristupa+=pokusaj+1;
            brNadjenih++;
            return true;
        }
        return false;
    }
    bool deleteKey(int k) {
        int adresa = k % tabela.size();
        int pocetnaAdresa= k%tabela.size();
        int pokusaj = 0;
        int pocetnibr=brUspjesnihPristupa;

        while (pokusaj < tabela.size() && (tabela[adresa].zauzet || tabela[adresa].obrisan)) {
            brUspjesnihPristupa--;
            if (tabela[adresa].kljuc == k) {
                tabela[adresa].zauzet = false;
                tabela[adresa].obrisan = true;
                brNadjenih--;
                return true;
            }
            pokusaj++;
            adresa = adresnaFunkcija->getAddress(k, pocetnaAdresa, pokusaj) % tabela.size();
        }
        brUspjesnihPristupa=pocetnibr;
        return false;
    }
    double avgAccessSuccess() const{
         if(brNadjenih==0) return 0;
        return (double)(brUspjesnihPristupa)/brNadjenih;
    }
    double avgAccessUnsuccess() const{
        if (brNepronadjenihKljuceva == 0) return 0;
        return (double)(brNeuspjesnihPristupa)/brNepronadjenihKljuceva;
    }
    void resetStatistics(){
        brNepronadjenihKljuceva=0;
        brNeuspjesnihPristupa=0;
    }
    void clear(){
        for(int i=0;i<tabela.size();i++){
            tabela[i].kljuc=-1;
            tabela[i].vrijednost="";
            tabela[i].zauzet=false;
            tabela[i].obrisan= false;
        }
        resetStatistics();
        brUspjesnihPristupa=0;
    }
    int keyCount() const {
        int brojac = 0;
        for(int i = 0; i < tabela.size(); i++) {
            if (tabela[i].zauzet) {
                brojac++;
            }
        }
        return brojac;
    }
    int tableSize() const {
        return tabela.size();
    }
    friend ostream& operator<<(ostream& os, const HesTabela& hes){
        for(int i=0;i<hes.tableSize();i++){
            if(hes.tabela[i].zauzet){
                os<<i<<'.'<<hes.tabela[i].kljuc<<'-'<<hes.tabela[i].vrijednost<<endl;
            }else{
                os<<i<<'.'<<"EMPTY"<<endl;
            }
        }
        return os;
    }
   double fillRatio() const{
       return ((double)(keyCount())/tableSize())*100;
   }
    ~HesTabela() {
        delete adresnaFunkcija;
    }
};


#endif
