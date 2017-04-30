#include <PID_v1.h>


int in1=7;
int in2=6;
int in3=5;
int in4=4;
int e1=10;
int e2=9;

double Setpoint1, Input1, Output1;
double aggKp=6, aggKi=8, aggKd=10; //best ---> 8 8 10
double consKp=8, consKi=8, consKd=8;
PID myPID_soft_left(&Input1, &Output1, &Setpoint1, consKp, consKi, consKd,REVERSE);

double Setpoint2,Input2,Output2;
double agg2Kp=  20, agg2Ki=5, agg2Kd=15;
double cons2Kp= 20, cons2Ki=5, cons2Kd=15;
PID myPID_camera(&Input2, &Output2, &Setpoint2, cons2Kp, cons2Ki, cons2Kd, DIRECT);


int pwm1;
int pwm2;
int role;
int extra_pwm_1=0;
int role_select;


//functions
int role_checker();
int soft_read_real(int role);
int soft_read_left();
int soft_read_right(); 
int serial_read(void);
int flex_read();
int left_assistant();
void left_role_2();
int soft_to_flex_ref(int s);
void starting_right(int time);


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
	Input1=soft_read(1);
	//Input2=serial_read();
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
      
    return a;
}

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
      
    return a;
}

int serial_read(void) //read serial data from raspi
{ 
  
  int iB=0; 
         if(Serial.available()>0)
              {               
                iB=Serial.read()-'0';  
              }
	delay(70);

	
	return iB;  
}

int flex_read()  //read flex sensor real values
{
        
      int flex_array[10] ={0,0,0,0,0,0,0,0,0,0} ;

      int flag1=0;

      int flex_total =0;
      int flex_ave =0;
      

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
            
            return flex_ave;
}

int left_assistant() // arrange flex sensor refereance
{
  int konum = soft_read(1);
  int ref = konum -3;
  ref = ref*5;

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

	myPID_soft_left.SetOutputLimits(20,50);
   //myPID_camera.SetOutputLimits(0,30);
   
   
         if(Serial.available()>0)
              {
                softpot_avg_Val_2 = soft_read(1); //discrete okuyan, pid input1
                Input1 = softpot_avg_Val_2;
				
                iB=Serial.read()- '0';
  
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
                  
				pwm_ext=15-Output2;
				  
				pwm1=pwm1;
				pwm2=pwm2+pwm_ext;
                                     
 
                int ref  = left_assistant(1);

                if(iB==3){
                    pwm1 = pwm1;
                    pwm2 = pwm2 +ref;
                  }
                  
                  if(iB==4){
                    pwm1 = pwm1;
                    pwm2 = pwm2*5/3+ref;
                  }
                  
                  if(iB==5){
                    pwm1 = pwm1;
                    pwm2 = pwm2*5/2+ref;
                  }
                  
                  if(iB==1){
                    pwm1 = pwm1;
                    pwm2 = pwm2/5*2+ref;
                  }
                  
                  if(iB==2){
                    pwm1 = pwm1;
                    pwm2 = pwm2*3/5+ref;
                  }
                      
                analogWrite(e1,pwm2);
                analogWrite(e2,pwm1);
   
              }

 
  
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
   
void starting_right(int time) // starting time pwm arrange 
{
	
	int flag = 0;	
	
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
	
	
	for(flag<10){
	 
		analogWrite(e1,30);
		analogWrite(e2,30);
        
	

		delay(time); // starting time
    
		flag++;	
	}
	
	

}
   
void right_role() //right role operation of the robot
{

    int flex_ave = 0;
    int softpot_real = 0;
	int softpot_dis = 0;
	
	
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
	
	
	starting_right(3000);
	
    
    while(1){
        
		int flag_stop = 0;
		int ref_turn =0; 
		int flex_ref = 0;
		int flex_difference =0;
		   
		   
		                 
        flex_ave = flex_read(); 
        softpot_real = soft_read_real(0);//sağ soft okunuyor 0 ile
		softpot_dis = soft_read_right();

        flex_ref = soft_to_flex_ref(softpot_ave)+5; //flex sensor reference value change with softpot 
        flex_difference = flex_ave - flex_ref;
             
		flex_difference = flex_difference/20;
		
		extra_pwm_1 = 0;
        if(softpot_dis == 3)
		{ 
               
			extra_pwm_1 = 0;
        }
        
		if(softpot_dis==5)
		{
       
           extra_pwm_1 = 1;        // hızlanma referansı
        
		}
			  
		if(softpot_dis==5){
            extra_pwm_1 = 0;
                 // buraya girerse dursun artÄ±k  
            pwm1 = 0;
            pwm2 = 0;
			
			analogWrite(e1,pwm1);
			analogWrite(e2,pwm2);
			flag_stop = 1; 
			
		}

		
		while(flag_stop){           // dengeye gelene kadar geri geri gidiyor
               
			softpot_ave = soft_read_right(role);

            if( softpot_ave<3){
                  flag_stop = 0;
				  starting_right(1000);
                  }                
            }

    
        if(flag_stop == 0){

			if(flex_difference>=0){

                pwm2 = 27; //içe dogru hareket
                pwm1 = 27 + 2*flex_difference*flex_difference;

				if(pwm1>50){
					pwm1 = 50;
                             
				}
			}
              
			else if(flex_difference<0){               
                pwm1 =27-4*flex_difference*flex_difference; //dışa dogru hareket
                pwm2 =27;
				
				if(pwm1<15){
					pwm1 =15;
				
				}
             
			}
                  
                  
            if(extra_pwm_1){
                    pwm1 = 1.2*pwm1;
                    pwm2 = 1.2*pwm2;
				}
              
		}   

                 
			if (softpot_ave == 0){
                     
				pwm1 = 0;
                pwm2 = 0;            
			}

              
			  analogWrite(e1,pwm1);
              analogWrite(e2,pwm2);
             
			 
			 
			role_select=role_checker();                        
            if (role_select==0)
                  break;
            

              //delay(1000);

    }
        		  
}

void loop() // main loop function
{
	int role_select;
	
	role_select=role_checker();
 
	if(role_select==1)  //right robot role
	{
        right_role();  
    }

	if(role_select==0) // left robot role
	{   
		left_role_2();
	}
}


















