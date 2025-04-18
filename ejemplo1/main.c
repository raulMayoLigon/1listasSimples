#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void buscarNodo(struct tipoNodo *primero);
void modificarNodo(struct tipoNodo **primero);
void eliminarNodo(struct tipoNodo **primero);

int main(void) {
    
    struct tipoNodo *primeroMain = NULL; //lista vacía
    int option;
    
    
    printf("\n--------MENÚ--------\n");
    printf("\t-1.Añadir un nodo.\n");
    printf("\t-2.Visualizar Lista.\n");
    printf("\t-3.Ver Nº de nodos.\n");
    printf("\t-4.Añadir un nodo al final.\n");
    printf("\t-5.Buscar un nodo.\n");
    printf("\t-6.Modificar un nodo.\n");
    printf("\t-0.Salir\n");
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
                buscarNodo(primeroMain);
                break;
                
            case 6:
                //F: Modificar la información de un elemento con una cierta clave.
                modificarNodo(&primeroMain);
                break;
                
            case 7:
                //G: Eliminar un nodo con una determinada key.
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
        
        nuevo->siguiente = *primero; //Primero apunta a NULL, pasa a estar último.
        *primero = nuevo;
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

void buscarNodo(struct tipoNodo *primero) {
    
    struct tipoNodo *recorrer;
    recorrer = primero;
    int keyBuscar;
    int encontrado = 0;
    printf("\nIntroduce la key del nodo que buscas: "); scanf("%d", &keyBuscar);
    
    while (recorrer != NULL) {
        if (keyBuscar == recorrer->informacion.key) {
            printf("Tu nodo con Key %d tiene un valor de: %lf\n", keyBuscar, recorrer->informacion.value);
            encontrado = 1;
            break;
        
        }
        recorrer = recorrer->siguiente;
    }
    if (encontrado == 0) {
        printf(".....Nodo no encontrado\n"); return;
    }
        
}

void modificarNodo(struct tipoNodo **primero) {
    
    struct tipoNodo *recorrer;
    recorrer = *primero;
    
    int nodoModificar;
    printf("Introduce el nodo que quieres modificar: "); scanf("%d", &nodoModificar);
    
    int encontrado = 0;
    
    while (recorrer != NULL) {
        
        if (nodoModificar == recorrer->informacion.key) {
            
            printf("Introduce el nuevo valor de tu nodo: \n");
            scanf("%lf", &recorrer->informacion.value);
            
            encontrado = 1;
            printf("\nNodo modificado !\n");
            break;
        
        }
        recorrer = recorrer->siguiente;
        }
    if (encontrado == 0) {
        printf("No encontramos tu nodo..."); return;
    }
}

void eliminarNodo(struct tipoNodo **primero) {
    
    struct tipoNodo *recorrer = *primero;
    int nodoEliminar;
    
    printf("Introduce el nodo que quieres eliminar: "); scanf("%d", &nodoEliminar);
    
    int encontrado = 0;
    
    while (recorrer != NULL) {
        
        if (nodoEliminar == recorrer->informacion.key) {
            
            
            
            encontrado = 1;
            printf("\nNodo eliminado !\n");
            break;
        
        }
        recorrer = recorrer->siguiente;
        }
    if (encontrado == 0) {
        printf("No encontramos tu nodo..."); return;
    }
}
    



