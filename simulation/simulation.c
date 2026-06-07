#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define size 100
#define max_particules 1000

int space [size][size]={0};

int neighbor(int x, int y){
    if (x<size-1 && space[x+1][y]) return 1;
    if (x>0 && space[x-1][y]) return 1;
    if (y<size-1 && space[x][y+1]) return 1;
    if (y>0 && space[x][y-1]) return 1;
    return 0;
} 


int main(){
    srand(time(NULL));
    space[size/2][size/2]=1; // On place la première particule au centre de l'espace

    int particules=0;
    while (particules<max_particules){
        //position aléatoire de la particule
        int x=rand()%size;
        int y=rand()%size;

        while (space[x][y]){ // On cherche une position libre pour la particule
            int direction=rand()%4;
            if (direction==0 && x<size-1) x++; // droite
            else if (direction==1 && x>0) x--; // gauche
            else if (direction==2 && y<size-1) y++; // bas
            else if (direction==3 && y>0) y--; // haut
        }

        if (neighbor(x,y)){ // Si la particule a un voisin, elle s'arrête
            space[x][y]=1;
            particules++;
        }
    }

    //sauvegarde de l'espace dans un fichier
    FILE *f = fopen("space.txt", "w");
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            fprintf(f, "%d ", space[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}