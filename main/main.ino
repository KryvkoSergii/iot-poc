
//pins for LED
#define PIN_LED_1 2
#define PIN_LED_2 3
#define PIN_LED_3 4

// pins STEP, DIRIRECTION for connecting to the driver A4988 of stepmotor
#define PIN_STEPMOTOR_STEP 3
#define PIN_STEPMOTOR_DIR 2

// number of steps per 1 rotation
#define STEPMOTOR_STEP_ROUND 200

// stepmotor speed constant
#define STEPMOTOR_SPEED_CONST 10

//Ethernet Chip Select
#define ETHERNET_CS 10
//Ethernet Master Out Slave In
#define ETHERNET_MOSI 11
//Ethernet Master In Slave Out
#define ETHERNET_MISO 11
//Ethernet Serial Clock
#define ETHERNET_SCK 13

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins as an output.
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_STEPMOTOR_STEP, OUTPUT);
  pinMode(PIN_STEPMOTOR_DIR, OUTPUT);
  // stepmotor initial values
  digitalWrite(PIN_STEPMOTOR_STEP, 1);
  digitalWrite(PIN_STEPMOTOR_DIR, 0);
}


void loop() {
}

void turnOnLed(int led) {
  digitalWrite(led, HIGH);
}

void turnOffLed(int led) {
  digitalWrite(led, LOW);
}

// direction either HIGH or LOW
void rotateStepmotorForAngle(int direction, int angleInDegree) {
  int steps = angleInDegree * STEPMOTOR_STEP_ROUND % 360;
  rotateStepmotorForSteps(direction, steps);
}

// direction either HIGH or LOW
void rotateStepmotorForSteps(int direction, int numberOfSteps) {
  // direction of rotation
  digitalWrite(PIN_STEPMOTOR_DIR, direction);
  for (int j = 0; j < numberOfSteps; j++) {
    digitalWrite(PIN_STEPMOTOR_STEP, HIGH);
    delay(STEPMOTOR_SPEED_CONST);
    digitalWrite(PIN_STEPMOTOR_STEP, LOW);
    delay(STEPMOTOR_SPEED_CONST);
  }
}
