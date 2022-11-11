#include <AFMotor.h> 
//attaching motors
AF_DCMotor motor_left(2); 
AF_DCMotor motor_right(4); 
//variables
int sensor1 = 0;
int sensor2 = 0;
int sensor3 = 0;
int sensor4 = 0;
int sensor5 = 0;

int adj_1 = 0;
int adj_2 = 0;
int adj_3 = 0;
int adj_4 = 0;
int adj_5 = 0;
//tunes sensitivity
int s1_min = 185;
int s1_max = 950;
int s2_min = 185;
int s2_max = 950;
int s3_min = 200;
int s3_max = 900;
int s4_min = 190;
int s4_max = 900;
int s5_min = 180;
int s5_max = 895;
//sensor thresholds
int lower_threshold = 17;
int threshold = 128;
int upper_threshold = 230;
//bot speed
int speed_value = 220;

void setup()
{
Serial.begin(9600); 
motor_left.setSpeed(200);
motor_left.run(RELEASE);

motor_right.setSpeed(200);
motor_right.run(RELEASE);
}
//reading the line
void update_sensors(){

sensor1 = analogRead(0);
adj_1 = map(sensor1, s1_min, s1_max, 0, 255);
adj_1 = constrain(adj_1, 0, 255);

sensor2 = analogRead(1); 
adj_2 = map(sensor2, s2_min, s2_max, 0, 255);
adj_2 = constrain(adj_2, 0, 255);

sensor3 = analogRead(2); 
adj_3 = map(sensor3, s3_min, s3_max, 0, 255);
adj_3 = constrain(adj_3, 0, 255);

sensor4 = analogRead(3); 
adj_4 = map(sensor4, s4_min, s4_max, 0, 255);
adj_4 = constrain(adj_4, 0, 255);

sensor5 = analogRead(4); 
adj_5 = map(sensor5, s5_min, s5_max, 0, 255);
adj_5 = constrain(adj_5, 0, 255);

}
void loop(){
update_sensors(); 
//centered
if (adj_3 < lower_threshold){
//forward
if (adj_2 > threshold && adj_4 > threshold){

motor_left.run(FORWARD);
motor_left.setSpeed(speed_value);
motor_right.run(FORWARD);
motor_right.setSpeed(speed_value);
}
//black box stop robot
else if (adj_1 < 1){
if (adj_2 < 1){
if (adj_3 < 1){
if (adj_4 < 1){
if (adj_5 < 1){

motor_left.run(RELEASE);
motor_right.run(RELEASE);
}
}
}
}
}
}
//not centered
else {
//turn left
if (adj_1 < upper_threshold && adj_5 > upper_threshold){
motor_left.run(RELEASE);
motor_left.setSpeed(0);
motor_right.run(FORWARD);
motor_right.setSpeed(speed_value);
}
//turn right
else if (adj_1 > upper_threshold && adj_5 < upper_threshold){
motor_left.run(FORWARD);
motor_left.setSpeed(speed_value);
motor_right.run(RELEASE);
motor_right.setSpeed(0);
}
//turn left
else if (adj_2 < upper_threshold && adj_4 > upper_threshold){
motor_left.run(RELEASE);
motor_left.setSpeed(0);
motor_right.run(FORWARD);
motor_right.setSpeed(speed_value);
}
//turn right
else if (adj_2 > upper_threshold && adj_4 < upper_threshold){
motor_left.run(FORWARD);
motor_left.setSpeed(speed_value);
motor_right.run(RELEASE);
motor_right.setSpeed(0);
}
}

}
