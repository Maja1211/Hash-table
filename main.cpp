#include "HesTabela.h"
#include "AdresnaFunkcija.h"
#include "KvadratnoAdresiranje.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <random>


int main() {
    int velicina;
    int c1,c2;
    KvadratnoAdresiranje* kvadratno=nullptr;
    HesTabela* tabela=nullptr;
    HesTabela* novatabela=nullptr;
    while(true){
    cout<<"1.Kreiraj praznu hes tabelu."<<endl<<
    "2.Unesi kljuceve u tabelu."<<endl<<
    "3.Ispisi hes tabelu."<<endl<<
    "4.Unesi kljuceve iz datoteke."<<endl<<
    "5.Izbrisi kljuc iz tabele."<<endl<<
    "6.Prikazi prosjecan broj za uspjesnu pretragu."<<endl<<
    "7.Prikazi prosjecan broj za neuspjesnu pretragu."<<endl<<
    "8.Resetuj podatke za neuspjesnu pretragu."<<endl<<
    "9.Obrisi sve kljuceve u tabeli."<<endl<<
    "10.Popunjenost tabele:"<<endl<<
    "11.Velicina tabele:"<<endl<<
    "12.Broj umetnutih kljuceva:"<<endl<<
    "13.Performanse:"<<endl<<
    "14.Pretrazi neki kljuc."<<endl<<
    "15.Prekid programa."<<endl;
    cout<<endl<<"Unesite opciju koju zelite: ";
    int opcija;
    cin>>opcija;
    cout<<endl;
    if(opcija==1){
        if(tabela!=nullptr) delete tabela;
        //int velicina;
        cout<<"Unesite velicinu tabele: ";
        cin>>velicina;
        cout<<endl;
        cout<<"Unesite parametre za adresnu funkciju, c1 i c2: ";
       // int c1,c2;
        cin>>c1>>c2;
        cout<<endl;
        kvadratno=new KvadratnoAdresiranje(c1,c2);
        tabela=new HesTabela(velicina,kvadratno);
        cout<<"Kreirana je prazna hes tabela."<<endl<<endl;
    }
    if(opcija==2){
        if(tabela!=nullptr) {
            bool adaptivno;
         cout<<"Da li zelite da se radi adaptivno prosirenje tabele prilikom umetanja? (da/ne)"<<endl;
         string odgovor;
         cin>>odgovor;
         cout<<endl;
         if(odgovor=="da") {
             adaptivno=true;
         }
         if(odgovor=="ne") {
             adaptivno=false;
         }
        cout<<"Broj kljuceva koji zelite da unesete je: ";
        int broj;
        cin>>broj;
        cout<<endl;
        for(int i=0;i<broj;i++){
            int indeks;
            string string;
            cout<<"Unesite indeks i string za vas kljuc:";
            cin>>indeks;
            cin>>string;
            tabela->insertKey(indeks, string,adaptivno);
        }
        cout<<endl<<"Kljucevi su uneseni!"<<endl<<endl;
        }
        else{
            cout<<"Prvo morate da kreirate tabelu da biste unosili kljuceve!"<<endl<<endl;
        }
    }
    if(opcija==3){
        if(tabela!=nullptr){
            cout<<*tabela;
            cout<<endl;
        }else{
            cout<<"Prvo morate da kreirate tabelu da biste je ispisali!"<<endl<<endl;
        }
    }
    if(opcija==4){
        if(tabela!= nullptr){
            bool adaptivno;
            cout<<"Da li zelite da se radi adaptivno prosirenje tabele prilikom umetanja? (da/ne)"<<endl;
            string odgovor;
            cin>>odgovor;
            cout<<endl;
            if(odgovor=="da") {
                adaptivno=true;
            }
            if(odgovor=="ne") {
                adaptivno=false;
            }
        string fajl;
        cout<<"Ime datoteke je: "<<endl;
        cin>>fajl;
        ifstream datoteka(fajl);
        int indeks;
        string rijec;
        while(datoteka>>rijec>>indeks){
            tabela->insertKey(indeks, rijec,adaptivno);
        }
        cout<<endl;
        cout<<"Zavrseno unosenje rijeci iz datoteke u hes tabelu!"<<endl<<endl;
        datoteka.close();
        }
        else{
            cout<<"Prvo kreirajte tabelu!"<<endl<<endl;
        }
    }
    if(opcija==5){
        if(tabela!= nullptr){
            cout<<"Kljuc koji zelite da izbrisete je: ";
                int kljuc;
                cin>>kljuc;
                cout<<endl;
                tabela->deleteKey(kljuc);
            cout<<endl<<"Brisanje gotovo!"<<endl<<endl;
        }else{
            cout<<"Prvo kreirajte tabelu."<<endl<<endl;
        }
    }
    if(opcija==6){
        cout<<"Prosjecan broj za uspjesnu pretragu je: ";
        cout<<setprecision(3)<<tabela->avgAccessSuccess();
        cout<<endl<<endl;
    }
    if(opcija==7){
        cout<<"Prosjecan broj za neuspjesnu pretragu je: ";
        cout<<setprecision(3)<<tabela->avgAccessUnsuccess();
        cout<<endl<<endl;
    }
    if(opcija==8){
        tabela->resetStatistics();
        cout<<endl<<"Vrijednosti su resetovane!"<<endl<<endl;
    }
    if(opcija==9){
        tabela->clear();
        cout<<endl<<"Tabela je sada prazna!"<<endl<<endl;
    }
    if(opcija==10){
        cout<<"Popunjenost tabele je ";
        cout<<setprecision(3)<<tabela->fillRatio()<<"%";
        cout<<endl<<endl;
    }
    if(opcija==11){
        cout<<"Velicina tabele je: ";
        cout<<tabela->tableSize();
        cout<<endl<<endl;
    }
    if(opcija==12){
        cout<<"Broj kljuceva u tabeli je: ";
        cout<<tabela->keyCount();
        cout<<endl<<endl;
    }
    if(opcija==13){
        if(novatabela!=nullptr) delete novatabela;
        int broj;
        bool adaptivno;
        cout<<"Da li zelite da se radi adaptivno prosirenje tabele prilikom umetanja? (da/ne)"<<endl;
        string odgovor;
        cin>>odgovor;
        cout<<endl;
        if(odgovor=="da") {
            adaptivno=true;
        }
        if(odgovor=="ne") {
            adaptivno=false;
        }
        novatabela=new HesTabela(velicina,kvadratno);

        cout<<"Broj kljuceva koje zelis da dodas je: ";
        cin>>broj;
        vector<string>rijeci(broj);
        vector<int>kljucevi(broj);
        int i;
        for(i=0;i<broj;i++){
            cout<<"Na poziciji "<<i<<" je rijec: ";
            cin>>rijeci[i];
            cout<<endl;
            cout<<"Na poziciji "<<i<<" je kljuc: ";
            cin>>kljucevi[i];
            cout<<endl;
        }
        int random=10*broj;
        int min, maks;
        min=maks=kljucevi[0];
        for(int i=0;i<kljucevi.size();i++){
            novatabela->insertKey(kljucevi[i], rijeci[i],adaptivno);
            if(kljucevi[i]<min){
                min=kljucevi[i];
            }
            if(kljucevi[i]>maks){
                maks=kljucevi[i];
            }
        }
        if(random>0){
            for(int i=0;i<random;i++){
                random_device random;
                mt19937 gen(random());
                uniform_int_distribution<int> granice(min, maks);
                int rb=granice(gen);
                novatabela->findKey(rb);
            }
        }
       double uspjesnePerf=novatabela->avgAccessSuccess();
       double neuspjesnePerf=novatabela->avgAccessUnsuccess();
       cout << "Performanse za uspjesno pretrazivanje: " <<setprecision(3) <<uspjesnePerf <<endl;
       cout << "Performanse za neuspjesno pretrazivanje: "  <<setprecision(3)<< neuspjesnePerf <<endl <<endl;
    }
    if(opcija==14){
        cout<<"Koliko kljuceva zelite da pretrazite?"<<endl;
        int broj;
        cin>>broj;
        for(int i=0;i<broj;i++){
            cout<<"Unesite kljuc koji zelite da pretrazite: ";
            int kljuc;
            cin>>kljuc;
            cout<<endl;
            cout<<tabela->findKey(kljuc);
            cout<<endl<<endl;
        }
    } if(opcija==15){
        cout<<"Kraj programa..."<<endl;
        break;
    }
    if(opcija<1 || opcija>15){
        cout<<"Unijeli ste nevalidnu opciju, pokusajte ponovo..."<<endl<<endl;
    }

    }
    }




