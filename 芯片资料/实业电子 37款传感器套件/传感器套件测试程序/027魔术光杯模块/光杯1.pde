int LedPinA = 5;
int LedPinB = 6;
int ButtonPinA = 7;
int ButtonPinB = 4;
int buttonStateA = 0; 
int buttonStateB = 0;
int brightness   = 0;

void setup() 
{
    pinMode(LedPinA, OUTPUT); 
    pinMode(LedPinB, OUTPUT);  
    pinMode(ButtonPinA, INPUT); 
    pinMode(ButtonPinB, INPUT);     
}

void loop() 
{
  buttonStateA = digitalRead(ButtonPinA);
  if (buttonStateA == HIGH && brightness != 255)
  { 
   brightness ++;
  } 

   buttonStateB = digitalRead(ButtonPinB);
   if (buttonStateB == HIGH && brightness != 0)
  { 
   brightness --;
  } 
      analogWrite(LedPinA, brightness);  //  A慢漸暗
      analogWrite(LedPinB, 255 - brightness);  // B慢漸亮
      delay(25);
}

