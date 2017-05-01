#include <PID_v1.h>


int in1=7;
int in2=6;
int in3=5;
int in4=4;
int e1=10;
int e2=9;

/////////////////////////////////////////////////
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


int speed_ar(int soft_real){
  
      int a =0;
      if(soft_real > 650){
        a = 1;
      }
      else if(soft_real<550){
        a = -1;
      }
      else{
        a= 0;
      }
      
      return a;
}


int trace_left(void){
  int iB=6;
    pwm1 = 0;
    pwm2 = 0;
  
  iB = serial_read();
  
     if(iB==3){
    
       pwm1 = 30;
       pwm2 = 30;
    }
     else if(iB==5){
       
       pwm1 = 15;
       pwm2 = 30;
    }
    else if(iB==4){
   
    
       pwm1 = 22;
       pwm2 = 30;        
    }
    else if(iB==2){
       pwm1 = 30;
       pwm2 = 22;
    }
    else if(iB==1){
      pwm1 = 30;
      pwm2 = 15 ;
    }
  else if(iB==0){
      pwm1 = 0;
      pwm2 = 0 ;
      }
  
}


void left_role_2()   // left robot operation
{
  
  int iB=0;
  int softpot_dis=0;
  int softpot_real =0;
  int role_select;
  int pwm_ext=0;
  int ref;
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  
  while(1){   // görüntü 0 da iken kesin duracak ayarla
              // soft 0 ken pwmlere 0 ver

        
               iB= serial_read();
               //softpot_dis = soft_read_left();
               softpot_real = soft_read_real(1);
               ref = speed_ar(softpot_real); // softpot değeri balon ortadaysa 0 verir

               pwm1 = 0;
               pwm2 = 0;
       
                if(ref == 0){

                  /// sağ sol aranacak
                  trace_left();
                  
                }
                
                else {

                  if(iB == 0){
                    pwm1 = 0;
                    pwm2 = 0;
                  }
                  else{
                    if(softpot_real == 0 ){
                      pwm1 = 0;
                      pwm2 = 0;
                    }
                    else{
                      pwm1 = 25+15.0*ref;
                      pwm2 = 25+25.0*ref ;
                    }
                    
                  }
                }
                
                
                analogWrite(e1,pwm2);
                analogWrite(e2,pwm1);
                //delay(1000);

                
   
             
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

                pwm2 = 27 -  3*flex_difference*(-1); //sola dogru hareket
                pwm1 = 27 + 7*flex_difference*(-1);
      
        }
      
              
      else if(flex_difference>0){               
                pwm1 =27- 3*flex_difference; //sağa dogru hareket
                pwm2 =27 + 7*flex_difference;
   
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
            

             // delay(1000);

    }
              
}

void loop() // main loop function
{
  int role_select;
  
  role_select=role_checker();

  //Serial.println("aa");
  //Serial.println(role_select);
 
  if(role_select==1)  //right robot role
  {   
        pwm1 = 0;
        pwm2 = 0;
        right_role();  
    }

  if(role_select==0) // left robot role
  {   
      pwm1 = 0;
      pwm2 = 0;
      left_role_2();
  }
}



















