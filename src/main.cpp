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
  pinMode(EV2, OUTPUT);
  pinMode(LUZ2r, OUTPUT);
  pinMode(LUZ2v, OUTPUT);
  pinMode(EV3, OUTPUT);
  pinMode(LUZ3r, OUTPUT);
  pinMode(LUZ3v, OUTPUT);
  pinMode(EV4, OUTPUT);
  pinMode(LUZ4r, OUTPUT);
  pinMode(LUZ4v, OUTPUT);
  pinMode(EV5, OUTPUT);
  pinMode(LUZ5r, OUTPUT);
  pinMode(LUZ5v, OUTPUT);
  balanza1.begin(DT1, SCK1);
  balanza2.begin(DT2, SCK2);
  balanza3.begin(DT3, SCK3);
  balanza4.begin(DT4, SCK4);
  balanza5.begin(DT5, SCK5);
  digitalWrite(EV1, LOW);
  digitalWrite(LUZ1r, HIGH);
  digitalWrite(LUZ1v, LOW);
  digitalWrite(EV2, LOW);
  digitalWrite(LUZ2r, HIGH);
  digitalWrite(LUZ2v, LOW);
  digitalWrite(EV3, LOW);
  digitalWrite(LUZ3r, HIGH);
  digitalWrite(LUZ3v, LOW);
  digitalWrite(EV4, LOW);
  digitalWrite(LUZ4r, HIGH);
  digitalWrite(LUZ4v, LOW);
  digitalWrite(EV5, LOW);
  digitalWrite(LUZ5r, HIGH);
  digitalWrite(LUZ5v, LOW);
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
        {
          d1 = 0;
          d2 = 0;
          d3 = 0;
          d4 = 0;
          digito = 1;
          pesoNuevo = 0000;
          flag = 210; // ir a Mostrar Agregar Receta
        }
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
      drawMensajeNuevoPeso(d1, d2, d3, d4, digito);
      flag = 211; // ir a espera para agregar receta o cancelar
    }
    break;
  case 211:                            // Espera para agregar receta o cancelar
    if (digitalRead(BTN_verde) == LOW) // Agregar
    {
      pesoNuevo = d1*1000 + d2*100 + d3*10 + d4;
      if(pesoNuevo == 0){
        
      }
      Serial.println(pesoNuevo);
      flag = 200; // ir a accion de guardar receta
    }
    else if (digitalRead(BTN_negro) == LOW) // Cancelar
      flag = 200;                           // ir a Mostrar Menu Recetas
    else if (digitalRead(encoderPinA) == LOW)
    {
      if (digitalRead(encoderPinB) == HIGH)
      { // Sentido Horario
        if (digito == 1)
        {
          if (d1 < 9)
            d1++;
          else if (d1 == 9)
            d1 = 0;
        }
        else if (digito == 2)
        {
          if (d2 < 9)
            d2++;
          else if (d2 == 9)
            d2 = 0;
        }
        else if (digito == 3)
        {
          if (d3 < 9)
            d3++;
          else if (d3 == 9)
            d3 = 0;
        }
        else if (digito == 4)
        {
          if (d4 < 9)
            d4++;
          else if (d4 == 9)
            d4 = 0;
        }
      }
      else if (digitalRead(encoderPinB) == LOW)
      { // Sentido Antihorario
        if (digito == 1)
        {
          if (d1 > 0)
            d1--;
          else if (d1 == 0)
            d1 = 9;
        }
        else if (digito == 2)
        {
          if (d2 > 0)
            d2--;
          else if (d2 == 0)
            d2 = 9;
        }
        else if (digito == 3)
        {
          if (d3 > 0)
            d3--;
          else if (d3 == 0)
            d3 = 9;
        }
        else if (digito == 4)
        {
          if (d4 > 0)
            d4--;
          else if (d4 == 0)
            d4 = 9;
        }
      }
      flag = 210;
    }
    else if (digitalRead(encoderBoton) == LOW)
      if (digitalRead(encoderBoton) == LOW)
        if (digitalRead(encoderBoton) == LOW)
        { // Boton encoder
          if (digito < 4)
            digito++;
          else if (digito == 4)
            digito = 1;
          flag = 210;
        }
    break;
  case 212:                  // Accion de agregar receta

    break;
  case 213:
    t1 = millis();
    t2 = t1;
    while ((t2 - t1) < 10000 && digitalRead(BTN_verde))
    {
      t2 = millis();
    }
    if ((t2 - t1) >= 10000)
    {
      recetaNueva = false;
      agotoEspera = true;
    }
    else if (!digitalRead(BTN_verde))
    {
      digitalWrite(LUZ1r, LOW);
      digitalWrite(LUZ1v, HIGH);
      drawMensajeCentrado("MARCHA");
      digitalWrite(EV1, HIGH);
      while (!digitalRead(BTN_verde))
      {
      }
      digitalWrite(EV1, LOW);
      digitalWrite(LUZ1v, LOW);
      digitalWrite(LUZ1r, HIGH);
      //pesoNuevo = balanza1.get_units(50);
      pesoNuevo = 4987;
      //drawMensajeNuevoPeso(pesoNuevo);
    }
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
