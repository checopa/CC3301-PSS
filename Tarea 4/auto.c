#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "jsocket.h"
#include "util.h"
int largoHost(char* env){
    char* aux=env;
    int i=0;
    while((*aux)!=':'){
        i++;
        aux++;
    }
    return i;
}
int getPort(char* env){
    char* aux=env;
    while((*aux)!=':'){
        aux++;
    }
    aux++;
    int res=0;
    res=atoi(aux);
    return res;
}

int main(int argc,char **argv){
	int s;
	int esp;
	int ind;

	s=j_socket();
	char* ambiente=getenv("PARKING");
    char* host=malloc(largoHost(ambiente));
    strncpy(host,ambiente,lhost);
    int port=getPort(ambiente);
    if(j_connect(s,host,port)<0){
        fprintf(stderr,"Conexion fallida\n");
        exit(1);
}
	char *nom=argv[1];
	char *acc=argv[2];
	if(strcmp("r",acc)==0){
		esp=atoi(argv[3]);
		sendstr(s,nom);
		sendstr(s,acc);
		write(s,&esp,1);
		leer(s,(char*)&ind,sizeof(ind));
		fprintf(stderr,"%d \n",ind);
		close(s);

	}
	else{
		sendstr(s,nom);
		sendstr(s,acc);
		close(s);		
	
	}
}