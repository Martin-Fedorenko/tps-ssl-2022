#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int enteros=0, octales=0, hexa=0, errores=0;

typedef struct tnodo{
   int numero;
   char operador;
   struct tnodo* sig;
}nodo;

typedef nodo* ptrNodo;

//PUNTO 1
//Esta función se encarga de analizar si un caracter pertenece a un alfabeto determinado.
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
};

//Esta función se encarga de devolver a que estado va a dirigirse el automata1
//dependiendo de que caracter fue consumido por el automata1.
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
};

//Este procedimiento analiza una cadena de caracteres conformada por distintos numeros separados por "&",
//determinando y contabilizando si se trata de un número entero con o sin signo, octale,
//hexadecimal o un error léxico.
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
    return;
};

//PUNTO 2
//Esta función toma como parámetro una cadena de caracteres
//que posee un numero entero positivo y lo transforma en un numero entero de tipo int.
int caracterAEntero(char cadena[]){
    int i = 0, numero = 0, potencia=0;
    while(cadena[i]){
        potencia = pow(10, strlen(cadena)-i-1);
        numero = numero + potencia*(cadena[i]-48);
        i++;
    }
    return numero;
};

//PUNTO 3
//Esta función devuelve la cantidad de numeros del vector de números.
int cargarOperandos(char *cadena,int numeros[]){
	char cadenaAuxiliar[100];
	int contCadena = 0;
	int contNumeros = 0;
	int i = 0;
    while(cadena[i]){
    	if(cadena[i] != '&'){
    		cadenaAuxiliar[contCadena]=cadena[i];
    		contCadena++;
		}
		else{
			//como el ultimo numero es seguido por un & no tenemos problema
        	numeros[contNumeros] = caracterAEntero(cadenaAuxiliar);
        	contNumeros++;
        	//reseteamos el vector de cad auxiliar que vamos casteando y el contador del vector
        	memset(cadenaAuxiliar, 0, 100);
        	contCadena = 0;
		}
        i++;
    }
    return contNumeros;
};

void recorrerOperacion(char a[],char b[], char c[]){
	int i =0;

	int iteradorOp =0;
	for(i; a[i];i++){
		b[i]=a[i];
		if(a[i]=='+' || a[i]=='-' || a[i]=='*'){
			b[i]='&';
			c[iteradorOp] = a[i];
			iteradorOp++;
		}
	}
	b[i++] = '&';
	return;
};

int resolverOperacion(int a, int b, char operacion){
	if(operacion == '*')
		return a*b;
	if(operacion == '+')
		return a+b;
	if(operacion == '-')
		return a-b;
};

void agregarALista(ptrNodo* lista, int num, char op) {
    ptrNodo nuevo=(ptrNodo)malloc(sizeof(nodo));
    nuevo->numero=num;
    nuevo->operador=op;
    nuevo->sig= NULL;

    if(*lista == NULL){
        *lista = nuevo;
    }
    else{
   	   //la lista no está vacia
        ptrNodo aux=(ptrNodo)malloc(sizeof(nodo));
        aux = *lista;
        while( aux->sig !=NULL){
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
    return;
};

void mostrarLista(ptrNodo* lista){
	if(lista != NULL){
		ptrNodo aux = (ptrNodo)malloc(sizeof(nodo));
		aux = *lista;
		while(aux != NULL){
			printf("%d", aux->numero);
			printf("%c", aux->operador);
			aux = aux->sig;
		}
	}
	return;
};

ptrNodo* resolverMultiplicaciones(ptrNodo* lista){
	ptrNodo aux = (ptrNodo)malloc(sizeof(nodo));
	aux = *lista;
	while(aux != NULL){
		if(aux->operador == '*'){
			if(aux == *lista){//si el primero tiene suma
				aux->sig->numero = resolverOperacion(aux->numero,aux->sig->numero,aux->operador);
				return (*lista);
			}
			else{
				aux->sig->numero = resolverOperacion(aux->numero,aux->sig->numero,aux->operador);
				return aux;
			}
		}
		aux = aux->sig;
	}
};

ptrNodo* resolverSumRes(ptrNodo* lista){
	ptrNodo aux = (ptrNodo)malloc(sizeof(nodo));
	aux = *lista;
	while(aux->sig != NULL){
		if(aux->operador == '+'){
			if(aux == *lista){//si el primero tiene suma
				aux->sig->numero = resolverOperacion(aux->numero,aux->sig->numero,aux->operador);
				return (*lista);
			}
			else{
				aux->sig->numero = resolverOperacion(aux->numero,aux->sig->numero,aux->operador);
				return aux;
			}
		}
		if(aux->operador == '-'){
			if(aux == *lista){//si el primero tiene suma
				aux->sig->numero = resolverOperacion(aux->numero,aux->sig->numero,aux->operador);
				return (*lista);
			}
			else{
				aux->sig->numero = resolverOperacion(aux->numero,aux->sig->numero,aux->operador);
				return aux;
			}
		}

		aux = aux->sig;
	}
};

void borrarEnlazar(ptrNodo* lista,ptrNodo nodo){
	ptrNodo aux = (ptrNodo)malloc(sizeof(nodo));
	aux = *lista;
	if(nodo == *lista){
		*lista=(*lista)->sig;
		free(nodo);
	}
	else{
		while(aux->sig != nodo){
			aux = aux->sig;
		}
		aux->sig = nodo->sig;
		nodo->sig = NULL;
		free(nodo);
	}
	return;
};

//Esta función se encarga de devolver a que estado va a dirigirse el automata2
//dependiendo de que caracter fue consumido por el automata2.
int columnaAutomata2(int c){
    if(esCaracterDelAlfabeto(c, "0123456789"))
        return 0;
    else if(esCaracterDelAlfabeto(c, "+-*"))
        return 1;
    else
        return 2;
};

//Esta función analiza si una "palabra" (cadena de caracteres) pertenece o no al lenguaje conformado por:
//aquellas ecuaciones aritméticas conformadas por numeros enteros positivos, sumas, restas y multipliaciones.
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

//Este procedimiento permite ingresar una cadena de caracteres tanto por medio de un archivo como por medio de la consola.
void ingresarCadena(char *cadena){
    char modo;
    while(modo!= '1' && modo!= '2'){
        printf("Ingrese '1' para obtener la cadena de caracteres por archivo o '2' para obtenerla por consola \n");
        scanf("%c", &modo);
        if(modo == '1')
            ingresarPorArchivo(cadena);
        else if(modo == '2')
            ingresarPorConsola(cadena);
        fflush(stdin);
    }
    return;
};

void ingresarPorConsola(char *cadena){
    char cadenaAux[100];
    printf("Ingrese la cadena de caracteres para realizar la operacion seleccionada: \n");
    scanf("%s", cadenaAux);
    strcpy(cadena,cadenaAux);
	return;
};

void ingresarPorArchivo(char *cadena){
    char nombreArchivo[20];
    printf("Ingrese el nombre del archivo:\n");
    scanf("%s", nombreArchivo);

    FILE *f;
    long fileSize;
    char *buffer;

    f = fopen ( nombreArchivo , "rb" );

    //Busca el tamaño del archivo
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
    return;
}

int main(){
	char operacion[100]= {};
	char operandos[100];
	char vOperaciones[100];

	int cantNumerosOp = 0;
	int numerosCasteados[100];

	int i = 0;//para recorrer operaciones y cargar lista
	int q = 0;//para recorrer operandos y cargar lista

    char modo;
    while(modo!= '1' && modo!= '2' && modo!= '3'){

        printf("Ingrese '1' para reconocer tipos numericos de una cadena de numeros enteros, octales o hexadecimales, \n");
        printf("Ingrese '2' para transformar caracteres numericos de tipo char a tipo int, \n");
        printf("Ingrese '3' para resolver una ecuacion aritmetica con sumas, restas y multipliaciones: \n");
        scanf("%c", &modo);

        switch(modo){
            case '1':
                fflush(stdin);
                ingresarCadena(operacion);
                automata1(operacion);
                printf("Se registraron: \n", enteros);
                printf("\t%d numeros enteros \n", enteros);
                printf("\t%d numeros octales \n", octales);
                printf("\t%d hexadecimales \n", hexa);
                printf("\t%d errores lexicos \n", errores);
                break;
            case '2':
                fflush(stdin);
                ingresarCadena(operacion);
                printf("El numero es: %d", caracterAEntero(operacion));
                break;
            case '3':
                fflush(stdin);
                ingresarCadena(operacion);

                if(automata2(operacion)){

                    recorrerOperacion(operacion,operandos,vOperaciones);
                    cantNumerosOp = cargarOperandos(operandos,numerosCasteados);

                    ptrNodo lista = NULL;
                    //CARGAMOS LA LISTA con los vectores de op y operandos
                    for(q;q<cantNumerosOp;q++){
                        agregarALista(&lista,numerosCasteados[q],vOperaciones[i]);
                        i++;
                    }
                    int a = 0;//para analizar cuantas operaciones hay que realizar
                    //Resolvemos primero todas las multiplicaciones
                    for(a;a<i;a++){
                        if(vOperaciones[a]=='*')
                            borrarEnlazar(&lista,resolverMultiplicaciones(&lista));
                    }
                    //y luego las sumas y restas
                    a=0;
                    for(a;a<i;a++){
                        if(vOperaciones[a]=='+' || vOperaciones[a]=='-')
                            borrarEnlazar(&lista,resolverSumRes(&lista));
                    }
                    printf("El resultado de la operacion ingresada es: ");
                    mostrarLista(&lista);//muestra el resultado

                }else{
                    printf("La operacion escrita posee errores sintacticos y no puede resolverse. \n");
                }
                break;
        }
        fflush(stdin);
    }
	return 0;
}


