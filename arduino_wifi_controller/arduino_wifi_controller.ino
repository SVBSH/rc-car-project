#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


IPAddress local_IP(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

const char *ssid = "MyWiFiHotspot";
const char *password = "password123";

// Vytvorenie HTTP servera
ESP8266WebServer server(80);

void setup() {
  // Inicializácia sériovej komunikácie
  Serial.begin(9600);
  Serial.println("NodeMCU serial started");

  WiFi.softAPConfig(local_IP, gateway, subnet);
  // Nastavenie NodeMCU ako prístupový bod (AP)
  WiFi.softAP(ssid, password);

  // Získanie IP adresy prístupového bodu
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Hotspot IP Address: ");
  Serial.println(IP);

  // Definovanie spracovania HTTP požiadaviek
  server.on("/", HTTP_GET, handleRoot);
  server.on("/ledon", HTTP_GET, handleLEDOn);
  server.on("/ledoff", HTTP_GET, handleLEDOff);

  // Spustenie servera
  server.begin();
  Serial.println("HTTP server running");
}

void loop() {
  // Spracovanie prichádzajúcich požiadaviek
  server.handleClient();
}

// Funkcia na spracovanie požiadavky na koreňovú URL ("/")
void handleRoot() {
  server.send(200, "text/plain", "Use /ledon or /ledoff to control the LED.");
}

// Funkcia na zapnutie LED
void handleLEDOn() {
  Serial.println("LEDON");
  server.send(200, "text/plain", "LED is turned on");
}

// Funkcia na vypnutie LED
void handleLEDOff() {
  Serial.println("LEDOFF");
  server.send(200, "text/plain", "LED is turned off");
}
