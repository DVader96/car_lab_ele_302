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

/* General Strategy:
 * Update k_p till we get to the target speed 
 * Tune k_i till we get few errors
 * We'll not be using k_d in this control loop
 */

double k_p = 10;  /* Gives us a fast rise time */
double k_i = 10;  /* Allows us to correct the steady state error */
double k_d = 0;  /* Dampens the system and reduces overshoot */

double timer_max = 65535.0f;

double wheel_diam_feet = 2.5f / 12.0f; /* Diameter of the wheel in feet */
double clock_frequency = 10000.0f; /* Frequency of the clock in Hz */
double desired_speed = 4.0f;   /* Reference speed 4ft/sec */
int magnet_flag = 0;    /* Keeps track of magnet passes */

/* Changes Made:
 * Structure of the if-else block
 * Measured and set wheel_diam_inches to 2.5 inches
 * Defined magnet_separation_distance and got the input speed.
 * Added the PWM write statement to give the new speed.
 * Print out the recently measured speed to the LCD display.
 * The timer output is in clock cycles. Divided by frequency to get the time.
 * Update the strategy for updating k_i, k_p and k_d.
 * We don't need the array of magnet_view_times. We need the last & the current reading only.
 *
 * 1st attempt: 
 * The motor wasn't working. Prof. Jeff showed me that the grounds aren't connected.
 * To check for connectedness, use the noisy part of the special multimeter.
 * To fix the ground problem, we connected the two grounds together.
 *
 * 2nd attempt:
 * We need a way of converting from ft/sec to a number between 0 and 255 for the PWM
 * 0 means always off, while 255 means always on.
 * We're using the feet_per_sec_to_counts_factor to handle this conversion.
 * Actually, feet_per_sec_to_counts_factor is doing double work. The conversion should be
 * handled by the values of k_p and k_i that we choose. We've now deleted feet_per_sec_to_counts_factor
 *
 * 3rd attempt
 * We're trying to display the speed of the car on the LCD. However, the if-elses in the infinite for-loop
 * are not working as expected. 
 * We added an LED to ensure that the interrupt is firing.
 *
 */

CY_ISR(magnet_inter) {
    /* char str_buffer[16]; */
    magnet_flag = 1;
    Timer_ReadStatusRegister();
    /*
    sprintf(str_buffer, "Magnet");
    LCD_Position(0, 0);
    LCD_PrintString(str_buffer); */
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
    
    sprintf(str_buffer, "Speed Control");
    LCD_Position(0, 0);
    LCD_PrintString(str_buffer);
    
    /* PWM_WriteCompare(70); */
    Magnet_Interrupt_SetVector(magnet_inter);
    
    for(;;) {
        
        /*sprintf(str_buffer, "%d", magnet_view_counter);
        LCD_Position(0, 0);
        LCD_PrintString(str_buffer); */
        
        
      
        
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
                output_speed = k_p * error + k_i * err_sum + 20;
        
                /* Send the output signal to the MOSFET controlling the motor */
                PWM_WriteCompare(output_speed);
                 //PWM_WriteCompare(7);
                /* Communicate the speed to the user */ 
                /* sprintf(str_buffer, "I:%.2f, O:%.2f", input_speed, output_speed); */
                
                if (magnet_view_counter % 10 == 0) {
                    /*sprintf(str_buffer, "%.2f", input_speed);
                    LCD_Position(0, 0);
                    LCD_PrintString(str_buffer);*/
                    sprintf(str_buffer, "%.2f", error);
                    LCD_Position(0, 0);
                    LCD_PrintString(str_buffer);
                }
            
            } else {
                
                /* Communicate the speed to the user */ 
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
