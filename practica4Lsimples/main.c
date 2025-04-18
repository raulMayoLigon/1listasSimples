#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tipoInfo {
    
    char usuario[21];
    char codigoProducto[21];
    int unidades;
    int importe;
};

struct compra {
    
    struct tipoInfo informacion;
    struct compra * siguiente;
};

void anadirCompra(struct compra **primero);
void mostrarCompra(struct compra *primero);
void anularCompra(struct compra **primero);
void visualizarCompras(struct compra *primero);

int main(void) {
    
    struct compra * primeroMain = NULL;
    int option;
    
    printf("----------MENÚ----------\n");
    printf("\t-1.Realizar compra.\n");
    printf("\t-2.Mostrar la última compra de un usuario.\n");
    printf("\t-3.Anular compra.\n");
    printf("\t-4.Visualizar las compras de un usuario.\n");
    printf("\t-0.Salir.\n");
    
    do {
        printf("Introduce una opción: "); scanf("%d", &option);
        
        switch (option) {
                
            case 1:
                anadirCompra(&primeroMain);
                break;
                
            case 2:
                mostrarCompra(primeroMain);
                break;
            
            case 3:
                anularCompra(&primeroMain);
                break;
            
            case 4:
                visualizarCompras(primeroMain);
                break;
                
            default:
                break;
        }
    } while (option != 0);
    
    
    
    return 0;
}

void anadirCompra(struct compra **primero) {
    
    struct compra *nuevo, *ultimo;
    nuevo = (struct compra *)malloc(sizeof(struct compra));
    if (nuevo == NULL) {
        printf("ERROR...\nError al asignar memoria.\nSaliendo---->>"); return;
    }
    
    printf("\nIntroduce los datos de tu compra:\n");
    printf("\t-Usuario: "); fpurge(stdin);
    scanf("%s", nuevo->informacion.usuario);
    printf("\t-Código del producto: "); fpurge(stdin);
    scanf("%s", nuevo->informacion.codigoProducto);
    printf("\t-Unidades: "); scanf("%d", &nuevo->informacion.unidades);
    printf("\t-Importe de la compra: "); scanf("%d", &nuevo->informacion.importe);
    
    
    if (*primero == NULL) {
        //La lista estará vacía:
        nuevo->siguiente = NULL;
        *primero = nuevo;
    } else {
        //La lista ya tiene nodos:
        ultimo = *primero;
        while (ultimo->siguiente != NULL) {
            //Avanza hasta que no sea NULL:
            ultimo = ultimo->siguiente;
        }
        nuevo->siguiente = NULL; // Lo ponemos al final.
        ultimo->siguiente = nuevo;
        
    }
}

void mostrarCompra(struct compra *primero) {
    
    char usuarioBuscar[21];
    struct compra *actual = primero;
    struct compra *ultimo = NULL;
    
    printf("Introduce el usuario: "); fpurge(stdin); scanf("%s", usuarioBuscar);
    
    while (actual != NULL) {
            if (strcmp(actual->informacion.usuario, usuarioBuscar) == 0) {
                ultimo = actual;  // Actualizamos la última compra encontrada
            }
            actual = actual->siguiente;
        }

        if (ultimo != NULL) {
            printf("Última compra de %s:\n", usuarioBuscar);
            printf("\t- Código del producto: %s\n", ultimo->informacion.codigoProducto);
            printf("\t- Unidades: %d\n", ultimo->informacion.unidades);
            printf("\t- Importe: %d\n", ultimo->informacion.importe);
        } else {
            printf("\nEl usuario %s no ha realizado ninguna compra.\n", usuarioBuscar);
        }
}

void anularCompra(struct compra **primero) {
    char usuarioBuscar[21], codigoBuscar[21];
    int importeBuscar;
    struct compra *actual = *primero;
    struct compra *anterior = NULL;

    printf("Introduce el usuario: "); fpurge(stdin);
    scanf("%s", usuarioBuscar);
    printf("Introduce el código del producto: "); fpurge(stdin);
    scanf("%s", codigoBuscar);
    printf("Introduce el importe: "); fpurge(stdin);
    scanf("%d", &importeBuscar);

    while (actual != NULL) {
        if (strcmp(actual->informacion.usuario, usuarioBuscar) == 0 &&
            strcmp(actual->informacion.codigoProducto, codigoBuscar) == 0 &&
            actual->informacion.importe == importeBuscar) {
            
            if (anterior == NULL) {
                *primero = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }

            free(actual);
            printf("Compra eliminada correctamente!\n");
            return;
        }

        anterior = actual;
        actual = actual->siguiente;
    }

    printf("No se encontró ninguna compra con esos datos.\n");
}

void visualizarCompras(struct compra *primero) {
    char usuarioBuscar[21];
    int encontrado = 0;

    printf("Introduce el usuario: "); fpurge(stdin);
    scanf("%s", usuarioBuscar);

    struct compra *actual = primero;

    printf("Compras del usuario %s:\n", usuarioBuscar);

    while (actual != NULL) {
        if (strcmp(actual->informacion.usuario, usuarioBuscar) == 0) {
            printf("- Código: %s | Unidades: %d | Importe: %d\n",
                   actual->informacion.codigoProducto,
                   actual->informacion.unidades,
                   actual->informacion.importe);
            encontrado = 1;  // Lo encontramos.
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        printf("El usuario %s no ha realizado ninguna compra.\n", usuarioBuscar);
    }
}
