# Detailed Design Document

| **Author**              | Youssef Alaa |
|:------------------------|:--------------|
| **Status**              | Final |
| **Version**             | 2.0 |
| **Date**                | 19/10/2025 |

---

## Introduction

This document presents the **LED & Pushbutton Embedded Test System**, developed on **Arduino UNO** using a layered embedded architecture.  
It demonstrates modular interaction between the LED, pushbutton, LCD, and UART modules for system testing via serial communication.

### Purpose
- Implement a **layered embedded architecture** (MCAL, HAL, and APP).  
- Enable **UART-based control and feedback** for testing automation.  
- Demonstrate **LCD visual response** and **LED control** based on UART commands and button presses.  

### Scope
- **MCAL:** Direct hardware register control (GPIO, UART, Timer).  
- **HAL:** Abstract hardware via driver APIs (LED, LCD, Button).  
- **APP:** Logic and event handling (commands, button interaction).

---

## System Architecture

### Layered Design Overview

```plantuml
@startuml
rectangle "Test System" #orange {
  
    rectangle "Application" {
        rectangle "Main" 
        rectangle "Button Handling"
        rectangle "Command Processing"
    }

    rectangle "MCU" #green {
        rectangle "LED"
        rectangle "LCD"
    }

    rectangle "MCAL" #skyblue {
        rectangle "GPIO"
        rectangle "UART"
        rectangle "Timer"
    }
    
    Application -[hidden]-> MCU
    MCU -[hidden]-> MCAL
}
@enduml

| **Layer**       | **Description**                                                 |
| --------------- | --------------------------------------------------------------- |
| **Application** | Manages logic, command parsing, and system flow.                |
| **HAL**         | Abstracts hardware modules like LED, LCD, and Button.           |
| **MCAL**        | Provides low-level access to hardware registers and interfaces. |

System Flowchart 
@startuml
skinparam backgroundColor #FAFAFA
skinparam activity {
    StartColor #6C63FF
    EndColor #6C63FF
    DiamondBackgroundColor #FCE38A
    DiamondBorderColor #F08A5D
    ArrowColor #40514E
    BarColor #E27D60
}

(*) --> "System Init"

--> "Wait for Event"

if "UART Command Received?" then
  -->[yes] "Read UART Command"
  if "Command = ON?" then
    -->[yes] "Turn LED ON"
    --> "LCD displays 1"
    --> "Serial prints ON"
    --> "Wait for Event"
  else
    if "Command = OFF?" then
      -->[yes] "Turn LED OFF"
      --> "LCD displays 2"
      --> "Serial prints OFF"
      --> "Wait for Event"
    else
      -->[no] "Invalid Command"
      --> "LCD displays INVALID"
      --> "Serial prints INVALID"
      --> "Wait for Event"
    endif
  endif
else
  -->[no] "Check Button State"
  if "Button Pressed?" then
    -->[yes] "LCD displays 3"
    --> "Serial prints BUTTON PRESSED"
    --> "Wait for Event"
  else
    -->[no] "Button Released"
    --> "LCD displays 4"
    --> "Serial prints BUTTON RELEASED"
    --> "Wait for Event"
  endif
endif
@enduml


Function Call Hierarchy
1. System Initialization
@startuml
skinparam sequence {
    ArrowColor #007ACC
    ActorBorderColor #333
    ParticipantBorderColor #007ACC
    LifeLineBorderColor #333
    LifeLineBackgroundColor #C6E2FF
}

participant "main()" as Main
participant "System_Init()" as SysInit
participant "LCD_Init()" as LCD
participant "LED_Init()" as LED
participant "Button_Init()" as Button
participant "UART_Init()" as UART

Main -> SysInit : call
SysInit -> LCD : init
SysInit -> LED : init
SysInit -> Button : init
SysInit -> UART : init
@enduml

2.UART Command Processing 

@startuml
skinparam sequence {
    ArrowColor #5D8AA8
    LifeLineBackgroundColor #EAF2F8
    ParticipantBackgroundColor #AED6F1
}

participant "UART_Receive_Command()" as UARTRecv
participant "Process_Command()" as Process
participant "LED_On()" as LEDOn
participant "LED_Off()" as LEDOff
participant "UART_Send_Response()" as UARTSend

UARTRecv -> Process : call
Process -> LEDOn : if command == "on"
Process -> LEDOff : if command == "off"
Process -> UARTSend : send response
@enduml

3. Button Handling Sequence

@startuml
skinparam sequence {
    ArrowColor #148F77
    LifeLineBackgroundColor #D5F5E3
    ParticipantBackgroundColor #ABEBC6
}

participant "Button_Read()" as ButtonRead
participant "Process_Button()" as ProcessBtn
participant "LCD_Display()" as LCDDisp
participant "UART_Send()" as UARTSend

ButtonRead -> ProcessBtn : call
ProcessBtn -> LCDDisp : display "3" if pressed / "4" if released
ProcessBtn -> UARTSend : print state to serial monitor
@enduml


Project file Struccture 

@startuml
skinparam package {
    BackgroundColor #DDEEFF
    BorderColor #3333CC
}
skinparam component {
    BackgroundColor<<header>> #FFDD99
    BackgroundColor<<source>> #CCFFCC
}

package "Project" {
    [main.c] <<source>> #A9CCE3
    [led.h] <<header>> #F9E79F
    [push_button.h] <<header>> #F9E79F
    [lcd.h] <<header>> #F9E79F
    [uart.h] <<header>> #F9E79F

    [led.c] <<source>> #A9DFBF
    [push_button.c] <<source>> #A9DFBF
    [lcd.c] <<source>> #A9DFBF
    [uart.c] <<source>> #A9DFBF

    [main.c] --> [led.h]
    [main.c] --> [push_button.h]
    [main.c] --> [lcd.h]
    [main.c] --> [uart.h]

    [led.c] --> [gpio.h] 
    [push_button.c] --> [gpio.h]
    [lcd.c] --> [gpio.h]
    [uart.c] --> [gpio.h]
}
@enduml

**Module Summary**
| **Function**             | **Description**                                 |
| ------------------------ | ----------------------------------------------- |
| `System_Init()`          | Initializes LCD, LED, Button, and UART modules. |
| `LED_On()` / `LED_Off()` | Controls LED state.                             |
| `Button_Read()`          | Reads pushbutton input.                         |
| `UART_Receive_Command()` | Receives command via serial monitor.            |
| `UART_Send_Response()`   | Sends messages back to serial monitor.          |
| `LCD_Display()`          | Displays numeric status on the LCD.             |


**Hardware Configuration**
| **Name**            | **Value Range / Default** | **Description**                   |
| ------------------- | ------------------------- | --------------------------------- |
| `LED_PIN`           | PB0                       | Pin connected to LED output       |
| `BUTTON_PIN`        | PB1                       | Pin connected to Pushbutton input |
| `LCD_PORT`          | PORTD                     | Port used by LCD data lines       |
| `BAUD_RATE`         | 9600                      | UART communication speed (bps)    |
| `LCD_ADDR`          | 0x27                      | I2C address of the LCD            |
| `CMD_DELAY_MS`      | 200–300 ms                | Delay between UART commands       |
| `DEBOUNCE_DELAY_MS` | 50 ms                     | Button debounce delay             |
| `SYS_CLK_FREQ`      | 16 MHz                    | Arduino UNO clock frequency       |



Test Cases (LCD & UART Validation)

| **Test Case ID** | **Description**      | **Input / Action**                   | **Expected LCD Output**         | **Expected Serial Output**         | **LED State** | **Status** |
| ---------------- | -------------------- | ------------------------------------ | ------------------------------- | ---------------------------------- | ------------- | ---------- |
| **TC1**          | LED Turn ON          | Type `"ON"` in Serial Monitor        | `1`                             | `LED ON`                           | ON            | ✅ Pass     |
| **TC2**          | LED Turn OFF         | Type `"OFF"` in Serial Monitor       | `2`                             | `LED OFF`                          | OFF           | ✅ Pass     |
| **TC3**          | Invalid Command      | Type any invalid text (`abc`, `xyz`) | `INVALID`                       | `Invalid Command`                  | Unchanged     | ✅ Pass     |
| **TC4**          | Button Pressed       | Press pushbutton                     | `3`                             | `BUTTON PRESSED`                   | Toggles       | ✅ Pass     |
| **TC5**          | Button Released      | Release pushbutton                   | `4`                             | `BUTTON RELEASED`                  | No Change     | ✅ Pass     |
| **TC6**          | Rapid Button Presses | Press multiple times quickly         | No lag; cycles `3`/`4` smoothly | Serial logs match real-time events | Stable        | ✅ Pass     |

### Assumptions & Constraints
- System operates on a 5V Arduino UNO board.
- Serial Monitor baud rate fixed at 9600 bps.
- Button uses pull-down resistor for stable input.
- LCD connected via I2C at address 0x27.
- Limited to single LED and button configuration.
