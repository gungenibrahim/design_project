int in1=7;
int in2=6;
int in3=5;
int in4=4;
int e1=10;
int e2=9;
int role_select=1; //role selection pin if high, robot is right role, left otherwise
void setup()
{
  Serial.begin(9600);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(e1,OUTPUT);
  pinMode(e2,OUTPUT);
  int flag;
 
  
}

int position_control(int s,int f)
{
  
}
void loop()
{
  int role_analog = analogRead(A5);
  Serial.println(role_analog);
  if(role_analog <500){
    int role_select = 0;
    
  }
  else if(role_analog>=500){
    int role_select =1;
  }

  int pwm1,pwm2;
  
  if(role_select==1)  //right robot role
  {
          digitalWrite(in1,LOW);
          digitalWrite(in2,HIGH);
          digitalWrite(in3,HIGH);
          digitalWrite(in4,LOW);

          /*analogWrite(e1,30);
          analogWrite(e2,30);
          

          delay(3000); // starting time
*/

          
          int flex_array[10] ;
          int soft_array[10];

          for(int i=0;i<10;i++){
            flex_array[i] = 0;
            soft_array[i] = 0;
          }


       

          while(1){
            int flag1=0;
            int softpot_total=0;
            int flex_total =0;
            int flex_ave =0;
             int softpot_ave =0;
            while(flag1<10) 
          {
                int flexVal = analogRead(A1);//flex sensor value
                int softpotVal = analogRead(A2);// softpot sensor value for right robot
                /*Serial.println("flexsensor");
                Serial.println(flexVal);
                */
               
                
                int pwm1,pwm2;
                flex_array[flag1]= flexVal;
                if(softpotVal > 0){
                
                soft_array[flag1] =softpotVal;
                 
                }

                flag1++;
            }
            
            //int flexVal = analogRead(A1);//flex sensor value

            for(int i=0; i<10; i++){
              softpot_total = softpot_total + soft_array[i];
              flex_total = flex_total + flex_array[i];
            }
            flex_ave = flex_total/10;
            softpot_ave= softpot_total/10;


             
              //int softPot_1_Position=map(softpotVal,180,580,0,400);
              
              int flexposition=map(flex_ave,300,600,0,300);

              int flex_ref = 180; //flex sensor reference value

              int flex_difference = flexposition-flex_ref;

              //arranging turning refereance

              int flag_stop = 0;
              int ref_turn =0;

              if(316>softpot_ave>250){ 
                ref_turn = 0;
              }
              else if(200<softpot_ave<250){
                flex_ref = 200;
                ref_turn = -7;
              }
              else if(200<softpot_ave<250){
                pwm1 =0;
                pwm2 =0;
                flag_stop =1;  // buraya girerse dursun artık 
              }



              if(flag_stop == 0){

              if(flex_difference>=0){

                  pwm2 = 30 + flex_difference*flex_difference*flex_difference +ref_turn; //dısa dogru hareket
                  pwm1 =20+ref_turn;
              }
              else if(flex_difference<400){
                  pwm1 =30+ 4*flex_difference*flex_difference +ref_turn; //ice dogru hareket
                  pwm2 =30 +ref_turn;
                }
              }     



             /*
              //shows object location on softpot sensor
              Serial.println("distance");
              Serial.println(softPotPosition);
              position_control(softPotPosition,flexposition);

              if(softPotPosition==0)
              {
                pwm1=0;
                pwm2=0;
              }
              if(flexposition)
              {

              }

        */


              analogWrite(e1,pwm1);
              analogWrite(e2,pwm2);
                          
            //  if (role_select==0){
            //    break;
            //  }

              delay(1000);
        }
//  }
  

if(role_select==0)
  {     
      int iB=0;
      int pwm1;
      int pwm2;
      int softpotVal_2;
       digitalWrite(in1,LOW);
       digitalWrite(in2,HIGH);
       digitalWrite(in3,HIGH);
       digitalWrite(in4,LOW);
       
      if(Serial.available()>0)
      {
        if(iB==3)
        {
          softpotVal_2=analogRead(A0);
          if(220<softpotVal_2<260)
          {
            pwm1=30;
            pwm2=30;
          }
          else if(softpotVal_2>260)
          {
            pwm1=30+8;
            pwm2=30+8;
          }
          else if(softpotVal_2<220)
          {
            pwm1=30-8;
            pwm2=30-8;
          }
          
        }
        if(iB==5)
        {
          softpotVal_2=analogRead(A0);
          if(220<softpotVal_2<260)
          {
            pwm1=15;
            pwm2=30;
          }
          else if(softpotVal_2>260)
          {
            pwm1=15+8;
            pwm2=30+16;
          }
          else if(softpotVal_2<220)
          {
            pwm1=15-4;
            pwm2=30-8;
          }
          
        }
        if(iB==4)
        {
          softpotVal_2=analogRead(A0);
          if(220<softpotVal_2<260)
          {
            pwm1=22;
            pwm2=30;
          }
          else if(softpotVal_2>260)
          {
            pwm1=22+4;
            pwm2=30+6;
          }
          else if(softpotVal_2<220)
          {
            pwm1=22-4;
            pwm2=30-6;
          }
          
        }
        if(iB==2)
        {
          softpotVal_2=analogRead(A0);
          if(220<softpotVal_2<260)
          {
            pwm1=30;
            pwm2=22;
          }
          else if(softpotVal_2>260)
          {
            pwm1=30+6;
            pwm2=22+4;
          }
          else if(softpotVal_2<220)
          {
            pwm1=30-6;
            pwm2=22-4;
          }
          
        }
        if(iB==1)
        {
          softpotVal_2=analogRead(A0);
          if(220<softpotVal_2<260)
          {
            pwm1=30;
            pwm2=15;
          }
          else if(softpotVal_2>260)
          {
            pwm1=30+16;
            pwm2=15+8;
          }
          else if(softpotVal_2<220)
          {
            pwm1=30-8;
            pwm2=15-4;
          }
          
        }
        analogWrite(e1,pwm1);
        analogWrite(e2,pwm2);

      }
  }
}
}
