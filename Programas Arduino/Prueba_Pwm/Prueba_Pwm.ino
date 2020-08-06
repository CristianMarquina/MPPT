float D=0.71;
float T=28.57;
void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{

  digitalWrite(13, HIGH);
  delayMicroseconds(D*T); // Approximately 10% duty cycle @ 1KHz
  digitalWrite(13, LOW);
  delayMicroseconds((1-D)*T);
}
