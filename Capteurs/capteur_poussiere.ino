int pin = 3;

unsigned long duration;

void setup()
{
  pinMode(pin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  duration = pulseIn(pin, HIGH);
  Serial.println(duration);
}
