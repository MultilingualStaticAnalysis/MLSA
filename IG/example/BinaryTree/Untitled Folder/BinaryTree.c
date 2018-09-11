// Pedro Henrique Rossi Ribeiro - Jun 2016

#include <stdio.h>
#include <stdlib.h>

typedef struct grafo{
    struct grafo *esq;
    struct grafo *dir;
    int i;
}GRAFO;

struct grafo* cria()
{
    return NULL;
};

struct grafo* insere(GRAFO *G, int elem){

    GRAFO *gr = (GRAFO*)malloc(sizeof(struct grafo)),*aux,*ant;
    aux = G;
    if(!gr)return G;
    gr->i = elem;
    gr->dir = NULL;
    gr->esq = NULL;

    if(!G)
        return gr;

    while(1)
    {

        if(aux->i<elem)
        {
            if(aux->dir!=NULL){
                aux = aux->dir;
            }
            else if(aux->dir == NULL){
                aux->dir = gr;
                return G;
            }
        }
        else if(aux->i>elem)
        {
            if(aux->esq!=NULL){
                aux = aux->esq;
            }
            else if(aux->esq == NULL){
                aux->esq = gr;
                return G;
            }
        }
    }
};

void preO(GRAFO *G)
{
    if(G)
    {
        printf(" %d",G->i);
        preO(G->esq);
        preO(G->dir);
    }
}

void posO(GRAFO *G)
{
    if(G)
    {
        posO(G->esq);
        posO(G->dir);
        printf(" %d",G->i);
    }
}

void intO(GRAFO *G)
{
    if(G)
    {
        intO(G->esq);
        printf(" %d",G->i);
        intO(G->dir);
    }
}

int main(){
    int a,b,c,d=1;
    GRAFO *g = cria();
    scanf("%d",&a);
    while(a--)
    {
        scanf("%d",&b);
        while(b--)
        {
            scanf("%d",&c);
            g = insere(g,c);
        }
        printf("Case %d:\n",d++);
        printf("Pre.:");
        preO(g);
        printf("\nIn..:");
        intO(g);
        printf("\nPost:");
        posO(g);
        printf("\n\n");
        g = cria();
    }
}