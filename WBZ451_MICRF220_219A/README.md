# PIC32CXBZ2_WBZ45x_Sub-GHz_MICRF220/219A

<img src="docs/IoT-Made-Easy-Logo.png" width=100>


> "IoT Made Easy!" 

Devices: **| PIC32CXBZ2 | WBZ45x |**<br>
Features: **| BLE SENSOR | MICRF220-433-EV | MICRF219A-433-EV |**


## ⚠ Disclaimer

<p><span style="color:red"><b>
THE SOFTWARE ARE PROVIDED "AS IS" AND GIVE A PATH FOR SELF-SUPPORT AND SELF-MAINTENANCE. This repository contains example code intended to help accelerate client product development. </br>

For additional Microchip repos, see: <a href="https://github.com/Microchip-MPLAB-Harmony" target="_blank">https://github.com/Microchip-MPLAB-Harmony</a>

Checkout the <a href="https://microchipsupport.force.com/s/" target="_blank">Technical support portal</a> to access our knowledge base, community forums or submit support ticket requests.
</span></p></b>

## Contents

1. [Introduction](#step1)
1. [Bill of materials](#step2)
1. [Hardware Setup](#step3)
1. [Software Setup](#step4)
1. [Harmony MCC Configuration](#step5)
1. [Board Programming](#step6)
1. [Run the demo](#step7)

## 1. Introduction<a name="step1">

This application demonstrates the use of an MICRF220/219A as receiver using ASK Modulation interfaced with the WBZ451 Curiosity Board to control the RGB LED of the WBZ451 Curiosity board with the data received from the MICRF112.

![](docs/Picture1.png)

## 2. Bill of materials<a name="step2">

| TOOLS | QUANTITY |
| :- | :- |
| [PIC32CX-BZ2 and WBZ451 Curiosity Development Board](https://www.microchip.com/en-us/development-tool/EV96B94A) | 1 |
| [MICRF220-433 EVALBOARD](https://www.microchip.com/en-us/development-tool/MICRF220-433-EV) | 1 |

## 3. Hardware Setup<a name="step3">

- Connect the MICRF220-433 EVALBOARD with the WBZ451 CURIOSITY BOARD using the below table.

| MICRF220/219A | WBZ451		   | Description |
| :- | :- | :- |
| VDD     |    3.3V       |     VDD     |
| GND     | 	 GND 	   |     GND     |
| DO     |  PWM		   |     Data Out|
| SCLK     |  NC          |   SCLK    |
| SHDN    |       NC     |     Shutdown     |
| RSSI     |    AN        |    RSSI Noise      |

![](docs/micrf_1.png)

![](docs/micrf_2.png)

## 4. Software Setup<a name="step4">

- [MPLAB X IDE ](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide#tabs)

    - Version: 6.05
	- XC32 Compiler v4.10
	- MPLAB® Code Configurator v5.1.17
	- PIC32CX-BZ_DFP v1.0.107
	- MCC Harmony
	  - csp version: v3.13.1
	  - core version: v3.11.1
	  - CMSIS-FreeRTOS: v10.4.6
	  - wireless_pic32cxbz_wbz: v1.0.0
	  - wireless_ble: v1.0.0	  
	  - dev_packs: v3.13.1
	  - wolfssl version: v4.7.0
	  - crypto version: v3.7.6
	    

- [Microchip Bluetooth Data (MBD) iOS/Android app](https://play.google.com/store/apps/details?id=com.microchip.bluetooth.data&hl=en_IN&gl=US)

- [MPLAB X IPE v6.05](https://microchipdeveloper.com/ipe:installation)

## 5. Harmony MCC Configuration<a name="step5">

### Getting started with MICRF220/219A with WBZ451 CURIOSITY BOARD.

| Tip | New users of MPLAB Code Configurator are recommended to go through the [overview](https://onlinedocs.microchip.com/pr/GUID-1F7007B8-9A46-4D03-AEED-650357BA760D-en-US-6/index.html?GUID-AFAB9227-B10C-4FAE-9785-98474664B50A) |
| :- | :- |

**Step 1** - Connect the WBZ451 CURIOSITY BOARD to the device/system using a micro-USB cable.

**Step 2** - This application is built by using [WBZ45x BLE Sensor with ATTINY3217 Touch Demo](https://github.com/MicrochipTech/PIC32CXBZ2_WBZ45x_BLE_SENSOR_Touch_ATtiny3217) as the building block. The project graph of the WBZ45x BLE Sensor with ATTINY3217 Touch Demo application is shown below.

![](docs/Ble_sensor_project_graph.png)

**Step 3** - In MCC harmony project graph add the TC0 from device resources->peripherals->TC and configure as shown below.

![](docs/tc0.png)

- The TC0 Timer is configured for a time period of 100 microseconds to sample the received data from the transmitter.

**Step 4** - In MCC harmony project graph select the ADCHS and configure as shown below.

![](docs/adchs_pg.png)

**Step 5** - In MCC harmony project graph select the Pin Configurations from plugins and configure as shown below.

![](docs/pin.png)

**Step 6** - The project graph after making the configurations is shown below.

![](docs/pg.png)

**Step 7** - [Generate the code](https://onlinedocs.microchip.com/pr/GUID-A5330D3A-9F51-4A26-B71D-8503A493DF9C-en-US-1/index.html?GUID-9C28F407-4879-4174-9963-2CF34161398E).

| Note: Download or clone the application to do the following steps !! |
| --- |

**Step 8** - From the unzipped folder copy the folder MICRF220_219A from WBZ451_MICRF112_114 to the folder firmware/src under your MPLAB Harmony v3 application project and add the Header (dvr_crc.h, dvr_micrf112.h, transmitter.h) and Source file (dvr_crc.c, dvr_micrf112.c, transmitter.c).

- In the project explorer, Right click on folder Header Files and add a sub folder MICRF220_219A by selecting “Add Existing Items from Folders…”

![](docs/header_add.png)

- Click on “Add Folder…” button.

![](docs/header_add2.png)

- Select the “MICRF220_219A” folder and select “Files of Types” as Header Files.

![](docs/header_add3.png)

- Click on “Add” button to add the selected folder.

![](docs/header_add4.png)
 
- The MICRF220_219A header files gets added to your project.

![](docs/header_add5.png)

- In the project explorer, Right click on folder Source Files and add a sub folder MICRF220_219A by selecting “Add Existing Items from Folders…”.

![](docs/source_add.png)

- Click on “Add Folder…” button

![](docs/source_add2.png)

- Select the “MICRF220_219A” folder and select “Files of Types” as Source Files.

![](docs/source_add3.png)

- Click on “Add” button to add the selected folder

![](docs/source_add4.png)

- The MICRF220_219A source files gets added to your project.

![](docs/source_add5.png)

**Step 9** - In your MPLAB Harmony v3 based application go to "firmware\src" and replace the app.h and app.c files from the link given below.

- [app.h](https://github.com/MicrochipTech/PIC32CXBZ2_WBZ45x_Sub-GHz_MICRF112_114_MICRF220_219A_BLE_SENSOR/blob/main/WBZ451_MICRF220_219A/firmware/src/app.h)

- [app.c](https://github.com/MicrochipTech/PIC32CXBZ2_WBZ45x_Sub-GHz_MICRF112_114_MICRF220_219A_BLE_SENSOR/blob/main/WBZ451_MICRF220_219A/firmware/src/app.c)

**Step 10** - In your MPLAB Harmony v3 based application go to "firmware\src\app_ble\app_ble.c" and do the following changes.

- Add the folllowing line.

```
#include "../default/driver/device_support/include/info_block.h"
```

![](docs/app_ble1.png)

- Edit/Replace the folllowing line.

```
#define GAP_DEV_NAME_VALUE          "BLE_MICRF_219A"
```

![](docs/app_ble.png)

- Edit/Replace the folllowing code.

```
BLE_GAP_Addr_T devAddr;
if (!IB_GetBdAddr(&devAddr.addr[0]) )
{
devAddr.addrType = BLE_GAP_ADDR_TYPE_PUBLIC;
devAddr.addr[0] = 0x9A;
devAddr.addr[1] = 0x21;
devAddr.addr[2] = 0x78;
devAddr.addr[3] = 0xA6;
devAddr.addr[4] = 0xB7;
devAddr.addr[5] = 0xC8;

// Configure device address
BLE_GAP_SetDeviceAddr(&devAddr);
}
```

![](docs/id.png)

**Step 11** - To Know about the implimentation of ADC to RSSI conversion go to "firmware\src\MICRF220_219A\dvr_micrf220_219a.c" in your MPLAB Harmony v3 based application.

- [dvr_micrf220_219a.c](https://github.com/MicrochipTech/PIC32CXBZ2_WBZ45x_Sub-GHz_MICRF112_114_MICRF220_219A_BLE_SENSOR/blob/main/WBZ451_MICRF220_219A/firmware/src/MICRF220_219A/dvr_micrf220_219a.c)

The RSSI values can be viewed in the COM PORT.

![](docs/rssi.png)

**Step 12** - Clean and build the project. To run the project, select "Make and program device" button.

## 6. Board Programming<a name="step6">

## Programming hex file:

### Program the precompiled hex file using MPLAB X IPE

- The Precompiled hex file is given in the hex folder.
Follow the steps provided in the link to [program the precompiled hex file](https://microchipdeveloper.com/ipe:programming-device) using MPLABX IPE to program the pre-compiled hex image. 


### Build and program the application using MPLAB X IDE

The application folder can be found by navigating to the following path: 

- "WBZ451_MICRF220_219A/firmware/WBZ451_MICRF220_219A.X"

Follow the steps provided in the link to [Build and program the application](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_pic32cxbz2_wbz45/tree/master/apps/ble/advanced_applications/ble_sensor#build-and-program-the-application-guid-3d55fb8a-5995-439d-bcd6-deae7e8e78ad-section).

## 7. Run the demo<a name="step7">

- After programming the board, the expected application behavior is shown in the below [video](https://github.com/MicrochipTech/PIC32CXBZ2_WBZ45x_Sub-GHz_MICRF112_114_MICRF220_219A_BLE_SENSOR/blob/main/WBZ451_MICRF220_219A/docs/micrf_working.gif).

![Alt Text](docs/micrf_working.gif)




