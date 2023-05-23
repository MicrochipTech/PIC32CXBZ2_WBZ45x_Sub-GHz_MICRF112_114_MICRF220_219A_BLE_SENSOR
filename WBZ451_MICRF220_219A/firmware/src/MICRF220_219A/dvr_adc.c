// <editor-fold defaultstate="collapsed" desc="File Header">
/***********************************************************************************************************************
 *
 * Filename:   dvr_adc.c
 *
 * Global Designator: ToDo
 *
 * Contents: ToDo
 * 
 ***********************************************************************************************************************
 * © 2023 Microchip Technology Inc. and its subsidiaries.  You may use this software and any derivatives exclusively
 * with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS
 * SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE,
 * COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF
 * THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON
 * ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID
 * DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 * 
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS. 
 ***********************************************************************************************************************
 *
 * Notes:  This ADC driver is simply an example of what a customer may use.  The ADC is NOT the intent of the demo.
 *         This module is created simply to convert the ADC reading from raw ADC counts to mV and send the data to the
 *         receiver module.  How the customer does this may vary.
 * 
 **********************************************************************************************************************/
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Include Files">
/* ****************************************************************************************************************** */
/* INCLUDE FILES */

#include "dvr_adc.h"
#include <stdbool.h>
#include "definitions.h"
#include "dvr_micrf220_219a.h"
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Macro Definitions">
/* ****************************************************************************************************************** */
/* MACRO DEFINITIONS */

// <editor-fold defaultstate="collapsed" desc="Type Definitions">
/* ****************************************************************************************************************** */
/* TYPE DEFINITIONS */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Constant Definitions">
/* ****************************************************************************************************************** */
/* CONSTANTS */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="File Variables - Static">
/* ****************************************************************************************************************** */
/* FILE VARIABLE DEFINITIONS */

static bool     bProcessAdcResult_ = false;
static void (*fpAdcCallBack_)(uint16_t);
uint16_t adcValue = 0;
uint16_t mV = 0;
        
// </editor-fold>

/* ****************************************************************************************************************** */
/* FUNCTION DEFINITIONS */

// <editor-fold defaultstate="collapsed" desc="void DVR_ADC_init( void )">
/***********************************************************************************************************************
 *
 * Function Name: DVR_ADC_init
 *
 * Purpose: Initialize the ADC driver module
 *
 * Arguments: None
 *
 * Returns: N/A
 *
 * Side Effects: ADC will be running
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void DVR_ADC_init( void )
{
    ADCHS_ChannelConversionStart(ADCHS_CH5);
    ADCHS_CallbackRegister( ADCHS_CH5, DVR_ADC_isr, (uintptr_t)NULL);
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void DVR_ADC_enable( void )">
/***********************************************************************************************************************
 *
 * Function Name: DVR_ADC_enable
 *
 * Purpose: Enables the ADC converter for the demo
 *
 * Arguments: None
 *
 * Returns: N/A
 *
 * Side Effects: The ADC will be running!
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void DVR_ADC_enable( void )
{
    ADCHS_ChannelConversionStart(ADCHS_CH5);
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void DVR_ADC_disable( void )">
/***********************************************************************************************************************
 *
 * Function Name: DVR_ADC_disable
 *
 * Purpose: Disables the ADC converter
 *
 * Arguments: None
 *
 * Returns: N/A
 *
 * Side Effects: The ADC will no longer be running
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void DVR_ADC_disable( void )
{
    ADCHS_GlobalLevelConversionStop();
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void DVR_ADC_setCallback( void (* fpCallbackFunction)( uint16_t adcVolts_mV ) )">
/***********************************************************************************************************************
 *
 * Function Name: DVR_ADC_setCallback
 *
 * Purpose: Sets a call-back function when the data has been processed.
 *
 * Arguments: void (* fpCallbackFunction)( uint16_t adcVolts_mV )
 *
 * Returns: None
 *
 * Side Effects: None
 *
 * Reentrant Code: No
 * 
 * Notes:  Call back at non-interrupt level!
 *
 **********************************************************************************************************************/
void DVR_ADC_setCallback( void (* fpCallbackFunction)( uint16_t adcVolts_mV ) )
{
    fpAdcCallBack_ = fpCallbackFunction;
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void DVR_ADC_processConversion( void )">
/***********************************************************************************************************************
 *
 * Function Name: DVR_ADC_processConversion
 *
 * Purpose: Processes the ADC results and calls the callback function.
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Side Effects: None
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void DVR_ADC_processConversion( void )
{
    if (bProcessAdcResult_)
    {
        bProcessAdcResult_ = false;        
        mV = (adcValue * 3000) / 4095; // Convert the ADC value to mV  
        fpAdcCallBack_(mV);
    }
}
/* ****************************************************************************************************************** */
// </editor-fold>

/* ****************************************************************************************************************** */
/* EVENT/ISR HANDLERS */

// <editor-fold defaultstate="collapsed" desc="void DVR_ADC_isr( void )">
/***********************************************************************************************************************
 *
 * Function Name: DVR_ADC_isr
 *
 * Purpose: Must be called at a rate of 1/2 to 1/4 the data rate.
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Side Effects: N/A
 *
 * Reentrant Code: No
 * 
 * Notes:  This function is called from the ADC module.  In the customer's application, the function may need to be
 *         removed and MICRF_setAdcValue() called from the customer's ADC module.
 *
 **********************************************************************************************************************/
void DVR_ADC_isr( ADCHS_CHANNEL_NUM channel, uintptr_t context )
{
    bProcessAdcResult_ = true;
    adcValue = ADCHS_ChannelResultGet(channel);
}
/* ****************************************************************************************************************** */
// </editor-fold>
