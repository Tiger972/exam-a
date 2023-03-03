#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HORIZ 0
#define VERT 1

/*
Pour l'exercice vous aurez besoin de generer des entiers aléatoire : rand() renvoit un entier aléatoire.
il s'utilise : rand() % NOMBREMAX + 1
Pour un entier aléatoire entre 0 et 1 il faut donc faire rand() %2
voir dans la methode main.
*/

// Ecrire la fonction generer(), elle prend en paramètre la grille et renvoie le nombre d'éléments non nuls

int generer(int grid[9][9]) {
    int ligne, colonne;
    int Nb_nn = 0;

    for (ligne = 0; ligne < 9; ligne++) {
        for (colonne = 0; colonne < 9; colonne++) {
            if (grid[ligne][colonne] != 0) {
                Nb_nn++;
            }
        }
    }
    return Nb_nn;
}

// Ce lien vous sera utile : https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

/*Écrire une fonction saisir() qui demande à l’utilisateur de saisir au clavier les indices i et j et la valeur v à placer à l’emplacement (i,j).
La fonction doit vérifier la validité des indices et de la valeur.
Si la case n’est pas occupée, la valeur doit être placée dans la grille. remplissage est alors incrémentée*/

void saisir(int grid[9][9]) {
    int i, j, v;
    printf("Ligne : \n");
    scanf("%d", &i);
    printf("Colonne : \n");
    scanf("%d", &j);
    printf("Valeur : \n");
    scanf("%d", &v);

    if(i < 0 || i > 8 || j < 0 || j > 8 || v < 1 || v > 9) {
        printf("Erreur \n");
    }
    else {
        if(grid[i][j] == 0) {
            grid[i][j] = v;
        } else {
            printf("la case est indisponible\n");
        }
    }
}


/*
Écrire la fonction verifierLigneColonne() qui prend en paramètre un numéro et un sens (HORIZ ou VERT)
qui vérifie que la ligne ou la colonne (suivant les cas) numéro est bien remplie.
On pourra utiliser un tableau intermédiaire pour vérifier cela. La fonction retournera 1 si tout s’est bien passé, 0 sinon.
 Les constantes HORIZ de valeur 0 et VERT de valeur 1 sont à définir.
*/

#define HORIZ 0
#define VERT 1

int verifierLigneColonne(int grid[9][9], int value, int sens) {
    int i;
    int array[9];
    if(sens == 0) {
        for(i = 0; i < 9; i++) {
            array[i] = grid[i][value];
        }
    } else if(sens == 1) {
        for(i = 0; i < 9; i++) {
            array[i] = grid[value][i];
        }
    }
    int sum = 0;
    for(i = 0; i < 9; i++) {
        sum += array[i];
    }

    if(sum == 45) {
        return 0;
    } else {
        return 1;
    }
}

/*
Écrire la fonction verifierRegion() qui prend en paramètre deux indices k et l qui correspondent à la région (k,l)
et qui renvoie 1 si la région est correctement remplie, 0 sinon.
*/

int verifierRegion(int grid[9][9], int k, int l) {
    int i, j;
    int array[9];
    int index = 0;
    for(i = 0; i < 3; i= i+3) {
        for(j = 0; j < 3; j = j+3) {
            array[index] = grid[i + k][j + l];
            index++;
        }
    }
    int sum = 0;
    for(i = 0; i < 9; i++) {
        sum += array[i];
    }
    if(sum == 45) {
        return 0;
    } else {
        return 1;
    }
}

//Écrire la fonction verifierGrille() qui renvoie 1 si la grille est correctement remplie et 0 sinon.

int verifierGrille(int grid[9][9]) {
    int i, j;
    int sum = 0;
    for(i = 0; i < 9; i++) {
        sum += verifierLigneColonne(grid, i, 0);
        sum += verifierLigneColonne(grid, i, 1);
    }
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            sum += verifierRegion(grid, i, j);
        }
    }
    if(sum == 0) {
        return 1;
    } else {
        return 0;
    }
}

//Écrire le programme principal, en supposant que la seule condition d’arrêt est la réussite du sudoku (ce test ne devra être fait que si nécessaire)

int main(){
    // Ne pas toucher le code entre les commentaires
    srand(time(NULL));
    int i, j;
    int solution[9][9];
    printf("SOLUTION");
    printf("\n");
    printf("---------------------------------");
    printf("\n");
    for(j=0;j<9; ++j) {
        for(i=0; i<9; ++i) solution[j][i] = (i + j*3 +j /3) % 9 +1 ;
    }

    int num_to_remove  = 30;
    while (num_to_remove > 0) {
        int row = rand() % 9;
        int col = rand() % 9;
        if (solution[row][col] != 0) {
            solution[row][col] = 0;
            num_to_remove--;
        }
    }

    for(i=0;i<9; ++i) {
        for(j=0; j<9; ++j) printf("%d ", solution[i][j]); printf("\n");
    }

    printf("---------------------------------");
    printf("\n");
    //toucher le code entre les commentaires

    int nombre = generer(solution);
    printf("Nombre d'elements non nuls : %d\n", nombre);

    int nb_casesrest(int grid[9][9]){
        int i, j;
        int sum = 0;
        for(i = 0; i < 9; i++) {
            for(j = 0; j < 9; j++) {
                if(grid[i][j] == 0) {
                    sum++;

                }
            }
        }
        return sum;
    }
    printf("Nombre de cases à remplir  : %d\n", nb_casesrest(solution));

    saisir(solution);
    for(i=0;i<9; ++i) {
        for(j=0; j<9; ++j) printf("%d ", solution[i][j]); printf("\n");
    }

    int k = 0;
    while(k == 0) {
        if(verifierGrille(solution) == 1) {
            printf("Bravo, vous avez gagne !\n");
            k = 1;
        } else {
            saisir(solution);
            for(i=0;i<9; ++i) {
                for(j=0; j<9; ++j) printf("%d ", solution[i][j]); printf("\n");
            }
        }
    }
    //Ne pas toucher au code ci dessous
    system("pause");
    return 0;
}
