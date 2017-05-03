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

byte server [] = { 192, 168, 2, 7 }; //This is the IP address of the arduino we want to send data to.
const int buttonPin = 7;  //There is a button connected to this arduino. When pressed it will send a ssignal to the other arduino.
BridgeClient client;  // Initiate the arduino as a client named "client".
int buttonState = 0;

void setup() {
 Serial.begin(9600);
 
 delay(1000);
 
 pinMode(buttonPin,INPUT);  //Set button as an input.
 Bridge.begin();
 if (client.connect(server, 5555)) //Attempt to connect to server arduino, on port 5555 (designated arduino port)
 {
    Serial.println("connected");
 } 
 else 
 {
   Serial.println("connection failed");
 }
}

void loop() {

   if(client.available())  
   {
    Serial.println("Still Connected");
    buttonState = digitalRead(buttonPin); //Once connected read button state
    if(buttonState == 1)
    {
      client.write(1);  //Send a 1 to other arduino
    }
    else
    {
      client.write(0);  //Send a 0 across
    }
   }
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }
}
