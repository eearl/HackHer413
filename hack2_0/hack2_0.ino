#include <MIDI.h>
#define LED 13
#define BUTTON 2

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}
// DEFINE GLOBAL VARIABLES AS NEEDED
int freq = 1;
unsigned long time = 500;
unsigned long prevBlink = 0;
unsigned long prevPress = 0;
unsigned long rel = 0;
unsigned long dur = 0;
byte prev_state = 1;
int count = 0;
int first[] = {0, 0, 0, 0};
//int LED = 13
//int BUTTON = 10
MIDI_CREATE_DEFAULT_INSTANCE();

void loop() {
  // YOUR CODE HERE
byte curr_state = digitalRead(BUTTON);
if(count < 4) { 
    //Serial.println("<4");
    if(curr_state==0 && prev_state==1 && millis() > prevPress + 100){//BUTTON PRESSED
      first[count] = millis();
      count++;
      Serial.println(count);
    }
    prev_state = curr_state;
}else{
////Serial.println(">=4");
if(count==4){
  unsigned long total = first[3] - first[0];
  time = total/4;
  count++;
}

if(millis() > prevBlink + time){
   digitalWrite(LED, 1-digitalRead(LED));
   prevBlink = millis();
}

if(curr_state==0 && prev_state==1 && millis() > prevPress + 100) { //BUTTON PRESSED
    prevPress = millis();
    //Serial.println("Pressed at:");
}
if(curr_state==1 && prev_state==0) {
    rel = millis();
    dur = rel - prevPress;
    if(dur < .5*time){ //short
      Serial.print("s ");
    }else if(dur<time){ //long
      Serial.print("e ");
   } else if(dur<1.5*time){
      Serial.print("e. ");
    }else if(dur<2*time){ //long
      Serial.print("q ");
       }else if(dur<3*time){ //long
      Serial.print("q. ");
       }else{
     Serial.print("o ");
    }
}
   prev_state = curr_state;

}
}

