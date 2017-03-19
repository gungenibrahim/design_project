
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

/*void loop()
{
if(Serial.available()>0)
{incomingByte=Serial.read()-'0';
incomingByte=incomingByte;
//Serial.print("burakhan recieved: ");
//Serial.println(incomingByte, DEC);


}
}*/

class something{//class yazılacak
  
};

void loop()
{   int iB=0;

  int pwm1;
  int pwm2;
  if(Serial.available()>0)
  {iB=Serial.read()-'0';
  Serial.println(iB,DEC);

  
  
    if(iB=3){
  
     pwm1 = 30;
     pwm2 = 30;
  }
   else if(iB=5){
     
     pwm1 = 15;
     pwm2 = 30;
  }
  else if(iB=4){
 
  
     pwm1 = 22;
     pwm2 = 30;
  }
  else if(iB=2){
     pwm1 = 30;
     pwm2 = 22;
  }
  else if(iB=1){
    pwm1 = 30;
    pwm2 = 15 ;
  }

  else{
  
  }
  
  analogWrite(e1,pwm1);
  analogWrite(e2,pwm2);
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  
  
  delay(1);
  
}
}
