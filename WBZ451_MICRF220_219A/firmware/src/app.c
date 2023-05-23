// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include "app.h"
#include "configuration.h"
#include "definitions.h"
#include "app_ble.h"
#include "ble_dis/ble_dis.h"
#include "app_ble_conn_handler.h"
#include "app_ble_sensor.h"
#include "app_adv.h"
#include "system/console/sys_console.h"
#include "ble_otaps/ble_otaps.h"
#include "app_ota/app_ota_handler.h"
#include "sensors/inc/rgb_led.h"
#include "MICRF220_219A/receiver.h"
#include "MICRF220_219A/dvr_micrf220_219a.h"
#include "MICRF220_219A/dvr_adc.h"
#include <stdio.h>

rxDataPacket_t rxPacket;                        // Populated by RX_process() if data is ready.
engData_t      engData;                         // Contains engineering data from RX_getEngData() module.
uint32_t       txCnt;
char result[4];

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
#define BLE_SENSOR_VERSION  "1.0.0.0"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

SYS_CONSOLE_HANDLE touchDevConsoleHandle;
SYS_CONSOLE_HANDLE uartConsoleHandle;

uint8_t slider_table[9] = {0,0,36,73,109,146,182,219,255};

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

static inline void ble_send_notification(const uint8_t nfy)
{
    if ( APP_GetBleState() == APP_BLE_STATE_CONNECTED)
    {
        APP_TRPS_SendNotification(APP_TRP_VENDOR_OPCODE_BLE_SENSOR,nfy);
    }
    else
    {
        APP_ADV_Init();
    }
}

void APP_RGB_Handler(uint32_t val)
{
    APP_TRPS_SensorData_T *sensorData;
    sensorData =  APP_TRPS_Get_SensorData();
      
    uint8_t red, green, blue;
    uint8_t red_value = result[0] - '0';
    uint8_t green_value = result[1] - '0';
    uint8_t blue_value = result[2] - '0';
    uint8_t onOff_value = result[3] - '0';
    
    red = slider_table[red_value];
    green = slider_table[green_value];
    blue = slider_table[blue_value];
    RGB_LED_ConvertRGB2HSV(red, green, blue, &sensorData->RGB_color.Hue, &sensorData->RGB_color.Saturation, &sensorData->RGB_color.Value);
    RGB_LED_SetLedColorHSV(sensorData->RGB_color.Hue,sensorData->RGB_color.Saturation,sensorData->RGB_color.Value);                
    uint8_t onOff_button_read = onOff_value;
    if(onOff_button_read ==  0x01)      //off command
    {
        if(sensorData->rgbOnOffStatus == LED_ON)
        {
            RGB_LED_Off();
            sensorData->rgbOnOffStatus = LED_OFF;
            ble_send_notification(RGB_ONOFF_STATUS_NFY);
            SYS_CONSOLE_MESSAGE("LED OFF \n\r");
            SYS_CONSOLE_MESSAGE("\n\r");
        }
    }
    else
    {
        if(sensorData->rgbOnOffStatus == LED_OFF)
        {
            RGB_LED_SetLedColorHSV(sensorData->RGB_color.Hue,sensorData->RGB_color.Saturation,sensorData->RGB_color.Value);
            sensorData->rgbOnOffStatus = LED_ON;
            ble_send_notification(RGB_ONOFF_STATUS_NFY);
            SYS_CONSOLE_MESSAGE("LED ON \n\r");
            SYS_CONSOLE_MESSAGE("\n\r");
        }
    }
    if( (onOff_button_read > 1) && (onOff_button_read < 5))
    {                            
        ble_send_notification(RGB_COLOR_NFY);
        SYS_CONSOLE_MESSAGE("COLOR SET\n\r");
    }
}

static void APP_Init(void)
{
   
    APP_BleStackInit();

    /* Add BLE Service */
    BLE_DIS_Add();

    APP_UpdateLocalName(0, NULL);
    APP_InitConnList();
    APP_ADV_Init();
    
    SYS_CONSOLE_MESSAGE("BLE Sensor Application: Version ");
    SYS_CONSOLE_PRINT(BLE_SENSOR_VERSION);
    SYS_CONSOLE_MESSAGE("\n\r[BLE} Advertisement Started\n\r");    

    APP_TRPS_Sensor_Init();    
    APP_OTA_HDL_Init();
    
    SYS_CONSOLE_MESSAGE("\n\r MICRF 220/219A \n\r");
    DVR_ADC_init();
    RX_init();
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;


    appData.appQueue = xQueueCreate( 64, sizeof(APP_Msg_T) );
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    APP_Msg_T    appMsg[1];
    APP_Msg_T   *p_appMsg;
    p_appMsg=appMsg;
    
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;
            //appData.appQueue = xQueueCreate( APP_QUEUE_LENGTH, sizeof(APP_Msg_T) );

            APP_Init();
            RTC_Timer32Start();
            touchDevConsoleHandle = SYS_CONSOLE_HandleGet(SYS_CONSOLE_INDEX_1);
            uartConsoleHandle = SYS_CONSOLE_HandleGet(SYS_CONSOLE_INDEX_0);
            
            if (appInitialized)
            {
                APP_Msg_T appMsg;
                appMsg.msgId = APP_MSG_MICRF_ADC_EVT;
                OSAL_QUEUE_Send(&appData.appQueue, &appMsg, 0);
                appMsg.msgId = APP_MSG_MICRF_DATA_EVT;
                OSAL_QUEUE_Send(&appData.appQueue, &appMsg, 0);
                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            if (OSAL_QUEUE_Receive(&appData.appQueue, &appMsg, OSAL_WAIT_FOREVER))
            {
                if(p_appMsg->msgId==APP_MSG_BLE_STACK_EVT)
                {
                    // Pass BLE Stack Event Message to User Application for handling
                    APP_BleStackEvtHandler((STACK_Event_T *)p_appMsg->msgData);
                }
                else if(p_appMsg->msgId== APP_TIMER_ADV_CTRL_MSG)
                {
                    APP_BLE_Adv_TimerHandler();
                }
                else if(p_appMsg->msgId== APP_TIMER_BLE_SENSOR_MSG)
                {
                    APP_TRPS_Sensor_TimerHandler();
                }
                else if(p_appMsg->msgId== APP_MSG_TRS_BLE_SENSOR_INT)
                {
                    APP_TRPS_Sensor_Button_Handler();
                }               
                else if(p_appMsg->msgId == APP_TIMER_OTA_TIMEOUT_MSG)
                {
                    APP_OTA_Timeout_Handler(); 
                }
                else if(p_appMsg->msgId== APP_TIMER_OTA_REBOOT_MSG)
                {
                    APP_OTA_Reboot_Handler(); 
                }
                else if(p_appMsg->msgId== APP_TOUCH_USART_READ_MSG)
                {                    
                    APP_RGB_Handler(txCnt);                    
                }
                else if(p_appMsg->msgId== APP_MSG_MICRF_ADC_EVT)
                {                    
                    DVR_ADC_enable();
                    DVR_ADC_processConversion();                // Process ADC data   
                    
                    APP_Msg_T appMsg;
                    appMsg.msgId = APP_MSG_MICRF_ADC_EVT;
                    OSAL_QUEUE_Send(&appData.appQueue, &appMsg, 0); 
                }
                else if( p_appMsg->msgId == APP_MSG_MICRF_DATA_EVT)
                {
                    APP_Msg_T appMsg;           
                    if (RX_process(&rxPacket))                  // Check if there is an RF packet received
                    {
                        (void)memcpy(&txCnt, &rxPacket.data[0], sizeof(txCnt));  
                        sprintf(result, "%ld", txCnt);
                        SYS_CONSOLE_MESSAGE("\n\r");
                        SYS_CONSOLE_PRINT("Received Data: %ld\n\r",txCnt); // Display the data received
                            
                        #if MICRF_ENABLE_RSSI == 1
                        SYS_CONSOLE_PRINT("Message RSSI/Noise RSSI: %d/%d\n\r",rxPacket.msgRssi, rxPacket.noiseRssi); // Display the RSSI values
                        #endif

                        #if RX_ENG_DATA_ON == 1                    
                        RX_getEngData(&engData);      // Get the engineering data
                        SYS_CONSOLE_PRINT("Valid Pkt:%ld,Cnt Fail:%d,CRC Fail:%d,Protocol Fail:%d,Buf:%d\n\r",engData.validPackets,engData.cntFailure,engData.crcFailures,engData.protocolFailures,engData.bufferOverflow);// Display only the number of packets received
                        #endif

                        appMsg.msgId = APP_TOUCH_USART_READ_MSG;
                        OSAL_QUEUE_Send(&appData.appQueue, &appMsg, 0);
                    }
                    appMsg.msgId = APP_MSG_MICRF_DATA_EVT;
                    OSAL_QUEUE_Send(&appData.appQueue, &appMsg, 0);                  
                }
            }
            break;
        }

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
