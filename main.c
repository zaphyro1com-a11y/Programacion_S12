//  Sistema de Gestión de Inventario y Clientes (SGIC) //

#include <stdio.h>
#include <stdlib.h>

#include "SGIC.h"
#include "betterio.h"

int main(){

    //////      INICIALIZAR DATOS     ///////

    // VARIABLES PARA LEER ARCHIVOS (metadatos)
    int cars_number, customers_number;

    // Inicializar MetaDatos
    LoadMetadata(&cars_number, &customers_number);

    // Crear Demas Archivos
    makeFiles();

    // VARIABLES //
    int user_option;
    
    Car *car_list = NULL;
    Customer *customers_list = NULL;

    // Iniciar Espacio En Memoria // 
    initializeData(&car_list, &customers_list, &cars_number, &customers_number);
    
    // Inicializar Variables/Estructuras
    loadCars(car_list, cars_number);
    loadCustomers(customers_list, customers_number);

    // Datos De Vendedor
    char seller_name[51];
    double seller_earnings= 0;
    float profit_percentage= 0;

    /////////   INICIALIZAR VENDEDOR     ///////

    printf("Ingrese el nombre del vendedor:\n  ");
    readLine(seller_name, 50);
    printf("Ingrese su porcentaje de ganancia por venta (0-100)\n");
    readFloatLoop("Porcentaje (%) >>> ", &profit_percentage, 0, 100);

    /////////   BUCLE PRINCIPAL DEL PROGRAMA    //////////

    printf("\nSistema de Gestion De Inventario y Clientes\n\n");
    printf("Bienvenido %s\n", seller_name);

    do{

        drawMainMenu();
        readIntLoop("Opcion >>> ", &user_option, 1, 5);

        switch (user_option){
            /* Menu Vehiculos */
            case 1:
                do{

                    drawCarsMenu();
                    readIntLoop("Opcion >>> ", &user_option, 1, 4);
                    car_list= carsMenu(user_option, car_list, &cars_number);

                }while(user_option != 4);

                user_option= 0;

                // Salvar datos
                SaveMetadata(cars_number, customers_number);

                break;
        
            /* Menu Clientes */
            case 2: 
                do{

                drawCustomersMenu();
                readIntLoop("Opcion >>> ", &user_option, 1, 4);
                customers_list= customersMenu(user_option, customers_list, &customers_number);

                }while(user_option != 4);

                // Salvar datos
                SaveMetadata(cars_number, customers_number);

                user_option= 0;

                break;

            /*  Buscar Auto Perfecto */
            case 3:

                car_list= getCustomerCarOptions(car_list, &customers_list, &cars_number, &customers_number, &seller_earnings, profit_percentage);

                break;

            /*  Ganancias */
            case 4:

                printf("\n|| GANANCIAS DEL VENDEDOR ||\n\n");

                if(seller_earnings == 0){
                    printf("No se han realizado ventas\n");
                    break;
                }

                printf("\nGanancias del vendedor %s: $%g\n", seller_name, seller_earnings);

                break;

            /*  Salir */
            case 5:
                printf("Saliendo...\n");

                break;

            default:
                printf("\nComo Llegaste Aqui???\n");

            break;
        }

    }while(user_option != 5);

    // Guardar Metadatos
    printf("Guardando Datos...\n");
    SaveMetadata(cars_number, customers_number);

    // Liberar Memoria
    free(car_list);
    free(customers_list);    

    printf("\nADIOS :3\n");

    return 0;
}