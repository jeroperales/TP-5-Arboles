#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// ESTRUCTURAS
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

typedef struct nodo
{
    persona dato;
    struct nodo* sig;
} nodo;


// PROTOTIPADO
//FUNCIONES ARBOLES
nodoArbol* inicArbol();
nodoArbol* crearNodoArbol(persona dato);
nodoArbol* insertar(nodoArbol* arbol, persona dato);
nodoArbol* buscaLegajo(nodoArbol* arbol, int legajo, nodoArbol* aux);
nodoArbol* buscaNombre(nodoArbol* arbol, char nombre[], nodoArbol* aux);
int contarTerminal(nodoArbol* arbol);
int contarGrado1(nodoArbol* arbol);
int buscar(nodoArbol* arbol, int edad);
int calculaAltura(nodoArbol* arbol);

//FUNCIONES LISTA
nodo* inicLista();
nodo* crearNodo(persona dato);
nodo* agregarPpio(nodo* lista, nodo* nuevo);
nodo* agregarFinal(nodo* lista, nodo* nuevo);
nodo* pasarALista(nodoArbol* arbol, nodo* lista);


persona crearPersona();
void mostrarPersona(persona personita);
void mostrarArbolInOrder(nodoArbol* arbol);
void mostrarArbolPreOrder(nodoArbol* arbol);
void mostrarArbolPostOrder(nodoArbol* arbol);
void mostrarLista(nodo* lista);


int main()
{
    int terminales = 0;
    int i = 0;
    int grado1 = 0;
    int flag = 0;
    int edad = 0;
    int legajo = 0;
    int altura = 0;
    char opc = 's';
    char nombre[20];
    nodoArbol* arbol = inicArbol();
    nodoArbol* aux = inicArbol();
    nodoArbol* aux2 = inicArbol();
    nodo* lista = inicLista();
    persona personita;

    while (opc == 's')
    {
        personita = crearPersona();
        arbol = insertar(arbol, personita);

        printf("INGRESE s SI DESEA CONTINUAR \n");
        fflush(stdin);
        scanf("%c", &opc);
    }

    //PUNTO 2 CONTAR NODOS DE GRADOS 1
    mostrarArbolInOrder(arbol);


    /*
        grado1 = contarGrado1(arbol);
        printf("\n\nNODOS GRADO 1: | %i |", grado1);

        printf("\n\nINGRESE EDAD A BUSCAR\n");
        scanf("%i", &edad);

        flag = buscar(arbol, edad);
        printf("\nFLAG = %d", flag);*/

    //PUNTO 3 PASAR DE ARBOL A LISTA SIMPLE
    lista = pasarALista(arbol, lista);
    printf("LISTA SIMPLE: \n");
    mostrarLista(lista);

    //PUNTO 4 BUSCAR LEGAJO DENTRO DE ARBOL
    printf("INGRESE LEGAJO A BUSCAR \n");
    scanf("%i", &legajo);
    aux = buscaLegajo(arbol, legajo, aux);

    if(aux != NULL)
    {
        printf("\nNODO DE DICHO LEGAJO: \n");
        mostrarPersona(aux->dato);
    }
    else
    {

        printf("DICHO LEGAJO NO SE ENCUENTRA DENTRO DEL ARBOL\n");
    }

    //PUNTO 5 BUSCAR NOMBRE DENTRO DE ARBOL
    printf("INGRESE NOMBRE A BUSCAR \n");
    fflush(stdin);
    gets(nombre);

    aux2 = buscaNombre(arbol, nombre, aux2);
    if (aux2 != NULL)
    {
        printf("\nNODO DE DICHO NOMBRE: \n");
        mostrarPersona(aux2->dato);
    }
    else
    {
        printf("DICHO NOMBRE NO SE ENCUENTRA DENTRO DEL ARBOL\n");
    }


    //PUNTO 6 CALCULAR ALTURA DE ARBOL
    altura = calculaAltura(arbol);
    printf("\n\nALTURA: %i", altura);


    //PUNTO 7 CONTAR CANTIDAD DE NODOS
    i = contarNodo(arbol, i);
    printf("\nCANTIDAD DE NODOS EN ARBOL: %i\n", i);

    // PUNTO 8 CONTAR TERMINALES
    /*terminales = contarTerminal(arbol);
    printf("\n\nTERMINALES: | %i |", terminales);*/

    //PUNTO 9 BORRAR NODO DE ARBOL
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
    printf("INGRESE NOMBRE: \n");
    fflush(stdin);
    gets(aux.nombre);

    printf("INGRESE EDAD: \n");
    scanf("%i", &aux.edad);

    printf("INGRESE LEGAJO: \n");
    scanf("%i", &aux.legajo);

    return aux;
}

void mostrarArbolInOrder(nodoArbol* arbol)
{
    if (arbol != NULL)
    {
        mostrarArbolInOrder(arbol->izq);
        mostrarPersona(arbol->dato);
        mostrarArbolInOrder(arbol->der);
    }
}

void mostrarArbolPreOrder(nodoArbol* arbol)
{
    if (arbol != NULL)
    {
        mostrarPersona(arbol->dato);
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
        mostrarPersona(arbol->dato);
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

nodo* inicLista()
{
    return NULL;
}

nodo* crearNodo(persona dato)
{
    nodo* nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->sig = NULL;
    return nuevo;
}

nodo* agregarPpio(nodo* lista, nodo* nuevo)
{
    if(lista)
    {
        nuevo->sig = lista;
    }
    lista = nuevo;
    return lista;
}

nodo* agregarFinal(nodo* lista, nodo* nuevo)
{
    nodo* aux = lista;
    if(aux)
    {
        while(aux->sig)
        {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
    else
    {
        lista = nuevo;
    }

    return lista;
}

nodo* pasarALista(nodoArbol* arbol, nodo* lista)
{
    nodo* nodoAux;
    nodoArbol* aux = arbol;
    if(aux)
    {
        lista = pasarALista(aux->izq, lista);
        nodoAux = crearNodo(arbol->dato);
        lista = agregarFinal(lista, nodoAux);
        lista = pasarALista(aux->der, lista);
    }
    return lista;
}

void mostrarLista(nodo* lista)
{
    printf("\n");
    while(lista)
    {
        printf("| %d |",lista->dato.edad);
        if(lista->sig)
        {
            printf(" -> ");
        }
        lista = lista->sig;
    }
    printf("\n");
}

void mostrarPersona(persona personita)
{
    printf("NOMBRE: %s\n", personita.nombre);
    printf("EDAD: %i\n", personita.edad);
    printf("LEGAJO: %i\n\n", personita.legajo);

}

nodoArbol* buscaLegajo(nodoArbol* arbol, int legajo, nodoArbol* aux)
{
    if(arbol)
    {
        aux = buscaLegajo(arbol->izq, legajo, aux);
        aux = buscaLegajo(arbol->der, legajo, aux);

        if (arbol->dato.legajo == legajo)
        {
            aux = arbol;
        }
    }
    return aux;
}

nodoArbol* buscaNombre(nodoArbol* arbol, char nombre[], nodoArbol* aux)
{
    if(arbol)
    {
        aux = buscaNombre(arbol->izq, nombre, aux);
        aux = buscaNombre(arbol->der, nombre, aux);

        if(strcmp(nombre, arbol->dato.nombre) == 0)
        {
            aux = arbol;
        }
    }

    return aux;
}

int contarNodo(nodoArbol* arbol, int i)
{
    if (arbol != NULL)
    {
        i++;
        i = contarNodo(arbol->izq, i);
        i = contarNodo(arbol->der, i);
    }
    return i;
}

int calculaAltura(nodoArbol* arbol)
{
    int i = 0;
    int alturaIzq = 0;
    int alturaDer = 0;
    if(arbol)
    {
        i++;
        if(arbol->izq)
        {
            alturaIzq += calculaAltura(arbol->izq);
        }
        if(arbol->der)
        {
            alturaDer += calculaAltura(arbol->der);
        }
        if(alturaDer < alturaIzq)
        {
            i += alturaIzq;
        }
        else
        {
            i += alturaDer;
        }
    }
    return i;
}

