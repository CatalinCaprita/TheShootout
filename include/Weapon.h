#ifndef WEAPON_H
#define WEAPON_H
//#include "Agent.h"
#include <iostream>
using namespace std;
/*Clasa abstracta Weapon din care se deriveaza 3 tipuri de arma, specifice pentur fiecare tip de agent
Damage - Damage-ul pe care il produce arma cand agentul va trage cu ea
Accuracy - Precizia cu care arma trage. Armele pot sau nu sa rateze in functie de acest parametru
Durability - De cate ori poate fi folosita arma
*/

class Weapon
{
    public:
        Weapon();
        virtual ~Weapon(){};
      virtual  int Hit(int) = 0;
protected:
    int Damage;
    int Accuracy;
    int Durability;

};

//Tipul BarrellGun, Specific pentru Tipul de agent Berserker
//int CritChance - arma are un anumit procentaj pentru sansa de a da mai mult Damage
class BarrellGun:public Weapon
{
public:
    BarrellGun();
    ~BarrellGun();
   int Hit(int);
private:
    int CritChance;
};

//Tipul HandGun, Specific pentru Tipul de agent Assassin
//int LuckOfThePro - Variabila care mareste damage-ul la o anumita sansa
class HandGun:public Weapon
{
public:
    HandGun();
    ~HandGun();
    int Hit(int );
private:
    int LuckOfThePro;
};
//Tipul SniperGun, Specific pentru Tipul de agent Sniper
//int ReloadTime - SniperGun-ul are nevoie de un anumit timp de reincarcare pana sa poata trage din nou
//int LastTimeShot - verifica ultima data cand Sniper-ul a tras
class SniperGun:public Weapon
{
public:
    SniperGun();
    ~SniperGun();
    int Hit(int);
private:
    int ReloadTime;
    int LastTimeShot;
};
#endif // WEAPON_H
