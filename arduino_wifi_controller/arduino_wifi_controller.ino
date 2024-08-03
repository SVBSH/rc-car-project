#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);

const char *ssid = "MyWiFiHotspot";
const char *password = "password123";

// Vytvorenie HTTP servera
ESP8266WebServer server(80);

const char *index_html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Car Control</title>
    <style>
        /* Inline CSS */
        body {
            font-family: Arial, sans-serif;
        }
        .control-container {
            display: flex;
            flex-direction: column;
            align-items: center;
        }
        .control-btn {
            margin: 10px;
            padding: 10px 20px;
            font-size: 16px;
        }
    </style>
    <script>
        // Inline JavaScript
        const API_URL = 'http://192.168.4.22';

        document.addEventListener('DOMContentLoaded', () => {
            const controlContainer = document.querySelector('.control-container');
            controlContainer.addEventListener('click', (e) => {
                const currButton = e.target.closest('.control-btn');
                if (currButton === null) {
                    return;
                }
                const btnType = currButton.dataset.type;
                handleCarControl(btnType);
            });
        });

        async function handleCarControl(btnType) {
            try {
                const request = `${API_URL}/control/${btnType}`;
                console.log(request);
                const response = await fetch(request, { mode: 'no-cors' });
                console.log(response);
            } catch (e) {
                console.log('Error: ', e);
            }
        }
    </script>
</head>
<body>
    <div class="control-container">
        <button class="control-btn" data-type="forward">UP</button>
        <button class="control-btn" data-type="backward">DOWN</button>
        <button class="control-btn" data-type="left">LEFT</button>
        <button class="control-btn" data-type="right">RIGHT</button>
    </div>
</body>
</html>
)rawliteral";

void setup()
{
  // Inicializácia sériovej komunikácie
  Serial.begin(9600);
  Serial.println("NodeMCU serial started");

  configureWebServer(server);

  // setLedEndpoints(server);
  setCarControllEndpoints(server);

  // Serve index.html
  server.on("/", HTTP_GET, []()
            { server.send(200, "text/html", index_html); });

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
  // server.on("/", HTTP_GET, handleRoot);
  // server.on("/ledon", HTTP_GET, handleLEDOn);
  // server.on("/ledoff", HTTP_GET, handleLEDOff);
}

void setCarControllEndpoints(ESP8266WebServer &server)
{
  server.on("/control/forward", HTTP_GET, handleControlForward);
  server.on("/control/right", HTTP_GET, handleControlRight);
  server.on("/control/left", HTTP_GET, handleControlLeft);
  server.on("/control/backward", HTTP_GET, handleControlBackward);
  server.on("/control/stop", HTTP_GET, handleControlStop);
}

void handleControlStop()
{
  Serial.println("CONTROL_STOP");
  server.send(200, "text/plain", "CONTROL_STOP");
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

void handleControlBackward()
{
  Serial.println("CONTROL_BACKWARD");
  server.send(200, "text/plain", "CONTROL_BACKWARD");
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
