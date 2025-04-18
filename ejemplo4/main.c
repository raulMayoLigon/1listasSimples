#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------LISTA--------------------------

struct paciente {
    char paciente [21];
    int edad;
    char motivoConsulta [40];
    int prioridad;
};

struct nodo {
    struct paciente informacion;
    struct nodo *siguiente;
};

//--------------------------Declarar FUNCIONES--------------------------

void anadirPaciente (struct nodo **primero);
void eliminarPrimero (struct nodo **primero);
void mostrarPacientes (struct nodo *primero);
void buscarPaciente (struct nodo *primero);
void ordenarPrioridad (struct nodo **primero);
void liberarMemoria (struct nodo **primero);

//--------------------------MAIN--------------------------

int main(void) {
    
    struct nodo *primeroMain = NULL;
    int option = 0;
    
    printf("\n********************MENÚ********************\n\n");
    printf("\t1.Añadir un paciente a la lista.\n");
    printf("\t2.Atender al primer paciente de la cola.\n");
    printf("\t3.Mostrar la lista de pacientes en espera.\n");
    printf("\t4.Buscar un paciente por nombre.\n");
    printf("\t5.Ordenar la lista por prioridad.\n");
    printf("\t0.Salir\n");
    printf("*********************************************\n");
    
    do {
        printf("Introduce una opción: "); scanf("%d", &option);
        
        switch (option) {
                
            case 1:
                anadirPaciente(&primeroMain);
                break;
                
            case 2:
                eliminarPrimero(&primeroMain);
                break;
                
            case 3:
                mostrarPacientes(primeroMain);
                break;
                
            case 4:
                buscarPaciente(primeroMain);
                break;
                
            case 5:
                ordenarPrioridad(&primeroMain);
                break;
                
            case 0:
                liberarMemoria(&primeroMain);
                printf("Memoria liberada! ---> ");
                break;
                
            default:
                printf("Opción no válida...");
                break;
        }
        
    } while (option<0 || option>5);
    
    return 0;
}

//--------------------------FUNCIONES--------------------------

void anadirPaciente (struct nodo **primero) {
 
    struct nodo *nuevo, *ultimo;
    nuevo = (struct nodo *)malloc(sizeof(struct nodo));
    if (nuevo == NULL) {
        printf("ERROR... Al asignar memoria...\n"); return;
    }
    
    printf("\nIntroduce los datos del paciente: \n");
    printf("-Paciente: "); scanf("%s", nuevo->informacion.paciente);
    printf("-Edad: "); scanf("%d", &nuevo->informacion.edad);
    printf("-Motivo: "); scanf("%s", nuevo->informacion.motivoConsulta);
    printf("-Prioridad: "); scanf("%d", &nuevo->informacion.prioridad);
    
    //Dos condiciones
    if (*primero == NULL) { //Lista vacía (caso normal)
        
        nuevo->siguiente = NULL; //No hay nadie detrás
        *primero = nuevo; //El nuevo será el primero
        
    } else { //Lista con nodos.
        
        ultimo = *primero;
        while (ultimo->siguiente != NULL) { //Localizamos al último
            ultimo = ultimo->siguiente;
        }
        //Metemos a nuevo en la lista detrás del último
        nuevo->siguiente = NULL;
        ultimo->siguiente = nuevo;
    }
}

void eliminarPrimero (struct nodo **primero) {
    
    if (*primero == NULL) {
        printf("No hay ningún paciente que atender.\n"); return;
    }
    struct nodo *borrar;
    borrar = *primero; //Para luego liberarlo.
    *primero = (*primero)->siguiente;
    free(borrar);
}

void mostrarPacientes (struct nodo *primero) {
    
    struct nodo *recorrer;
    recorrer = primero;
    
    if (primero == NULL) {
        printf("No hay ningún paciente.\n"); return;
    }
    
    printf("Pacientes en espera:\n");
    while (recorrer != NULL) {
        
        printf("-%s\n", recorrer->informacion.paciente);
        recorrer = recorrer->siguiente;
    }
}

void buscarPaciente (struct nodo *primero) {
    
    char pacienteBuscar [21];
    struct nodo *recorrer;
    recorrer = primero;
    
    printf("Introduce que paciente quieres buscar: ");
    scanf("%s", pacienteBuscar);
    while (recorrer != NULL) {
        
        if ((strcmp(pacienteBuscar, recorrer->informacion.paciente) == 0)) {
            printf("Paciente encontrado!\n");
            printf("Datos de %s:\n", recorrer->informacion.paciente);
            printf("-Edad: %d.", recorrer->informacion.edad);
            printf("-Motivo de la consulta: %s.\n", recorrer->informacion.motivoConsulta);
            printf("-Prioridad: %d.\n", recorrer->informacion.prioridad);
            
            return;
        }
        recorrer = recorrer->siguiente;
    }
    printf("No se encontró al paciente...\n");
}

void ordenarPrioridad (struct nodo **primero) {
    
    if (*primero==NULL || (*primero)->siguiente==NULL) {
        printf("No hay pacientes para ordenar...\n"); return;
    }
    
    printf("El orden de pacientes es: \n");
    int intercambiado = 0;
    struct nodo *actual;
    struct nodo *ultimo = NULL;
    
    do {
        intercambiado = 0;
        actual = *primero;
        
        while (actual->siguiente != ultimo) {
            
            if (actual->informacion.prioridad < actual->siguiente->informacion.prioridad) {
                //Cambiamos el orden:
                struct paciente temp;
                temp = actual->informacion;
                actual->informacion = actual->siguiente->informacion;
                actual->siguiente->informacion = temp;
                
                intercambiado = 1;
            }
            printf("-%d: %s\n", actual->informacion.prioridad, actual->informacion.paciente);
            actual = actual->siguiente;
        }
        ultimo = actual; //Actualizamos el último al que ya hemos ordenado
        
    } while (intercambiado == 1);
    
}

void liberarMemoria (struct nodo **primero) {
    
    struct nodo *actual, *temp;
    actual = *primero;
    
    while (actual != NULL) {
        
        temp = actual->siguiente;
        free(actual);
        actual = temp;
    }
}
