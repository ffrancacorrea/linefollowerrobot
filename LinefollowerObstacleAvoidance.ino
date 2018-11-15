#include "MeOrion.h"

const int DataPin = 2; //PORT_4
uint8_t Sensor_Data[3];
MeDCMotor motor2(M2); //gauche
MeDCMotor motor1(M1); //droit
MeDCMotor motor3(PORT_1);
MeUltrasonicSensor ultraSensor(PORT_7);
MePort port(PORT_3);
Servo myservo;
int16_t servopin =  port.pin1();
int var = 0 ;
int var2 = 0 ;
int linefollow = 1;
int count= 0;


void setup() 
{
    Serial.begin(9600);
    delay(100);
    Serial.println("Start.....");
    myservo.attach(servopin);
    motor3.stop();
}

void loop()
{
      
      Serial.println(getValue(),BIN);
        
    //SUIVRE LIGNE
    
    if (linefollow==1){
      
    
    switch (Sensor_Data[0]){ 
    case B111111:
      count = 0;
      Serial.println("Continue");
      motor1.run(-170);
      motor2.run(170); 
      myservo.write(180);
  
      if (ultraSensor.distanceCm() < 17 && myservo.read() == 180 && var == 0)
      {
        Serial.println("Obstacle à gauche");
        motor1.run(-20);
        motor2.run(150); 
        }
  
        else if (ultraSensor.distanceCm() > 28 && myservo.read() == 180 && var == 0)
      {
        Serial.println("Obstacle à droite");
        motor2.run(20);
        motor1.run(-150); 
        }
        else if (ultraSensor.distanceCm() <30 && myservo.read() == 180 && var == 1)
      {
        Serial.println("plan incliné");
        planIncline();
        }
        else if (var==1 && ultraSensor.distanceCm() > 100){
          motor1.run(-150);
          motor2.run(150);
          } 
        else if (var2==1 && ultraSensor.distanceCm() > 100){
          motor1.run(-100);
          motor2.run(150);
          } 

      
      
    break;
   
    case B011111:
      count = 0;
      Serial.println("Tout droite");
      motor1.stop();
      motor2.run(150);
    break;
   
    case B001111:
      count = 0;
      Serial.println("Droite");
      motor1.run(-20);
      motor2.run(150);
    break;

    case B000111:
      count = 0;
      Serial.println("Un peu droite");
      motor1.run(-50);
      motor2.run(170);
    break;

    case B100111:
      count = 0;
      Serial.println("Un peu droite");
      motor1.run(-100);
      motor2.run(170);
      myservo.write(90);
      if (myservo.read() == 90 && ultraSensor.distanceCm() < 20)
      {
        obstacleDevant();
        var = 1;
        }
    break;
    
    case B100011:
      count = 0;
      Serial.println("Un tout petit peu droite");
      motor1.run(-100);
      motor2.run(170);
      myservo.write(90);
      if (myservo.read() == 90 && ultraSensor.distanceCm() < 20)
      {
        obstacleDevant();
        }
    break;
   
    case B110011:
      count = 0;
      Serial.println("Continue");
      motor1.run(-170);
      motor2.run(170);
      myservo.write(90);  
  
      if (myservo.read() == 90 && ultraSensor.distanceCm() < 20)
      {
        obstacleDevant();
        }
    break;
    
    case B110001:
      count = 0;
      Serial.println("Un tout petit peu gauche");
      motor2.run(100);
      motor1.run(-170);
      myservo.write(90);
      if (myservo.read() == 90 && ultraSensor.distanceCm() < 20)
      {
        obstacleDevant();
        }
    break;

    case B111001:
      count = 0;
      Serial.println("Un peu gauche");
      motor2.run(100);
      motor1.run(-170);
      myservo.write(90);
      if (myservo.read() == 90 && ultraSensor.distanceCm() < 20)
      {
        obstacleDevant();
        }
    break;
    
    case B111000:
      count = 0;
      Serial.println("Un peu gauche");
      motor3.stop();
      motor2.run(50);
      motor1.run(-170);
    break;

    case B111100:
      count = 0;
      Serial.println("Gauche");
      motor3.stop();
      motor2.run(20);
      motor1.run(-150);
    break;

    case B111110:
      count = 0;
      Serial.println("Gauche toute");
      motor2.stop();
      motor1.run(-150);
    break;

    case B000000:
      Serial.println("S'arrête");
      motor1.stop();
      motor2.stop();
      if (count == 100){
        lancement();
      }
      else{
        count++;
        }
      break;
      }   
    }
}
 void  obstacleDevant()
   {
      
      Serial.println("Obstacle devant");
      
      motor1.run(50);
      motor2.run(-50);
      delay(2500);
      motor1.run(-50);
      motor2.run(150);
      delay(3000);
      motor1.run(-100);
      motor2.run(100);
      delay(500);
      motor1.stop();
      motor2.stop();
      motor1.run(-150);
      //motor2.run(50);
      delay(1800);
      motor1.stop();
      motor2.stop();
      motor1.run(-170);
      motor2.run(170);
      delay(1500);
      motor1.stop();
      motor2.stop();
      motor1.run(-150);
      motor2.run(50);
      delay(1700); //45 dg
      motor1.stop();
      motor2.stop();
      motor1.run(-100);
      motor2.run(100);
      delay(300);
      var = 1;
      }

void planIncline()
{     
        linefollow = 0;
        motor1.stop();
        motor2.run(150);
        delay(1000);
        motor1.run(-100);
        motor2.run(100);
        delay(1500);
        motor1.run(-150);
        motor2.run(10);
        //motor2.run(100);
        delay(1000);
        motor1.run(-150);
        motor2.run(150);
        delay(1000);
        motor1.run(-150);
        motor2.run(50);
        delay(1000);
        motor1.run(-150);
        motor2.run(150);
        linefollow = 1;
        delay(500);
        var2 = 1;
        
           
  
}

void lancement(){
    motor3.run(-250);
    delay(200);
    motor3.stop();
  }
uint8_t getValue()
{  
    long time_out_flag = 0;
    pinMode(DataPin, OUTPUT);
    digitalWrite(DataPin, LOW);
    delayMicroseconds(980);
    digitalWrite(DataPin, HIGH);
    delayMicroseconds(40);
    pinMode(DataPin, INPUT_PULLUP);
    delayMicroseconds(50); 
    time_out_flag = millis();
    while((digitalRead(DataPin) == 0)&&((millis() - time_out_flag) < 6)); 
    time_out_flag = millis();
    while((digitalRead(DataPin) == 1)&&((millis() - time_out_flag) < 6));
    for(uint8_t k=0; k<3; k++)
    {
        Sensor_Data[k] = 0x00;
        for(uint8_t i=0;i<8;i++)
        {
            time_out_flag = millis(); 
            while(digitalRead(DataPin) == 0&&((millis() - time_out_flag) < 6));
            uint32_t HIGH_level_read_time = micros();
            time_out_flag = millis(); 
            while(digitalRead(DataPin) == 1&&((millis() - time_out_flag) < 6));
            HIGH_level_read_time = micros() - HIGH_level_read_time;
           if(HIGH_level_read_time > 50 && HIGH_level_read_time < 100)  
            {
                Sensor_Data[k] |= (0x80 >> i);
            }
        }
    }

    
    if (Sensor_Data[1] == (uint8_t)(~(uint8_t)Sensor_Data[0]))
    {
       return Sensor_Data[0];
    }


}

