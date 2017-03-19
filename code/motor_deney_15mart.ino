
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
{   int iB=6;
  if(Serial.available()>0)
  {iB=Serial.read()-'0';
  Serial.println(iB,DEC);

  
  
  if(iB=3){
  
  analogWrite(e1,30);
  analogWrite(e2,30);
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  }
   if(iB=1){
     
  analogWrite(e1,15);
  analogWrite(e2,30);
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  }
  if(iB=2){
  analogWrite(e1,20);
  analogWrite(e2,30);
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  }
  if(iB=4){
  analogWrite(e1,30);
  analogWrite(e2,20);
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  }
  if(iB=5){
  analogWrite(e1,30);
  analogWrite(e2,15);
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  }
  
  
  
  delay(1);
  
}
}
