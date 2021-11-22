#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define t0 0
#define NDELTA 10

float Euler(float x0, float v0, float deltat, float omegaquadro, float m, int Tmax);
float Euler_Cromer(float x0, float v0, float deltat, float omegaquadro, float m, int Tmax);
float Energy(float m, float v, float k, float x);

int main(){

  //Dichiaro le variabili INPUT
  float x0, v0, m, deltat, k, omega;
  int Tmax;

  //Array che contiene i deltat a cui applicare l'algoritmo
  double deltats[NDELTA];
  deltats[0] = 1;
  for(int k=1;k<NDELTA;k++){
    deltats[k]= deltats[k-1]/Tmax;
  }
  
  printf("I dati sono: Tmax=10s, m=1Kg, k=1N/m, x0=1m, v0=0m/s\n");
  if(1){
    Tmax = 10;
    m = 1;
    k = 1;
    x0 = 1;
    v0 = 0;
  }
  
  //Calcolo omega al quadrato - pulsazione dell'oscillatore armonico
  omegaquadro = (k/m);
  
  Euler(x0, v0, deltat, omegaquadro, m, Tmax);
  Euler_Cromer(x0, v0, deltat, omegaquadro, m, Tmax);
}

float Euler(float x0, float v0, float deltat, float omegaquadro, float m, int Tmax){

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
