# PIC32CXBZ2_WBZ45x_Sub-GHz_MICRF112-114_MICRF220-219A

<img src="docs/IoT-Made-Easy-Logo.png" width=100>


> "IOT Made Easy!" 

Devices: **| PIC32CXBZ2 | WBZ45x |**<br>
Features: **| BLE | E-PAPER |**


## ⚠ Disclaimer

<p><span style="color:red"><b>
THE SOFTWARE ARE PROVIDED "AS IS" AND GIVE A PATH FOR SELF-SUPPORT AND SELF-MAINTENANCE. This repository contains example code intended to help accelerate client product development. </br>

For additional Microchip repos, see: <a href="https://github.com/Microchip-MPLAB-Harmony" target="_blank">https://github.com/Microchip-MPLAB-Harmony</a>

Checkout the <a href="https://microchipsupport.force.com/s/" target="_blank">Technical support portal</a> to access our knowledge base, community forums or submit support ticket requests.
</span></p></b>

## Contents

1. [Introduction](#step1)
1. [Contents](#step2)

## 1. Introduction<a name="step1">

This application demonstrates the use of an MICRF112/114 as transmitter and MICRF220/219A as receiver using ASK MODULATION with WBZ451 Curiosity Board.

![](docs/Picture1.png)

In this Demo the [BLE Sensor application](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_pic32cxbz2_wbz45/tree/master/apps/ble/advanced_applications/ble_sensor) is implemented on both transmitter part and receiver part to control the RGB LED. The RGB values are received from the [(MBD App)](https://play.google.com/store/apps/details?id=com.microchip.bluetooth.data&hl=en_IN&gl=US) using BLE Sensor application and then it is transmitted through MICRF112/114. The MICRF220/219A receives the RGB values and updates the RGB LED using [BLE Sensor application](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_pic32cxbz2_wbz45/tree/master/apps/ble/advanced_applications/ble_sensor).

![Alt Text](docs/micrf_working.gif)

The above video shows the working of MICRF112(433MHz) and MICRF219A(433MHz).

## 2. Contents<a name="step2">

1. [WBZ451_MICRF112_114](https://github.com/MicrochipTech/PIC32CXBZ2_WBZ45x_Sub-GHz_MICRF112_114_MICRF220_219A_BLE_SENSOR/tree/main/WBZ451_MICRF112_114)

2. [WBZ451_MICRF220_219A](https://github.com/MicrochipTech/PIC32CXBZ2_WBZ45x_Sub-GHz_MICRF112_114_MICRF220_219A_BLE_SENSOR/tree/main/WBZ451_MICRF220_219A)

