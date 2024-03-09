#include <UIPEthernet.h>
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

#define LISTENPORT 80
#define MACADDRESS 0x00, 0x01, 0x02, 0x03, 0x04, 0x05
#define MYIPADDR 192, 168, 1, 6
#define MYIPMASK 255, 255, 255, 0
#define MYDNS 192, 168, 1, 1
#define MYGW 192, 168, 1, 1

uint8_t mac[6] = { MACADDRESS };
uint8_t myIP[4] = { MYIPADDR };
uint8_t myMASK[4] = { MYIPMASK };
uint8_t myDNS[4] = { MYDNS };
uint8_t myGW[4] = { MYGW };

EthernetServer server(LISTENPORT);

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

  // initialize the ethernet device
  //Ethernet.begin(mac,myIP);
  Ethernet.begin(mac, myIP, myDNS, myGW, myMASK);
  // start listening for clients
  server.begin();
}


void loop() {
  if (EthernetClient client = server.available()) {
    while ((size = client.available()) > 0) {
      uint8_t* msg = (uint8_t*)malloc(size + 1);
      memset(msg, 0, size + 1);
      size = client.read(msg, size);
      // here should be server logic

      free(msg);
    }
  }
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
