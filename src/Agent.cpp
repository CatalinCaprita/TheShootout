#include "Agent.h"
#include <iostream>
#include <exception>
using namespace std;
Agent::Agent(int I=16,int J=16):CurrentI(I), CurrentJ(J), HasWeapon(false),HasArmour(false), HealthBar(10), Teleported(false)
{
}
//Fiecare Agent Echipeaza Armura in acelasi fel, facand upcasting prin *Arm la tipul de armura primit ca parametru
void Agent::EquipArmour(char Type, int I,int J)
{
    cout<<"\nAgent equipped an armour of type: ";
    switch (Type)
    {
        case '1' : { Arm = new Armour1(I,J); cout<<"1 "; break;};
        case '2' : { Arm = new Armour2(I,J); cout<<"2 "; break;};
        case '3' : { Arm = new Armour3(I,J); cout<<"3 ";break;};

    }
    cout<<"("<<CurrentI<<" "<<CurrentJ<<")\n";
    HasArmour = true;
}
//Destructor pentru Agent de Baza
Agent::~Agent()
{
    W = NULL;
    Arm = NULL;
    HasArmour = false;
    HasWeapon = false;
    Teleported = false;
    inPosition = false;
}

Berserker::Berserker(int I=16,int J=16):Agent(I,J),pace(4),pace2(-3),pace3(-3)
{
    TypeName = 'b';
    VisualRange = 1;
    inPosition = true;
    cout<<"\n A Berseker  has Spawned :"<<CurrentI<<" "<<CurrentJ;
}
Berserker::~Berserker()
{
    cout<<"\nBerserker at ("<<CurrentI<<" "<<CurrentJ<<") died.\n";
}
std::pair <int,int> Berserker::WalkAttempt()
{
    //Berserlerkerul se misca in zig zag spre WEREHOUSE
    if(HasWeapon == 0)
        {
            pace *= -1;
            if( CurrentI <= 4 )
            {
                if( CurrentJ < 20)
                    return std::make_pair( CurrentI + pace / 4 , CurrentJ + 4);
               return std::make_pair( CurrentI + pace / 4 , CurrentJ + 1);
            }
              if( CurrentI > 4 )
            {
                if( CurrentJ < 20)
                    return std::make_pair( CurrentI - 4 , CurrentJ + 4);
    //Daca este in apropiere de WEREHOUSE,  pasul se micosreaza la 1
               return std::make_pair( CurrentI - 4 , CurrentJ + pace / 4);
            }
        }
    //Are arma echipata, se misca in zig-zag cu pasul 3
    //Daca ajunge pe extremitatea stanga sau dreapta, modifica directia de deplasare si coboara
    if( CurrentJ <= 3 || CurrentJ >=21)
        {
            pace3 *= -1;
            pace2 *= -1;
        }
    else
    //Daca ajunge pe extremitatea sus sau jos, modifica directia de deplasare in partea opusa

    if(CurrentI >= 21 || CurrentI <=3 )
        {
            pace3 *= -1;
        }

        pace2 *= -1;
    return std::make_pair(CurrentI + pace2 , CurrentJ + pace3);
}
////Berserkerul echipeaza o arma de tip BARRELLGUN
//In momentul in care echipeaza o arma, inseamna ca se afla in WEREHOUSE, iar pentru urmatoarea tura va iesi
//prin deplasarea pe diagonala cu 4 spatii inapoi
void Berserker::EquipWeapon()
{
    if(HasWeapon == true )
        throw AlreadyArmed();
    W = new BarrellGun();
    HasWeapon = true;
     TypeName = 'B';
    CurrentI += 4;
    CurrentJ -= 4;


}
Assassin::Assassin(int I=16,int J=16):Agent(I,J)
{
    TypeName = 'a';
    VisualRange = 2;
    inPosition = true;
    cout<<"\n An Assassin has Spawned :"<<CurrentI<<" "<<CurrentJ;
}

Assassin::~Assassin()
{
    cout<<"\nAssassin at ("<<CurrentI<<" "<<CurrentJ<<") died.\n";
}

std::pair <int,int> Assassin::WalkAttempt()
{
    //Assasiunl cauta sa se lipeasca de un zid si sa continue spre depozit pana are arma
    if(HasWeapon == 0)
        {
            if(CurrentI > 4)
            {
                if(CurrentJ < 20)
                return std::make_pair(CurrentI - 4 , CurrentJ + 4);
                if(CurrentJ < 24)
                return std::make_pair(CurrentI - 4, CurrentJ + 1);
            return std::make_pair(CurrentI - 4, CurrentJ);
            }
    //Daca e mai sus de 4 pozitii fata de extremitatea nord, micsoreaza pasul de urcare la 1
            if(CurrentI > 0)
            {
                if(CurrentJ < 20)
                    return std::make_pair(CurrentI - 1, CurrentJ + 4);
                if(CurrentJ < 24)
                    return std::make_pair(CurrentI - 1, CurrentJ + 1);
                return std::make_pair(CurrentI - 1, CurrentJ);

            }
    //Daca e pe extremitatea de nord, merge pana la WEREHOUSE "lipit"
            if(CurrentJ < 20)
                return std::make_pair(CurrentI, CurrentJ + 4);
            if(CurrentJ < 24)
                return std::make_pair(CurrentI, CurrentJ + 1);
        }
    //Are arma echipata, se muta intr-o pozitie aleatoare a calului pe tabla de sah
    int k = rand() % 8;
    return std::make_pair(CurrentI + di[k], CurrentJ + dj[k]);
}

void Assassin::EquipWeapon()
{
    if(HasWeapon == true )
        throw AlreadyArmed();
    W = new HandGun();
    TypeName = 'A';
    HasWeapon = true;
    CurrentI += 4;
    CurrentJ -= 4;


}

Sniper::Sniper(int I=16,int J=16):Agent(I,J)
{
    TypeName = 's';
    VisualRange = 5;
    inPosition = false;
    cout<<"\n A Sniper has Spawned :"<<CurrentI<<" "<<CurrentJ;
}
Sniper::~Sniper()
{
    cout<<"\nSniper at ("<<CurrentI<<" "<<CurrentJ<<") died.\n";
}
std::pair <int,int> Sniper::WalkAttempt()
{
    //Sniperul fuge cu pasul 3 pe diagonala catre depozit, apoi fuge catre Teleporterul din centru
    if(HasWeapon == 0)
        {
            if(CurrentI > 4)
            {
                if(CurrentJ < 20)
                return std::make_pair(CurrentI - 3 , CurrentJ + 3);
                if(CurrentJ < 24)
                return std::make_pair(CurrentI - 3, CurrentJ + 1);
            return std::make_pair(CurrentI - 3, CurrentJ);
            }
            if(CurrentI > 0)
            {
                if(CurrentJ < 20)
                    return std::make_pair(CurrentI -1 , CurrentJ + 3);
                if(CurrentJ < 24)
                    return std::make_pair(CurrentI -1 , CurrentJ + 1);
            return std::make_pair(CurrentI - 1, CurrentJ);
            }

            if(CurrentJ < 20)
                return std::make_pair(CurrentI, CurrentJ + 3);
            if(CurrentJ < 24)
                return std::make_pair(CurrentI, CurrentJ + 1);

        }
    //Are arma echipata, dar inca nu este teleportat
    if( !Teleported )
        {
            if( 16 - CurrentJ > 0)
                return std::make_pair(CurrentI + 1, CurrentJ + 1);
            if( 16 - CurrentJ < 0)
                return std::make_pair(CurrentI + 1, CurrentJ - 1);
        return std::make_pair(CurrentI + 1, CurrentJ );
        }
    // Daca a fost repozitionat random pe harta prin TELEPORTER, atinge pozitia finala
    if( !inPosition )
        {
            inPosition = true;
            TypeName = 'S';
        }
    //Cand se apeleaza WalkAttempt, Sniper-ul nu mai are de ce sa se mute daca este n pozitia finala
    throw PositionAquired();
}

void Sniper::EquipWeapon()
{
    if(HasWeapon == true )
        throw AlreadyArmed();
    W = new SniperGun();
    HasWeapon = true;
    CurrentI += 4;
    CurrentJ -= 4;


}
