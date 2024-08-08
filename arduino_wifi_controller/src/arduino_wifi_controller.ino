#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include <WebSocketsServer.h>
#include "env.h"

#define USE_SERIAL Serial
IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);

AsyncWebServer web_server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

// Handles WebSocket events such as connection, disconnection, and incoming text messages.
// It sends appropriate responses based on the received commands
// (e.g., "forward", "backward", "left", "right").
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

    String direction = "";
    if (strcmp((const char *)payload, "forward") == 0)
    {
      direction = "CONTROL_FORWARD";
    }
    else if (strcmp((const char *)payload, "backward") == 0)
    {
      direction = "CONTROL_BACKWARD";
    }
    else if (strcmp((const char *)payload, "left") == 0)
    {
      direction = "CONTROL_LEFT";
    }
    else if (strcmp((const char *)payload, "right") == 0)
    {
      direction = "CONTROL_RIGHT";
    }
    else
    {
      return;
    }

    webSocket.sendTXT(num, ("Moving " + direction).c_str());
    Serial.println(direction);

    break;
  }
}

// Configures the WiFi access point with a specified local IP, gateway, and subnet.
// Initializes the access point with the provided SSID and password.
void configureWebServer(AsyncWebServer &web_server)
{
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(SSID, PASSWORD);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Hotspot IP Address: ");
  Serial.println(IP);
}

// Initializes the LittleFS file system
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

void handleLEDOn(AsyncWebServerRequest *request)
{
  Serial.println("LEDON");
  request->send(200, "text/plain", "LED is turned on");
}

void handleLEDOff(AsyncWebServerRequest *request)
{
  Serial.println("LEDOFF");
  request->send(200, "text/plain", "LED is turned off");
}

// Sets up the endpoints for controlling the LED (turning it on and off) using the specified web server.
void setLedEndpoints(AsyncWebServer &web_server)
{
  web_server.on("/ledon", HTTP_GET, handleLEDOn);
  web_server.on("/ledoff", HTTP_GET, handleLEDOff);
}

// Configures the web server to serve the main HTML page and associated CSS and JavaScript files from the LittleFS file system.
void setWebPageHosting(AsyncWebServer *web_server)
{
  web_server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                 { request->send(LittleFS, "/index.html", "text/html"); });
  web_server->on("/index.css", HTTP_GET, [](AsyncWebServerRequest *request)
                 { request->send(LittleFS, "/index.css", "text/css"); });
  web_server->on("/index.js", HTTP_GET, [](AsyncWebServerRequest *request)
                 { request->send(LittleFS, "/index.js", "text/javascript"); });
}

// Initializes the serial communication, configures the web server, sets up the web page hosting, initializes the file system, and starts the web server and WebSocket.
void setup()
{
  Serial.begin(9600);
  Serial.println("NodeMCU serial started");

  configureWebServer(web_server);

  // setLedEndpoints(web_server);
  setWebPageHosting(&web_server);
  initFS();

  web_server.begin();
  Serial.println("HTTP web_server running");
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop()
{
  webSocket.loop();
}