#include "Jungle.h"
#include <list>
#include <stdlib.h>
#include "Proie.h"
#include "Animal.h"
#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

Jungle::Jungle()
{
    //ctor
}

Jungle::~Jungle()
{
    //dtor
}


void Jungle::ajouter_proie (Proie* proie)
{
    proies.push_front(proie);

}

void Jungle::ajouter_predateur (Predateur* predateur)
{
    predateurs.push_front(predateur);
}

void Jungle::deplacer_tout()
{

    for(list<Proie*>::iterator it = proies.begin(); it!= proies.end(); ++it)
    {

        (*it)->mise_a_jour();

    }



    for(list<Predateur*>::iterator it = predateurs.begin(); it!= predateurs.end(); ++it)
    {

        (*it)->mise_a_jour();

    }


}

Proie* Jungle :: choix_proie( Predateur* predateur)

{
    if (proies.size() == 0) return NULL;

    else
    {
        Proie* proche;
        proche = *(proies.begin());


        for (list<Proie*>::iterator it = proies.begin(); it!= proies.end(); ++it)
        {
            int distance_1;
            int distance_2;
            distance_1 = abs((*it)->getX() - predateur->getX()) + abs((*it)->getY() - predateur->getY());
            distance_2 = abs(proche->getX() - predateur->getX()) + abs(proche->getY() - predateur->getY());
            if ( distance_1 < distance_2)
            {
                proche = *(it);
            }
        }

        return proche;


    }
}



void Jungle::tuer_proie(Proie* cible)
{
    proies.remove(cible);
    delete cible;

    for(list<Predateur*>::iterator it = predateurs.begin(); it!= predateurs.end(); ++it)
    {
        if((*it)->getCible() == cible)
        {
            (*it)->setCible(NULL);
        }
    }
}

void Jungle::tuer_pred(Predateur* pred)
{
    predateurs.remove(pred);
    delete pred;
}

void Jungle :: extinction ()
{


    predateurs_a_tuer.clear();

    for(list<Predateur*>::iterator it = predateurs.begin(); it!= predateurs.end(); ++it)
    {

        if ((*it)->doit_mourir())
        {
            predateurs_a_tuer.push_front(*it);

        }
    }





    for(list<Predateur*>::iterator it = predateurs_a_tuer.begin(); it!= predateurs_a_tuer.end(); ++it)
    {
        predateurs.remove(*it);
        delete (*it);
    }
    predateurs_a_tuer.clear();

    if (proies.size()==0)
    {
        ajouter_proie(new Proie());
        ajouter_proie(new Proie());
    }

    if (predateurs.size()==0)
    {
        ajouter_predateur(new Predateur(this));
        ajouter_predateur(new Predateur(this));
    }
}



int Jungle :: calcul_alea(int n)
{

    int resultat;
    resultat = rand()%(int)ceil((0.4*n))+ ceil(0.8*n);

    return resultat;
}

int Jungle :: calcul_alea(int a, int b)
{
    int max_ = std::max(a,b);
    int min_ = std::min(a,b);

    max_ = max_ + 0.2*max_;
    min_ = min_ - 0.2*min_;

    int finale = rand()%(max_ - min_)+ min_;

    return finale;
}

void Jungle :: reproduction_proie()
{

    if (proies.size()>1)
    {
        Proie* parent_1;
        Proie* parent_2;
        parent_1 = NULL;
        parent_2 = NULL;
        int i = 0;
        int j = 0;
        int fin_i, fin_j;
        do
        {
            fin_i = rand()%proies.size();
            fin_j = rand()%proies.size();
        }
        while ( fin_i != fin_j);
        list<Proie*>::iterator it = proies.begin();
        while (i<fin_i)
        {
            it++;
            i++;
        }
        parent_1 = (*it);

        j = 0;

        it = proies.begin();
        while (j<fin_j)
        {
            it++;
            j++;
        }
        parent_2 = (*it);



        Proie* enfant = new Proie(parent_1, parent_2, this);
        ajouter_proie(enfant);
    }
}


void Jungle :: reproduction_pred()
{

    if (predateurs.size()>1)
    {
        Predateur* parent_1;
        Predateur* parent_2;
        parent_1 = NULL;
        parent_2 = NULL;
        int i = 0;
        int j = 0;
        int fin_i, fin_j;
        do
        {
            fin_i = rand()%predateurs.size();
            fin_j = rand()%predateurs.size();
        }
        while ( fin_i != fin_j);
        list<Predateur*>::iterator it = predateurs.begin();
        while (i<fin_i)
        {
            it++;
            i++;
        }
        parent_1 = (*it);

        j = 0;

        it = predateurs.begin();
        while (j<fin_j)
        {
            it++;
            j++;
        }
        parent_2 = (*it);



        Predateur* enfant = new Predateur(parent_1, parent_2, this);
        ajouter_predateur(enfant);
    }




}
