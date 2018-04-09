// Project 12 - Pulse Monitor Test Script

int ledPin = 13;
int sensorPin = 0;

double alpha = 0.75;
int period = 20;
double change = 0.0;

void setup()                   
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop()                    
{
    static double oldValue = 0;
    static double oldChange = 0;
    int rawValue = analogRead(sensorPin);
    double value = alpha * oldValue + (1 - alpha) * rawValue;
    
    Serial.print(rawValue);
    Serial.print(",");
    Serial.println(value);

    oldValue = value;
    delay(period);
}



