#include <Arduino.h>
#include "Montiey_Util.h"
// Example Serial command: "P5S1<newline>"

#define LED 13
#define LEDR 11
#define LEDG 10

#define PORTFLAG 'P'
#define STATEFLAG 'S'
#define ENDFLAG '\n'
#define CARRIAGEFLAG '\r'

#define MAXLEN 32

// int ports[] = {12, 11, 10, 9, 8, 7, 6, 5};	//Uno
int ports[] = {A1, 2, 3, 4, 5, 6, 7, 8, 9, A2, 12, A0};	//Nano
int numPorts = 0;

char * str = (char*) calloc(MAXLEN, sizeof(char));
int index = 0;


HandyTimer ledGTimer(500);

void setup() {

	pinMode(LED, OUTPUT);
	pinMode(LEDG, OUTPUT);
	pinMode(LEDR, OUTPUT);

	numPorts = sizeof(ports)/sizeof(ports[0]);

	for(int i = 0; i < numPorts; i++){
		pinMode(ports[i], OUTPUT);
		digitalWrite(ports[i], LOW);
	}

	////////

	Serial.begin(115200);

	Serial.println("======== Jason Harriot 2019 ========");
	Serial.println("======= Manifold Adapter MK1 =======");
}

void set(int pin, bool state){
	// digitalWrite(LEDR, 1);
	digitalWrite(pin, state);
	// delay(250);
	// digitalWrite(LEDR, 0);
	// delay(250);
}

void loop() {
	if(ledGTimer.trigger()){
		digitalWrite(LEDG, !digitalRead(LEDG));
	}
	if(Serial.available()){
		char ch = Serial.read();

		if(ch == ENDFLAG || ch == CARRIAGEFLAG){
			Serial.println("");

			char* portStr = strchr(str, PORTFLAG)+1;
			char* stateStr = strchr(str, STATEFLAG)+1;

			int port = atoi(portStr);
			bool state = atoi(stateStr) == 0 ? false : true;

			// Serial.print("Port: ");
			// Serial.print(port);
			// Serial.print("\t");
			// Serial.println(state ? "ON" : "OFF");

			if(port < numPorts && port >= 0){
				set(ports[port], state);
			}

			memset(str, 0, MAXLEN);
			index = 0;

		} else{
			str[index] = ch;
			Serial.print(ch);

			index++;
			if(index >= MAXLEN){
				memset(str, 0, MAXLEN);
				index = 0;
			}
		}
	}
}
