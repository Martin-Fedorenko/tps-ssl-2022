%{
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "y.tab.h"
int i = 0;

#ifndef yywrap
static int yywrap(void) { return 1;}
#endif

void verificarTamanio(char* identificador);

%}

DIGITO [0-9]
LETRA [a-zA-Z]
IDENTIFICADOR {LETRA}({LETRA}|{DIGITO})*
CONSTANTE {DIGITO}({DIGITO})*
ESPACIOS [ \t\n]+ 

%%



"inicio"        {return (INICIO);}
"fin"           {return (FIN);}
"leer"          {return (LEER);}
"escribir"      {return (ESCRIBIR);}
{IDENTIFICADOR} {yylval.nombre = yytext; verificarTamanio(yylval.nombre);  return (IDENTIFICADOR);}
{CONSTANTE}     {yylval.num=atoi(yytext); return (CONSTANTE);};
":="            {return (ASIGNACION);}
"+"             {return (MAS);}
"-"             {return (MENOS);}
"("             {return (PARIZQ);}
")"             {return (PARDER);}
","             {return (COMA);}
";"             {return (PCOMA);}
{ESPACIOS}      ;

.               {printf("Error lexico: %s es un caracter invalido\n", yytext); exit(0);};

%%

void verificarTamanio(char* identificador){
    if(strlen(identificador) > 32){
        printf("Error lexico: %s supera los 32 caracteres permitidos \n", identificador); 
        exit(0);
    }
}
