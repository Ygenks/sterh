#include <mcs51reg.h>

char *str = "12345";

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

  while (1) {

    for (int i = 0; i < sizeof(str); i++) {
      transmit(str[i]);
    }
  }
}
