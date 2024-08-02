#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);

const char *ssid = "MyWiFiHotspot";
const char *password = "password123";

// Vytvorenie HTTP servera
ESP8266WebServer server(80);

void setup()
{
  // Inicializácia sériovej komunikácie
  Serial.begin(9600);
  Serial.println("NodeMCU serial started");

  configureWebServer(server);

  setLedEndpoints(server);
  setCarControllEndpoints(server);

  // run server
  server.begin();
  Serial.println("HTTP server running");
}

void loop()
{
  // Spracovanie prichádzajúcich požiadaviek
  server.handleClient();
}

void configureWebServer(ESP8266WebServer &server)
{
  WiFi.softAPConfig(local_IP, gateway, subnet);
  // Nastavenie NodeMCU ako prístupový bod (AP)
  WiFi.softAP(ssid, password);

  // Získanie IP adresy prístupového bodu
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Hotspot IP Address: ");
  Serial.println(IP);
}

void setLedEndpoints(ESP8266WebServer &server)
{
  server.on("/", HTTP_GET, handleRoot);
  server.on("/ledon", HTTP_GET, handleLEDOn);
  server.on("/ledoff", HTTP_GET, handleLEDOff);
}

void setCarControllEndpoints(ESP8266WebServer &server)
{
  server.on("/control/forward", HTTP_GET, handleControlForward);
  server.on("/control/right", HTTP_GET, handleControlRight);
  server.on("/control/left", HTTP_GET, handleControlLeft);
}

void handleControlForward()
{
  Serial.println("CONTROL_FORWARD");
  server.send(200, "text/plain", "CONTROL_FORWARD");
}

void handleControlRight()
{
  Serial.println("CONTROL_RIGHT");
  server.send(200, "text/plain", "CONTROL_RIGHT");
}

void handleControlLeft()
{
  Serial.println("CONTROL_LEFT");
  server.send(200, "text/plain", "CONTROL_LEFT");
}

// Funkcia na spracovanie požiadavky na koreňovú URL ("/")
void handleRoot()
{
  server.send(200, "text/plain", "Use /ledon or /ledoff to control the LED.");
}

// Funkcia na zapnutie LED
void handleLEDOn()
{
  Serial.println("LEDON");
  server.send(200, "text/plain", "LED is turned on");
}

// Funkcia na vypnutie LED
void handleLEDOff()
{
  Serial.println("LEDOFF");
  server.send(200, "text/plain", "LED is turned off");
}
