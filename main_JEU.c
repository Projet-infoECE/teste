#include <stdio.h>
#include <conio.h>  // Cette bibliothèque est utilisée pour détecter les touches du clavier sous Windows
#include <windows.h>
#include <unistd.h>
#include <pthread.h>

#define ROWS 10
#define COLS 20


char matrices[3][ROWS][COLS] = {
        {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 1},
                {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        },
        {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 1},
                {1, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 2, 8, 2, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 3, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1},
                {1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        },
        {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
                {1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1},
                {1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 3, 4, 3, 0, 0, 0, 0, 1},
                {1, 0, 0, 1, 0, 1, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                {1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 4, 1},
                {1, 4, 0, 3, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        }
};
char matrice0[ROWS][COLS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1},
        {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};// Matrice du jeux
char matrice1[ROWS][COLS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 1},
        {1, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 2, 8, 2, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 3, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1},
        {1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};
char matrice2[ROWS][COLS] =         {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 3, 4, 3, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 4, 1},
        {1, 4, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

struct ThreadData {
    int seconds;
    int isRunning;
};


void afficherChronometre(int seconds) {// Affiche le score par rapport au temps
    printf("\nTemps ecoule : %d secondes", 120-seconds);
}
void *chronometre(void *data) {//mise en place du chronometre
    struct ThreadData *threadData = (struct ThreadData *)data;

    while (threadData->isRunning) {
        afficherChronometre(threadData->seconds);
        Sleep(1000);
        threadData->seconds++;
    }
    pthread_exit(NULL);
}

void afficherMenu() {
    printf("Menu:\n");
    printf("1. Lancer le jeu\n");
    printf("2. Regle\n");
    printf("3. Option\n");
    printf("4. Mot de passe\n");
    printf("5. Quitter\n");
}

void Regle(){
    printf("***Bienvenue sur le jeu Snoopy's Magic Show!***\n");

    printf("-->Pour profiter pleinement du jeu, il est important\n d'en comprendre le fonctionnement et de bien suivre\n les regles qui lui sont attribuees:\n");
    printf("1.Afin de valider un niveau, il est necessaire d'attraper les 4 oiseaux situes dans les quatres coins de la map.\n");
    printf("2.Les quatre oiseaux doivent etre attrapes dans le temps imparti (120 secondes) sinon le niveau ne sera pas valide.\n");
    printf("3.Afin d'atteindre son objectif, Snoopy a la possibilite de deplacer certains blocs.\n");
    printf("4.Durant la partie une balle se deplace sur la map, si celle-ci touche Snoopy,alors celui-ci perd une vie.\n");
    printf("5.Des blocs pieges sont aussi dissimules parmi l'ensemble des blocs de la map, si Snoopy en heurte un,alors celui-ci perd une vie.\n");
    printf("6. Enfin si Snoopy utilise ses 3 vies avant de terminer le niveau,le joueur doit relancer le jeu et recommencer depuis le debut(GAME OVER).\n");
    printf("***Voila c'est a vous maintenant!***\n-->BONNE CHASSE<--");// ecrire les régles
}

void Option(){
    printf("Mouvement:-aller a droite-->appuyer sur 'd'\n");
    printf("           -aller a gauche-->appuyer sur 'q'\n");
    printf("           -aller en haut-->appuyer sur 'z'\n");
    printf("           -aller en bas-->appuyer sur 's'\n");
}
void afficherScore(int tempsRestant) {
    int score = tempsRestant * 100;
    printf("\nScore: %d", score);
}

void afficherMatrice(char matrix[ROWS][COLS] ) {
    int clk=0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            switch (matrix[i][j]) {
                case 0:
                    printf(" ");//bloc vide
                    break;
                case 1:
                    printf("%c", 0xDB);//mur incassable
                    break;
                case 2:
                    printf("%c", 0xDB);//mur incassable dasn la map
                    break;
                case 3:
                    printf("%c", 0xDB);//bloc cassable
                    break;
                case 4:
                    printf("%c", 0x05);//bloc de point
                    break;
                case 5:
                    printf("p");// spwan du joueur
                    break;
                case 6:
                    printf("%c", 0x06);
                    break;
                case 7:
                    printf("%c", 0x03);// rajoute de la vie
                    break;
                case 8:
                    printf("%c", 0xDB);//enleve de la vie
                    break;
                case 9:
                    printf("b");
                    break;
                default:
                    printf(" ");
                    break;
            }
        }
        printf("\n");
    }
}

// Fonction pour initialiser la matrice avec le personnage
void initialiserMatrice(char matrix[ROWS][COLS] ) {
    // Placer le personnage au centre de la matrice
    int initialRow = ROWS / 2;
    int initialCol = COLS / 2;
    matrix[initialRow][initialCol] = 'P';
}

void sauvegarderMatrice(char matrix[ROWS][COLS], int tempsRestant) {
    FILE *fichier;
    char nomFichier[100];

    printf("Entrez le nom du fichier de sauvegarde : ");
    scanf("%s", nomFichier);
    fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier !");
        return;
    }
    fprintf(fichier, "%d\n", tempsRestant);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fprintf(fichier, "%d ", matrix[i][j]);
        }
        fprintf(fichier, "\n");
    }
    fclose(fichier);
    printf("Matrice sauvegardee avec succes dans le fichier : %s\n", nomFichier);
}

void chargerMatrice(char matrix[ROWS][COLS], int *tempsRestant) {
    FILE *fichier;
    char nomFichier[100];

    printf("Entrez le nom du fichier a charger : ");
    scanf("%s", nomFichier);
    fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier !");
        return;
    }
    fscanf(fichier, "%d", tempsRestant);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fscanf(fichier, "%d", &matrix[i][j]);
        }
    }
    fclose(fichier);
}


void deplacment(char matrix[ROWS][COLS]){
    initialiserMatrice(matrix);
    char commande;
    int personnageRow = ROWS / 2;
    int personnageCol = COLS / 2;
    int point = 0;
    int vie = 3;
    int Game = 0;
    int current_matrice = 0;
    int niveau = 0;
    int posX = 1;
    int posY = 1;
    int dirX = 1;
    int dirY = 1;

    afficherMatrice(matrix);
    struct ThreadData threadData = {0, 1};


    // Création du thread pour le chronomètre
    pthread_t chronometreThread;
    pthread_create(&chronometreThread, NULL, chronometre, (void *)&threadData);


    while (!Game) {
        commande = getch();
        int clk = 0;
        int nextX = posX + dirX;
        int nextY = posY + dirY;

        // Vérification des rebonds
        if (matrix[nextX][nextY] != 1) {
            posX = nextX;
            posY = nextY;
            matrix[nextX-dirX][nextY-dirY]= 0;
            matrix[posX][posY]= 9;
        } else {
            // Rebond sur les murs
            if (matrix[nextX][posY] == 1) {
                dirX = -dirX;
                printf("murX");
                matrix[nextX][nextY]= 0;
                matrix[nextX][nextY]= 9;
                matrix[nextX][nextY]=1;
            }
            if (matrix[posX][nextY] == 1) {
                dirY = -dirY;
                printf("murX");
                matrix[nextX][nextY]= 0;
                matrix[nextX][nextY]= 9;
                matrix[nextX][nextY]=1;
            }
        }

        // Déplacer le personnage en fonction de la commande
        switch (commande) {
            case 'z': // Haut
                if (personnageRow > 0 && matrix[personnageRow - 1][personnageCol] == 0 && !(matrix[personnageRow - 1][personnageCol] == 2) || matrix[personnageRow - 1][personnageCol] == 3 || matrix[personnageRow - 1][personnageCol] ==4||matrix[personnageRow - 1][personnageCol] == 6|| (matrix[personnageRow-1][personnageCol] == 7)||matrix[personnageRow-1][personnageCol] == 8){
                    // Condtion si le mur n'est pas incassable
                    if (matrix[personnageRow-1][personnageCol] == 4) {
                        point = point +1;
                    }
//                    if (matrix[personnageRow - 1][personnageCol] == 6){
//                        matrix[personnageRow][personnageCol] = 6;
//
//                        printf("teste\n ");
//                    }
                    if (matrix[personnageRow-1][personnageCol] == 7){// ajoute de la vie
                        vie = vie +1;
                    }
                    if (matrix[personnageRow-1][personnageCol] == 8){// enleve de la vie
                        vie = vie -1;
                    }
                    if (matrix[personnageRow][personnageCol] == 9){
                        vie = vie-1;
                    }
                    // modifie la matrice pour faire offfice de déplacment
                    matrix[personnageRow][personnageCol] = 0;
                    personnageRow--;
                    matrix[personnageRow][personnageCol] = 5;
                }

                if (point == 4){
                    system("cls");

                    afficherMatrice(matrix);
                    afficherScore(120 - threadData.seconds);
                    threadData.isRunning = 0;
                    printf("\nGAGNE, vous avez fini le niveau");// Fin du jeu
                    niveau=niveau +1;

                    pthread_join(chronometreThread, NULL);
                    sleep(4);
                    system("cls");
                    break;
                }
                else{
                    system("cls");
                    Sleep(10);
                    afficherMatrice(matrix);
                }

// les cas suivant suivent les conditions a part que leur position dasn la matrice est modifier
                break;
            case 's': // Bas
                if (personnageRow < ROWS - 1 && matrix[personnageRow + 1][personnageCol] == 0 && !(matrix[personnageRow + 1][personnageCol] == 2) || matrix[personnageRow + 1][personnageCol] == 3 || (matrix[personnageRow + 1][personnageCol] == 4)||matrix[personnageRow+1][personnageCol] == 7||matrix[personnageRow+1][personnageCol] == 8) {
                    if (matrix[personnageRow + 1][personnageCol] == 4){
                        point = point +1;
                    }
                    if (matrix[personnageRow+1][personnageCol] == 7){
                        vie = vie +1;
                    }
                    if (matrix[personnageRow+1][personnageCol] == 8){
                        vie = vie-1;
                    }
                    if (matrix[personnageRow][personnageCol] == 9){
                        vie = vie-1;
                    }
                    matrix[personnageRow][personnageCol] = 0;
                    personnageRow++;
                    matrix[personnageRow][personnageCol] = 5;
                }
                if (point == 4){
                    system("cls");
                    afficherMatrice(matrix);
                    afficherScore(120 - threadData.seconds);
                    threadData.isRunning = 0;
                    printf("\nGAGNE, vous avez fini le niveau");
                    niveau=niveau +1;

                    pthread_join(chronometreThread, NULL);
                    sleep(4);
                    system("cls");
                    break;
                }
                else{
                    system("cls");
                    Sleep(10);
                    afficherMatrice(matrix);
                }

                break;
            case 'q': // Gauche
                if (personnageCol > 0 && matrix[personnageRow][personnageCol - 1] == 0 && !(matrix[personnageRow][personnageCol - 1] == 2) || matrix[personnageRow][personnageCol - 1] == 3 || matrix[personnageRow][personnageCol - 1] == 4 ||matrix[personnageRow][personnageCol-1] == 7||matrix[personnageRow][personnageCol-1] == 8) {
                    if (matrix[personnageRow][personnageCol - 1] == 4){
                        point = point +1;
                    }
                    if (matrix[personnageRow][personnageCol-1] == 7){
                        vie = vie +1;
                    }
                    matrix[personnageRow][personnageCol] = 0;
                    personnageCol--;
                    matrix[personnageRow][personnageCol] = 5;

                    if (matrix[personnageRow][personnageCol-1] == 8){
                        vie =vie-1;
                    }
                    if (matrix[personnageRow][personnageCol] == 9){
                        vie = vie-1;
                    }
                    if (matrix[personnageRow][personnageCol] == 9){
                        vie = vie-1;
                    }
                }
                if (point == 4){
                    system("cls");
                    afficherMatrice(matrix);
                    afficherScore(120 - threadData.seconds);
                    threadData.isRunning = 0;
                    printf("\nGAGNE, vous avez fini le niveau");
                    niveau=niveau +1;

                    pthread_join(chronometreThread, NULL);
                    sleep(4);
                    system("cls");
                    break;
                }
                else{
                    system("cls");
                    Sleep(10);
                    afficherMatrice(matrix);
                }
                break;
            case 'd': // Droite
                if (personnageCol < COLS - 1 && matrix[personnageRow][personnageCol + 1] == 0 && !(matrix[personnageRow][personnageCol + 1] == 2) || matrix[personnageRow][personnageCol + 1] == 3 || matrix[personnageRow][personnageCol + 1] == 4 ||matrix[personnageRow][personnageCol+1] == 7||matrix[personnageRow][personnageCol+1] == 8) {
                    if (matrix[personnageRow][personnageCol + 1] == 4){
                        point = point +1;
                    }
                    if (matrix[personnageRow][personnageCol+1] == 7){
                        vie = vie +1;
                    }
                    if (matrix[personnageRow][personnageCol+1] == 8){
                        vie =vie-1;
                    }
                    if (matrix[personnageRow][personnageCol] == 9){
                        vie = vie-1;
                    }
                    matrix[personnageRow][personnageCol] = 0;
                    personnageCol++;
                    matrix[personnageRow][personnageCol] = 5;
                }
                if (point == 4){
                    system("cls");
                    afficherMatrice(matrix);
                    afficherScore(120 - threadData.seconds);
                    threadData.isRunning = 0;
                    printf("\nGAGNE, vous avez fini le niveau");
                    niveau=niveau +1;

                    pthread_join(chronometreThread, NULL);
                    sleep(4);
                    system("cls");


                    break;
                }
                else{
                    system("cls");
                    Sleep(10);
                    afficherMatrice(matrix);
                }
                break;
            case 'r': // Quitter le jeu
                threadData.isRunning = 0;

                pthread_join(chronometreThread, NULL);
                return;
                break;
            case 'v': // Touche 's' pour sauvegarder
                threadData.isRunning = 0;
                sauvegarderMatrice(matrix, 120 - threadData.seconds);
                sleep(10);
                break;
            case 'c': // Touche 'c' pour charger une matrice sauvegardée
                threadData.isRunning = 0;
                chargerMatrice(matrix, &threadData.seconds);
                break;
            case 'p': // Touche 'c' pour charger une matrice sauvegardée
                threadData.isRunning = 0;
                sleep(5);
                break;
            default:
                break;
        }


        if (point == 4) {
            threadData.isRunning = 0;

            Sleep(2000); // Attendre 4 secondes

            if (current_matrice < 3 ) {
                current_matrice++;

            } else {
                // Si vous avez atteint la dernière matrice, vous pouvez faire ce que vous voulez ici
                // Par exemple, afficher un message de victoire ou simplement terminer le jeu
                printf("Vous avez terminé toutes les matrices!\n");
                return; // Terminer le jeu
            }


            // Réinitialiser les variables du jeu et utiliser la nouvelle matrice
            // Réinitialisation de point, Game, et autres variables si nécessaire

            initialiserMatrice(matrices[current_matrice]); // initialiser la nouvelle matrice
            matrix = matrices[current_matrice];
            point = 0;
            vie = 3;
            struct ThreadData threadData = {0, 1};
            pthread_t chronometreThread;
            pthread_create(&chronometreThread, NULL, chronometre, (void *)&threadData);


            // Afficher un message indiquant le passage à la nouvelle matrice


            // Reprise du jeu avec la nouvelle matrice
            continue;
        }

        if (!(point==4) && !(vie == 0)){
            printf("NB point = %d\f", point);
            printf("Vie: %d", vie );

        }

        if (vie ==0){
            system("cls");
            printf("\nGAME OVER");
            return;
        }
        if (niveau == 3){
            system("cls");
            threadData.isRunning = 0;
            printf("vous avez finis le jeu");
            return;
        }

    }

}
void mdp(){
    int choix_mdp = 0;
    printf("Pour sauter les niveaux voici les mots de passe possible : \n   -niveau 1 => 0, \n   -niveau 2 => 1, \n   -niveau 3 => 2. \n");
    scanf("%d", &choix_mdp);
    switch (choix_mdp) {
        case 0: {
            deplacment(matrice0);
            break;
        }
        case 1: {
            deplacment(matrice1);
            break;
        }
        case 2: {
            deplacment(matrice2);
            break;
        }
        default:
            printf("Choix invalide. Veuillez sélectionner une option valide.\n");
            break;

        }

    }

void lancement_du_menu(){

    int choix, s = 5;
    char c;
    int tmps=0;
    int commande = getch();
    afficherMenu();
    printf("Choisissez une option : ");
    scanf("%d", &choix);

    switch (choix) {
        case 1: {
            deplacment(matrice0);
            sleep(3);
            break;
        }
        case 2:
            Regle();
            printf("\n");
            sleep(10);
            deplacment(matrice0);
            break;
        case 3:
            Option();
            sleep(10);
            deplacment(matrice0);
            break;
        case 4:
            mdp();
            break;
        case 'l':
        case 'L':
            break;
        default:
            printf("Choix invalide. Veuillez sélectionner une option valide.\n");
            break;
    }
}
int main() {
    lancement_du_menu();
    return 0;
}
