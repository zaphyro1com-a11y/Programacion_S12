#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include "cars.h"

// Estructura de Clientes

typedef struct{

    char name[25];
    char last_name[25];
    int age;
    long int ID;
    Car preferences;

} Customer;

// Imprime la lista de Clientes
void printCustomersList(Customer *_customers_list, int _customers_number);

// Añade un cliente a la lista y al archivo
Customer* addCustomer(Customer *_customers_list, int *_customers_number);

// Eliminar un cliente de la lista y actualiza el archivo
Customer* removeCustomer(Customer *_customers_list, int *_customers_number);

// Guarda un cliente en el archivo
int saveCustomerInFile(Customer *_customer);

// Actualiza el archivo de clientes
int updateCustomersFile(Customer *_customers_list, int _customers_number);

// Guarda la lista de clientes del archivo dentro de la lista
int loadCustomers(Customer *_customers_list, int _customers_number);

#endif