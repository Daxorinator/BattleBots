int M1_F = 2; // Motor 1 Forward Pin
int M1_B = 3; // Motor 1 Backward Pin
int M2_F = 4; // Motor 2 Forward Pin
int M2_B = 5; // Motor 2 Backward Pin

int thpin = 6; // Throttle Pin
int rupin = 7; // Rudder Pin
int elpin = 8; // Elevator Pin
int repin = 9; // Relay Pin

const int dZone = 50;

void setup() {

  pinMode(M1_F, OUTPUT);
  pinMode(M1_B, OUTPUT);
  pinMode(M2_F, OUTPUT);
  pinMode(M2_B, OUTPUT);

  pinMode(thpin, INPUT);
  pinMode(rupin, INPUT);
  pinMode(elpin, INPUT);
  pinMode(repin, OUTPUT);

  Serial.begin(9600);
}

void stop() {
  // Stops all motors

  analogWrite(M1_F, 0);
  analogWrite(M1_B, 0);
  analogWrite(M2_F, 0);
  analogWrite(M2_B, 0);
}

void driveLR(int left, int right) {
  // Left and Right turning

  if (left > 0) {
    analogWrite(M1_F, left);
    analogWrite(M1_B, 0);
  } else {
    analogWrite(M1_F, 0);
    analogWrite(M1_B, -left);
  }

  if (right > 0) {
    analogWrite(M2_F, right);
    analogWrite(M2_B, 0);
  } else {
    analogWrite(M2_F, 0);
    analogWrite(M2_B, -right);
  }
}

void grinder(int io)
{
  digitalWrite(repin, io);
}

int rxmap(int x)
{
  // If I get 0, return -999.
  // Otherwise, throttle and others in range 1000-2000: map them to -255 to +255

  if (x == 0) return -999;
  return (map(x, 1000, 2000, -255, 255));
}

void loop() {

  int timeout = 35000;
  int th = 0; // Start with Throttle at 0
  int ru = 0; // Start with Rudder at 0
  int el = 0; // Start with Aileron at 0

  th = pulseIn(thpin, HIGH, timeout); //Read Throttle Position
  ru = pulseIn(rupin, HIGH, timeout); //Read Rudder Position
  el = pulseIn(elpin, HIGH, timeout); //Read Aileron Position

  th = rxmap(th);
  ru = rxmap(ru);
  el = rxmap(el);

  if (th > -dZone && th < dZone && ru > -dZone && ru < dZone) {
    stop();
  } else {
    driveLR(th - ru, th + ru);
  }

  if (el > 200) {
    grinder(LOW);
  } else {
    grinder(HIGH);
  }
}
