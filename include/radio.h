#ifndef RADIO_H
#define RADIO_H

#define RADIO_BASE_ADDR 0x40001000

typedef struct
{
    RW_reg  TASKS_TXEN;         // 0x000 Enable radio in TX mode
    RW_reg  TASKS_RXEN;         // 0x004 Enable radio in RX mode
    RW_reg  TASKS_START;        // 0x008 Start radio
    RW_reg  TASKS_STOP;         // 0x00C Stop radio
    RW_reg  TASKS_DISABLE;      // 0x010 Disable radio
    RW_reg  TASKS_RSSISTART;    // 0x014 Start the RSSI and take one sample of the receive signal strength
    RW_reg  TASKS_RSSISTOP;     // 0x018 Stop the RSSI measurement
    RW_reg  TASKS_BCSTART;      // 0x01C Start the bit counter
    RW_reg  TASKS_BCSTOP;       // 0x020 Stop the bit counter
    RO_reg  RESERVED_A[0x37];
    RO_reg  EVENTS_READY;       // 0x100 Radio has ramped up and is ready to be started
    RO_reg  EVENTS_ADDRESS;     // 0x104 Address sent or received
    RO_reg  EVENTS_PAYLOAD;     // 0x108 Packet payload sent or received
    RO_reg  EVENTS_END;         // 0x10C Packet sent or received
    RO_reg  EVENTS_DISABLED;    // 0x110 Radio has been disabled
    RO_reg  EVENTS_DEVMATCH;    // 0x114 A device address match occurred on the last received packet
    RO_reg  EVENTS_DEVMISS;     // 0x118 No device address match occurred on the last received packet
    RO_reg  EVENTS_RSSIEND;     // 0x11C Sampling of receive signal strength complete
    RO_reg  RESERVED_B[2];
    RO_reg  EVENTS_BCMATCH;     // 0x128 Bit counter reached bit count value
    RO_reg  EVENTS_CRCOK;       // 0x130 Packet received with CRC OK
    RO_reg  EVENTS_CRCERROR;    // 0x134 Packet received with CRC error
    RO_reg  RESERVED_C[0x32];
    
} tRadio_regMap;

#endif // RADIO_H
