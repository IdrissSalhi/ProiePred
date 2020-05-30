#ifndef PREDATEUR_H
#define PREDATEUR_H
#include "Animal.h"
#include "Proie.h"

class Jungle;


class Predateur : public Animal
{
    public:
        Predateur();
        Predateur(Jungle* jungle);
        Predateur(Predateur* pred1, Predateur* pred2, Jungle* jungle);
        virtual ~Predateur();
        void deplacer();
        void chasser();
        void manger();
        Proie* getCible();
        void setCible(Proie* _cible);
        void mise_a_jour();
        bool doit_mourir();
        void afficher();





    protected:

    private:
        Proie* cible;
        Jungle* here;
        int faim;
        int faim_max;


};

#endif // PREDATEUR_H
