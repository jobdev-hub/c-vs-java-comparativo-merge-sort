#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#define TAM 19

void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);

int main()
{
    int *a, elementos, i, j;
    float tempo;
    clock_t t;
    FILE *arquivo;
    arquivo = fopen("analitico-paralelo.csv","w");
    elementos = 1000;

    for(i=0; i < TAM; i++)
    {
        a = (int *)malloc(sizeof(int) * elementos);
        srand(time(0));
        for(j=0; j < elementos; j++) a[j] = rand() % 100;
        t = clock();
        mergesort(a, 0, elementos-1);
        t = clock() - t;
        tempo = ((float)t)/((CLOCKS_PER_SEC/1000)); // http://wurthmann.blogspot.com/2015/04/medir-tempo-de-execucao-em-c.html
        printf("elementos %d => %d ms\n", elementos, (int)tempo);
        fprintf(arquivo,"%d;%d\n",elementos,(int)tempo);
        free(a);
        elementos *= 2;
    }
    return 0;
}

void mergesort(int a[],int i,int j)
{
    int mid;
    if(i<j)
    {
        mid=(i+j)/2;
        #pragma omp parallel sections num_threads(2)
        {
          #pragma omp section
          {
            mergesort(a,i,mid);        //left recursion
          }
          #pragma omp section
          {
            mergesort(a,mid+1,j);    //right recursion
          }
        }
        merge(a,i,mid,mid+1,j);    //merging of two sorted sub-arrays
    }
}

void merge(int a[],int i1,int j1,int i2,int j2)
{
    int *temp;    //array used for merging
    int i,j,k,tam;
    i=i1;    //beginning of the first list
    j=i2;    //beginning of the second list
    k=0;
    tam = j2-i1+1;
    temp = (int *) malloc(tam*sizeof(int));

    while(i<=j1 && j<=j2)    //while elements in both lists
    {
        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }

    while(i<=j1)    //copy remaining elements of the first list
        temp[k++]=a[i++];

    while(j<=j2)    //copy remaining elements of the second list
        temp[k++]=a[j++];

    //Transfer elements from temp[] back to a[]
    for(i=i1,j=0;i<=j2;i++,j++)
        a[i]=temp[j];

    free(temp);
}
