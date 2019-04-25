#ifndef ARMOUR_H
#define ARMOUR_H
#include <iostream>
#include <utility>
using namespace std;
//Clasa abstracta Armour din care se deriveaza 3 tipuri de armuri
//int Durability - fiecare armura are un anumit numar de ture pentru care poate fi folosita
//int Type - tipul de armura in functie de care va fi modificat *Arm din clasa Agent
//int SpawnI, SpawnJ - locul in care se pozitioneaza armura pe harta
class Armour
{
    public:
        Armour(int,int);
        virtual ~Armour(){};
        virtual int DamageMitigation( int ) = 0;
    protected:
        int Durability;
        int Type;
        int SpawnI, SpawnJ;
};

//Tipul 1 de armura
class Armour1: public Armour
{
public:
    Armour1(int,int);
    ~Armour1();
    int DamageMitigation(int );

};

//Tipul 2 de armura
//Primeste damage, dar poate da Heal cu un HealFactor ales aleator
class Armour2: public Armour
{
public:
    Armour2(int,int);
    ~Armour2();
    int DamageMitigation(int );
private:
    double HealFactor;
};
//Tipul 3 de armura
//Ignora orice prim damage primit, se distrge dupa o singura folosire
class Armour3: public Armour
{
public:
    Armour3(int,int);
    int DamageMitigation(int );
    ~Armour3();
private:
    pair<int,int> Respawn();
};
#endif // ARMOUR_H
