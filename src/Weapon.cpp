#include "Weapon.h"
#include "Agent.h"
#include <iostream>
using namespace std;
//Constructor pentru clasa de baza
Weapon::Weapon()
{
    cout<<"weapon Created!";
}
//Constructor pentru BarrellGun
BarrellGun::BarrellGun():Weapon()
{
    Accuracy = 65;
    Durability = 3;
    Damage = 5;
}
//Desturctor pentru BArrellGun
BarrellGun::~BarrellGun()
{
    cout<<"\nBarrellGun destroyed";
    Accuracy = 0;
    Durability = 0;
    Damage = 0;
}
//Definirea functiei virtuale Hit din clasa abstracta
int BarrellGun::Hit(int RoundNo = 0)
{
    if(Durability == 0)
        return -1;
    int Crithit = rand() % 100;
    int HitChance = rand() % 100;
    //Daca a nimerit , exista sansa de lovitura critica
    if(HitChance <= Accuracy)
    {
        int Deals = Damage;
    //Daca e lovitura critica
        if (Crithit <= CritChance)
            Deals = Damage + 4;
        Durability--;
        return Deals;
    }
    //Daca nu nimereste, durabilitatea va scadea oricum
    Durability--;
    cout<<"The Gun Missed ! ";
    return 0;
}
//Constructor pentru Handgun
HandGun::HandGun():Weapon(), LuckOfThePro(60)
{
    Accuracy = 85 ;
    Durability = 5 ;
    Damage = 3 ;
}
//Destructor pentru Handgun
HandGun::~HandGun()
{
    Accuracy = 0 ;
    Durability = 3 ;
    Damage = 0 ;
    cout<<"\nHandgun destroyed;";
}
//Redefinirea functiei virtuale Hit din clasa abstracta
//Se comporta ca in cazul BarrellGun
int HandGun::Hit(int RoundNo = 0)
{
    if( Durability == 0)
        return -1;
    int Draw = rand() % 100;
    int HitChance = rand() % 100;
    if(HitChance <= Accuracy)
    {
        int Deals = Damage;
        if (Draw <= LuckOfThePro)
        Deals = Damage * 2;
    Durability--;
    return Deals;
    }
    Durability--;
        cout<<"The Gun Missed ! ";
        return 0;
}
//Constructor pentru SniperGun
SniperGun::SniperGun():Weapon(), ReloadTime (0),LastTimeShot(-1)
{
    Accuracy = 100 ;
    Durability = 4 ;
    Damage = 5 ;

}
//Destructor pentru Handgun
SniperGun::~SniperGun()
{
    Accuracy = 0 ;
    Durability = 0;
    Damage = 0 ;
    cout<<"\nSniperGun destroyed ";
}

int SniperGun::Hit(int RoundNo = 0)
{
//  SniperGun nu rateaza niciodata, dar are nevoie de 2 ture ca sa poata fi folosit iarasi
    if(Durability == 0)
        return -1;
    if(ReloadTime == 0)
    {
        Durability--;
        ReloadTime = 2;
        LastTimeShot = RoundNo;
        return Damage;
    }
    if(RoundNo <= LastTimeShot + 2)
    {
        cout<<"\nSniper is Still Reloading!;";
        return 0;
    }

    ReloadTime--;
    return 0;
}
