#ifndef MAP_H
#define MAP_H
#include <iostream>
using namespace std;
// Clasa care gestioneaza desfasurarea jocului poate manipula campurile matricei
class Simulation;
class Map
{
    public:
        Map();
        virtual ~Map();
        friend std::ostream & operator << (std::ostream &, const Map &);
    private:
        char **M;
        friend class Simulation;
};

#endif // MAP_H
