#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//prototipi
void esperimento();
double init();
void passotemporale(int);

//definizioni
#define L 10
#define DIM 2
#define VOLUME (int)pow(L,DIM) //ok perchè L, DIM sono sempre interi
#define N_SWEEPS 1000
#define N_MIS 100
#define MIS_PERIOD (N_SWEEPS / N_MIS)
#define NSAMPLES 5000

typedef unsigned long long int RANDOM_TYPE;
RANDOM_TYPE a, seed, randomNumber;

int main(){
    //definisco gli array
    long int **particleOfSite = (long int**)calloc(L,sizeof(long int *));
    for (int i=0; i<L; i++) *(particleOfSite+i) = (long int*)calloc(L,sizeof(long int));
    long int **positionOfParticle = (long int**)calloc(VOLUME,sizeof(long int *));
    for (int i=0; i<VOLUME; i++) *(positionOfParticle+i) = (long int*)calloc(DIM,sizeof(long int));
    long int **truePositionOfParticle = (long int**)calloc(VOLUME,sizeof(long int *));
    for (int i=0; i<VOLUME; i++) *(positionOfParticle+i) = (long int*)calloc(DIM,sizeof(long int));
    long int **zeroPositionOfParticle = (long int**)calloc(VOLUME,sizeof(long int *));
    for (int i=0; i<VOLUME; i++) *(positionOfParticle+i) = (long int*)calloc(DIM,sizeof(long int));
    double *averageDeltaR2 = (double *)calloc(N_MIS,sizeof(double));
    double *errorDeltaR2 = (double *)calloc(N_MIS,sizeof(double));
    long int *plusNeighbor = (long int *)calloc(L,sizeof(long int));
    long int *minusNeighbor = (long int *)calloc(L,sizeof(long int));
    for(int i=0; i<L; i++){
        *(plusNeighbor+i) = i + 1;
        *(minusNeighbor+i) = i - 1;
    }
    *(plusNeighbor+(L-1)) = 0;
    *minusNeighbor = L - 1;
    
    //INIZIALIZZAZIONE
    
    return 0;
}

void esperimento(){
    
}

double init(){
    //Controllo errori
    if((N_MIS * MIS_PERIOD) != N_SWEEPS){
        printf("ERRORE: numero di passi non multiplo del numero di misure");
        exit(-1);
    }
    
    //inizializzo il numero casuale
    a = 1181783497276652981;
    seed = 131419;
    randomNumber = seed;
    
    
}

void passotemporale(int tempo){
    
}