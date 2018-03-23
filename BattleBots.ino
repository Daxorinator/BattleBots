const int dZone = 20;
int th = 0; // Start with Throttle at 0
int thpin = 2; // Throttle Pin
int M1_F = 5; //Motor 1 Forward Pin
int M2_F = 10; // Motor 2 Forward Pin
int M1_B = 6; // Motor 1 Backward Pin
int M2_B = 9; // Motor 2 Backward Pin

void setup() {
    pinMode(M1_F, OUTPUT);
    pinMode(M1_B, OUTPUT);
    pinMode(M2_F, OUTPUT);
    pinMode(M2_B, OUTPUT);
    pinMode(thpin, INPUT);
    Serial.begin(9600);
}

void forward(int x) {
    analogWrite(M1_F, x);
    analogWrite(M2_F, x);
    analogWrite(M1_B, 0);
    analogWrite(M2_B, 0);
}

void back(int x) {
    map(x, 0, 127, 127, 0);
    Serial.print("backx: " + x);
    analogWrite(M1_F, 0);
    analogWrite(M2_F, 0);
    analogWrite(M1_B, x);
    analogWrite(M2_B, x);
}

void turnr(int x) {
    analogWrite(M1_F, 0);
    analogWrite(M2_F, x);
    analogWrite(M1_B, x);
    analogWrite(M2_B, 0);
}

void turnl(int x) {
    analogWrite(M1_F, x);
    analogWrite(M2_F, 0);
    analogWrite(M1_B, 0);
    analogWrite(M2_B, x);
}

void stop() {
    analogWrite(M1_F, 0);
    analogWrite(M2_F, 0);
    analogWrite(M1_B, 0);
    analogWrite(M2_B, 0);
}

void loop() {
    th = pulseIn(thpin, HIGH, 25000);
    //Serial.print("Channel Throttle:");
    th = map(th, 1065, 1946, 0, 255);
    //Serial.println(th);
    Serial.println(); //Blank Line
    delay(100); // delay in between reads for stability
    if (th < (127-dZone) && (th > -1)) {
      back(th);
    } else if (th > (127+dZone)) {
      forward(th);
    } else {
      stop();  
    }
}
