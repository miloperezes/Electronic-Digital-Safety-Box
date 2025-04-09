# Electronic Digital Safety Box with Keypad and LCD Display

## Project Overview

This project involves creating an electronic digital safety box using the PIC16F877A microcontroller. The system incorporates a 4x4 keypad for password input, an LCD to display messages, and a buzzer for audio feedback. The project demonstrates an embedded systems application by combining hardware and software to create a user-friendly safety box.

The microcontroller is programmed in MikroC to validate the entered passcode and control outputs such as LEDs, a DC motor for locking/unlocking the box, and a buzzer for wrong passcode attempts. The passcode is stored in EEPROM and can be changed through the system interface.

## Key Features

- **Password Protection**: Users input a passcode using the keypad. The system will unlock the safety box when the correct passcode is entered.
- **Visual and Audible Feedback**: The LCD displays status messages, and the buzzer sounds when an incorrect code is entered.
- **User-Settable Passcode**: Users can set a new passcode when the safe is closed.
- **Security Locking Mechanism**: A DC motor is used to simulate a lock that opens when the correct passcode is entered.

## Components

- **Microcontroller**: PIC16F877A or any PIC18 series
- **Keypad**: 4x4 matrix keypad
- **Display**: LCD (16x2)
- **Motor**: DC motor (used for locking/unlocking)
- **Buzzer**: Provides audio feedback
- **LEDs**: Optional, for visual output
- **Relay**: Optional, for relay control
- **Relay Driver**: ULN2003 (for relay control)

## Circuit Diagram

The circuit schematic can be found in the [Proteus](#) project files.

## Software

The program is written in MikroC and uses the following key functionalities:
- Keypad input for passcode entry.
- LCD output to show status messages.
- EEPROM for storing the passcode.
- DC motor control for unlocking the safety box.
- Buzzer feedback for incorrect passcodes.

### MikroC Code Snippets

#### Keypad Input

```c
kp = Keypad_Key_Click(); // Captures key press
EEPROM_Write(0x00, code1[0]);  // Write to EEPROM address 0
PORTA.B0 = 1;  // Activate DC motor for unlocking
PORTA.B2 = 1;  // Activate buzzer
```

Instructions
Setup:

Connect the PIC16F877A microcontroller to the components as per the circuit diagram.

Upload the MikroC code to the microcontroller using a programmer (e.g., PICkit 3).

Operation:

Power on the system.

Enter the passcode on the keypad.

The LCD will display either "Access Granted" or "Access Denied."

If the correct code is entered, the motor will unlock the safety box, and the buzzer will beep.

If the incorrect code is entered, the buzzer will sound, and the system will lock after 3 failed attempts.
