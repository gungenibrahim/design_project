#include <PID_v1.h>


int in1=7;
int in2=6;
int in3=5;
int in4=4;
int e1=10;
int e2=9;
int error;
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=10, Ki=10, Kd=1;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


void setup()
{
  Serial.begin(9600);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(e1,OUTPUT);
  pinMode(e2,OUTPUT);
 

  //initialize the variables we're linked to
  Input = soft_read(1)-650;
  Setpoint = 0;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);

 }



int pwm1,pwm2;
int role;
int extra_pwm_1=0;
int flag_stop = 0;
            

int soft_read(int role) // code for both softpot 0>> right role soft pot, 1>> left role softpot

{			

			int soft_array[10] ={0,0,0,0,0,0,0,0,0,0};
  			
  			/*
            int flag1=0;
            int softpot_total=0;
            int flex_total =0;
            int flex_ave =0;
            int softpot_ave =0;
            */

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
              softpotVal = analogRead(A2);// softpot sensor value for left robot	<<<<<< pini gir

             }   
                

                /*
                           
                if(softpotVal > 0){
                
                soft_array[flag1] =softpotVal;
                 
                }*/
            soft_array[flag1] =softpotVal;
            
            flag1++;
        	}
             
             for(int i=0; i<10; i++){
              softpot_total = softpot_total + soft_array[i];
               
            }
            
            softpot_ave= softpot_total/10;
           

            return softpot_ave;
            
            

}

int flex_read(){
	  		
	  		int flex_array[10] ={0,0,0,0,0,0,0,0,0,0} ;
        	

	  		/*
	  		Serial.println("role_analog"); 
            Serial.println(role_analog);
            int flag1=0;
            int softpot_total=0;
            int flex_total =0;
            int flex_ave =0;
            int softpot_ave =0;
            */

			int flag1=0;

      int flex_total =0;
      int flex_ave =0;
      

            while(flag1<10) 
           {
                int flexVal = analogRead(A1);//flex sensor value
               
               /*Serial.println("flexsensor");
                Serial.println(flexVal);
                */
                           
                flex_array[flag1]= flexVal;
                flag1++;
	        }

            for(int i=0; i<10; i++){
              
              flex_total = flex_total + flex_array[i];
            }

            flex_ave = flex_total/10;
            
            return flex_ave;
            

}





void left_role(){


  
  
  int soft_ref = 650;

  int soft_value = soft_read(1);
  
  error = soft_value-soft_ref;

  Input = error;

  myPID.Compute();

  int speed_diff;

  Serial.println("soft_value");
  Serial.println(soft_value);
  Serial.println("speed_diff");
  Serial.println(speed_diff);

  speed_diff = Output;

  int iB=0;

  int pwm1;
  int pwm2;
  if(Serial.available()>0)
  {iB=Serial.read()-'0';
  Serial.println(iB,DEC);

  
  
    if(iB==3){
  
     pwm1 = 30 +speed_diff;
     pwm2 = 30 +speed_diff;
      Serial.println("33333");
  }
   else if(iB==5){
     
     pwm1 = 15 +speed_diff/2;
     pwm2 = 30 +speed_diff;
      Serial.println("55555");
  }
  else if(iB==4){
 
  
     pwm1 = 22 +speed_diff*2/3;
     pwm2 = 30 +speed_diff; 
     Serial.println("444444");
     
  }
  else if(iB==2){
     pwm1 = 30 +speed_diff;
     pwm2 = 22+speed_diff*2/3;
      Serial.println("22222");
  }
  else if(iB==1){
    pwm1 = 30 +speed_diff;
    pwm2 = 15 +speed_diff/2;
     Serial.println("111111");
  }
else if(iB==0){
    pwm1 = 0;
    pwm2 = 0 ;
     Serial.println("00000");
  }


  Serial.println("pwm111");
  Serial.println(pwm1);
  Serial.println("pwm222");
  Serial.println(pwm2);


  analogWrite(e2,pwm1);
  analogWrite(e1,pwm2);
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  
  
  //delay(1);

}
}

int flex_ave = 0;
    int softpot_ave = 0;
    int extra_ref =0;
    
void right_role(int role_select){

		
		
		    digitalWrite(in1,LOW);
        digitalWrite(in2,HIGH);
        digitalWrite(in3,HIGH);
        digitalWrite(in4,LOW);

        ///////////////////////////////////////////////////
        analogWrite(e1,30);
        analogWrite(e2,30);
          

        //delay(3000); // starting time
         ////////////////////////////////////////////////// 

    
          
           
			      role =0;
                 
          	flex_ave = flex_read(); 
          	softpot_ave = soft_read(role);////////////
           

             int flex_ref = 400; //flex sensor reference value
             if(softpot_ave<700){
             extra_ref = (50/200)*(softpot_ave-650) ;}
             else if(850>softpot_ave>700){
              extra_ref = (50/100)*(softpot_ave-650);
             }
             flex_ref = flex_ref+extra_ref;////   flex referansı kaydırdık

             int flex_difference = flex_ave-flex_ref;
                
                flex_difference = flex_difference/20;
               
               /* Serial.println("flex_difference");
                Serial.println(flex_difference);
				*/

              //arranging turning refereance

              
              int ref_turn =0;
              ///////////////////////////////////////////////////////////////////////////////
            

              if(850<softpot_ave){
                
                extra_pwm_1 = 0;
                 // buraya girerse dursun artÃ„Â±k 

                  digitalWrite(in1,HIGH);
                  digitalWrite(in2,LOW);
                  digitalWrite(in3,LOW);
                  digitalWrite(in4,HIGH);           
              
              softpot_ave = soft_read(role);
               
                while(850<softpot_ave){
                  
               softpot_ave = soft_read(role);
           
              }

                flag_stop = 1; 
                
              }
             

             
              
              ////////////////////////////////////////////////////////////////////////////////////////
            
              while(flag_stop){           // dengeye gelene kadar geri geri gidiyor sonra duruyor
               
               softpot_ave = soft_read(role);

                if(softpot_ave>480){
               // flex_ref = 420;
                extra_pwm_1 = 0;        // hÄ±zlanma referansÄ±
              }

               digitalWrite(in1,LOW);
               digitalWrite(in2,LOW);
               digitalWrite(in3,LOW);
               digitalWrite(in4,LOW);
              
                if( softpot_ave<480){
                                               
                  extra_pwm_1 = 1;
                  
                  flag_stop = 0;
                  }
                
              }

            
              
              
              
              Serial.println("flex_ave");
             Serial.println(flex_ave);
             Serial.println("softpot_ave");
             Serial.println(softpot_ave);
              Serial.println("flex_difference");
             Serial.println(flex_difference);
             
        
        if(flag_stop == 0){

            digitalWrite(in1,LOW);
            digitalWrite(in2,HIGH);
            digitalWrite(in3,HIGH);
            digitalWrite(in4,LOW);

              if(flex_difference>=0){

                  pwm2 = 30 +flex_difference*flex_difference; //dÃ„Â±sa dogru hareket
                  pwm1 = 30;

              
              
              }
              else if(flex_difference<0){               
                  pwm1 =30+ flex_difference*flex_difference; //ice dogru hareket
                  pwm2 =30;
                  
                
                }

                 if(extra_pwm_1){
                    pwm1 == 1.5*pwm1;
                    pwm2 == 1.5*pwm2;
                  }
              }   





             
			        Serial.println("pwm111111111111111111111111111");
             Serial.println(pwm1);
             
             Serial.println("pwm222222222222222222222222222");
             Serial.println(pwm2);

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
                          
        

              //delay(1000);



              
          }




              
int position_control(int s,int f)
{
  
}
int role_checker(){
  int role_analog = analogRead(A5);

  int role_select;

  if(role_analog <500){
    role_select = 0;//role selection pin if high, robot is right role, left otherwise
    
  }
  else if(role_analog>=500){
    role_select =1;
  }


  return role_select;
}



void loop()
{

  int role_select = role_checker();
  
 
  

 Serial.println("role_select");
 Serial.println(role_select);
  
if(role_select==1)  //right robot role
  {
      while(1){
          right_role(role_select);

          role_select = role_checker();
          delay(1000);
          
          if (role_select==0){
              break;   
            } 
         }
  }




  

if(role_select==0)
  {  while(1){   
     left_role();


      role_select = role_checker();
      if (role_select==1){
              break;
            }
      }
  }
}



