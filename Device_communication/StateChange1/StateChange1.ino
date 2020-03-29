#define GPIO0               0
#define GPIO2               2

#define SWITCH_BUILTIN      GPIO0
#define LED_BUILTIN         GPIO2

#define OFF                 1

void setup() {
  Serial.begin(115200);
  digitalWrite(LED_BUILTIN, OFF);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SWITCH_BUILTIN, INPUT);
}

void loop() {
  static bool key;
  static bool once;
  static bool state = OFF;
  String buf;
 
 key = digitalRead(SWITCH_BUILTIN);

  if (key && once)
  {
    once = 0;

    state = !state;
    digitalWrite(LED_BUILTIN, state);
    Serial.print("Led is :");
    if(state == 0)
      Serial.println("OFF");
    else
      Serial.println("ON");
  }
  else if (key == 0)
  {
    once = 1;
  }
  if (Serial.available())
   {
        //buf = Serial.read();
      buf = Serial.readStringUntil('\n');
      Serial.println("Received : "+buf);
        
        if(buf == "ON")
        {
         digitalWrite(LED_BUILTIN,HIGH);
        }else if(buf == "OFF")        
        {
         digitalWrite(LED_BUILTIN,LOW);
        }
     }
 }
    
