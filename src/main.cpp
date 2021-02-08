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
  //Iteracion para "resetear" EEPROM
  /* for(i = 0; i < EEPROM.length(); i++) {
    EEPROM.update(i, 255);
  } */
  Serial.begin(9600);
  tamanoEstructura = sizeof(sReceta);
  Serial.println("------------INICIO EEPROM-------------");
  for (i = 0; i < maximoRecetas; i++)
  {
    EEPROM.get(tamanoEstructura * i, aRecetas[i]);
    Serial.print("Iteracion: ");
    Serial.println(i);
    Serial.print("Nro receta: ");
    Serial.println(aRecetas[i].numeroReceta);
    Serial.print("Peso: ");
    Serial.println(aRecetas[i].pesoProducto);
    Serial.print("Volumen: ");
    Serial.println(aRecetas[i].volumenProducto);
    Serial.println();
    if (aRecetas[i].numeroReceta < 65535)
      recetasGuardadas++;
  }
  Serial.print("Tamaño de estructura: ");
  Serial.println(tamanoEstructura);
  Serial.print("Recetas guardadas: ");
  Serial.println(recetasGuardadas);
  Serial.println("------------FIN EEPROM-------------");
  delay(2000);
  drawInicio();
}

void loop()
{
  switch (flag)
  {
  case 0: // Espera de tecla de inicio
    if (digitalRead(encoderPinA) == LOW || digitalRead(encoderBoton) == LOW)
      flag = 100; // ir a mostrar menu principal
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
      delay(20); // antirrebote
      if (digitalRead(encoderPinA) == LOW)
      {
        if (digitalRead(encoderPinB) == HIGH)
        {
          if (seleccion < 3)
            seleccion++;
          else if (seleccion == 3)
            seleccion = 1;
        }
        else if (digitalRead(encoderPinB == LOW)) // si B es LOW, sentido antihorario
        {
          if (seleccion > 1)
            seleccion--;
          else if (seleccion == 1)
            seleccion = 3;
        }
        drawMenuPrincipal();
        drawSelector(cantidad, seleccion);
      }
    }
    if (digitalRead(encoderBoton) == LOW)
    {
      delay(50); // Antirrebote
      if (digitalRead(encoderBoton) == LOW)
      {
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
      delay(10); // antirrebote
      if (digitalRead(encoderPinA) == LOW)
      {
        if (digitalRead(encoderPinB) == HIGH) // si B es HIGH, sentido horario
        {
          if (seleccion < 4)
            seleccion++;
          else if (seleccion == 4)
            seleccion = 1;
        }
        else if (digitalRead(encoderPinB == LOW)) // si B es LOW, sentido antihorario
        {
          if (seleccion > 1)
            seleccion--;
          else if (seleccion == 1)
            seleccion = 4;
        }
        drawMenuRecetas();
        drawSelector(cantidad, seleccion);
      }
    }
    if (digitalRead(encoderBoton) == LOW)
    {
      delay(50); // antirrebote
      if (digitalRead(encoderBoton) == LOW)
      {
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
        {
          paginaRecetas = 1;
          flag = 220; // ir a Mostrar Mostrar Recetas
        }
        else if (seleccion == 3)
        {
          d1 = 0;
          d2 = 0;
          digito = 1;
          flag = 230; // ir a Mostrar Eliminar Recetas
        }
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
      pesoNuevo = d1 * 1000 + d2 * 100 + d3 * 10 + d4;
      if (pesoNuevo == 0)
      {
        drawErrorAgregarReceta();
        delay(7000);
        flag = 210;
      }
      else
        flag = 212; // ir a accion de guardar receta
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
    {
      delay(50); // antirrebote
      if (digitalRead(encoderBoton) == LOW)
      { // Boton encoder
        if (digito < 4)
          digito++;
        else if (digito == 4)
          digito = 1;
        flag = 210;
      }
    }
    break;
  case 212: // Accion de agregar receta
    i = 0;
    while (aRecetas[i].pesoProducto != 65535 && i < 12)
    {
      i++;
    }
    drawRecetaCorrecta(i + 1);
    aRecetas[i].numeroReceta = i + 1;
    aRecetas[i].pesoProducto = pesoNuevo;
    EEPROM.put(tamanoEstructura * i, aRecetas[i]);
    recetasGuardadas++;
    delay(6000);
    flag = 200;
    break;
  case 220: // Mostrar Mostrar Recetas
    if (recetasGuardadas == 0)
    {
      drawSinRecetas();
      delay(7000);
      flag = 200;
    }
    else
    {
      recetasAMostrar();
      flag = 221; // Ir a Espera para cambiar paginas o salir
    }
    break;
  case 221: // Espera para cambiar de paginas o salir de Mostrar recetas
    if (digitalRead(BTN_negro) == LOW || digitalRead(BTN_verde) == LOW)
      flag = 200;
    else if (digitalRead(encoderPinA) == LOW)
    {
      delay(10); // antirrebote
      if (digitalRead(encoderPinA) == LOW)
      {
        if (digitalRead(encoderPinB) == HIGH)
        { // Sentido Horario
          if (paginaRecetas < 3)
            paginaRecetas++;
          else if (paginaRecetas == 3)
            paginaRecetas = 1;
        }
        else if (digitalRead(encoderPinB) == LOW)
        { // Sentido Antihorario
          if (paginaRecetas > 1)
            paginaRecetas--;
          else if (paginaRecetas == 1)
            paginaRecetas = 3;
        }
      }
      flag = 220;
    }
    break;
  case 230: // Mostrar Eliminar Recetas
    if (recetasGuardadas == 0)
    {
      drawSinRecetas();
      delay(7000);
      flag = 200;
    }
    else
    {
      drawEliminarReceta(d1, d2, digito);
      flag = 231; // ir a Espera para cambiar numero a eliminar o cancelar
    }
    break;
  case 231:                            // Espera para cambiar nro a eliminar o cancelar
    if (digitalRead(BTN_verde) == LOW) // Borrar
    {
      borrarReceta = d1 * 10 + d2;
      if (borrarReceta == 0 || borrarReceta > 12)
      {
        drawErrorEliminarReceta();
        delay(7000);
        flag = 200;
      }
      else
        flag = 232; // ir a accion de eliminar receta
    }
    else if (digitalRead(BTN_negro) == LOW) // Cancelar
      flag = 200;                           // ir a Mostrar Menu Recetas
    else if (digitalRead(encoderPinA) == LOW)
    {
      delay(10); // antirrebote
      if (digitalRead(encoderPinA) == LOW)
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
        }
        flag = 230; // actualizar pantalla
      }
    }
    else if (digitalRead(encoderBoton) == LOW)
    {
      delay(50); // antirrebote
      if (digitalRead(encoderBoton) == LOW)
      { // Boton encoder
        if (digito == 1)
          digito++;
        else if (digito == 2)
          digito--;
        flag = 230; // actualizar pantalla
      }
    }
    break;
  case 232:
    if (aRecetas[borrarReceta - 1].pesoProducto == 65535)
    {
      drawErrorRecetaVacia();
      delay(6000);
      flag = 230;
    }
    else
    {
      drawRecetaEliminada(borrarReceta);
      aRecetas[borrarReceta - 1].numeroReceta = 65535;
      aRecetas[borrarReceta - 1].pesoProducto = 65535;
      EEPROM.put(tamanoEstructura * (borrarReceta - 1), aRecetas[borrarReceta - 1]);
      recetasGuardadas--;
      delay(5000);
      flag = 200;
    }

    break;
  case 300: // Menu Marcha
    break;
  case 400: // Menu Lavado
    break;
  default:
    break;
  }
}

void recetasAMostrar()
{
  int pesos[4];
  int aux;
  if (paginaRecetas == 1)
    aux = 0;
  else if (paginaRecetas == 2)
    aux = 4;
  else if (paginaRecetas == 3)
    aux = 8;
  for (int i = 0; i < 4; i++)
  {
    pesos[i] = aRecetas[aux].pesoProducto;
    aux++;
  }
  drawMostrarRecetas(pesos, paginaRecetas, aux - 4);
}