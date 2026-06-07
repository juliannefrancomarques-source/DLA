#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define size 50
#define max_particules 500

int space [size][size][size]={0};

int neighbor(int x, int y, int z){
    if (x<size-1 && space[x+1][y][z]) return 1;
    if (x>0 && space[x-1][y][z]) return 1;

    if (y<size-1 && space[x][y+1][z]) return 1;
    if (y>0 && space[x][y-1][z]) return 1;

    if (z<size-1 && space[x][y][z+1]) return 1;
    if (z>0 && space[x][y][z-1]) return 1;
    return 0;
} 


int main(){
    srand(time(NULL));
    space[size/2][size/2][size/2]=1; // On place la première particule au centre de l'espace

    int particules=0;
    while (particules<max_particules){
        //position aléatoire de la particule
        int x=rand()%size;
        int y=rand()%size;
        int z=rand()%size;

        while (space[x][y][z]){ // On cherche une position libre pour la particule
            int direction=rand()%6;
            if (direction==0 && x<size-1) x++; // droite
            else if (direction==1 && x>0) x--; // gauche
            else if (direction==2 && y<size-1) y++; // derriere
            else if (direction==3 && y>0) y--; // devant
            else if (direction==4 && z<size-1) z++; // haut
            else if (direction==5 && z>0) z--; // bas   
        }

        if (neighbor(x,y,z)){ // Si la particule a un voisin, elle s'arrête
            space[x][y][z]=1;
            particules++;
        }
    }

    //sauvegarde de l'espace dans un fichier
    FILE *f = fopen("space.txt", "w");
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            for (int k = 0; k < size; k++){
                fprintf(f, "%d ", space[i][j][k]);
            }
            fprintf(f, "\n");
        }
    }
    fclose(f);
}