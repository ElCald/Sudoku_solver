#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

bool verifier_ligne_colonne(const int x, const int y, const int val);
bool verifier_carre(const int x, const int y, const int val);
void afficher_grille();
void sudoku_solver();

#endif