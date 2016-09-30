#include <TM1637Display.h>
#include <ESP8266WiFi.h>

#define DEVICE_NAME "TIG_WELDER"                          // So the same code/stream can work for different tools
const char* ssid      = "YOUR NETWORK";                   // SSID
const char* password  = "YOUR PASSWORD";                  // Password
const char* host      = "data.sparkfun.com";              // website

//input (assuming an analog signal)
int sensorPin = A0; //the analog pin

// Module connection pins (Digital Pins)
#define CLK D5
#define DIO D4

// The amount of time (in milliseconds) to wait
// take into account the time to send the data also
#define TEST_DELAY   1000

// LED pin to blink
#define ESP8266_LED 16

// set up the display
TM1637Display display(CLK, DIO);

// set up and initialize
void setup()
{


  // set up the pins
  pinMode(ESP8266_LED, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

  // set the brightness
  display.setBrightness(0x0a);

  // start the wifis!
  WiFi.begin(ssid, password);

  // wait for it to work
  while (WiFi.status() != WL_CONNECTED) {
    display.showNumberDec( 8080 );
    delay(500);
  }



}

// Rinse and repeat
void loop() {

   // reset to zero
   display.showNumberDec( 0 ); // send to the display

   int reading = analogRead( sensorPin ); // current voltage off the sensor

   // we just want to know if it is a strong signal right now
   if ( reading > 500 ) {

       // this is the internet bit
       // send that a session started
       connect( "START" );
   }

   // set counter to zero
   int count = 0;

   // while we have a strong signal, keep counting
   while ( reading > 500 ) {

     // increment!
     count++;
    
     // now we display it in decimal
     display.showNumberDec( count ); // send to the display
  
     // we are counting "seconds" so put in a delay
     delay(TEST_DELAY);

     // get another reading 
     reading = analogRead(sensorPin); // current voltage off the sensor

 
   }

  // if the count is greater than zero there must have been a session
  // that ended so send the end event
  if ( count > 0 ) 
  {
     connect( "END" );
  }
 
}

void blink() 
{

  // blinking the LED
  // yes I could use a for loop but I didn't. Copypasta FTW
  digitalWrite(ESP8266_LED, HIGH);
  delay(100);
  digitalWrite(ESP8266_LED, LOW);
  delay(100);
  digitalWrite(ESP8266_LED, HIGH);
  delay(100);
  digitalWrite(ESP8266_LED, LOW);
  delay(100);
  digitalWrite(ESP8266_LED, HIGH);
  delay(500);
  digitalWrite(ESP8266_LED, LOW);
  delay(100);
  
  }

void connect( String event ) {

  // you probably don't need this but I found
  // it unresponsive unless I waited a bit
  delay(200);

  // blink the LED to show stuff is happening
  blink();
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  // port = 80 for web stuffs
  const int httpPort = 80;

  // try out that connection plz
  if (!client.connect(host, httpPort)) {
    return;
  }
  
  // We now create a URI for the request including our data
  String url = "/input/NJODn6OOZwF30qpYVpwo?private_key=ENTER YOUR PRIVATE KEY&device=";
  url += DEVICE_NAME;   // name of the device, eg. WELDER
  url += "&event=";
  url += event;         // did the session start or end?
  
  // This will send the request to the server
  // we are not interested in the response in this example
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  // tiny delay             
  delay(10);
  
  
  
}
