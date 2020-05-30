#ifndef PROIE_H
#define PROIE_H
#include "Animal.h"


class Jungle;

class Proie : public Animal
{
    public:
        Proie();
        Proie(int _x, int _y, int _dx, int _dy);
        virtual ~Proie();
        void deplacer();
        void mise_a_jour();
        Proie(Proie* proie1, Proie* proie2, Jungle* jungle);
        void afficher();

    protected:

    private:
};

#endif // PROIE_H
