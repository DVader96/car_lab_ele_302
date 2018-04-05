/*******************************************************************************
* File Name: PWM_Steering_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_Steering.h"

static PWM_Steering_backupStruct PWM_Steering_backup;


/*******************************************************************************
* Function Name: PWM_Steering_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Steering_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Steering_SaveConfig(void) 
{

    #if(!PWM_Steering_UsingFixedFunction)
        #if(!PWM_Steering_PWMModeIsCenterAligned)
            PWM_Steering_backup.PWMPeriod = PWM_Steering_ReadPeriod();
        #endif /* (!PWM_Steering_PWMModeIsCenterAligned) */
        PWM_Steering_backup.PWMUdb = PWM_Steering_ReadCounter();
        #if (PWM_Steering_UseStatus)
            PWM_Steering_backup.InterruptMaskValue = PWM_Steering_STATUS_MASK;
        #endif /* (PWM_Steering_UseStatus) */

        #if(PWM_Steering_DeadBandMode == PWM_Steering__B_PWM__DBM_256_CLOCKS || \
            PWM_Steering_DeadBandMode == PWM_Steering__B_PWM__DBM_2_4_CLOCKS)
            PWM_Steering_backup.PWMdeadBandValue = PWM_Steering_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Steering_KillModeMinTime)
             PWM_Steering_backup.PWMKillCounterPeriod = PWM_Steering_ReadKillTime();
        #endif /* (PWM_Steering_KillModeMinTime) */

        #if(PWM_Steering_UseControl)
            PWM_Steering_backup.PWMControlRegister = PWM_Steering_ReadControlRegister();
        #endif /* (PWM_Steering_UseControl) */
    #endif  /* (!PWM_Steering_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Steering_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Steering_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Steering_RestoreConfig(void) 
{
        #if(!PWM_Steering_UsingFixedFunction)
            #if(!PWM_Steering_PWMModeIsCenterAligned)
                PWM_Steering_WritePeriod(PWM_Steering_backup.PWMPeriod);
            #endif /* (!PWM_Steering_PWMModeIsCenterAligned) */

            PWM_Steering_WriteCounter(PWM_Steering_backup.PWMUdb);

            #if (PWM_Steering_UseStatus)
                PWM_Steering_STATUS_MASK = PWM_Steering_backup.InterruptMaskValue;
            #endif /* (PWM_Steering_UseStatus) */

            #if(PWM_Steering_DeadBandMode == PWM_Steering__B_PWM__DBM_256_CLOCKS || \
                PWM_Steering_DeadBandMode == PWM_Steering__B_PWM__DBM_2_4_CLOCKS)
                PWM_Steering_WriteDeadTime(PWM_Steering_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Steering_KillModeMinTime)
                PWM_Steering_WriteKillTime(PWM_Steering_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Steering_KillModeMinTime) */

            #if(PWM_Steering_UseControl)
                PWM_Steering_WriteControlRegister(PWM_Steering_backup.PWMControlRegister);
            #endif /* (PWM_Steering_UseControl) */
        #endif  /* (!PWM_Steering_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Steering_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Steering_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Steering_Sleep(void) 
{
    #if(PWM_Steering_UseControl)
        if(PWM_Steering_CTRL_ENABLE == (PWM_Steering_CONTROL & PWM_Steering_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Steering_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Steering_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Steering_UseControl) */

    /* Stop component */
    PWM_Steering_Stop();

    /* Save registers configuration */
    PWM_Steering_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Steering_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Steering_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Steering_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Steering_RestoreConfig();

    if(PWM_Steering_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Steering_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
