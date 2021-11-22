#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define steps 5000

typedef unsigned long long int RANDOM_TYPE;

//Struct coi parametri

//DECLARATIONS
//Generazione con Parametri Generici
void NumberGeneration(RANDOM_TYPE a, RANDOM_TYPE b, RANDOM_TYPE m, RANDOM_TYPE seed);

//Assegnazione di parametri noti
void LewisGoodmanMiller(RANDOM_TYPE seed);
void Lecuyer1(RANDOM_TYPE seed);
void Lecuyer2(RANDOM_TYPE seed);

//Verifica sul periodo massimo
int TeoremaMassimoPeriodo(RANDOM_TYPE a, RANDOM_TYPE b, RANDOM_TYPE m);
//Test del chi quadro

void printarray(double(*arr)[5], int n);
double seeder();

int main(){
    
    system("clear");
    
    //CONDIZIONI
    
    
    /*int flag = TeoremaMassimoPeriodo(a, b, m);
    if(flag != 0) printf("Teorema violato - %d\n",flag);
    else printf("teorema non violato\n");*/
    
    /*LewisGoodmanMiller(756431);
    printf("-----------");
    Lecuyer1(756431);
    printf("-----------");*/
    Lecuyer2((RANDOM_TYPE)seeder());
    
    if(sizeof(RANDOM_TYPE)<8){
        printf("sizeof RANDOM_TYPE: %d", sizeof(RANDOM_TYPE));
        exit(EXIT_FAILURE);
    }
}

void NumberGeneration(RANDOM_TYPE a, RANDOM_TYPE b, RANDOM_TYPE m, RANDOM_TYPE seed){
    double values[steps][5], ave, ave2;
    RANDOM_TYPE randomNumber = seed;
    int i;
    for(i=0; i<steps; i++){
        randomNumber = (a * randomNumber) % m;
        double r = (double)randomNumber / (double)m;
        values[i][0] = i;
        values[i][1] = r;
        if(i==0) values[i][2] = 0; //Posizione iniziale = 0
        else if(r < 0.5) values[i][2] = values[i-1][2] -1;
        else values[i][2] = values[i-1][2] +1;
        ave2 += values[i][2]*values[i][2];
        values[i][3] += ave2;
        values[i][4] += ave2 * ave2;
        //printf("%lf\n", values[i][1]);
        
    }
    printarray(values, i);
}

double seeder(){
    srand48(time(0));
    double rand = drand48();
    srand48(time(0)+417627);
    rand = rand + drand48() * 100000;
    return rand;
}

void LewisGoodmanMiller(RANDOM_TYPE seed){
    RANDOM_TYPE a = 16807, m = pow(2,31) - 1, b = 0;
    NumberGeneration(a, b, m, seed);
}

void Lecuyer1(RANDOM_TYPE seed){
    RANDOM_TYPE a = 1181783497276652981, m = (RANDOM_TYPE)pow(2,64), b = 0;
    NumberGeneration(a, b, m, seed);
}

void Lecuyer2(RANDOM_TYPE seed){
    RANDOM_TYPE a = 1385320287, m = pow(2,17) - 1, b = 0;
    NumberGeneration(a, b, m, seed);
}

int TeoremaMassimoPeriodo(RANDOM_TYPE a, RANDOM_TYPE b, RANDOM_TYPE m){
    printf("Calcolo le violazioni del Teorema del Massimo Periodo\n");
    for(int i=2; i < m; i++){
        int j = 2, jMax = (int)sqrt(i) + 1;
        while((j < jMax) && (i % j)) j++;
        if (j == jMax) if((((b%i)==0)&&((m%i)==0))||(((m%i)==0)&&((a-1)%i)!=0)||(((m%4)==0)&&(((a-1)%4)!=0))) return i;
        printf("%.5lf %\r", (((double)i/(double)m)*100));
        fflush(stdout);
    }
    printf("100%\r");
    fflush(stdout);
    
    //a-1 è multiplo di p per ogni primo p che divide m
    
    return 0;
}

void printarray(double(*arr)[5], int n){
    //Apro una pipe di sistema e ci dialogo con gnuplot
    FILE *p = popen("gnuplot -persist", "w");
    fprintf(p, "plot '-' w lines linecolor rgb 'red' title 'random walk'\n");
    for(int i = 0; i < n; i++) fprintf(p, "%.14lf %.14lf\n", arr[i][0], arr[i][2]);
    fprintf(p, "e\n");
    pclose(p);
    FILE *q = popen("gnuplot -persist", "w");
    fprintf(q,"set log xy\n");
    fprintf(q, "plot '-' w lines linecolor rgb 'blue' title 'average^2'\n");
    for(int i = 0; i < n; i++) fprintf(p, "%.14lf %.14lf\n", arr[i][0], arr[i][3]);
    fprintf(q, "e\n");
    pclose(q);
}