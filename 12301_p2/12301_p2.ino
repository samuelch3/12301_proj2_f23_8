pinMode(in_pin, INPUT); // this should be the sensor

// output pins - there should be six of these, one for each type of die
pinMode(, OUTPUT);
pinMode(out_2, OUTPUT);
pinMode(out_3, OUTPUT);
pinMode(out_4, OUTPUT);
pinMode(, OUTPUT);
pinMode(, OUTPUT);

int outPins;

void write_led(int led_no) {
  if (led_no == 0) return;
  digitalWrite( , HIGH);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  pinValue = digitalRead( inPin );
  if (pinValue == HIGH) {

  }

}
