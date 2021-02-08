#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/52, /* data=*/51, /* CS=*/53, /* reset=*/50);

int alturaConTitulo;
int altoFila;
int filas;

void setupPantalla()
{
    u8g2.begin();
    u8g2.clearBuffer();               // clear the internal memory
    u8g2.setFont(u8g2_font_fub42_tr); // choose a suitable font
    int centroX = (u8g2.getDisplayWidth() - u8g2.getStrWidth("IDM")) / 2;
    int centroY = (u8g2.getDisplayHeight() + u8g2.getAscent()) / 2;
    u8g2.drawStr(centroX, centroY, "IDM"); // write something to the internal memory
    u8g2.sendBuffer();                     // transfer internal memory to the display
}

void drawInicio()
{
    u8g2.clearBuffer();
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_profont12_tr);
    u8g2.drawStr(1, u8g2.getAscent() + 1, "Pulse cualquier tecla");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 2, "para continuar.");
    u8g2.sendBuffer();
}

void drawMenuPrincipal()
{
    u8g2.clearBuffer();
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_profont17_tr);
    alturaConTitulo = u8g2.getDisplayHeight() - u8g2.getAscent() + 1;
    altoFila = alturaConTitulo / 3 - 1;
    int centroX = (u8g2.getDisplayWidth() - u8g2.getStrWidth("MENU PRINCIPAL")) / 2;
    int x1 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("RECETAS")) / 2;
    int x2 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("MARCHA")) / 2;
    int x3 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("LAVADO")) / 2;
    u8g2.drawStr(centroX, u8g2.getAscent() + 1, "MENU PRINCIPAL");
    u8g2.drawHLine(0, u8g2.getAscent() + 2, u8g2.getDisplayWidth());
    u8g2.drawStr(x1, u8g2.getAscent() + 1 + altoFila, "RECETAS");
    u8g2.drawStr(x2, u8g2.getAscent() + 1 + altoFila * 2, "MARCHA");
    u8g2.drawStr(x3, u8g2.getAscent() + 1 + altoFila * 3, "LAVADO");
    u8g2.sendBuffer();
}

void drawSelector(int cantidad, int seleccion)
{
    int alto = u8g2.getAscent();
    int y1, y2, y3, y4;
    u8g2.setFont(u8g2_font_profont17_tr);
    alturaConTitulo = u8g2.getDisplayHeight() - u8g2.getAscent() + 1;
    switch (cantidad)
    {
    case 2:
        y1 = 1 + (alturaConTitulo / 2 - u8g2.getAscent() * 0.5);
        y2 = 1 + (alturaConTitulo / 2 + u8g2.getAscent() * 1.5);
        if (seleccion == 1)
        {
            u8g2.drawBox(1, y1, alto, alto);
            u8g2.drawFrame(1, y2, alto, alto);
            u8g2.sendBuffer();
        }
        else if (seleccion == 2)
        {
            u8g2.drawFrame(1, y1, alto, alto);
            u8g2.drawBox(1, y2, alto, alto);
            u8g2.sendBuffer();
        }
        break;
    case 3:
        y1 = u8g2.getAscent() + 1 + ((alturaConTitulo - 1) / 3) - alto; // desfazaje del titulo + division dinamica - altura del cuadrado
        y2 = u8g2.getAscent() + 1 + ((alturaConTitulo - 1) / 3) * 2 - alto;
        y3 = u8g2.getAscent() + 1 + ((alturaConTitulo - 1) / 3) * 3 - alto;
        if (seleccion == 1)
        {
            u8g2.drawBox(1, y1, alto, alto);
            u8g2.drawFrame(1, y2, alto, alto);
            u8g2.drawFrame(1, y3, alto, alto);
            u8g2.sendBuffer();
        }
        else if (seleccion == 2)
        {
            u8g2.drawFrame(1, y1, alto, alto);
            u8g2.drawBox(1, y2, alto, alto);
            u8g2.drawFrame(1, y3, alto, alto);
            u8g2.sendBuffer();
        }
        else if (seleccion == 3)
        {
            u8g2.drawFrame(1, y1, alto, alto);
            u8g2.drawFrame(1, y2, alto, alto);
            u8g2.drawBox(1, y3, alto, alto);
            u8g2.sendBuffer();
        }
        break;
    case 4:
        u8g2.setFont(u8g2_font_profont12_tr);
        alturaConTitulo = u8g2.getDisplayHeight() - u8g2.getAscent() + 1;
        alto = u8g2.getAscent();
        altoFila = alturaConTitulo / 4 - 1;
        y1 = alto + 6 + 0;
        y2 = alto + 6 + altoFila;
        y3 = alto + 6 + altoFila * 2;
        y4 = alto + 6 + altoFila * 3;
        if (seleccion == 1)
        {
            u8g2.drawBox(1, y1, alto, alto);
            u8g2.drawFrame(1, y2, alto, alto);
            u8g2.drawFrame(1, y3, alto, alto);
            u8g2.drawFrame(1, y4, alto, alto);
            u8g2.sendBuffer();
        }
        else if (seleccion == 2)
        {
            u8g2.drawFrame(1, y1, alto, alto);
            u8g2.drawBox(1, y2, alto, alto);
            u8g2.drawFrame(1, y3, alto, alto);
            u8g2.drawFrame(1, y4, alto, alto);
            u8g2.sendBuffer();
        }
        else if (seleccion == 3)
        {
            u8g2.drawFrame(1, y1, alto, alto);
            u8g2.drawFrame(1, y2, alto, alto);
            u8g2.drawBox(1, y3, alto, alto);
            u8g2.drawFrame(1, y4, alto, alto);
            u8g2.sendBuffer();
        }
        else if (seleccion == 4)
        {
            u8g2.drawFrame(1, y1, alto, alto);
            u8g2.drawFrame(1, y2, alto, alto);
            u8g2.drawFrame(1, y3, alto, alto);
            u8g2.drawBox(1, y4, alto, alto);
            u8g2.sendBuffer();
        }
        break;
    default:
        break;
    }
}

void drawMenuRecetas()
{
    u8g2.clearBuffer();
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_profont12_tr);
    alturaConTitulo = u8g2.getDisplayHeight() - u8g2.getAscent() + 1;
    altoFila = alturaConTitulo / 4 - 1;
    int centroX = (u8g2.getDisplayWidth() - u8g2.getStrWidth("MENU RECETAS")) / 2;
    int x1 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("AGREGAR RECETA")) / 2;
    int x2 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("MOSTRAR RECETAS")) / 2;
    int x3 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("ELIMINAR RECETA")) / 2;
    int x4 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("MENU PRINCIPAL")) / 2;
    u8g2.drawStr(centroX, u8g2.getAscent() + 1, "MENU RECETAS");
    u8g2.drawHLine(0, u8g2.getAscent() + 2, u8g2.getDisplayWidth());
    u8g2.drawStr(x1, u8g2.getAscent() + 1 + altoFila, "AGREGAR RECETA");
    u8g2.drawStr(x2, u8g2.getAscent() + 1 + altoFila * 2, "MOSTRAR RECETAS");
    u8g2.drawStr(x3, u8g2.getAscent() + 1 + altoFila * 3, "ELIMINAR RECETA");
    u8g2.drawStr(x4, u8g2.getAscent() + 1 + altoFila * 4, "MENU PRINCIPAL");
    u8g2.sendBuffer();
}

void drawMaximoRecetas()
{
    u8g2.clearBuffer();
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_profont12_tr);
    u8g2.drawStr(1, u8g2.getAscent() + 1, "SE ALCANZO EL LIMITE");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 2, "DE RECETAS GUARDADAS.");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 4, "ELIMINE ALGUNA RECETA");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 5, "SI DESEA CONTINUAR.");
    u8g2.sendBuffer();
}

void drawInstruccionesAgregarReceta()
{
    u8g2.clearBuffer();
    u8g2.clearDisplay();
    //u8g2.setFont(u8g2_font_profont10_tr); // 9 renglones
    u8g2.setFont(u8g2_font_profont11_tr); // 8 renglones
    u8g2.drawStr(1, u8g2.getAscent() + 1, "Ubique el envase en");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 2, "posicion de llenado y");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 3, "sin perdidas.");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 4, "Mantenga pulsado el");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 5, "boton verde hasta el");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 6, "nivel que usted desee");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 7, "VERDE - continuar");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 8, "NEGRO - cancelar");
    u8g2.sendBuffer();
}

void drawPrueba()
{
    u8g2.begin();
    u8g2.clearBuffer();                   // clear the internal memory
    u8g2.setFont(u8g2_font_profont17_tr); // choose a suitable font
    int centroX = (u8g2.getDisplayWidth() - u8g2.getStrWidth("PRUEBA")) / 2;
    int centroY = (u8g2.getDisplayHeight() + u8g2.getAscent()) / 2;
    u8g2.drawStr(centroX, centroY, "PRUEBA"); // write something to the internal memory
    u8g2.sendBuffer();
}

void drawMensajeDestarando()
{
    u8g2.clearBuffer();
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_profont12_tr);
    u8g2.drawStr(1, u8g2.getAscent() + 1, "NO APOYE NINGUN");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 2, "ENVASE SOBRE LA");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 3, "BALANZA.");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 5, "DESTARANDO...");
    u8g2.sendBuffer();
}

void drawMensajeCentrado(String palabra)
{
    u8g2.clearBuffer();                   // clear the internal memory
    u8g2.setFont(u8g2_font_profont17_tr); // choose a suitable font
    char caracteres[palabra.length() + 1];
    palabra.toCharArray(caracteres, palabra.length() + 1);
    int centroX = (u8g2.getDisplayWidth() - u8g2.getStrWidth(caracteres)) / 2;
    int centroY = (u8g2.getDisplayHeight() + u8g2.getAscent()) / 2;
    u8g2.drawStr(centroX, centroY, caracteres); // write something to the internal memory
    u8g2.sendBuffer();
}

void drawMensajeNuevoPeso(int d1, int d2, int d3, int d4, int digito)
{
    String peso = "PESO: " + String(d1) + " " + String(d2) + " " + String(d3) + " " + String(d4) + " gr";
    char caracteres[peso.length() + 1];
    peso.toCharArray(caracteres, peso.length() + 1);
    u8g2.clearBuffer();
    //u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_profont12_tr);
    alturaConTitulo = u8g2.getDisplayHeight() - u8g2.getAscent() + 1;
    altoFila = alturaConTitulo / 3 - 1;
    int centroX = (u8g2.getDisplayWidth() - u8g2.getStrWidth("RECETA NUEVA")) / 2;
    int x1 = (u8g2.getDisplayWidth() - u8g2.getStrWidth(caracteres)) / 2;
    int x2 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("VERDE - Aceptar")) / 2;
    int x3 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("NEGRO - Cancelar")) / 2;
    int ancho = u8g2.getStrWidth("9 ");
    u8g2.drawStr(centroX, u8g2.getAscent() + 1, "RECETA NUEVA");
    u8g2.drawHLine(0, u8g2.getAscent() + 2, u8g2.getDisplayWidth());
    u8g2.drawStr(x1, u8g2.getAscent() + 1 + altoFila, caracteres);
    x1 = x1 + u8g2.getStrWidth("PESO: ");
    u8g2.drawHLine(x1 + ancho * (digito - 1) - 2, u8g2.getAscent() + 1 + altoFila + 1, ancho - 3);
    u8g2.drawStr(x2, u8g2.getAscent() + 1 + altoFila * 2, "VERDE - Aceptar");
    u8g2.drawStr(x3, u8g2.getAscent() + 1 + altoFila * 3, "NEGRO - Cancelar");
    u8g2.sendBuffer();
}

void drawErrorAgregarReceta()
{
    u8g2.clearBuffer();
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_profont12_tr);
    alturaConTitulo = u8g2.getDisplayHeight() - u8g2.getAscent() + 1;
    filas = 5;
    altoFila = alturaConTitulo / filas - 1;
    int centroX = (u8g2.getDisplayWidth() - u8g2.getStrWidth("ERROR")) / 2;
    int x1 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("NO PUEDE AGREGAR")) / 2;
    int x2 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("RECETAS SIN PESO")) / 2;
    u8g2.drawStr(centroX, u8g2.getAscent() + 1, "ERROR");
    u8g2.drawHLine(0, u8g2.getAscent() + 2, u8g2.getDisplayWidth());
    u8g2.drawStr(x1, u8g2.getAscent() + 1 + altoFila * 2, "NO PUEDE AGREGAR");
    u8g2.drawStr(x2, u8g2.getAscent() + 1 + altoFila * 3, "RECETAS SIN PESO");
    u8g2.sendBuffer();
}

void drawRecetaCorrecta(int nroReceta)
{
    String cadena = "RECETA Nro " + String(nroReceta);
    char caracteres[cadena.length() + 1];
    cadena.toCharArray(caracteres, cadena.length() + 1);
    u8g2.clearBuffer();
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_profont12_tr);
    filas = 5;
    altoFila = u8g2.getDisplayHeight() / filas - 1;
    int x1 = (u8g2.getDisplayWidth() - u8g2.getStrWidth(caracteres)) / 2;
    int x2 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("GUARDADA CON EXITO")) / 2;
    u8g2.drawStr(x1, u8g2.getAscent() + 1 + altoFila * 2, caracteres);
    u8g2.drawStr(x2, u8g2.getAscent() + 1 + altoFila * 4, "GUARDADA CON EXITO");
    u8g2.sendBuffer();
}

void drawSinRecetas()
{
    u8g2.clearBuffer();
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_profont12_tr);
    alturaConTitulo = u8g2.getDisplayHeight() - u8g2.getAscent() + 1;
    filas = 5;
    altoFila = alturaConTitulo / filas - 1;
    int centroX = (u8g2.getDisplayWidth() - u8g2.getStrWidth("ERROR")) / 2;
    int x1 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("NO HAY RECETAS")) / 2;
    int x2 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("GUARDADAS")) / 2;
    u8g2.drawStr(centroX, u8g2.getAscent() + 1, "ERROR");
    u8g2.drawHLine(0, u8g2.getAscent() + 2, u8g2.getDisplayWidth());
    u8g2.drawStr(x1, u8g2.getAscent() + 1 + altoFila * 2, "NO HAY RECETAS");
    u8g2.drawStr(x2, u8g2.getAscent() + 1 + altoFila * 3, "GUARDADAS");
    u8g2.sendBuffer();
}

void drawMostrarRecetas(int recetas[], int pagina, int aux)
{
    String cadena;
    char caracteres[22];
    int x, ancho = u8g2.getDisplayWidth();
    u8g2.clearBuffer();
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_profont12_tr);
    alturaConTitulo = u8g2.getDisplayHeight() - u8g2.getAscent() + 1;
    filas = 5;
    altoFila = alturaConTitulo / filas - 1;
    cadena = "RECETAS  -  pag " + String(pagina) + "/3";
    char titulo[cadena.length() + 1];
    cadena.toCharArray(titulo, cadena.length() + 1);
    x = (ancho - u8g2.getStrWidth(titulo)) / 2;
    u8g2.drawStr(x, u8g2.getAscent() + 1, titulo);
    u8g2.drawHLine(0, u8g2.getAscent() + 2, u8g2.getDisplayWidth());
    for (int i = 0; i < 4; i++)
    {
        cadena = "Receta Nro " + String(i + 1 + aux) + ": ";
        if (recetas[i] < 1 || recetas[i] > 9999)
            cadena += "VACIA   ";
        else
            cadena += String(recetas[i]) + " gr";
        cadena.toCharArray(caracteres, cadena.length() + 1);
        u8g2.drawStr(1, u8g2.getAscent() + 2 + altoFila * (i + 1), caracteres);
    }
    x = ancho - u8g2.getStrWidth("Verde/Negro - Volver");
    u8g2.drawStr(x - 1, u8g2.getDisplayHeight() - 1, "Verde/Negro - Volver");
    u8g2.sendBuffer();
}

void drawEliminarReceta(int d1, int d2, int digito)
{
    String receta = "RECETA Nro: " + String(d1) + " " + String(d2);
    char caracteres[receta.length() + 1];
    receta.toCharArray(caracteres, receta.length() + 1);
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_profont12_tr);
    alturaConTitulo = u8g2.getDisplayHeight() - u8g2.getAscent() + 1;
    altoFila = alturaConTitulo / 3 - 1;
    int centroX = (u8g2.getDisplayWidth() - u8g2.getStrWidth("ELIMINAR RECETA")) / 2;
    int x1 = (u8g2.getDisplayWidth() - u8g2.getStrWidth(caracteres)) / 2;
    int x2 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("VERDE - Aceptar")) / 2;
    int x3 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("NEGRO - Cancelar")) / 2;
    int ancho = u8g2.getStrWidth("9 ");
    u8g2.drawStr(centroX, u8g2.getAscent() + 1, "ELIMINAR RECETA");
    u8g2.drawHLine(0, u8g2.getAscent() + 2, u8g2.getDisplayWidth());
    u8g2.drawStr(x1, u8g2.getAscent() + 1 + altoFila, caracteres);
    x1 = x1 + u8g2.getStrWidth("RECETA Nro: ");
    u8g2.drawHLine(x1 + ancho * (digito - 1) - 2, u8g2.getAscent() + 1 + altoFila + 1, ancho - 3);
    u8g2.drawStr(x2, u8g2.getAscent() + 1 + altoFila * 2, "VERDE - Aceptar");
    u8g2.drawStr(x3, u8g2.getAscent() + 1 + altoFila * 3, "NEGRO - Cancelar");
    u8g2.sendBuffer();
}

void drawErrorEliminarReceta()
{
    u8g2.clearBuffer();
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_profont12_tr);
    alturaConTitulo = u8g2.getDisplayHeight() - u8g2.getAscent() + 1;
    filas = 5;
    altoFila = alturaConTitulo / filas - 1;
    int centroX = (u8g2.getDisplayWidth() - u8g2.getStrWidth("ERROR")) / 2;
    int x1 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("NO EXISTE EL")) / 2;
    int x2 = (u8g2.getDisplayWidth() - u8g2.getStrWidth(" Nro DE RECETA")) / 2;
    u8g2.drawStr(centroX, u8g2.getAscent() + 1, "ERROR");
    u8g2.drawHLine(0, u8g2.getAscent() + 2, u8g2.getDisplayWidth());
    u8g2.drawStr(x1, u8g2.getAscent() + 1 + altoFila * 2, "NO EXISTE EL");
    u8g2.drawStr(x2, u8g2.getAscent() + 1 + altoFila * 3, "Nro DE RECETA");
    u8g2.sendBuffer();
}

void drawErrorRecetaVacia()
{
    u8g2.clearBuffer();
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_profont12_tr);
    alturaConTitulo = u8g2.getDisplayHeight() - u8g2.getAscent() + 1;
    filas = 3;
    altoFila = (alturaConTitulo / filas) - 1;
    int centroX = (u8g2.getDisplayWidth() - u8g2.getStrWidth("ERROR")) / 2;
    int x1 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("RECETA VACIA")) / 2;
    u8g2.drawStr(centroX, u8g2.getAscent() + 1, "ERROR");
    u8g2.drawHLine(0, u8g2.getAscent() + 2, u8g2.getDisplayWidth());
    u8g2.drawStr(x1, u8g2.getAscent() + 1 + (altoFila), "RECETA VACIA");
    u8g2.sendBuffer();
}

void drawRecetaEliminada(int nroReceta)
{
    String cadena = "RECETA Nro " + String(nroReceta);
    char caracteres[cadena.length() + 1];
    cadena.toCharArray(caracteres, cadena.length() + 1);
    u8g2.clearBuffer();
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_profont12_tr);
    filas = 5;
    altoFila = u8g2.getDisplayHeight() / filas - 1;
    int x1 = (u8g2.getDisplayWidth() - u8g2.getStrWidth(caracteres)) / 2;
    int x2 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("ELIMINADA CON EXITO")) / 2;
    u8g2.drawStr(x1, u8g2.getAscent() + 1 + altoFila * 2, caracteres);
    u8g2.drawStr(x2, u8g2.getAscent() + 1 + altoFila * 4, "ELIMINADA CON EXITO");
    u8g2.sendBuffer();
}
