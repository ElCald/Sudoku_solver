#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>

#include "sudoku_solver.h"

using namespace std;


//facile
int tab[9][9] = {
    {0,0,0,-7,0,-1,0,-3,0},
    {-1,0,0,0,0,0,0,-4,-5},
    {-5,-7,0,0,-8,-2,0,-9,0},
    {0,0,0,0,0,-9,0,-6,-1},
    {0,0,-5,-3,0,0,0,0,0},
    {-6,0,0,-5,0,0,-3,0,0},
    {0,-5,-1,0,-7,0,-9,0,0},
    {-4,0,0,-1,0,0,-2,-5,0},
    {-2,-8,0,0,0,0,0,-1,0}
};

//expert
int tab2[9][9] = {
    {0,0,0,-8,-3,0,0,-5,-7},
    {0,0,-8,-5,0,0,-6,0,0},
    {-1,-3,0,0,0,-2,0,-8,0},
    {-8,0,-2,-3,-9,0,-7,0,0},
    {-6,0,0,-1,0,0,0,-3,-2},
    {0,-5,-7,-2,0,-4,0,-9,0},
    {0,-6,0,-4,-1,0,-3,-7,0},
    {0,-7,-3,-9,0,-8,0,-6,0},
    {0,0,0,-7,-6,0,-4,0,0}
};

//extreme
int tab3[9][9] = {
    {-8,0,0,0,0,-7,0,-4,0},
    {0,-5,0,0,0,0,0,-8,-9},
    {-9,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,-2,0,0,-5},
    {0,-2,-6,0,0,0,-1,0,0},
    {0,0,0,-4,0,0,-7,0,0},
    {0,0,-3,0,-5,0,0,0,0},
    {0,0,0,-9,-8,-4,0,0,0},
    {-1,0,-5,0,-7,0,0,0,0}
};


/**
 * return True si la ligne et la colonne sont libres pour la valeur val
 */
bool verifier_ligne_colonne(const int x, const int y, const int val){

    // cout << "val:" << val << "|";
    for(int i=0; i<9; i++){

        if(abs(tab[x][i]) == val){
            // cout << endl;
            return false;
        }

        if(abs(tab[i][y]) == val){
            // cout << endl;
            return false;
        }

        // cout << abs(tab[x][i]) << " ";
    }
    // cout << endl;

    return true;
}//fin verifier_ligne_colonne


/**
 * return True si le carré est libre pour la valeur val
 */
bool verifier_carre(const int x, const int y, const int val){
    int x_deb, x_fin, y_deb, y_fin;

    if(x >= 0 && x <= 2){
        x_deb=0;
        x_fin=2;
        if(y >= 0 && y <= 2){
            y_deb=0;
            y_fin=2;
        }
        else if(y >= 3 && y <= 5){
            y_deb=3;
            y_fin=5;
        }
        else if(y >= 6 && y <= 8){
            y_deb=6;
            y_fin=8;
        }
        else{
            cerr << "Index error : verifier_carre y 1 : " << y << endl;
            exit(EXIT_FAILURE);
        }
    }
    else if(x >= 3 && x <= 5){
        x_deb=3;
        x_fin=5;
        if(y >= 0 && y <= 2){
            y_deb=0;
            y_fin=2;
        }
        else if(y >= 3 && y <= 5){
            y_deb=3;
            y_fin=5;
        }
        else if(y >= 6 && y <= 8){
            y_deb=6;
            y_fin=8;
        }
        else{
            cerr << "Index error : verifier_carre y 2 : " << y << endl;
            exit(EXIT_FAILURE);
        }
    }
    else if(x >= 6 && x <= 8){
        x_deb=6;
        x_fin=8;
        if(y >= 0 && y <= 2){
            y_deb=0;
            y_fin=2;
        }
        else if(y >= 3 && y <= 5){
            y_deb=3;
            y_fin=5;
        }
        else if(y >= 6 && y <= 8){
            y_deb=6;
            y_fin=8;
        }
        else{
            cerr << "Index error : verifier_carre y 3 : " << y << endl;
            exit(EXIT_FAILURE);
        }
    }
    else{
        cerr << "Index error : verifier_carre x : " << x << endl;
        exit(EXIT_FAILURE);
    }

    for(int i=x_deb; i<=x_fin; i++){
        for(int j=y_deb; j<=y_fin; j++){
            if(abs(tab[i][j]) == val){
                return false;
            }
        }
    }

    return true;
}//fin verifier_carre


void afficher_grille(){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            cout << abs(tab[i][j]);
            if(j%3 == 2){
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}


void sudoku_solver(SDL_Renderer* renderer){

    cout << "grille départ" << endl;
    afficher_grille();

    int n_case = 0; // Nombre de case totale posée
    int n=0;
    int x, y;
    int stop_verif=0;
    int n_display=0; // valeur pour l'affichage
    pthread_t t_sudoku;

    // renderer_sudoku = r;

    // pthread_create(&t_sudoku, NULL, display_jeu, &r);

    while(n_case < 81){// parcours du tableau

        x = n_case/9;
        y = n_case%9;

        while(tab[x][y] < 0){
            n_case++;
            x = n_case/9;
            y = n_case%9;
        }

        n = tab[x][y];
        tab[x][y] = 0;

        if(n==0){
            n=1;
        }

        // Boucle qui vérifie les 3 règles
        stop_verif = 0;
        while(stop_verif == 0 && n<=9){
            if(verifier_ligne_colonne(x, y, n)){
                if(verifier_carre(x, y, n)){
                    tab[x][y] = n;
                    stop_verif = 1;
                }
                else{
                    n++;  
                }
            }
            else{
                n++;  
            }
        }

        // Si on dépasse 9 ça veut dire qu'aucune des règles n'est respecté pour la case donc on retourne en arrière
        if(n > 9){
            n_case--;

            x = n_case/9;
            y = n_case%9;

            while(tab[x][y] < 0){
                n_case--;
                x = n_case/9;
                y = n_case%9;
            }

            tab[x][y]++;
        }
        else{
            n_case++;

            x = n_case/9;
            y = n_case%9;

            while(tab[x][y] < 0){
                n_case++;
                x = n_case/9;
                y = n_case%9;
            }
        }

        n=0;

        if(n_display%10 == 0){
            display_jeu(renderer);
        }

        n_display++;

    
    }//fin while

    cout << "grille fin" << endl;
    afficher_grille();
    display_jeu(renderer);

    // pthread_cancel(t_sudoku);
    // pthread_join(t_sudoku, NULL);

}//fin main

/**
 * Méthode qui permet l'affichage de la grille avec SDL2
 */
void display_jeu(SDL_Renderer* renderer){
    int n;
    char val[8];
    SDL_Surface* textSurface;
    SDL_Rect posText;
    SDL_Color textColor;
    SDL_Texture* textTexture;
    SDL_Texture* grilleTexture;
    SDL_Surface* grilleSurface = NULL;


    // Chargement d'une image
    if( (grilleSurface = SDL_LoadBMP("misc/grille.bmp")) == NULL )
        exit(EXIT_FAILURE);

    // Chargement de l'image dans une texture pour pouvoir l'afficher
    if( (grilleTexture = SDL_CreateTextureFromSurface(renderer, grilleSurface)) == NULL ){
        SDL_FreeSurface(grilleSurface);
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(grilleSurface); // Libération de la mémoire utilisé par l'image car on ne l'utilise plus

    SDL_Rect posGrille;

    // Charger une police
    TTF_Font* font = TTF_OpenFont("misc/arial.ttf", SIZE_NUMBER);
    if (font == nullptr) {
        cerr << "Erreur de chargement de la police: " << TTF_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    // Emplacement de l'image dans notre fenêtre
    if( (SDL_QueryTexture(grilleTexture, NULL, NULL, &posGrille.w, &posGrille.h)) != 0 )
        exit(EXIT_FAILURE);


    posGrille.w = SIZE_NUMBER*9;
    posGrille.h = SIZE_NUMBER*9;
    posGrille.x = 0;
    posGrille.y = 0;

    
    // Chargement de la texture contenant l'image dans le rendu pour l'affichage
    if( (SDL_RenderCopy(renderer, grilleTexture, NULL, &posGrille)) != 0 )
        exit(EXIT_FAILURE);


    
    // Rendu du visuel
    SDL_RenderClear(renderer);

    // Chargement de la texture contenant l'image dans le rendu pour l'affichage
    if( (SDL_RenderCopy(renderer, grilleTexture, NULL, &posGrille)) != 0 )
        exit(EXIT_FAILURE);

    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){

            n = tab[j][i];

            if(n < 0){
                textColor = {255, 0, 0};// Couleur du texte (rouge)
                sprintf(val, "%d", abs(n));
            }
            else if(n == 0 || n == 10){
                textColor = {255, 255, 255};// Couleur du texte (blanc)
                sprintf(val, "%s", " ");
            }
            else{
                textColor = {255, 255, 255};// Couleur du texte (blanc)
                sprintf(val, "%d", abs(n));
            }
            

            // Générer le texte à afficher (par exemple, le chiffre "123")
            textSurface = TTF_RenderText_Solid(font, val, textColor);
            if (textSurface == nullptr) {
                cerr << "Erreur de rendu du texte: " << TTF_GetError() << endl;
                exit(EXIT_FAILURE);
            }

            // Créer une texture à partir de la surface du texte
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (textTexture == nullptr) {
                cerr << "Erreur de création de la texture: " << SDL_GetError() << endl;
                exit(EXIT_FAILURE);
            }


            // Emplacement de l'image dans notre fenêtre
            if( (SDL_QueryTexture(textTexture, NULL, NULL, &posText.w, &posText.h)) != 0 )
                exit(EXIT_FAILURE);


            posText.w = SIZE_NUMBER;
            posText.h = SIZE_NUMBER;
            posText.x = i*SIZE_NUMBER;
            posText.y = j*SIZE_NUMBER;


            // Chargement de la texture contenant l'image dans le rendu pour l'affichage
            if( (SDL_RenderCopy(renderer, textTexture, NULL, &posText)) != 0 )
                exit(EXIT_FAILURE);

        }
    }

    SDL_FreeSurface(textSurface);

    SDL_RenderPresent(renderer); // Actualise à l'écran

}//fin display jeu