#ifndef SIMULATION_H
#define SIMULATION_H
#include <iostream>
#include "Map.h"
#include "Agent.h"
#include "Armour.h"
#include "Weapon.h"
#include <utility>
#include <vector>
using namespace std;

////Clasa Simulatiion, care gestioneaza desfasurarea unei runde
////Map Table - un obiect de tipul Map, care va descrie configuratia unei runde
////          - la un anumit moment din joc, pe Table apar caractere mari sau mici - tipul de Agent,
////            cifre - tipul de armura
////            T - teleporterul
////            W - zona WEREHOUSE, de unde agentii isi procura armele
////vector <Agent *> AgentArray - vector de pointeri de tipul clasei de baza Agent
////                            - prin parcugerea acestuia se determina comportamentul unui agent pe runda
////int RoundNo - retine numarul rundei curente

class Simulation
{
    public:
        Simulation();
        ~Simulation();
        void SpotEnemy( Agent *) ;
        bool ValidWalk( int, int ) const ;
        void operator ++ (int);
        friend std::ostream& operator << (std::ostream &, const Simulation &);
    private:
        Map Table;
        vector <Agent *> AgentArray;
        int RoundNo;
};

#endif // SIMULATION_H
