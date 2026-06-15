#ifndef BETTERIO_H
#define BETTERIO_H

/*  // FUNCIONES DE ENTRADA //  */

// Lee una string de n+1 caracteres una sola vez.
void readLine(char str[], int n);

// Lee una string de 10 caracteres y lo transforma a entero.
int readInt(int *var);

// Lee una string de 10 caracteres y lo transforma a entero.
// Ademas verifica su rango de valor.
int readIntRange(int *var, int min, int max);

// Lee una string de 10 caracteres y lo transforma a entero.
// Ademas verifica su rango de valor y solicita el numero hasta que sea valido.
void readIntLoop(char msg[], int *var, int min, int max);

// Lee una string de 10 caracteres y lo transforma a long int.
int readLongInt(long int *var);

// Lee una string de 10 caracteres y lo transforma a long int.
// Ademas verifica su rango de valor.
int readLongIntRange(long int *var, long int min, long int max);

// Lee una string de 10 caracteres y lo transforma a long int.
// Ademas verifica su rango de valor y solicita el numero hasta que sea valido.
void readLongIntLoop(char msg[], long int *var, long int min, long int max);

// Lee una string de 10 caracteres y lo transforma a flotante.
int readFloat(float *var);

// Lee una string de 10 caracteres y lo transforma a flotante.
// Ademas verifica su rango de valor.
int readFloatRange(float *var, float min, float max);

// Lee una string de 10 caracteres y lo transforma a flotante.
// Ademas verifica su rango de valor y solicita el numero hasta que sea valido.
void readFloatLoop(char msg[], float *var, float min, float max );

// Lee una string de 10 caracteres y lo transforma a double.
int readDouble(double *var);

// Lee una string de 10 caracteres y lo transforma a double.
// Ademas verifica su rango de valor.
int readDoubleRange(double *var, double min, double max);

// Lee una string de 10 caracteres y lo transforma a double.
// Ademas verifica su rango de valor y solicita el numero hasta que sea valido.
void readDoubleLoop(char msg[], double *var, double min, double max );

/*  // FUNCIONES DE SALIDA //  */

// Dibuja un menu en pantalla
void drawMenu(char *title, char **options, int options_num);
#endif