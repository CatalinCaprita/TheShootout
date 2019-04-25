#include "Simulation.h"
#include "Agent.h"
#include <exception>
#include <string.h>

//Exceptie pentru Tipul Sniper, daca nu si-a atnis sau nu pozita, i.e. s-a teleportat
class NotYetPositioned: public exception
{
public:
    const char *  what() {return "\nSniper has equipped the weapon but is not in position\n";};
};

// Constructor pentru Simulation
Simulation::Simulation(): RoundNo(0)
{
    //Incepe Jocul; Initializam Tabla de joc
    for(int i=0; i < 25; i++)
        for(int j = 0 ; j< 25 ; j++)
        Table.M[i][j] = '-';
    for(int i=0;i<4;i++)
        for(int j=22; j<25;j++)
        Table.M[i][j] = 'W';
    Table.M[16][16] = 'T';
    int stop = 0;
    int SpawnI, SpawnJ;
    //Momentul in care se Pozitioneaza aleator pe harta tipul de agent ales de user
    do{
            cout<<"\nWhat is the next type of agent ? 1.Berserker; 2.Assassin; 3.Sniper; ? Press 0 to terminate ";
            int TypeGenerator;//= rand () % 3;
            cin>>TypeGenerator;

        do{
            SpawnI = rand() % 25;
            SpawnJ = rand() % 25;

        }while(Table.M[SpawnI][SpawnJ] != '-');

            Agent *A;
            stop = 0;
            switch ( TypeGenerator )
        {
            case 0 : { stop = 1; break; };
            case 1 : { A = new Berserker(SpawnI,SpawnJ);  Table.M[SpawnI][SpawnJ] = A->TypeName; break;};
            case 2 : { A = new Assassin(SpawnI,SpawnJ); Table.M[SpawnI][SpawnJ] = A->TypeName; break;};
            case 3 : { A = new Sniper(SpawnI,SpawnJ);  Table.M[SpawnI][SpawnJ] = A->TypeName; break;};
            default :{ cout<<"\n Invalid Type Selected! ";};
        }
        //Introduc in vectorul de agenti
            AgentArray.push_back(A);

    }while( stop == 0);
 // Plasarea random pe harta a unor armuri
     cout<<"\nThere can be at most 10 armours randomly split around the map. Choose their type!";
    stop = 0 ;
    for(int i=0 ; i<10 && stop == 0; i++)
    {
        int ArmourType;
        cout<<"\nNext armour is of type : ";
        cin>>ArmourType;
        stop = 0;
        do{
             SpawnI = rand() % 25;
             SpawnJ = rand() % 25;

        }while( Table.M[SpawnI][SpawnJ] != '-');
        switch ( ArmourType )
        {
            case 0 : { stop = 1; break; };
            case 1 : { Table.M[SpawnI][SpawnJ] = '1'; break;};
            case 2 : { Table.M[SpawnI][SpawnJ] = '2'; break;};
            case 3 : { Table.M[SpawnI][SpawnJ] = '3'; break;};
            default :{ cout<<"\nInvalid Type Selected! "; i--; };
        }
    }
    cout<<(*this);
}
//Supraincarcare pentru operatorul de afisare
std::ostream & operator << (std::ostream &out,const Simulation &S)
{
    out<<"\nCurrent Status:\nRound "<< S.RoundNo<<endl;;
    out<<S.Table;
    return out;
}

//Verifica daca pe Coordonatele I si J de pe Table se poate face mutarea
//Daca pozitia este in interiorul Table si daca nu e ocupata de alt Agent
bool Simulation::ValidWalk(int I,int J) const
{
    if(I < 0 || J < 0 || I >= 25 || J >= 25 || strchr("ABSabs",Table.M[I][J]))
        return false;
    return true;
}

//Metoda pentru fiecare Agent
//Scaneaza imprejurul agentului in functie de VisualRange si verifica daca exista inamici
void Simulation::SpotEnemy( Agent *a)
{
    if( !a->inPosition )
        throw NotYetPositioned();

    for(int i = a->CurrentI - a->VisualRange ; i <= a->CurrentI + a->VisualRange + 1; i++)
        for(int j = a->CurrentJ - a->VisualRange ; j <= a->CurrentJ + a->VisualRange + 1 ; j++)
    {
        //Daca Sunt in interiorul Table si Nu este chiar pozitia Agentului
        if(i < 25 && j < 25 && i >= 0 && j >=0  && i != a->CurrentI && j != a->CurrentJ)
           {
               if( strchr( "ABSabs",Table.M[i][j]) )
        //Cauta in AgentArray, agentul de pe configuratia respectiva
               for(unsigned  K = 0 ; K < AgentArray.size() ; K++)
        //Exista posibilitatea ca agentul sa isi foloseasca arma in aceeasi runda de mai multe ori, dar sa fie distrusa
        //intre timp, deci verifica daca mai poate folosi
                if( AgentArray[K]->CurrentI == i && AgentArray[K]->CurrentJ == j && a->HasWeapon == true )
                {

                    int IncomingDmg = a->W->Hit(RoundNo);
                //Daca Hit() reutrneaza -1 inseamna ca durabilitatea este 0, deci arma se distruge
                    if( IncomingDmg < 0)
                        {
                            delete a->W;
                            a->HasWeapon = false;
                            a->W = NULL;
                        }
                    else
                    {

                        cout<<"\nAgent (" << AgentArray[K]-> CurrentI <<"  " << AgentArray[K]->CurrentJ << ") ( HP: "<<AgentArray[K]->HealthBar<<") was hit.";
                        cout<<"by ("<<a->CurrentI<<" "<<a->CurrentJ<<")"<<endl;
                    //Exista posibilitatea ca agentul sa aibe armura, deci Damage-ul poate fi redus
                            if(AgentArray[K]->HasArmour)
                            {
                                int ActualDmg = AgentArray[K]->Arm->DamageMitigation( IncomingDmg );
                    //Daca DamageMitigation intoarce -1, inseamna ca armura are Durability 0 , deci e distrusa
                                if(ActualDmg == -1)
                                {
                                    AgentArray[K]->HasArmour = false;
                                    delete (AgentArray[K]->Arm);
                                    AgentArray[K]->Arm = NULL;
                                }
                    //Damage-ul primit de la arma este redus
                                else
                                IncomingDmg = ActualDmg;
                            }
                        AgentArray[K]->HealthBar -= IncomingDmg;
                        cout<<"\nRecieved "<<IncomingDmg<<" damage"<<endl;
                    //Agentul A fost omorat, deci este sters de pe Table si din vectorul de agenti
                    if(AgentArray[K]-> HealthBar <= 0)
                        {
                            Table.M[AgentArray[K]->CurrentI][AgentArray[K]->CurrentJ] = '-';
                            delete AgentArray[K];
                            AgentArray.erase(AgentArray.begin()+K);
                        }
                    }

                }
           }
    }

}
//Supraincarcarea operatorului ++ Care inseamna ca se desfasoara o noua runda
void Simulation::operator ++(int Dummy)
{

    RoundNo++;
    //Afisez situatia curenta: Pozitiile fiecarui Agent viu de pe Table
    cout<<(*this);
    //Momentul in care fiecare agent Ataca
     cout<<"\nNow it's Attacking Time\n";
    for(unsigned  i = 0; i < AgentArray.size(); i++)
        if(AgentArray[i]->HasWeapon == true)
        {

            try{
                SpotEnemy(AgentArray[i]);
            }
            //Daca prind NotYetPositioned, am un sniper care nu este teleportat, deci nu poate
            //Folosi arma inca
            catch (NotYetPositioned &e)
            {
                continue;
            }
        }

    //Dupa ce toti agentii ataca, toti agentii se misca pe Table
    cout<<"\nEverybody Moves.";
    for(unsigned  i = 0; i < AgentArray.size(); i++)
    {

        try{
        // Se trimit coordonatele la care Agentul i vrea sa se mute pe Table si se verifica daca este posibil
       std::pair <int,int > New = AgentArray[i]->WalkAttempt();

            if( ValidWalk( New.first, New.second ) )
            {

            //Agentul paraseste pozitia curenta
                Table.M[AgentArray[i]->CurrentI][AgentArray[i]->CurrentJ] = '-';
                AgentArray[i]->CurrentI = New.first;
                AgentArray[i]->CurrentJ = New.second;

            //Agentul Ajunge in WEREHOUSE
                if(Table.M[AgentArray[i]->CurrentI][AgentArray[i]->CurrentJ]  == 'W')
                {
                    try
                    {
                        AgentArray[i] -> EquipWeapon();
            //Daca agentul are deja o arma echipata
                    }catch (AlreadyArmed &e)
                    {
                        cout<<e.what();
                        continue;
                    }

                }
            //Daca Agentul nimereste pe o armura, o echipeaza
            //Nou comment pentru git
                else
                if( isdigit( Table.M[AgentArray[i]->CurrentI][AgentArray[i]->CurrentJ] ) )
                   AgentArray[i]->EquipArmour( Table.M[AgentArray[i]->CurrentI][AgentArray[i]->CurrentJ], New.first, New.second );
            //Daca Agentul nimereste pe TELEPORTER, se repozitioneaza pe coordonate aleatoare pe Table
                    else
                        if(Table.M[New.first][New.second] == 'T')
                {
                    AgentArray[i] -> Teleported = true;
                    AgentArray[i] -> CurrentI = rand() % 21 ;
                    AgentArray[i] -> CurrentJ = rand() % 21 ;
                }

        //Configurez Pe pozitia mutarii litera specifica Tipului de Agent care se misca
        Table.M[AgentArray[i]->CurrentI][AgentArray[i]->CurrentJ] = AgentArray[i]->TypeName;
            }
        }

        catch( PositionAquired &e )
            {
                Table.M[AgentArray[i]->CurrentI][AgentArray[i]->CurrentJ] = AgentArray[i]->TypeName;
                continue;
            }
    }
    cout<<"\nEverybody moved.\n";

}
//Destructorul care elibereaza vectorul de agenti
Simulation::~Simulation()
{
    cout<<"\nGame Finished";
    AgentArray.clear();
    RoundNo = 0;
}
