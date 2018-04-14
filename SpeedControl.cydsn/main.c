/* ================================================================================
 *
 * Chege Gitau & Eric Ham
 * ELE 302: Navigation Control
 *
 * ================================================================================
 */

#include "project.h"
#include <stdio.h>
#include "math.h"

/* Parameters for speed control */
double k_p = 5;  /* Gives us a fast rise time */
double k_i = 7;  /* Allows us to correct the steady state error */
double k_d = 0;  /* Dampens the system and reduces overshoot */

/* Parameters for navigation control */
double kp_nav_control = .08;
double ki_nav_control = 0;
double kd_nav_control = 0.06;

double timer_max = 65535.0f;

double wheel_diam_feet = 2.5f / 12.0f; /* Diameter of the wheel in feet */
double clock_frequency = 10000.0f; /* Frequency of the clock in Hz */
double desired_speed = 4.0f;   /* Reference speed 4ft/sec */
int magnet_flag = 0;    /* Keeps track of magnet passes */

int time_line_raw_read = 0; //time when reach comparator value within line
double time_line = 0.0; //time when comparator sees black part of line
double max_comparator_timer = 65536;
double time_per_line = (double) 60e-6; //time it takes to traverse 1 line of video input
double distance_to_line = 0.0;
int num_pixels_per_line = 320;
int nav_flag = 0;
int line_1 = 50; /* The line at which we'll check the black line */

int count_up_to_ith_line_flag = 0; 
char str_buffer2[16];
/* A counter for the line number */
int current_line_number = 0;

double desired_steering_value = 740;


/* Set the flag that communicates that we've just seen a magnet */
CY_ISR(magnet_inter) {
    magnet_flag = 1;
    Timer_ReadStatusRegister();
}

/* Invoked when we see black in our preferred line in every frame */
CY_ISR(comparator_inter) {
    time_line_raw_read = Timer_1_ReadCapture();
    nav_flag = 1;
}

int main(void) {
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    double input_speed = 0.0f;
    double output_speed = 0.0f;
    double magnet_separation_distance = (22.0f / 7.0f) * wheel_diam_feet / 5.0f;
    double previous_time = timer_max;
    double current_time = timer_max / 2.0f;
    double time_delta = timer_max / 2.0f;
    char str_buffer[16];
    int magnet_view_counter = 0;
    double time_diff;
    
    double error = input_speed - desired_speed;
    double err_sum = 0;
    double nav_error = 0;
    double prev_nav_error = 0;
    double output_direction = 0;
    

    /* Initialization Code */
    PWM_Start();
    Timer_Start();
    Magnet_Interrupt_Start();
    LCD_Start();
    
    /* Added in Navigation Control */
    Composite_Sync_Counter_Start();
    
    Comparator_Interrupt_Start();
    Composite_Sync_Interrupt_Start();
    
    Timer_1_Start();
    
    /* Our Hall Sensor broke, so we wrote a constant speed to the motor */
    PWM_Steering_Start();
    PWM_WriteCompare(35);
    
    // Magnet_Interrupt_SetVectore(magnet_inter);
    Composite_Sync_Interrupt_SetVector(composite_sync_inter);
    Comparator_Interrupt_SetVector(comparator_inter);
    
    for(;;) {
        
        /* Navigation Control */
        if (nav_flag == 1) {
            
            time_line = max_comparator_timer - time_line_raw_read;
            
            if (time_line != 0.0) {
                
                /* Estimate the current error */
                nav_error = time_line - desired_steering_value;
                if (fabs(prev_nav_error - nav_error) > 600) {
                    nav_error = prev_nav_error;
                }
                
                /* Store this error so that we can implement derivative control */
                prev_nav_error = nav_error;
                
                /* Calculate the output signal */
                output_direction = 152 + kp_nav_control * nav_error + kd_nav_control*(nav_error - prev_nav_error);
                
                /* Communicate the current error to the user for debugging */
                sprintf(str_buffer, "%f", nav_error);
                LCD_ClearDisplay();
                LCD_Position(0, 0);
                LCD_PrintString(str_buffer);
                
                /* Trim the output. 100 goes all the way to the left, 200 goes all the way to the right */
                if (output_direction < 100) {
                    output_direction = 100;
                } else if (output_direction > 200) { 
                    output_direction = 200;
                }
                
                /* Actuation */
                PWM_Steering_WriteCompare(output_direction);             
            }      
            nav_flag = 0;       
        }
    }
}

/* [] END OF FILE */
