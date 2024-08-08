#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include <WebSocketsServer.h>

#define USE_SERIAL Serial
IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);

const char *ssid = "MyWiFiHotspot";
const char *password = "password123";

AsyncWebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{

  switch (type)
  {
  case WStype_DISCONNECTED:
  {
    USE_SERIAL.printf("[%u] Disconnected!\n", num);
    break;
  }
  case WStype_CONNECTED:
  {
    IPAddress ip = webSocket.remoteIP(num);
    USE_SERIAL.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

    // send message to client
    webSocket.sendTXT(num, "Connected");
  }
  break;
  case WStype_TEXT:
    USE_SERIAL.printf("[%u] get Text: %s\n", num, payload);

    // send message to client
    // webSocket.sendTXT(num, "message here");

    // send data to all connected clients
    // webSocket.broadcastTXT("message here");
    String direction = ""; // Declare direction outside the if-else blocks
    if (strcmp((const char *)payload, "forward") == 0)
    {
      direction = "CONTROL_FORWARD"; // Assign value to direction
    }
    else if (strcmp((const char *)payload, "backward") == 0)
    {
      direction = "CONTROL_BACKWARD"; // Assign value to direction
    }
    else if (strcmp((const char *)payload, "left") == 0)
    {
      direction = "CONTROL_LEFT"; // Assign value to direction
    }
    else if (strcmp((const char *)payload, "right") == 0)
    {
      direction = "CONTROL_RIGHT"; // Assign value to direction
    }
    else
    {
      return;
    }

    webSocket.sendTXT(num, ("Moving " + direction).c_str()); // Convert String to const char*
    Serial.println(direction);

    break;
  }
}

void configureWebServer(AsyncWebServer &server)
{
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Hotspot IP Address: ");
  Serial.println(IP);
}

void setLedEndpoints(AsyncWebServer &server)
{
  server.on("/ledon", HTTP_GET, handleLEDOn);
  server.on("/ledoff", HTTP_GET, handleLEDOff);
}

// Initialize LittleFS
void initFS()
{
  if (!LittleFS.begin())
  {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  else
  {
    Serial.println("LittleFS mounted successfully");
  }
}

// Funkcia na zapnutie LED
void handleLEDOn(AsyncWebServerRequest *request)
{
  Serial.println("LEDON");
  request->send(200, "text/plain", "LED is turned on");
}

// Funkcia na vypnutie LED
void handleLEDOff(AsyncWebServerRequest *request)
{
  Serial.println("LEDOFF");
  request->send(200, "text/plain", "LED is turned off");
}

void setup()
{
  Serial.begin(9600);
  Serial.println("NodeMCU serial started");

  configureWebServer(server);

  // setLedEndpoints(server);
  initFS();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/index.html", "text/html"); });
  server.on("/index.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/index.css", "text/css"); });
  server.on("/index.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/index.js", "text/javascript"); });

  server.begin();
  Serial.println("HTTP server running");
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop()
{
  webSocket.loop();
}