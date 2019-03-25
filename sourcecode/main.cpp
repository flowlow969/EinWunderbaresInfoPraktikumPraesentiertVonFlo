/*!
 *
 * @brief Dies ist symolations Programm für einen kaffee automaten.
 * @file main.cpp
 * @author Florian Herrmann
 * @date März, 12, 2019
 *
 * \mainpage
 * AUTHOR:     Florian Herrmann (ufh969@gmail.com),
 * \copyright Florian Herrmann 2019 all rights reseved
 *
 * \section library_sec Librarys used in this Projekt
 * \subsection library1 standdart librarys
 * iostream, ctype.h
 *
 */

#include <iostream>
#include <ctype.h>
#include "funktionen.hpp"
// #include<conio.h> auf dem mac nicht funktional... getc(); wird durch cin ersetzt
// Definition für Debug modus
//#define debug // #steht für eine preprozesor direktive d.h das nur der pre prozesor diese anweisung liest
// defenition des namespace
using namespace std;

bool debugbool{0}; //mit der variante über bool kann der test modus jetzt auch wärend der laufzeit aktiviert werden

//! structur daten
/*!
 Struktur für alle Mengen und Preis angaben
 */
/*struct daten {
    int vorrat_kaffee;// g
    int vorrat_espresso;// g
    int vorrat_zucker;// g
    int vorrat_milch; // ml
    int vorrat_wasser;// ml
    // Mengenangaben pro Tasse
    int menge_kaffee_pro_tasse; // g
    int menge_espresso_pro_tasse; // g
    int menge_wasser_pro_tasse_kaffee;// ml
    int menge_wasser_pro_tasse_espresso; // ml
    int menge_zucker_pro_tasse;  // g
    int menge_milch_pro_tasse; // ml
    
    //Preise
    float preis_pro_tasse; // Euro
    float preis_zutaten_pro_tasse; // Euro, kann sein Milch oder Zucker
    };*/
// f¸r Passwortabfrage
char passwort[] = { 'k', 'a', 'f', 'f', 'e', 'e' };;
char eingabe[6];
int i;
bool temp;


int main()
//declaring valuse for daten k
{   daten k;
    k.vorrat_kaffee                     = 1000;
    k.vorrat_espresso                   = 1000;
    k.vorrat_zucker                     = 1000;
    k.vorrat_milch                      = 1000;
    k.vorrat_wasser                     = 1000;
    k.menge_kaffee_pro_tasse            = 5 ;
    k.menge_espresso_pro_tasse          = 5 ;
    k.menge_wasser_pro_tasse_kaffee     = 125;
    k.menge_wasser_pro_tasse_espresso   = 25 ;
    k.menge_zucker_pro_tasse            = 3 ;
    k.menge_milch_pro_tasse             = 30;
    k.preis_pro_tasse                   = 1.00f;
    k.preis_zutaten_pro_tasse           = 0.10f;
    float aktueller_preis{0.00f}; // Preis des bestellten Getr‰nks
    
    // Zustandsvariablen, die die Bestellung registrieren
    bool bkaffee;
    bool bespresso;
    bool bzucker;
    bool bmilch;
    bool bservice;
    bkaffee = bespresso = bzucker = bmilch = bservice = false;
    bool *pbkaffee = &bkaffee;
    bool *pbespresso = &bespresso;
    bool *pbzucker = &bzucker;
    bool *pbmilch = &bmilch;
    bool *pbservice = &bservice;

    //start der dauerschleife....an dieser stelle besser while(true);
    for (;;)
    {
        aktueller_preis = 0.0f;
         bkaffee = bespresso = bzucker = bmilch = bservice = false;
        //springen ins Hauptmenue
        bool shutdown = UI(pbkaffee, pbmilch, pbzucker, pbespresso, pbservice, k);
#if defined debug
        cout << "stati der zustandswerte" << endl;
        cout << "pbkaffee, pbmilch, pbzucker, pbespresso, pbservice, shutdown" << endl;
        cout << bkaffee << bmilch << bzucker << bespresso << bservice << shutdown << endl;
#endif
        
        if (debugbool == true){
            cout << "stati der zustandswerte" << endl;
            cout << "pbkaffee, pbmilch, pbzucker, pbespresso, pbservice, shutdown" << endl;
            cout << bkaffee << bmilch << bzucker << bespresso << bservice << shutdown << endl;
        }
        if (shutdown == true)
            return 0;
        
        //abfrage des service modes
        if (bservice !=false) {
            system("cls");
            cout << "Bitte geben Sie das Passwort ein:";
            for (i = 0; i < 6; ++i)
            {
                cin >> eingabe[i];
                cout << "*";
            }
            temp = true;
            for (i = 0; i < 6; ++i)
            {
                if (eingabe[i] != passwort[i])
                {
                    temp = false;
                }
            }
            if (temp == false)
            {
                cerr << "\nFalsches Passwort! Zugang zum Service-Interface verweigert!\n";
                system("pause");
                continue;
            }
            //wenn passwort korekt springen in servicemodus funktion
            else if (temp == true) {
                SI(k);
                temp = false;
            }
        }
        // ermittel und ausgeben des Preises
        aktueller_preis = preis_berechnen(bkaffee, bmilch, bzucker, bespresso, k);
    if (aktueller_preis != 0.00f) {
      
        cout << "\nBitte " << aktueller_preis << "Euro eingeben und ENTER druecken:";
        float eingabe;
        float rueckgeld;
        cin >> eingabe;
        rueckgeld = eingabe - aktueller_preis;
        if (rueckgeld >= 0.0f)
        {
            //verbleibenden lagerstand aktualisieren
            mengen_aktualisieren(bkaffee, bmilch, bzucker,bespresso, &k);
            if (rueckgeld > 0.0f)
                cout << "\nBitte " << rueckgeld << " Euro Rueckgeld und ";
            cout << "das Getraenk entnehmen -:) und eine Taste druecken";
        }
        else
        {
            cout << "\nZu wenig Geld, Bestellung abgebrochen\n";
            system("pause");
        }
    }
    }
    return 0;
}
