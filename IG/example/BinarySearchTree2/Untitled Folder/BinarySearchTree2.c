// Pedro Henrique Rossi Ribeiro - Jun 2016

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

int aux = 0;

struct noArv{
    int info;
    struct noArv* esq;
    struct noArv* dir;
};
typedef struct noArv NoArv;

struct noArv* cria(void)
{;
    return NULL;
}
struct noArv* retira(struct noArv *r,int v)
{
    if(r==NULL)return NULL;
    else if(r->info > v)r->esq = retira(r->esq,v);
    else if(r->info < v)r->dir = retira(r->dir,v);
    else{
        if(r->esq == NULL && r->dir ==NULL)
        {
            free(r);
            r = NULL;
        }
        else if(r->esq == NULL)
        {
            NoArv *t = r;
            r = r->dir;
            free(t);
        }
        else if(r->dir==NULL)
        {
            NoArv* t = r;
            r = r->esq;
            free(t);
        }
        else{
            NoArv* f = r->esq;
            while(f->dir !=NULL)
            {
                f = f->dir;
            }
            r->info = f->info;
            f->info = v;
            r->esq = retira(r->esq,v);
        }

    }
    return r;
}
void infixa(NoArv* a)
{
    if(a!=NULL)
    {
        infixa(a->esq);
        if(aux==1)printf(" ");
        printf("%d",a->info);
        aux = 1;
        infixa(a->dir);
    }
}

void prefixa(NoArv* a)
{
    if(a!=NULL)
    {
        if(aux==1)printf(" ");
        printf("%d",a->info);
        aux = 1;
        prefixa(a->esq);
        prefixa(a->dir);
    }
}
void posfixa(NoArv* a)
{
    if(a!=NULL)
    {

        posfixa(a->esq);
        posfixa(a->dir);
        if(aux==1)printf(" ");
        printf("%d",a->info);
        aux = 1;
    }
}
struct noArv* procura(struct noArv* r,int v)
{
    if(r==NULL)
        return NULL;
    else if(r->info>v)return procura(r->esq,v);
    else if(r->info<v)return procura(r->dir,v);
    else return r;
}

struct noArv* insere(struct noArv *a,int v)
{
    if(a==NULL)
    {
        a = (NoArv*)malloc(sizeof(struct noArv));
        a->info = v;
        a->esq = a->dir = NULL;
    }
    else if(v<a->info)a->esq = insere(a->esq,v);
    else if(v>a->info)a->dir = insere(a->dir,v);
    return a;
}

int main()
{
    struct noArv *g = cria();
    char str[10];
    int x;
    while(scanf("%[^\n]s",str)!=EOF)
    {
        if(str[0]=='I' && str[1]==' '){
            x = atoi(&str[2]);
            g = insere(g,x);
        }
        if(str[0]=='P' && str[1]==' '){
            x = atoi(&str[2]);
            if(procura(g,x))printf("%d existe\n",x);
            else printf("%d nao existe\n",x);
        }
        if(str[0]=='I' && str[1]=='N'){
            aux = 0;
            infixa(g);
            printf("\n");
        }
        if(str[0]=='P' && str[1]=='O'){
            aux = 0;
            posfixa(g);
            printf("\n");
        }
        if(str[0]=='P' && str[1]=='R'){
            aux = 0;
            prefixa(g);
            printf("\n");
        }
        if(str[0]=='R')
        {
            x = atoi(&str[2]);
            g = retira(g,x);
        }
        getchar();
    }
    return 0;
}