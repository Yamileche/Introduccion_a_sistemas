#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int defSimb(char c);
int aut(char far[]);

int state(int type, int estado);

int main(){
	char pal[80];
	printf("Ingrese el nombre de variable: ");
	fgets(pal, 80, stdin);
	if(aut(pal) == 1) printf("Nombre de variable aceptado\n");
	else printf("No es aceptado el nombre\n");

	return 0;
}


int aut(char far[]){
	int len, i, st = 0;
	len = strlen(far);
	for(i=0;i<len;i++){
		st = state(defSimb(far[i]),st);
		//printf("prog %c  sta %d\n\n",far[i], st);
		if(st == -1 || far[i] == ' ') return -1;
	}
	if(st == 1) return 1;
	else return -1;
}

int defSimb(char c){
	if(isalpha(c)) return 0;
	if(isdigit(c)) return 1;
	if(c == '_') return 2;
	return -1;
}

int state(int type, int estado){
	switch(estado){
		case 0:
			if(type == 0) return 1;
			if(type == 1) return -1;
			if(type == 2) return 2;
			break;
		case 1:
			if(type == 0) return 1;
			if(type == 1) return 1;
			if(type == 2) return 1;
			break;
		case 2:
			if(type == 0) return 1;
			if(type == 1) return -1;
			if(type == 2) return -1;
			break;
		default: return -1;		
	}
}
