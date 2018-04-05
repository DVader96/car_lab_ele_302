/*******************************************************************************
* File Name: Comparator_Counter_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Comparator_Counter.h"

static Comparator_Counter_backupStruct Comparator_Counter_backup;


/*******************************************************************************
* Function Name: Comparator_Counter_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Comparator_Counter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Comparator_Counter_SaveConfig(void) 
{
    #if (!Comparator_Counter_UsingFixedFunction)

        Comparator_Counter_backup.CounterUdb = Comparator_Counter_ReadCounter();

        #if(!Comparator_Counter_ControlRegRemoved)
            Comparator_Counter_backup.CounterControlRegister = Comparator_Counter_ReadControlRegister();
        #endif /* (!Comparator_Counter_ControlRegRemoved) */

    #endif /* (!Comparator_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Comparator_Counter_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Comparator_Counter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Comparator_Counter_RestoreConfig(void) 
{      
    #if (!Comparator_Counter_UsingFixedFunction)

       Comparator_Counter_WriteCounter(Comparator_Counter_backup.CounterUdb);

        #if(!Comparator_Counter_ControlRegRemoved)
            Comparator_Counter_WriteControlRegister(Comparator_Counter_backup.CounterControlRegister);
        #endif /* (!Comparator_Counter_ControlRegRemoved) */

    #endif /* (!Comparator_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Comparator_Counter_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Comparator_Counter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Comparator_Counter_Sleep(void) 
{
    #if(!Comparator_Counter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Comparator_Counter_CTRL_ENABLE == (Comparator_Counter_CONTROL & Comparator_Counter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Comparator_Counter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Comparator_Counter_backup.CounterEnableState = 0u;
        }
    #else
        Comparator_Counter_backup.CounterEnableState = 1u;
        if(Comparator_Counter_backup.CounterEnableState != 0u)
        {
            Comparator_Counter_backup.CounterEnableState = 0u;
        }
    #endif /* (!Comparator_Counter_ControlRegRemoved) */
    
    Comparator_Counter_Stop();
    Comparator_Counter_SaveConfig();
}


/*******************************************************************************
* Function Name: Comparator_Counter_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Comparator_Counter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Comparator_Counter_Wakeup(void) 
{
    Comparator_Counter_RestoreConfig();
    #if(!Comparator_Counter_ControlRegRemoved)
        if(Comparator_Counter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Comparator_Counter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Comparator_Counter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
