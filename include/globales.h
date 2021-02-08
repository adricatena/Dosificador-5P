#include <HX711.h>

#define encoderPinA 2
#define encoderPinB 3
#define encoderBoton 4
#define s1_trig 5 // Ultrasonido 1
#define s1_echo 6
#define s2_trig 7 // Ultrasonido 2
#define s2_echo 8
#define s3_trig 9 // Ultrasonido 3
#define s3_echo 10
#define s4_trig 11 // Ultrasonido 4
#define s4_echo 12
#define s5_trig 13 // Ultrasonido 5
#define s5_echo 48
#define BTN_verde 14
#define BTN_negro 15
#define DT1 22 // Celda 1
#define SCK1 23
#define DT2 24 // Celda 2
#define SCK2 25
#define DT3 26 // Celda 3
#define SCK3 27
#define DT4 28 // Celda 4
#define SCK4 29
#define DT5 30 // Celda 5
#define SCK5 31
#define BOMBA 32
#define EV1 33
#define LUZ1r 34
#define LUZ1v 35
#define EV2 36
#define LUZ2r 37
#define LUZ2v 38
#define EV3 39
#define LUZ3r 40
#define LUZ3v 41
#define EV4 42
#define LUZ4r 43
#define LUZ4v 44
#define EV5 45
#define LUZ5r 46
#define LUZ5v 47

HX711 balanza1, balanza2, balanza3, balanza4, balanza5;

unsigned int flag = 0;
unsigned int seleccion = 1; // Seleccion de item
unsigned int cantidad = 2;  // Cantidad de items de un menu

unsigned int pesoNuevo;
int d1 = 0, d2 = 0, d3 = 0, d4 = 0, digito = 1;

const int maximoRecetas = 12;
struct sReceta
{
    unsigned int numeroReceta;
    unsigned int pesoProducto;
    unsigned int volumenProducto;
};
sReceta aRecetas[maximoRecetas];
int recetasGuardadas = 0;
int tamanoEstructura;
int paginaRecetas = 1;
int borrarReceta;

int duracion1, duracion2, duracion3, duracion4, duracion5;
float distancia1, distancia2, distancia3, distancia4, distancia5;

int i = 0;

void recetasAMostrar();