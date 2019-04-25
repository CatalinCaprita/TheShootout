#include "Armour.h"
#include <iostream>
using namespace std;
//Constructor pentru clasa de baza ,fiecare armura ocupa un anume loc pe harta
Armour::Armour(int I,int J): SpawnI(I),SpawnJ(J)
{
}
//Constructor pentru tipul 1

Armour1::Armour1(int I,int J):Armour(I,J)
{
    Durability = 5;

}
//Redefinirea metodei DamageMitigation din clasa abstracta
//Primul tip de armura ignora 1/2 din damage-ul primit
int Armour1::DamageMitigation(int DamageTaken)
{
    if(Durability == 0)
        return -1;
    Durability--;
    return DamageTaken / 2;
}

//Destructor pentru tipul 1
Armour1::~Armour1()
{
    cout<<"\nArmor type 1 destroyed!";
    Durability = 0;
    Type = 1;
}
//Constructor pentru tipul 2
Armour2::Armour2(int I,int J):Armour(I,J)
{
    Durability = rand() % 6;
    HealFactor = 10 * (1 + rand() % 9);
    Type = 2;
}

//Redefinirea metodei DamageMitigation din clasa abstracta
//Al doilea tip de armura primeste tot damage-ul dar poate restabili un anumit procent din Health pierdut
int Armour2::DamageMitigation(int DamageTaken)
{
    if(Durability == 0 )
        return -1;
    cout << "\nThis agent has A Healing-Type Armour. It will recieve " << DamageTaken << " Damage";
    cout << "\nIt can however be healed by a factor of " << HealFactor << " for " << Durability << " more time(s). Heal? (1/0)";
    int Answer;
    do{
        cin >> Answer;
    switch( Answer)
    {
        case 1 : { Durability--; return DamageTaken * (double)(1 - ((double)HealFactor / 100 ))  ;  break; };
        case 0 : {  return DamageTaken; break; };
        default : {cout<<"\nPlease select a valid answer!";};
    }
    }while (Answer != 1 || Answer != 0);
}

//Destructor pentru tipul 2
Armour2::~Armour2()
{
    cout<<"\nArmor type 2 desrtoyed";
    Durability = 0;
}
//Constructor pentru tipul 3
Armour3::Armour3(int I,int J):Armour(I,J)
{
    Durability = 1;
    Type = 3;
}

//Redefinirea metodei DamageMitigation din clasa abstracta
//Tipul 3 de armura ignora tot damage-ul primit dar se distruge imediat
int Armour3::DamageMitigation(int)
{
    if( Durability == 0)
        return -1;
    cout << "\nAttack blocked due to type3 Armour!";
    return 0;
}

//Destructor pentru tipul 3
Armour3::~Armour3()
{
     cout<<"\nArmor type 3 destroyed!";
    Durability = 0;
}
std::pair <int,int>  Armour3::Respawn()
{
    cout<<"\nArmor type3 expired! It will redrop randombly on the map";
    Durability = 1;
    SpawnI = rand () % 25;
    SpawnJ = rand () % 25;
    return std::make_pair( SpawnI, SpawnJ);
}
