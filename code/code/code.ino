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

/*class something{//class yazılacak
  
};*/

void loop()
{
 
   int sensorValue = analogRead(A1);
   int softpotval = analogRead(A2);
   int stopflag =0;
  
  // print out the value you read:
  Serial.println("flexsensor");
  Serial.println(sensorValue);
  Serial.println("softpot");
  Serial.println(softpotval);
  int pwm1,pwm2;  

float softdistance = (softpotval-100)/20;
Serial.println("softpotcm");
  Serial.println(softdistance);
float diff1 = sensorValue-375;//flex sensor differences
int difflex = diff1/15;

Serial.println("flexsensor");
  Serial.println(difflex);

if(470>softpotval>180){
  difflex = difflex*8/softdistance;
     
 }

 if(diff1 >0){
         pwm2 = 30+difflex*difflex*difflex;
         pwm1 = 30;}
     else{
         pwm1 = 30+4*difflex*difflex;
         pwm2 = 30;
     }
 
if(softpotval<120){
  pwm1= pwm1 =0;
  pwm2= pwm2 =0;}


 Serial.println(pwm2);
  








  
// 10 pwm de yaklasÄ±k 6 cm/saniye yol alÄ±yor
 analogWrite(e1,pwm1);
 analogWrite(e2,pwm2);
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
 
  
  
  
  delay(1000);
  
}


