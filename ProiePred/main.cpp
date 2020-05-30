#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include "Parametres.h"
#include "Proie.h"
#include "Animal.h"
#include "Predateur.h"
#include "Jungle.h"
#include <list>
#include <time.h>
#include <iostream>




using namespace std;



void afficher_proie (Proie* proie, SDL_Surface* p, SDL_Surface* screen)
{

    SDL_Rect dstrect;
    dstrect.x = proie->getX();
    dstrect.y = proie->getY();


    SDL_BlitSurface( p, 0, screen, &dstrect);
    proie->afficher();

}

void afficher_predateur (Predateur* predateur, SDL_Surface* p, SDL_Surface* screen)
{

    SDL_Rect dstrect;
    dstrect.x = predateur->getX();
    dstrect.y = predateur->getY();


    SDL_BlitSurface( p, 0, screen, &dstrect);
    predateur->afficher();
}

void afficher_jungle (Jungle* jungle, SDL_Surface* p, SDL_Surface* pred, SDL_Surface* screen)
{

    if (PRINT)
    {
        cout << "nb proie :" <<jungle->proies.size()<<endl;
    }

    for(list<Proie*>::iterator it = jungle->proies.begin(); it!=jungle->proies.end(); ++it)
    {
        afficher_proie(*it, p, screen);

    }
    if (PRINT)
    {
        cout << "nb pred :" <<jungle->predateurs.size()<<endl;
    }

    for(list<Predateur*>::iterator it = jungle->predateurs.begin(); it!=jungle->predateurs.end(); ++it)
    {
        afficher_predateur(*it, pred, screen);

    }


}













int main ( int argc, char** argv )
{


    srand(time(NULL)) ;

    Jungle* jungle = new Jungle;

    int i;
    for (i=0; i<4; i++)
    {
        jungle->ajouter_proie(new Proie());
    }

    //jungle->ajouter_proie(new Proie());
    //jungle->ajouter_proie(new Proie());
    jungle->ajouter_predateur(new Predateur(jungle));
    jungle->ajouter_predateur(new Predateur(jungle));









    freopen("CON","w",stdout);

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window

    // load an image
    SDL_Surface* proie_im = SDL_LoadBMP("proie.bmp");
    SDL_SetColorKey(proie_im, SDL_SRCCOLORKEY, SDL_MapRGB(proie_im->format, 128, 0, 128));
    SDL_Surface* pred_im = SDL_LoadBMP("pred.bmp");
    SDL_SetColorKey(pred_im, SDL_SRCCOLORKEY, SDL_MapRGB(pred_im->format, 128, 0, 128));

    if (!proie_im || !pred_im)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* screen = SDL_SetVideoMode(LARGEUR+proie_im->w, HAUTEUR+proie_im->h, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }


    // centre the bitmap on screen
    /*SDL_Rect dstrect;
     dstrect.x = (screen->w - bmp->w) / 2;
     dstrect.y = (screen->h - bmp->h) / 2;*/

    // program main loop
    bool done = false;
    int nb_jours = 0;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
            // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

            // check for keypresses
            case SDL_KEYDOWN:
            {
                // exit if ESCAPE is pressed
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                break;
            }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));


        //afficher_proie(p1, proie_im, screen);
        //afficher_predateur(q1, pred_im, screen);
        //deplacer();

        if (nb_jours%300==0)
        {
            jungle->reproduction_proie();
            jungle->reproduction_pred();
        }
        afficher_jungle(jungle, proie_im, pred_im, screen);
        jungle->deplacer_tout();
        jungle->extinction();

        // SDL_BlitSurface(bmp, 0, screen, &dstrect); ,

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
        nb_jours++;
        if (nb_jours > 1000)
        {
            nb_jours = 0;
        }
    } // end main loop





    // free loaded bitmap
    SDL_FreeSurface(proie_im);
    SDL_FreeSurface(pred_im);


    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
