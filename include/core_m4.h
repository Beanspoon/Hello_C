#ifndef CORE_M4_H
#define CORE_M4_H

#include "types.h"

/************************************************
 * NVIC
 * *********************************************/

typedef struct
{
    void *pStack;   // Stack pointer

    // Exception handlers
    void *pfReset_handler;
    void *pfNMI_handler;
    void *pfHardfault_handler;
    void *pfMemMgmtFault_handler;
    void *pfBusFault_handler;
    void *pfUsageFault_handler;
    void *RESERVED_A[4];
    void *pfSVCall_handler;
    void *RESERVED_B[2];
    void *pfPendSV_handler;
    void *pfSystick_handler;
} tVectorTable;


#endif // CORE_M4_H