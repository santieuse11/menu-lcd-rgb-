
/**************** creacion de la flecha *******************/

byte Flecha[] = {
  B11000,
  B01100,
  B00110,
  B00011,
  B00011,
  B00110,
  B01100,
  B11000
};

/*********************** librerias ************************/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/************* botones *********************************/

#define MENU  0
#define EXIT  1
#define UP    2
#define DOWN  3

/************************************ botones *********************************/
uint8_t boton[4] = {4, 5, 6, 7};
uint8_t button_estate[4];

#define HOME  0
#define SET_R 1
#define SET_G 2
#define SET_B 3

uint8_t estado = HOME;

uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;

uint8_t R = 9;
uint8_t G = 10;
uint8_t B = 11;

uint8_t i = 1;

LiquidCrystal_I2C lcd(0x3F, 20, 4);

/*************************** Inicialización *********************************/
void setup() {

  // configuracion de pines de salida

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  // Configurar como PULL-UP para ahorrar resistencias

  pinMode(boton[MENU], INPUT_PULLUP);
  pinMode(boton[EXIT], INPUT_PULLUP);
  pinMode(boton[UP], INPUT_PULLUP);
  pinMode(boton[DOWN], INPUT_PULLUP);

  //estado inicial en HIGH

  button_estate[0] = HIGH;
  button_estate[1] = HIGH;
  button_estate[2] = HIGH;
  button_estate[3] = HIGH;

  lcd.init();
  lcd.backlight();
  lcd.createChar(0, Flecha);
  lcd.write(0);
  lcd.setCursor(6, 1);
  lcd.print("CONTROL");
  lcd.setCursor(8, 2);
  lcd.print("RGB");
  delay(2000);


  printColor();
  printHome();
}

uint8_t flancoSubida(int btn) {
  uint8_t valor_nuevo = digitalRead(boton[btn]);
  uint8_t result = button_estate[btn] != valor_nuevo && valor_nuevo == 1;
  button_estate[btn] = valor_nuevo;
  return result;
}

/*************** parte grafica ************************/

void printColor() {
  analogWrite(R, r);
  analogWrite(G, g);
  analogWrite(B, b);
}

void printHome() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MENU CONFIGURACION");
  lcd.setCursor(1, 1);
  lcd.print("CONFIG. ROJO");
  lcd.setCursor(16, 1);
  lcd.print(r, DEC);
  lcd.setCursor(1, 2);
  lcd.print("CONFIG. VERDE");
  lcd.setCursor(16, 2);
  lcd.print(g, DEC);
  lcd.setCursor(1, 3);
  lcd.print("CONFIG. AZUL");
  lcd.setCursor(16, 3);
  lcd.print(b, DEC);

  lcd.setCursor(0, i);
  lcd.write(0);
}

void printRed() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CONFIGURACION ROJO");
  lcd.setCursor(1, 1);
  lcd.print("INTENSIDAD");
  lcd.setCursor(13, 1);
  lcd.print(r, DEC);
  lcd.setCursor(1, 2);
  lcd.print("DISMINUIR");
  lcd.setCursor(1, 3);
  lcd.print("AUMENTAR");

  lcd.setCursor(0, i);
  lcd.write(0);

}

void printGreen() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CONFIGURACION VERDE");
  lcd.setCursor(1, 1);
  lcd.print("INTENSIDAD");
  lcd.setCursor(13, 1);
  lcd.print(g, DEC);
  lcd.setCursor(1, 2);
  lcd.print("DISMINUIR");
  lcd.setCursor(1, 3);
  lcd.print("AUMENTAR");

  lcd.setCursor(0, i);
  lcd.write(0);
}

void printBlue() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CONFIGURACION AZUL");
  lcd.setCursor(1, 1);
  lcd.print("INTENSIDAD");
  lcd.setCursor(13, 1);
  lcd.print(b, DEC);
  lcd.setCursor(1, 2);
  lcd.print("DISMINUIR");
  lcd.setCursor(1, 3);
  lcd.print("AUMENTAR");

  lcd.setCursor(0, i);
  lcd.write(0);
}

/***************** fin de la parte visual ***********************/

/**************** inicio de la parte logica ********************/

void loop() {

  switch (estado) {

    case HOME:

      if (flancoSubida(DOWN)) {
        if (i < 3) {
          i++;
        } else {
          i = 1;
        }
        printHome();
        break;
      }

      if (flancoSubida(UP)) {
        if (i > 1) {
          i--;
        } else {
          i = 3;
        }
        printHome();
        break;
      }

      if ( i == 1 && flancoSubida(MENU)) {
        i = 1;
        estado = SET_R;
        printRed();
        break;
      }

      if ( i == 2 && flancoSubida(MENU)) {
        i = 1;
        estado = SET_G;
        printGreen();
        break;
      }

      if ( i == 3 && flancoSubida(MENU)) {
        i = 1;
        estado = SET_B;
        printBlue();
        break;
      }

      break;

    case SET_R:

      if (flancoSubida(DOWN)) {
        if (i < 3) {
          i++;
        } else {
          i = 1;
        }
        printRed();
        break;
      }

      if (flancoSubida(UP)) {
        if (i > 1) {
          i--;
        } else {
          i = 3;
        }
        printRed();
        break;
      }

      if (flancoSubida(EXIT)) {
        i = 1;
        estado = HOME;
        printHome();
        break;
      }
      if ( i == 1 && flancoSubida(MENU)) {
        r = 0;

        printColor();
        printRed();
        break;
      }

      if ( i == 2 && flancoSubida(MENU)) {
        if (r > 0) {
          r--;
        } else {
          r = 255;
        }
        printColor();
        printRed();
        break;
      }

      if ( i == 3 && flancoSubida(MENU)) {
        if (r < 255) {
          r++;
        } else {
          r = 0;
        }
        printColor();
        printRed();
        break;
      }

      break;

    case SET_G:

      if (flancoSubida(DOWN)) {
        if (i < 3) {
          i++;
        } else {
          i = 1;
        }
        printGreen();
        break;
      }

      if (flancoSubida(UP)) {
        if (i > 1) {
          i--;
        } else {
          i = 3;
        }
        printGreen();
        break;
      }

      if (flancoSubida(EXIT)) {
        i = 1;
        estado = HOME;
        printHome();
        break;
      }
      if ( i == 1 && flancoSubida(MENU)) {
        g = 0;

        printColor();
        printGreen();
        break;
      }

      if ( i == 2 && flancoSubida(MENU)) {
        if (g > 0) {
          g--;
        } else {
          g = 255;
        }
        printColor();
        printGreen();
        break;
      }

      if ( i == 3 && flancoSubida(MENU)) {
        if (g < 255) {
          g++;
        } else {
          g = 0;
        }
        printColor();
        printGreen();
        break;
      }
      break;

    case SET_B:

      if (flancoSubida(DOWN)) {
        if (i < 3) {
          i++;
        } else {
          i = 1;
        }
        printBlue();
        break;
      }

      if (flancoSubida(UP)) {
        if (i > 1) {
          i--;
        } else {
          i = 3;
        }
        printBlue();
        break;
      }

      if (flancoSubida(EXIT)) {
        i = 1;
        estado = HOME;
        printHome();
        break;
      }

      if ( i == 1 && flancoSubida(MENU)) {
        b = 0;

        printColor();
        printBlue();
        break;
      }

      if ( i == 2 && flancoSubida(MENU)) {
        if (b > 0) {
          b--;
        } else {
          b = 255;
        }
        printColor();
        printBlue();
        break;
      }

      if ( i == 3 && flancoSubida(MENU)) {
        if (b < 255) {
          b++;
        } else {
          b = 0;
        }
        printColor();
        printBlue();
        break;
      }
      break;
  };
}
