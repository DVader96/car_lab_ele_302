/* ================================================================================
 *
 * Chege Gitau & Eric Ham
 * ELE 302
 * Speed Control
 *
 * ================================================================================
 */

#include "project.h"
#include <stdio.h>
#include <time.h>

/* General Strategy:
 * Update k_p till we get to the target speed 
 * Tune k_i till we get few errors
 * We'll not be using k_d in this control loop
 */

double k_p = 5;  /* Gives us a fast rise time */
double k_i = 7;  /* Allows us to correct the steady state error */
double k_d = 0;  /* Dampens the system and reduces overshoot */

double timer_max = 65535.0f;

double wheel_diam_feet = 2.5f / 12.0f; /* Diameter of the wheel in feet */
double clock_frequency = 10000.0f; /* Frequency of the clock in Hz */
double desired_speed = 4.0f;   /* Reference speed 4ft/sec */
int magnet_flag = 0;    /* Keeps track of magnet passes */

CY_ISR(magnet_inter) {
    magnet_flag = 1;
    Timer_ReadStatusRegister();
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

    /* Initialization Code */
    PWM_Start();
    Timer_Start();
    Magnet_Interrupt_Start();
    LCD_Start();
    Magnet_Interrupt_SetVector(magnet_inter);
    
    for(;;) {   
        if (magnet_flag == 1) {
            magnet_view_counter += 1;
            current_time = (double)(Timer_ReadCapture());
            
            /* Run this block only after the first magnet has been seen */
            if (magnet_view_counter != 1) {
                
                /* previous - current because the timer is counting down. */
                time_diff = previous_time - current_time;
                if (time_diff < 0) {
                    time_diff+=timer_max;
                }
                time_delta = (time_diff) / (clock_frequency);
                
                input_speed = magnet_separation_distance / time_delta;
                
                /* Compute the error variables */
                error = desired_speed - input_speed;
                err_sum += error * time_delta;
        
                /* Compute the PID output */
                output_speed = k_p * error + k_i * err_sum + 10;
        
                /* Send the output signal to the MOSFET controlling the motor */
                PWM_WriteCompare(output_speed);
                
                if (magnet_view_counter % 10 == 0) {
                    sprintf(str_buffer, "I:%.2f E:%.2f", input_speed, error);
                    LCD_Position(0, 0);
                    LCD_PrintString(str_buffer);                    
                }
            } else { 
                sprintf(str_buffer, "Skipped");
                LCD_Position(0, 0);
                LCD_PrintString(str_buffer);
            }
            
            magnet_flag = 0;
            previous_time = current_time;    
        }
    }
}

/* [] END OF FILE */
