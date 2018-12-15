#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include "util.h"
#include "jsocket.h"

#define BUF_SIZE 200

pthread_mutex_t m= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
char *est[]={NULL,NULL,NULL,NULL,NULL};

typedef void *(*Thread_fun)(void *);


int disponible(int k){
	int cont=0;
	for(int i=0;i<5;i++){
		if (est[i]==NULL){
			cont++;
		}
		if (est[i]!=NULL){
			cont=0;
		}
		if (cont==k){
			return i-k+1;
		}
	}
	return -1;
}

int reservar(char *nom,int k){
	pthread_mutex_lock(&m);
	int emp=disponible(k);
	if (emp==-1){
		pthread_cond_wait(&cond,&m);
	}
	for (int i=emp;i<emp+k;i++){
		est[i]=nom;
	}
	pthread_mutex_unlock(&m);
	return emp;
}

void liberar(char *nom){
	pthread_mutex_lock(&m);
	for(int i=0;i<5;i++){
		if(strcmp(est[i],nom)==0){
			est[i]=NULL;
		}
	}
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&m);
}

void *serv(int s){
	char *nom;
	int ind;
	char esp;
	char *acc;
	fprintf(stderr,"cliente conectado\n");
	nom=getstr(s);
	acc=getstr(s);
	if(strcmp(acc,"r")){
		leer(s,&esp,1);
		ind=reservar(nom,esp);
		write(s,&ind,sizeof(ind));	
	}
	if(strcmp(acc,"l")){
		liberar(nom);
	}
	close(s);
	fprintf(stderr,"cliente desconectado\n");
	return NULL;
}


int main(int argc, char **argv) {
    long s, s2;
    pthread_t pid;
    int port= argc>=2 ? atoi(argv[1]) : 3000;
    signal(SIGPIPE, SIG_IGN);
    s = j_socket();
    if(j_bind(s, port) < 0) {
        fprintf(stderr, "bind failed\n");
    exit(1);
    }
/* Cada vez que se conecta un cliente le creo un thread */
    for(;;) {
        pthread_attr_t attr;
        s2= j_accept(s);
        pthread_attr_init(&attr);
        if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) {
            fprintf(stderr, "No se puede establecer el atributo\n");
        }
        if ( pthread_create(&pid, &attr, (Thread_fun)serv, (void *)s2) != 0) {
            fprintf(stderr, "No pude crear thread para nuevo cliente %ld!!!\n", s2);
            close(s2);
        }
        pthread_attr_destroy(&attr);
    }
    return 0;
}
