#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef long int RANDOM_TYPE;

int main(){
  
  RANDOM_TYPE a = 7, seed = 9, randomNumber, m = 10;
  int position = 0, steps = 100000;
  randomNumber = seed;

  FILE *filedat = fopen("file.dat","w"); 

  int i=0;
  for(i=0;i<steps;i++){
    double r;
    fprintf(filedat, "%d %d \n", i, position);
    randomNumber = (a * randomNumber);
    r = (double)randomNumber * 1/m;
    if(r<0.5){
      position += 1;
    }else{
      position -= 1;
    }
  }

  fprintf(filedat, "%d %d \n", i, position);
  
  return 0;
}
