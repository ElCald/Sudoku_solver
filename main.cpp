#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <pthread.h>

#include "sudoku_solver.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600


using namespace std;

SDL_Window* fenetre;
SDL_Renderer* renderer;


void ExitWithError(const char* msg){
    SDL_Log("Erreur : %s > %s\n", msg, SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    exit(EXIT_FAILURE);
}


int main(int argc, char* argv[]){

    fenetre = NULL;
    renderer = NULL;
    SDL_Surface* perso = NULL;
    SDL_Texture* texture = NULL;


    // Initialisation de la SDL
    if( SDL_Init(SDL_INIT_VIDEO) != 0 )
        ExitWithError("Initialisation SDL");

    // Creation fenetre + rendu
    if( SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN, &fenetre, &renderer) != 0 )
        ExitWithError("Creation fenetre et rendu echouee");

    // Creation police d'écriture
    if (TTF_Init() == -1) {
        cerr << "Erreur d'initialisation de SDL_ttf: " << TTF_GetError() << endl;
        exit(EXIT_FAILURE);
    }


    // ---------------------- Chargement des images et objets ----------------------
    sudoku_solver(renderer);


    SDL_bool program_launched = SDL_TRUE; // Conditionnelle pour garder la fenêtre ouverte

    while(program_launched){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            switch(event.type){

                case SDL_KEYDOWN: // gestion du clavier
                    switch (event.key.keysym.sym) {

                        case SDLK_ESCAPE:
                            program_launched = SDL_FALSE; ;
                            break;
                        default:
                            continue;
                    }
                    
                    break;

                case SDL_QUIT: // clique sur la croix de la fenêtre
                    program_launched = SDL_FALSE; break;
                
                default:
                    break;
            }

        }//fin boucle event
/*
        // Rendu du visuel
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer); // Actualise à l'écran
*/
    }//fin boucle main



    // Fin de programme
    cout << "Fin de prog" << endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit(); 

    return EXIT_SUCCESS;
}//fin main