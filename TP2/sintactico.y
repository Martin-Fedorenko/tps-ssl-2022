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
void errorIdentificadorNoDeclarado();
int asignarExpresion(char* identificador, int valor);
int procesarIdentificador(char* identificador);

char tablaDeSimbolos[100][32];
int valores[100] = {};
int ultimoIdentificador = 0;

%}

%union {char nombre[32]; int num;}

%token <num> INICIO FIN LEER ESCRIBIR ASIGNACION MAS MENOS PARIZQ PARDER COMA PCOMA CONSTANTE
%token <nombre> IDENTIFICADOR 

%type <num> expresion listaExpresiones primaria;

%start programa


%%

programa: INICIO listaSentencias FIN {printf("Compilacion exitosa!");exit(0);};

listaSentencias: listaSentencias sentencia  | sentencia;

sentencia:    IDENTIFICADOR ASIGNACION expresion PCOMA{asignarExpresion($1,$3);}
            | LEER PARIZQ listaIdentificadores PARDER PCOMA 
            | ESCRIBIR PARIZQ listaExpresiones PARDER PCOMA;

expresion: primaria{$$ = $1;} | primaria MAS expresion{$$ = $1 + $3;} | primaria MENOS expresion{$$ = $1 - $3;};

listaIdentificadores:   IDENTIFICADOR{leerIdentificador($1);} COMA listaIdentificadores | IDENTIFICADOR{leerIdentificador($1);};

listaExpresiones:  expresion{escribirExpresion($1);} COMA listaExpresiones| expresion{escribirExpresion($1);};

primaria: IDENTIFICADOR{$$ = procesarIdentificador($1);} | CONSTANTE{$$ = $1;} | PARIZQ expresion PARDER{$$ = $2;};

%%


int identificadorNoDeclarado(char* identificador){
  for(int i=0; i<10; i++){
    if(!(strcmp(tablaDeSimbolos[i], identificador))){
        return 0;
    }
  }
  return 1;
}

int buscarIdentificador(char* identificador){
  for(int i=0; i<10; i++){
    if(!(strcmp(tablaDeSimbolos[i], identificador))){
        return i;
    }
  }
  return -1;
}

void leerIdentificador(char* identificador){
    int valor;
    printf("Inserte un valor %s\n", identificador);
    fflush(stdin);
    scanf("%d", &valor);
    if(identificadorNoDeclarado(identificador)){
      strcpy(tablaDeSimbolos[ultimoIdentificador], identificador);
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
    errorIdentificadorNoDeclarado();
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
    errorIdentificadorNoDeclarado();
  }
}

void errorIdentificadorNoDeclarado(){
    printf("Error semantico: uno de los identificadores no fue declarado \n");
    exit(0);
}

void yyerror()
{
  printf("Error sintactico: el programa no esta estructurado correctamente");
  exit(0);
}
