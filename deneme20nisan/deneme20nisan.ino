int in1=7;
int in2=6;
int in3=5;
int in4=4;
int e1=8;
int e2=9;
int role_select=1;


void setup() {
 Serial.begin(9600);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(e1,OUTPUT);
  pinMode(e2,OUTPUT);
  pinMode(role_select,INPUT);
  int flag;
 }
 
int pwm1,pwm2;
int role;
int extra_pwm_1=0;
int flag_stop = 0;

int softpot_read(int role)
{  int soft_array[10] ={0,0,0,0,0,0,0,0,0,0};
   int a=0;
   int softpotVal_2 = analogRead(A2);
   Serial.println("softpotVal_1");
  // Serial.println(softpotVal_2);
      int flag1=0;
      int softpotVal = 0;
      int softpot_total =0;
      int softpot_ave=0;
    while(flag1<10)
    {
      soft_array[flag1]=softpotVal_2;
      flag1++;
    }
      for(int i=0;i<10;i++)
      softpot_total=softpot_total+soft_array[i];
      
      softpot_ave=softpot_total/10;
      
   if(softpot_ave>450 &&  softpot_ave<520)
    a=1;
   if(softpot_ave>520 && softpot_ave<570)
    a=2;
   if(softpot_ave>570 && softpot_ave<680)
    a=3;
    if(680<softpot_ave && softpot_ave<820)
    a=4;
    if(softpot_ave>820)
    a=5; 
    if(softpot_ave==0)
    a=0;
     
   return a;
  }
int flex_read()
{
  int flex_array[10] ={0,0,0,0,0,0,0,0,0,0} ;
  int flag1=0;
  int flex_total =0;
  int flex_ave =0;
  int b=0;
  while(flag1<10) 
           {
                int flexVal = analogRead(A1);//flex sensor value
                flex_array[flag1]= flexVal;
                flag1++;
          }
  for(int i=0;i<10;i++)
      flex_total=flex_total+flex_array[i];

      flex_ave=flex_total/10;

      if(flex_ave> && flex_ave<)


      return b;
}
  void right_role(int rl)
  {
    int flex_ave=0;
    int softpot_ave=0;
    int extra_ref =0;

        digitalWrite(in1,LOW);
        digitalWrite(in2,HIGH);
        digitalWrite(in3,HIGH);
        digitalWrite(in4,LOW);

        analogWrite(e1,30);
        analogWrite(e2,30);

        delay(3000);

        while(1)
        {
          
          }
        

    
  }

  
void loop() {
 

  
  int role_analog = analogRead(A5);

  int role_select;

  if(role_analog <500){
    role_select = 0;//role selection pin if high, robot is right role, left otherwise
    
  }
  else if(role_analog>=500){
    role_select =1;
  }

 Serial.println("role_select");
 Serial.println(role_select);
  
  if(role_select==1)  //right robot role
  {
          right_role(role_select);
          
             
        }

}
