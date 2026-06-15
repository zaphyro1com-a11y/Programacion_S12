#include <stdio.h>
#include <stdlib.h>

#include "customers.h"
#include "betterio.h"
#include "cars.h"

void printCustomersList(Customer *_customers_list, int _customers_number){

    if(_customers_number < 1){
        printf("\nIngrese primero al menos un cliente\n");
        return;
    }

    printf("\n\tLista De Clientes\n");
    printf("Numero de Clientes: %d \n", _customers_number);

    printf("====================================================================================\n");
    printf(" %-6s %-15s %-15s%-4s\t    %-11s %-25s \n",
            "INDICE", "NOMBRE", "APELLIDO", "EDAD", "ID", "COCHE FAVORITO");
    printf("------------------------------------------------------------------------------------\n");

    for(int i= 0; i < _customers_number; i++){

        printf("   %d\t%-15s %-15s %d\t%ld\t %-25s \n",
                i,
                _customers_list[i].name,
                _customers_list[i].last_name,
                _customers_list[i].age,
                _customers_list[i].ID,
                _customers_list[i].preferences.model
        );

    }
    
    printf("\n====================================================================================\n");

    printf("Presione ENTER para continuar...\n");
    getchar();

}

// Añade un cliente a la lista y al archivo
Customer* addCustomer(Customer *_customers_list, int *_customers_number){

    printf("\n\tAñadir Un Cliente\n");

    // Puntero temporal
    Customer *new_p= realloc(_customers_list, sizeof(Customer) * (*_customers_number+1));

    // Validar asignacion de memoria 
    if (new_p == NULL) {
        printf("ERROR: No se pudo redimensionar memoria\n");
        return _customers_list; // devolvemos el puntero original en caso de errror 
    }

    // Actualizar el puntero de la lista si todo salio bien
    _customers_list= new_p;

    // Asignar Valores

    printf("Ingrese el nombre del cliente.\n");
    printf(" >>> "); readLine(_customers_list[*_customers_number].name, 24);

    printf("Ingrese el apellido del cliente.\n");
    printf(" >>> "); readLine(_customers_list[*_customers_number].last_name, 24);

    printf("Ingrese la edad del cliente.\n");
    readIntLoop("Edad >>> ", &(_customers_list[*_customers_number].age), 18, 100 );

    printf("Ingrese el ID del cliente (9 digitos).\n");
    readLongIntLoop("ID >>> ", &(_customers_list[*_customers_number].ID), 100000000, 999999999);

    printf("Ingrese la marca preferida del cliente.\n");
    printf(" >>> "); readLine(_customers_list[*_customers_number].preferences.brand, 24);

    printf("Ingrese el modelo preferido del cliente.\n");
    printf(" >>> "); readLine(_customers_list[*_customers_number].preferences.model, 24);

    printf("Ingrese el tipo de auto preferido del cliente.\n");
    printf(" >>> "); readLine(_customers_list[*_customers_number].preferences.type, 24);

    printf("Ingrese el anio de preferencia.\n");
    readIntLoop("Anio >>> ", &(_customers_list[*_customers_number].preferences.year), 1985, 2026);

    printf("Ingrese el estado del vehiculo de preferencia (1) Nuevo / (2) Viejo.\n");
    readIntLoop("Estado >>> ", &(_customers_list[*_customers_number].preferences.state), 1, 2);

    printf("Ingrese el precio adecuado para el cliente.\n");
    readDoubleLoop("Precio >>> ", &(_customers_list[*_customers_number].preferences.price), 3000, 400000);

    // Guardar Cliente en el Archivo
    saveCustomerInFile(&(_customers_list[*_customers_number]));

    // Aumentar numero de Clientes
    (*_customers_number)++;

    printf("\n\t=== CLIENTE AGREGADO A LA LISTA ===\n");

    // Regresar el puntero a la lista
    return _customers_list;

}

// Eliminar un cliente de la lista y actualiza el archivo
Customer* removeCustomer(Customer *_customers_list, int *_customers_number){

    if(*_customers_number < 1){
        printf("Primero agregue al menos un cliente.\n");
        return _customers_list;

    }

    int customer_indx;

    printf("\n\tEliminar un Cliente\n");

    printCustomersList(_customers_list, *_customers_number);

    printf("Ingrese el indice del cliente.\n");
    readIntLoop("Indice >>> ", &customer_indx, 0, ((*_customers_number) - 1) );

    for(int i= customer_indx; i < ((*_customers_number)-1); i++ ){
        _customers_list[i]= _customers_list[i+1];

    }

    // disminuir el numero de clientes
    (*_customers_number)--;

    int new_size = (*_customers_number == 0)? 1: *_customers_number;

    Customer *new_p = realloc(_customers_list, sizeof(Customer)* new_size);

    // Validar asignacion de memoria 
    if (new_p == NULL) {
        printf("ERROR: No se pudo redimensionar memoria\n");
        return _customers_list; // devolvemos el puntero viejo 
    }

    _customers_list= new_p;

    // Actualizar el archivo de clientes
    updateCustomersFile(_customers_list, *_customers_number);

    printf("\n\t=== CLIENTE REMOVIDO DE LA LISTA ===\n");

    // Devolver nuevo puntero a lista de clientes
    return _customers_list;

}

// Guarda un cliente en el archivo
int saveCustomerInFile(Customer *_customer){

    FILE *customers_F= fopen("Data/customers.dat", "ab");

    if(customers_F == NULL){
        printf("\nERROR. No se pudo abrir el archivo customers.dat\n");
        return 1;

    }

    if( fwrite(_customer, sizeof(Customer), 1, customers_F) != 1 ){
        printf("\nERROR. No se logro guardar el cliente dentro del archivo\n");
    }

    fclose(customers_F);

    return 0;

}

// Actualiza el archivo de clientes
int updateCustomersFile(Customer *_customers_list, int _customers_number){

    FILE *customers_F= fopen("Data/customers.dat", "wb");

    if(customers_F == NULL){
        printf("\nERROR. No se pudo abrir el archivo customers.dat\n");
        return 1;

    }

    if( fwrite(_customers_list, sizeof(Customer), _customers_number, customers_F) != _customers_number){
        printf("\nERROR.No se logro actualizar el archivo\n");
    }

    fclose(customers_F);

    return 0;

}

// Guarda la lista de clientes del archivo dentro de la lista
int loadCustomers(Customer *_customers_list, int _customers_number){

    FILE *customers_F= fopen("Data/customers.dat", "rb");

    if(customers_F == NULL){
        printf("\nERROR. No se pudo abrir el archivo customers.dat\n");
        return 1;

    }

    if( fread(_customers_list, sizeof(Customer), _customers_number, customers_F) != _customers_number ){
        printf("\nERROR. No se logro obtener los datos de los clientes\n");

    }

    fclose(customers_F);

    return 0;

}