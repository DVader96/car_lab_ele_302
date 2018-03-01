/* ========================================
 *
 * Chege Gitau & Eric Ham
 * ELE 302
 * Speed Control
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>


static double k_p = 0;  /* Gives us a fast rise time */
static double k_i = 0;  /* Allows us to correct the steady state error */
static double k_d = 0;  /* Dampens the system and reduces overshoot */

static double wheel_diam_inches = 2.5;

static double desired_speed = 4;   /* Reference speed 4ft/sec */

static int magnet_flag = 0;    /* Keeps track of magnet passes */

static int index_of_magnet = 0;
static double magnet_view_times[] = {0, 0, 0, 0, 0};


CY_ISR(magnet_inter) {
    magnet_flag = 1;
    index_of_magnet += 1;
}

int main(void)
{
    double input_speed, output_speed, magnet_separation_distance;
    unsigned long time_delta;
    double error, err_sum, err_derivative, last_error;
    int current_index, previous_index;
    char str_buffer[16];
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Initialization Code */
    PWM_Start();
    Timer_Start();
    Counter_Interrupt_Start();
    Counter_Interrupt_SetVector(magnet_inter);
    
    LCD_Position(0, 0);
    LCD_PrintString("Speed Control!");
    magnet_separation_distance = (22.0f / 7.0f) * wheel_diam_inches / 5.0f;
    last_error = 0;
    
    /* Changes Made:
     * Structure of the if-else block
     * Measured and set wheel_diam_inches to 2.5 inches
     * Defined magnet_separation_distance and got the input speed.
     * Added the PWM write statement to give the new speed.
     * Print out the recently measured speed to the LCD display.
     */
    
    for(;;) { 
        
        if (magnet_flag == 1) {
            
            current_index = index_of_magnet % 5;
            magnet_view_times[current_index] = Timer_ReadCapture();
        
            if (index_of_magnet != 1) {
                
                previous_index = (index_of_magnet - 1) % 5; 
            
                /* previous - current because the timer is counting down. */
                time_delta = (double)(magnet_view_times[previous_index] - magnet_view_times[current_index]);
                input_speed = magnet_separation_distance / time_delta;
                
                /* Compute the error variables */
                error = desired_speed - input_speed;
                err_sum = error * time_delta;
                err_derivative = (error - last_error) / time_delta;
        
                /* Compute the PID output */
                output_speed = k_p * error + k_i * err_sum + k_d * err_derivative;
        
                /* Tell the motor to switch to this new speed */
                PWM_WriteCompare(output_speed);
        
                /* Store variables needed for the next run */
                last_error = error;
                
                /* Communicate the speed to the user */
                sprintf(str_buffer, "%f", input_speed);
                LCD_Position(0, 0);
                LCD_PrintString(str_buffer);
            }
            
            /* Set the flag to off so that it can be updated in the next cycle */
            magnet_flag = 0;
        }   
    }
}

/* [] END OF FILE */
