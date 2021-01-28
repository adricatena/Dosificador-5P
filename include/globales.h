#define encoderPinA 3
#define encoderPinB 4
#define encoderBoton 5

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
