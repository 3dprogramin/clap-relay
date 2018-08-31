const int PIN_RELAY = 0;
const int PIN_GATE_IN = 1;
const int PIN_ANALOG_IN = A1;

const int MILLIS_MIN_DIFFERENCE = 400;
const int MILLIS_MAX_DIFFERENCE = 1000;
const int CLAP_MIN_VALUE = 35;
const int CLAP_MAX_VALUE = 1000;

boolean _enabled = false;

// control relay method, enable or disable it
void control_relay()
{
  if(_enabled)
  {
    // if it's enabled, disable it
    digitalWrite(PIN_RELAY, LOW);
    _enabled = false;
//    Serial.println("disabled");
  }
  else
  {
    // if it's disabled, enable it
    digitalWrite(PIN_RELAY, HIGH);
    _enabled = true;
//    Serial.println("enabled");
  }
}

// check if the of the sound is ok
boolean value_ok(int value)
{
  return (value >= CLAP_MIN_VALUE) && (value <= CLAP_MAX_VALUE);
}

void setup()
{
  //Serial.begin(9600);

  //  Configure LED pin as output
  pinMode(PIN_RELAY, OUTPUT);

  // configure input to interrupt
  pinMode(PIN_GATE_IN, INPUT);

  digitalWrite(PIN_RELAY, LOW);   // disable RELAY

  // Display status
  //Serial.println("Initialized");
}

void loop()
{
  int value;

  // Check the envelope input
  value = analogRead(PIN_ANALOG_IN);  

  //Serial.println(value);
  
  // check for first clap
  if(value_ok(value))
  {
    //Serial.println("first clap");
    
    delay(MILLIS_MIN_DIFFERENCE);

    int counter = 0;

    // check for second clap
    while(counter < MILLIS_MAX_DIFFERENCE)
    {
      value = analogRead(PIN_ANALOG_IN);
      if(value_ok(value))
      {
        // we've got the second tigger, control relay
        control_relay();
        delay(500);     // sleep for half a second
        break;
      }
      counter += 1;
    }
    
  }

  // pause for 50 millis
  delay(50);
}

