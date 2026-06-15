#ifndef CARS_H
#define CARS_H

// Estructura de Autos
typedef struct{

    int year;
    int state; // 0 nuevo : 1 usado
    char brand[25];
    char model[25];
    char type[25];
    double price;

}Car;

// Añadir Carro al inventario
Car* addCar(Car *_car_list, int *_cars_number);

// Eliminar un carro del inventario
Car* removeCar(Car *_car_list, int *_cars_number);

// Imprimir la lista de carros
void printInventory(Car *_car_list, int _cars_number);

// Guarda un carro en archivo CARS.dat
int saveCarFile(Car *_car);

// Actualiza el contenido del archivo cada vez que se elimina
int updateCarFile(Car *_car_list, int _cars_number);

// Lee cars.dat y guarda los archivos en una lista de Car
int loadCars(Car *_car_list, int _cars_number);

// elimina un vehiculo sin pedir informacion
Car* removeCarDirect(Car *_car_list, int *_cars_number, int car_index);

#endif
