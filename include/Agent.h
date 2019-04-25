#ifndef AGENT_H
#define AGENT_H
#include <string>
#include <iostream>
#include <exception>
#include "Armour.h"
#include "Weapon.h"
#include "Armour.h"
using namespace std;

//Clasa care gestioneaza runda are acces la campurile unui agent
class Simulation;
//Exceptie pentru tipul de agent "Sniper". Aceasta este aruncata in momentul in care un agent
//de tip sniper se teleporteaza. Abia dupa ce acesta este teleportat la noua sa locatie
//el va ramane acolo tot restul jocului si doar dupa ce atinge aceasta pozitie poate sa traga.
class PositionAquired: public exception
{
public:
    const char *what(){return "Position aquired.Waiting";}
};

//Exceptie pentru cazul in care un agent ajunge din nou in WEREHOUSE, dar are deja arma
class AlreadyArmed: public exception
{
public:
    const char *  what() {return "\nAlready Armed!\n";};
};

////Clasa abstracta Agent din care se deriveaza cele 3 tipuri de agent.
//Typename - in functie de tipul agentului care vor indica unde se muta acesta pe harta
//         - literele mici  a, b, s indica faptul ca agentul nu este inarmat
//         - literele mari  A, B, S indica faptul ca agentul  este inarmat
//Current I, Current J - coordonatele pozitiei curente ale unui agent pe harta
//VisualRange - distanta la care poate vedea tipul de agent in jurul sau
//HasWeapon - indica daca agentul are arma echipata
//HasArmour - indica daca agentul are armura echipata
//HealthBar - viata curenta pe care o are agentul
//*W - pointer de tip arma prin care se gestioneaza cum actioneaza agentul arma , daca o are
//*Arm - pointer de tip armura care gestioneaza cum functioneaza armurma agentului, daca are
//inPosition - determina daca agentul este gata de atac. Pentru Berserker si Assassin aceasta va fi activata in momentul echiparii armei

class Agent
{
    public:
        Agent(int,int);
        virtual ~Agent();
        virtual pair <int,int> WalkAttempt() = 0;
        void EquipArmour(char, int, int);
        virtual void EquipWeapon() = 0;
    protected:
        char TypeName;
        int CurrentI,CurrentJ;
        int VisualRange;
        bool HasWeapon; // fiecare arma este specifica tipului derivat de agent
        bool HasArmour;
        int HealthBar;
        Armour *Arm;
        Weapon *W;
        bool Teleported;
        bool inPosition;
        friend class Simulation;
};

//Tipul Berserker
//pace - indice care se folosesce pentru mutarile in zig-zag ale agentului pana ajunge la werehouse
//pace2, pace 3 - indici folositi pentru mutarile in zig-zag si spre norul/sudul hartii dupa ce iese din werehouse

class Berserker:public Agent
{
public:
    Berserker(int,int);
    ~Berserker();
    pair <int,int> WalkAttempt();
    void EquipWeapon();
private:
    int pace,pace2,pace3;
};

//Tipul Assassin
////const int di[], dj[] - array-uri care tin minte coordonatele pentru configuratiile posibile
////                        cand agentul se muta precum calul pe tabla de sah
////int pace - variabila folosita pentru miscarea in zig-zag inainte de a ajunge in WEREHOUSE
class Assassin:public Agent
{
public:
    Assassin(int,int);
    ~Assassin();
    pair <int,int> WalkAttempt();
    void EquipWeapon();
private:
    int pace;
    const int di[8] = {-2,-2,-1,1,2,2,1,-1};
    const int dj[8] = {-1,1,2,2,1,-1,-2,-2};
};

//Tipul Sniper
//int pace- variabila folosita pentru miscarea in zig-zag inainte de a ajunge in WEREHOUSE
class Sniper:public Agent
{
public:
    Sniper(int,int);
    ~Sniper();
    pair <int,int> WalkAttempt();
    void EquipWeapon();
private:
    int pace;
};
#endif // AGENT_H
