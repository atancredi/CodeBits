#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define t0 0

float Euler(float x0, float v0, float deltat, float omega, float m, int Tmax);
float Euler_Cromer(float x0, float v0, float deltat, float omega, float m, int Tmax);
float Energy(float m, float v, float k, float x);

int main(){

  //Dichiaro le variabili INPUT
  float x0, v0, m, deltat, k, omega;
  int Tmax;
  
  //Chiedo all'utente se vuole usare i dati preimpostati ed inserire solo il delta T oppure vuole inserire i dati a mano
  char automode;
  printf("Usare la modalita' automatica (y / n)? Verra' richiesto di inserire solo l'intervallo temporale.\n");
  printf("I dati per la modalita' automatica sono: Tmax=50s, m=1Kg, k=1N/m, x0=1m, v0=0m/s\n");
  scanf(" %c", &automode);
  if(automode == 'y'){
    Tmax = 50;
    m = 1;
    k = 1;
    x0 = 1;
    v0 = 0;
    printf("\nInserisci il passo di integrazione Delta t\n");
    printf("(In secondi - float maggiore di zero)\n");
    scanf(" %f", &deltat);
  }else if(automode == 'n'){
    //Richiedo all'utente di inserire le variabili
    printf("\nInserisci il tempo massimo di esecuzione\n");
    printf("(In secondi - intero maggiore di zero)\n");
    scanf(" %i", &Tmax);
    printf("\nInserisci il passo di integrazione Delta t\n");
    printf("(In secondi - float maggiore di zero)\n");
    scanf(" %f", &deltat);
    printf("\nInserisci la massa del corpo\n");
    printf("(In Kg - float maggiore di zero)\n");
    scanf(" %f", &m);
    printf("\nInserisci la costante elastica della molla\n");
    printf("(In newton/metro - float maggiore di zero)\n");
    scanf(" %f", &k);
    printf("Inserisci la posizione al tempo zero\n");
    printf("(In metri - float maggiore di zero)\n");
    scanf(" %f", &x0);
    printf("\nInserisci la velocita' al tempo zero\n");
    printf("(In metri/secondo - float maggiore di zero)\n");
    scanf(" %f", &v0);
  }else{
    printf("Puoi inserire solo y per confermare o n per inserire i dati a mano.\n");
    exit(0);
  }
  
  //Calcolo omega - pulsazione dell'oscillatore armonico, e metto per comodità il segno meno
  omega = (k/m)*(-1);
  
  Euler(x0, v0, deltat, omega, m, Tmax);
  Euler_Cromer(x0, v0, deltat, omega, m, Tmax);
}

float Euler(float x0, float v0, float deltat, float omega, float m, int Tmax){

  //punto al file su cui devo salvare i dati
  FILE *fout, *fopen();
  fout = fopen("osc_eulero.dat","w");
  
  //dichiaro due variabili che contengono i dati del passo attuale
  float x_now, v_now;
  
  //dichiaro due variabili che mi aiutano a contenere i dati del passo precedente a quello attuale
  float x_old, v_old;

  //Prima di iterare il ciclo assegno alle variabili *_old i valori iniziali di posizione e velocità
  x_old = x0;
  v_old = v0;
  
  for(float t=t0; t<Tmax; t+=deltat){

    x_now = x_old + deltat*v_old;
    v_now = v_old + deltat*omega*x_old;

    x_old = x_now;
    v_old = v_now;

    float costanteelastica = omega*m;
    float energy = Energy(m, v_now, costanteelastica, x_now);
    
    fprintf(fout,"%f\t%f\t%f\t%f\n", t,x_now,v_now,energy);
  }

}

float Euler_Cromer(float x0, float v0, float deltat, float omega, float m, int Tmax){

  //punto al file su cui devo salvare i dati
  FILE *fout, *fopen();
  fout = fopen("osc_eulerocromer.dat","w");
  
  //dichiaro due variabili che contengono i dati del passo attuale
  float x_now, v_now;
  
  //dichiaro due variabili che mi aiutano a contenere i dati del passo precedente a quello attuale
  float x_old, v_old;

  //Prima di iterare il ciclo assegno alle variabili *_old i valori iniziali di posizione e velocità
  x_old = x0;
  v_old = v0;
  
  for(float t=t0; t<Tmax; t+=deltat){

    x_now = x_old + deltat*v_now;
    v_now = v_old + deltat*omega*x_old;

    x_old = x_now;
    v_old = v_now;

    float costanteelastica = omega*m;
    float energy = Energy(m, v_now, costanteelastica, x_now);
    
    fprintf(fout,"%f\t%f\t%f\t%f\n", t,x_now,v_now,energy);
  }

}

float Energy(float m, float v, float k, float x){
  //Calcolo l'energia nel singolo passo d'integrazione
  float E = ((m*pow(v,2))/2)+((k*pow(x,2))/2);
  return E;
}
