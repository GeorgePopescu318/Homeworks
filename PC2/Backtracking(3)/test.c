//Besel Adrian, Grupa 162, Pb 7

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char wordle[5];
char cuvant[5];
char galbene[5];
char solutie[5];
int nr_galbene = 0;

void citire(FILE *fin)
{

    char litera;
    char potrivire;

    fscanf(fin, "%c", &litera);
    printf("Litera stiuta este: %c\n", litera);

    fscanf(fin, "%c", &potrivire);

    fscanf(fin, "%c", &potrivire);
    printf("Potrivirea stiuta este: %c\n", potrivire);

    fscanf(fin, "%s", &solutie);
    printf("Solutia este: %s\n", solutie);

    if(potrivire == 'G')
    {
        galbene[nr_galbene] = litera;
        nr_galbene++;
    }
    else
    {
        int i;
        for(i = 0; i < 5; i++)
            if(litera == solutie[i])
                wordle[i] = litera;
    }

    fclose(fin);
}

int valid(int k)
{
    int i;
    FILE *dic = fopen("Dictionar.txt", "r");
    for(i = 0; i < k; i++)
        fscanf(dic, "%s", cuvant);
    fclose(dic);

    for(i = 0; i < 5; i++)
        {
            if(wordle[i] != NULL)
            if(wordle[i] != cuvant[i])
                return 0;
        }

    int ok = 1;
    for(i = 0; i < nr_galbene; i++)
            if(strchr(cuvant,galbene[i]) == NULL)
                ok = 0;
    if(ok == 0)
        return 0;
    return 1;
}

void litere_noi(char cuvant[5], FILE *fout)
{
    int i;
    fprintf(fout,"%s\n",cuvant);
    for(i = 0; i < 5; i++)
        if(cuvant[i] == solutie[i])
            wordle[i] = cuvant[i];

    int aux = nr_galbene;
    for(i= 0; i < 5; i++)
        if(strchr(solutie,cuvant[i]) && strchr(galbene, cuvant[i]) == NULL
           && strchr(wordle,cuvant[i]) == NULL)
    {
        galbene[nr_galbene] = cuvant[i];
        nr_galbene++;
    }
}

void bkt(int k, FILE *fout)
{
    int i;
    int ok = 1;
    if(valid(k))
    {
        litere_noi(cuvant,fout);
        for(i = 0; i < 5; i++)
            if(wordle[i] == NULL)
                ok = 0;
    }
    else
        ok = 0;
    if(ok == 1)
        fprintf(fout, "Cuvantul cautat este: %s", wordle);
    else
        {
            k++;
            bkt(k,fout);
        }
}

void asert()
{
    char cuv1[9],cuv2[9];
    FILE *f1 = fopen("date.out", "r");
    FILE *f2;

    ///Test 1
    /*f2 = fopen("Test1.out", "r");
    while(fscanf(f1, "%s", cuv1) != EOF && fscanf(f2, "%s", cuv2) != EOF)
        assert(strcmp(cuv1,cuv2) == 0);
    fclose(f2);*/

    ///Test 2
    /*f2 = fopen("Test2.out", "r");
    while(fscanf(f1, "%s", cuv1) != EOF && fscanf(f2, "%s", cuv2) != EOF)
        assert(strcmp(cuv1,cuv2) == 0);
    fclose(f2);*/

    ///Test 3
    /*f2 = fopen("Test3.out", "r");
    while(fscanf(f1, "%s", cuv1) != EOF && fscanf(f2, "%s", cuv2) != EOF)
        assert(strcmp(cuv1,cuv2) == 0);
    fclose(f2);*/

    fclose(f1);
}

int main()
{
    FILE *fin = fopen("date.in", "r");
    FILE *fout = fopen("date.out", "w");

    citire(fin);
    bkt(1,fout);
    fclose(fout);
    asert();

    return 0;
}