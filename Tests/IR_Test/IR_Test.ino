#include "IRremote.h"

IRrecv irrecv(6);

decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if ( irrecv.decode( &results )) {
    Serial.println(results.value);
    irrecv.resume();
  }
}
