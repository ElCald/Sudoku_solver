#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>

#include "sudoku_solver.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define SIZE_NUMBER 16 //pixels


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

    if (TTF_Init() == -1) {
        cerr << "Erreur d'initialisation de SDL_ttf: " << TTF_GetError() << endl;
        return -1;
    }



    // ---------------------- Chargement des images et objets ----------------------
    // Chargement d'une image
    if( (perso = SDL_LoadBMP("hyaki.bmp")) == NULL )
        ExitWithError("Chargement image hyaki bmp");

    // Chargement de l'image dans une texture pour pouvoir l'afficher
    if( (texture = SDL_CreateTextureFromSurface(renderer, perso)) == NULL ){
        SDL_FreeSurface(perso);
        ExitWithError("Texturing");
    }

    SDL_FreeSurface(perso); // Libération de la mémoire utilisé par l'image car on ne l'utilise plus

    SDL_Rect posPerso;

    // Emplacement de l'image dans notre fenêtre
    if( (SDL_QueryTexture(texture, NULL, NULL, &posPerso.w, &posPerso.h)) != 0 )
        ExitWithError("Query texture");


    posPerso.w = 50;
    posPerso.h = 50;
    posPerso.x = 10;
    posPerso.y = 10;

    
    // Chargement de la texture contenant l'image dans le rendu pour l'affichage
    if( (SDL_RenderCopy(renderer, texture, NULL, &posPerso)) != 0 )
        ExitWithError("Affichage image");



    // Charger une police
    TTF_Font* font = TTF_OpenFont("arial.ttf", 52); // Spécifiez le chemin de votre fichier .ttf
    if (font == nullptr) {
        cerr << "Erreur de chargement de la police: " << TTF_GetError() << endl;
        return -1;
    }

    // Couleur du texte (blanc)
    SDL_Color textColor = {255, 255, 255};

    // Générer le texte à afficher (par exemple, le chiffre "123")
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "123", textColor);
    if (textSurface == nullptr) {
        cerr << "Erreur de rendu du texte: " << TTF_GetError() << endl;
        return -1;
    }

    // Créer une texture à partir de la surface du texte
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        cerr << "Erreur de création de la texture: " << SDL_GetError() << endl;
        return -1;
    }

    SDL_FreeSurface(textSurface);

    SDL_Rect posText;

    // Emplacement de l'image dans notre fenêtre
    if( (SDL_QueryTexture(textTexture, NULL, NULL, &posText.w, &posText.h)) != 0 )
        ExitWithError("Query texture");


    posText.w = 50;
    posText.h = 50;
    posText.x = 100;
    posText.y = 10;

    
    // Chargement de la texture contenant l'image dans le rendu pour l'affichage
    if( (SDL_RenderCopy(renderer, textTexture, NULL, &posText)) != 0 )
        ExitWithError("Affichage image");


    SDL_RenderPresent(renderer); // Actualise à l'écran

    


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

        // Rendu du visuel
        SDL_RenderClear(renderer);

        if( (SDL_RenderCopy(renderer, texture, NULL, &posPerso)) != 0 )
            ExitWithError("Affichage image");

        if( (SDL_RenderCopy(renderer, textTexture, NULL, &posText)) != 0 )
            ExitWithError("Affichage image");


        SDL_RenderPresent(renderer); // Actualise à l'écran
    }//fin boucle main



    // Fin de programme
    cout << "Fin de prog" << endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit(); 



    return EXIT_SUCCESS;
}//fin main