/*******************************************************************************
* File Name: Composite_Sync_Counter_PM.c  
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

#include "Composite_Sync_Counter.h"

static Composite_Sync_Counter_backupStruct Composite_Sync_Counter_backup;


/*******************************************************************************
* Function Name: Composite_Sync_Counter_SaveConfig
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
*  Composite_Sync_Counter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Composite_Sync_Counter_SaveConfig(void) 
{
    #if (!Composite_Sync_Counter_UsingFixedFunction)

        Composite_Sync_Counter_backup.CounterUdb = Composite_Sync_Counter_ReadCounter();

        #if(!Composite_Sync_Counter_ControlRegRemoved)
            Composite_Sync_Counter_backup.CounterControlRegister = Composite_Sync_Counter_ReadControlRegister();
        #endif /* (!Composite_Sync_Counter_ControlRegRemoved) */

    #endif /* (!Composite_Sync_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Composite_Sync_Counter_RestoreConfig
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
*  Composite_Sync_Counter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Composite_Sync_Counter_RestoreConfig(void) 
{      
    #if (!Composite_Sync_Counter_UsingFixedFunction)

       Composite_Sync_Counter_WriteCounter(Composite_Sync_Counter_backup.CounterUdb);

        #if(!Composite_Sync_Counter_ControlRegRemoved)
            Composite_Sync_Counter_WriteControlRegister(Composite_Sync_Counter_backup.CounterControlRegister);
        #endif /* (!Composite_Sync_Counter_ControlRegRemoved) */

    #endif /* (!Composite_Sync_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Composite_Sync_Counter_Sleep
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
*  Composite_Sync_Counter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Composite_Sync_Counter_Sleep(void) 
{
    #if(!Composite_Sync_Counter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Composite_Sync_Counter_CTRL_ENABLE == (Composite_Sync_Counter_CONTROL & Composite_Sync_Counter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Composite_Sync_Counter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Composite_Sync_Counter_backup.CounterEnableState = 0u;
        }
    #else
        Composite_Sync_Counter_backup.CounterEnableState = 1u;
        if(Composite_Sync_Counter_backup.CounterEnableState != 0u)
        {
            Composite_Sync_Counter_backup.CounterEnableState = 0u;
        }
    #endif /* (!Composite_Sync_Counter_ControlRegRemoved) */
    
    Composite_Sync_Counter_Stop();
    Composite_Sync_Counter_SaveConfig();
}


/*******************************************************************************
* Function Name: Composite_Sync_Counter_Wakeup
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
*  Composite_Sync_Counter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Composite_Sync_Counter_Wakeup(void) 
{
    Composite_Sync_Counter_RestoreConfig();
    #if(!Composite_Sync_Counter_ControlRegRemoved)
        if(Composite_Sync_Counter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Composite_Sync_Counter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Composite_Sync_Counter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
