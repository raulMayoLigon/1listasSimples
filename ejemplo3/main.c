#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------LISTA----------------------

struct libro {
    char titulo [21];
    char autor [21];
    int anno;
};

struct nodo {
    struct libro informacion;
    struct nodo *siguiente;
};

//---------------------DECLARAR FUNCIONES---------------------

void anadirLibro (struct nodo **primero);
void mostrarLibros (struct nodo *primero);
void buscarLibro (struct nodo *primero);
void eliminarLibro (struct nodo **primero);
void contarLibros (struct nodo *primero);
void ordenarLista (struct nodo **primero); //Queda pendiente

void liberarMemoria (struct nodo **primero);


//----------------------MAIN----------------------

int main (void) {
    
    struct nodo *primeroMain = NULL;
    int option = 0;
    
    printf("\n\n************MENÚ************\n");
    printf("\t1.Agregar un libro.\n");
    printf("\t2.Mostrar todos los libros.\n");
    printf("\t3.Buscar un libro por título.\n");
    printf("\t4.Eliminar un libro por título.\n");
    printf("\t5.Contar cuántos libros hay en la lista.\n");
    printf("\t6.ordenar la lista por año de publicación.\n");
    printf("\t0.Liberar memoria y salir.\n");
    
    do {
        
        printf("Introduce una opción: "); scanf("%d", &option);
        
        switch (option) {
                
            case 1:
                anadirLibro(&primeroMain);
                break;
                
            case 2:
                mostrarLibros(primeroMain);
                break;
                
            case 3:
                buscarLibro(primeroMain);
                break;
                
            case 4:
                eliminarLibro(&primeroMain);
                break;
                
            case 5:
                contarLibros(primeroMain);
                break;
                
            case 0:
                liberarMemoria(&primeroMain);
                break;
                
            default:
                printf("Opción no válida, vuelve a intentarlo.\n");
                break;
        }
        
    } while (option != 0);
    
    return 0;
}

//----------------------FUNCIONES----------------------

void anadirLibro (struct nodo **primero) {
    
    struct nodo *nuevo;
    nuevo = (struct nodo *)malloc(sizeof(struct nodo));
    
    if (nuevo != NULL) {
        printf("Introduce los datos del nuevo Libro: \n");
        printf("\t-Titulo: "); scanf("%s", nuevo->informacion.titulo);
        printf("\t-Autor: "); scanf("%s", nuevo->informacion.autor);
        printf("\t-Año: "); scanf("%d", &nuevo->informacion.anno);
        
        nuevo->siguiente = *primero;
        *primero = nuevo;
    }
    
}

void mostrarLibros (struct nodo *primero) {
    
    struct nodo *recorrer;
    recorrer = primero;
    
    while (recorrer != NULL) {
        printf("[%s | %s | %d] --> ", recorrer->informacion.titulo, recorrer->informacion.autor, recorrer->informacion.anno);
        
        recorrer = recorrer->siguiente;
    }
    printf("[NULL]\n");
}

void buscarLibro (struct nodo *primero) {
    struct nodo *recorrer;
    recorrer = primero;
    char tituloBuscar [21];
    
    printf("Introduce el título del libro que buscas: ");
    scanf("%s", tituloBuscar);
    
    while (recorrer != NULL) {
        
        if (strcmp(recorrer->informacion.titulo, tituloBuscar)==0) {
            printf("Libro encontrado ✅\n");
            printf("Libro: [%s, %s, %d]\n", recorrer->informacion.titulo, recorrer->informacion.autor, recorrer->informacion.anno);
            
            return;
        }
        recorrer = recorrer->siguiente;
    }
    printf("ERROR libro no encontrado ❌\n");
}

void eliminarLibro (struct nodo **primero) {
    
    struct nodo *eliminar;
    eliminar = *primero;
    struct nodo *anterior;
    anterior = NULL;
    
    char tituloBuscar[21];
    printf("Introduce el título del libro que quieres eliminar: ");
    scanf("%s", tituloBuscar);
    
    while (eliminar != NULL) {
        
        if (strcmp(eliminar->informacion.titulo, tituloBuscar) == 0) {
            printf("Libro encontrado, eliminando...\n");
            if (anterior == NULL) { //Es el primero
                *primero = eliminar->siguiente;
            } else { //Es cualquier otro libro
                anterior->siguiente = eliminar->siguiente;
            }
            free(eliminar);
            return;
        }
        //Condición del bucle.
        anterior = eliminar;
        eliminar = eliminar->siguiente;
    }
    printf("ERROR... no se encontró tu libro.\n");
    
}

void contarLibros (struct nodo *primero) {
    
    struct nodo *recorrer;
    recorrer = primero;
    int contar = 0;
    
    while (recorrer != NULL) {
        
        contar ++;
        recorrer = recorrer->siguiente;
    }
    printf("Hay %d Libros en total.\n", contar);
}

void liberarMemoria (struct nodo **primero) {
    
    struct nodo *actual = *primero;
    struct nodo *temp;
    
    while (actual != NULL) {
        
        temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    *primero = NULL; //Volver a inicializarla.
}

void ordenarLista (struct nodo **primero) {

}
