# include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CHAR_BITS 8
typedef unsigned int uint;

void print_binit(int num){
	int sup=CHAR_BITS*sizeof(int);
	while(sup>= 0){
		if (num & (((int)1)<<sup))
			printf("1");
		else
			printf("0");
		sup--;
	}
	printf("\n");
}

uint borrar_bits (uint x, uint pat, int len){
	print_binit(x);
	for(int i=0;i<=(32-len);i++){
		unsigned mask1=(1<<32-i)-1;
		unsigned mask2=(1<<(32-len-i))-1;
		int c=mask1-mask2;
		int d=c&x;
		if ((d>>(32-len-i))==pat){
			x=x&(~c);
			print_binit(x);
			i=i+len;
		}
	}
	return x;
}

char *reemplazo(char *s, char c, char *pal){
	char *s1=s;
	char *pal1=pal;
	int cont=0;
	while(*s1){
		cont++;
		*s1++;
	}
	char *prt=(char*)malloc(cont*sizeof(char));
	char *prt1=prt;
	printf("%s\n", prt);
	while(*s){
		if(*s!=c){
			*prt=*s;
			printf("%s\n", prt);
			*prt++;
			*s++;
			}
		else{
			*s++;
		}
	}
	*prt=*prt1;
	return prt;

}



int main(int argc, const char * argv[]){	
		char *src= "";
		src= "hola que tal";
        char *res= reemplazo(src, 'a', "xyz");
        printf("%d\n",*res+1 );
	}