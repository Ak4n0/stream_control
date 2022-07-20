/*
    Caracteres de control:
    @ -> Elimina la última palabra
    , -> Elimina el último carácter
    ! -> Elimina todos los caracteres introducidos
    . -> Termina el programa
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 50

struct nodo {
    char simbolo;
    struct nodo *sig;
} *raiz = NULL;

void insertar(char x) {
    struct nodo *nuevo;
    
	nuevo = malloc(sizeof(struct nodo));
    nuevo->simbolo = x;
    nuevo->sig = raiz;
    raiz = nuevo;
}

char extraer() {
	char informacion = -1;
	struct nodo *bor = raiz;
    
	if (raiz) {
        informacion = raiz->simbolo;
        raiz = raiz->sig;
        free(bor);   
    }
	
	return informacion;
}

void liberar() {
    struct nodo *bor;

    while(raiz) {
        bor = raiz;
        raiz = raiz->sig;
        free(bor);
    }
}

int vacia() {
	return raiz? 0 : 1;
}

void cargarCadena(char *cadena) {
    printf("Ingrese la cadena: ");
    fgets(cadena, MAX, stdin);
}

void imprimir_cadena_pila_auxiliar(struct nodo *n) {
	if(n) {
		imprimir_cadena_pila_auxiliar(n->sig);
		putchar(n->simbolo);
	}
}

void imprimir_cadena_pila() {
	imprimir_cadena_pila_auxiliar(raiz);
}

int verificarCaracteres(char *cadena) {
    for (size_t i=0, iterar=1; iterar && i<strlen(cadena); i++) {
		switch(cadena[i]) {
		case '@': // elimina la ultima palabra
			;
			char c = extraer();
			while(c != ' ' && c != -1)
				c = extraer();
			if(c == ' ')
				insertar(' ');
			break;
		case ',': // elimina el ultimo caracter
			if(!vacia())
				extraer();
			break;
		case '!': // elimina todos los caracteres introducidos
			liberar();
			break;
		case '.': // termina el programa
			iterar = 0;
			break;
		default: // introducir el caracter en la pila
			insertar(cadena[i]);
		}
		imprimir_cadena_pila();
		puts("");
    }
    
	return !vacia();
}


int main() {
    char cadena[MAX];

    cargarCadena(cadena);
    if (verificarCaracteres(cadena)) {
        printf("Proceso finalizado con éxito");
    } else {
        printf("La cadena esta vacia");
    }
    liberar();
}
