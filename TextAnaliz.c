#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char *ptr; //указатель
    unsigned int size; //количество заполненных элементов счетчик
    unsigned int capacity; //вместимость счетчик
}CharVector;

CharVector* new_vector(size_t initial_capacity) //создает новый массив
{   
    CharVector *z=malloc(sizeof(CharVector));
    if (z==NULL)
    {
        exit(-1);
    }
    z->ptr=malloc(initial_capacity*sizeof(int));
    if (z->ptr==NULL)
    {
        exit(-1);
    }
    z->capacity = initial_capacity;
    z->size=0;
    return z;
}

int count_word(CharVector *z)
{
    int cnt=0;
    for (int i = 0; i < z->size; i++)
    {
        if (z->ptr[i]==' ' || z->ptr[i]=='\n')
        {
            cnt++;
        }
        
    }
return cnt;
}

void check_open(FILE *a)
{
    if (a==NULL)
    {
        printf("Произошла ошибка открытия текстого файла. Завершение программы.\n");
        exit(1);
    }

}

void check(int a)
{
    if (a==1)
    {
        printf("Произошла ошибка. Программа завершается...\n");
        exit(1);
    }
    
}

void printall(CharVector *z, int cnt, char *argv[])
{
    FILE *result;
    result=fopen(argv[2],"w");
    fprintf(result, "Количество символов в тексте: %d\n", z->size);
    fprintf(result, "Количество слов в строке: %d\n", cnt);
    fclose(result);
}

void word_count(CharVector *z, FILE *text, char *argv[])
{
    fread(z->ptr,1,z->capacity,text);
    fseek(text ,0, SEEK_SET);    
    char sep[15]=" .,!?;:-\n";
    char* t;
    char *a[z->size],*pov[z->size];
    int i=0,j,k,sk,pov_count[500],h=0,d,f;
    
    t=strtok(z->ptr, sep);
    while (t != NULL) 
    {
        a[i]=t;
        t = strtok (NULL, sep);
        i++;
    }

    for ( j = 0; j < i; j++)
    {
        sk=0;
        f=0;
        for ( k = 0; k < i; k++)
        {
            if (strcmp(a[k],a[j])==0)
            {
                sk++;
            }
            
        }
        for ( d = 0; d < h; d++)
        {
            if (strcmp(a[j],pov[d])==0)
            {
                f++;
            }
            
        }
        
        if (sk>1 && f==0)
        {
            pov[h]=a[j];
            pov_count[h]=sk;
            h++;
        }
    }
    
    FILE *result;
    result=fopen(argv[2],"a");
    check_open(result);
    for(j=0; j<h; j++) 
    {
      fprintf(result, "\nСлово, которое повторяется: %s",pov[j]);
      fprintf(result, "\nКоличество повторений     : %i",pov_count[j]);
      fprintf(result, "\n");
    }
    fclose(result);
}

void longworld(CharVector *z, FILE *text, char *argv[])
{
    fread(z->ptr,1,z->capacity,text);
    fseek(text ,0, SEEK_SET);
    char geps[]=" .,!?;:-\n";
    char *t;
    char *a[z->size],*res;
    int i=0, q=0, maxlong=0;

    t=strtok(z->ptr, geps);
    while (t != NULL) 
    {
        a[i]=t;
        t = strtok (NULL, geps);
        i++;
    }

    for (int j = 0; j < i; j++)
    {
        q=strlen(a[j]);
        if (q>maxlong)
        {
            res=a[j];
            maxlong=q;
        }
           
    }

    FILE *result;
    result=fopen(argv[2],"a");
    check_open(result);
    fprintf(result,"\nСамое длинное слово : %s\n", res);
    fclose(result);
}

void longSentence(CharVector *z, FILE *text, char *argv[])
{
    fread(z->ptr,1,z->capacity,text);
    fseek(text ,0, SEEK_SET);
    char *t;
    char *a[z->size],*res;
    int i=0, q=0, maxlong=0;

    t=strtok(z->ptr, ".!?");
    while (t != NULL) 
    {
        a[i]=t;
        t = strtok (NULL, ".!?");
        i++;
    }
    for (int j = 0; j < i; j++)
    {
        q=strlen(a[j]);
        if (q>maxlong)
        {
            res=a[j];
            maxlong=q;
        }
           
    }
    FILE *result;
    result=fopen(argv[2] ,"a");
    check_open(result);
    fprintf(result,"\nСамое длинное предложение : %s\n", res);
    fclose(result);
}

int main(int argc, char *argv[])
{   
    if (argc!=3)
    {
      printf("Необходимо ввести название текстового файла и название выходного файла\n");
      return 1;
    }

    int cnt=0, size=0;
    FILE *text;

    text=fopen(argv[1], "r");
    check_open(text);
    
    fseek (text, 0, SEEK_END);
    size= ftell(text);
    fseek(text ,0, SEEK_SET);
    CharVector *z = new_vector(size);

    z->size=fread(z->ptr,1,z->capacity,text);
    cnt=count_word(z);
    printall(z, cnt, argv);
    longSentence(z, text, argv);
    longworld(z, text, argv);
    word_count(z, text, argv);
    fclose(text);
    
return 0;
}