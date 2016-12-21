int pwmPin = 9;      //digital pin 9
int redLEDPin = 13;  //  PIN für die rote LED
int redLED = 0;      //  Der Wert für dir Leuchtkraft der LED, Werte von 0-255
int pwmVal = 250;
unsigned long time;
unsigned int rpm;
int bindex,dindex=0;
String inputString = "";  
String coretmp = "";
int coretmpInt = 0;

boolean NewData = false;  // update Lcd flag


void setup()
{
 pinMode(pwmPin, OUTPUT);   // sets the pin as output
 Serial.begin(9600);
 inputString.reserve(200);
}

void loop(){
  if(NewData){
    Serial.print("wert als INT: "); 
    Serial.print(coretmpInt); 
    Serial.print("\n"); 

    if(coretmpInt < 43) {
      pwmVal = 50;
    }else if ((coretmpInt > 42) && (coretmpInt < 49)) {
      pwmVal = 100;
    }else if ((coretmpInt > 48) && (coretmpInt < 55)) {
      pwmVal = 150;
    }else if ((coretmpInt > 54) && (coretmpInt < 61)) {
      pwmVal = 200;
    }else if (coretmpInt > 60) {
      pwmVal = 250;    
    }else {
      pwmVal = 250;
    }
    
    if (pwmVal != 255) {
      //pwmVal += 10;
      Serial.print("pwmVal: "); 
      Serial.print(pwmVal);  // Print PWM value
      Serial.print("\n"); 
    } else {
      Serial.print("pwmVal: "); 
      Serial.print(pwmVal);  // Print PWM value
      Serial.print("\n");
    }
    inputString = ""; 
    NewData = false;
  }
  analogWrite(redLEDPin, redLED);  //  Sendet den analogen Wert an den PIN
  analogWrite(pwmPin, pwmVal);
  
}

int b[4];// b #0

void serialEvent() {

  b[0] = 0;
    // clear the string:
  while (Serial.available()) {
  redLED = 255;
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
//    Serial.println(inputString);
    // if the incoming character is a newline, set the flag
    // so the main loop can do something about it:
    // update the strings to input.
    if (inChar == ';') {
      b[1] = inputString.indexOf(';');
      coretmp = inputString.substring(b[0],b[1]);
      coretmpInt = inputString.toInt();
      NewData = true;
    } 
 //    Serial.println(NewData);
   
  }
  
}
