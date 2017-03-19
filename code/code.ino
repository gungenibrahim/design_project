//ekwfwejhfb
int in1=7;
int in2=6;
int in3=5;
int in4=4;
int e1=3;
int e2=9;
void setup()
{
  Serial.begin(9600);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(e1,OUTPUT);
  pinMode(e2,OUTPUT);
  //int sensorValue1 = analogRead(A1);
  int flag;
 
  
}
class something{//class yazılacak
  
};

void loop()
{
 
   int sensorValue = analogRead(A1);
   int softpotval = analogRead(A2);
   int softpotpres = analogRead(A3);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println("flexsensor");
  Serial.println(sensorValue);
  Serial.println("softpot");
  Serial.println(softpotval);
  Serial.println("softpotpressure");
  Serial.println(softpotpres);
  
  //optimize yapılacak, maximum ve minimum değerler algılanıp referans noktası belirlenecek.
  /*if(flag < 5){
    svalueflex=sensor
  }
*/
float diff2 = softpotval-365;
Serial.println("sadwsa");
  Serial.println(diff2);
float diff1 = sensorValue-500;//flex sensor differences
int difflex = diff1/20;
int difsoftpot = diff2/10;
Serial.println("afsaefeafffafdwafaefeafaef");
  Serial.println(diff1);

int pwm1 = 30+difflex+difsoftpot;
int pwm2= 30-difflex+difsoftpot;
// 10 pwm de yaklasÄ±k 6 cm/saniye yol alÄ±yor
 analogWrite(e1,pwm1);
 analogWrite(e2,pwm2);
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
 
  
  
  
  delay(1);
  
}


