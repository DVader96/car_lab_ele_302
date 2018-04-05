/*******************************************************************************
* File Name: hall_effect_sensor.h  
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

#if !defined(CY_PINS_hall_effect_sensor_H) /* Pins hall_effect_sensor_H */
#define CY_PINS_hall_effect_sensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "hall_effect_sensor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 hall_effect_sensor__PORT == 15 && ((hall_effect_sensor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    hall_effect_sensor_Write(uint8 value);
void    hall_effect_sensor_SetDriveMode(uint8 mode);
uint8   hall_effect_sensor_ReadDataReg(void);
uint8   hall_effect_sensor_Read(void);
void    hall_effect_sensor_SetInterruptMode(uint16 position, uint16 mode);
uint8   hall_effect_sensor_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the hall_effect_sensor_SetDriveMode() function.
     *  @{
     */
        #define hall_effect_sensor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define hall_effect_sensor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define hall_effect_sensor_DM_RES_UP          PIN_DM_RES_UP
        #define hall_effect_sensor_DM_RES_DWN         PIN_DM_RES_DWN
        #define hall_effect_sensor_DM_OD_LO           PIN_DM_OD_LO
        #define hall_effect_sensor_DM_OD_HI           PIN_DM_OD_HI
        #define hall_effect_sensor_DM_STRONG          PIN_DM_STRONG
        #define hall_effect_sensor_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define hall_effect_sensor_MASK               hall_effect_sensor__MASK
#define hall_effect_sensor_SHIFT              hall_effect_sensor__SHIFT
#define hall_effect_sensor_WIDTH              1u

/* Interrupt constants */
#if defined(hall_effect_sensor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in hall_effect_sensor_SetInterruptMode() function.
     *  @{
     */
        #define hall_effect_sensor_INTR_NONE      (uint16)(0x0000u)
        #define hall_effect_sensor_INTR_RISING    (uint16)(0x0001u)
        #define hall_effect_sensor_INTR_FALLING   (uint16)(0x0002u)
        #define hall_effect_sensor_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define hall_effect_sensor_INTR_MASK      (0x01u) 
#endif /* (hall_effect_sensor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define hall_effect_sensor_PS                     (* (reg8 *) hall_effect_sensor__PS)
/* Data Register */
#define hall_effect_sensor_DR                     (* (reg8 *) hall_effect_sensor__DR)
/* Port Number */
#define hall_effect_sensor_PRT_NUM                (* (reg8 *) hall_effect_sensor__PRT) 
/* Connect to Analog Globals */                                                  
#define hall_effect_sensor_AG                     (* (reg8 *) hall_effect_sensor__AG)                       
/* Analog MUX bux enable */
#define hall_effect_sensor_AMUX                   (* (reg8 *) hall_effect_sensor__AMUX) 
/* Bidirectional Enable */                                                        
#define hall_effect_sensor_BIE                    (* (reg8 *) hall_effect_sensor__BIE)
/* Bit-mask for Aliased Register Access */
#define hall_effect_sensor_BIT_MASK               (* (reg8 *) hall_effect_sensor__BIT_MASK)
/* Bypass Enable */
#define hall_effect_sensor_BYP                    (* (reg8 *) hall_effect_sensor__BYP)
/* Port wide control signals */                                                   
#define hall_effect_sensor_CTL                    (* (reg8 *) hall_effect_sensor__CTL)
/* Drive Modes */
#define hall_effect_sensor_DM0                    (* (reg8 *) hall_effect_sensor__DM0) 
#define hall_effect_sensor_DM1                    (* (reg8 *) hall_effect_sensor__DM1)
#define hall_effect_sensor_DM2                    (* (reg8 *) hall_effect_sensor__DM2) 
/* Input Buffer Disable Override */
#define hall_effect_sensor_INP_DIS                (* (reg8 *) hall_effect_sensor__INP_DIS)
/* LCD Common or Segment Drive */
#define hall_effect_sensor_LCD_COM_SEG            (* (reg8 *) hall_effect_sensor__LCD_COM_SEG)
/* Enable Segment LCD */
#define hall_effect_sensor_LCD_EN                 (* (reg8 *) hall_effect_sensor__LCD_EN)
/* Slew Rate Control */
#define hall_effect_sensor_SLW                    (* (reg8 *) hall_effect_sensor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define hall_effect_sensor_PRTDSI__CAPS_SEL       (* (reg8 *) hall_effect_sensor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define hall_effect_sensor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) hall_effect_sensor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define hall_effect_sensor_PRTDSI__OE_SEL0        (* (reg8 *) hall_effect_sensor__PRTDSI__OE_SEL0) 
#define hall_effect_sensor_PRTDSI__OE_SEL1        (* (reg8 *) hall_effect_sensor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define hall_effect_sensor_PRTDSI__OUT_SEL0       (* (reg8 *) hall_effect_sensor__PRTDSI__OUT_SEL0) 
#define hall_effect_sensor_PRTDSI__OUT_SEL1       (* (reg8 *) hall_effect_sensor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define hall_effect_sensor_PRTDSI__SYNC_OUT       (* (reg8 *) hall_effect_sensor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(hall_effect_sensor__SIO_CFG)
    #define hall_effect_sensor_SIO_HYST_EN        (* (reg8 *) hall_effect_sensor__SIO_HYST_EN)
    #define hall_effect_sensor_SIO_REG_HIFREQ     (* (reg8 *) hall_effect_sensor__SIO_REG_HIFREQ)
    #define hall_effect_sensor_SIO_CFG            (* (reg8 *) hall_effect_sensor__SIO_CFG)
    #define hall_effect_sensor_SIO_DIFF           (* (reg8 *) hall_effect_sensor__SIO_DIFF)
#endif /* (hall_effect_sensor__SIO_CFG) */

/* Interrupt Registers */
#if defined(hall_effect_sensor__INTSTAT)
    #define hall_effect_sensor_INTSTAT            (* (reg8 *) hall_effect_sensor__INTSTAT)
    #define hall_effect_sensor_SNAP               (* (reg8 *) hall_effect_sensor__SNAP)
    
	#define hall_effect_sensor_0_INTTYPE_REG 		(* (reg8 *) hall_effect_sensor__0__INTTYPE)
#endif /* (hall_effect_sensor__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_hall_effect_sensor_H */


/* [] END OF FILE */
