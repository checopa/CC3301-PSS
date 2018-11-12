#include <stdio.h>
#include <stdlib.h>
#include "colapri.h"
#include "colapri-lista.h"

typedef struct nodo {
void *valor;
struct nodo *sig;
}Nodo ;

typedef struct {
  ColaPriOps *ops;
  CompPri comp;
  int n;
  Nodo *elems;
} ColaPriList;

static void agregar(ColaPri colapri,void *a);
static void* extraer(ColaPri colapri);
static void* mejor(ColaPri colapri);
static int tamano(ColaPri colapri);
static void destruir(ColaPri colapri);
static IterColaP iterador(ColaPri colapri);

static ColaPriOps colapri_list_ops= {
  agregar, extraer, mejor, tamano,destruir, iterador };

ColaPri nuevaColaPriLista(CompPri comp) {
  ColaPriList *cp= malloc(sizeof(ColaPriList));
  cp->ops= &colapri_list_ops;
  cp->comp= comp;
  cp->n=0;
  cp->elems= malloc(sizeof(Nodo));
  cp->elems->sig=NULL;
  return (ColaPri)cp;
}

static void agregar(ColaPri colapri,void *a){
	ColaPriList *cp=(ColaPriList*)colapri;
	Nodo *temp=(Nodo*)malloc(sizeof(Nodo));
	Nodo *aux=cp->elems;
	temp->valor=a;
	temp->sig=NULL;
	if (cp->n==0){
		cp->elems->valor=a;
	}
	else{

	if ((*cp->comp)(a,cp->elems->valor)<0){
		temp->sig=cp->elems;
		cp->elems=temp;
	}
	else{

		while(aux->sig!=NULL && ((*cp->comp)(a, aux->sig->valor)>0)){
			aux=aux->sig;
		}
		temp->sig=aux->sig;
		aux->sig=temp;
	}
	}
	cp->n++;	
}


static int tamano(ColaPri colapri) {
  ColaPriList *cp= (ColaPriList*)colapri;
  return cp->n;
}

static void* mejor(ColaPri colapri) {
  ColaPriList *cp= (ColaPriList*)colapri;
  return cp->elems->valor;
}


static void* extraer(ColaPri colapri) {
	ColaPriList *cp= (ColaPriList*)colapri;
	void *res=cp->elems->valor;
	if (cp->n==1){
		cp->elems->valor=NULL;
	}
	else{
	Nodo *aux=cp->elems->sig;
	cp->elems->sig=aux->sig;
	cp->elems->valor=aux->valor;
	}
	cp->n--;
	return res;
}

static void destruir(ColaPri colapri) {
  ColaPriList *cp= (ColaPriList*)colapri;
  free(cp->elems);
  free(cp);
}

typedef struct {
  IterColaPOps *ops;
  ColaPriList *cp;
  int k;
} IterColaPList;

static int continua(IterColaP iter);
static void* proximo(IterColaP iter);
static void destruirIter(IterColaP iter);

static IterColaPOps iterOps= { continua, proximo, destruirIter };

IterColaP iterador(ColaPri colapri) {
  IterColaPList *iter= malloc(sizeof(IterColaPList));
  iter->ops= &iterOps;
  iter->cp= (ColaPriList*)colapri;
  iter->k= 0;
  return (IterColaP)iter;
}

static int continua(IterColaP itercp) {
  IterColaPList *iter= (IterColaPList*)itercp;
  return iter->k < iter->cp->n;
}
static void *proximo(IterColaP itercp) {
  IterColaPList *iter= (IterColaPList*)itercp;
  int i=0;
  Nodo *aux=iter->cp->elems;
  while(i<iter->k){
  	aux=aux->sig;
  	i++;
  }
  iter->k++;
  return aux->valor;
}

static void destruirIter(IterColaP iter) {
  free(iter);
}
