#include <HX711.h>

#define encoderPinA 2
#define encoderPinB 3
#define encoderBoton 4
#define BTN_verde 14
#define BTN_negro 15
#define DT1 22  // Celda 1
#define SCK1 23
#define DT2 24  // Celda 2
#define SCK2 25
#define DT3 26  // Celda 3
#define SCK3 27
#define DT4 28  // Celda 4
#define SCK4 29
#define DT5 30  // Celda 5
#define SCK5 31
#define BOMBA 32
#define EV1 33
#define LUZ1r 34
#define LUZ2v 35

HX711 balanza1, balanza2, balanza3, balanza4, balanza5;

unsigned int flag = 0;
unsigned int seleccion = 1; // Seleccion de item
unsigned int cantidad = 2;  // Cantidad de items de un menu

const int maximoRecetas = 10;
struct sReceta
{
    unsigned int numeroReceta;
    unsigned int pesoProducto;
    unsigned int volumenProducto;
};
sReceta aRecetas[maximoRecetas];
int recetasGuardadas = 0;
int tamanoEstructura;

int i = 0;
