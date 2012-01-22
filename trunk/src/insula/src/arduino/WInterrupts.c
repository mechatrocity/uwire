#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "WConstants.h"
#include "wiring_private.h"

volatile static voidFuncPtr intFunc[EXTERNAL_NUM_INTERRUPTS];
// volatile static voidFuncPtr twiIntFunc;

#if defined(__AVR_ATmega8__)
#define EICRA MCUCR
#define EIMSK GICR
#endif

void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode) {
  if(interruptNum < EXTERNAL_NUM_INTERRUPTS) {
    intFunc[interruptNum] = userFunc;

    // Configure the interrupt mode (trigger on low input, any change, rising
    // edge, or falling edge).  The mode constants were chosen to correspond
    // to the configuration bits in the hardware register, so we simply shift
    // the mode into place.

    // Enable the interrupt.

    switch (interruptNum)
    {
		case 0:
		  EICRB = (EICRB & ~((1 << ISC40) | (1 << ISC41))) | (mode << ISC40);
		  EIMSK |= (1 << INT4);
		  break;
		case 1:
		  EICRB = (EICRB & ~((1 << ISC50) | (1 << ISC51))) | (mode << ISC50);
		  EIMSK |= (1 << INT5);
		  break;
		case 2:
		  EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
		  EIMSK |= (1 << INT0);
		  break;
		case 3:
		  EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
		  EIMSK |= (1 << INT1);
		  break;
		case 4:
		  EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
		  EIMSK |= (1 << INT2);
		  break;
		case 5:
		  EICRA = (EICRA & ~((1 << ISC30) | (1 << ISC31))) | (mode << ISC30);
		  EIMSK |= (1 << INT3);
		  break;
		case 6:
		  EICRB = (EICRB & ~((1 << ISC60) | (1 << ISC61))) | (mode << ISC60);
		  EIMSK |= (1 << INT6);
		  break;
		case 7:
		  EICRB = (EICRB & ~((1 << ISC70) | (1 << ISC71))) | (mode << ISC70);
		  EIMSK |= (1 << INT7);
		  break;
    }
  }
}

void detachInterrupt(uint8_t interruptNum) {
  if(interruptNum < EXTERNAL_NUM_INTERRUPTS) {
    // Disable the interrupt.  (We can't assume that interruptNum is equal
    // to the number of the EIMSK bit to clear, as this isn't true on the
    // ATmega8.  There, INT0 is 6 and INT1 is 7.)
    switch (interruptNum) {
    case 2:
      EIMSK &= ~(1 << INT0);
      break;
    case 3:
      EIMSK &= ~(1 << INT1);
      break;
    case 4:
      EIMSK &= ~(1 << INT2);
      break;
    case 5:
      EIMSK &= ~(1 << INT3);
      break;
    case 0:
      EIMSK &= ~(1 << INT4);
      break;
    case 1:
      EIMSK &= ~(1 << INT5);
      break;
    case 6:
      EIMSK &= ~(1 << INT6);
      break;
    case 7:
      EIMSK &= ~(1 << INT7);
      break;
    }

    intFunc[interruptNum] = 0;
  }
}

SIGNAL(INT0_vect) {
  if(intFunc[EXTERNAL_INT_2])
    intFunc[EXTERNAL_INT_2]();
}

SIGNAL(INT1_vect) {
  if(intFunc[EXTERNAL_INT_3])
    intFunc[EXTERNAL_INT_3]();
}

SIGNAL(INT2_vect) {
  if(intFunc[EXTERNAL_INT_4])
    intFunc[EXTERNAL_INT_4]();
}

SIGNAL(INT3_vect) {
  if(intFunc[EXTERNAL_INT_5])
    intFunc[EXTERNAL_INT_5]();
}

SIGNAL(INT4_vect) {
  if(intFunc[EXTERNAL_INT_0])
    intFunc[EXTERNAL_INT_0]();
}

SIGNAL(INT5_vect) {
  if(intFunc[EXTERNAL_INT_1])
    intFunc[EXTERNAL_INT_1]();
}

SIGNAL(INT6_vect) {
  if(intFunc[EXTERNAL_INT_6])
    intFunc[EXTERNAL_INT_6]();
}

SIGNAL(INT7_vect) {
  if(intFunc[EXTERNAL_INT_7])
    intFunc[EXTERNAL_INT_7]();
}