#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define k 1

struct body{
    double x;
    double v;
    double mass;
};

struct time{
    int Tmax;
    double dt;
    int t0;
};

//DICHIARO I PROTOTIPI DELLE FUNZIONI
//funzioni dipendenti dal problema fisico in esame
double Phi_old(double m, double x_old);
double Energy(struct body pnt);

//algoritmi di integrazione
double Euler(struct body pnt, struct time tm);


int main(int argc, char *argv[]){
    
    //Dichiaro le costanti note a priori
    struct body pnt;
    struct time tm;
    
    
    //SCHEMA DI CONTROLLO DELL'INPUT
    int expected_args = 7;
    //se non ho inserito gli argomenti che voglio
    if(argc != expected_args){
        //controllo se ce ne sono solo due
        if(argc == 2){
            //se il secondo è help stampo un messaggio di aiuto
            if(strcmp(argv[1], "help") == 0){
                printf("usage: ./integrazione.x x0 v0 mass tmax dt \n");
                printf("./integrazione.x help: show help \n");
                printf("./integrazione.x auto: run with default values \n");
                exit(-1);
            }
            //se il secondo è auto eseguo il programma con dei valori predefiniti
            else if(strcmp(argv[1], "auto") == 0){
                printf("auto mode \n");
                printf("x0 = 1m, v0 = 0m/s, mass = 1kg, Tmax = 10s, dt = 0.01s, t0 = 0s \n");
                pnt.x = 1;
                pnt.v = 0;
                pnt.mass = 1;
                tm.Tmax = 10;
                tm.dt = 0.01;
                tm.t0 = 0;
            }
            else{
                printf("usage: ./integrazione.x x0 v0 mass tmax dt \n");
                printf("./integrazione.x help: show help \n");
                printf("./integrazione.x auto: run with default values \n");

                exit(-1);
            }
        }else{
            printf("usage: ./integrazione.x x0 v0 mass tmax dt \n");
            printf("./integrazione.x help: show help \n");
            printf("./integrazione.x auto: run with default values \n");;
            exit(-1);
        }
    }
    //se ho inserito abbastanza argomenti assegno i valori alle variabili scorrendo in argv[]
    pnt.x = atof(argv[1]);
    pnt.v = atof(argv[2]);
    pnt.mass = atof(argv[3]);
    tm.Tmax = atof(argv[4]);
    tm.dt = atof(argv[5]);
    tm.t0 = atof(argv[6]);
    
    //RUNNO IL CODICE PRINCIPALE
    Euler(pnt, tm);
}

//Funzioni

//DEFINISCO L'ACCELERAZIONE PHI
double Phi_old(double m, double x_old){
    //Oscillatore armonico
    double omega2 = -(k/m);
    double phi_old = omega2 * x_old;
    return phi_old;
}

double Energy(struct body pnt){
    double energy = ((pnt.mass*pow(pnt.v,2))/2)+((k*pow(pnt.x,2))/2);
    return energy;
}

double Euler(struct body pnt, struct time tm){
    
    //variabili temporanee
    double v_now, x_now;
    
    //calcolo l'energia al tempo zero
    double energiazero = Energy(pnt);

    //Handler per il file
    FILE *fout, *fopen();
    fout = fopen("data/data_euler.dat","w+");
    
    printf("Metodo di Eulero: inizio ciclo iterativo\n");
    
    //Ciclo iterativo
    for(double t=tm.t0; t<tm.Tmax;t+=tm.dt){
        //Calcolo per il tempo n+1
        v_now = pnt.v + (Phi_old(pnt.mass, pnt.x))*tm.dt;
        x_now = pnt.x + pnt.v*tm.dt;
        
        //Aggiorno la struct
        pnt.x = x_now;
        pnt.v = v_now;
        
        //Calcolo il delta sull'energia
        double deltaenergy = (Energy(pnt) - energiazero) / energiazero;
        
        //Stampo su file
        fprintf(fout,"%f\t%f\t%f\t%f\n", t,pnt.x,pnt.v,deltaenergy);
    }
    
    printf("Metodo di Eulero: inizio stampa dei grafici\n");
    
    //Stampaggio dei grafici
    
    printf("Metodo di Eulero: fine\n");
    
}

