#ifndef SGIC_H
#define SGIC_H

#include "cars.h"
#include "customers.h"

// dibuja el menu principal
void drawMainMenu();

// Dibuja el menu de los vehiculos
void drawCarsMenu();

// Dibuja el menu de los usuarios
void drawCustomersMenu();

// Maneja la logica del menu de los autos
Car* carsMenu(int option, Car *_car_list, int *_car_number);

// Maneja La Logica del menu de los Clientes
Customer* customersMenu(int option, Customer *_customers_list, int *_customers_number);

// Revisa si existen los archivos necesarios, de no ser asi los crea
int makeFiles();

// Inicializa las listas de clientes y carros
int initializeData(Car **_cars_list, Customer **_customers_list, int *_cars_number, int *_customers_number);

// Abrir archivo de datos principales y sobrescribir
int SaveMetadata(int _cars_number, int _customers_number);

// Lee el archivo meta y devuelve los valores a sus variables correspondientes
int LoadMetadata(int *_cars_number, int *_customers_number);

// Copia una cadena en minusculas
void strTolower(char string[], char new_str[]);

// Analiza las preferencias de un cliente y las compara con el inventario actual
Car* getCustomerCarOptions(Car *_cars_list, Customer **_customers_list, int *_cars_number, int *_customers_number);


#endif