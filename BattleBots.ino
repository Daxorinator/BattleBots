int M1_F = 2; // Motor 1 Forward Pin
int M1_B = 3; // Motor 1 Backward Pin
int M2_F = 4; // Motor 2 Forward Pin
int M2_B = 5; // Motor 2 Backward Pin

int thpin = 6; // Throttle Pin
int rupin = 7; // Rudder Pin

const int dZone = 50;

void setup() {

  // Setup pins and motors

  pinMode(M1_F, OUTPUT);
  pinMode(M1_B, OUTPUT);
  pinMode(M2_F, OUTPUT);
  pinMode(M2_B, OUTPUT);

  pinMode(thpin, INPUT);
  pinMode(rupin, INPUT);

  Serial.begin(9600);
}

void stop() {

  // Set motors to complete zero.

  Serial.println("Stopping Motors");

  analogWrite(M1_F, 0);
  analogWrite(M1_B, 0);
  analogWrite(M2_F, 0);
  analogWrite(M2_B, 0);
}

void driveLR(int left, int right) {

  Serial.print("Drive LEFT: ");
  Serial.print(left);
  Serial.print("  \t RIGHT: ");
  Serial.print(right);
  Serial.println();

  if (left > 0) {
    analogWrite(M1_F, left);
    analogWrite(M1_B, 0);
  }
  else
  {
    analogWrite(M1_F, 0);
    analogWrite(M1_B, -left);
  }

  if (right > 0) {
    analogWrite(M2_F, right);
    analogWrite(M2_B, 0);
  }
  else
  {
    analogWrite(M2_F, 0);
    analogWrite(M2_B, -right);
  }
}

int rxmap(int x)
{
  // If I get 0, return -999.
  // Otherwise, throttle and others in range 1000-2000: map them to -255 to +255
  
  if (x == 0) return -999;
  return (map(x, 1000, 2000, -255, 255));
}

void loop() {

  delay(500); // delay in between reads for stability

  int timeout = 35000;
  int th = 0; // Start with Throttle at 0
  int ru = 0; // Start with Rudder at 0

  th = pulseIn(thpin, HIGH, timeout); //Read Throttle Position
  ru = pulseIn(rupin, HIGH, timeout); //Read Rudder Position

  th = rxmap(th);
  ru = rxmap(ru);

  Serial.print("After map: Th = ");
  Serial.print(th); //Debug: Print th
  Serial.print("   \t El = ");
  Serial.print(ru); //Debug: Print ru
  Serial.print("  \t\t");

  if (th > -dZone && th < dZone && ru > -dZone && ru < dZone) {
    stop();
  }
  else {
    driveLR(th - ru, th + ru);
  }

}
