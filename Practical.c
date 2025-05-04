#include <xc.h>
#include <PIC18F4550.h> 
#include <stdlib.h>
#pragma config WDT = OFF // making watchdog timer off
#pragma config LVP = OFF // making low voltage programming off
#define LCD_DATA PORTD 
#define ctrl PORTE 
#define rs PORTEbits.RE0 
#define rw PORTEbits.RE1 
#define en PORTEbits.RE2 
void init_LCD(void); 
void LCD_command(unsigned char cmd); 
void LCD_data(unsigned char data); 
void LCD_write_string(char *str); 
void msdelay (unsigned int time); 
void main(void) 
{ 
char var1[] = "Welcome"; 
char var2[] = "SE-IT"; 
ADCON1 = 0x0F; // all the analog pins (AN0 to AN3) are disabled and set to digital I/O (Digital Mode).
               // These bits configure the Vref+ and Vref- sources for the A/D converter.
TRISD = 0x00; 
TRISE = 0x00; 
init_LCD(); 
msdelay(50); 

LCD_write_string(var1); 
msdelay(150); 
LCD_command(0xC0); 
LCD_write_string(var2); 
while (1); 
} 
void msdelay (unsigned int time) 
{ 
unsigned int i, j; 
for (i = 0; i < time; i++) 
for (j = 0; j < 710; j++); 
} 
void init_LCD(void) 
{ 
LCD_command(0x38); // 2 lines and 5X7 Matrix
msdelay(15); 
LCD_command(0x01); // Clear display screen
msdelay(15); 
LCD_command(0x0C); // Display on cursor off
msdelay(15); 
LCD_command(0x80); // Force cursor to begin of first line
msdelay(15); 
} 
void LCD_command(unsigned char cmd) 
{ 
LCD_DATA = cmd; 
rs = 0; 
rw = 0; 
en = 1; 
msdelay(15); 
en = 0; 
} 
void LCD_data(unsigned char data) 
{ 
LCD_DATA = data; 
rs = 1; 
rw = 0; 
en = 1; 
msdelay(15); 
en = 0; 
} 
void LCD_write_string( char *str) 
{ 
int i = 0; 
while (str[i] != '\0') 
{ 
LCD_data(str[i]); 
msdelay(15); 
i++; 
} 
}
