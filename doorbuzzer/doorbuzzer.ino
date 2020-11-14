#include <ESP8266WiFi.h>
#include <Servo.h>

const char* ssid = "discount lion safari";
const char* password = "password";

bool buzz = false;
int buzzTime = 5000;
int buzzInc = 0;

WiFiServer server(80);


Servo servo;
int angle = 170;
int anglezero = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  // attach servo
  // this is D2
  // https://github.com/esp8266/Arduino/blob/master/variants/d1/pins_arduino.h
  servo.attach(16);
  servo.write(anglezero);

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  server.begin();
  Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
}


String preparePage(String contentType, String data)
{
  String htmlPage =
    String("HTTP/1.1 200 OK\r\n") +
    "Content-Type: " + contentType + "\r\n" +
    "Connection: close\r\n" +  // the connection will be closed after completion of the response
    "Content-Length: " +data.length() + "\r\n" +
    "\r\n" +
    data +
    "\r\n\r\n";
  return htmlPage;
}


// prepare a web page to be send to a client (web browser)
String prepareHtmlPage()
{
  return preparePage("text/html", "<!DOCTYPE HTML><html><body><h1>Hello!</h1></body></html>");
}


int wait = 1;
void loop()
{
  if (buzz) {
    servo.write(angle);
    delay(buzzTime);
    buzz = false;
    servo.write(anglezero);
    /*
    if (buzzInc >= buzzTime) {
      buzz = false;
      buzzInc = 0;
      servo.write(0);
    } else {
      if (buzzInc == 0) {
    servo.write(angle);
      }

    buzzInc = buzzInc + wait;
    */
  }
  WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  if (client)
  {
    Serial.println("\n[Client connected]");
    while (client.connected())
    {
      // read line by line what the client (web browser) is requesting
      if (client.available())
      {
        String line = client.readStringUntil('\r');
        Serial.print(line);
        // wait for end of client's request, that is marked with an empty line
        if (line.length() == 1 && line[0] == '\n')
        {
          buzz = true;
          client.println(prepareHtmlPage());
          break;
        }
      }
    }
    delay(1); // give the web browser time to receive the data

    // close the connection:
    client.stop();
    Serial.println("[Client disconnected]");
  }
}
