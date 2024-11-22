// C++ code
//

float distance{0};
int on_state{0};
int min_distance{200};


long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}





void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(8, INPUT);
}

void loop() {
    distance = 0.01723 * readUltrasonicDistance(6, 5);
    Serial.println(distance);
    if (on_state == 1){
      if (distance > 0 and distance < min_distance) {
        tone(11, 392 + 5 * static_cast<int>((2 * (min_distance - distance)) / 5), 1000);  // play tone 60 (C5 = 523 Hz)
        delay(1000 + static_cast<int>(500 * distance / min_distance));                    // Wait for 1000 millisecond(s)
      }
      noTone(11);

      if(digitalRead(8) == HIGH){
        on_state = 0;
        tone(11, 1000, 2000);
        delay(2000);
      }
    }else{
      if(digitalRead(8) == HIGH){
        on_state = 1;
        tone(11, 1000, 2000);
        delay(2000);
      }
    }

}

