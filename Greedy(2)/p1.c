// 162 Popescu Andrei - George nr. 4
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct 
{
    int left, right;
}intervals;
void read_alloc( intervals **v, int *n, FILE *f)
{
    int i;   
    fscanf(f,"%d", n);
    *v = (intervals *) malloc((*n) * sizeof(intervals));
    for (i = 0; i < *n; i++)
    {
       fscanf(f,"%d %d", &((*v)[i].left), &((*v)[i].right));
    }
}
int compare(const void *A, const void *B)
{
    intervals *a = (intervals *)A;
    intervals *b = (intervals *)B;
    return a->left - b->left;
}
void solution(intervals *v, int n, FILE *g)
{
    int point;
    point = v[0].right;
    int aux = v[0].left;
    for (int i = 1; i < n; i++)
    {
        if(point < v[i].left)
        {
            fprintf(g,"%d\n", point);
            point = v[i].right;
            aux = v[0].left;
        }
        if(aux < v[i].left && point > v[i].right)
        {
            point = v[i].right;
            aux = v[i].left;
        }
    }
    fprintf(g,"%d", point);
}
void verification(FILE *f, FILE *g)
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
            printf(";%c;%c;\n",c,d);
        }
        assert( c == d);        
    }
    assert( c == d);
}
void sorted_print(intervals *v, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d %d\n", v[i].left, v[i].right);
    }
    
}
void files()
{
    FILE *out = fopen("date.out","w+");
    FILE *i1 = fopen("date1.in","r");
    FILE *o1 = fopen("date1.out","r");
    FILE *i2 = fopen("date2.in","r");
    FILE *o2 = fopen("date2.out","r");
    FILE *i3 = fopen("date3.in","r");
    FILE *o3 = fopen("date3.out","r");
    FILE *i4 = fopen("date4.in","r");
    FILE *o4 = fopen("date4.out","r");
    FILE *i5 = fopen("date5.in","r");
    FILE *o5 = fopen("date5.out","r");
    int m;
    intervals *s;
    printf("....................................\n");
    read_alloc(&s, &m, i1);
    qsort(s, m, sizeof(intervals), compare);
    sorted_print(s, m);
    solution(s, m, out);
    fclose(out);
    out = fopen("date.out","r");
    verification(out, o1);
    fclose(out);
    free(s);
    printf("....................................\n");
    out = fopen("date.out","w+");
    read_alloc(&s, &m, i2);
    qsort(s, m, sizeof(intervals), compare);
    sorted_print(s, m);
    solution(s, m, out);
    fclose(out);
    out = fopen("date.out","r");
    verification(out, o2);
    fclose(out);
    free(s);
    printf("....................................\n");
    out = fopen("date.out","w+");
    read_alloc(&s, &m, i3);
    qsort(s, m, sizeof(intervals), compare);
    sorted_print(s, m);
    solution(s, m, out);
    fclose(out);
    out = fopen("date.out","r");
    verification(out, o3);
    fclose(out);
    free(s);
    printf("....................................\n");
    out = fopen("date.out", "w+");
    read_alloc(&s, &m, i4);
    qsort(s, m, sizeof(intervals), compare);
    sorted_print(s, m);
    solution(s, m, out);
    fclose(out);
    free(s);
    printf("....................................\n");
    out = fopen("date.out","w+");
    read_alloc(&s, &m, i5);
    qsort(s, m, sizeof(intervals), compare);
    sorted_print(s, m);
    solution(s, m, out);
    fclose(out);
    free(s);
    printf("....................................\n");
    fclose(i1);
    fclose(o1);
    fclose(i2);
    fclose(o2);
    fclose(i3);
    fclose(o3);
    fclose(i4);
    fclose(o4);
    fclose(i5);
    fclose(o5);
}
int main()
{
    int n;
    intervals *v;
    FILE *f = fopen("date.in", "r");
    FILE *g = fopen("date.out", "w");
    read_alloc(&v, &n,f);
    qsort(v,n,sizeof(intervals), compare);
    sorted_print(v,n);
    solution(v, n, g);
    free(v);
    fclose(f);
    fclose(g);
    files();

return 0;

}