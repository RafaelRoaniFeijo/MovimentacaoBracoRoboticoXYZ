int passo = 1;
void acionaMotor()
{
  int dif = atual - grau_Q0;
  int taxa;
  int dif2 = atual2 - grau_Q1;
  int taxa2;
  int dif3 = atual3 - grau_q2;
  int taxa3;

  if (atual > grau_Q0) taxa = -passo;
  else if  (atual < grau_Q0)taxa = passo;

  if (atual2 > grau_Q1) taxa2 = -passo;
  else if  (atual2 < grau_Q1)taxa2 = passo;
  
  if (atual3 > grau_q2) taxa3 = -passo;
  else if  (atual3 < grau_q2)taxa3 = passo;

  if (atual != grau_Q0)
  {
    atual = atual + taxa;
  }
  if (atual2 != grau_Q1)
  {
    atual2 = atual2 + taxa2;
  }
  if (atual3 != grau_q2)
  {
    atual3 = atual3 + taxa3;
  }
  delay(10);
  myservo.write(atual);
  myservo2.write(atual2);
  myservo3.write(atual3);

}

