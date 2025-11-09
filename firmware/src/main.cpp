#include <ArtnetWifi.h>
#include <Arduino.h>
#include <esp_dmx.h>

//#define DEBUGLOG_ENABLED

const char* ssid = "SSID";
const char* password = "PASSWORD";

ArtnetWifi artnet;
const int startUniverse = 1;
const char host[] = "192.168.0.55";

int transmitPin = 17;
int receivePin = 16;
int enablePin = 21;

dmx_port_t dmxPort = 1;

byte data[DMX_PACKET_SIZE];

bool dmxIsConnected = false;
unsigned long lastUpdate = millis();


bool ConnectWifi(void) {
  bool state = true;
  int i = 0;

  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");
  
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false;
      break;
    }
    i++;
  }
  if (state){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  
  return state;
}

void setupDMX() {
  dmx_config_t config = DMX_CONFIG_DEFAULT;
  dmx_personality_t personalities[] = {
    {1, "Default Personality"}
  };
  int personality_count = 1;
  dmx_driver_install(dmxPort, &config, personalities, personality_count);

  dmx_set_pin(dmxPort, transmitPin, receivePin, enablePin);
}

void setup() {
  Serial.begin(115200);
  setupDMX();

  ConnectWifi();
  artnet.begin(host);
  artnet.setLength(192);
  artnet.setUniverse(startUniverse);
}

void loop() {
  dmx_packet_t packet;

  if (dmx_receive(dmxPort, &packet, DMX_TIMEOUT_TICK)) {
    unsigned long now = millis();

    if (!packet.err) {
      if (!dmxIsConnected) {
        Serial.println("DMX is connected!");
        dmxIsConnected = true;
      }

      dmx_read(dmxPort, data, packet.size);

      #ifdef DEBUGLOG_ENABLED
        Serial.printf("Start code is 0x%02X and slot 1 is 0x%02X, size: %u\n", data[0],
                    data[1], packet.size);
      #endif
      lastUpdate = now;
      #ifdef DEBUGLOG_ENABLED
        Serial.print("Sending artnet ...");
      #endif
      for (uint32_t i=0;i<192;i++) {
        artnet.setByte(i, data[i+1]);
      }
      #ifdef DEBUGLOG_ENABLED
        Serial.print("go ...");
      #endif
      artnet.write();
      #ifdef DEBUGLOG_ENABLED
        Serial.println("Done");
      #endif
    } else {
      Serial.println("A DMX error occurred.");
    }
  } else if (dmxIsConnected) {
    Serial.println("DMX was disconnected, reconnecting.");
  }
}
