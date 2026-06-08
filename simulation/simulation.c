#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define size 100
#define max_particules 5000
#define attachment_prob 0.3
#define R_spawn (size/2 -2)// point de spawn des particules
#define R_kill (size/2 -1) // point de kill des particules
#define gravity 0.05
#define attraction 0.2


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

void spawn_particule(int *x, int *y, int *z){

    double phi   = ((double)rand()/RAND_MAX) * 2.0 * M_PI;
    double theta = acos(1.0 - 2.0 * ((double)rand()/RAND_MAX));

    *x=size/2 + (int)round(R_spawn * sin(theta) * cos(phi));
    *y=size/2 + (int)round(R_spawn * sin(theta) * sin(phi));
    *z=size/2 + (int)round(R_spawn * cos(theta));
}

void mass_attraction(int x, int y, int z, int *pt_x, int *pt_y, int *pt_z){
    int distance=size*size*size; // distance maximale dans l'espace
    *pt_x = size/2;
    *pt_y = size/2;
    *pt_z = size/2;

    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            for(int k=0; k<size; k++){
                if(space[i][j][k]==1){
                    int dx = i - x;
                    int dy = j - y;
                    int dz = k - z;
                    double dist = sqrt(dx*dx + dy*dy + dz*dz);

                    if(dist<distance){
                        distance = dist;
                        *pt_x =i;
                        *pt_y =j;
                        *pt_z =k;
                    }
                }
            }
        }
    }

}

int dist_center(int x, int y, int z) {
    int dx = x - size/2, dy = y - size/2, dz = z - size/2;
    return dx*dx + dy*dy + dz*dz;
}


int main(){
    srand(time(NULL));

    space[size/2][size/2][size/2]=1; // On place la première particule au centre de l'espace

    int particules=0;
    while (particules<max_particules){ //tant qu'on à pas le nombres de particules
        //pose les particules
        int x,y,z;
        spawn_particule(&x,&y,&z); //spawn d'une particule

        int live=1;
        while (live){ //tant que la particule est vivante

            if(dist_center(x,y,z)>R_kill*R_kill){ //si la particule est trop loin du centre, elle meurt
                break;
            }



            if (neighbor(x,y,z)){ 
                double p=(double)rand()/RAND_MAX; // probabilité d'attachement
                if(p<attachment_prob) {
                // attachement de la particule
                    space[x][y][z]=1;
                    particules++; //ajout d'une particule 
                    break;
                }
            }
//diffusion
            double g=(double)rand()/RAND_MAX; // probabilité de gravité
            double a=(double)rand()/RAND_MAX; // probabilité d'attraction
            
            if(a<attraction){ //si la particule est influencée par l'attraction
                int pt_x, pt_y, pt_z;
                mass_attraction(x,y,z,&pt_x,&pt_y,&pt_z);

                if (x<pt_x && x<size-1) x++; // droite
                else if (x>pt_x && x>0) x--; // gauche

                if (y<pt_y && y<size-1) y++; // derriere
                else if (y>pt_y && y>0) y--; // devant

                if (z<pt_z && z<size-1) z++; // haut
                else if (z>pt_z && z>0) z--; // bas   
            }

            if(g<gravity){ //si la particule est influencée par la gravité
                if (z>0) z--; // la particule tombe vers le bas
            }

            
            else{ //sinon elle diffuse normalement
                int direction=rand()%6;

                if (direction==0 && x<size-1) x++; // droite
                else if (direction==1 && x>0) x--; // gauche
                else if (direction==2 && y<size-1) y++; // derriere
                else if (direction==3 && y>0) y--; // devant
                else if (direction==4 && z<size-1) z++; // haut
            else if (direction==5 && z>0) z--; // bas   

            }
        }
    }
    //sauvegarde de l'espace dans un fichier
    FILE *f = fopen("space.txt", "w");
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            for (int k = 0; k < size; k++){
                fprintf(f, "%d ", space[i][j][k]);
            }
            
        }
    }
    fclose(f);
} 