#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "t1.h"

uint borrar_bits (uint x, uint pat, int len){
	//print_binit(x);
	for(int i=0;i<=(32-len);i++){
		unsigned mask1=(1<<(32-i))-1;
		unsigned mask2=(1<<(32-len-i))-1;
		int c=mask1-mask2;
		int d=c&x;
		if ((d>>(32-len-i))==pat){
			x=x&(~c);
			//print_binit(x);
			i=i+len;
		}
	}
	return x;
}

char *reemplazo(char *s, char c, char *pal){
	int cont=0;
	int contpal=0;
	int conc=0;
	while(*pal){
		contpal++;
		pal++;
	}
	pal=pal-contpal;
	while(*s){
		if(*s==c){
			conc++;
		}
		cont++;
		s++;
	}
	s=s-cont;
	int larpal=cont+conc*(contpal-1);
	char *prt=(char*)malloc(larpal);
	while(*s){
		if(*s==c){
			while(*pal){
				*prt=*pal;
				prt++;
				pal++;
			}
			pal=pal-contpal;
			s++;
		}
		else{
			*prt=*s;
			prt++;
			s++;
		}
	}

	prt=prt-larpal;
	return prt;

}

