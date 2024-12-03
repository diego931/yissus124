#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Se agregan comentarios para facilitarnos la organizacion del programa

// Estructuras para manejar los datos
typedef struct {
    char nombre[50];
    char usuario[20];
    char contrasena[20];
    int tipo_tarjeta; // 1: Básica, 2: Oro, 3: Platino
    int puntos;
} Tarjetahabiente;

typedef struct {
    char categoria[30];
    char nombre_producto[50];
    int disponibles;
    int tipo_tarjeta_necesaria; // 1: Básica, 2: Oro, 3: Platino
    int puntos_requeridos;
} Producto;

// Datos iniciales
Tarjetahabiente usuarios[] = {
    {"Salvador Rivero", "jorges", "1234", 2, 5000},   // Oro
    {"Alan Jasso", "alanj", "5678", 3, 10000},        // Platino
    {"Diego Munguia", "diegom", "91011", 1, 2000}     // Básica
};

Producto productos[] = {
    {"Artículos para el hogar", "Batería T-Fal", 5, 3, 4000},    // Platino
    {"Certificados", "Tarjeta de regalo Amazon $200", 10, 1, 100}, // Básica
    {"Viajes o tours", "Tour 'El Cielito' Cozumel", 2, 2, 10000} // Oro
};

int numUsuarios = 3;
int numProductos = 3;

// Funciones
int mostrarMenu(int usuarioIndex);
int realizarCanje(int usuarioIndex);
int mostrarProductos();
int mostrarDatosUsuario(int usuarioIndex);

int main() {
    char usuario[20], contrasena[20];
    int intentos = 3, usuarioIndex = -1;

    do {
        printf("Ingrese su usuario: ");
        scanf("%s", usuario);
        printf("Ingrese su contrasena: ");
        scanf("%s", contrasena);

        for (int i = 0; i < numUsuarios; i++) {
            if (strcmp(usuarios[i].usuario, usuario) == 0 && strcmp(usuarios[i].contrasena, contrasena) == 0) {
                usuarioIndex = i;
                break;
            }
        }

        if (usuarioIndex == -1) {
            printf("Usuario o contrasena incorrectos. Intentos restantes: %d\n", --intentos);
        }
    } while (usuarioIndex == -1 && intentos > 0);

    if (usuarioIndex != -1) {
        mostrarMenu(usuarioIndex);
    } else {
        printf("Se agotaron los intentos. Reinicie el programa.\n");
    }

    return 0;
}

int mostrarMenu(int usuarioIndex) {
    int opcion, repetir;
    do {
        printf("\nMenu Tarjetahabiente:\n");
        printf("1. Mostrar mis datos\n");
        printf("2. Mostrar productos\n");
        printf("3. Canjear producto\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                mostrarDatosUsuario(usuarioIndex);
                break;
            case 2:
                mostrarProductos();
                break;
            case 3:
                realizarCanje(usuarioIndex);
                break;
            case 4:
                printf("Gracias por usar el sistema.\n");
                repetir = 0;
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
        printf("¿Desea realizar otra acción? (1: Sí, 0: No): ");
        scanf("%d", &repetir);
    } while (repetir);
    return 0;
}

int mostrarDatosUsuario(int usuarioIndex) {
    printf("\nDatos del usuario:\n");
    printf("Nombre: %s\n", usuarios[usuarioIndex].nombre);
    printf("Usuario: %s\n", usuarios[usuarioIndex].usuario);

    // Mostrar tipo de tarjeta
    printf("Tipo de tarjeta: ");
    switch (usuarios[usuarioIndex].tipo_tarjeta) {
        case 1: printf("Básica\n"); break;
        case 2: printf("Oro\n"); break;
        case 3: printf("Platino\n"); break;
    }

    printf("Puntos disponibles: %d\n", usuarios[usuarioIndex].puntos);
    return 0;
}

int mostrarProductos() {
    printf("\nProductos disponibles:\n");
    for (int i = 0; i < numProductos; i++) {
        printf("%d. %s - %s (Puntos requeridos: %d, Disponibles: %d, Tarjeta necesaria: ",
               i + 1, productos[i].categoria, productos[i].nombre_producto,
               productos[i].puntos_requeridos, productos[i].disponibles);

        // Mostrar tipo de tarjeta necesaria
        switch (productos[i].tipo_tarjeta_necesaria) {
            case 1: printf("Básica"); break;
            case 2: printf("Oro"); break;
            case 3: printf("Platino"); break;
        }
        printf(")\n");
    }
    return 0;
}

int realizarCanje(int usuarioIndex) {
    int seleccion;
    mostrarProductos();
    printf("Seleccione el producto que desea canjear (1-%d): ", numProductos);
    scanf("%d", &seleccion);
    seleccion--;

    if (seleccion < 0 || seleccion >= numProductos) {
        printf("Selección no válida.\n");
        return 1;
    }

    Producto *producto = &productos[seleccion];
    Tarjetahabiente *usuario = &usuarios[usuarioIndex];

    if (producto->disponibles <= 0) {
        printf("Lo sentimos, este producto ya no está disponible.\n");
    } else if (usuario->puntos < producto->puntos_requeridos) {
        printf("No tienes suficientes puntos para canjear este producto.\n");
    } else if (usuario->tipo_tarjeta < producto->tipo_tarjeta_necesaria) {
        printf("Tu tarjeta no cumple con los requisitos para este producto.\n");
    } else {
        usuario->puntos -= producto->puntos_requeridos;
        producto->disponibles--;
        printf("Canje exitoso. Disfruta tu %s.\n", producto->nombre_producto);
    }
    return 0;
}
