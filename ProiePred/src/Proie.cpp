#include "Proie.h"
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include "Jungle.h"
#include "../Parametres.h"
#include <iostream>


using namespace std;

Proie::Proie() : Animal()
{
    dx = (rand()%(vitesse*2 + 1)) - vitesse;

    int v_restante;
    v_restante = abs(vitesse - dx) ;

    dy = (rand()%(v_restante*2 +1)) - v_restante;
}




Proie::Proie(Proie* proie1, Proie* proie2, Jungle* jungle) : Animal()
{

    vitesse = Jungle::calcul_alea(proie1->vitesse,proie2->vitesse);
    sommeil_max = Jungle::calcul_alea(proie1->sommeil_max,proie2->sommeil_max);

}






Proie::~Proie()
{
    //dtor
}







void Proie::deplacer()
{
    x = x + dx ;
    y = y + dy ;

    if (x > LARGEUR || x < 0)
    {
        dx = - dx ;
    }

    if (y > HAUTEUR || y < 0)
    {
        dy = - dy ;
    }



}

void Proie :: mise_a_jour()
{
    if (dormir == false)
    {
        deplacer();
        sommeil = sommeil+1;
        if (sommeil>= sommeil_max)
        {
            dormir = true;
        }
    }

    else
    {
        sommeil = sommeil - 2;
        if (sommeil <=0 )
        {
            dormir = false;
        }
    }

}

void Proie :: afficher()
{
    if (PRINT)
    {
        cout << "vitesse : "<< vitesse <<"   " << "sommeil: "<< sommeil <<"/"<<sommeil_max <<endl;
    }
}
