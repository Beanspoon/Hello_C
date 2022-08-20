#ifndef RADIO_H
#define RADIO_H

#define RADIO_BASE_ADDR 0x40001000

typedef struct
{
    RW_reg  TASKS_TXEN;     // 0x000 Enable radio in TX mode
    RW_reg  TASKS_RXEN;     // 0x004 Enable 
} tRadio_regMap;

#endif // RADIO_H