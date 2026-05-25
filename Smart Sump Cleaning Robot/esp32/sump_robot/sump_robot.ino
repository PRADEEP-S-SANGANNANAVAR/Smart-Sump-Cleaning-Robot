/**
 * Smart Water Sump Cleaning Robot
 * ESP32 Main Controller Code
 *
 * Author  : Pradeep S Sangannanavr (USN: 1HK22EC122)
 * College : HKBK College Of Engineering
 * Dept    : Electronics and Communication Engineering
 *
 * Features:
 *  - WiFi-based web UI for manual control
 *  - Auto mode with obstacle avoidance (Ultrasonic + IR)
 *  - Motor control via L298N
 *  - Relay control for water pump, suction pump, brush motor
 *  - pH sensor reading
 */

#include <WiFi.h>

// -------- WIFI CREDENTIALS --------
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiServer server(80);

// -------- MOTOR DRIVER (L298N) --------
#define IN1  25
#define IN2  26
#define IN3  27
#define IN4  14
#define ENA  32   // PWM channel A
#define ENB  33   // PWM channel B

// -------- RELAY MODULE --------
#define WATER_PUMP    18
#define SUCTION_PUMP  19
#define BRUSH_MOTOR   23

// -------- SENSORS --------
#define TRIG_PIN   5
#define ECHO_PIN   17   // Connect via voltage divider (1kΩ + 2kΩ) — HC-SR04 outputs 5V
#define IR_LEFT    34
#define IR_RIGHT   35
#define PH_PIN     36   // Analog input (optional)

// -------- CONSTANTS --------
#define OBSTACLE_DISTANCE_CM  20   // Stop and turn if obstacle within 20 cm
#define DEFAULT_SPEED         200  // PWM speed (0–255)

// -------- VARIABLES --------
long duration;
int  distance;

// ========================================================
//  SETUP
// ========================================================
void setup() {
  Serial.begin(115200);

  // Motor driver pins
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  // Relay pins (active HIGH — adjust to LOW if your relay is active-low)
  pinMode(WATER_PUMP,   OUTPUT); digitalWrite(WATER_PUMP,   LOW);
  pinMode(SUCTION_PUMP, OUTPUT); digitalWrite(SUCTION_PUMP, LOW);
  pinMode(BRUSH_MOTOR,  OUTPUT); digitalWrite(BRUSH_MOTOR,  LOW);

  // Sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_LEFT,  INPUT);
  pinMode(IR_RIGHT, INPUT);

  // Set default motor speed
  setSpeed(DEFAULT_SPEED);

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! IP: " + WiFi.localIP().toString());

  server.begin();
}

// ========================================================
//  HELPER FUNCTIONS
// ========================================================

/** Measure distance using HC-SR04 ultrasonic sensor (in cm) */
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  return (int)(duration * 0.034 / 2);
}

/** Set PWM speed for both motors (0–255) */
void setSpeed(int spd) {
  analogWrite(ENA, spd);
  analogWrite(ENB, spd);
}

// -------- MOVEMENT FUNCTIONS --------
void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

void stopBot() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

// -------- CLEANING FUNCTIONS --------
void cleaningON() {
  digitalWrite(WATER_PUMP,   HIGH);
  digitalWrite(SUCTION_PUMP, HIGH);
  digitalWrite(BRUSH_MOTOR,  HIGH);
}

void cleaningOFF() {
  digitalWrite(WATER_PUMP,   LOW);
  digitalWrite(SUCTION_PUMP, LOW);
  digitalWrite(BRUSH_MOTOR,  LOW);
}

// -------- AUTO MODE --------
void autoMode(int dist, int leftIR, int rightIR) {
  if (dist > 0 && dist < OBSTACLE_DISTANCE_CM) {
    // Obstacle ahead — back up and turn
    moveBackward(); delay(400);
    turnRight();    delay(400);
  } else if (leftIR == LOW) {
    // Left boundary detected
    turnRight();
  } else if (rightIR == LOW) {
    // Right boundary detected
    turnLeft();
  } else {
    moveForward();
  }
}

// -------- WEB UI --------
void sendWebUI(WiFiClient& client, int dist, int phValue) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type: text/html");
  client.println("Connection: close");
  client.println();
  client.println("<!DOCTYPE html><html><head>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  client.println("<title>Sump Cleaning Robot</title>");
  client.println("<style>");
  client.println("body{font-family:Arial,sans-serif;text-align:center;background:#1a1a2e;color:#eee;padding:20px;}");
  client.println("h2{color:#00d4ff;} .btn{display:inline-block;margin:6px;padding:12px 24px;");
  client.println("background:#0f3460;color:#fff;border-radius:8px;text-decoration:none;font-size:16px;}");
  client.println(".btn:hover{background:#00d4ff;color:#000;} .info{margin:10px;font-size:18px;}");
  client.println(".clean{background:#16213e;} .danger{background:#e94560;}");
  client.println("</style></head><body>");
  client.println("<h2>🤖 Smart Sump Cleaning Robot</h2>");
  client.println("<div class='info'>📏 Distance: <b>" + String(dist) + " cm</b></div>");
  client.println("<div class='info'>🧪 pH Value: <b>" + String(phValue) + "</b></div>");
  client.println("<hr>");
  client.println("<h3>Movement</h3>");
  client.println("<a class='btn' href='/forward'>⬆ Forward</a><br>");
  client.println("<a class='btn' href='/left'>⬅ Left</a>");
  client.println("<a class='btn danger' href='/stop'>⏹ Stop</a>");
  client.println("<a class='btn' href='/right'>➡ Right</a><br>");
  client.println("<a class='btn' href='/back'>⬇ Back</a>");
  client.println("<hr><h3>Cleaning</h3>");
  client.println("<a class='btn clean' href='/cleanON'>🧹 Clean ON</a>");
  client.println("<a class='btn clean' href='/cleanOFF'>🚫 Clean OFF</a>");
  client.println("<hr><h3>Autonomous</h3>");
  client.println("<a class='btn' href='/auto'>🤖 Auto Mode</a>");
  client.println("</body></html>");
}

// ========================================================
//  MAIN LOOP
// ========================================================
void loop() {
  WiFiClient client = server.available();

  // Read sensors every loop iteration
  int dist     = getDistance();
  int leftIR   = digitalRead(IR_LEFT);
  int rightIR  = digitalRead(IR_RIGHT);
  int phValue  = analogRead(PH_PIN);

  if (client) {
    String req = client.readStringUntil('\r');
    client.flush();

    Serial.println("Request: " + req);

    // --- Movement Commands ---
    if (req.indexOf("/forward") != -1) moveForward();
    if (req.indexOf("/back")    != -1) moveBackward();
    if (req.indexOf("/left")    != -1) turnLeft();
    if (req.indexOf("/right")   != -1) turnRight();
    if (req.indexOf("/stop")    != -1) stopBot();

    // --- Cleaning Commands ---
    if (req.indexOf("/cleanON")  != -1) cleaningON();
    if (req.indexOf("/cleanOFF") != -1) cleaningOFF();

    // --- Auto Mode ---
    if (req.indexOf("/auto") != -1) {
      autoMode(dist, leftIR, rightIR);
    }

    // --- Send Web UI Response ---
    sendWebUI(client, dist, phValue);
    client.stop();
  }
}
