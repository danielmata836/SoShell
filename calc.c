#include "shell.h"

void calc(char *value1, char *op, char *value2){
	float v1=atof( value1) ;   
	float v2=atof( value2 );
	float result;   
	switch(*op){
		case '+':	
		result = v1+v2;
	        printf("Resultado = %.2f\n",result);
	        break;
	        case '-':
	        result=v1-v2;
	        printf("Resultado = %.2f\n",result);
	        break;
	        case '*':
	        result=v1*v2;
	        printf("Resultado = %.2f\n",result);
	        break;
	        case '/':
	        result=v1/v2;
	        printf("Resultado = %.2f\n",result);
	        break;
	        case '^':
	        result=pow(v1, v2);
	        printf("Resultado = %.2f\n",result);
	        break;
	        default: printf("Erro! Operação não é correta.\n");
	}
	return;
}


void bits(char *op1, char *op, char *op2){
	unsigned int v1=atof(op1) ;   
	unsigned int v2=atof(op2 );
	if(*op == '&'){
		printf("%d\n", v1 & v2);
	}
	if(*op == '|'){ 
		printf("%d\n", v1 | v2);
	}
	if(*op == '^'){ 
		printf("%d\n", v1 ^ v2);		
	}

}

int isjpg(int fileDescriptor) //esboço da função
{
	unsigned char b[4];
	read(fileDescriptor,b,4);
	//voltar ao inicio do ficheiro com lseek
	if ( b[0]==0xff && b[1]==0xd8 && b[2]==0xff && b[3]==0xe0)
		return 1;//se for JPG
	return 0;//se não for
}

/*EXEMPLO
void calc( char *value1, char *op, char *value2){{   
int v1=atotf( value1) ;   
int v2=atotf( value2 );   
if ( op=='+' ) 	result = v1+v2   printf("Resulatdo = %f",result)}

Mudar Makefile (incluir calc.c)
Mudar shell.h .. adicionar protipos
Mudar  main.c .. 
adicicionar codigo na função "builtin")*/
