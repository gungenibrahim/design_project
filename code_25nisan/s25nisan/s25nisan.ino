#include <PID_v1.h>


int in1=7;
int in2=6;
int in3=5;
int in4=4;
int e1=10;
int e2=9;

double Setpoint1, Input1, Output1;
double aggKp=6, aggKi=8, aggKd=10; //best ---> 8 8 10
double consKp=1, consKi=1, consKd=1;
PID myPID_soft_left(&Input1, &Output1, &Setpoint1, consKp, consKi, consKd,REVERSE);

double Setpoint2,Input2,Output2;
double agg2Kp= 5 , agg2Ki=1, agg2Kd=0.5; //1,0.5,
double cons2Kp= 5, cons2Ki=1, cons2Kd=0.5;
PID myPID_camera(&Input2, &Output2, &Setpoint2, cons2Kp, cons2Ki, cons2Kd, REVERSE);

int pwm1;
int pwm2;
int role;
int extra_pwm_1=0;
int role_select;


//functions
/*int role_checker();
int soft_read_real(int role);
int soft_read_left();
int soft_read_right(); 
int serial_read(void);
int flex_read();
int left_assistant();
void left_role_2();
int soft_to_flex_ref(int s);
void starting_right(int time1);
*/

void setup()
{
  Serial.begin(9600);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(e1,OUTPUT);
  pinMode(e2,OUTPUT);
  myPID_camera.SetMode(AUTOMATIC);
  myPID_soft_left.SetMode(AUTOMATIC);
    
  Setpoint2=3;
  Setpoint1=3;
  Input1=soft_read_left();
  Input2=serial_read();
}

void pwm_generator(int soft, int camera){
  pwm1=30;
  pwm2=30;
  if(soft==0 || camera ==0){
    pwm1 =0;
    pwm2 =0;
  }
  else{
    if(soft == 1){
      pwm1 =0;
      pwm2 =0;
    }
    else if(soft==2){
      pwm1 =pwm1*3/4;
      pwm2 =pwm2*3/4;
    }
    else if(soft==3)
    {
      pwm1 =pwm1;
      pwm2 =pwm2;
    }
    else if(soft==4)
    {
      pwm1 =pwm1*5/4;
      pwm2 =pwm2*5/4;
    }
    else {
      pwm1 =pwm1*4/3;
      pwm2 =pwm2*4/3;
    }

    if(camera == 1){
      pwm1 =pwm1;
      pwm2 =pwm2/2;
    }
    else if(camera==2){
      pwm1 =pwm1;
      pwm2 =pwm2*3/4;
    }
    else if(camera==3)
    {
      pwm1 =pwm1;
      pwm2 =pwm2;
    }
    else if(camera==4)
    {
      pwm1 =pwm1*4/3;
      pwm2 =pwm2;
    }
    else {
      pwm1 =pwm1/2;
      pwm2 =pwm2;
    }
      
  }
  
  
}





int role_checker() // decide robot will run which operation
{ 
  int role_analog = analogRead(A5);
    
    if(role_analog <500){
    role_select = 0;//role selection pin if high, robot is right role, left otherwise
    
    }
    else if(role_analog>=500){
    role_select =1;
    }

    return role_select;
} 

int soft_read_real(int role) // code for both softpot reading (0):right role soft pot, (1): left role softpot
{      
      int a;
      int soft_array[10] ={0,0,0,0,0,0,0,0,0,0};
        
  
      int flag1=0;
      int softpotVal = 0;
      int softpot_total =0;
      int softpot_ave=0;
    
            while(flag1<10)
            { 
            
         if(role == 0){
          softpotVal = analogRead(A0);// softpot sensor value for right robot
             }
         else if(role == 1){
          softpotVal = analogRead(A2);// softpot sensor value for left robot  <<<<<< pini gir

             }   
                
            soft_array[flag1] =softpotVal;
            
            flag1++;
          }
             
             for(int i=0; i<10; i++){
        softpot_total = softpot_total + soft_array[i];

            }
      
      softpot_ave= softpot_total/10;
                

    return softpot_ave;
}



int glob_soft_left;
int soft_read_left() // discrete values of the softpot on the left
{      
      int a;
      int soft_array[10] ={0,0,0,0,0,0,0,0,0,0};

      int flag1=0;
      int softpotVal = 0;
      int softpot_total =0;
      int softpot_ave=0;
            while(flag1<10)
            { 
          
            softpotVal = analogRead(A2);// softpot sensor value for left robot  <<<<<< pini gir


            soft_array[flag1] =softpotVal;
            
            flag1++;
          }
             
            for(int i=0; i<10; i++){
              softpot_total = softpot_total + soft_array[i];

            }
      
            softpot_ave= softpot_total/10;
                
       if(softpot_ave>400 &&  softpot_ave<520)
       a=1;
       else if(softpot_ave>520 && softpot_ave<570)
       a=2;
       else if(softpot_ave>570 && softpot_ave<680)
       a=3;
       else if(680<softpot_ave && softpot_ave<820)
       a=4;
       else if(softpot_ave>820)
       a=5; 
       else if(softpot_ave==0)
       a=0;
   
    
   /*    if(a != 0){
          glob_soft_left = a;
       }
       
     */ 
   return a;        //     glob_soft_left;
}

int glob_soft_right;
int soft_read_right() // discrete values of the softpot on the right
{      
      int a;
      int soft_array[10] ={0,0,0,0,0,0,0,0,0,0};

      int flag1=0;
      int softpotVal = 0;
      int softpot_total =0;
      int softpot_ave=0;
            while(flag1<10)
            { 
          
            softpotVal = analogRead(A0);// softpot sensor value for left robot  <<<<<< pini gir


            soft_array[flag1] =softpotVal;
            
            flag1++;
          }
             
            for(int i=0; i<10; i++){
              softpot_total = softpot_total + soft_array[i];

            }
      
            softpot_ave= softpot_total/10;
                
       if(softpot_ave>380 &&  softpot_ave<420)
       a=1;
       else if(softpot_ave>420 && softpot_ave<515)
       a=2;
       else if(softpot_ave>515 && softpot_ave<720)
       a=3;
       else if(softpot_ave>720 && softpot_ave<800)
       a=4;
       else if(softpot_ave>800)
       a=5; 
       else if(softpot_ave==0)
       a=0;

       
        if(a != 0){
          glob_soft_right = a;
        }
       
      
    return glob_soft_right;
}

int serial_read(void) //read serial data from raspi
{ 
  
  int iB=6; 
         if(Serial.available()>0)
              {               
                iB=Serial.read()-'0';  
              }
  delay(120);

  
  return iB;  
}

int glob_loc;

float flex_read()  //read flex sensor real values
{
        
      int flex_array[10] ={0,0,0,0,0,0,0,0,0,0} ;

      int flag1=0;

      int flex_total =0;
      int flex_ave =0;
      int  loc; 
  
            while(flag1<10) 
           {
                int flexVal = analogRead(A1);//flex sensor value
                flex_array[flag1]= flexVal;
                flag1++;
           }

            for(int i=0; i<10; i++){
              
              flex_total = flex_total + flex_array[i];
            }

            flex_ave = flex_total/10;

            if(flex_ave>520){
              loc=1.0;
            }
            else if(flex_ave<=520 && flex_ave>470){
              loc=2.0;
            }
            else if(flex_ave<=470 && flex_ave>430){
              loc=3.0;
            }
            else if(flex_ave<=430 && flex_ave>403){
              loc=4.0;
            }
            else if(flex_ave<=403){
              loc=5.0;
            }

            if(loc != 0.0){
              glob_loc =loc;
            }

            Serial.println("loc");
            Serial.println(loc);

             Serial.println("glob_loc");
            Serial.println(glob_loc);
            
                        
            return glob_loc;
}


int left_assistant() // arrange flex sensor refereance speed
{
  int ref=0;
  if(ref >0 ){
    
  int konum = soft_read_left();
  ref = konum -3;
  ref = ref*3;
  }
  return ref;
}

void left_role_2()   // left robot operation
{
  
  int iB=0;
  int softpot_avg_Val_2=0;
  int role_select;
  int pwm_ext=0;
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  
  while(1){
/* 
  myPID_soft_left.SetOutputLimits(0,40);
  myPID_camera.SetOutputLimits(-10,10);
   
   
       
                softpot_avg_Val_2 = soft_read_left(); //discrete okuyan, pid input1
                Input1 = softpot_avg_Val_2;
        
                iB= serial_read();
            
  
                double gap = abs(Setpoint1-Input1); //distance away from setpoint
                  
                if (gap <2)
                {  //we're close to setpoint, use conservative tuning parameters
                  myPID_soft_left.SetTunings(consKp, consKi, consKd);
                }         
                 else
                {
                   //we're far from setpoint, use aggressive tuning parameters
                   myPID_soft_left.SetTunings(aggKp, aggKi, aggKd);
                }
          
                myPID_soft_left.Compute();

                pwm1 = Output1;
                pwm2 = Output1;

                
               
                 
                Input2=iB;
                double gap2=abs(Setpoint2-Input2);
                if(gap2<2)
                {
                  myPID_camera.SetTunings(cons2Kp, cons2Ki, cons2Kd);
                }
                else
                {
                  myPID_camera.SetTunings(agg2Kp, agg2Ki, agg2Kd);                  
                }
                                 
                 myPID_camera.Compute();
                
                  
                 pwm_ext=Output2;
          
        pwm1=pwm1-pwm_ext/4;
        pwm2=pwm2 + pwm_ext;

   */     
              //  Serial.println("IB");
               // Serial.println(iB);
                //Serial.println("Output1");
               // Serial.println(Output1);
               // Serial.println("Output2, sol teker extra");
               // Serial.println(Output2);
               // delay(1000);
                
                /*
                if(iB==3){
                    pwm1 = pwm1;
                    pwm2 = pwm2 +ref;
                  }
                  
                  if(iB==4){
                    pwm1 = 4/5*pwm1;
                    pwm2 = pwm2*5/3+ref;
                  }
                  
                  if(iB==5){
                    pwm1 = 4/6*pwm1;
                    pwm2 = pwm2*5/2+ref;
                  }
                  
                  if(iB==1){
                    pwm1 = 6/4*pwm1;
                    pwm2 = pwm2/5*2+ref;
                  }
                  
                  if(iB==2){
                    pwm1 = 5/4*pwm1;
                    pwm2 = pwm2*3/5+ref;
                  }

                  if(iB ==0){
                    pwm1=0;
                    pwm2=0;
                  }
             */
                  
                 //
                 int ref  = left_assistant();
        
                   iB= serial_read();
                   softpot_avg_Val_2 = soft_read_left();
                   pwm_generator(softpot_avg_Val_2,iB);
                      
                
                pwm2 =pwm2+ref;
                
                analogWrite(e1,pwm2);
                analogWrite(e2,pwm1);
                delay(1000);

                
   
             
              Serial.println("pwm1");
                Serial.println(pwm1);
                Serial.println("pwm2");
                Serial.println(pwm2);
          
  
            role_select=role_checker();                       
            if (role_select==1){
              break;
              }
      
          }

  
  }
  
int soft_to_flex_ref(int s)//initialize for 420 value of flex sensor
{     

        double p1;
        double p2;
        double p3 ;
        double p4 ;
        double p5 ;
    p1 =   2.428e-09;
    p2 =  -6.439e-06;
    p3 =    0.006431;
    p4 =       -2.76;
    p5 =       833.7;

        int a=(p1*pow(s,4)+p2*pow(s,3)+p3*pow(s,2)+p4*pow(s,1)+p5);


         return a;
}
   
void starting_right(int time1) // starting time pwm arrange 
{
  
  int flag = 0; 
  
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
  
  
  while(flag<10)
  {
   
    analogWrite(e1,30);
    analogWrite(e2,30);
        
  

    delay(time1); // starting time
    
    flag++; 
  }
  
  

}
   
void right_role() //right role operation of the robot
{

    float flex_ave = 0.0;
    int softpot_real = 0;
    int softpot_dis = 0;
  
  
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
  
  
 // starting_right(3000);
  
    
    while(1){
        
    int flag_stop = 0;
    int ref_turn =0; 
    float flex_ref = 0.0;
    float flex_difference = 0.0;
       
       
                     
        flex_ave = flex_read(); // artık discrete okuyoruz
        Serial.println("flex_ave");
        Serial.println(flex_ave);
        
        
        softpot_real = soft_read_real(0);//sağ soft okunuyor 0 ile
        softpot_dis = soft_read_right();
        Serial.println(softpot_dis);
        flex_ref = soft_to_flex_ref(softpot_real); //flex sensor reference value change with softpot 
        
        
        if(softpot_dis <3){
          flex_ref=3.5;
        }
        else if(softpot_dis == 3 ){
          flex_ref=3.0;
        }
        else if(softpot_dis == 4 ){
          flex_ref =2.0;
        }
        else{
          flex_ref =1.0;
        }
        
        
        
        flex_difference = flex_ave - flex_ref;
    
    extra_pwm_1 = 0;
    
    if(softpot_dis == 3)
    {                
        extra_pwm_1 = 0;
        }
        
    if(softpot_dis==1)
    {
       
        extra_pwm_1 = 1;        // hızlanma referansı
        
    }
        
    if(softpot_dis==5){
            extra_pwm_1 = 0;
                 // buraya girerse dursun artÄ±k  
            pwm1 = 0;
            pwm2 = 0;

      flag_stop = 1; 
      
    }
          
      analogWrite(e1,pwm2);
      analogWrite(e2,pwm1);

  
    while(softpot_dis>4){////3te harekete dön
      softpot_dis = soft_read_right();

      if(softpot_dis<=3){
        flag_stop=0;
      }      
    }

//pwm2 --> sol teker
//pwm1--> sağ teker
    
      if(flag_stop == 0){

      if(flex_difference<=0){

                pwm2 = 27 -  flex_difference*(-1); //sola dogru hareket
                pwm1 = 27 + 6*flex_difference*(-1);
      
        }
      
              
      else if(flex_difference>0){               
                pwm1 =27-flex_difference; //sağa dogru hareket
                pwm2 =27 + 6*flex_difference;
   
        }
             
      }
                  
              
       

                 
      if (softpot_dis == 0){
                     
                pwm1 = 0;
                pwm2 = 0;            
      }

              
        analogWrite(e1,pwm2);
        analogWrite(e2,pwm1);
             
       Serial.println("pwm1");
       Serial.println(pwm1);
       Serial.println("pwm2");
       Serial.println(pwm2);

      role_select=role_checker();                        
            if (role_select==0)
                  break;
            

              delay(1000);

    }
              
}

void loop() // main loop function
{
  int role_select;
  
  role_select=role_checker();

  Serial.println("aa");
  Serial.println(role_select);
 
  if(role_select==1)  //right robot role
  {
        right_role();  
    }

  if(role_select==0) // left robot role
  {   
      left_role_2();
  }
}



















