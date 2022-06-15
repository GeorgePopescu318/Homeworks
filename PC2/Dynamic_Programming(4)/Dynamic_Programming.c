//Popescu Andrei-George, 162, Problema 6
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
int min(int a, int b)
{
    if (a < b)
        return a;
    return  b;
}
void read_alloc(int ***a, int ***b, int *n, FILE *f)
{
    fscanf(f,"%d", n);
    *a = malloc((*n)*sizeof(int *));
    for (int i = 0; i < *n; i++)
    {
        *(*a + i)=malloc((i+1)*sizeof(int));
    }
    *b = malloc((*n)*sizeof(int *));
    for (int i = 0; i < *n; i++)
    {
        *(*b + i) =malloc((i+1)*sizeof(int));
    }
    
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j <= i; j++) {
            fscanf(f,"%d", &(*a)[i][j]);
        }
    }
}
void deallocM(int ***a, int ***b, int n)
{
    for (int i = 0; i < n; i++)
    {
        free((*a)[i]);
    }
    free(*a);
    for (int i = 0; i < n; i++)
    {
        free((*b)[i]);
    }
    free(*b);
    
}
void matrix_creation(int **a, int **b, int n)
{
    b[n-1][0] = a[n-1][0];
    for (int i = n-2; i >= 0; i--) {
        b[i][0] = a[i][0] + b[i+1][0];
    }
    for (int i = 1; i < n; i++) {
        b[n-1][i] = a[n-1][i] + b[n-1][i-1];
    }
    for (int i = n-2; i >=1 ; i--) {
        for (int j = 1; j <= i; j++) {
            b[i][j] = a[i][j] + min(b[i+1][j],b[i][j-1]);
        }
    }
}
void solution(int **a, int **b, int n, FILE *g)
{
    int min1 = INT_MAX;
    int i;
    int j;
    for (int k = 0; k < n-1; k++)
    {
        if (b[k][k] < min1)
        {
            min1 = b[k][k];
            i = k;
        }
        
    }
    j = i;
    b[i][j] = -1;
    while (i < n-1 && j >= 0)
    {
        if (i == n-1)
            j--;
        else
            if (j == 0)
                i++;
        else
            if (b[i+1][j] < b[i][j-1])
                i++;
        else
            if (b[i+1][j] >= b[i][j-1])
            j--;  
        b[i][j] = -1;
    }
    b[n-1][0]= -1;
    i = n-1;
    j = 0;
    fprintf(g,"%d",a[i][j]);
    while (i >0 && j <i)
    {
        if (b[i][j+1] == -1)
        {
            j++;
        }
        else
            i--;
        fprintf(g,"->%d",a[i][j]);
        
    }
}
void check(FILE *f, FILE *g)
{
    char d,c;
    c = getc(f);
    d = getc(g);
    while(c != EOF && d != EOF)
    {
        c = getc(f);
        d = getc(g);
        if (c != d)
        {
            printf("%c %c\n",c,d);
        }
        assert( c == d);        
    }
}
void files()
{
    FILE *i1 = fopen("test1.in","r");
    FILE *i2 = fopen("test2.in","r");
    FILE *o1 = fopen("test1.out","r");
    FILE *o2 = fopen("test2.out","r");
    FILE *out = fopen("date.out","w+");
    int n;
    int **a;
    int **b;
    read_alloc(&a, &b, &n, i1);
    matrix_creation(a, b, n);for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
    solution(a, b, n, out);
    deallocM(&a, &b, n);
    check(out, o1);
    fclose(out);
    fclose(i1);
    fclose(o1);
    printf("\n\n");
    out = fopen("date.out","w+");
    read_alloc(&a, &b, &n, i2);
    matrix_creation(a, b, n);for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
    solution(a, b, n, out);
    deallocM(&a, &b, n);
    check(out, o2);
    printf("\n\n");
    fclose(i2);
    fclose(o2);
}
int main() {
    int n;
    int **a;
    int **b;
    files();
    FILE *f = fopen("date.in","r");
    FILE *g = fopen("date.out","w+");
    read_alloc(&a, &b, &n, f);
    matrix_creation(a, b, n);for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
    solution(a, b, n, g);
    deallocM(&a, &b, n);
    fclose(f);
    fclose(g);
    return 0;
}