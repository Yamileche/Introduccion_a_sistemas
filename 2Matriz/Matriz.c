#include <stdio.h>    
#include <stdlib.h>      
#include <string.h>   
#include <math.h>



typedef struct _matriz_{
  	int n, m;
  	double **A;
}MATRIZ;

MATRIZ Lee(int m,int n);
void Escribe(MATRIZ A);
MATRIZ GJ(MATRIZ A);


MATRIZ creaEspacioMatriz(int m, int n);
int liberaEspacioMatriz(MATRIZ *mat);

MATRIZ MatCoef(MATRIZ A);

MATRIZ GJ(MATRIZ a);
MATRIZ multaFilEs(MATRIZ a, int fila, double escalar);
MATRIZ intfila(MATRIZ a, int fil1, int fil2);
MATRIZ sumafilaPorEs(MATRIZ a,int fil1,int fil2, double c);
MATRIZ copiaMatriz(MATRIZ a);

MATRIZ refina(MATRIZ A);
int sol(MATRIZ A);

int determina(MATRIZ A); 



int main(int argN, char ** ArgV[]){
	int m, n;
	MATRIZ A, ret;
	printf("Ingrese el número de variables: ");
	scanf("%d", &m);
	n = m + 1; 
	A = Lee(m,n);
	printf("\n\nSe ha ingresado:\n");
	Escribe(A);
	printf("\n\n");
	ret = GJ(A);
	if(determina(ret)){
		printf("La solución es:\n\n");
		sol(ret);	
	}else{
		printf("El sistema no tiene solución\n\n");
	}
	return 0;
}

MATRIZ copiaMatriz(MATRIZ a){
	MATRIZ m;
	int i, j;
	m.m=a.m;
	m.n=a.n;
	m=creaEspacioMatriz(m.m,m.n);
	for(i=0;i<a.m;i++){
		for(j=0;j<a.m;j++){
			m.A[i][j]=a.A[i][j];
		}
	}
	return m;
}

MATRIZ MatCoef(MATRIZ A){
	MATRIZ ret;
	int i, j;
	ret = creaEspacioMatriz(A.m, A.m);	
	ret.m = A.m;
	ret.n = A.m;
	for(i=0; i<A.m; i++){
		for(j=0;j<A.m;j++){
			ret.A[i][j] = A.A[i][j];
		}
	}
	return ret;
}

MATRIZ Lee(int m, int n){
	MATRIZ ret={m:m, n:n, A:NULL}; 
  	int i, j;

  	ret.A = (double**)malloc(m*sizeof(double*));
	for(i=0;i<m;i++){
		ret.A[i] = (double*)malloc(n*sizeof(double*));
	}
	
	for(i=0; i<m;i++){
		printf("\n\nPor leer coeficientes de la %d ecuación\n\n", i+1);
		for(j=0; j<n-1;j++){
			printf("x_%d = ", j+1);
			scanf("%lg", &ret.A[i][j]);
		}
		printf("\nCoef ind = ");
		scanf("%lg", &ret.A[i][n-1]);	
	}
  return ret;
}
void Escribe(MATRIZ A){
	int i, j;
	
	for(i=0; i<A.m;i++){
		for(j=0; j<A.n-1;j++){
			printf("%4lg * x_%d  ",A.A[i][j],j+1);
		}
		printf("= %4lg", A.A[i][A.n-1]);
		printf("\n");	
	}
}

MATRIZ creaEspacioMatriz(int m, int n){
	MATRIZ ret={m:m, n:n, A:NULL}; 
  int i;

  ret.A = (double**)malloc(m*sizeof(double*));
  if (ret.A!=NULL){
    for(i=0; i<m; i++){
      ret.A[i] = (double *)malloc(n*sizeof(double));
      if (ret.A[i]==NULL){
        while(i>0){
          free(ret.A[--i]);
          ret.A[i] = NULL;
        }
        break;
      }
    }
  }

  return ret;
}
int liberaEspacioMatriz(MATRIZ *mat){
	int i;

  for (i=0; i<mat->m; i++){
    free(mat->A[i]);
    mat->A[i]=NULL;
  }
  free(mat->A);
  mat->A=NULL;
  mat->m = mat->n = 0;
  return 0;
}




/**************************************************************/









MATRIZ GJ(MATRIZ a){
	MATRIZ I, b, copia;
	int i,j;
	double c;


	for(j=0;j<a.m;j++){
	    for(i=j;i<a.m;i++){

		    if(a.A[j][j]==0.0){
			    if(a.A[j][j]==0.0 && a.A[i][j]!=0.0){
			        c=a.A[i][j];
				    multaFilEs(a,i,1.0/c);
				    intfila(a,j,i);
				    break;
	            }	
		    }else{
			    c=a.A[j][j];
	            multaFilEs(a,i,1.0/c);	
		   }
	    
	    }
	    for(i=j+1;i<a.m;i++){
		    c=a.A[i][j];
		    sumafilaPorEs(a,j,i,-c);
	    }
    }
    
    for(i=0;i<a.m;i++){
    	for(j=i+1;j<a.m;j++){
    		c=a.A[i][j];
		    sumafilaPorEs(a,j,i,-c);
		}
	}
	return refina(a);
}

MATRIZ multaFilEs(MATRIZ a, int fila, double escalar){
	int i;
	for(i=0;i<a.n;i++){
		a.A[fila][i]=a.A[fila][i]*escalar;
	}
	return a;
}
MATRIZ intfila(MATRIZ a, int fil1, int fil2){
	int i;
	double c;
	for(i=0;i<a.n;i++){
		c=a.A[fil2][i];
		a.A[fil2][i]=a.A[fil1][i];
		a.A[fil1][i]=c;
	}
	return a;
}
MATRIZ sumafilaPorEs(MATRIZ a,int fil1,int fil2, double c){
	int i;
	for(i=0;i<a.n;i++){
		a.A[fil2][i]=a.A[fil1][i]*c+a.A[fil2][i];
	}
	return a;
}
MATRIZ refina(MATRIZ A){
	int i, j;
	double ep = 0.0000000001;

	for(i=0;i< A.m;i++){
		for(j=0;j< A.m;j++){
			if(-ep < A.A[i][j] && A.A[i][j] < ep) A.A[i][j] = 0;
		}	
	}

	return A;
}


int determina(MATRIZ A){
	int i, j, k =0;
	for(i=0;i<A.m;i++){
		k=0;
		for(j = 0; j<A.m;j++){
			if (A.A[i][j] != 0.0) k = 1;
		}
		if(k == 0) return 0;	
	}
	return 1;
}

int sol(MATRIZ A){
	int i;
	for(i=0; i<A.m;i++) printf("x_%d = %lg\n", i+1, A.A[i][A.m]);
}





