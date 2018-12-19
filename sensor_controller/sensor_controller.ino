#include <Ultrasonic.h>
#include "Stepper.h"

#define trig_front    6 // Front sensor trigger
#define echo_front    7 // Front sensor echo
#define trig_rear     8 // Rear sensor trigger
#define echo_rear     9 // Rear sensor echo
#define turn_left     10 // Output signal telling vehicle to turn left
#define turn_right    11 // Output signal telling vehicle to turn right
#define reverse       12 // Output signal telling vehicle to start backing
#define stuck         13 // Output signal telling vehicle that it's stuck and has to stop
#define feedback_in   18 // Feedback from Micro:bit when it's done turning
#define feedback_out  19  // Feedback to Micro:bit

Ultrasonic sensor_front(trig_front, echo_front);  // Sensor facing forward
Ultrasonic sensor_rear(trig_rear, echo_rear);     // Sensor facing backward

unsigned int distance_front;  // Measured distance to obstacle in front of vehicle
unsigned int distance_rear;   // Measured distance to obstacle behind vehicle
unsigned int distance_left;   // Measured distance to obstacle to the left of vehicle
unsigned int distance_right;  // Measured distance to obstacle to the right of vehicle

// Inputs on stepper motor
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

const int stepsPerRev = 32;
Stepper stepper(stepsPerRev, IN1, IN3, IN2, IN4); // Init stepper motor

bool dir = false; // Direction: false = forward, true = reverse
bool halt = false; // Nothing happens if this is true. It resets when feedback signal goes low 
unsigned long time_last = millis(); // Used for periodically updating and checking distance_rear when reverse.

void setup()
{
  Serial.begin(9600);
  pinMode(turn_left, OUTPUT);
  digitalWrite(turn_left, LOW);
  
  pinMode(turn_right, OUTPUT);
  digitalWrite(turn_right, LOW);

  pinMode(reverse, OUTPUT);
  digitalWrite(reverse, LOW);

  pinMode(stuck, OUTPUT);
  digitalWrite(stuck, LOW);

  pinMode(feedback_out, OUTPUT);
  digitalWrite(feedback_out, HIGH);

  stepper.setSpeed(1100);

  // Attach interrupt on feedback_in to interrupt service routine isr
  pinMode(feedback_in, INPUT);  
  attachInterrupt(digitalPinToInterrupt(feedback_in), isr, FALLING);
}

// interrupt service routine setting halt to false
void isr()
{  
  digitalWrite(turn_left, LOW);
  digitalWrite(turn_right, LOW);
  halt = false;
}

void loop()
{
  // the loop does nothing if halt = true
  if (!halt)
  { 
    digitalWrite(feedback_out, LOW);
    // dir = false -> moving forward routine, dir = true -> reverse routine
    if (!dir)
    {
      distance_front = sensor_front.distanceRead(); // Read sensor data from sensor_front

      // Check if distance_front < 70 cm, if not, do nothing
      if (distance_front <= 70 && distance_front != 0)
      {
        digitalWrite(stuck, HIGH); // Set stuck signal high for Micro:bit to temporary stop
        distance_rear = sensor_rear.distanceRead(); // Read sensor data from sensor_rear
        stepper.step(512); // Turn stepper motor 90deg to be able to check distance on the sides              
        
        // Stepper motor rotated clockwise, so the front sensor is now, and rear sensor is left
        distance_right = sensor_front.distanceRead(); // Read right distance
        distance_left = sensor_rear.distanceRead();   // Read left distance

        // Obstacle on both sides -> check if it is possible to back up, else stuck forever.
        if (distance_right <= 70 && distance_right != 0 && distance_left <= 70 && distance_left != 0)
        {      
          if (distance_rear > 70 || distance_rear == 0)
          {
            digitalWrite(stuck, LOW); // Letting Micro:bit know we're no longer stuck
            digitalWrite(reverse, HIGH); // Tell Micro:bit to back up            
            dir = true; // Setting direction to reverse
          }
          else
          {
            stepper.step(-512);
          }          
        }
        // If one or both of the sides are clear, set the corresponding turn signal high,
        // let Micro:bit know we're no longer stuck, rotate stepper back to origin
        // and halt until feedback_in from Micro:bit goes low
        else  
        {
          digitalWrite(stuck, LOW);
          
          if (distance_right > distance_left)
          {
            digitalWrite(turn_right, HIGH);  
          }
          else
          {
            digitalWrite(turn_left, HIGH); 
          }  
                                  
          stepper.step(-512);
          digitalWrite(feedback_out, HIGH);
          halt = true;                    
        }
      } 
    }
    // Reverse routine
    else
    {
      // Stepper motor already rotated to 90deg meaning sensor_front is on the right side and sensor_rear is on left side
      // Measuring left and right distance
      distance_right = sensor_front.distanceRead();
      distance_left = sensor_rear.distanceRead();

      // Checking if either left or right is clear
      if (distance_right > 70 || distance_right == 0 || distance_left > 70 || distance_left == 0)
      {
        // Setting the turn direction
        if (distance_right > distance_left)
        {
          digitalWrite(turn_right, HIGH);  
        }
        else
        {
          digitalWrite(turn_left, HIGH); 
        }
                               
        stepper.step(-512);         // Turning the stepper motor back to origin
        digitalWrite(reverse, LOW); // Tell Micro:bit to no longer back up
        dir = false;                //direction = false -> forward
        digitalWrite(feedback_out, HIGH);
        halt = true;                // halt = true -> wait for feedback_in signal to go low     
      }
      // If time since last time rear was checked is more than 750ms
      else if (millis() - time_last >= 750)
      {
        stepper.step(-512); // Turn stepper motor back to origin
        distance_rear = sensor_rear.distanceRead(); // Measure rear distance
        
        if (distance_rear <= 70 && distance_rear != 0)
        {
          digitalWrite(stuck, HIGH);
          digitalWrite(reverse, LOW);
        }
        else
        {
          // Rear is still clear, keep backing up
          stepper.step(512); // Turn stepper motor so sensors are facing the sides          
        }

        time_last = millis(); // Update the variable keeping track of the last time rear was checked
      }
    }
  }    
}
