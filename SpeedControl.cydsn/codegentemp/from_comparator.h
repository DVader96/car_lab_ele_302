/*******************************************************************************
* File Name: from_comparator.h  
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

#if !defined(CY_PINS_from_comparator_H) /* Pins from_comparator_H */
#define CY_PINS_from_comparator_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "from_comparator_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 from_comparator__PORT == 15 && ((from_comparator__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    from_comparator_Write(uint8 value);
void    from_comparator_SetDriveMode(uint8 mode);
uint8   from_comparator_ReadDataReg(void);
uint8   from_comparator_Read(void);
void    from_comparator_SetInterruptMode(uint16 position, uint16 mode);
uint8   from_comparator_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the from_comparator_SetDriveMode() function.
     *  @{
     */
        #define from_comparator_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define from_comparator_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define from_comparator_DM_RES_UP          PIN_DM_RES_UP
        #define from_comparator_DM_RES_DWN         PIN_DM_RES_DWN
        #define from_comparator_DM_OD_LO           PIN_DM_OD_LO
        #define from_comparator_DM_OD_HI           PIN_DM_OD_HI
        #define from_comparator_DM_STRONG          PIN_DM_STRONG
        #define from_comparator_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define from_comparator_MASK               from_comparator__MASK
#define from_comparator_SHIFT              from_comparator__SHIFT
#define from_comparator_WIDTH              1u

/* Interrupt constants */
#if defined(from_comparator__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in from_comparator_SetInterruptMode() function.
     *  @{
     */
        #define from_comparator_INTR_NONE      (uint16)(0x0000u)
        #define from_comparator_INTR_RISING    (uint16)(0x0001u)
        #define from_comparator_INTR_FALLING   (uint16)(0x0002u)
        #define from_comparator_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define from_comparator_INTR_MASK      (0x01u) 
#endif /* (from_comparator__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define from_comparator_PS                     (* (reg8 *) from_comparator__PS)
/* Data Register */
#define from_comparator_DR                     (* (reg8 *) from_comparator__DR)
/* Port Number */
#define from_comparator_PRT_NUM                (* (reg8 *) from_comparator__PRT) 
/* Connect to Analog Globals */                                                  
#define from_comparator_AG                     (* (reg8 *) from_comparator__AG)                       
/* Analog MUX bux enable */
#define from_comparator_AMUX                   (* (reg8 *) from_comparator__AMUX) 
/* Bidirectional Enable */                                                        
#define from_comparator_BIE                    (* (reg8 *) from_comparator__BIE)
/* Bit-mask for Aliased Register Access */
#define from_comparator_BIT_MASK               (* (reg8 *) from_comparator__BIT_MASK)
/* Bypass Enable */
#define from_comparator_BYP                    (* (reg8 *) from_comparator__BYP)
/* Port wide control signals */                                                   
#define from_comparator_CTL                    (* (reg8 *) from_comparator__CTL)
/* Drive Modes */
#define from_comparator_DM0                    (* (reg8 *) from_comparator__DM0) 
#define from_comparator_DM1                    (* (reg8 *) from_comparator__DM1)
#define from_comparator_DM2                    (* (reg8 *) from_comparator__DM2) 
/* Input Buffer Disable Override */
#define from_comparator_INP_DIS                (* (reg8 *) from_comparator__INP_DIS)
/* LCD Common or Segment Drive */
#define from_comparator_LCD_COM_SEG            (* (reg8 *) from_comparator__LCD_COM_SEG)
/* Enable Segment LCD */
#define from_comparator_LCD_EN                 (* (reg8 *) from_comparator__LCD_EN)
/* Slew Rate Control */
#define from_comparator_SLW                    (* (reg8 *) from_comparator__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define from_comparator_PRTDSI__CAPS_SEL       (* (reg8 *) from_comparator__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define from_comparator_PRTDSI__DBL_SYNC_IN    (* (reg8 *) from_comparator__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define from_comparator_PRTDSI__OE_SEL0        (* (reg8 *) from_comparator__PRTDSI__OE_SEL0) 
#define from_comparator_PRTDSI__OE_SEL1        (* (reg8 *) from_comparator__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define from_comparator_PRTDSI__OUT_SEL0       (* (reg8 *) from_comparator__PRTDSI__OUT_SEL0) 
#define from_comparator_PRTDSI__OUT_SEL1       (* (reg8 *) from_comparator__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define from_comparator_PRTDSI__SYNC_OUT       (* (reg8 *) from_comparator__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(from_comparator__SIO_CFG)
    #define from_comparator_SIO_HYST_EN        (* (reg8 *) from_comparator__SIO_HYST_EN)
    #define from_comparator_SIO_REG_HIFREQ     (* (reg8 *) from_comparator__SIO_REG_HIFREQ)
    #define from_comparator_SIO_CFG            (* (reg8 *) from_comparator__SIO_CFG)
    #define from_comparator_SIO_DIFF           (* (reg8 *) from_comparator__SIO_DIFF)
#endif /* (from_comparator__SIO_CFG) */

/* Interrupt Registers */
#if defined(from_comparator__INTSTAT)
    #define from_comparator_INTSTAT            (* (reg8 *) from_comparator__INTSTAT)
    #define from_comparator_SNAP               (* (reg8 *) from_comparator__SNAP)
    
	#define from_comparator_0_INTTYPE_REG 		(* (reg8 *) from_comparator__0__INTTYPE)
#endif /* (from_comparator__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_from_comparator_H */


/* [] END OF FILE */
