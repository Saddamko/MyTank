#include <SoftwareSerial.h>
#include <Servo.h> 
int state = 0;

int IN1 = 4; // Input1 подключен к выводу 5 
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int EN1 = 3;
int EN2 = 9;
int ENBT = 2;
int i;

int LE=8, RE=12, SERVO=13;

SoftwareSerial mySerial(10, 11); // RX, TX
Servo myservo;  // create servo object to control a servo 
void blink ()
{int i;
  for (i=0; i<10; i++)
  {
  digitalWrite(LE, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);              // wait for a second
  digitalWrite(LE, LOW);    // turn the LED off by making the voltage LOW
  delay(50);              // wait for a second
  
  digitalWrite(RE, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);              // wait for a second
  digitalWrite(RE, LOW);    // turn the LED off by making the voltage LOW
  delay(50);              // wait for a second
  }
}

void move_head ( )
      {
      myservo.write(0);                  // sets the servo position according to the scaled value 
      delay(1000    );                    // waits for the servo to get there 
      myservo.write(45); 
      delay(1000    );  
      }

void setup() {
      Serial.begin(9600);           // set up Serial library at 9600 bps
      Serial.println("Welcome: Forward = 1 Left = 2 Right = 3 Backwards = 4 Stop = 0");
      mySerial.begin(9600);
      mySerial.println("Hello, world?");
      
      pinMode(LE, OUTPUT);
      pinMode(RE, OUTPUT);
      pinMode(SERVO, OUTPUT);
      myservo.attach(SERVO); // attaches the servo on pin 9 to the servo object 
      
      pinMode (EN1, OUTPUT);
      pinMode (IN1, OUTPUT);
      pinMode (IN2, OUTPUT);
      pinMode (EN2, OUTPUT);
      pinMode (IN4, OUTPUT);
      pinMode (IN3, OUTPUT);
      pinMode (ENBT, OUTPUT);
      digitalWrite (ENBT, HIGH);
      state=0;
      
      myservo.write(0);                  // sets the servo position according to the scaled value 
      delay(1000    );                    // waits for the servo to get there 
      myservo.write(45); 
      delay(1000    );  
      blink();
}

void do_move (int mode, int time)
{ 
  switch (mode)
  {
    case 0:
      //do something when stop
      digitalWrite (IN1, LOW);
      digitalWrite (IN2, LOW); 
      digitalWrite (IN3, LOW);
      digitalWrite (IN4, LOW); 
      break;
    case 1:
      //do something when var equals 1 (Forvard)
      digitalWrite (IN1, HIGH);
      digitalWrite (IN2, LOW); 
      digitalWrite (IN3, HIGH);
      digitalWrite (IN4, LOW);       
      break;
    case 2:
      //do something when var equals 2 (Turn Left)
      digitalWrite (IN1, LOW);
      digitalWrite (IN2, LOW); 
      digitalWrite (IN3, HIGH);
      digitalWrite (IN4, LOW);            
      break;
    case 3:
      //do something when var equals 3 (Turn Right)
      digitalWrite (IN1, HIGH);
      digitalWrite (IN2, LOW); 
      digitalWrite (IN3, LOW);
      digitalWrite (IN4, LOW);   
      break;
    case 4:
      //do something when var equals 4 (Backwards)
      digitalWrite (IN1, LOW);
      digitalWrite (IN2, HIGH); 
      digitalWrite (IN3, LOW);
      digitalWrite (IN4, HIGH);         
      break; 
     case 5:
      //do something when var equals 5 (Forward Right)
      digitalWrite (IN1, LOW);
      digitalWrite (IN2, HIGH); 
      digitalWrite (IN3, HIGH);
      digitalWrite (IN4, LOW);    
      break; 
     case 6:
      //do something when var equals 6 (Forward Left)
      digitalWrite (IN1, HIGH);
      digitalWrite (IN2, LOW); 
      digitalWrite (IN3, LOW);
      digitalWrite (IN4, HIGH);    
      break;       
      case 7:
      //do something when var equals 6 (Forward Left)
      blink();
      break;    
      case 8:
      //do something when var equals 6 (Forward Left)
      move_head();
      break;   
    default: 
      // if nothing else matches, do the default
      // default is optional
      digitalWrite (IN1, LOW);
      digitalWrite (IN2, LOW); 
      digitalWrite (IN3, LOW);
      digitalWrite (IN4, LOW); 
    break;
  }
    

  for (i = 50; i <= 200; ++i)
  {
      analogWrite(EN1, i);
      analogWrite(EN2, i);
      delay(5);
  }
    delay(time);
  analogWrite (EN1, 0);
  analogWrite (EN2, 0);

}

void loop(){   //if some data is sent, read it and save it in the state variable
int time;

if(mySerial.available() > 0)
  {
      state = mySerial.read();
      //if (state = 255) { mySerial.end();Serial.begin(9600);Serial.print("Is Restarted ");};
      Serial.print("I received: ");
      Serial.println(state);
      
      delay(50);
if (state == '0') 
    {
      do_move (0,0);
      
      Serial.println("Stopped");
      delay(100);
      state = 0; 
    }
else if (state == '1')      // If 1 Forwards
    {
      do_move (1,2000);
      
      Serial.println("Forward");
      delay(100);
      state = 0; 
    }
else if (state == '2')      // If 2 Turn Left
    { 
      do_move (2,500);

      Serial.println("Left");
      delay(100);
      state = 0;     
    }
else if (state == '3') {    // If 3 Turn Right
      do_move (3,500); 
      
      Serial.println("Right");
      delay(100);
      state = 0;  
    }
else if (state == '4')       // If 4 Backwards
    {
      do_move (4,2000);

      Serial.println("Backward");
      delay(100);
      state = 0;   
    }
else if (state == '5') 
    {
      do_move (5,200); 

      Serial.println("Forward Right");
      delay(100);
      state = 0;   
     }
else if (state == '6') 
    {
      do_move (6,200);       

      Serial.println("Forward Left");
      delay(100);
      state = 0;   
     }
else if (state == '7')       // 
    {
      do_move (7,200);
      Serial.println("Backward Right");
      delay(100);
      state = 0;   
    }
else if (state == '8')       // 
    {
      do_move (8,0);
      Serial.println("Backward Left");
      delay(100);
      state = 0;   
    }
else if (state >= '9')
    {
      do_move (9,0);
      Serial.println("Invalid");
      delay(100);
      state = 0; 
    }
    if(mySerial.available()){

	    while(mySerial.available()) mySerial.read();//purge buffer
	  }//if(Serial1)

  }
}


