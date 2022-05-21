#include <Servo.h>
#include <EEPROM.h>

#include <math.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;


float atual;
float atual2;
float atual3;
////////////////////////////////////////////
//funçoes primeiras equações
float hip;
float ang1;
float ang2;
float angfin;
float x = 0;
float y = 0;
float z = 0;
double ang_q2;
float a1 = 105;
float a2 = 90;
//float a3 = 90;
float ex;
float x_quad;
float y_quad;
float a1_quad;
float a2_quad;
float soma;
float baixo;
float divide;
float grau_q2 = 0;
const float pi = 3.1415926535897932384626433832795;
float div_q1;
float var_atanq1;
float va_a2sinq2_Q1;
float var_a2cosq2a1_Q1;
float ATAN_fracao_Q1;
float ang_Q1;
float grau_Q1 = 0;
////////////////////////////////////////////
//3D
float grau_Q0 = 0;
float z_quad;
float divisao;
float cos_Q0;
float divid_Q0;
float quadrado_Q0;
float rot;
float soma_a1_a2;
float soma_total;
//float baixo;
//float grau_Q1 = 0;
//float grau_q2 = 0;
//float x_quad;
//float y_quad;
//float a1_quad;
//float a2_quad;
float divide_tudo;
float divisao2;
float div3;
float parte1_do_q1;
float seno_do_q2;
float mult_com_a2;
float cosseno_do_q2;
float mult_com_a2_dois;
float soma_com_a1;
float divis4;
float parte2_do_q1;
float rad_Q0;
float rad_Q2;
float rad_Q1;

/////////////////////////////////////////////
//funçoes primeiras equações

//////////////////////////////////////////////
//funçoes sengunda equação
/*float x_pot;
  float y_pot;
  float a1_pot;
  float a2_pot;
  float soma_dois;
  float baixo_dois;
  float divide_dois;
  float ang_q2_dois;
  float grau_q2_dois;
  //q1
  float div_q1_seg;
  float var_atanq1_seg;
  float va_a2sinq2_Q1_seg;
  float var_a2cosq2a1_Q1_seg;
  float ATAN_fracao_Q1_seg;
  float ang_Q1_seg;
  float grau_Q1_seg;*/

void setup() {

  myservo.attach(8);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(9);
  myservo3.attach(10);

  atual = EEPROM.read(0);
  atual2 = EEPROM.read(1);
  atual3 = EEPROM.read(2);

  grau_Q0  = atual;
  grau_Q1  = atual2;
  grau_q2 = atual3;

  Serial.begin(9600);
}

int comando = 0;

void loop() {



  if (Serial.available() > 0) {
    comando = Serial.parseFloat();

    if (comando == 1)
    {
      x = 0;
      y = 195;
      z = 0;
    }


    if (comando == 2)  x = Serial.parseFloat(), y = Serial.parseFloat(), z = Serial.parseFloat();


    calcula_ang_q2_q1();

    EEPROM.write(0, grau_Q0), EEPROM.write(1, grau_Q1), EEPROM.write(2, grau_q2);
    Serial.readString();
  }

  acionaMotor();

}
void calcula_ang_q2_q1() {
  /////////////////Q0/////////////////////
  divisao = (x / y);
  rad_Q0 = atan(divisao);
  grau_Q0 = ((rad_Q0 * 180) / pi) / 1.1;
  //rot
  cos_Q0 = cos(rad_Q0);
  z_quad = pow(z, 2);
  divid_Q0 = (y / cos_Q0);
  quadrado_Q0 = pow(divid_Q0, 2);
  rot = (quadrado_Q0 + z_quad);

  ////Q2
  x_quad = pow(x, 2);
  y_quad = pow(y, 2);
  a1_quad = pow(a1, 2);
  a2_quad = pow(a2, 2);
  soma = (quadrado_Q0 + z_quad + (-a1_quad - a2_quad));

  if (soma > 18900) {
    soma = 18900;
  }
  baixo = 2 * (a1 * a2);
  divide = (soma / baixo);
  ang_q2 = acos(divide);//onde apresenta erro
  grau_q2 = ((ang_q2 * 180) / pi)* 1.05 + 120;

  /*if (120 <= grau_Q1 <= 145) {
    grau_q2;

  }
  else {
    Serial.println("fora do aceitavel");
  }*/


  ////Q1

  div_q1 = (z / divid_Q0);
  var_atanq1 = atan(div_q1);
  va_a2sinq2_Q1 = a2 * sin(ang_q2);
  var_a2cosq2a1_Q1 = a2 * cos(ang_q2) + a1;
  ATAN_fracao_Q1 = atan(va_a2sinq2_Q1 / var_a2cosq2a1_Q1);
  ang_Q1 = (var_atanq1 - ATAN_fracao_Q1);
  grau_Q1 = ((ang_Q1 * 180) / pi) * 1.1 + 48 ;


  /*if (48 <= grau_Q1 <= 120) {
    grau_Q1;
  }
  else {
    Serial.println("fora do aceitavel");
  }*/







  Serial.print("Q0=");
  Serial.println(grau_Q0 * 1.1) ;
  Serial.print("Q1=");
  Serial.println((grau_Q1 - 48) / 1.1);
  Serial.print("Q2=");
  Serial.println((grau_q2 - 120) *1.05);
 /* Serial.println(x_quad);
  Serial.println(y_quad);
  Serial.println(a1_quad);
  Serial.println(a2_quad);
  Serial.println(quadrado_Q0);
  Serial.println(soma);
  Serial.println(baixo);
  Serial.println(divide);
  Serial.println(ang_q2);//erro
  Serial.println(div_q1);
  Serial.println(var_atanq1);
  Serial.println(va_a2sinq2_Q1);
  Serial.println(var_a2cosq2a1_Q1);
  Serial.println(ATAN_fracao_Q1);
  Serial.println(ang_Q1);
  Serial.println(grau_Q1);*/
}












/* ////Q2
  x_quad = pow(x, 2);
  y_quad = pow(y, 2);
  a1_quad = pow(a1, 2);
  a2_quad = pow(a2, 2);
  soma = (x_quad + y_quad) + (-a1_quad - a2_quad);
  baixo = 2 * (a1 * a2);
  divide = (soma / baixo);
  ang_q2 = acos(divide);
  grau_q2 = ((ang_q2 * 180) / pi) * 1.05 + 120;

  if (120 <= grau_Q1 <= 145) {
  grau_q2;

  }
  else {
  Serial.println("fora do aceitavel");
  }


  ////Q1

  div_q1 = (y / x);
  var_atanq1 = atan(div_q1);
  va_a2sinq2_Q1 = a2 * sin(ang_q2);
  var_a2cosq2a1_Q1 = a2 * cos(ang_q2) + a1;
  ATAN_fracao_Q1 = atan(va_a2sinq2_Q1 / var_a2cosq2a1_Q1);
  ang_Q1 = (var_atanq1 - ATAN_fracao_Q1);
  grau_Q1 = ((ang_Q1 * 180) / pi) * 1.1 + 48;


  if (48 <= grau_Q1 <= 120) {
  grau_Q1;
  }
  else {
  Serial.println("fora do aceitavel");
  }

  //atan de div_x
  //Serial.println (div_q1);
  //Serial.println(var_atanq1);
  //Serial.println(va_a2sinq2_Q1);
  // Serial.println(var_a2cosq2a1_Q1);
  //Serial.println(ATAN_fracao_Q1);
  //Serial.println(ang_Q1);
  Serial.print("Q1=");
  Serial.println((grau_Q1 - 48)/ 1.1);

  //Serial.print atan(div_q1);
  //Serial.print("div_x=");

  //Serial.println(x_quad);
  //Serial.println(y_quad);
  //Serial.println(a1_quad);
  //Serial.println(a2_quad);
  //Serial.println(soma);
  //Serial.println(baixo);
  //Serial.println(divide);
  //Serial.println(ang_q2);
  Serial.print("Q2=");
  Serial.println((grau_q2 - 120)* 1.05) ;


  /* Serial.print("Q2=");
  Serial.println(ang_q2);
  Serial.println(x);
  Serial.println(y);
  Serial.print("hip=");
  Serial.println(hip);
  Serial.print("ang1=");
  Serial.println(ang1);
  Serial.print("ang2=");
  Serial.println(ang2);
  Serial.println(105);
  Serial.println(90);
  delay(3000);

  }*/

/*void calcula_q1_q2_seg_solucao () {

  //Q2
  x_pot = pow(x, 2);
  y_pot = pow(y, 2);
  a1_pot = pow(a1, 2);
  a2_pot = pow(a2, 2);
  soma_dois = (x_pot + y_pot) - (a1_pot + a2_pot);
  baixo_dois = 2 * (a1 * a2);
  divide_dois = (soma_dois / baixo_dois);
  ang_q2_dois = -acos(divide_dois);
  grau_q2_dois = (ang_q2_dois * 180) / pi;
  Serial.print("Q2=");
  Serial.println(grau_q2_dois);

  //Q1
  div_q1_seg = (y / x);
  var_atanq1_seg = atan(div_q1_seg);
  va_a2sinq2_Q1_seg = a2 * sin(ang_q2_dois);
  var_a2cosq2a1_Q1_seg = a2 * cos(ang_q2_dois) + a1;
  ATAN_fracao_Q1_seg = atan(va_a2sinq2_Q1_seg / var_a2cosq2a1_Q1_seg);
  ang_Q1_seg = (var_atanq1_seg + ATAN_fracao_Q1_seg);
  grau_Q1_seg = (ang_Q1_seg * 180) / pi;
  Serial.print("Q1_2=");
  Serial.println(grau_Q1_seg);
  delay(3000);
  }*/
