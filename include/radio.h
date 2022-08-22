#ifndef RADIO_H
#define RADIO_H

#include "types.h"

#define RADIO_BASE_ADDR 0x40001000

typedef struct
{
    RW_reg  READY_START         : 1; // Bit[0] Shortcut between READY event and START task
    RW_reg  END_DISABLE         : 1; // Bit[1] Shortcut between END event and DISABLE task
    RW_reg  DISABLED_TXEN       : 1; // Bit[2] Shortcut between DISABLED event and TXEN task
    RW_reg  DISABLED_RXEN       : 1; // Bit[3] Shortcut between DISABLED event and RXEN task
    RW_reg  ADDRESS_RSSISTART   : 1; // Bit[4] Shortcut between ADDRESS event and RSSISTART task
    RW_reg  END_START           : 1; // Bit[5] Shortcut between END event and START task
    RW_reg  ADDRESS_BCSTART     : 1; // Bit[6] Shortcut between ADDRESS event and BCSTART task
    const uint8_t               : 0;
    RW_reg  DISABLED_RSSISTOP   : 1; // Bit[8] Shortcut between DISABLED event and RSSISTOP task
    RO_reg                      : 0;
} tRadio_shortsReg;

typdef struct
{
    RW_reg  READY               : 1; // Bit[0] Write '1' to set/clear READY event interrupt
    RW_reg  ADDRESS             : 1; // Bit[1] Write '1' to set/clear ADDRESS event interrupt
    RW_reg  PAYLOAD             : 1; // Bit[2] Write '1' to set/clear PAYLOAD event interrupt
    RW_reg  END                 : 1; // Bit[3] Write '1' to set/clear END event interrupt
    RW_reg  DISABLED            : 1; // Bit[4] Write '1' to set/clear DISABLED event interrupt
    RW_reg  DEVMATCH            : 1; // Bit[5] Write '1' to set/clear DEVMATCH event interrupt
    RW_reg  DEVMISS             : 1; // Bit[6] Write '1' to set/clear DEVMISS event interrupt
    RW_reg  RSSIEND             : 1; // Bit[7] Write '1' to set/clear RSSIEND event interrupt
    RO_reg                      : 2;
    RW_reg  BCMATCH             : 1; // Bit[10] Write '1' to set/clear BCMATCH event interrupt
    RO_reg                      : 1;
    RW_reg  CRCOK               : 1; // Bit[12] Write '1' to set/clear CRCOK event interrupt
    RW_reg  CRCERROR            : 1; // Bit[13] Write '1' to set/clear CRCERROR event interrupt
    RO_reg                      : 0;
} tRadio_intEnReg;

typedef struct
{
    RW_reg  FREQUENCY           : 7; // Bit[0-6] Radio channel frequency (2400 + FREQUENCY) MHz [0-100]
    const uint8_t               : 0;
    RW_reg  MAP                 : 1; // Bit[8] Base frequency 0: 2360 MHz, 1: 2400 MHz
    RO_reg                      : 0;
} tRadio_frequencyReg;

typedef struct
{
    RW_reg              TASKS_TXEN;         // 0x000 Enable radio in TX mode
    RW_reg              TASKS_RXEN;         // 0x004 Enable radio in RX mode
    RW_reg              TASKS_START;        // 0x008 Start radio
    RW_reg              TASKS_STOP;         // 0x00C Stop radio
    RW_reg              TASKS_DISABLE;      // 0x010 Disable radio
    RW_reg              TASKS_RSSISTART;    // 0x014 Start the RSSI and take one sample of the receive signal strength
    RW_reg              TASKS_RSSISTOP;     // 0x018 Stop the RSSI measurement
    RW_reg              TASKS_BCSTART;      // 0x01C Start the bit counter
    RW_reg              TASKS_BCSTOP;       // 0x020 Stop the bit counter
    RO_reg              RESERVED_A[0x37];
    RO_reg              EVENTS_READY;       // 0x100 Radio has ramped up and is ready to be started
    RO_reg              EVENTS_ADDRESS;     // 0x104 Address sent or received
    RO_reg              EVENTS_PAYLOAD;     // 0x108 Packet payload sent or received
    RO_reg              EVENTS_END;         // 0x10C Packet sent or received
    RO_reg              EVENTS_DISABLED;    // 0x110 Radio has been disabled
    RO_reg              EVENTS_DEVMATCH;    // 0x114 A device address match occurred on the last received packet
    RO_reg              EVENTS_DEVMISS;     // 0x118 No device address match occurred on the last received packet
    RO_reg              EVENTS_RSSIEND;     // 0x11C Sampling of receive signal strength complete
    RO_reg              RESERVED_B[2];
    RO_reg              EVENTS_BCMATCH;     // 0x128 Bit counter reached bit count value
    RO_reg              EVENTS_CRCOK;       // 0x130 Packet received with CRC OK
    RO_reg              EVENTS_CRCERROR;    // 0x134 Packet received with CRC error
    RO_reg              RESERVED_C[0x32];
    tRadio_shortsReg    SHORTS;             // 0x200 Shortcuts register
    RO_reg              RESERVED_D[0x40];
    tRadio_intEnReg     INTENSET;           // 0x304 Interrupt enable register
    tRadio_intEnReg     INTENCLR;           // 0x308 Interrupt clear register
    RO_reg              RESERVED_E[0x3D];
    RO_reg              CRCSTATUS;          // 0x400 CRC status register
    RO_reg              RESERVED_F;
    RO_reg              RXMATCH;            // 0x408 Received address logical match register
    RO_reg              RXCRC;              // 0x40C CRC field of previously received packet
    RO_reg              DAI;                // 0x410 Device address match index
    RO_reg              RESERVED_G[0x3C];
    RW_reg              PACKETPTR;          // 0x504 RAM address of memory in which packet is stored
    tRadio_frequencyReg FREQUNECY;          // 0x508 Frequency setting register
} tRadio_regMap;

#endif // RADIO_H