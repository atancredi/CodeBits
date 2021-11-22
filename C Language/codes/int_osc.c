#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define t0 0
#define k 1

///////////////////////////////////////////////
//Migliorie da apportare:                    //
// - Implementare il resto degli algoritmi   //
// - Migliorare l'estetica dei grafici       //
// - Automatizzare la creazione dei grafici  //
// - OTTIMIZZAZIONE                          //
// - salvare dati su file temporanei o array //
///////////////////////////////////////////////

double Euler(double x0, double v0, double dt, double omega2, double m, int Tmax);
double EulerCromer(double x0, double v0, double dt, double omega2, double m, int Tmax);
double PuntoCentrale(double x0, double v0, double dt, double omega2, double m, int Tmax);
//double MezzoPasso
//double Verlet
double VerletAS(double x0, double v0, double dt, double omega2, double m, int Tmax);
//double PredictCorrect
//double RungeKuttaII
double RungeKuttaIV(double x0, double v0, double dt, double omega2, double m, int Tmax);

int main(int argc, char *argv[]){
    
    //Dichiaro i tipi dei dati in ingresso
    int Tmax;
    double m, x0, v0;
    
    //Controllo le variabili in ingresso se ho due argomenti ed il secondo è 'help' o se non ho il numero congruo
    int expected_args = 5;
    if ((argc == 2 && argv[1] == "help") || (argc != expected_args)){
        //STAMPO AIUTO
        printf("usage: Tmax, m, x0, v0 \n");
        exit(0);
    }
    if(argc == expected_args){
        //Assegno
        Tmax = atof(argv[1]);
        m = atof(argv[2]);
        x0 = atof(argv[3]);
        v0 = atof(argv[4]);
    }           
    
    double omega2 = -(k/m);
    double current;
    
    //Dichiaro i dt
    double dts[5];
    dts[0] = 0.1;
    dts[1] = 0.05;
    dts[2] = 0.005;
    dts[3] = 0.001;
    dts[4] = 0.01;
    
    //DEBUG FLAG
    printf("Inizio Esecuzione\n");
    
    //Eseguo 5 volte ogni metodo a 5 dt diversi, l'ultimo dt è quello per cui stampo bene grafici e dati
    //Poi stampo 
    
    //Eulero
    FILE *fout1, *fopen();
    fout1 = fopen("errors/error_eulero.dat","w");
    for(int j=0;j<5;j++){
        current = Euler(x0,v0,dts[j],omega2,m,Tmax);
        fprintf(fout1,"%f\t%f\n",dts[j],current);
    }
    current = 0;
    fclose(fout1);
    //DEBUG FLAG
    printf("Metodo di Eulero completato\n\n");
    
    //Eulero Cromer
    FILE *fout2, *fopen();
    fout2 = fopen("errors/error_eulerocromer.dat","w");
    for(int j=0;j<5;j++){
        current = EulerCromer(x0,v0,dts[j],omega2,m,Tmax);
        fprintf(fout2,"%f\t%f\n",dts[j],current);
    }
    current = 0;
    fclose(fout2);
    //DEBUG FLAG
    printf("Metodo di Eulero-Cromer completato\n\n");
    
    //Punto Centrale
    FILE *fout3, *fopen();
    fout3 = fopen("errors/error_puntocentrale.dat","w");
    for(int j=0;j<5;j++){
        current = PuntoCentrale(x0,v0,dts[j],omega2,m,Tmax);
        fprintf(fout3,"%f\t%f\n",dts[j],current);
    }
    current = 0;
    fclose(fout3);
    //DEBUG FLAG
    printf("Metodo del Punto Centrale completato\n\n");
    
    //Mezzo Passo
    
    //Verlet
    
    //Verlet Autosufficiente
    FILE *fout6, *fopen();
    fout6 = fopen("errors/error_verletAS.dat","w");
    for(int j=0;j<5;j++){
        current = VerletAS(x0,v0,dts[j],omega2,m,Tmax);
        fprintf(fout6,"%f\t%f\n",dts[j],current);
    }
    current = 0;
    fclose(fout6);
    //DEBUG FLAG
    printf("Metodo di Verlet Autosufficiente completato\n\n");
    
    //Predict Correct
    
    //Runge Kutta 2o Ordine
    
    //Runge Kutta 4o Ordine
    
    //DEBUG FLAG
    printf("Salvo tutti i grafici relativi all'andamento degli errori\n\n");
    
    //Printo nella cartella degli errori i grafici relativi all'andamento degli errori
    system("gnuplot -e \"set terminal png; set output 'errors/eulero.png'; plot 'errors/error_eulero.dat' using 1:2 \"");
    system("gnuplot -e \"set terminal png; set output 'errors/eulerocromer.png'; plot 'errors/error_eulerocromer.dat' using 1:2 \"");
    system("gnuplot -e \"set terminal png; set output 'errors/puntocentrale.png'; plot 'errors/error_puntocentrale.dat' using 1:2 \"");
    //system("gnuplot -e \"set terminal png; set output 'errors/mezzopasso.png'; plot 'errors/error_mezzopasso.dat' using 1:2 \"");
    //system("gnuplot -e \"set terminal png; set output 'errors/verlet.png'; plot 'errors/error_verlet.dat' using 1:2 \"");
    system("gnuplot -e \"set terminal png; set output 'errors/verletAS.png'; plot 'errors/error_verletAS.dat' using 1:2 \"");
    //system("gnuplot -e \"set terminal png; set output 'errors/predictcorrect.png'; plot 'errors/error_predictcorrect.dat' using 1:2 \"");
    //system("gnuplot -e \"set terminal png; set output 'errors/RKII.png'; plot 'errors/error_RKII.dat' using 1:2 \"");
    //system("gnuplot -e \"set terminal png; set output 'errors/RKIV.png'; plot 'errors/error_RKIV.dat' using 1:2 \"");

    //DEBUG FLAG
    printf("Codice Terminato, arrivederci\n\n");
    
    return 0;
}

double Euler(double x0, double v0, double dt, double omega2, double m, int Tmax){
    //Memoria del passo attuale e del passo precedente
    double x_now, v_now;
    double x_old = x0, v_old = v0;
    
    //Calcolo dell'energia al tempo zero
    double energiazero = ((m*(v0*v0))/2)+((k*(x0*x0))/2);
    double energy, deltaenergy;
    
    //Handler per il file
    FILE *fout, *fopen();
    fout = fopen("data_eulero.dat","w");
    
    //DEBUG FLAG
    printf("Metodo di Eulero: inizio ciclo iterativo\n");
    
    //Ciclo iterativo
    for(double t=t0; t<Tmax;t+=dt){
        //calcolo posizione e velocità nel passo
        x_now = x_old + dt*v_old;
        v_now = v_old + dt*omega2*x_old;
        
        //aggiorno le variabili
        x_old = x_now;
        v_old = v_now;
        
        //calcolo l'energia
        energy = ((m*pow(v_now,2))/2)+((k*pow(x_now,2))/2);
        
        //calcolo il delta sulle energie normalizzato, (E(t)-E(0)) / E(0)
        deltaenergy = (energy - energiazero) / energiazero;
        
        fprintf(fout,"%f\t%f\t%f\t%f\t%f\n", t,x_now,v_now,energy,deltaenergy);
    }
    
    //DEBUG FLAG
    printf("Metodo di Eulero: stampo i grafici\n");
    
    system("gnuplot -e \"set terminal png; set output 'x_v_eulero.png'; plot 'data_eulero.dat' using 2:3 \"");
    system("gnuplot -e \"set terminal png; set output 't_x_eulero.png'; plot 'data_eulero.dat' using 1:2 \"");
    system("gnuplot -e \"set terminal png; set output 't_E_eulero.png'; plot 'data_eulero.dat' using 1:4 \"");

    return deltaenergy;
}

double EulerCromer(double x0, double v0, double dt, double omega2, double m, int Tmax){
    //Memoria del passo attuale e del passo precedente
    double x_now, v_now;
    double x_old = x0, v_old = v0;
    
    //Calcolo dell'energia al tempo zero
    double energiazero = ((m*(v0*v0))/2)+((k*(x0*x0))/2);
    double energy, deltaenergy;
    
    //Handler per il file
    FILE *fout, *fopen();
    fout = fopen("data_eulerocromer.dat","w");
    
    //DEBUG FLAG
    printf("Metodo di Eulero-Cromer: inizio ciclo iterativo\n");
    
    //Ciclo iterativo
    for(double t=t0; t<Tmax;t+=dt){
        //calcolo posizione e velocità nel passo
        v_now = v_old + dt*omega2*x_old;
        x_now = x_old + dt*v_now;
        
        //aggiorno le variabili
        x_old = x_now;
        v_old = v_now;
        
        //calcolo l'energia
        energy = ((m*pow(v_now,2))/2)+((k*pow(x_now,2))/2);
        
        //calcolo il delta sulle energie normalizzato, (E(t)-E(0)) / E(0)
        deltaenergy = (energy - energiazero) / energiazero;
        
        fprintf(fout,"%f\t%f\t%f\t%f\t%f\n", t,x_now,v_now,energy,deltaenergy);
    }
    
    //DEBUG FLAG
    printf("Metodo di Eulero-Cromer: stampo i grafici\n");
    
    system("gnuplot -e \"set terminal png; set output 'x_v_eulerocromer.png'; plot 'data_eulerocromer.dat' using 2:3 \"");
    system("gnuplot -e \"set terminal png; set output 't_x_eulerocromer.png'; plot 'data_eulerocromer.dat' using 1:2 \"");
    system("gnuplot -e \"set terminal png; set output 't_E_eulerocromer.png'; plot 'data_eulerocromer.dat' using 1:4 \"");
    
    return deltaenergy;
}

double PuntoCentrale(double x0, double v0, double dt, double omega2, double m, int Tmax){
    //Memoria del passo attuale e del passo precedente
    double x_now, v_now;
    double x_old = x0, v_old = v0;
    
    //Calcolo dell'energia al tempo zero
    double energiazero = ((m*(v0*v0))/2)+((k*(x0*x0))/2);
    double energy, deltaenergy;
    
    //Handler per il file
    FILE *fout, *fopen();
    fout = fopen("data_puntocentrale.dat","w");
    
    //DEBUG FLAG
    printf("Metodo del Punto Centrale: inizio ciclo iterativo\n");
    
    //Ciclo iterativo
    for(double t=t0; t<Tmax;t+=dt){
        //calcolo posizione e velocità nel passo
        v_now = v_old + dt*omega2*x_old;
        x_now = x_old + dt*((v_old+v_now)/2);
        
        //aggiorno le variabili
        x_old = x_now;
        v_old = v_now;
        
        //calcolo l'energia
        energy = ((m*pow(v_now,2))/2)+((k*pow(x_now,2))/2);
        
        //calcolo il delta sulle energie normalizzato, (E(t)-E(0)) / E(0)
        deltaenergy = (energy - energiazero) / energiazero;
        
        fprintf(fout,"%f\t%f\t%f\t%f\t%f\n", t,x_now,v_now,energy,deltaenergy);
        
    }
    
    //DEBUG FLAG
    printf("Metodo del Punto Centrale: stampo i grafici\n");
    
    system("gnuplot -e \"set terminal png; set output 'x_v_puntocentrale.png'; plot 'data_puntocentrale.dat' using 2:3 \"");
    system("gnuplot -e \"set terminal png; set output 't_x_puntocentrale.png'; plot 'data_puntocentrale.dat' using 1:2 \"");
    system("gnuplot -e \"set terminal png; set output 't_E_puntocentrale.png'; plot 'data_puntocentrale.dat' using 1:4 \"");
    
    return deltaenergy;
}

double VerletAS(double x0, double v0, double dt, double omega2, double m, int Tmax){
    //Memoria del passo attuale e del passo precedente
    double x_now, v_now;
    double x_old = x0, v_old = v0;
    
    //Calcolo dell'energia al tempo zero
    double energiazero = ((m*(v0*v0))/2)+((k*(x0*x0))/2);
    double energy, deltaenergy;
    
    //Handler per il file
    FILE *fout, *fopen();
    fout = fopen("data_verletAS.dat","w");
    
    //DEBUG FLAG
    printf("Metodo di Verlet Autosufficiente: inizio ciclo iterativo\n");
    
    //Ciclo iterativo
    for(double t=t0; t<Tmax;t+=dt){
        //calcolo posizione e velocità nel passo
        x_now = x_old + v_old*dt + (0.5)*(omega2*x_old)*(dt*dt);
        v_now = v_old + (((omega2*x_old)+(omega2*x_now))/2)*dt;
        
        //aggiorno le variabili
        x_old = x_now;
        v_old = v_now;
        
        //calcolo l'energia
        energy = ((m*pow(v_now,2))/2)+((k*pow(x_now,2))/2);
        
        //calcolo il delta sulle energie normalizzato, (E(t)-E(0)) / E(0)
        deltaenergy = (energy - energiazero) / energiazero;
        
        fprintf(fout,"%f\t%f\t%f\t%f\t%f\n", t,x_now,v_now,energy,deltaenergy);
        
    }
    
    //DEBUG FLAG
    printf("Metodo di Verlet Autosufficiente: stampo i grafici\n");
    
    system("gnuplot -e \"set terminal png; set output 'x_v_verletAS.png'; plot 'data_verletAS.dat' using 2:3 \"");
    system("gnuplot -e \"set terminal png; set output 't_x_verletAS.png'; plot 'data_verletAS.dat' using 1:2 \"");
    system("gnuplot -e \"set terminal png; set output 't_E_verletAS.png'; plot 'data_verletAS.dat' using 1:4 \"");
    
    return deltaenergy;
}

double RungeKuttaIV(double x0, double v0, double dt, double omega2, double m, int Tmax){
    //Memoria del passo attuale e del passo precedente
    double x_now, v_now;
    double x_old = x0, v_old = v0;
    
    //dichiaro
    double k1, j1, vm1, am1, k2, j2, vm2, am2, k3, j3, vf, af, k4, j4, a; 
    
    //Ciclo iterativo
    for(double t=t0; t<Tmax; t+=dt){
        
        //aggiorno le variabili
        x_old = x_now;
        v_old = v_now;
    }
}
