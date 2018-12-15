#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "jsocket.h"
#include "util.h"
unsigned int largo_host(char* env){
    char* aux=env;
    unsigned int i=0;
    while((*aux)!=':'){
        i++;
        aux++;
    }
    return i;
}
void my_copy(char** s1,char* s2){
    char* ps1=*s1;
    char* aux=s2;
    while((*aux)!=':'){
        *ps1=*aux;
        aux++;
        ps1++;
    }
    *ps1=0;
}
int getPort(char* env){
    char* aux=env;
    while((*aux)!=':'){
        aux++;
    }
    aux++;
    int res=0;
    while(*aux){
        res=res*10+(*aux-'0');
        aux++;
    }
    return res;
}

int main(int argc,char **argv){
	int s;
	int esp;
	int ind;

	s=j_socket();

	/*if (j_connect(s,"localhost",3000)<0){
		fprintf(stderr,"connection refused\n");
		exit(1);
	}*/
	char* ambiente=getenv("PARKING");
    unsigned int lhost=largo_host(ambiente);
    char* host=malloc(lhost+1);
    my_copy(&host,ambiente);
    int port=getPort(ambiente);
    if(j_connect(s,host,port)<0){
        fprintf(stderr,"Falló conexión");
        exit(1);
}
	char *nom=argv[1];
	char *acc=argv[2];
	fprintf(stderr, "%s\n",nom );
	fprintf(stderr, "%s\n",acc );
	if(strcmp("r",acc)==0){
		esp=atoi(argv[3]);
		sendstr(s,nom);
		sendstr(s,acc);
		write(s,&esp,1);
		leer(s,(char*)&ind,sizeof(ind));
		fprintf(stderr,"%d \n",ind);
		close(s);
		fprintf(stderr, "Esta aqui" );
	}
	else{
		write(s,nom,sizeof(nom)+1);
		write(s,&acc,1);
		close(s);		
	
	}
}