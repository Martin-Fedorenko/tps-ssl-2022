#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int enteros=0, octales=0, hexa=0, errores=0;

void ingresarCadena(char *cadena){
    printf("Ingrese 'a' para leer un archivo o 'c' para ingresar una cadena por consola \n");
    char modo;
    scanf("%c", &modo);
    if(modo == 'a')
        ingresarPorArchivo(cadena);
    else if(modo == 'c')
        ingresarPorConsola(cadena);
}

void ingresarPorConsola(char *cadena){
    char cadenaAux[100];
    printf("Ingrese una cadena: \n");
    scanf("%s", cadenaAux);
    strcpy(cadena,cadenaAux);
}

void ingresarPorArchivo(char *cadena){
    char nombreArchivo[20];
    printf("Ingrese el nombre del archivo \n");
    scanf("%s", nombreArchivo);

    FILE *f;
    long fileSize;
    char *buffer;

    f = fopen ( nombreArchivo , "rb" );

    //Busca el tamanio del archivo
    fseek( f , 0L , SEEK_END);
    fileSize = ftell( f );
    rewind( f );

    //Asigna memoria
    buffer = calloc( 1, fileSize+1 );

    //Lee el archivo
    fread( buffer , fileSize, 1 , f);

    fclose(f);
    strcpy(cadena,buffer);
    free(buffer);
}

//PUNTO 2
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
//ESTA FUNCION ASIGNA A QUE COLUMNA DE LA MATRIZ DE TRANSICIÓN EL AUTOMATA DIRIGIRSE DEPENDIENDO QUE CARACTER HAYA INGRESADO
int columnaAutomata1(int c){
    if(esCaracterDelAlfabeto(c, "+-"))
        return 0;
    else if(esCaracterDelAlfabeto(c, "0"))
        return 1;
    else if(esCaracterDelAlfabeto(c, "x"))
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

int columnaAutomata2(int c){
    if(esCaracterDelAlfabeto(c, "0123456789"))
        return 0;
    else if(esCaracterDelAlfabeto(c, "+-*"))
        return 1;
    else
        return 2;
}
//ESTA FUNCION RECORRE LA CADENA DE CARACTERES, RECORRE EL AUTOMATA DEPENDIENDO
//QUE CARACTER SE HAYA INGRESADO Y TAMBIEN CONTABILIZA LA CANTIDAD DE NUMEROS O ERRORES LEXICOS QUE HUBO

void automata1(const char *cadena){
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

        if(cadena[i] == '&')
            switch(e) {
                case 2:
                    enteros++;
                    break;
                case 4:
                    octales++;
                    break;
                case 6:
                    hexa++;
                    break;
                default:
                    errores++;
            }

        e=tt[e][columnaAutomata1(cadena[i])];
        i++;
    }
        switch(e){
            case 2:
                enteros++;
                break;
            case 3:
                enteros++;
                break;
            case 4:
                octales++;
                break;
            case 6:
                hexa++;
                break;
            default:
                errores++;
        }
}

int automata2(const char *cadena){
    static int tt[5][3] = {{1,4,4},
                           {1,2,4},
                           {3,4,4},
                           {3,0,4},
                           {4,4,4}};
	int e=0, i=0;
    while(cadena[i] != '\0'){
        e=tt[e][columnaAutomata2(cadena[i])];
        i++;
    }
    if(e==4)
        return 0;
    else
        return 1;
};

struct lista {
    int caracter;
    struct lista* sig;
    struct lista* ant;
};

void muestraLista ( struct lista *lista ) {
    while(lista){
        printf("%d\n", lista->caracter);
        lista = lista->sig;
    }
};

void agregarNodoAlFinal(struct lista **lista, int valor){
    struct lista* nodoNuevo;
    struct lista* aux = *lista;
    nodoNuevo = (struct lista*)malloc(sizeof(struct lista));
    nodoNuevo->caracter = valor;

    if(aux){
        while(aux->sig)
            aux = aux->sig;
        nodoNuevo->sig = NULL;
        aux->sig = nodoNuevo;
        nodoNuevo->ant = aux;
    }
    else{
        nodoNuevo->sig = NULL;
        nodoNuevo->ant = NULL;
        *lista=nodoNuevo;
    }
    return;
};

void deCadenaALista(char cadena[], struct lista **lista){
    int i = 0;
    struct lista* aux = *lista;
    while(cadena[i] != '\0'){
        agregarNodoAlFinal(&*lista, cadena[i]);
        i++;
    }
    return;
};

void eliminarNodo(struct lista** lista, struct lista* nodoAEliminar)
{
    if (*lista == nodoAEliminar)
        *lista = nodoAEliminar->sig;

    if (nodoAEliminar->sig != NULL)
        nodoAEliminar->sig->ant = nodoAEliminar->ant;

    if (nodoAEliminar->ant != NULL)
        nodoAEliminar->ant->sig = nodoAEliminar->sig;

    free(nodoAEliminar);
    return;
}

void unificar(struct lista **lista){
    struct lista* aux = *lista;
    int i = 0, numero = 0, potencia = 0;
    while(aux->sig)
        aux = aux->sig;

    while(aux){
        if(aux->caracter == '*' || aux->caracter == '+' || aux->caracter == '-'){
            i =0;
            numero = 0;
            potencia = 0;
            aux = aux->ant;
        }
        potencia = pow(10, i);
        numero = numero + potencia * (aux->caracter-48);
        aux->caracter = numero;
        i++;
        if(aux->ant != NULL && aux->ant->caracter!='*' && aux->ant->caracter!='+' && aux->ant->caracter!='-')
            eliminarNodo(&*lista, aux);

        aux = aux->ant;
    }
}

void operar(struct lista **lista, int (*f)(int, int), char operacion){
    struct lista *aux = *lista;
    int a, b;
        while(aux->sig){
            if(aux->caracter == operacion){
                a = aux->ant->caracter;
                b = aux->sig->caracter;
                aux->caracter = f(a,b);
                eliminarNodo(&*lista, aux->ant);
                eliminarNodo(&*lista, aux->sig);
            }
                if(aux->sig == NULL)
                    break;
                else
                    aux = aux->sig;
    }
};

int suma(int x, int y) {
    return x + y;
}
int resta(int x, int y) {
    return x - y;
}
int multiplica(int x, int y) {
    return x * y;
}

/*int main(){ //Programa que implementa automatas para saber la cantidad de numeros o errores lexicos que hay en una expresion
    char cadena[100];
    ingresarCadena(cadena);
    automata1(cadena);
    printf("Enteros: %d\n", enteros);
    printf("Octales: %d\n", octales);
    printf("Hexadecimales: %d\n", hexa);
    printf("Errores lexicos: %d\n", errores);
};*/

int main(){ //Programa que implementa automatas y listas doblemente enlazadas para calcular una operacion matematica o detectar los posibles errores sintacticos que posea la operacion
    struct lista* lista = NULL;
    char cadena[100];
    ingresarPorConsola(cadena);
    if(automata2(cadena)){
        deCadenaALista(cadena, &lista);
        unificar(&lista);
        operar(&lista, multiplica,'*');
        operar(&lista, resta, '-');
        operar(&lista, suma, '+');
        printf("El resultado es: ");
        muestraLista(lista);
    }else{
        printf("La operacion es sintacticamente incorrecta \n");
    }

    system("PAUSE");
    return 0;
};
