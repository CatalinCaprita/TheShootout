#include <iostream>
#include "Simulation.h"
#include <vector>
#include <utility>
#include <time.h>
using namespace std;

int main()
{
    srand(time(NULL));
    Simulation Game1;
    int Stop = 1;
    do
    {

        cout<<"\n Continue ?";
        cin>> Stop;
        if( Stop == 0)
            break;
        Game1++;
    }while (1);

    return 0;
}
