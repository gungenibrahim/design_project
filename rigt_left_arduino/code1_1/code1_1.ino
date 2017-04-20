int in1=7;
int in2=6;
int in3=5;
int in4=4;
int e1=10;
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
 }



int pwm1,pwm2;
int role;
int extra_pwm_1=0;

            

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
            
             if(role = 0){
              softpotVal = analogRead(A2);// softpot sensor value for right robot
             }
             else if(role = 1){
              softpotVal = analogRead(A0);// softpot sensor value for left robot	<<<<<< pini gir

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

}


void right_role(int role_select){

		int flex_ave = 0;
		int softpot_ave = 0;
		
		    digitalWrite(in1,LOW);
        digitalWrite(in2,HIGH);
        digitalWrite(in3,HIGH);
        digitalWrite(in4,LOW);

        ///////////////////////////////////////////////////
        analogWrite(e1,30);
        analogWrite(e2,30);
          

        delay(3000); // starting time
         ////////////////////////////////////////////////// 

    
          while(1){
           
			      role =0;
                 
          	flex_ave = flex_read(); 
          	softpot_ave = soft_read(role);

             int flex_ref = 420; //flex sensor reference value

             int flex_difference = flex_ave-flex_ref;
              flex_difference = flex_difference/20;
               
               /* Serial.println("flex_difference");
                Serial.println(flex_difference);
				*/

              //arranging turning refereance

              int flag_stop = 0;
              int ref_turn =0;
              ////////////////////////////////////////////////////////////////////////////////


            /* Serial.println("softpot_ave");
             Serial.println(softpot_ave);
             */
              extra_pwm_1 = 0;
              if(700>softpot_ave>480){ 
                extra_pwm_1 = 0;
              }
              if(softpot_ave<480){
                flex_ref = 430;
                extra_pwm_1 = 1;        // hızlanma referansı
              }
              if(700<softpot_ave){
                extra_pwm_1 = 0;
                 // buraya girerse dursun artÄ±k 

             

                  pwm1 = -1* pwm1;
                  pwm2 = -1* pwm2;
    
              
              Serial.println("pwm1");
              Serial.println(pwm1);
              Serial.println("pwm2");
              Serial.println(pwm2);
                
              analogWrite(e1,pwm1);
              analogWrite(e2,pwm2);
              
               
                while(700<softpot_ave){
                  
                	softpot_ave = soft_read(role);

                  if(700>softpot_ave>480){
                     pwm1 = 0;
                     pwm2 = 0;

                     
                 analogWrite(e1,pwm1);
                 analogWrite(e2,pwm2);
                 
                
                  }

                  delay(1000);

                }

               
                flag_stop = 1; 
                
             }

               ///////////////////////////////////////////////////////////////////////////////////////

               if (softpot_ave = 0){
                     pwm1 = 0;
                     pwm2 = 0;

                
                }
              
              ////////////////////////////////////////////////////////////////////////////////////////
              while(flag_stop){           // dengeye gelene kadar geri geri gidiyor
               softpot_ave = soft_read(role);

                 Serial.println("pwm1");
                   Serial.println(pwm1);
             
                 Serial.println("pwm2");
                 Serial.println(pwm2);
                if( softpot_ave<480){
                  
                 
                  
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

              if(flex_difference>=0){

                  pwm2 = 30 + flex_difference*flex_difference*flex_difference; //dÄ±sa dogru hareket
                  pwm1 = 30;

              
              
              }
              else if(flex_difference<0){               
                  pwm1 =30+ flex_difference*flex_difference*flex_difference/(-1); //ice dogru hareket
                  pwm2 =30;
                  
                
                }

                 if(extra_pwm_1){
                    pwm1 = 1.2*pwm1;
                    pwm2 = 1.2*pwm2;
                  }
              }   





             
			        Serial.println("pwm1");
             Serial.println(pwm1);
             
             Serial.println("pwm2");
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
                          
            if (role_select==0){
              break;
            }

              delay(1000);



              }
          }




              
int position_control(int s,int f)
{
  
}



void loop()
{
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
//  }





  

if(role_select==0)
  {     
      int iB=0;
     
      int softpotVal_2;

       digitalWrite(in1,LOW);
       digitalWrite(in2,HIGH);
       digitalWrite(in3,HIGH);
       digitalWrite(in4,LOW);

      while(1){ 
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
        
        Serial.println("pwm11111");
        Serial.println(pwm1);
             
        Serial.println("pwm22222");
        Serial.println(pwm2);


      }
      if (role_select==1){
              break;
            }
      }
  }
}


