const int dZone = 35;
int th = 0; // Start with Throttle at 0
int thpin = 2; // Throttle Pin
int el = 0; // Start with Elevator at 0
int elpin = 3; // Elevator Pin
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
    pinMode(elpin, INPUT);
    Serial.begin(9600);
}

void forward(int sp, int rl) {
//    Serial.print("forward  M1=");
//    Serial.print(sp+rl);
//    Serial.print("   M2=");
//    Serial.print(sp-rl);
//    Serial.println();
    analogWrite(M1_F, sp+rl);
    analogWrite(M2_F, sp-rl);
    analogWrite(M1_B, 0);
    analogWrite(M2_B, 0);
}

void back(int sp, int rl) {
//    Serial.print("Backward  M1=");
//    Serial.print(sp+rl);
//    Serial.print("   M2=");
//    Serial.print(sp-rl);
//    Serial.println();
    analogWrite(M1_F, 0);
    analogWrite(M2_F, 0);
    analogWrite(M1_B, sp-rl);
    analogWrite(M2_B, sp+rl);
}

void stop() {
    analogWrite(M1_F, 0);
    analogWrite(M2_F, 0);
    analogWrite(M1_B, 0);
    analogWrite(M2_B, 0);
}

void loop() {
    th = pulseIn(thpin, HIGH, 25000); //Read Throttle Position
    el = pulseIn(elpin, HIGH, 25000); //Read Eleavtor Position

    Serial.println("Before map");
    Serial.println(th); //Debug: Print th
    Serial.println(el); //Debug: Print el

    th = map(th, 1065, 1946, -255, 255); //Map throttle to -255, 255 for use in forward and back
    el = map(el, 1947, 1028, -255, 255); //Map elevator to -255, 255 for use in left and right

    Serial.println("After map");
    Serial.println(th); //Debug: Print th
    Serial.println(el); //Debug: Print el

    delay(100); // delay in between reads for stability
    
    if (th > dZone) { //th > dzone would be above deadzone or pointing up
      forward(th, el); //so go forward
    } else if (th < -dZone) { //otherwise check if its less than the deadzone, which would be down
      back(-th, -el); //then go backward negative th, to provide a positive output to use in function
    } else { //otherwise, if it's in the deadzone
      stop();  //stop moving
    } 
}
