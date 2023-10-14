#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// ESTRUCTURA
typedef struct
{
    int legajo;
    char nombre[20];
    int edad;
} persona;

typedef struct nodoArbol
{
    persona dato;
    struct nodoArbol* izq;
    struct nodoArbol* der;
} nodoArbol;

// PROTOTYPES
nodoArbol* inicArbol();
nodoArbol* crearNodoArbol(persona dato);
nodoArbol* insertar(nodoArbol* arbol, persona dato);
persona crearPersona();
void mostrarArbolInOrder(nodoArbol* arbol);
void mostrarArbolPreOrder(nodoArbol* arbol);
void mostrarArbolPostOrder(nodoArbol* arbol);
int contarTerminal(nodoArbol* arbol);
int contarGrado1(nodoArbol* arbol);
int buscar(nodoArbol* arbol, int edad);

int main()
{
    int terminales = 0;
    int grado1 = 0;
    int flag = 0;
    int edad = 0;
    char opc = 's';
    nodoArbol* arbol = inicArbol();
    nodoArbol* nodo;
    persona personita;

    while (opc == 's')
    {
        personita = crearPersona();
        arbol = insertar(arbol, personita);

        printf("INGRESE s SI DESEA CONTINUAR \n");
        fflush(stdin);
        scanf("%c", &opc);
    }

    mostrarArbolInOrder(arbol);

    terminales = contarTerminal(arbol);
    printf("\n\nTERMINALES: | %i |", terminales);

    grado1 = contarGrado1(arbol);
    printf("\n\nNODOS GRADO 1: | %i |");

    printf("\n\nINGRESE EDAD A BUSCAR\n");
    scanf("%i", &edad);

    flag = buscar(arbol, edad);
    printf("\nFLAG = %d", flag);

    return 0;
}

nodoArbol* inicArbol()
{
    return NULL;
}

nodoArbol* crearNodoArbol(persona dato)
{
    nodoArbol* aux = (nodoArbol*)malloc(sizeof(nodoArbol));
    aux->dato = dato;
    aux->izq = NULL;
    aux->der = NULL;
    return aux;
}

nodoArbol* insertar(nodoArbol* arbol, persona dato)
{
    if (arbol != NULL)
    {
        if (dato.edad < arbol->dato.edad)
        {
            arbol->izq = insertar(arbol->izq, dato);
        }
        else
        {
            arbol->der = insertar(arbol->der, dato);
        }
    }
    else
    {
        arbol = crearNodoArbol(dato);
    }
    return arbol;
}

persona crearPersona()
{
    persona aux;
    printf("INGRESE EDAD: \n");
    fflush(stdin);
    scanf("%i", &aux.edad);
    return aux;
}

void mostrarArbolInOrder(nodoArbol* arbol)
{
    if (arbol != NULL)
    {
        mostrarArbolInOrder(arbol->izq);
        printf("| %i |", arbol->dato.edad);
        mostrarArbolInOrder(arbol->der);
    }
}

void mostrarArbolPreOrder(nodoArbol* arbol)
{
    if (arbol != NULL)
    {
        printf("| %i |", arbol->dato.edad);
        mostrarArbolPreOrder(arbol->izq);
        mostrarArbolPreOrder(arbol->der);
    }
}

void mostrarArbolPostOrder(nodoArbol* arbol)
{
    if (arbol != NULL)
    {
        mostrarArbolPostOrder(arbol->izq);
        mostrarArbolPostOrder(arbol->der);
        printf("| %i |", arbol->dato.edad);
    }
}

int contarTerminal(nodoArbol* arbol)
{
    int i = 0;
    if (arbol != NULL)
    {
        i = i + contarTerminal(arbol->izq);
        i = i + contarTerminal(arbol->der);
        if (arbol->der == NULL && arbol->izq == NULL)
        {
            i = i + 1;
        }
    }
    return i;
}

int contarGrado1(nodoArbol* arbol)
{
    int i = 0;
    if (arbol != NULL)
    {
        i = i + contarGrado1(arbol->izq);
        i = i + contarGrado1(arbol->der);
        if ((arbol->izq == NULL) ^ (arbol->der == NULL))
        {
            i++;
        }
    }
    return i;
}

int buscar(nodoArbol* arbol, int edad)
{
    int i = 0;
    if (arbol != NULL)
    {
        if (arbol->dato.edad == edad)
        {
            return 1;
        }
        else
        {
            i = buscar(arbol->der, edad) + buscar(arbol->izq, edad);
        }
    }
    return i;
}
