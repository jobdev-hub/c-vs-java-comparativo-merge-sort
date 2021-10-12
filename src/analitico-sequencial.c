#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void mergeSort(int a[], int inicio, int fim){
    int meio;
    if(inicio < fim){
        meio = floor((inicio+fim)/2);
        mergeSort(a,inicio,meio);
 		mergeSort(a,meio+1,fim);
        merge(a,inicio,meio,fim);
    }
}

void merge(int a[], int inicio, int meio, int fim){
    int *temp, p1, p2, tam, i, j, k;
    int fim1 = 0, fim2 = 0;
    tam = fim-inicio+1;
    p1 = inicio;
    p2= meio+1;
    temp = (int *) malloc(tam*sizeof(int));
    if (temp != NULL){
        for (i=0; i < tam; i++){
            if(!fim1 && !fim2){
                if(a[p1] < a[p2]) temp[i]=a[p1++];
                else temp[i]=a[p2++];
                if(p1>meio) fim1=1;
                if(p2>fim) fim2=1;
            } else{
                if(!fim1) temp[i]=a[p1++];
                else temp[i]=a[p2++];
            }
        }
        for(j=0, k=inicio; j<tam; j++, k++) a[k]=temp[j];
    }
    free(temp);
}

int intRand(int min, int max){
    int n = (rand() % (max - min + 1)) + min;
    return n;
}

int main(){
    int *a, num, i, j;
    float tempo;
    clock_t t;
    for(i=0; i <= 25; i++){
        num = pow(2,i)*1000;
        a = (int *)(malloc(num * sizeof(int)));
        srand(time(0));
        for(j=0; j < num; j++) a[j] = intRand(1, 100);
        t = clock();
        mergeSort(a, 0, num-1);
        t = clock() - t;
        tempo = ((float)t)/((CLOCKS_PER_SEC/1000)); // http://wurthmann.blogspot.com/2015/04/medir-tempo-de-execucao-em-c.html
        printf("\n%d elements => %.0f ms", num, tempo);
    }
    return 0;
}
