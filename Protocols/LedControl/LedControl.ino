#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "Girija";
const char* password = "girijan@79";


WebServer server(80);

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  pinMode(LED_BUILTIN, OUTPUT);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

//handler for root
  server.on("/", []() {
    server.send(200, "text/plain", "hello from esp32!");
  });

//instead of query string arg is used and is retrieved using pathArg
  server.on("/led/{}", []() {
    String led_status = server.pathArg(0);

    int status = (led_status == "ON" ? 1 : 0);
    digitalWrite(LED_BUILTIN, status);
    
    server.send(200, "text/plain", "LED: '" + led_status + "'");
  });
  
  server.on("/users/{}", []() {
    String user = server.pathArg(0);
    server.send(200, "text/plain", "User: '" + user + "'");
  });
  
  server.on("/users/{}/devices/{}", []() {
    String user = server.pathArg(0);
    String device = server.pathArg(1);
    server.send(200, "text/plain", "User: '" + user + "' and Device: '" + device + "'");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
