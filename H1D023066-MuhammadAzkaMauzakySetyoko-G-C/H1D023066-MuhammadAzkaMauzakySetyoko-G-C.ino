#include <arduino.h>
#include <servo.h>

Servo myservo;

CONST int PIN_LED_HIJAU = 10;
CONST int PIN_LED_MERAH = 11;

CONST int button = 3;
CONST int servo = 10;

bool upState = HIGH;

int pos = 0;
int val = 0;

void setup(){
	pinMode
}

void loop(){

pos = map(val,
		  0,
		  10
		  0,
		  90);

		  
bool upState = digitalRead(button);

	if(buttonState == LOW){
		digitalWrite(PIN_LED_MERAH, LOW);
		digitalWrite(PIN_LED_HIJAU, HIGH);
		
		myservo.write(pos);
	}else{
		digitalWrite(PIN_LED_HIJAU, LOW);
		digitalWrite(PIN_LED_MERAH, HIGH);
		
		myservo.write(pos*-1);
	}
}