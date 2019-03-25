//
//  funktionen.hpp
//  kaffeemaschine
//
//  Created by florian Herrmann on 19.03.19.
//  Copyright © 2019 florian Herrmann. All rights reserved.
//

#ifndef funktionen_hpp
#define funktionen_hpp

#include <iostream>
#include <ctype.h>
// defenition des namespace
using namespace std;

#endif /* funktionen_hpp */
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


/* Function prototypes -------------------------------------------------------*/
bool UI(bool *pbkaffee, bool *pbmilch, bool *pbzucker, bool *pbespresso, bool *pbservice, daten kaffee);
void UI_zusaetze_kaffee(bool beide, bool *pbmilch, bool *pbzucker);
void SI(daten kaffee);
float preis_berechnen(bool bkaffee, bool bmilch, bool bzucker, bool bespresso, daten kaffee);
void mengen_aktualisieren(bool bkaffee, bool bmilch, bool bzucker,bool bespresso, daten *pkaffee);
/*****END OF FILE****/
