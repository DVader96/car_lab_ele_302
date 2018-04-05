/*******************************************************************************
* File Name: Vertical_Sync_Counter_PM.c  
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

#include "Vertical_Sync_Counter.h"

static Vertical_Sync_Counter_backupStruct Vertical_Sync_Counter_backup;


/*******************************************************************************
* Function Name: Vertical_Sync_Counter_SaveConfig
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
*  Vertical_Sync_Counter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Vertical_Sync_Counter_SaveConfig(void) 
{
    #if (!Vertical_Sync_Counter_UsingFixedFunction)

        Vertical_Sync_Counter_backup.CounterUdb = Vertical_Sync_Counter_ReadCounter();

        #if(!Vertical_Sync_Counter_ControlRegRemoved)
            Vertical_Sync_Counter_backup.CounterControlRegister = Vertical_Sync_Counter_ReadControlRegister();
        #endif /* (!Vertical_Sync_Counter_ControlRegRemoved) */

    #endif /* (!Vertical_Sync_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Vertical_Sync_Counter_RestoreConfig
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
*  Vertical_Sync_Counter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Vertical_Sync_Counter_RestoreConfig(void) 
{      
    #if (!Vertical_Sync_Counter_UsingFixedFunction)

       Vertical_Sync_Counter_WriteCounter(Vertical_Sync_Counter_backup.CounterUdb);

        #if(!Vertical_Sync_Counter_ControlRegRemoved)
            Vertical_Sync_Counter_WriteControlRegister(Vertical_Sync_Counter_backup.CounterControlRegister);
        #endif /* (!Vertical_Sync_Counter_ControlRegRemoved) */

    #endif /* (!Vertical_Sync_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Vertical_Sync_Counter_Sleep
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
*  Vertical_Sync_Counter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Vertical_Sync_Counter_Sleep(void) 
{
    #if(!Vertical_Sync_Counter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Vertical_Sync_Counter_CTRL_ENABLE == (Vertical_Sync_Counter_CONTROL & Vertical_Sync_Counter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Vertical_Sync_Counter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Vertical_Sync_Counter_backup.CounterEnableState = 0u;
        }
    #else
        Vertical_Sync_Counter_backup.CounterEnableState = 1u;
        if(Vertical_Sync_Counter_backup.CounterEnableState != 0u)
        {
            Vertical_Sync_Counter_backup.CounterEnableState = 0u;
        }
    #endif /* (!Vertical_Sync_Counter_ControlRegRemoved) */
    
    Vertical_Sync_Counter_Stop();
    Vertical_Sync_Counter_SaveConfig();
}


/*******************************************************************************
* Function Name: Vertical_Sync_Counter_Wakeup
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
*  Vertical_Sync_Counter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Vertical_Sync_Counter_Wakeup(void) 
{
    Vertical_Sync_Counter_RestoreConfig();
    #if(!Vertical_Sync_Counter_ControlRegRemoved)
        if(Vertical_Sync_Counter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Vertical_Sync_Counter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Vertical_Sync_Counter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
