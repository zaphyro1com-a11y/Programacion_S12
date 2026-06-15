#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "SGIC.h"
#include "betterio.h"
#include "cars.h"
#include "customers.h"


void drawMainMenu(){

    char *main_menu_options[25]={

        "V E H I C U L O S",
        "C L I E N T E S",
        "B U S C A R",
        "S A L I R",

    };

    drawMenu("S G I C", main_menu_options, 4);

}

void drawCarsMenu(){

    char *cars_menu_options[25]= {
        "Lista De Vehiculos",
        "Agregar Vehiculo",
        "Eliminar Vehiculo",
        "Cerrar",
    };

    drawMenu("C A R S", cars_menu_options, 4);

}

Car* carsMenu(int option, Car *_car_list, int *_car_number){

 
    switch (option){
        //Lista de vehiculos
        case 1:
            printInventory(_car_list, *_car_number);

            break;

        case 2:
            _car_list= addCar(_car_list, _car_number);

            break;

        case 3:
            _car_list= removeCar(_car_list, _car_number);

            break;

        case 4:
            printf("\nRegresando...\n");

            break;

        default:
            printf("Como llegaste aqui??\n");

            break;
        }

    return _car_list;

}

void drawCustomersMenu(){

    char *customers_menu_options[25]= {

        "Lista De Clientes",
        "Agregar Cliente",
        "Eliminar Clientes",
        "Cerrar",

    };

    drawMenu("C U S T O M E R S", customers_menu_options, 4);

}

Customer* customersMenu(int option, Customer *_customers_list, int *_customers_number){

 
    switch (option){
        //Lista de clientes
        case 1:
            printCustomersList(_customers_list, *_customers_number);

            break;

        // Añadir Clientes    
        case 2:
            _customers_list= addCustomer(_customers_list, _customers_number);

            break;

        // Eliminar Clientes
        case 3:
            _customers_list= removeCustomer(_customers_list, _customers_number);

            break;

        // SALIR 
        case 4:
            printf("\nRegresando...\n");

            break;

        default:
            printf("Como llegaste aqui??\n");

            break;
        }

    return _customers_list;

}

int makeFiles() {

    // Intentar abrir en modo lectura para ver si ya existen
    FILE *cars_f = fopen("Data/cars.dat", "rb");
    if (cars_f == NULL) {
        // Si no existe, lo creamos
        cars_f = fopen("Data/cars.dat", "wb");
        if (cars_f == NULL) {
            printf("ERROR: No se pudo crear Data/cars.dat\n");
            return -1;
        }
    }
    fclose(cars_f);

    FILE *customers_f = fopen("Data/customers.dat", "rb");
    if (customers_f == NULL) {
        // Si no existe, lo creamos
        customers_f = fopen("Data/customers.dat", "wb");
        if (customers_f == NULL) {
            printf("ERROR: No se pudo crear Data/customers.dat\n");
            return -1;
        }
    }
    fclose(customers_f);

    return 0; 
}

int initializeData(Car **_cars_list, Customer **_customers_list, int *_cars_number, int *_customers_number){

    if(*_cars_number > 0) {
        *_cars_list = malloc((*_cars_number) * sizeof(Car)); // espacio necesario para cargar
    }else {
        *_cars_list = malloc(1 * sizeof(Car)); // Espacio mínimo inicial
        return 1;
    }

    if(*_customers_number > 0){
        *_customers_list= malloc((*_customers_number) * sizeof(Customer));
    }else{
        *_customers_list= malloc(1 * sizeof(Customer));
        return 1;
    }

    // Validar Asignacion de Memoria
    if (*_cars_list == NULL || *_customers_list == NULL) {
        printf("\nERROR. No se pudo asignar memoria\n");
        exit(EXIT_FAILURE);

    }

    return 0;

}

int SaveMetadata(int _cars_number, int _customers_number){

    FILE *metadata_f= fopen("Data/meta.dat", "wb");

    if(metadata_f == NULL){
        printf("\nERROR. No se pudo abrir el archivo meta.dat.\n");
        exit(EXIT_FAILURE);

    }

    fwrite(&_cars_number, sizeof(int), 1, metadata_f);
    fwrite(&_customers_number, sizeof(int), 1, metadata_f);

    fclose(metadata_f);

    return 0;

}

int LoadMetadata(int *_cars_number, int *_customers_number){

    FILE *metadata_f= fopen("Data/meta.dat", "rb");

    if(metadata_f == NULL){
        SaveMetadata(0, 0);
        (*_cars_number)= 0;
        (*_customers_number)= 0;
        return 1; // se creo el archivo por primera vez

    }

    fread(_cars_number, sizeof(int), 1, metadata_f);
    fread(_customers_number, sizeof(int), 1, metadata_f);

    fclose(metadata_f);

    return 0;

}

void strTolower(char string[], char new_str[]) {
    int i = 0;
    // Convertir cada caracter a minuscula y guardarlo en new_str
    while(string[i]) {
        new_str[i] = tolower(string[i]);
        i++;
    }
    // AGREGRAR al nuevo string el caracter '\0'
    new_str[i] = '\0'; 
}

Car* getCustomerCarOptions(Car *_cars_list, Customer **_customers_list, int *_cars_number, int *_customers_number){

    int user_option, customer_indx, options_number=0;
    int options_indx[10];
    Car *Options = malloc(sizeof(Car)*1);

    if(Options == NULL){
        printf("\nERROR. No se pudo iniciar memoria\nIntente de Nuevo\n");
        return _cars_list;
    }

    printf("\n\tFILTRO DE CARROS POR PREFERENCIA\n");

    // Preguntar al usuario si desea crear un nuevo cliente
    printf("Desea Agregar un Cliente a la lista?\n(1)SI / (2)NO\n");
    readIntLoop(" >>> ", &user_option, 1, 2);

    if(user_option == 1){
        //Crear Nuevo Usuario y Seleccionarlo
        *_customers_list= addCustomer(*_customers_list, _customers_number);
        customer_indx= (*_customers_number)-1;

    }else{
        // Seleccionar un Usuario
        printCustomersList(*_customers_list, *_customers_number);
        printf("Ingrese el indice del Cliente seleccionado\n");
        readIntLoop("Indice >>> ", &customer_indx, 0, (*_customers_number)-1);

    }

    //////   Realizar Busqueda   /////
    // Filtrar Busqueda por precio
    // guardar carros que cumplan con el precio del cliente
    for(int i= 0; i<(*_cars_number); i++){
        // Si el dinero del usuario es mayor al precio del carro entonces guardar el carro en la lista de opciones
        if((*_customers_list)[customer_indx].preferences.price >= _cars_list[i].price){

            Options[options_number]= _cars_list[i];
            
            //almacenar indices gemelos
            options_indx[options_number]= i;

            options_number++;

            Car *tmp_p= realloc(Options, sizeof(Car)*(options_number+1));

            if(tmp_p == NULL){
                printf("\nERROR. No se pudo solicitar memoria\nIntente de Nuevo\n");
                return _cars_list;
;
            }

            Options= tmp_p;

        }

    }
    if(options_number == 0){
        printf("No se Encontraron Coincidencias\nEl cliente no cuenta con los fondos suficientes para comprar algun auto.\n");
        return _cars_list;
    }

    // Reordenar la lista Dandole prioridad al tipo de Vehiculo
    // recorrer de fin a incio moviendo los carros con el tipo prerencia compatible con el usuario al principio
    Car auxiliar_car;
    int better_coincidences = 0 ;
    char auxiliar_customer_type_str[25];
    char auxiliar_car_type_str[25];

    for(int i= options_number-1; i >= (0 + better_coincidences) ; i--){

        // Normalizar cadenas para la comparacion
        strTolower((*_customers_list)[customer_indx].preferences.type, auxiliar_customer_type_str);
        strTolower(Options[i].type, auxiliar_car_type_str);

        //realizar comparacion SIMPLE
        if(strstr(auxiliar_car_type_str, auxiliar_customer_type_str) || strstr(auxiliar_customer_type_str, auxiliar_car_type_str)){

            // guardar coincidencia
            auxiliar_car= Options[i];
            int auxiliar_indx = options_indx[i];

            // mover el resto de carros hacia delante +1
            for(int j = i; j > better_coincidences; j--){
                    Options[j] = Options[j-1];
                    options_indx[j] = options_indx[j-1];
            }

            // aumentar el numero de coincidencias superiores
            Options[better_coincidences] = auxiliar_car;
            options_indx[better_coincidences] = auxiliar_indx;
            better_coincidences++;
        }

    }

    if(better_coincidences == 0){
        printf("No se encontraron coincidencias de TIPO\n");

    }else{
        int superior_coincidenses= 0;
        char auxiliar_customer_brand_str[25];
        char auxiliar_car_brand_str[25];
        // Reordenar Options desde 0 hasta better_Coincidenses segun la marca del carro
        for(int i=better_coincidences-1; i >= (0+superior_coincidenses); i--){

            // Normalizar marcas para la comparacion
            strTolower((*_customers_list)[customer_indx].preferences.brand, auxiliar_customer_brand_str);
            strTolower(Options[i].brand, auxiliar_car_brand_str);

            //Comparacion Simple
            if( strstr(auxiliar_car_brand_str, auxiliar_customer_brand_str) || strstr(auxiliar_customer_brand_str, auxiliar_car_brand_str) ){

                //guardar coincidencia
                auxiliar_car= Options[i];
                int auxiliar_indx = options_indx[i];

                // mover el resto de carros a la izquierda
                for(int j = i; j > superior_coincidenses; j--){
                    Options[j] = Options[j-1];
                    options_indx[j] = options_indx[j-1];
                }

                // aumentar el numero de coincidencias superiores
                Options[superior_coincidenses] = auxiliar_car;
                options_indx[superior_coincidenses] = auxiliar_indx;
                superior_coincidenses++;
                
            }

        }

        if(better_coincidences == 0) printf("No se encontraron coincidencias de MARCA\n");

    }

    //Mostrar Options
    printf("\nCoincidencias Para El Usuario\n");
    printInventory(Options, options_number);

    //Preguntar al usuario si desea eliminar un vehiculo de la lista
    printf("\nDesea vender uno de los vehiculos de la lista de coincidencias y eliminarlo del inventario?\n");
    printf("(1) SI\n(2) NO\n");
    readIntLoop(" >>> ", &user_option, 1, 2);

    if(user_option == 1){
        
        printf("Ingrese el indice del vehiculo a eliminar\n");
        readIntLoop("Indice >>> ", &user_option, 0, options_number-1);
        _cars_list= removeCarDirect(_cars_list, _cars_number, options_indx[user_option]);

    }

    free(Options);

    return _cars_list;

}
