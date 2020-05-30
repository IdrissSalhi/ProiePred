#ifndef JUNGLE_H
#define JUNGLE_H
#include <list>
#include "Proie.h"
#include "Predateur.h"

class Jungle
{
    public:
        Jungle();
        virtual ~Jungle();
        void ajouter_proie(Proie* proie);
        void ajouter_predateur(Predateur* predateur);
        std::list<Proie*> proies;
        std::list<Predateur*>predateurs;
        std::list<Predateur*>predateurs_a_tuer;
        void deplacer_tout();
        Proie* choix_proie( Predateur* predateur);
        void tuer_proie(Proie* cible);
        void tuer_pred(Predateur* pred);
        void extinction();
        static int calcul_alea(int n);
        static int calcul_alea(int a, int b);
        void reproduction_proie();
        void reproduction_pred();


    protected:

    private:

};

#endif // JUNGLE_H
