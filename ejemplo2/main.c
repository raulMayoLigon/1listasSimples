#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct tipoInfo {
    int key;
    double value;
};

struct tipoNodo {
    struct tipoInfo informacion;
    struct tipoNodo *siguiente;
};

void anadirNodo(struct tipoNodo **primero);
void visualizar(struct tipoNodo *primero);
int contarNodos(struct tipoNodo *primero);
void anadirAlFinal(struct tipoNodo **primero);
struct tipoNodo * buscarEnUnaLista(struct tipoNodo *primero, int key);
void modificarNodo(struct tipoNodo **primero);
void eliminarNodo(struct tipoNodo **primero);

void insertarOrdenado(struct tipoNodo **primero);
void eliminarLista(struct tipoNodo **primero);
struct tipoNodo * buscarOrdenadoxClave(struct tipoNodo **primero, int keyBuscar);

int main(void) {
    
    struct tipoNodo *primeroMain = NULL; //lista vacía
    
    int clave;
    int option;
    int buscado, key;
    
    
    printf("\n===========MENÚ===========\n");
    printf("\t-1.Añadir un nodo.\n");
    printf("\t-2.Visualizar Lista.\n");
    printf("\t-3.Ver Nº de nodos.\n");
    printf("\t-4.Añadir un nodo al final.\n");
    printf("\t-5.Buscar un nodo.\n");
    printf("\t-6.Modificar un nodo.\n");
    printf("\t-7.Eliminar un nodo.\n");
    printf("\t-8.Eliminar todos los nodos.\n");
    printf("\t-0.Salir\n");
    printf("=============================\n");
    
    do {

        printf("Introduce una opción: "); scanf("%d", &option);
        switch (option) {
            case 1:
                //A: Añadir un nodo al principio de la lista.
                anadirNodo(&primeroMain);
                printf("\n");
                break;
                
            case 2:
                //B: Visualizar la información de la lista.
                visualizar(primeroMain);
                printf("\n");
                break;
                
            case 3:
                //C: Obtener el número de nodos que hay en la lista.
                printf("Nº de nodos: %d.\n", contarNodos(primeroMain));
                break;
                
            case 4:
                //D: Añadir un nodo al final de la lista.
                anadirAlFinal(&primeroMain);
                break;
                
            case 5:
                //E: Buscar un elemento con una cierta key dentro de la lista.
                
                printf("Introduce la key de nodo que buscas: "); scanf("%d", &clave);
                struct tipoNodo *encontrado = buscarEnUnaLista(primeroMain, clave);

                if (encontrado != NULL) {
                    printf("Nodo Encontrado!\n");
                    printf("\t-key: %d \n\t-value: %lf\n", encontrado->informacion.key, encontrado->informacion.value);
                } else {
                    printf("Nodo no encontrado\n");
                }

                break;
                
            case 6:
                //F: Modificar la información de un elemento con una cierta clave.
                modificarNodo(&primeroMain);
                break;
                
            case 7:
                //G: Eliminar un nodo con una determinada key.

                break;
            
            case 8:
                
                break;
                
            case 9:
                
                printf("Introduce la key: "); scanf("%d", &key);
                buscado = buscarOrdenadoxClave(primeroMain, key);
                if (buscado == NULL) {
                    <#statements#>
                }
                
                break;
                
                
            case 0:
                
                break;
            default:
                printf("ERROR... \nOpción no válida...\n");
                break;
        }
    } while (option != 0);
    
    
    
}

void anadirNodo(struct tipoNodo **primero) {
    
    struct tipoNodo *nuevo;
    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo));
    
    if(nuevo!=NULL){
        printf("\nIntroduce Nodo: \n");
        printf("\t-Key: "); scanf("%d", &nuevo->informacion.key);
        printf("\t-Value: "); scanf("%lf", &nuevo->informacion.value);
        
        nuevo->siguiente = NULL; //Pasa a estar último, el siguiente.
        *primero = nuevo; //Nuevo pasa a ser el primero
        //[nuevo] -> NULL
    } else {
        printf("ERROR...\nError al asignar memoria.\nSaliendo---->>"); return;
    }

    
    
}

void visualizar(struct tipoNodo *primero) {
    
    struct tipoNodo *recorrer;
    recorrer = primero;
    
    printf("Contenido de la lista: \n\n");
    while (recorrer != NULL) {
        
        printf("[Key: %d, Value: %lf: ] --> ", recorrer->informacion.key, recorrer->informacion.value);
        
        recorrer = recorrer->siguiente;
    
    }
    printf("\n\n");
}

int contarNodos(struct tipoNodo *primero) {
    
    int contador = 0;
    struct tipoNodo *recorrer = primero;
    
    while (recorrer != NULL) {
        contador++;
        recorrer = recorrer->siguiente;
        
    }
    return contador;
}

void anadirAlFinal(struct tipoNodo **primero) {
    
    //2 casos: Lista: vacía / con nodos.
    struct tipoNodo *nuevo, *ultimo;
    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo));
    if (nuevo == NULL) {
        printf("ERROR...\nError al asignar memoria.\nSaliendo---->>"); return;
    }
    
    printf("\nIntroduce los datos del nodo:\n\t-Key: ");
    scanf("%d", &nuevo->informacion.key);
    printf("\t-Value: "); scanf("%lf", &nuevo->informacion.value);
    
    if (*primero == NULL) {
        //La lista esta vacía, lo añadimos normal:
        nuevo->siguiente = NULL; //Es como apuntar a *primero, en el caso normal.
        *primero = nuevo;
    } else {
        //La lista ya tiene nodos:
        //Hay que buscar cual apunta al último:
        ultimo = *primero;
        while (ultimo->siguiente != NULL) {
            //Hasta que no sea igual a NULL, avanza al siguiente.
            ultimo = ultimo->siguiente;
        }
        //Cuando ya localizamos el final:
        //Añadimos el último nodo al final (nuevo):
        nuevo->siguiente = NULL;
        ultimo->siguiente = nuevo;
    }
}

struct tipoNodo * buscarEnUnaLista(struct tipoNodo *primero, int key) {
    struct tipoNodo *recorrer;
    recorrer = primero;

    while (recorrer != NULL && key != recorrer->informacion.key) {
        //Tambien se puede hacer un if. y devolver null para comprobar
        recorrer = recorrer->siguiente;
    }
    return recorrer;
}

void modificarNodo(struct tipoNodo **primero) {

    struct tipoNodo *recorrer;
    recorrer = *primero;
    int key;
    printf("Introduce una key: "); scanf("%d", &key);

    while (recorrer != NULL && key != recorrer->informacion.key) {
        printf("Introduce un nuevo valor: "); scanf("%d", &recorrer->informacion.value);
        recorrer = recorrer->siguiente;
    }
    if (recorrer == NULL) { //No ha encontrado el nodo (key)
    }
        printf("La key que has introducido no existe."); return;
}

void eliminarNodo(struct tipoNodo **primero) {

    /* El objetivo es que el nodo que eliminamos apunte al siguiente de la lista*/
    struct tipoNodo *borrar, *anterior;
    borrar = *primero; //Para recorrer la lista.
    anterior = NULL; //Apunta al inicio.

    int keyUser;
    printf("Introduce la key del nodo que quieres eliminar"); scanf("%d", &keyUser);

    while (borrar != NULL && borrar->informacion.key != keyUser) {
        //Avanzamos con ambos:
        anterior = borrar;
        borrar = borrar->siguiente;
    }
    if (borrar == NULL) {
        printf("Error está key no está en la lista"); return;
    }

    //Dos casos que sea el primero o que no:
    if (borrar == *primero) {
        //muevo el primero para que apunte al segundo que ahora será el primero
        primero = borrar->siguiente;
    } else { //borro otro distinto al primero:
        anterior->siguiente = borrar->siguiente;
    }
    free(borrar);
}

void insertarOrdenado(struct tipoNodo **primero) {
    
    
}

void eliminarLista(struct tipoNodo **primero) {
    
    struct tipoNodo *borrar, *recorrer = *primero;
    
    while (recorrer != NULL) {
        borrar = recorrer;
        recorrer = recorrer->siguiente;
        free(borrar);
    }
    *primero = NULL;
}

struct tipoNodo * buscarOrdenadoxClave(struct tipoNodo *primero, int keyBuscar) {
    
    struct tipoNodo *recorrer;
    recorrer = primero;
    
    while (recorrer != NULL && recorrer->informacion.key<keyBuscar) {
        
        recorrer = recorrer->siguiente;
    }
    if (recorrer == NULL || recorrer->informacion.key != keyBuscar) {
        return NULL;
    } else {
        return recorrer;
    }
}

struct tipoNodo * eliminarOrdenadoxClave(struct tipoNodo **primero, int keyBuscar) {
    
    struct tipoNodo *borrar, *anterior;
    
    borrar = *primero;
    anterior = NULL;
    while (borrar != NULL) {
        anterior
    }
    
    
    *primero = NULL;
    
}
