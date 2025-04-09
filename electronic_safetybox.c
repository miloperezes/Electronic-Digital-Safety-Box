#include <built_in.h>

#define LCD_RS PORTA.F0
#define LCD_EN PORTA.F1
#define LCD_D4 PORTA.F2
#define LCD_D5 PORTA.F3
#define LCD_D6 PORTA.F4
#define LCD_D7 PORTA.F5

#define FP_BAUDRATE 9600
#define FP_UART_TX RC6_bit
#define FP_UART_RX RC7_bit

// relay and seatbelt switch connections
#define RELAY PORTB.F0
#define SEATBELT_SWITCH PORTD.F1

void LCD_Init();
void LCD_Cmd(char cmd);
void LCD_Chr(char row, char col, char out_char);
void LCD_Out(char row, char col, char *text);
void FP_SendCommand(char *command, int length);
void FP_ReceiveResponse(char *response, int length);
int FP_EnrollFinger();
int FP_VerifyFinger();
void StartEngine();


void main() {
    TRISA = 0x00; // Set PORTA as output for LCD
    TRISB = 0x00; // Set PORTB as output for relay
    TRISC = 0x80; // Set RC6 (TX) and RC7 (RX) for UART
    TRISD = 0xF2; // Set PORTD as input for seatbelt switch and buttons RD4-RD7
    UART1_Init(FP_BAUDRATE); // UART for fingerprint scanner
    LCD_Init();
    ADCON1 = 0x06; // Set PORTA and PORTE as digital I/O

    while (1) {
        LCD_Out(1, 1, "Select option:");
        LCD_Out(2, 1, "1: Enroll  2: Verify");

        // Placeholder for button press simulation
        char option = '1'; 
        if (PORTD.F4) option = '1'; // If RD4 is pressed
        if (PORTD.F5) option = '2'; // If RD5 is pressed

        if (option == '1') {
            if (FP_EnrollFinger()) {
                LCD_Out(1, 1, "Enrollment Success");
            } else {
                LCD_Out(1, 1, "Enrollment Failed");
            }
        } else if (option == '2') {
            if (FP_VerifyFinger()) {
                LCD_Out(1, 1, "Finger Verified");
                LCD_Out(2, 1, "Buckle Seatbelt!");

                // Wait for seatbelt switch to be pressed
                while (!SEATBELT_SWITCH);

                StartEngine();
            } else {
                LCD_Out(1, 1, "Finger Not Found");
            }
        }

        Delay_ms(2000); 
        LCD_Cmd(0x01); 
    }
}

void LCD_Init() {
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
}

void FP_SendCommand(char *command, int length) {
    int i;
    for (i = 0; i < length; i++) {
        UART1_Write(command[i]);
    }
}

void FP_ReceiveResponse(char *response, int length) {
    int i;
    for (i = 0; i < length; i++) {
        response[i] = UART1_Read();
    }
}

// Enroll fingerprint
int FP_EnrollFinger() {
    char command[] = {0x55, 0xAA, 0x01, 0x00, 0x03, 0x01, 0x00, 0x05}; // Example command
    char response[12];

    FP_SendCommand(command, sizeof(command));
    FP_ReceiveResponse(response, sizeof(response));

    return (response[6] == 0x00); // Return success if response is OK
}

// Verify fingerprint
int FP_VerifyFinger() {
    char command[] = {0x55, 0xAA, 0x01, 0x00, 0x03, 0x02, 0x00, 0x06}; // Example command
    char response[12];

    FP_SendCommand(command, sizeof(command));
    FP_ReceiveResponse(response, sizeof(response));

    return (response[6] == 0x00); 
}

// Start the engine (DC motor)
void StartEngine() {
    RELAY = 1; 
    LCD_Out(1, 1, "Engine Started");
    Delay_ms(5000); 
    RELAY = 0; // Deactivate relay to stop motor
    LCD_Out(1, 1, "Engine Stopped");
}
