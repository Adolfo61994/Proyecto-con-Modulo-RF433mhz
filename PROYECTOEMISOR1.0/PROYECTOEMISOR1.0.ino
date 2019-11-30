#include <Keypad.h>     // importa libreria Keypad
#include <VirtualWire.h>

/////////////////////////////////////////////////////////////////    TECLADO 4X4
// Definimos las columnas y filas que utilizaremos del teclado 4x4 
const byte FILAS = 2;     // define numero de filas
const byte COLUMNAS = 2;    // define numero de columnas
char keys[FILAS][COLUMNAS] = {    // define la distribucion de teclas
  {'1','2'},
  {'4','5'}
};

byte pinesFilas[FILAS] = {10,11};   // pines correspondientes a las filas
byte pinesColumnas[COLUMNAS] = {12,13}; // pines correspondientes a las columnas

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // crea objeto

char TECLA;       // almacena la tecla presionada
//////////////////////////////////////////////////////////////////

int numero = 0;
int dato[1];
const int dataPin = 2;
void setup()
{
   Serial.begin(9600);      // inicializa comunicacion serie
   Serial.println("Emisor: Setup");
   
 // Se inicializa el RF
    vw_setup(2000); // velocidad: Bits per segundo
    vw_set_tx_pin(dataPin); //Pin 2 como salida para el RF
    
    // se inicializan los pines en los cuales esta conectado el display de 7 segmentos
     for (int i= 3; i<10; i++)
     {
          pinMode(i, OUTPUT);
     }
}

void loop(){
  TECLA = teclado.getKey();   // obtiene tecla presionada y asigna a variable
  if (TECLA)        // comprueba que se haya presionado una tecla
  {  
    numero = TECLA - 48;   //Convertimos la cadena de caracteres en enteros
    Numero_d (numero);

    String str;  
    char buf[VW_MAX_MESSAGE_LEN];
   
   // Ejemplo de envío int
   int dataInt = numero;
    str = "i" + String(dataInt); /// Convertir a string
    str.toCharArray(buf,sizeof(buf)); // Convertir a char array
    vw_send((uint8_t *)buf, strlen(buf)); // Enviar array
    vw_wait_tx(); // Esperar envio
    
    
    Serial.println("Se envio el mensaje");
    Serial.println("=======================================");
    delay(200);
  }else {
      Numero_d (numero);
  }
    
}

void Numero_d(int num){
  switch (num){
              case 0:
              display (1,1,1,1,1,1,0); //escribe 0
              break;

              case 1:
              display (0,1,1,0,0,0,0); //escribe 1
              break;

              case 2:
              display (1,1,0,1,1,0,1); //escribe 2
              break;

              case 3:
              display (1,1,1,1,0,0,1); //escribe 3
              break;

              case 4:
              display (0,1,1,0,0,1,1); //escribe 4
              break;
             
              case 5:
              display (1,0,1,1,0,1,1); //escribe 5
              break;
             
              case 6:
              display (1,0,1,1,1,1,1); //escribe 6
              break;
             
              case 7:
              display (1,1,1,0,0,0,0); //escribe 7
              break;
             
              case 8:
              display (1,1,1,1,1,1,1); //escribe 8
              break;
             
              case 9:
              display (1,1,1,0,0,1,1); //escribe 9
              break;
  }
  
}
   
void display (int a, int b, int c, int d, int e, int f, int g)
// Funcion del display
{
  digitalWrite (3,a);   //Se reciben 7 variables y se asignan
  digitalWrite (4,b);   //a cada una de las salidas
  digitalWrite (5,c);
  digitalWrite (6,d);
  digitalWrite (7,e);
  digitalWrite (8,f);
  digitalWrite (9,g);
}
