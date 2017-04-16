int in1=7;
int in2=6;
int in3=5;
int in4=4;
int e1=8;
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
  pinMode(role_select,INPUT);
  int flag;
 
  
}

int position_control(int s,int f)
{
	
}
void loop()
{
	if(role_select==1)  //right robot role
	{
				while(1)	
				{
					int flexVal = analogRead(A1);//flex sensor value
			        int softpotVal = analogRead(A2);// softpot sensor value
			        Serial.println("flexsensor");
			        Serial.println(flexVal);
			        Serial.println("softpot");
			        Serial.println(softpotVal);
			        int pwm1,pwm2;
			        

			       
			        int softPotPosition=map(softpotVal,0,1023,0,100);
			        
			        int flexposition=map(flexVal,300,600,0,100);

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




			        analogWrite(e1,pwm1);
			        analogWrite(e2,pwm2);
			                    
			        digitalWrite(in1,LOW);
			        digitalWrite(in2,HIGH);
			        digitalWrite(in3,HIGH);
			        digitalWrite(in4,LOW);
			        delay(1000);
				}
	}
	

	if(role_select==0)
	{			while(1)
				{	//right
					int softpotVal=analogRead(A0);
					
					int softPotPosition=map(softpotVal,0,1023,0,100);

					if(softPotPosition==0)
					{
						pwm1=0;
						pwm2=0;
					}



				
					analogWrite(e1,pwm1);
			        analogWrite(e2,pwm2);
			                    
			        digitalWrite(in1,LOW);
			        digitalWrite(in2,HIGH);
			        digitalWrite(in3,HIGH);
			        digitalWrite(in4,LOW);
			        delay(1000);

				}
	}
}