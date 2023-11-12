#include <stdio.h>
#include <conio.h>  // Cette bibliothèque est utilisée pour détecter les touches du clavier sous Windows
#include <windows.h>
#include <unistd.h>
#include <pthread.h>
#define ROWS 10
#define COLS 20

char matrix[ROWS][COLS] = {
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
};// Matrice du jeux

char matrice[1][7] = {
        {0,1,2,3,4,5,6}
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

// Affichage du menu
void afficherMenu() {
    printf("Menu:\n");
    printf("1. Lancer le jeu\n");
    printf("2. Regle\n");
    printf("3. Option\n");
    printf("4. Quitter\n");
}

void Regle(){
    printf("***Bienvenue sur le jeu Snoopy's Magic Show!***\n");

    printf("-->Pour profiter pleinement du jeu, il est important\n d'en comprendre le fonctionnement et de bien suivre\n les regles qui lui sont attribuees:\n");
    printf("1.Afin de valider un niveau, il est necessaire d'attraper les 4 oiseaux situes dans les quatres coins de la map.\n");
    printf("2.Les quatre oiseaux doivent etre attrapes dans le temps imparti (120 secondes) sinon le niveau ne sera pas valide.\n");
    printf("3.Afin d'atteindre son objectif, Snoopy a la possibilite de deplacer certains blocs.\n");
    printf("4.Durant la partie une balle se deplace sur la map, si celle-ci touche Snoopy,alors celui-ci perd une vie.\n");
    printf("5.Des blocs pieges sont aussi dissimules parmi l'ensemble des blocs de la map, si Snoopy en heurte un,alors celui-ci perd une vie.\n");
    printf("6. Enfin si Snoopy utilise ses 3 vies avant de terminer le niveau,le joeur doit relancer le jeu et recommencer depuis le debut(GAME OVER).\n");
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



// Fonction pour afficher la matrice
void afficherMatrice() {
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
                    printf("s");// spwan du joueur
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
//                case 9:
//                    for (int n = 0; n < 60; n++) {
//                        printf("\r"); // Efface la ligne
//                        printf("\r%d", clk); // Affiche la nouvelle valeur de clk
//                        fflush(stdout); // Vide le tampon de sortie
//                        sleep(1);
//                        clk = clk + 1;
//                    }

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
void initialiserMatrice() {
    // Placer le personnage au centre de la matrice
    int initialRow = ROWS / 2;
    int initialCol = COLS / 2;
    matrix[initialRow][initialCol] = 'P';

}
int isPaused =0;
void deplacment(){
    initialiserMatrice();
    char commande;
    int personnageRow = ROWS / 2;
    int personnageCol = COLS / 2;
    int point = 0;
    int vie = 3;
    int Game = 0;
    afficherMatrice();
    struct ThreadData threadData = {0, 1};

    // Création du thread pour le chronomètre
    pthread_t chronometreThread;
    pthread_create(&chronometreThread, NULL, chronometre, (void *)&threadData);


    while (!Game) {


        commande = getch();
        int clk = 0;


        // Déplacer le personnage en fonction de la commande
        switch (commande) {

            case 'z': // Haut
                if (personnageRow > 0 && matrix[personnageRow - 1][personnageCol] == 0 && !(matrix[personnageRow - 1][personnageCol] == 2) || matrix[personnageRow - 1][personnageCol] == 3 || matrix[personnageRow - 1][personnageCol] ==4||matrix[personnageRow - 1][personnageCol] == 6|| (matrix[personnageRow-1][personnageCol] == 7)||matrix[personnageRow-1][personnageCol] == 8){
                    if (matrix[personnageRow-1][personnageCol] == 4) {
                        point = point +1;
                    }
//                    if (matrix[personnageRow - 1][personnageCol] == 6){
//                        matrix[personnageRow][personnageCol] = 6;
//
//                        printf("teste\n ");
//                    }
                    if (matrix[personnageRow-1][personnageCol] == 7){
                        vie = vie +1;
                    }
                    if (matrix[personnageRow-1][personnageCol] == 8){
                        vie = vie -1;
                    }
                    matrix[personnageRow][personnageCol] = 0;
                    personnageRow--;
                    matrix[personnageRow][personnageCol] = 5;

                }
                if (point == 4){
                    system("cls");

                    afficherMatrice();
                    afficherScore(120 - threadData.seconds);
                    printf("\n GAGNE ");

                    return;
                }

                else{
                    system("cls");
                    Sleep(10);

                    afficherMatrice();
                }
                

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
                    matrix[personnageRow][personnageCol] = 0;
                    personnageRow++;
                    matrix[personnageRow][personnageCol] = 5;


                }
                if (point == 4){
                    system("cls");
                    afficherMatrice();
                    afficherScore(120 - threadData.seconds);
                    printf("\nGAGNE");

                    return;
                }
                else{
                    system("cls");
                    Sleep(10);
                    afficherMatrice();
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
                }
                if (point == 4){
                    system("cls");
                    afficherMatrice();
                    afficherScore(120 - threadData.seconds);
                    printf("\nGAGNE");

                    return;
                }
                else{
                    system("cls");
                    Sleep(10);
                    afficherMatrice();
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
                    matrix[personnageRow][personnageCol] = 0;
                    personnageCol++;
                    matrix[personnageRow][personnageCol] = 5;


                }
                if (point == 4){
                    system("cls");
                    afficherMatrice();
                    afficherScore(120 - threadData.seconds);
                    printf("\nGAGNE");

                    return;
                }
                else{
                    system("cls");
                    Sleep(10);
                    afficherMatrice();

                }


                break;
            case 'r': // Quitter le jeu
                threadData.isRunning = 0;
                pthread_join(chronometreThread, NULL);
            default:


                break;
        }

        printf("NB point = %d\f", point);
        printf("Vie: %d", vie );
        if (vie ==0){
            system("cls");
            printf("\nGAME OVER");
            return;
        }



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


            deplacment();

            // Arrêt du chronomètre

            break;
        }
        case 2:
            Regle();
            // Ajoutez votre code pour l'option 2 ici
            printf("\n");
            sleep(20);

            deplacment();


            break;
        case 3:
            Option();
            sleep(10);
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
