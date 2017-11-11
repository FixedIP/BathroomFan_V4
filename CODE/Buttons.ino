int Pozitiv () {
  byte i;
  if (digitalRead(PozitivButton) == HIGH && digitalRead(NegativButton) == LOW)
  {
    delay(50);
    if (digitalRead(PozitivButton) == HIGH && digitalRead(NegativButton) == LOW)
    {
      i = 1;
    }
  }
  else i = 0;
  return i;
}

int Negativ () {
  byte i;
  if (digitalRead(NegativButton) == HIGH && digitalRead(PozitivButton) == LOW)
  {
    delay(50);
    if (digitalRead(NegativButton) == HIGH && digitalRead(PozitivButton) == LOW)
    {
      i = 2;
    }
  }
  else i = 0;
  return i;
}
