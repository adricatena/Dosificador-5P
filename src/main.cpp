#include <Arduino.h>
#include "globales.h"
#include "pantalla.h"
#include <EEPROM.h>

void setup()
{
  setupPantalla();
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(encoderBoton, INPUT);
  pinMode(BTN_verde, INPUT_PULLUP);
  pinMode(BTN_negro, INPUT_PULLUP);
  pinMode(BOMBA, OUTPUT);
  pinMode(EV1, OUTPUT);
  pinMode(LUZ1r, OUTPUT);
  pinMode(LUZ2v, OUTPUT);
  balanza1.begin(DT1, SCK1);
  balanza2.begin(DT2, SCK2);
  balanza3.begin(DT3, SCK3);
  balanza4.begin(DT4, SCK4);
  balanza5.begin(DT5, SCK5);
  /*Iteracion para "resetear" EEPROM
  for(i = 0; i < EEPROM.length(); i++) {
    EEPROM.update(i, 255);
  }*/

  Serial.begin(9600);
  tamanoEstructura = sizeof(sReceta);
  for (i = 0; i < maximoRecetas; i++)
  {
    EEPROM.get(tamanoEstructura * i, aRecetas[i]);
    Serial.println(i);
    Serial.println(aRecetas[i].numeroReceta);
    Serial.println(aRecetas[i].pesoProducto);
    Serial.println(aRecetas[i].volumenProducto);
    if (aRecetas[i].numeroReceta < 65535)
      recetasGuardadas++;
  }
  Serial.println(tamanoEstructura);
  Serial.println(recetasGuardadas);
  delay(2000);
  drawInicio();
}

void loop()
{
  switch (flag)
  {
  case 0: // Espera de tecla de inicio
    if (digitalRead(encoderPinA) == LOW || digitalRead(encoderBoton) == LOW)
    {
      flag = 100; // ir a mostrar menu principal
    }
    break;
  case 100: // Mostrar Menu Principal
    cantidad = 3;
    seleccion = 1;
    drawMenuPrincipal();
    flag = 101; // Ir a mostrar selector
    break;
  case 101: // Mostrar selector
    drawSelector(cantidad, seleccion);
    flag = 102; // Ir a espera tecla menu Principal
    break;
  case 102: // Espera tecla Menu Principal
    if (digitalRead(encoderPinA) == LOW)
    {
      if (digitalRead(encoderPinA) == LOW)
      { // Antirrebote
        if (digitalRead(encoderPinB) == HIGH)
        {
          if (digitalRead(encoderPinB) == HIGH)
          {
            if (seleccion < 3)
              seleccion++;
            else if (seleccion == 3)
              seleccion = 1;
          }
        }
        else if (digitalRead(encoderPinB == LOW)) // si B es LOW, sentido antihorario
        {
          if (digitalRead(encoderPinB == LOW))
          {
            if (seleccion > 1)
              seleccion--;
            else if (seleccion == 1)
              seleccion = 3;
          }
        }
        drawMenuPrincipal();
        drawSelector(cantidad, seleccion);
      }
    }
    if (digitalRead(encoderBoton) == LOW)
    {
      if (digitalRead(encoderBoton) == LOW)
      { // Antirrebote
        if (seleccion == 1)
          flag = 200; // ir a Mostrar Menu Recetas
        else if (seleccion == 2)
          flag = 300; // ir a Mostrar Menu Marcha
        else if (seleccion == 3)
          flag = 400; // ir a Mostrar Menu Lavado
      }
    }
    break;
  case 200: // Mostrar Menu Recetas
    cantidad = 4;
    seleccion = 1;
    drawMenuRecetas();
    flag = 201; // ir a Mostar selector
    break;
  case 201: // Mostrar selector
    drawSelector(cantidad, seleccion);
    flag = 202; // ir a Espera tecla de Menu Recetas
    break;
  case 202: // Espera tecla Menu Recetas
    if (digitalRead(encoderPinA) == LOW)
    {
      if (digitalRead(encoderPinA) == LOW)
      {                                       // Antirrebote
        if (digitalRead(encoderPinB) == HIGH) // si B es HIGH, sentido horario
        {
          if (digitalRead(encoderPinB) == HIGH)
          { // Antirrebote
            if (seleccion < 4)
              seleccion++;
            else if (seleccion == 4)
              seleccion = 1;
          }
        }
        else if (digitalRead(encoderPinB == LOW)) // si B es LOW, sentido antihorario
        {
          if (digitalRead(encoderPinB == LOW))
          {
            if (seleccion > 1)
              seleccion--;
            else if (seleccion == 1)
              seleccion = 4;
          }
        }
        drawMenuRecetas();
        drawSelector(cantidad, seleccion);
      }
    }
    if (digitalRead(encoderBoton) == LOW)
    {
      if (digitalRead(encoderBoton) == LOW)
      { // Antirrebote
        if (seleccion == 1)
          flag = 210; // ir a Mostrar Agregar Receta
        else if (seleccion == 2)
          flag = 220; // ir a Mostrar Mostrar Recetas
        else if (seleccion == 3)
          flag = 230; // ir a Mostrar Eliminar Recetas
        else if (seleccion == 4)
          flag = 100; // ir a Mostrar Menu Principal
      }
    }
    break;
  case 210: // Mostrar Agregar Receta
    if (recetasGuardadas == maximoRecetas)
    {
      drawMaximoRecetas();
      delay(6000);
      flag = 200; // ir a Mostrar Menu Recetas
    }
    else
    {
      drawInstruccionesAgregarReceta();
      flag = 211; // ir a espera para agregar receta o cancelar
    }
    break;
  case 211:                               // Espera para agregar receta o cancelar
    if (digitalRead(BTN_verde) == LOW) // Agregar
    {
      flag = 212; // ir a accion de agregar receta
    }
    else if (digitalRead(BTN_negro) == LOW) // Cancelar
      flag = 200;                             // ir a Mostrar Menu Recetas
    break;
  case 212: // Accion de agregar receta
    drawMensajeDestarando(); // 'No apoyar envases, destarando...'
    balanza1.set_scale(100.7562521); // Establecemos la ESCALA calculada anteriormente
    balanza1.tare(20);               // El peso actual es considerado Tara.    
    delay(1000);

    flag = 200;
    break;
  case 220: // Mostrar Mostrar Recetas
    break;
  case 230: // Mostrar Eliminar Recetas
    break;
  case 300: // Menu Marcha
    break;
  case 400: // Menu Lavado
    break;
  default:
    break;
  }
}
