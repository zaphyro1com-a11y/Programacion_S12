#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "betterio.h"

// Lee una string de n+1 caracteres.
void readLine(char str[], int n){
    
    //variables
    int buffer_size= n+1;

    do{
        
        //leer cadena
        fgets(str, buffer_size, stdin);

        //obtener longitud de cadena
        int str_len= strlen(str);
        
        // eliminar '\n' y verificar un tamaño minimo
        if(str_len > 1){
            if(str[str_len-1]== '\n'){
                str[str_len-1]= '\0'; 
                break;

            }
        }else{
            printf("\nERROR. Recuerde Ingresar Al Menos Un Caracter\n");
            printf("Ingrese el campo solicitado nuevamente.\n >>> ");
        }
    }while(1);
    

}

// Lee una string de 10 caracteres y lo transforma a entero.
int readInt(int *var){
    //campos
    const int buffer_size= 10;
    char buffer[buffer_size];
    char *aux;

    // leer entrada
    fgets(buffer, buffer_size, stdin);

    // convertir a entero
    *var= strtol(buffer, &aux, 10);

    if(buffer== aux){
        printf("\nERROR. Ingrese Un Numero Vaido\n");
        return 1;

    }

    return 0;
}

// Lee una string de 10 caracteres y lo transforma a entero.
// Ademas verifica su rango de valor.
int readIntRange(int *var, int min, int max){

    //campos
    const int buffer_size= 10;
    char buffer[buffer_size];
    char *aux;

    // leer entrada
    fgets(buffer, buffer_size, stdin);

    // convertir a entero
    *var= strtol(buffer, &aux, 10);

    if(buffer== aux){
        printf("\nERROR. Ingrese Un Numero Valido\n");
        return 1;

    }else if(*var < min){
        
        printf("\nERROR. El Numero Ingresado Debe Ser Mayor A %d\n", min);
        return 1;

    }else if(*var > max){

        printf("\nERROR. El Numero Ingresado Debe Ser Menor A %d\n", max);
        return 1;

    }
    
    return 0;

}

// Lee una string de 10 caracteres y lo transforma a entero.
// Ademas verifica su rango de valor y solicita el numero hasta que sea valido.
void readIntLoop(char msg[], int *var, int min, int max){

    do{

        printf("%s", msg);

    }while(readIntRange(var, min, max) == 1);

}

// Lee una string de 10 caracteres y lo transforma a long int.
int readLongInt(long int *var){
    //campos
    const int buffer_size= 15;
    char buffer[buffer_size];
    char *aux;

    // leer entrada
    fgets(buffer, buffer_size, stdin);

    // convertir a entero
    *var= strtol(buffer, &aux, 10);

    if(buffer== aux){
        printf("\nERROR. Ingrese Un Numero Vaido\n");
        return 1;

    }

    return 0;
}

// Lee una string de 10 caracteres y lo transforma a long int.
// Ademas verifica su rango de valor.
int readLongIntRange(long int *var, long int min, long int max){

    //campos
    const int buffer_size= 15;
    char buffer[buffer_size];
    char *aux;

    // leer entrada
    fgets(buffer, buffer_size, stdin);

    // convertir a entero
    *var= strtol(buffer, &aux, 10);

    if(buffer== aux){
        printf("\nERROR. Ingrese Un Numero Valido\n");
        return 1;

    }else if(*var < min){
        
        printf("\nERROR. El Numero Ingresado Debe Ser Mayor A %d\n", min);
        return 1;

    }else if(*var > max){

        printf("\nERROR. El Numero Ingresado Debe Ser Menor A %d\n", max);
        return 1;

    }
    
    return 0;

}

// Lee una string de 10 caracteres y lo transforma a long iny.
// Ademas verifica su rango de valor y solicita el numero hasta que sea valido.
void readLongIntLoop(char msg[], long int *var, long int min, long int max){

    do{

        printf("%s", msg);

    }while(readLongIntRange(var, min, max) == 1);

}

// Lee una string de 10 caracteres y lo transforma a flotante.
int readFloat(float *var){

    //campos
    const int buffer_size= 8;
    char buffer[buffer_size];
    char *aux;

    // leer entrada
    fgets(buffer, buffer_size, stdin);

    // convertir a entero
    *var= strtof(buffer, &aux);

    if(buffer== aux){
        printf("\nERROR. Ingrese Un Numero Valido\n");
        return 1;

    }

    return 0;

}

// Lee una string de 10 caracteres y lo transforma a flotante.
// Ademas verifica su rango de valor.
int readFloatRange(float *var, float min, float max){

    //campos
    const int buffer_size= 8;
    char buffer[buffer_size];
    char *aux;

    // leer entrada
    fgets(buffer, buffer_size, stdin);

    // convertir a entero
    *var= strtof(buffer, &aux);

    if(buffer== aux){
        printf("\nERROR. Ingrese Un Numero Valido\n");
        return 1;

    }else if(*var < min){
        
        printf("\nERROR. El Numero Ingresado Debe Ser Mayor A %.3f\n", min);
        return 1;

    }else if(*var > max){

        printf("\nERROR. El Numero Ingresado Debe Ser Menor A %.3f\n", max);
        return 1;

    }

    return 0;

}

// Lee una string de 10 caracteres y lo transforma a flotante.
// Ademas verifica su rango de valor y solicita el numero hasta que sea valido.
void readFloatLoop(char msg[], float *var, float min, float max){

    do{

        printf("%s", msg);

    }while(readFloatRange(var, min, max));

}

// Lee una string de 10 caracteres y lo transforma a flotante.
int readDouble(double *var){

    //campos
    const int buffer_size= 15;
    char buffer[buffer_size];
    char *aux;

    // leer entrada
    fgets(buffer, buffer_size, stdin);

    // convertir a entero
    *var= strtod(buffer, &aux);

    if(buffer== aux){
        printf("\nERROR. Ingrese Un Numero Valido\n");
        return 1;

    }

    return 0;

}

// Lee una string de 10 caracteres y lo transforma a flotante.
// Ademas verifica su rango de valor.
int readDoubleRange(double *var, double min, double max){

    //campos
    const int buffer_size= 15;
    char buffer[buffer_size];
    char *aux;

    // leer entrada
    fgets(buffer, buffer_size, stdin);

    // convertir a entero
    *var= strtod(buffer, &aux);

    if(buffer== aux){
        printf("\nERROR. Ingrese Un Numero Valido\n");
        return 1;

    }else if(*var < min){
        
        printf("\nERROR. El Numero Ingresado Debe Ser Mayor A %.3f\n", min);
        return 1;

    }else if(*var > max){

        printf("\nERROR. El Numero Ingresado Debe Ser Menor A %.3f\n", max);
        return 1;

    }

    return 0;

}

// Lee una string de 10 caracteres y lo transforma a flotante.
// Ademas verifica su rango de valor y solicita el numero hasta que sea valido.
void readDoubleLoop(char msg[], double *var, double min, double max){

    do{

        printf("%s", msg);

    }while(readDoubleRange(var, min, max));

}

void drawMenu(char *title, char **options, int options_num){

    // obtener string mas largo
    int max_strlen= strlen(options[0]);

    for(int i= 1; i < options_num; i++){

        if(strlen(options[i])> max_strlen)
            max_strlen= strlen(options[i]);  

    }

    // Linea de separacion
    printf("\n");

    // Titulo
     for(int i= 0; i < ((max_strlen+10)/4); i++) printf(" ");
     printf("| %s |\n", title);

    // Margen superior
    for(int i= 0; i < (max_strlen+10); i++) printf("=");
    
    // Contenido
    for(int i= 0; i < options_num; i++){

        printf("\n  (%d) %s ", i+1, options[i]);

    }
    // Margen inferior
    printf("\n");
    for(int i= 0; i < (max_strlen+10); i++) printf("=");

    // Linea de Separacion
    printf("\n");
}