#include "types.h"

#define GPIO_BASE_ADDR  0x50000000U

#define OUT_ADDR         (GPIO_BASE_ADDR + 0x504)
#define PIN17_CNF_ADDR      ( GPIO_BASE_ADDR + 0x744U )

typedef struct 
{
    RW_reg  PINCNF_DIR      : 1;    // Pin direction: input (0) or output (1)
    RW_reg  PINCNF_INPUT    : 1;    // Connect (0) or disconnect (1) input buffer
    RW_reg  PINCNF_PULL     : 2;    // No pull (0) / pull down (1) / pull up (3)
    RO_reg                  : 4;
    RW_reg  PINCNF_DRIVE    : 3;    // Drive config
    RO_reg                  : 0;
    RW_reg  PINCNF_SENSE    : 2;    // Disable (0) / High (2) / Low (3)
} tPincnf_reg;

#define OUT      (*((volatile RW_reg *) OUT_ADDR))
#define PIN17_CNF   (*((volatile tPincnf_reg *) PIN17_CNF_ADDR))

void main( void )
{
    PIN17_CNF.PINCNF_DIR = 1U;  // Output
    PIN17_CNF.PINCNF_INPUT = 1U;    // Disconnect
    PIN17_CNF.PINCNF_PULL = 0u; // No pull
    PIN17_CNF.PINCNF_DRIVE = 0u;    // Standard 0, standard 1
    PIN17_CNF.PINCNF_SENSE = 0u;    // Disable

    OUT = 0u;

    while(1) {}
}
