#include <stdio.h>
#include <stdlib.h>

//ESTRUCTURA
typedef struct
{
    int legajo;
    char nombre[20];
    int edad;
} persona;

typedef struct nodoArbol
{
    persona dato;
    struct nodoArbol * izq;
    struct nodoArbol * der;
} nodoArbol;


//PROTOTIPADO
nodoArbol* inicArbol();
nodoArbol* crearNodoArbol(persona dato);
nodoArbol* insertar(nodoArbol* arbol, persona dato);
persona crearPersona ();
void mostrarArbol (nodoArbol* arbol);


int main()
{
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

    mostrarArbol(arbol);
    return 0;
}

nodoArbol* inicArbol()
{
    return NULL;
}

nodoArbol* crearNodoArbol(persona dato)
{
    nodoArbol* aux = malloc(sizeof(nodoArbol));
    aux->dato;
    aux->izq = NULL;
    aux->der = NULL;

    return aux;
}

nodoArbol* insertar(nodoArbol* arbol, persona dato) //ORDENADO POR EDAD
{
    if (arbol != NULL)
    {
        if(dato.edad < arbol->dato.edad)
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

persona crearPersona ()
{
    persona aux;

    printf("INGRESE NOMBRE: \n");
    fflush(stdin);
    gets(aux.nombre);
    printf("INGRESE EDAD: \n");
    fflush(stdin);
    scanf("%i", &aux.edad);
    printf("INGRESE LEGAJO:\n");
    scanf("%i", &aux.legajo);

    return aux;
}

void mostrarArbol (nodoArbol* arbol)
{
    if (arbol != NULL)
    {

        printf("%i", arbol->dato.edad);
        mostrarArbol(arbol->izq);
        printf("%i", arbol->dato.edad);

    }
}
