/*******************************************************************************
* File Name: Magnet_Interrupt.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Magnet_Interrupt_H)
#define CY_ISR_Magnet_Interrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Magnet_Interrupt_Start(void);
void Magnet_Interrupt_StartEx(cyisraddress address);
void Magnet_Interrupt_Stop(void);

CY_ISR_PROTO(Magnet_Interrupt_Interrupt);

void Magnet_Interrupt_SetVector(cyisraddress address);
cyisraddress Magnet_Interrupt_GetVector(void);

void Magnet_Interrupt_SetPriority(uint8 priority);
uint8 Magnet_Interrupt_GetPriority(void);

void Magnet_Interrupt_Enable(void);
uint8 Magnet_Interrupt_GetState(void);
void Magnet_Interrupt_Disable(void);

void Magnet_Interrupt_SetPending(void);
void Magnet_Interrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Magnet_Interrupt ISR. */
#define Magnet_Interrupt_INTC_VECTOR            ((reg32 *) Magnet_Interrupt__INTC_VECT)

/* Address of the Magnet_Interrupt ISR priority. */
#define Magnet_Interrupt_INTC_PRIOR             ((reg8 *) Magnet_Interrupt__INTC_PRIOR_REG)

/* Priority of the Magnet_Interrupt interrupt. */
#define Magnet_Interrupt_INTC_PRIOR_NUMBER      Magnet_Interrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Magnet_Interrupt interrupt. */
#define Magnet_Interrupt_INTC_SET_EN            ((reg32 *) Magnet_Interrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Magnet_Interrupt interrupt. */
#define Magnet_Interrupt_INTC_CLR_EN            ((reg32 *) Magnet_Interrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Magnet_Interrupt interrupt state to pending. */
#define Magnet_Interrupt_INTC_SET_PD            ((reg32 *) Magnet_Interrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Magnet_Interrupt interrupt. */
#define Magnet_Interrupt_INTC_CLR_PD            ((reg32 *) Magnet_Interrupt__INTC_CLR_PD_REG)


#endif /* CY_ISR_Magnet_Interrupt_H */


/* [] END OF FILE */
