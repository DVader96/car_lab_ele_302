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

double k_p = 5;  /* Gives us a fast rise time */
double k_i = 7;  /* Allows us to correct the steady state error */
double k_d = 0;  /* Dampens the system and reduces overshoot */

double kp_nav_control = 5;
double ki_nav_control = 7;
double kd_nav_control = 0;

double timer_max = 65535.0f;

double wheel_diam_feet = 2.5f / 12.0f; /* Diameter of the wheel in feet */
double clock_frequency = 10000.0f; /* Frequency of the clock in Hz */
double desired_speed = 4.0f;   /* Reference speed 4ft/sec */
int magnet_flag = 0;    /* Keeps track of magnet passes */

/* The line at which we'll check the black line */
int ith_line = 50; 
/* Boolean for deciding whether to listen to composite sync output */
int count_up_to_ith_line_flag = 0; 
/* A counter for the line number */
int current_line_number = 0;  


/* Set the flag that communicates that we've just seen a magnet */
CY_ISR(magnet_inter) {
    magnet_flag = 1;
    Timer_ReadStatusRegister();
}

/* If we encounter a dip in the vertical sync output, a new frame has
 * started. Set the flag that tells to listen for the ith line of our
 * choice.
 */
CY_ISR(vertical_sync_inter) {
    count_up_to_ith_line_flag = 1;
    current_line_number = 0;
}

/*
 * If the flag is true, count the lines up to i, and then set out to
 * determine the black line's position using the comparator output.
 */
CY_ISR(composite_sync_inter) {
    if (count_up_to_ith_line_flag) {
        
    }
}

/* */
CY_ISR(comparator_inter) {
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
    
    /* Added in Navigation Control */
    Composite_Sync_Counter_Start();
    Comparator_Counter_Start();
    Vertical_Sync_Counter_Start();
    PWM_Steering_Start();
    
    sprintf(str_buffer, "Speed Control");
    LCD_Position(0, 0);
    LCD_PrintString(str_buffer);
    
    /* PWM_WriteCompare(70); */
    
    /* Set the Interrupts */
    Magnet_Interrupt_SetVector(magnet_inter);
    Composite_Sync_Interrupt_SetVector(composite_sync_inter);
    Comparator_Interrupt_SetVector(comparator_inter);
    Vertical_Sync_Interrupt_SetVector(vertical_sync_inter);
    
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
                output_speed = k_p * error + k_i * err_sum + 20;
        
                /* Send the output signal to the MOSFET controlling the motor */
                PWM_WriteCompare(output_speed);
                // PWM_WriteCompare(7);
                
                if (magnet_view_counter % 10 == 0) {
                    sprintf(str_buffer, "%.2f", error);
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
        
        /* What to do with comparator? */
        
    }
}

/* [] END OF FILE */
