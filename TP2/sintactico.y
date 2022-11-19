%{
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
extern char *yytext;
extern int yylex(void);
extern void yyerror();

void leerIdentificador(char* identificador);
void escribirExpresion(int valor);
int asignarExpresion(char* identificador, int valor);
int procesarIdentificador(char* identificador);

char* tablaDeSimbolos[10];
int valores[10];
int ultimoIdentificador;

%}

%union {char* nombre; int num;}

%token <num> INICIO FIN LEER ESCRIBIR ASIGNACION MAS MENOS PARIZQ PARDER COMA PCOMA CONSTANTE
%token <nombre> IDENTIFICADOR 

%type <num> expresion listaExpresiones primaria;


%start programa

%%



programa: INICIO listaSentencias FIN {printf("Compilacion exitosa!");exit(0);};

listaSentencias: listaSentencias sentencia  | sentencia;

sentencia:    IDENTIFICADOR ASIGNACION expresion PCOMA{asignarExpresion($1,$3);} // printf("algo es algo \n"); el error de los identificadores NO declarados esta aca
            | LEER PARIZQ listaIdentificadores PARDER PCOMA 
            | ESCRIBIR PARIZQ listaExpresiones PARDER PCOMA;

expresion: primaria{$$ = $1;} | primaria MAS expresion{$$ = $1 + $3;} | primaria MENOS expresion{$$ = $1 - $3;}; //ya

listaIdentificadores:   IDENTIFICADOR{leerIdentificador($1);} COMA listaIdentificadores | IDENTIFICADOR{leerIdentificador($1);};

listaExpresiones:  expresion{escribirExpresion($1);} COMA listaExpresiones| expresion{escribirExpresion($1);}  ;

primaria: IDENTIFICADOR{$$ = procesarIdentificador($1);} | CONSTANTE{$$ = $1;} | PARIZQ expresion PARDER{$$ = $2;}; //ya


%%

int main(){
yyparse();
}

int identificadorNoDeclarado(char* identificador){
  for(int i=0; i<10; i++){
    if(tablaDeSimbolos[i] == identificador){
        return 0;
    }
  }
  return 1;
}

int buscarIdentificador(char* identificador){
  for(int i=0; i<10; i++){
    if(tablaDeSimbolos[i] == identificador){
        return i;
    }
  }
  return -1;
}

void leerIdentificador(char* identificador){
    int valor;
    printf("Inserte un valor %s\n", identificador);
    scanf("%d", valor);
    if(identificadorNoDeclarado(identificador)){
      tablaDeSimbolos[ultimoIdentificador] = identificador;
      valores[ultimoIdentificador] = valor;
      ultimoIdentificador++;
    }else{
      int i = buscarIdentificador(identificador);
      valores[i] = valor;
    }

}

int procesarIdentificador(char* identificador){
  int i = buscarIdentificador(identificador);
  if(i>=0){
    return valores[i];
  }else{
    printf("Error semantico: uno de los identificadores no fue declarado \n");
    exit(0);
  }

}

void escribirExpresion(int valor){
  printf("El valor de la expresion es: %d \n", valor);
}

int asignarExpresion(char* identificador, int valor){
  int i = buscarIdentificador(identificador);
  if(i>=0){
    valores[i]=valor;
  }else{
    printf("Error semantico: uno de los identificadores no fue declarado \n");
    exit(0);
  }
}

void yyerror()
{
  printf("Error sintactico: el programa no esta estructurado correctamente");
  exit(0);
}

int yywrap()
{	
return 1;
}