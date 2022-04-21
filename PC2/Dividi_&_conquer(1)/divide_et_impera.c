#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
void read_alloc(int **arr, int *n)
{
    FILE *f = fopen("etaje.in", "r");
    fscanf(f,"%d",n);
    *arr = (int *) malloc( ((*n) + 1) * sizeof(int));
    for (int i = 0; i <= *n; i++)
    {
        (*arr)[i] = i;
    }
    fclose(f);
}
int gauss(int n)
{

    int sum= 0;
    int i;
   for (i = 0; sum <= n; i++)
   {
       sum += i;
   }
   return i-1;
 
}
void gauss_conquer(int *arr,int lf, int rg,int x,int gterm,FILE *g, int n)
{
    if (arr[rg] + gterm - 1 > n)
        {
        for (int i = rg; i <= x; i++)
            {
               fprintf(g,"Maria arunca de la etajul:%d\n", arr[i]);
            }
        fprintf(g,"Sticla s-a spart!\n");
        }
    else
    if (arr[rg] < x)
        {
            fprintf(g,"Maria arunca de la etajul:%d\n",arr[rg]);
            gauss_conquer( arr, rg, rg + gterm - 1, x, gterm - 1, g, n);
        }
    else
    if (arr[rg] >= x)
        {
            fprintf(g,"Maria arunca de la etajul:%d\n",arr[rg]);
            fprintf(g,"Sticla s-a spart!\n");
            int i;
            for (i = lf+1; i <= x; i++)
            {
               fprintf(g,"Maria arunca de la etajul:%d\n",arr[i]);
            }
            if( i == x + 1)
            fprintf(g,"Sticla s-a spart!\n");
        }
    
        
        
}
void binary_search(int *arr,int lf,int rg,int x,FILE *g,int n)
{
    int mid;
    mid = (lf + rg)/2;
    if(arr[mid] == n)
        {fprintf(g,"Maria arunca de la etajul:%d\n",arr[mid]);
        fprintf(g,"Sticla s-a spart!\n");
        }
    else
    if (arr[mid] < x)
        {
            fprintf(g,"Maria arunca de la etajul:%d\n",arr[mid]);
            binary_search(arr, mid + 1, rg, x, g,n);
        }
    else
    if (arr[mid] >= x)
        {
            fprintf(g,"Maria arunca de la etajul:%d\n",arr[mid]);
            fprintf(g,"Sticla s-a spart!\n");
            int i;
            for (i = lf; i <= x; i++)
            {
               fprintf(g,"Maria arunca de la etajul:%d\n", arr[i]);
            }
            fprintf(g,"Sticla s-a spart!\n");
            return;
        }
}
void verificare(FILE *f, FILE *g, int *arr, int n, int x, int gterm)
{
    
    gauss_conquer(arr, 0, gterm, x, gterm, g, n);
    fprintf(g,"-----------------------------------------\n");
    binary_search(arr, 0, n, x, g, n);
    rewind(f);
    rewind(g);
    char d,c;
    c = getc(f);
    d = getc(g);
    while(c != EOF)
    {
        c = getc(f);
        d = getc(g);
        assert( c == d);
        if (c != d)
        {
            printf(";%c;%c;%d;\n",c,d,x);
        }
        
    }
    assert( c == d);

}
void files(int *arr)
{
    FILE *f = fopen("test.txt", "r");
    FILE *g = fopen("etaje.out", "w+");
    FILE *d = fopen("test1.txt", "r");
    FILE *e = fopen("test2.txt", "r");
    int n = 100;
    int x = 87;
    int gterm = gauss(n);
    verificare(f, g, arr, n, x, gterm);
    fclose(g);
    x = 100;
    g = fopen("etaje.out", "r+");
    verificare(d, g, arr, n, x, gterm);
    fclose(g);
    x = 69;
    g = fopen("etaje.out", "r+");
    verificare(e, g, arr, n, x, gterm);
    fclose(f);
    fclose(g);
    fclose(d);
    fclose(e);
}
void randomcheck(int *arr, int gterm, int n)
{
    srand(time(NULL));
    int x = rand()%n + 1;
    FILE *g = fopen("etaje.out","w");
    printf("%d\n", x);
    time_t t1, t2;
    t1 = clock();
    gauss_conquer(arr, 0, gterm, x, gterm, g, n);
    t2 = clock();
    printf("%.3f\n", 1. *  (t2 - t1) / CLOCKS_PER_SEC);
    fprintf(g,"-----------------------------------------\n");
    time_t t3, t4;
    t3 = clock();
    binary_search(arr, 0, n, x, g, n);
    t4 = clock();
    printf("%.3f\n", 1. *  (t4 - t3) / CLOCKS_PER_SEC);
    fclose(g);
}
int main()
{
    int n, *arr, gterm;
    read_alloc(&arr, &n);
    gterm = gauss(n);
    files(arr);
    randomcheck(arr, gterm, n);
    free(arr);

return 0;

}