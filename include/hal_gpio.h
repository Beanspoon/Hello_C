#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include "types.h"

#define GPIO_BASE_ADDR  0x50000000

typedef enum
{
    GPIO_DIR_INPUT,
    GPIO_DIR_OUTPUT
} tGpio_dir;

typedef enum
{
    GPIO_INBUF_CONNECT,
    GPIO_INBUF_DISCONNECT
} tGpio_inBuf;

typedef enum
{
    GPIO_PULL_DISABLED,
    GPIO_PULL_DOWN,
    GPIO_PULL_UP
} tGpio_pull;

typedef enum
{
    GPIO_DRIVE_S0S1,    // Standard '0', standard '1'
    GPIO_DRIVE_H0S1,    // High drive '0', standard '1'
    GPIO_DRIVE_S0H1,    // Standard '0', high drive '1'
    GPIO_DRIVE_H0H1,    // High drive '0', high drive '1'
    GPIO_DRIVE_D0S1,    // Disconnect '0', standard '1' (wired-or)
    GPIO_DRIVE_D0H1,    // Disconnect '0', high drive '1' (wired-or)
    GPIO_DRIVE_S0D1,    // Standard '0', disconnect '1' (wired-and)
    GPIO_DRIVE_H0D1,    // High drive '0', disconnect '1' (wired-and) 
} tGpio_drive;

typedef enum
{
    
}

typedef struct
{
    tGpio_pinDir    PINCNF_DIR      : 1;    // Bit[0]   Pin direction
    tGpio_inBuf     PINCNF_INPUT    : 1;    // Bit[1]   Connect or disconnect input buffer
    tGpio_pull      PINCNF_PULL     : 2;    // Bit[2-3] Pin pull configuration
    const uint8_t                   : 0;
    tGpio_drive     PINCNF_DRIVE    : 3;    // Bit[8-10]    Drive configuration

} tGpio_pinCnfReg;

typedef struct
{
    RO_reg  RESERVED_A[0x141];
    RW_reg  GPIO_OUT;           // 0x504 Write GPIO port
    RW_reg  GPIO_OUTSET;        // 0x508 Set individual bits in GPIO port
    RW_reg  GPIO_OUTCLR;        // 0x50C Clear individual bits in GPIO port
    RO_reg  GPIO_IN;            // 0x510 Read GPIO port
    RW_reg  GPIO_DIR;           // 0x514 Direction of GPIO pins
    RW_reg  GPIO_DIRSET;        // 0x518 Direction set register (sets pin to output)
    RW_reg  GPIO_DIRCLR;        // 0x51C Direction clear register (sets pin to input)
    RW_reg  GPIO_LATCH;         // 0x520 Latch register indicating which GPIO pins have met criteria set in PIN_CNF[n].SENSE. Write '1' to clear
    RW_reg  GPIO_DETECTMODE;    // 0x524 Select between default DETECT signal behaviour (0) and LDETECT mode (1)
    RW_reg
} tGpio_regMap;

#define GPIO    (*((volatile tGpio_regMap *) GPIO_BASE_ADDR))

#endif // HAL_GPIO_H