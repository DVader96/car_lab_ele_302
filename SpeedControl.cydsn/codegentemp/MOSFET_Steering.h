/*******************************************************************************
* File Name: MOSFET_Steering.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_MOSFET_Steering_H) /* Pins MOSFET_Steering_H */
#define CY_PINS_MOSFET_Steering_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MOSFET_Steering_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MOSFET_Steering__PORT == 15 && ((MOSFET_Steering__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MOSFET_Steering_Write(uint8 value);
void    MOSFET_Steering_SetDriveMode(uint8 mode);
uint8   MOSFET_Steering_ReadDataReg(void);
uint8   MOSFET_Steering_Read(void);
void    MOSFET_Steering_SetInterruptMode(uint16 position, uint16 mode);
uint8   MOSFET_Steering_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MOSFET_Steering_SetDriveMode() function.
     *  @{
     */
        #define MOSFET_Steering_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MOSFET_Steering_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MOSFET_Steering_DM_RES_UP          PIN_DM_RES_UP
        #define MOSFET_Steering_DM_RES_DWN         PIN_DM_RES_DWN
        #define MOSFET_Steering_DM_OD_LO           PIN_DM_OD_LO
        #define MOSFET_Steering_DM_OD_HI           PIN_DM_OD_HI
        #define MOSFET_Steering_DM_STRONG          PIN_DM_STRONG
        #define MOSFET_Steering_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MOSFET_Steering_MASK               MOSFET_Steering__MASK
#define MOSFET_Steering_SHIFT              MOSFET_Steering__SHIFT
#define MOSFET_Steering_WIDTH              1u

/* Interrupt constants */
#if defined(MOSFET_Steering__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MOSFET_Steering_SetInterruptMode() function.
     *  @{
     */
        #define MOSFET_Steering_INTR_NONE      (uint16)(0x0000u)
        #define MOSFET_Steering_INTR_RISING    (uint16)(0x0001u)
        #define MOSFET_Steering_INTR_FALLING   (uint16)(0x0002u)
        #define MOSFET_Steering_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MOSFET_Steering_INTR_MASK      (0x01u) 
#endif /* (MOSFET_Steering__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MOSFET_Steering_PS                     (* (reg8 *) MOSFET_Steering__PS)
/* Data Register */
#define MOSFET_Steering_DR                     (* (reg8 *) MOSFET_Steering__DR)
/* Port Number */
#define MOSFET_Steering_PRT_NUM                (* (reg8 *) MOSFET_Steering__PRT) 
/* Connect to Analog Globals */                                                  
#define MOSFET_Steering_AG                     (* (reg8 *) MOSFET_Steering__AG)                       
/* Analog MUX bux enable */
#define MOSFET_Steering_AMUX                   (* (reg8 *) MOSFET_Steering__AMUX) 
/* Bidirectional Enable */                                                        
#define MOSFET_Steering_BIE                    (* (reg8 *) MOSFET_Steering__BIE)
/* Bit-mask for Aliased Register Access */
#define MOSFET_Steering_BIT_MASK               (* (reg8 *) MOSFET_Steering__BIT_MASK)
/* Bypass Enable */
#define MOSFET_Steering_BYP                    (* (reg8 *) MOSFET_Steering__BYP)
/* Port wide control signals */                                                   
#define MOSFET_Steering_CTL                    (* (reg8 *) MOSFET_Steering__CTL)
/* Drive Modes */
#define MOSFET_Steering_DM0                    (* (reg8 *) MOSFET_Steering__DM0) 
#define MOSFET_Steering_DM1                    (* (reg8 *) MOSFET_Steering__DM1)
#define MOSFET_Steering_DM2                    (* (reg8 *) MOSFET_Steering__DM2) 
/* Input Buffer Disable Override */
#define MOSFET_Steering_INP_DIS                (* (reg8 *) MOSFET_Steering__INP_DIS)
/* LCD Common or Segment Drive */
#define MOSFET_Steering_LCD_COM_SEG            (* (reg8 *) MOSFET_Steering__LCD_COM_SEG)
/* Enable Segment LCD */
#define MOSFET_Steering_LCD_EN                 (* (reg8 *) MOSFET_Steering__LCD_EN)
/* Slew Rate Control */
#define MOSFET_Steering_SLW                    (* (reg8 *) MOSFET_Steering__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MOSFET_Steering_PRTDSI__CAPS_SEL       (* (reg8 *) MOSFET_Steering__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MOSFET_Steering_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MOSFET_Steering__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MOSFET_Steering_PRTDSI__OE_SEL0        (* (reg8 *) MOSFET_Steering__PRTDSI__OE_SEL0) 
#define MOSFET_Steering_PRTDSI__OE_SEL1        (* (reg8 *) MOSFET_Steering__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MOSFET_Steering_PRTDSI__OUT_SEL0       (* (reg8 *) MOSFET_Steering__PRTDSI__OUT_SEL0) 
#define MOSFET_Steering_PRTDSI__OUT_SEL1       (* (reg8 *) MOSFET_Steering__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MOSFET_Steering_PRTDSI__SYNC_OUT       (* (reg8 *) MOSFET_Steering__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MOSFET_Steering__SIO_CFG)
    #define MOSFET_Steering_SIO_HYST_EN        (* (reg8 *) MOSFET_Steering__SIO_HYST_EN)
    #define MOSFET_Steering_SIO_REG_HIFREQ     (* (reg8 *) MOSFET_Steering__SIO_REG_HIFREQ)
    #define MOSFET_Steering_SIO_CFG            (* (reg8 *) MOSFET_Steering__SIO_CFG)
    #define MOSFET_Steering_SIO_DIFF           (* (reg8 *) MOSFET_Steering__SIO_DIFF)
#endif /* (MOSFET_Steering__SIO_CFG) */

/* Interrupt Registers */
#if defined(MOSFET_Steering__INTSTAT)
    #define MOSFET_Steering_INTSTAT            (* (reg8 *) MOSFET_Steering__INTSTAT)
    #define MOSFET_Steering_SNAP               (* (reg8 *) MOSFET_Steering__SNAP)
    
	#define MOSFET_Steering_0_INTTYPE_REG 		(* (reg8 *) MOSFET_Steering__0__INTTYPE)
#endif /* (MOSFET_Steering__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MOSFET_Steering_H */


/* [] END OF FILE */
