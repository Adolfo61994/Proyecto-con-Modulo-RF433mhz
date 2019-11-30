#include <VirtualWire.h>

const int dataPin = 2;
void setup()
   {   
    Serial.begin(9600);  // Debugging only
    Serial.println("Receptor: setup");

    // Se inicializa el RF
    vw_setup(2000);  // velocidad: Bits per segundo
    vw_set_rx_pin(dataPin);    //Pin 2 como entrada del RF
    vw_rx_start();       // Se inicia como receptor

    for (int i= 7; i<14; i++){
            pinMode(i, OUTPUT);
        }
   }

void loop()
   {
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
 
   // Recibir dato
    if (vw_get_message((uint8_t *)buf,&buflen))
    {
      String dataString;
        if((char)buf[0]=='i')
        {
            for (int i = 1; i < buflen; i++)
            {
            dataString.concat((char)buf[i]);
            }
            int dataInt = dataString.toInt();  // Convertir a int
            Serial.print("Dato tipo Int: ");
            Serial.println(dataInt);
            Numero_d(dataInt);
            delay(800);
        }
        else 
        {
            
            Serial.print("No hay mensajes recibidos: 0");
            int num = 0;
            Numero_d(num);
            Serial.println();
        }
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
  digitalWrite (7,a);   //Se reciben 7 variables y se asignan
  digitalWrite (8,b);   //a cada una de las salidas
  digitalWrite (9,c);
  digitalWrite (10,d);
  digitalWrite (11,e);
  digitalWrite (12,f);
  digitalWrite (13,g);
}
