# Carte Nucleo 103
## Overview and Layout
### The top 
![layout](./layout.png)
### The bottom 
![layout](./layout_bottom.png)
### PINS 
- **View :** 


![pins](./pins.png)


- **Table :**


![tab](./tab.png)
### Specifications
- **CN2 :** 

![layout](./CN2_.png)

---

- **CN4 :**(Serial Wire Debug)

![CN4](./CN4.png)


---

- **LEDS:** 

  - **LED1 (LD1; COM):**  
    The tricolor LED (green, orange, red) LD1 (COM) provides information about ST-LINK
    communication status. LD1 default color is red. LD1 turns to green to indicate that
    communication is in progress between the PC and the ST-LINK/V2-1, with the following setup:

      - Slow blinking Red/Off: at power-on before USB initialization
      - Fast blinking Red/Off: after the first correct communication between the PC and ST-LINK/V2-1 (enumeration)
      - Red LED On: when the initialization between the PC and ST-LINK/V2-1 is complete
      - Green LED On: after a successful target communication initialization
      - Blinking Red/Green: during communication with target
      - Green On: communication finished and successful
      - Orange On: communication failure

  - **User LD2:**  
    The green LED is a user LED connected to Arduino signal D13 corresponding to MCU I/O `PA5` (pin 21).

      - If the I/O is HIGH, the LED is on
      - If the I/O is LOW, the LED is off

  - **LD3 PWR:**  
    The red LED indicates that the MCU part is powered and +5V power is available.

- **Push buttons:**

  - **B1 USER:**  
    The user button is connected to the I/O `PC13` (pin 2) of the STM32 microcontroller.

  - **B2 RESET:**  
    This push button is connected to NRST and is used to reset the STM32 microcontroller.

**NOTE:**  
The blue and black plastic hats that are placed on the push buttons can be removed if necessary, for example when a shield or when an application board is plugged on top of the Nucleo board. This will avoid pressure on the buttons and consequently a possible permanent target MCU reset.


---

- **OSC Clock Supply**

There are four ways to configure the pins corresponding to the external high-speed clock (HSE):

1. **MCO from ST-LINK:**  
   MCO output of ST-LINK MCU is used as the input clock. This frequency cannot be changed; it is fixed at 8 MHz and connected to `PF0`/`PD0`/`PH0-OSC_IN` of the STM32 microcontroller.

   The following configuration is needed:
   - SB55 OFF and SB54 ON
   - SB16 and SB50 ON
   - R35 and R37 removed

2. **HSE oscillator on-board from X3 crystal (not provided):**  
   For typical frequencies, capacitors, and resistors, refer to the STM32 microcontroller datasheet. Also, refer to the AN2867 Application note for oscillator design guide for STM32 microcontrollers. The X3 crystal has the following characteristics: 8 MHz, 16 pF, 20 ppm, and DIP footprint. It is recommended to use 95L8000016AFXHFO manufactured by Hong Kong X'tals Limited.

   The following configuration is needed:
   - SB54 and SB55 OFF
   - R35 and R37 soldered
   - C33 and C34 soldered with 20 pF capacitors
   - SB16 and SB50 OFF

3. **Oscillator from external `PF0`/`PD0`/`PH0`:**  
   From an external oscillator through pin 29 of the CN7 connector.

   The following configuration is needed:
   - SB55 ON
   - SB50 OFF
   - R35 and R37 removed

4. **HSE not used:**  
   `PF0`/`PD0`/`PH0` and `PF1`/`PD1`/`PH1` are used as GPIO instead of a clock.

   The following configuration is needed:
   - SB54 and SB55 ON
   - SB16 and SB50 (MCO) OFF
   - R35 and R37 removed



There are two possible default configurations of the HSE pins, depending on the version of the Nucleo board hardware.

- The board version **MB1136 C-01** or **MB1136 C-02** is mentioned on the sticker placed on the bottom side of the PCB.
  
  - **MB1136 C-01:** This version is configured as HSE not used.
  - **MB1136 C-02 (or higher):** This version is configured to use ST-LINK MCO as the clock input.

---

- **LOSC 32 KHz clock supply:**

  There are three ways to configure the pins corresponding to the low-speed clock (LSE):

  - **On-board oscillator:**  
    X2 crystal. Refer to the Oscillator design guide for STUBS, STMBA, and STM32 microcontrollers application note (AN2867) for oscillator design guide for STM32 microcontrollers. It is recommended to use ABS25-32.768KHZ-6-T, manufactured by Abracon Corporation.

  - **Oscillator from external `PC14`:**  
    From an external oscillator through pin 25 of the CN7 connector.

    The following configuration is needed:
    - SB48 and SB49 ON
    - R34 and R36 removed

  - **LSE not used:**  
    `PC14` and `PC15` are used as GPIOs instead of a low-speed clock.

    The following configuration is needed:
    - SB48 and SB49 ON
    - R34 and R36 removed



There are three possible default configurations of the LSE depending on the version of the Nucleo board hardware:

- The board version **MB1136 C-01** or **MB1136 C-02** is mentioned on the sticker placed on the bottom side of the PCB.

  - **MB1136 C-01:** This version is configured as LSE not used.
  - **MB1136 C-02 (or higher):** This version is configured with an on-board 32 KHz oscillator.
  - **MB1136 C-03 (or higher):** This version uses the new LSE crystal (ABS25) with G26, C31, and C32 value updates.

---

- **USART communication:**

  The USART2 interface available on `PA2` and `PA3` of the STM32 microcontroller can be connected to ST-LINK MCU, ST morpho connector, or to the Arduino connector. The configuration can be changed by setting the related solder bridges.

  - By default, the USART2 communication between the target MCU and ST-LINK MCU is enabled, in order to support Virtual Com Port for mbed.
    
    - SB13 and SB14 ON
    - SB62 and SB63 OFF

  - If the communication between the target MCU `PA2` (D1) or `PA3` (D0) and a shield or extension board is required:
    
    - SB62 and SB63 should be ON
    - SB13 and SB14 should be OFF

  - In such a case, it is possible to connect another USART to ST-LINK MCU using flying wires between the ST morpho connector and CN3. For instance, on the NUCLEO-F103RB, it is possible to use USART3 available on `PC10` (TX) and `PC11` (RX).

    Two flying wires need to be connected as follows:
    
    - `PC10` (USART3_TX) available on CN7 pin 1 to CN3 pin RX
    - `PC11` (USART3_RX) available on CN7 pin 2 to CN3 pin TX

## STM32F103RB 
### GPIO
  - **Configuration:**

![Configuration](./configuration_Pin.png)

  - **Output Mode:** 

  ![Output](./Output.png)




