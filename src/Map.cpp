#include "Map.h"
#include <iostream>
#include <exception>
using namespace std;
//Clasa care gestioneaza o harta. Matrice patratica de 25x25 de caractere.
//
Map::Map()
{
    try{
    M=new char*[25];
    }
    catch(bad_alloc)
    {
        cout<<"\nUnavailable Memory";
    }
    for(int i=0;i<25;i++)
    try{
        M[i]=new char[25];

    }
    catch(bad_alloc)
    {
        cout<<"\nUnavailable Row;";
    }
}
//Supraincarca operatorul << pentru afisare
std::ostream & operator << (ostream &out, const Map & Table)
{
    for(int i=0 ; i < 25; i++)
    {
        for(int j = 0; j < 25 ; j++)
            out << Table.M[i][j] << " ";
        out << endl;
    }
    return out;
}
//Destructorul matricei de caractere
Map::~Map()
{
    for(int i= 24; i >= 0; i--)
    delete[] M[i];
    delete M;
}
