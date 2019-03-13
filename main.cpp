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



using namespace std;



/**
 @ingroup
 @const
 @brief    Gibt die maximale Größe des eingelesen Strings an.
 */
struct daten {
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
    };
// f¸r Passwortabfrage
char passwort[] = { 'k', 'a', 'f', 'f', 'e', 'e' };;
char eingabe[6];
int i;
bool temp;

bool UI(bool *pbkaffee, bool *pbmilch, bool *pbzucker, bool *pbespresso, bool *pbservice, daten kaffee);
void UI_zusaetze_kaffee(bool beide, bool *pbmilch, bool *pbzucker);
void SI(daten kaffee);
float preis_berechnen(bool bkaffee, bool bmilch, bool bzucker, bool bespresso, daten kaffee);
void mengen_aktualisieren(bool bkaffee, bool bmilch, bool bzucker,bool bespresso, daten *pkaffee);


int main()
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
    

    
    
    
    for (;;)
    {
        aktueller_preis = 0.0f;
        UI(pbkaffee, pbmilch, pbzucker, pbespresso, pbservice, k);
        if (bservice == true) {
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
            
            else if (temp == true) {
                SI(k);
            }
        };
        aktueller_preis = preis_berechnen(bkaffee, bmilch, bzucker, bespresso, k);
        cout << "\nBitte " << aktueller_preis << "Euro eingeben und ENTER druecken:";
        float eingabe;
        float rueckgeld;
        cin >> eingabe;
        rueckgeld = eingabe - aktueller_preis;
        if (rueckgeld >= 0.0f)
        {
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
    return 0;
}

void gotoxy(int x, int y) {
    printf("\x1b[%d;%df", y, x);
}



bool UI(bool *pbkaffee, bool *pbmilch, bool *pbzucker, bool *pbespresso, bool *pbservice, daten kaffee)
{
    system("cls");
    cout << "Herzlich willkommen beim Kaffe-Automaten!\n";
    cout << "\n Preis pro Tasse :\nKaffee oder Espresso:\t" << kaffee.preis_pro_tasse << "\tEuro\nMilch oder Zucker:\t" << kaffee.preis_zutaten_pro_tasse << "\tEuro\n\n";
    cout << "Bitte w\x84 \bhlen Sie aus:\n";
    cout << "(k)Kaffee\n";
    cout << "(e)Espresso\n";
    cout << "(s)Service-Mode\n";
    
    char auswahl;
    cin >> auswahl;
    
    switch (auswahl)
    {
        case 'k':
            cout << "\nSie haben sich f\x81 \br die Auswahl Kaffee " << auswahl << " entschieden\n";
            *pbkaffee = true;
            UI_zusaetze_kaffee(true,pbmilch,pbzucker);
            break;
        case 'e':
            cout << "\nSie haben sich f\x81 \br die Auswahl Espresso " << auswahl << " entschieden\n";
            *pbespresso = true;
            UI_zusaetze_kaffee(false, pbmilch, pbzucker);
            break;
        case 's':
            return true;
        case '!':
            cout << "\nProgramm beendet sich\n";
            system("pause");
            return 0;
        default:
            cout << "Falsche Eingabe";
               return true;    }
    return false;
            
}
void UI_zusaetze_kaffee(bool beide, bool *pbmilch, bool *pbzucker){
    
    char auswahl;
    cout << "\nM\x94 \bchten Sie Zucker (j\\n)?";
    cin >> auswahl;
    switch (auswahl)
    {
        case'j':
            *pbzucker = true;
            break;
        case'n':
            break;
        default:
            cout << "\nFalsche Eingabe!\n";
            system("pause");
           
    }
    if (beide == false){
        return ;
    }
    cout << "\nM\x94 \bchten Sie Milch(j\\n)?";
    cin >> auswahl; // ersetzt_getche()
    switch (auswahl)
    {
        case'j':
            *pbmilch = true;
            break;
        case'n':
            break;
        default:
            cout << "\nFalsche Eingabe!\n";
            system("pause");
    }
    
}
void SI(daten kaffee){
    system("cls");
    cout << "Service-Interface \n";
    cout << "----------------------------------------------------------------\n";
    cout << "Noch vorhandene Mengen:\nKaffee\t:" << kaffee.vorrat_kaffee << " g\tMilch:\t" << kaffee.vorrat_milch <<
    " ml\nEspresso:" << kaffee.vorrat_espresso << " g\tWasser:\t" << kaffee.vorrat_wasser << " ml\nZucker:  \t" << kaffee.vorrat_zucker << " g\n";
    cout << "----------------------------------------------------------------\n";
    cout << "Mengen pro Tasse :\nKaffee:\t\t" << kaffee.menge_kaffee_pro_tasse << " g\tMilch:\t" << kaffee.menge_milch_pro_tasse <<
    " ml\nEspresso:\t" << kaffee.menge_espresso_pro_tasse << " g\tWasser fuer Kaffee:\t" << kaffee.menge_wasser_pro_tasse_kaffee << " ml\nZucker:\t" << kaffee.menge_zucker_pro_tasse <<
    " g\t\tWasser fuer Espresso:\t" << kaffee.menge_wasser_pro_tasse_espresso << " ml\n";
    cout << "----------------------------------------------------------------\n";
    system("pause");
    
}
float preis_berechnen(bool bkaffee, bool bmilch, bool bzucker, bool bespresso, daten kaffee){
    float preis {0.00f};
    // Getr‰nkepreis berechnen
    if (bkaffee == true )
    {
        preis += kaffee.preis_pro_tasse;
    }
    if (bzucker == true)
    {
        preis += kaffee.preis_zutaten_pro_tasse;
    }
    if (bmilch == true)
    {
        preis += kaffee.preis_zutaten_pro_tasse;
    }
    return  preis;
    
}
void mengen_aktualisieren(bool bkaffee, bool bmilch, bool bzucker,bool bespresso, daten *pkaffee){
    
    // Vorratsmengen aktualisieren
    if (bkaffee == true)
    {
        pkaffee->vorrat_kaffee -= pkaffee->menge_kaffee_pro_tasse;
        pkaffee->vorrat_wasser -= pkaffee->menge_wasser_pro_tasse_kaffee;
    }
    else if (bespresso == true)
    {
        pkaffee->vorrat_espresso -= pkaffee->menge_espresso_pro_tasse;
        pkaffee->vorrat_wasser -= pkaffee->menge_wasser_pro_tasse_espresso;
    }
    if (bzucker == true)
    {
       pkaffee->vorrat_zucker -= pkaffee->menge_zucker_pro_tasse;
    }
    if (bmilch == true)
    {
       pkaffee->vorrat_milch -= pkaffee->menge_milch_pro_tasse;
    }
    cout << "Ihr Getraenk wird zubereitet..... \n";
    
}
                
