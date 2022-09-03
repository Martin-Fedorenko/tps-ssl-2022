#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int enteros=0, octales=0, hexa=0, errores=0;

int main(){


    //FALTA UNA FUNCIÓN QUE PERMITA INGRESAR LA CADENA DE CARACTERES DESDE UN ARCHIVO
    //ACA PODRÍA IR UNA FUNCIÓN QUE PONGA EN 0 LOS VALORES (ENTEROS, OCTALES, HEXA, ERRORES) ANTES DE UTILIZAR EL AUTOMATA
    char cadena[100];
    printf("Ingrese una cadena de numeros enteros, octales o hexadecimales separados por un &: \n");
    scanf("%s", cadena);
    automata(cadena);
    printf("Enteros: %d\n", enteros);
    printf("Octales: %d\n", octales);
    printf("Hexadecimales: %d\n", hexa);
    printf("Errores lexicos: %d\n", errores);


    //char caracter;
    //scanf("%c", &caracter);
    //printf("Numero: %d\n", caracterAEntero("454545"));

}
//PUNTO 2?
int caracterAEntero(char cadena[]){

    int i = 0, numero = 0, potencia=0;
    while(cadena[i] != '\0'){
        potencia = pow(10, strlen(cadena)-i-1);
        numero = numero + potencia*(cadena[i]-48);
        i++;
    }
    return numero;
}

//PUNTO 1

//ESTA FUNCION VERIFICA SI UN CARACTER ES MIEMBRO DE UNA CADENA DE CARACTERES (ALFABETO)
int esCaracterDelAlfabeto(int c, char alfabeto[]){
    int i = 0, pertenece = 0;
    while(alfabeto[i] != '\0'){
        if(c == alfabeto[i]){
            pertenece = 1;
            break;
        }
        else
            i++;
    }
    return pertenece;
}
//ESTA FUNCION ASIGNA A QUE COLUMNA DE LA MATRIZ DE TRANSICIÓN DEL AUTOMATA DIRIGIRSE DEPENDIENDO QUE CARACTER HAYA INGRESADO
int columna(int c){
    if(esCaracterDelAlfabeto(c, "+-"))
        return 0;
    else if(esCaracterDelAlfabeto(c, "0"))
        return 1;
    else if(esCaracterDelAlfabeto(c, "xX"))
        return 2;
    else if(esCaracterDelAlfabeto(c, "1234567"))
        return 3;
    else if(esCaracterDelAlfabeto(c, "89"))
        return 4;
    else if(esCaracterDelAlfabeto(c, "AaBbCcDdEeFf"))
        return 5;
    else if(esCaracterDelAlfabeto(c, "&"))
        return 6;
    else
        return 7;
}
//ESTA FUNCION RECORRE LA CADENA DE CARACTERES, RECORRE EL AUTOMATA DEPENDIENDO
//QUE CARACTER SE HAYA INGRESADO Y TAMBIEN CONTABILIZA LA CANTIDAD DE NUMEROS O ERRORES LEXICOS QUE HUBO

void automata(const char *cadena){
    static int tt[8][8] = {{1,3,7,2,2,7,0,7},
                           {7,7,7,2,2,7,0,7},
                           {7,2,7,2,2,7,0,7},
			               {7,4,5,4,7,7,0,7},
			               {7,4,7,4,7,7,0,7},
			               {7,6,7,6,6,6,0,7},
			               {7,6,7,6,6,6,0,7},
			               {7,7,7,7,7,7,0,7}};
	int e=0, i=0;
    while(cadena[i] != '\0'){

    //NO OLVIDAR QUE LOS OCTALES ESTAN INCLUIDOS EN LOS ENTEROS Y LOS HEXADECIMALES
    //VALDRÁ LA PENA CAMBIAR ESTO POR UN SWITCH?
        if(cadena[i] == '&' && e == 2)
            enteros++;
        else if(cadena[i] == '&' && e == 4)
            octales++;
        else if(cadena[i] == '&' && e == 6)
            hexa++;
        else if(cadena[i] == '&' && e == 7)
            errores++;

        e=tt[e][columna(cadena[i])];
        i++;
    }

    //PUEDE IR UN SWITCH
        if(e == 2)
            enteros++;
        else if(e == 3)
            enteros++;
        else if(e == 4)
            octales++;
        else if(e == 6)
            hexa++;
        else if(e == 7)
            errores++;
}
