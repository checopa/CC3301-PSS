#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "t1.h"


uint borrar_bits (uint x, uint pat, int len){
	for(int i=0;i<=(32-len);i++){
		unsigned mask1=(1<<(32-i))-1;
		unsigned mask2=(1<<(32-len-i))-1;
		int c=mask1-mask2;
		int d=c&x;
		if ((d>>(32-len-i))==pat){
			x=x&(~c);
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

void reemplazar(char *s, char c, char *pal){
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
	if (contpal>1){
		char *r;
		r=s+larpal;
		s=s+cont;
		pal=pal+contpal-1;
		int cont2=0;
		while(cont2!=larpal){
			if (*s==c){
				int cont3=0;
				while(cont3<=contpal-1){
					*r=*pal;
					r--;
					pal--;
					cont3++;
				}
				pal=pal+contpal;
				cont3=0;
				s--;
			}
			else{
				*r=*s;
				r--;
				s--;
			}
		cont2++;	
		}
		*s=*r;
	}
	if (contpal==0){
		char *r;
		r=s;
		while(*s){
			if (*s==c){
				s++;
			}
			else{
				*r=*s;
				s++;
				r++;
			}
		}
		*s=*r;
		*r='\0';
}
	if(contpal==1){
		while(*s){
			if(*s==c){
				*s=*pal;
			}
			s++;
		}
	}
	
}
