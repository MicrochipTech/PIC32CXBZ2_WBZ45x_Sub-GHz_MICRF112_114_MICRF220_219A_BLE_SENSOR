// <editor-fold defaultstate="collapsed" desc="File Header">
/***********************************************************************************************************************
 *
 * Filename:   dvr_crc.c
 *
 * Global Designator: DVR_CRC_
 *
 * Contents: Interface to the hardware CRC module created by MCC.
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
 **********************************************************************************************************************/
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Include Files">
/* ****************************************************************************************************************** */
/* INCLUDE FILES */

#include "dvr_crc.h"
#include <stdio.h>
#include <stdint.h>

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Macro Definitions">
/* ****************************************************************************************************************** */
/* MACRO DEFINITIONS */


#define POLY 0x8005

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Type Definitions">
/* ****************************************************************************************************************** */
/* TYPE DEFINITIONS */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Local Function Prototypes">
/* ****************************************************************************************************************** */
/* FUNCTION PROTOTYPES */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Constant Definitions">
/* ****************************************************************************************************************** */
/* CONSTANTS */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="File Variables - Static">
/* ****************************************************************************************************************** */
/* FILE VARIABLE DEFINITIONS */

// </editor-fold>

/* ****************************************************************************************************************** */
/* FUNCTION DEFINITIONS */

// <editor-fold defaultstate="collapsed" desc="uint16_t DVR_CRC_calc( void *pData, uint8_t cnt )">

/***********************************************************************************************************************
 *
 * Function Name: DVR_CRC_calc
 *
 * Purpose: Calculates the CRC on the data past in, pData.
 *
 * Arguments: void *pData, uint8_t cnt
 *
 * Returns: uint16_t - CRC Result
 *
 * Side Effects: Time!
 *
 * Reentrant Code: No
 *
 * Notes:  This is blocking code.  The function will return after the CRC is calculated.
 * 
 **********************************************************************************************************************/
uint16_t crc16(volatile void *pData, uint8_t cnt) {

    uint8_t *data = (uint8_t *)pData;
    uint16_t crc = 0xFFFF;
    for (int i = 0; i < cnt; i++) 
    {
        crc ^= (uint16_t)data[i] << 8;
        for (int j = 0; j < 8; j++) 
        {

            if (crc & 0x8000) 
            {
                crc = (crc << 1) ^ POLY;
            } 
            else 
            {
                crc <<= 1;
            }
        }
    }
    return crc;
}


/* ****************************************************************************************************************** */
// </editor-fold>

/* ****************************************************************************************************************** */
/* Local Functions */

/* ****************************************************************************************************************** */
/* Event Handlers */

/* ****************************************************************************************************************** */
/* Unit Test Code */


