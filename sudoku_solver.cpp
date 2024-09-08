#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>

using namespace std;

//facile
int tab3[9][9] = {
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
int tab[9][9] = {
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


void sudoku_solver(){

    cout << "grille départ" << endl;
    afficher_grille();

    int n_case = 0; // Nombre de case totale posée
    int n=0;
    int x, y;
    int stop=0, stop_verif=0;

    while(n_case < 81){// parcours du tableau mais sans boucle for

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

        // cout << x << " " << y << " " << n << " " << n_case << " " << endl;
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

        // afficher_grille();
        stop++;

    }//fin while

    cout << "grille fin" << endl;
    afficher_grille();

}//fin main