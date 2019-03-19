//
//  funktionen.cpp
//  kaffeemaschine
//
//  Created by florian Herrmann on 19.03.19.
//  Copyright © 2019 florian Herrmann. All rights reserved.
//

#include "funktionen.hpp"

// @UI
/* @b Description:
 Zeigt das Hauptmenue an.
 */
//@param *bool daten
//@return bool
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
#if defined debug
    cout << auswahl << endl;
#endif
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
            *pbservice = true;
            break;
        case '!':
            cout << "\nProgramm beendet sich\n";
            system("pause");
            return 0;
        default:
            cout << "Falsche Eingabe";
        return true;    }
    return false;
    
}
// @UI_zusaetze_kaffee
/* @b Description:
 Zeigt das menue fuer die auswahl derzusätze an
 */
//@param *bool
//@return void
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
#if defined debug
    cout << pbzucker << endl;
#endif
}

// @brief SI
/* @b Description:
 Zeigt das servicemenue mit allen fuellstaenden an
 */
//@param daten
//@return void
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
    return;
}

// @preis_berechnen
/* @b Description:
 Berechnet den gesamtpreis des zusammengstellten getränks
 */
//@param bool daten
//@return float
float preis_berechnen(bool bkaffee, bool bmilch, bool bzucker, bool bespresso, daten kaffee){
    float preis {0.00f};
    // Getr‰nkepreis berechnen
    if (bkaffee == true )
    {
        preis += kaffee.preis_pro_tasse;
    }
    else if (bespresso == true )
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

// @mengen_aktualisieren
/* @b Description:
 Berechnet die im vorrat verbleibenden menge
 */
//@param bool *daten
//@return void
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



