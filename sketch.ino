#define trigPin 9
#define echoPin 10
#define buzzer 6
#define motor 5
#define moistureSensor A0

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(motor, OUTPUT);
    pinMode(moistureSensor, INPUT);
    Serial.begin(9600);
}

void loop() {
    long duration;
    int distance;
    
    // Ultrasonic Sensor - Distance Measurement
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;  // Convert to cm
    
    // Obstacle Alert
    if (distance > 0 && distance <= 50) {  
        digitalWrite(buzzer, HIGH);
        digitalWrite(motor, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
        digitalWrite(motor, LOW);
    }

    // Water/Puddle Detection - Siren Sound
    int moistureValue = analogRead(moistureSensor);
    Serial.println(moistureValue);
    if (moistureValue < 500) {  // Adjust threshold as needed
        for (int i = 0; i < 5; i++) {  // Siren effect for 5 cycles
            tone(buzzer, 800);   // Low tone
            digitalWrite(motor, HIGH);
            delay(300);
            tone(buzzer, 1200);  // High tone
            delay(300);
        }
        noTone(buzzer);
        digitalWrite(motor, LOW);
    }

    delay(300);
}
