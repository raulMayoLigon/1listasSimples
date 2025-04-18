#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user {
    char mail[31];
    char name[31];
    char password[17];
};

struct nodo {
    struct user informacion;
    struct nodo *siguiente;
};

struct nodo *comprobarMail(struct nodo *primero, char email[]);
void apartado1(struct nodo **primero);
void anadirUser(struct nodo **primero, char email[]);
void visualizarUsuario(struct nodo *primero);
void verListaUsuarios(struct nodo *primero);
void cambiarContraseña(struct nodo **primero);
void freeLista(struct nodo **primero);

int main(void) {
    
    struct nodo *primeroMain = NULL;
    
    int option;
    
    printf("\n--------MENÚ--------\n");
    printf("\t-1. REGISTRARSE.\n");
    printf("\t-2. Visualizar Información sobre un Usuario.\n");
    printf("\t-3. Visualizar Todos los Usuarios.\n");
    printf("\t-4: Cambiar Contraseña.\n");
    printf("\t-0: Salir\n");
    
    do {
        printf("Introduce la opción que quieras realizar: "); scanf("%d", &option);
        printf("\n");
        
        switch (option) {
            case 1:
                apartado1(&primeroMain);
                break;
                
            case 2:
                if (primeroMain == NULL) {
                    printf("No hay usuarios registrados\n");
                } else {
                    visualizarUsuario(primeroMain);
                }
                break;
                
            case 3:
                verListaUsuarios(primeroMain);
                break;
                
            case 4:
                if (primeroMain==NULL) {
                    printf("ERROR... No hay usuarios registrados.\n");
                } else {
                    cambiarContraseña(&primeroMain);
                }
                break;
                
            case 0:
                freeLista(&primeroMain);
                break;
                
            default:
                printf("Opción no válida, vuelve a intentarlo.\n");
                break;
        }
    } while (option != 0);
    
    
    return 0;
}

void apartado1(struct nodo **primero) {
    
    struct nodo *buscar;
    
    char email[31];
    printf("Introduce el email: "); fpurge(stdin); scanf("%30s", email);
    buscar = comprobarMail(*primero, email);
    
    if (buscar == NULL) {
        //Todo bien, lo añadimos:
        anadirUser(primero, email);
    } else {
        printf("ERROR... ya está registrado\n");
    }
}

struct nodo *comprobarMail(struct nodo *primero, char email[]) {
    
    struct nodo *actual = primero;
    while (actual != NULL) {
        if(strcmp(actual->informacion.mail, email) == 0){
            
            return actual;
        }
        actual=actual->siguiente;
    }
    return NULL; //No está.
}

void anadirUser(struct nodo **primero, char email[]) {
    
    struct nodo *nuevo;
    nuevo = (struct nodo*)malloc(sizeof(struct nodo));
    
    if (nuevo != NULL) {
        
        strcpy(nuevo->informacion.mail, email);
        
        if (comprobarMail(*primero, email) != NULL) {
            printf("ERROR... ya existe este usuario\n");
            free(nuevo);
            return;
        } else {
            printf("Introduce el nombre de usuario: ");
            fpurge(stdin); scanf("%30s", nuevo->informacion.name);
            printf("Introduce la contraseña del usuario: ");
            fpurge(stdin); scanf("%16s", nuevo->informacion.password);
            
            //Unirlo a la lista:
            nuevo->siguiente = *primero;
            *primero = nuevo;
            
            printf("Usuario Registrado!\n");
        }
        
        
    }
}

void visualizarUsuario(struct nodo *primero) {
    
    char email[31];
    printf("Introduce el mail del usuario a visualizar: ");
    fpurge(stdin); scanf("%30s", email);
    
    //Nodo para recorrer toda la lista empezando por primero:
    struct nodo *recorrer;
    recorrer = comprobarMail(primero, email);
    
    if (recorrer != NULL) {
        printf("Usuario: %s. Nombre: %s. Contraseña: %s.\n", recorrer->informacion.mail ,recorrer->informacion.name, recorrer->informacion.password);
    } else {
        printf("Usuario no encontrado...\n");
    }
        
    
}

void verListaUsuarios(struct nodo *primero) {
    
    struct nodo *recorrerLista;
    
    //Probamos a hacer un bucle for para recorrer toda la lista mediante un nuevo nodo.
    for (recorrerLista=primero; recorrerLista!=NULL; recorrerLista=recorrerLista->siguiente) {
        printf("\n[Usuario: %s | Nombre %s | Contraseña: %s]\n\n", recorrerLista->informacion.mail, recorrerLista->informacion.name, recorrerLista->informacion.password);
    }
}

void cambiarContraseña(struct nodo **primero) {
    
    char email[31];
    char nuevaContraseña[17];
    printf("Introduce a que usuario le quieres cambiar la contraseña (su mail): ");
    scanf("%30s", email);
    
    // Comprobar si el usuario existe
    struct nodo *usuario = comprobarMail(*primero, email);
    if (usuario == NULL) {
        printf("ERROR... El usuario con mail %s no existe.\n", email);
        return;
       }
    
    char comprobarContraseña[17];
    int intentos=0;
    
    if (usuario != NULL ) {
        
        printf("Introduce la contraseña actual del usuario (tienes 3 intentos)\n");
        
        while (intentos<3) {
            printf("Contraseña: ");
            scanf("%16s", comprobarContraseña);
            
            if (strcmp(comprobarContraseña, usuario->informacion.password)==0) {
                
                printf("Contraseña Correcta! Introduce la Nueva: ");
                scanf("%16s", nuevaContraseña);
                
                strcpy(usuario->informacion.password, nuevaContraseña);
                printf("Contraseña cambiada correctamente!\n");
                return;
            } else {
                printf("Contraseña Incorrecta! vuelve a intentarlo.\n");
                intentos ++;
            }
        }
        if (intentos>=3) {
            printf("Demasiados Intentos, no se permite cambiar la contraseña....\n");
        }
    }
}

void freeLista(struct nodo **primero) {
    struct nodo *actual = *primero;
    while (actual != NULL) {
        struct nodo *temp = actual;
        actual = actual->siguiente; //Guardamos el siguiente nodo antes de liberar.
        free(temp);
    }
    *primero = NULL;
    printf("Memoria liberada correctamente.\n");
}
