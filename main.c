#include <mcs51reg.h>
#include <string.h>

static char *str = "12345";

void delay() {
  TMOD = 0x01; // Timer0 mode1
  TH0 = 0xFC;  // initial value for 1ms
  TL0 = 0x66;
  TR0 = 1; // timer start
  while (TF0 == 0)
    ;      // check overflow condition
  TR0 = 0; // Stop Timer
  TF0 = 0; // Clear flag
}

void transmit(char byte) {
  SBUF = byte; /* Load char in SBUF register */
  while (TI == 0)
    ;     /* Wait until stop bit transmit */
  TI = 0; /* Clear TI flag */
}

void main(void) {

  TMOD = 0x20; /* Timer 1, 8-bit auto reload mode */
  TH1 = 0xFD;  /* Load value for 9600 baud rate */
  SCON = 0x50; /* Mode 1, reception enable */
  TR1 = 1;     /* Start timer 1 */

  P2 = 0xFF;

  while (1) {

    for (int i = 0; i < strlen(str); i++) {
      transmit(str[i]);
      delay();
    }

    P2 = ~P2;
  }
}
