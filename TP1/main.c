#include <stdio.h>
#include <stdlib.h>

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

}

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
    else if(esCaracterDelAlfabeto(c, "1234567"))
        return 2;
    else if(esCaracterDelAlfabeto(c, "89"))
        return 3;
    else if(esCaracterDelAlfabeto(c, "AaBbCcDdEeFf"))
        return 4;
    else if(esCaracterDelAlfabeto(c, "&"))
        return 5;
    else
        return 6;
}
//ESTA FUNCION RECORRE LA CADENA DE CARACTERES, RECORRE EL AUTOMATA DEPENDIENDO
//QUE CARACTER SE HAYA INGRESADO Y TAMBIEN CONTABILIZA LA CANTIDAD DE NUMEROS O ERRORES LEXICOS QUE HUBO

int automata(const char *cadena){
    static int tt[7][6] = {{1,6,2,4,5,0,6},
                           {6,3,3,3,6,0,6},
			               {6,2,2,4,5,0,6},
			               {6,3,3,3,6,0,6},
			               {6,4,4,4,5,0,6},
			               {6,5,5,5,5,0,6},
			               {6,6,6,6,6,0,6}};
	int e=0, i=0;
    while(cadena[i] != '\0'){

    //NO OLVIDAR QUE LOS OCTALES ESTAN INCLUIDOS EN LOS ENTEROS Y LOS HEXADECIMALES
    //VALDRÁ LA PENA CAMBIAR ESTO POR UN SWITCH?
        if(cadena[i] == '&' && e == 2){
            octales++;
            enteros++;
            hexa++;
        }
        else if(cadena[i] == '&' && e == 3)
            enteros++;
        else if(cadena[i] == '&' && e == 4){
            enteros++;
            hexa++;
        }
        else if(cadena[i] == '&' && e == 5)
            hexa++;
        else if(cadena[i] == '&' && e == 6)
            errores++;

        e=tt[e][columna(cadena[i])];
        i++;
    }

    //PUEDE IR UN SWITCH
    if(e == 2){
        octales++;
        enteros++;
        hexa++;
    }
    else if(e == 3)
        enteros++;
    else if(e == 4){
        enteros++;
        hexa++;
    }
    else if(e == 5)
        hexa++;
    else if(e == 6)
        errores++;
}

