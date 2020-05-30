#include "Animal.h"
#include "../Parametres.h"
#include <time.h>
#include <cstdlib>
#include "Jungle.h"
#include <stdio.h>

Animal::Animal()
{
    x=rand()%LARGEUR;
    y=rand()%HAUTEUR;
    dx=2;
    dy=1;
    vitesse = Jungle::calcul_alea(5);
    sommeil = 0;
    sommeil_max = Jungle::calcul_alea(700);
}

Animal::Animal (int _x, int _y, int _dx, int _dy)
{
    x = _x;
    y = _y;
    dx = _dx;
    dy = _dy;
}

Animal::~Animal()
{
    //dtor
}


int Animal :: getX()
{
    return x;
}

int Animal :: getY()
{
    return y;
}



bool Animal::doit_dormir()
{
    dormir = false;
    if (sommeil >= sommeil_max)
    {
        dormir = true;
    }

    return dormir;
}


