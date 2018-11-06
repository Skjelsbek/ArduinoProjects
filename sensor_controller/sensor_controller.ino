#include <Ultrasonic.h>
#include "Stepper.h"

#define trig_front  6 // Front sensor trigger
#define echo_front  7 // Front sensor echo
#define trig_rear   8 // Rear sensor trigger
#define echo_rear   9 // Rear sensor echo
#define turn_left   10 // Output signal telling vehicle to turn left
#define turn_right  11 // Output signal telling vehicle to turn right
#define reverse     12 // Output signal telling vehicle to start backing
#define stuck       13 // Output signal telling vehicle that it's stuck and has to stop
#define feedback    18 // Feedback from Micro:bit when it's done turning

Ultrasonic sensor_front(trig_front, echo_front);  // Sensor facing forward
Ultrasonic sensor_rear(trig_rear, echo_rear);     // Sensor facing backward

unsigned int distance_front;  // Measured distance to obstacle in front of vehicle
unsigned int distance_rear;   // Measured distance to obstacle behind vehicle
unsigned int distance_left;
unsigned int distance_right;

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
  pinMode(turn_left, OUTPUT);
  digitalWrite(turn_left, LOW);
  
  pinMode(turn_right, OUTPUT);
  digitalWrite(turn_right, LOW);

  pinMode(reverse, OUTPUT);
  digitalWrite(reverse, LOW);

  pinMode(stuck, OUTPUT);
  digitalWrite(stuck, LOW);

  stepper.setSpeed(1100);

  // Attach interrupt on feedback to interrupt service routine isr
  pinMode(feedback, INPUT);  
  attachInterrupt(digitalPinToInterrupt(feedback), isr, FALLING);
}

// interrupt service routine setting halt to false
void isr()
{
  halt = false;
}

void loop()
{
  // the loop does nothing if halt = true
  if (!halt)
  { 
    // dir = false -> moving forward routine, dir = true -> reverse routine
    if (!dir)
    {
      distance_front = sensor_front.distanceRead(); // Read sensor data from sensor_front

      // Check if distance_front < 50 cm, if not, do nothing
      if (distance_front <= 50)
      {
        digitalWrite(stuck, HIGH); // Set stuck signal high for Micro:bit to temporary stop
        distance_rear = sensor_rear.distanceRead(); // Read sensor data from sensor_rear
        stepper.step(512); // Turn stepper motor 90deg to be able to check distance on the sides

        // Stepper motor rotated clockwise, so the front sensor is now, and rear sensor is left
        distance_right = sensor_front.distanceRead(); // Read right distance
        distance_left = sensor_rear.distanceRead();   // Read left distance

        // Obstacle on both sides -> check if it is possible to back up, else stuck forever.
        if (distance_right <= 50 && distance_left <= 50)
        {      
          if (distance_rear > 50)
          {
            digitalWrite(reverse, HIGH); // Tell Micro:bit to back up
            digitalWrite(stuck, LOW); // Letting Micro:bit know we're no longer stuck
            dir = true; // Setting direction to reverse
          }    
        }
        // If one or both of the sides are clear, set the corresponding turn signal high,
        // let Micro:bit know we're no longer stuck, rotate stepper back to origin
        // and halt until feedback from Micro:bit goes low
        else  
        {
          if (distance_right > distance_left)
          {
            digitalWrite(turn_right, HIGH);  
          }
          else
          {
            digitalWrite(turn_left, HIGH); 
          }      
          
          digitalWrite(stuck, LOW);
          stepper.step(-512);
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
      if (distance_right > 50 || distance_left > 50)
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
                       
        stepper.step(-512); // Turning the stepper motor back to origin
        halt = true;        // halt = true -> wait for feedback signal to go low
        dir = false;        //direction = false -> forward
      }
      // If time since last time rear was checked is more than 2 sec
      else if (millis() - time_last >= 2000)
      {
        stepper.step(-512); // Turn stepper motor back to origin
        distance_rear = sensor_rear.distanceRead(); // Measure rear distance
        
        if (distance_rear <= 50)
        {
          // If you end up here you're fucked!
          digitalWrite(stuck, HIGH);
        }
        else
        {
          // Rear is still clear, keep backing up
          stepper.step(512); // Turn stepper motor so sensors are facing the sides
          time_last = millis(); // Update the variable keeping track of the last time rear was checked
        }
      }
    }
  }    
}
