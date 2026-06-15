#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cars.h"
#include "betterio.h"

Car* addCar(Car *_car_list, int *_cars_number){

    char buffer[25];

    printf("\n\tAgregar Auto al Inventario\n\n");

    // Crear nuevo puntero de car_list
    Car *new_p= realloc(_car_list, sizeof(Car) * (*_cars_number+1));
    
    // Validar asignacion de memoria 
    if (new_p == NULL) {
        printf("ERROR: No se pudo redimensionar memoria\n");
        return _car_list; // devolvemos el puntero viejo 
    }

    // reasignar valor a car_list
    _car_list= new_p;

    // Asignar Valores

    printf("Ingrese la marca del auto\n");
    printf(">>> "); readLine(buffer, 24);
    strcpy(_car_list[*_cars_number].brand, buffer);  

    printf("Ingrese el modelo del auto\n");
    printf(">>> "); readLine(buffer, 24);
    strcpy(_car_list[*_cars_number].model, buffer); 

    printf("Ingrese el tipo de coche\n");
    printf(">>> "); readLine(buffer, 24);
    strcpy(_car_list[*_cars_number].type, buffer);

    printf("Ingrese de que anio es el vehiculo\n");
    readIntLoop("Anio >>> ", &(_car_list[*_cars_number].year), 1965, 2026);

    printf("Ingrese el estado del vehiculo (1) Nuevo / (2) Usado\n");
    readIntLoop("Estado >>> ", &(_car_list[*_cars_number].state), 1, 2);

    printf("Ingrese el precio de venta del vehiculo ($)\n");
    readDoubleLoop("Precio >>> ", &(_car_list[*_cars_number].price), 1000.0, 400000.0);

    // Guardar el carro en archivo
    saveCarFile(&(_car_list[*_cars_number]));

    // Aumentar el numero de vehiculos
    (*_cars_number)++;

    printf("\n\t=== CARRO AÑADIDO AL INVENTARIO ===\n");

    // Devolver nuevo puntero a car_list
    return _car_list;

}

Car* removeCar(Car *_car_list, int *_cars_number){

    if(*_cars_number == 0){
        printf("\nPrimero Agregue Al Menos Un Carro\n");
        return _car_list;
    }

    int car_indx;

    printf("\n\tEliminar Auto del Inventario\n");

    // Mostrar Lista Con Nombres de los vehiculos
    printInventory(_car_list, *_cars_number);

    printf("Ingrese el Indice del auto\n");
    readIntLoop("Indice >>> ", &car_indx, 0, ((*_cars_number)-1));

    for(int i = car_indx; i < ((*_cars_number)-1); i++ ){
        _car_list[i] = _car_list[i+1];
    }

    // disminuir la cantidad de vehiculos
    (*_cars_number)--;

    int new_size = (*_cars_number > 0)? (*_cars_number) : 1;

    //Reasignar memoria
    Car *new_p= realloc(_car_list, sizeof(Car) * new_size);

    // Validar asignacion de memoria 
    if (new_p == NULL) {
        printf("ERROR: No se pudo redimensionar memoria\n");
        return _car_list; // devolvemos el puntero viejo 
    }

    _car_list= new_p;

    // Sobreescribir archivo
    updateCarFile(_car_list, *_cars_number);

    printf("\n\t=== CARRO REMOVIDO DEL INVENTARIO ===\n");

    // Devolver nuevo puntero a car_list
    return _car_list;

}

void printInventory(Car *_car_list, int _cars_number){

    if(_cars_number == 0){
        printf("\nPrimero Agregue Al Menos Un Carro\n");
        return;
    }

    printf("\n\tLista De Carros\n");
    printf("Total de carros: %d \n", _cars_number);

    printf("========================================================================================================================\n");
    printf(" %-6s  %-25s %-25s %-8s %-25s %-10s %-10s \n",
            "INDICE","MARCA", "MODELO", "ANIO", "TIPO", "ESTADO", "PRECIO");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    for(int i=0; i < _cars_number; i++){

        printf(" %d\t %-25s %-25s %d     %-25s  %-9s %-10.2lf \n",
                i,
                (_car_list[i].brand),
                (_car_list[i].model),
                (_car_list[i].year),
                (_car_list[i].type),
                ((_car_list[i].state == 1)? "Nuevo" : "Usado"),
                (_car_list[i].price));

    }
    printf("\n========================================================================================================================\n");

    printf("presione ENTER para continuar...");
    getchar();

}

int saveCarFile(Car *_car){

    FILE *cars_F= fopen("Data/cars.dat", "ab");

    if(cars_F == NULL) {
        printf("\nERROR. No se pudo abrir el archivo cars.dat.\n");
        return 1;

    }

    if (fwrite(_car, sizeof(Car), 1, cars_F) != 1) {
        printf("ERROR: no se pudo guardar el auto.\n");
    
    }

    fclose(cars_F);

    return 0;

}

int updateCarFile(Car *_car_list, int _cars_number){

    FILE *cars_F= fopen("Data/cars.dat", "wb");

    if(cars_F == NULL) {
        printf("\nERROR. No se pudo abrir el archivo cars.dat.\n");
        return 1;

    }

    if(fwrite(_car_list, sizeof(Car), _cars_number, cars_F) !=  _cars_number){

        printf("ERROR: no se pudo actualizar el archivo.\n");

    }

    fclose(cars_F);

    return 0;
}

int loadCars(Car *_car_list, int _cars_number){

    FILE *cars_F= fopen("Data/cars.dat", "rb");

    if(cars_F == NULL) {
        printf("\nERROR. No se pudo abrir el archivo cars.dat.\n");
        return 1;

    }

    fread(_car_list, sizeof(Car), _cars_number, cars_F);

    fclose(cars_F);
    return 0;

}

Car* removeCarDirect(Car *_car_list, int *_cars_number, int car_index){

    if(*_cars_number == 0){
        printf("\nPrimero Agregue Al Menos Un Carro\n");
        return _car_list;
    }

    for(int i = car_index; i < ((*_cars_number)-1); i++ ){
        _car_list[i] = _car_list[i+1];
    }

    // disminuir la cantidad de vehiculos
    (*_cars_number)--;

    int new_size = (*_cars_number > 0)? (*_cars_number) : 1;

    //Reasignar memoria
    Car *new_p= realloc(_car_list, sizeof(Car) * new_size);

    // Validar asignacion de memoria 
    if (new_p == NULL) {
        printf("ERROR: No se pudo redimensionar memoria\n");
        return _car_list; // devolvemos el puntero viejo 
    }

    _car_list= new_p;

    // Sobreescribir archivo
    updateCarFile(_car_list, *_cars_number);

    printf("\n\t=== CARRO REMOVIDO DEL INVENTARIO ===\n");

    // Devolver nuevo puntero a car_list
    return _car_list;

}