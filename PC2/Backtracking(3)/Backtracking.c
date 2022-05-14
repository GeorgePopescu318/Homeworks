#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
char answer[6];
char option[6];
int position[6];
char letters[6];
void get_answer()
{
    int pos, col;
    printf("Insert the answer: ");
    scanf("%s", answer);
    printf("Inset the given letter:");
    scanf("%s", letters);
    printf("Insert the position of the given letter, 1 for yellow and 2 for green:");
    scanf("%d %d", &pos, &col);
    position[pos] = col;
}
int verification(FILE *g)
{
    int ok = 1;
    if (position[0] == 2 && option[0] != answer[0])
        {
       //printf("..%c..\n", option[0]);
        ok = 0 ;
        }
    else
        for (int i = 0; i < 5; i++)
        {
            if (strchr(answer, option[i]) != 0 && strchr(letters, option[i]) == 0 && position[i] != 2)
                {
                        position[i] = 1;
                        strncat(letters, &option[i],1); 
                        //printf("{%s}\n", letters);
                }     
            if (option[i] == answer[i])
                {
                    if (position[i] != 2)
                    {
                        fprintf(g,"%s\n", option); 
                        position[i] = 2;
                        continue;

                    }
               }
            if (position[i] == 2)
                {
                    if (option[i] != answer[i])      
                        {
                            //printf("..%c.1\n", option[i]);
                            ok = 0;
                            continue;
                        }
                }
            if (position[i] == 1)
                {
                    if (strchr(letters, option[i]) != 0)
                        {
                            ///printf("..%c.2\n", option[i]);
                            ok = 0;
                        }
                }
        }

    return ok;
}
int all_green(FILE *g)
{
    if(verification(g) == 0)
        {
            //printf("1%s\n", option);
            return 0;
        }
    for (int i = 0; i < 5; i++)
        {
            if ( position[i] != 2)
                {
                    //printf("2%s\n", option);
                    return 0;
                }
        }
    return 1;
    
}
void word_finder(FILE *f, FILE *g)
{
    while (strcmp(option,"!") != 0)
    { 
        fscanf(f,"%s",option);
        if( all_green(g) == 1)
        {   
            fprintf(g,"%s", option);   
            break;
        }
    }
}
void check(FILE *f, FILE *g)
{
    // char d,c;
    // c = getc(f);
    // d = getc(g);
    // while(c != EOF && d != EOF)
    // {
    //     c = getc(f);
    //     d = getc(g);
    //     if (c != d)
    //     {
    //         printf("%c %c\n",c,d);
    //     }
    //     assert( c == d);        
    // }
    // assert( c == d);
    char word1[6],word2[6];
    while(fscanf(g,"%s",word2) != EOF && fscanf(f,"%s",word1) != EOF)
        {
            if (strcmp(word1,word2) !=0)
            printf("%s %s\n", word1, word2);
            assert(strcmp(word1,word2)==0);
        }
}
void files(FILE *f)
{
    FILE *out = fopen("Order.out","w+");
    FILE *o1 = fopen("date1.out","r");
    FILE *o2 = fopen("date2.out","r");
    FILE *o3 = fopen("date3.out","r");
    FILE *o4 = fopen("date4.out","r");
    FILE *o5 = fopen("date5.out","r");
    rewind(f);
    answer[0] = '\0';
    strcpy(answer,"glass");
    answer[6] = '\0';
    letters[1] = '\0';
    letters[0] = 'a';
    for (int i = 0; i < 5; i++)
    {
        option[i] = 0;
    }
    option[0] = 1;
    word_finder(f,out);
    check(o1,out);
    rewind(f);
    answer[0] = '\0';
    strcpy(answer, "hotel");
    answer[6] = '\0';
    letters[1] = '\0';
    letters[0] = 'h';
    for (int i = 0; i < 5; i++)
    {
        option[i] = 0;
    }
    option[0] = 2;
    fclose(out);
    out = fopen("Order.out","w+");
    word_finder(f,out);
    check(o2,out);   
    fclose(out);
    rewind(f);
    answer[0] = '\0';
    strcpy(answer, "knife");
    answer[6] = '\0';
    letters[1] = '\0';
    letters[0] = 'e';
    for (int i = 0; i < 5; i++)
    {
        option[i] = 0;
    }
    option[1] = 1;
    out = fopen("Order.out","w+");
    word_finder(f,out);
    check(o2,out);
    fclose(out);
    rewind(f);
    answer[0] = '\0';
    strcpy(answer, "limit");
    answer[6] = '\0';
    letters[1] = '\0';
    letters[0] = 'i';
    for (int i = 0; i < 5; i++)
    {
        option[i] = 0;
    }
    option[2] = 1;
    out = fopen("Order.out","w+");
    word_finder(f,out);
    check(o2,out);
    fclose(out);
    rewind(f);
    answer[0] = '\0';
    strcpy(answer, "queen");
    answer[6] = '\0';
    letters[1] = '\0';
    letters[0] = 'e';
    for (int i = 0; i < 5; i++)
    {
        option[i] = 0;
    }
    option[2] = 2;
    out = fopen("Order.out","w+");
    word_finder(f,out);
    check(o2,out);
    fclose(out);  
    fclose(o1);
    fclose(o2);
    fclose(o3);
    fclose(o4);
    fclose(o5);
}
int main()
{
    get_answer();
    FILE *f = fopen("Words.in","r");
    FILE *g = fopen("Order.out","w");
    word_finder(f, g);
    files(f);
    fclose(f);
    fclose(g);
return 0;

}