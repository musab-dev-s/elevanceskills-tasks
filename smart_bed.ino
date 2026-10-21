/*
  Smart Bed Controller - ESP32 + Servo + MQTT (HiveMQ public broker)

  Commands (topic: mosab/bed/command), not case sensitive:
    SLEEP      -> bed angle 10
    BREATHING  -> bed angle 45
    EMERGENCY  -> bed angle 90 (moves fast)
    AUTO       -> cycles 10 -> 45 -> 90 every 10 s, starts immediately
    STOP       -> stops at the current angle
    0 - 90     -> any angle (decimals are rounded)

  Published:
    mosab/bed/angle   current angle
    mosab/bed/status  last mode: SLEEP / BREATHING / EMERGENCY / AUTO / STOP / MANUAL

  Wokwi libraries.txt:
    PubSubClient
    ESP32Servo

  Wiring: servo signal -> GPIO 18, servo V+ -> VIN (5V), servo GND -> GND

  NOTE: the public broker is open to everyone. Make the topic prefix unique
  (for example "mosab-7f3a/bed/...") so nobody else can send commands to your bed.
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

// Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT broker
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// MQTT topics
const char* commandTopic = "mosab/bed/command";
const char* statusTopic  = "mosab/bed/status";
const char* angleTopic   = "mosab/bed/angle";

// Objects
WiFiClient espClient;
PubSubClient client(espClient);
Servo bedServo;

// Servo settings
const int SERVO_PIN = 18;
const int ANGLE_MIN = 0;
const int ANGLE_MAX = 90;

int currentAngle = 0;
int targetAngle = 0;

// Movement speed: one degree every N ms
const unsigned long MOVE_INTERVAL_NORMAL = 30;   // 90 degrees in ~2.7 s
const unsigned long MOVE_INTERVAL_FAST   = 5;    // emergency: 90 degrees in ~0.45 s
unsigned long moveInterval = MOVE_INTERVAL_NORMAL;
unsigned long lastMoveTime = 0;

// Timers
unsigned long lastReconnectAttempt = 0;
unsigned long lastWifiAttempt = 0;
unsigned long lastPublishTime = 0;

// Automatic demonstration mode
bool autoMode = false;
unsigned long lastAutoTime = 0;
const unsigned long AUTO_INTERVAL = 10000;

// Last command, published as the status
String currentMode = "MANUAL";

// Publish angle and status
void publishStatus() {
  if (!client.connected()) return;

  char angleBuffer[8];
  snprintf(angleBuffer, sizeof(angleBuffer), "%d", currentAngle);

  client.publish(angleTopic, angleBuffer);
  client.publish(statusTopic, currentMode.c_str());
}

// Set target angle (always limited to 0-90)
void setTargetAngle(int angle) {
  targetAngle = constrain(angle, ANGLE_MIN, ANGLE_MAX);

  Serial.print("Target angle: ");
  Serial.println(targetAngle);
}

// Process incoming MQTT commands
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message;

  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  message.trim();
  message.toUpperCase();

  Serial.print("Received topic: ");
  Serial.println(topic);
  Serial.print("Received command: ");
  Serial.println(message);

  if (String(topic) != commandTopic) return;

  if (message == "SLEEP") {
    autoMode = false;
    moveInterval = MOVE_INTERVAL_NORMAL;
    currentMode = "SLEEP";
    setTargetAngle(10);
  }
  else if (message == "BREATHING") {
    autoMode = false;
    moveInterval = MOVE_INTERVAL_NORMAL;
    currentMode = "BREATHING";
    setTargetAngle(45);
  }
  else if (message == "EMERGENCY") {
    autoMode = false;
    moveInterval = MOVE_INTERVAL_FAST;     // react quickly
    currentMode = "EMERGENCY";
    setTargetAngle(90);
  }
  else if (message == "AUTO") {
    autoMode = true;
    moveInterval = MOVE_INTERVAL_NORMAL;
    currentMode = "AUTO";
    lastAutoTime = millis();
    setTargetAngle(10);                    // start moving immediately
    Serial.println("Automatic mode enabled");
  }
  else if (message == "STOP") {
    autoMode = false;
    moveInterval = MOVE_INTERVAL_NORMAL;
    currentMode = "STOP";
    targetAngle = currentAngle;
    Serial.println("Stopped at current angle");
  }
  else {
    // Numeric angle (integers and decimals accepted)
    char *end;
    float value = strtof(message.c_str(), &end);

    if (message.length() > 0 && end != message.c_str() && *end == 0) {

      if (value >= ANGLE_MIN && value <= ANGLE_MAX) {
        autoMode = false;
        moveInterval = MOVE_INTERVAL_NORMAL;
        currentMode = "MANUAL";
        setTargetAngle((int)round(value));
      } else {
        Serial.println("Angle must be between 0 and 90");
      }

    } else {
      Serial.println("Unknown command ignored");
    }
  }

  publishStatus();   // report the new mode immediately
}

// Connect to MQTT
void reconnectMQTT() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected!");
    return;
  }

  Serial.println("Connecting to MQTT broker...");

  String clientId = "ESP32-Bed-";
  clientId += String((uint32_t)ESP.getEfuseMac(), HEX);

  if (client.connect(clientId.c_str())) {
    Serial.println("MQTT CONNECTED SUCCESSFULLY!");

    if (client.subscribe(commandTopic)) {
      Serial.println("Subscribed to bed command topic!");
    } else {
      Serial.println("Subscription failed!");
    }

    publishStatus();

  } else {
    Serial.print("MQTT connection failed. Error code: ");
    Serial.println(client.state());
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("Smart Bed Controller Starting...");

  ESP32PWM::allocateTimer(0);
  bedServo.setPeriodHertz(50);
  bedServo.attach(SERVO_PIN, 500, 2400);
  bedServo.write(currentAngle);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);
  client.setSocketTimeout(3);   // do not freeze the servo if the broker is unreachable

  Serial.println("Controller ready!");
}

void loop() {

  // Wi-Fi reconnect
  if (WiFi.status() != WL_CONNECTED) {
    if (millis() - lastWifiAttempt >= 5000) {
      lastWifiAttempt = millis();
      Serial.println("WiFi lost, reconnecting...");
      WiFi.reconnect();
    }
  }

  // MQTT
  if (!client.connected()) {
    if (millis() - lastReconnectAttempt >= 3000) {
      lastReconnectAttempt = millis();
      reconnectMQTT();
    }
  } else {
    client.loop();
  }

  // Smooth servo movement
  if (millis() - lastMoveTime >= moveInterval) {
    lastMoveTime = millis();

    if (currentAngle < targetAngle) {
      currentAngle++;
      bedServo.write(currentAngle);
    } else if (currentAngle > targetAngle) {
      currentAngle--;
      bedServo.write(currentAngle);
    }
  }

  // Publish position every 500 ms
  if (millis() - lastPublishTime >= 500) {
    lastPublishTime = millis();
    publishStatus();
  }

  // Automatic demonstration mode
  if (autoMode && millis() - lastAutoTime >= AUTO_INTERVAL) {
    lastAutoTime = millis();

    if (targetAngle == 10) {
      setTargetAngle(45);
    } else if (targetAngle == 45) {
      setTargetAngle(90);
    } else {
      setTargetAngle(10);
    }
  }
}
