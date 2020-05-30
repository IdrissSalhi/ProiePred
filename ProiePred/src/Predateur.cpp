#include "Predateur.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Jungle.h"
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include "../Parametres.h"

using namespace std;


Predateur::Predateur(Jungle* jungle) : Animal ()
{
    cible=NULL;
    vitesse = Jungle::calcul_alea(4);;
    here = jungle;
    faim = 0;
    faim_max = Jungle::calcul_alea(1400);;
}



Predateur::Predateur(Predateur* pred1, Predateur* pred2, Jungle* jungle) : Animal ()
{
    cible=NULL;
    here = jungle;
    vitesse = Jungle::calcul_alea(pred1->vitesse,pred2->vitesse);
    faim = 0;
    faim_max = Jungle::calcul_alea(pred1->faim_max,pred2->faim_max);
    sommeil_max = Jungle::calcul_alea(pred1->sommeil_max,pred2->sommeil_max);


}




Predateur::~Predateur()
{
    //dtor
}

Proie* Predateur::getCible()
{
    return cible;
}

void Predateur::setCible(Proie* _cible)
{

    cible = _cible;

}


void Predateur::deplacer()
{

    if (cible==NULL)
    {
        cible = here->choix_proie(this);
    }
    else
    {
        int dis_x;
        int dis_y;
        dis_x = abs(this->x - cible->getX());
        dis_y = abs(this->y - cible->getY());


        if (this->x > cible->getX())
        {
            dx =  -floor(vitesse * ((float)dis_x/(float)(dis_y + dis_x)));
        }
        else
        {
            dx =  floor(vitesse * ((float)dis_x/(float)(dis_y + dis_x)));
        }

        if (this->y > cible->getY())
        {
            dy =  -floor(vitesse * ((float)dis_y/(float)(dis_y + dis_x)));
        }
        else
        {
            dy = floor(vitesse * ((float)dis_y/(float)(dis_y + dis_x)));
        }

        //cout << "v ="<< vitesse <<", dis_x =" << dis_x <<", dis_y =" << dis_y << ",dx ="<< dx <<", dy ="<< dy << endl;

        x = x + dx;
        y = y + dy;

        manger();
    }
}

void Predateur :: chasser()
{
    cible = here->choix_proie(this);
}

void Predateur :: manger()

{
    int distance = abs(cible->getX() - this->getX()) + abs(cible->getY() - this->getY());

    if (distance <= 30)
    {
        here->tuer_proie(cible);
        cible = NULL;
        faim = 0;

    }

}



void Predateur :: mise_a_jour()
{

    faim = faim +1;
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



    /*if (faim==faim_max)
    {
        here->tuer_pred(this);
    }*/
}


bool Predateur::doit_mourir()
{
    bool mourir = false;
    if ( faim >= faim_max)
    {
        mourir = true;
    }

    return mourir;

}

void Predateur::afficher()
{
    if (PRINT)
    {
        cout << "vitesse : "<< vitesse<<"    "<< "sommeil : "<< sommeil<<"/"<<sommeil_max <<"     "<<"faim : "<<faim<<"/"<<faim_max<<"    "<<"cible : ";

        if (cible==NULL)
        {
            cout<<"NULL"<<endl;;
        }
        else
        {
            cible->afficher();
        }
    }
}


