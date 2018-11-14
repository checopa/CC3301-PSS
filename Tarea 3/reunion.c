#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "reunion.h"

struct reunion {
	int asisten;
	int concluyen;
	pthread_mutex_t m;
	pthread_cond_t cond;
   // declare acá un mutex y una condición y los contadores que
      // Ud. necesitará para resolver el problema de sincronización
};

Reunion *nuevaReunion(){
	Reunion *r=malloc(sizeof(Reunion));
	pthread_mutex_init(&r->m,NULL);
	pthread_cond_init(&r->cond,NULL);
	r->asisten=0;
	r->concluyen=0;
	return r;
}

void entrar(Reunion *r){
	pthread_mutex_lock(&r->m);
	while(r->asisten!=r->concluyen)
		pthread_cond_wait(&r->cond,&r->m);
	r->asisten++;
	pthread_cond_broadcast(&r->cond);
	pthread_mutex_unlock(&r->m);
}

void concluir(Reunion *r){
	pthread_mutex_lock(&r->m);
	while(r->asisten==r->concluyen)
		pthread_cond_wait(&r->cond,&r->m);
	r->concluyen++;
	pthread_cond_broadcast(&r->cond);
	pthread_mutex_unlock(&r->m);
}
