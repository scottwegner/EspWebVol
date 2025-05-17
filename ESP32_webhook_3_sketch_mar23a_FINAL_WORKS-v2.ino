#include <WiFi.h>
#include <Wire.h>
#include <WebServer.h>
#include <PT2258.h>
#include <uptime.h>

#define RebootMinutes 1440

// === WiFi Config ===
const char* ssid = "WegnerGuest";
const char* password = "WegnerGuest";

// === Static IP Config ===
IPAddress local_IP(10, 0, 1, 14);
IPAddress gateway(10, 0, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// === I2C Address of PT2258 ===
// Change to 0x44 if your scanner showed that
PT2258 myPT2258(0x88);

// === Web Server on port 80 ===
WebServer server(80);

// === Volume States ===
const int LOW_VOLUME = 10;
const int HIGH_VOLUME = 80;

int currentVolume = LOW_VOLUME; // start with low volume
const int VOLUME_STEP = 1;      //  per step

// === Web Routes ===
void handleRoot() {
  String html = "<h1>PT2258 Volume Control</h1>"
                "<p><a href=\"/volume/low\">Set Volume LOW</a></p>"
                "<p><a href=\"/volume/high\">Set Volume HIGH</a></p>";
  server.send(200, "text/html", html);
}

void setLowVolume() {
  myPT2258.volumeAll(LOW_VOLUME);
  Serial.println("Volume set to LOW.");
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void handleVolumeStatus() {
  server.send(200, "application/json", "{\"volume\": " + String(currentVolume) + "}");
}

void setHighVolume() {
  myPT2258.volumeAll(HIGH_VOLUME);
  Serial.println("Volume set to HIGH.");
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void handleSetVolume() {
  String volumeStr = "";

  if (server.hasArg("volume")) {
    volumeStr = server.arg("volume");
  } else if (server.method() == HTTP_POST && server.hasArg("plain")) {
    // Optional: parse raw POST body if needed
  }

  if (volumeStr != "") {
    int volume = volumeStr.toInt();
    volume = constrain(volume, 0, 100);
    myPT2258.volumeAll(volume);
    currentVolume = volume;
    Serial.printf("Volume set via %s to %d\n",
                  server.method() == HTTP_POST ? "POST" : "GET", volume);
    server.send(200, "text/plain", "Volume set to " + String(volume));
  } else {
    server.send(400, "text/plain", "Missing 'volume' parameter");
  }
}

void handleVolumeUp() {
  currentVolume += VOLUME_STEP;
  currentVolume = constrain(currentVolume, 0, 100);
  myPT2258.volumeAll(currentVolume);
  Serial.printf("Volume increased to %d\n", currentVolume);
  server.send(200, "text/plain", "Volume increased to " + String(currentVolume));
}

void handleVolumeDown() {
  currentVolume -= VOLUME_STEP;
  currentVolume = constrain(currentVolume, 0, 100);
  myPT2258.volumeAll(currentVolume);
  Serial.printf("Volume decreased to %d\n", currentVolume);
  server.send(200, "text/plain", "Volume decreased to " + String(currentVolume));
}

void setup() {
  Serial.begin(115200);

  // === I2C Init ===
  Wire.begin();  // ESP32 default: SDA = 21, SCL = 22
  Wire.setClock(100000);

  // === PT2258 Init ===
  if (!myPT2258.begin()) {
    Serial.println("PT2258 not found!");
    while (1) delay(10);
  }
  myPT2258.mute(false);
  myPT2258.volumeAll(LOW_VOLUME); // start with low volume

  // === WiFi with Static IP ===
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Failed to configure static IP");
  }

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi..");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected! IP Address: ");
  Serial.println(WiFi.localIP());

  // === Web Server Routes ===
server.on("/volume/status", handleVolumeStatus);
server.on("/volume/up", handleVolumeUp);
server.on("/volume/down", handleVolumeDown);
server.on("/", handleRoot);
server.on("/volume/low", setLowVolume);
server.on("/volume/high", setHighVolume);
server.on("/volume/set", handleSetVolume);
  server.begin();

  Serial.println("Web server started.");
}

void loop() {
  uptime::calculateUptime();
  if ((uptime::getMinutes()) >= RebootMinutes) {
  ESP.restart(); // Reboot the ESP32 every 24 hours (1440 minutes)
}
  server.handleClient();
}
