#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <webots/light_sensor.h>
#include <webots/gps.h>
#include <stdio.h>
#include <webots/speaker.h>


#define TIME_STEP 64
#define MAX_SPEED 6.28
#define WAIT_DURATION 10.0 // Wait time in seconds


//Prototypes
void set_speed(double left_speed, double right_speed);
void follow_wall();
void record_light_intensity();
void record_gps();
int count_deadends();
bool cycle_one();


WbDeviceTag left_motor, right_motor; // Initialize motors
WbDeviceTag ps[8]; // Initialize proximity sensors
WbDeviceTag ls[8]; // Initialize light sensors
WbDeviceTag gps; //Initialize GPS
WbDeviceTag speaker; //initialize speaker


double highest_light_intensity = -1.0;
double threshold_light_intensity = -1.0;
double start_time;
double average_light_intensity = -1.0;
float brightest_gpsx = 0, brightest_gpsy = 0, start_gpsx = 0, start_gpsy = 0;
bool waitfwlw=false;
bool firstcycletrue = false;
double firstFWLW_time = 10000;
int deadend_count = 0;

void set_speed(double left_speed, double right_speed) {
  wb_motor_set_velocity(left_motor, left_speed);
  wb_motor_set_velocity(right_motor, right_speed);
}

void follow_wall() {
  double ps_values[8];
  for (int i = 0; i < 8; i++) {
    ps_values[i] = wb_distance_sensor_get_value(ps[i]);
  }

  bool front_wall = ps_values[0] > 90.0 || ps_values[7] > 90.0;
  bool left_wall = ps_values[5] > 100.0;

  if (front_wall) {
    set_speed(2.0, -1.0);  // Turn right
  } else if (left_wall) {
    set_speed(3.0, 3.0);   // Move forward
  } else {
    set_speed(-1.0, 2.0);  // Turn left
  }
}


void record_light_intensity() {
  double total_light_intensity = 0.0;
  for (int i = 0; i < 8; i++) {
    total_light_intensity += wb_light_sensor_get_value(ls[i]);
  }
  average_light_intensity = total_light_intensity / 8.0;

  if (average_light_intensity > highest_light_intensity) {
    highest_light_intensity = average_light_intensity;
    record_gps();
  }
}

bool cycle_one(){
  const double *current_gps_values = wb_gps_get_values(gps);
  float buffer = 0.1;
  
  if (wb_robot_get_time() - start_time < 60){ return false;}

  if (current_gps_values[0] < (start_gpsx+buffer) && current_gps_values[0] > (start_gpsx-buffer) && current_gps_values[1] < (start_gpsy+buffer) && current_gps_values[1] > (start_gpsy-buffer) ) {
      printf("Initial Position Reached\n");
      return true;
    }
  else{return false;}
}

void record_gps(){
  const double *brightest_gps_values = wb_gps_get_values(gps);
  brightest_gpsx = brightest_gps_values[0];
  brightest_gpsy = brightest_gps_values[1];
}

void wait(double seconds) {
  double start = wb_robot_get_time();
  while (wb_robot_get_time() - start < seconds) {
    wb_robot_step(TIME_STEP);
  }
}

int count_deadends(){

  if (firstcycletrue){
     return deadend_count;
  }
  double ps_values[8];
  for (int i = 0; i < 8; i++) {
    ps_values[i] = wb_distance_sensor_get_value(ps[i]);
    //printf("%d: %f\n",i,ps_values[i]);
  }

  bool front_wall = ps_values[7] > 93; // || ps_values[7] > 93;
  bool left_wall = ps_values[5] > 100;
  

  if (front_wall==true && left_wall==true && waitfwlw == false){
    firstFWLW_time = wb_robot_get_time();
    
   // printf("First FWLW detected\n");
    waitfwlw = true;
    }
   
   float wait_time = wb_robot_get_time()-firstFWLW_time;
   //printf("wait time : %f \n",wait_time);
  if (front_wall && left_wall && waitfwlw == true && wait_time>4.7 && wait_time<6 ){
    
     deadend_count++;
     //printf("Deadend %d Detected\n",deadend_count);
     waitfwlw = false;
     }
    if(wait_time>6){
   // printf("wait reset\n");
    waitfwlw = false;
  
        }
        return deadend_count;}

int main() {
  wb_robot_init();
  speaker = wb_robot_get_device("speaker");
  gps= wb_robot_get_device("gps");
  wb_gps_enable(gps,TIME_STEP);
 

  // Get motors
  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_velocity(left_motor, 0.0);
  wb_motor_set_velocity(right_motor, 0.0);

  // Get and enable proximity sensors
  char ps_names[8][4] = {"ps0", "ps1", "ps2", "ps3", "ps4", "ps5", "ps6", "ps7"};
  for (int i = 0; i < 8; i++) {
    ps[i] = wb_robot_get_device(ps_names[i]);
    wb_distance_sensor_enable(ps[i], TIME_STEP);
  }

  // Get and enable light sensors
  char ls_names[8][4] = {"ls0", "ls1", "ls2", "ls3", "ls4", "ls5", "ls6", "ls7"};
  for (int i = 0; i < 8; i++) {
    ls[i] = wb_robot_get_device(ls_names[i]);
    wb_light_sensor_enable(ls[i], TIME_STEP);
  }
  
  wait(1);

  start_time = wb_robot_get_time();
  const double *start_gps_values = wb_gps_get_values(gps);
  start_gpsx = start_gps_values[0];
  start_gpsy = start_gps_values[1];
  printf("Starting at X: %f  Y: %f\n", start_gpsx,start_gpsy);


  while (wb_robot_step(TIME_STEP) != -1) {
    follow_wall();
    record_light_intensity();
    count_deadends();
    firstcycletrue = cycle_one();

    double current_time = wb_robot_get_time();

    if (firstcycletrue) {
      printf("Pausing after reaching start position\n");
      set_speed(0, 0);  // Stop the robot
      wait(WAIT_DURATION);  // Wait for a few seconds
      printf("Resuming\n");

      // Restart the robot and continue moving
      while (wb_robot_step(TIME_STEP) != -1) {
       follow_wall();
       record_light_intensity();
       const double *current_gps_values = wb_gps_get_values(gps);
       float buffer = 0.1;

        if (current_gps_values[0] < (brightest_gpsx+buffer) && current_gps_values[0] > (brightest_gpsx-buffer) && current_gps_values[1] < (brightest_gpsy+buffer) && current_gps_values[1] > (brightest_gpsy-buffer) ) {
          printf("Stopping at X: %f  Y: %f\n", current_gps_values[0],current_gps_values[1]);
          set_speed(0, 0);  // Stop the robot
          wb_speaker_speak(speaker, "Brightest Recorded Spot Reached", 1);
          break;
        }

        printf("Current Coordinates X: %f  Y: %f\n", current_gps_values[0],current_gps_values[1]);
        printf("looking within range X: %f - %f | Y: %f - %f\n ",(brightest_gpsx-buffer),(brightest_gpsx+buffer),(brightest_gpsy-buffer),(brightest_gpsy+buffer));
      }
      break;
    }

    printf("Highest light intensity so far: %f\n", highest_light_intensity);
    printf("at X: %f  Y: %f\n ",brightest_gpsx,brightest_gpsy);
  }

  wb_robot_cleanup();  // Cleanup Webots resources
  return 0;  // Exit the program
}
