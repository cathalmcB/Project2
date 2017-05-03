#include <Bridge.h>
#include <BridgeClient.h>
#include <BridgeServer.h>
#include <BridgeSSLClient.h>
#include <BridgeUdp.h>
#include <Console.h>
#include <FileIO.h>
#include <HttpClient.h>
#include <Mailbox.h>
#include <Process.h>

byte serverIP[] = { 192, 168, 2, 7 };
const int buzzerPin = 7;  //This arduino has an alarm connected to it. So it received a signal and the alarm goes off.
const int ledPin = 3;     //Light will also go on.

// The one global server object listening for incoming connections.
BridgeServer server(serverIP, 5555);
BridgeClient client;


void setup()
{
   Bridge.begin();
   Serial.begin(19200);
   while (!Serial)
      ;  // Wait until a Serial Monitor is connected.
    
   Server.noListenOnLocalhost(); // Listen for external connections
   Server.begin();

   pinMode(buzzerPin,OUTPUT);   //Initiate two outputs, LED and Buzzer.
   pinMode(ledPin,OUTPUT);
}


void loop()
{
      digitalWrite(buzzerPin,LOW);  //Set two outputs to off at beginning
      digitalWrite(ledPin,LOW);
      
      if (client.connected()) // Is it connected?
      {
        process();          // It's connected, process the client
      }
      else
      {
        Serial.println("Nothing Connected");
      }
}



void process()
{
   // Read and echo all available data from the client.
   int received;

   // Read all available data, append to string
   while (client.available())
   {
      received=client.read();
   }
      
   // Got something? If so, print out what was recevied, send client ID back to other side
   if (received != null)
   {
      digitalWrite(ledPin,HIGH);  //IF something came through turn LED ON

      if(received == 1)
      {
        digitalWrite(buzzerPin,HIGH); //IF a one came through (ie-Button was pressed) turn on buzzer.
      }
   }
}
