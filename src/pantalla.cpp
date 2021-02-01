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
    int centroX = (u8g2.getDisplayWidth() - u8g2.getStrWidth("MENU PRINCIPAL")) / 2;
    int x1 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("RECETAS")) / 2;
    int x2 = (u8g2.getDisplayWidth() - u8g2.getStrWidth("MARCHA")) / 2;
    u8g2.drawStr(centroX, u8g2.getAscent() + 1, "MENU PRINCIPAL");
    u8g2.drawHLine(0, u8g2.getAscent() + 2, u8g2.getDisplayWidth());
    u8g2.drawStr(x1, u8g2.getAscent() + 1 + (alturaConTitulo / 2 - u8g2.getAscent() * 0.5), "RECETAS");
    u8g2.drawStr(x2, u8g2.getAscent() + 1 + (alturaConTitulo / 2 + u8g2.getAscent() * 1.5), "MARCHA");
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
    u8g2.setFont(u8g2_font_profont12_tr);
    u8g2.drawStr(1, u8g2.getAscent() + 1, "Ubique el envase en");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 2, "posicion de llenado");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 3 + 5, "*Presione el selector");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 4 + 5, " si desea continuar.");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 6 - 1, "*Gire el selector");
    u8g2.drawStr(1, (u8g2.getAscent() + 1) * 7 - 1, " si desea cancelar.");
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
