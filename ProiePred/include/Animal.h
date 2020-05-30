#ifndef ANIMAL_H
#define ANIMAL_H


class Animal
{
    public:
        Animal();
        Animal(int _x, int _y, int _dx, int _dy);
        virtual ~Animal();
        int getX();
        int getY();
        bool doit_dormir();
        bool getDormir();


    protected:
        int x;
        int y;
        int dx;
        int dy;
        bool dormir;
        int vitesse;
        int sommeil;
        int sommeil_max;


    private:
};

#endif // ANIMAL_H
