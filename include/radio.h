#ifndef RADIO_H
#define RADIO_H

#include "types.h"

#define RADIO_BASE_ADDR 0x40001000

typedef struct
{
    tBitState   READY_START         : 1; // Bit[0] Shortcut between READY event and START task
    tBitState   END_DISABLE         : 1; // Bit[1] Shortcut between END event and DISABLE task
    tBitState   DISABLED_TXEN       : 1; // Bit[2] Shortcut between DISABLED event and TXEN task
    tBitState   DISABLED_RXEN       : 1; // Bit[3] Shortcut between DISABLED event and RXEN task
    tBitState   ADDRESS_RSSISTART   : 1; // Bit[4] Shortcut between ADDRESS event and RSSISTART task
    tBitState   END_START           : 1; // Bit[5] Shortcut between END event and START task
    tBitState   ADDRESS_BCSTART     : 1; // Bit[6] Shortcut between ADDRESS event and BCSTART task
    const uint8_t                   : 0;
    tBitState   DISABLED_RSSISTOP   : 1; // Bit[8] Shortcut between DISABLED event and RSSISTOP task
    RO_reg                          : 0;
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
    // PCNF0
    RW_reg      LFLEN               : 4; // Bit[0-3] Length on air of LENGTH field in bits
    const uint8_t                   : 0;
    RW_reg      S0LEN               : 1; // Bit[8] Length on air of S0 field in bytes
    const uint16_t                  : 0;
    RW_reg      S1LEN               : 4; // Bit[16-19] Length on air of S1 field in bits
    RW_reg      S1INCL              : 1; // Bit[20] 0: Include S1 in RAM if S1LEN > 0, 1: Always include
    const uint8_t                   : 0;
    RW_reg      PLEN                : 1; // Bit[24] Length of preamble on air 0: 8bit, 1: 16bit
    RO_reg                          : 0;
    //PCNF1
    RW_reg      MAXLEN              : 8; // Bit[0-7] Maximum length in bytes of packet payload. Larger payloads will be truncated
    RW_reg      STATLEN             : 8; // Bit[8-15] Static length in bytes. This is added to payload length
    RW_reg      BALEN               : 3; // Bit[16-18] Base address length in bytes
    const uint8_t                   : 0;
    RW_reg      ENDIAN              : 1; // Bit[24] On-air endianness of packet (S0, LENGTH, S1 & PAYLOAD). 0: Little, 1: Big
    tBitState   WHITEEN             : 1; // Bit[25] 0: disable, or 1: enable packet whitening
    RO_reg                          : 0;
} tRadio_pCnfRegs;

typedef struct
{
    // PREFIX0
    RW_reg  AP0                 : 8; // Bit[0-7] Address prefix 0
    RW_reg  AP1                 : 8; // Bit[8-15] Address prefix 1
    RW_reg  AP2                 : 8; // Bit[16-24] Address prefix 2
    RW_reg  AP3                 : 8; // Bit[25-31] Address prefix 3
    // PREFIX1
    RW_reg  AP4                 : 8; // Bit[0-7] Address prefix 4
    RW_reg  AP5                 : 8; // Bit[8-15] Address prefix 5
    RW_reg  AP6                 : 8; // Bit[16-24] Address prefix 6
    RW_reg  AP7                 : 8; // Bit[25-31] Address prefix 7
} tRadio_prefixRegs;

typedef struct
{
    tBitState   ADDR0               : 1; // Bit[0] 0: disable, or 1: enable reception on logical address 0
    tBitState   ADDR1               : 1; // Bit[1] 0: disable, or 1: enable reception on logical address 1
    tBitState   ADDR2               : 1; // Bit[2] 0: disable, or 1: enable reception on logical address 2
    tBitState   ADDR3               : 1; // Bit[3] 0: disable, or 1: enable reception on logical address 3
    tBitState   ADDR4               : 1; // Bit[4] 0: disable, or 1: enable reception on logical address 4
    tBitState   ADDR5               : 1; // Bit[5] 0: disable, or 1: enable reception on logical address 5
    tBitState   ADDR6               : 1; // Bit[6] 0: disable, or 1: enable reception on logical address 6
    tBitState   ADDR7               : 1; // Bit[7] 0: disable, or 1: enable reception on logical address 7
    RO_reg                          : 0;
} tRadio_rxAddressReg;

typedef struct
{
    RW_reg  LEN                 : 3; // Bit[0-2] CRC length in number of bytes
    const uint8_t;
    RW_reg  SKIPADDR            : 1; // Bit[8] 0: include, or 1: skip address field in CRC calculation
    RO_reg                      : 0;
} tRadio_crcCnf;

typedef enum
{
    RADIO_POWER_POS4DBM   = 0x04,
    RADIO_POWER_POS3DBM   = 0x03,
    RADIO_POWER_0DBM      = 0x00,
    RADIO_POWER_NEG4DBM   = 0xFC,
    RADIO_POWER_NEG8DBM   = 0xF8,
    RADIO_POWER_NEG12DBM  = 0xF4,
    RADIO_POWER_NEG16DBM  = 0xF0,
    RADIO_POWER_NEG20DBM  = 0xEC,
    RADIO_POWER_NEG40DBM  = 0xD8
} tRadio_txPower;

typedef enum
{
    RADIO_MODE_NRF1MBIT,
    RADIO_MODE_NRF2MBIT,
    RADIO_MODE_BLE1MBIT = 3,
    RADIO_MODE_BLE2MBIT,
} tRadio_mode;

typedef enum
{
    RADIO_LOGADDR0,
    RADIO_LOGADDR1,
    RADIO_LOGADDR2,
    RADIO_LOGADDR3,
    RADIO_LOGADDR4,
    RADIO_LOGADDR5,
    RADIO_LOGADDR6,
    RADIO_LOGADDR7
} tRadio_logAddr;

typedef enum
{
    RADIO_DISABLED,
    RADIO_RXRU,
    RADIO_RXIDLE,
    RADIO_RX,
    RADIO_RXDISABLE,
    RADIO_TXRU      = 9,
    RADIO_TXIDLE,
    RADIO_TX,
    RADIO_TXDISABLE,
} tRadio_state;

typedef struct
{
    tBitState   ENA0    : 1;    // Bit[0] 0: disable, or 1: enable device address matching using address 0
    tBitState   ENA1    : 1;    // Bit[1] 0: disable, or 1: enable device address matching using address 1
    tBitState   ENA2    : 1;    // Bit[2] 0: disable, or 1: enable device address matching using address 2
    tBitState   ENA3    : 1;    // Bit[3] 0: disable, or 1: enable device address matching using address 3
    tBitState   ENA4    : 1;    // Bit[4] 0: disable, or 1: enable device address matching using address 4
    tBitState   ENA5    : 1;    // Bit[5] 0: disable, or 1: enable device address matching using address 5
    tBitState   ENA6    : 1;    // Bit[6] 0: disable, or 1: enable device address matching using address 6
    tBitState   ENA7    : 1;    // Bit[7] 0: disable, or 1: enable device address matching using address 7
    tBitState   TXADD0  : 1;    // Bit[8] Txadd for device address 0
    tBitState   TXADD1  : 1;    // Bit[9] Txadd for device address 1
    tBitState   TXADD2  : 1;    // Bit[10] Txadd for device address 2
    tBitState   TXADD3  : 1;    // Bit[11] Txadd for device address 3
    RW_reg  TXADD4  : 1;    // Bit[12] Txadd for device address 4
    RW_reg  TXADD5  : 1;    // Bit[13] Txadd for device address 5
    RW_reg  TXADD6  : 1;    // Bit[14] Txadd for device address 6
    RW_reg  TXADD7  : 1;    // Bit[15] Txadd for device address 7
    RO_reg          : 0;
} tRadio_daCnfReg;

typedef enum
{
    B1,         // Transmit '1'
    B0,         // Transmit '0'
    CENTER,     // Transmit center frequency
} tRadio_dtx;

typedef struct
{
    RW_reg      RU      : 1;    // Bit[0] Radio ramp up time 0: Default, 1: Fast
    const uint8_t       : 0;
    tRadio_dtx  DTX     : 2;    // Bit[8-9] Default TX value - specifies what is transmitted when radio is up but not started
} tRadio_modeCnf0Reg;

typedef struct
{
    RW_reg                  TASKS_TXEN;         // 0x000 Enable radio in TX mode
    RW_reg                  TASKS_RXEN;         // 0x004 Enable radio in RX mode
    RW_reg                  TASKS_START;        // 0x008 Start radio
    RW_reg                  TASKS_STOP;         // 0x00C Stop radio
    RW_reg                  TASKS_DISABLE;      // 0x010 Disable radio
    RW_reg                  TASKS_RSSISTART;    // 0x014 Start the RSSI and take one sample of the receive signal strength
    RW_reg                  TASKS_RSSISTOP;     // 0x018 Stop the RSSI measurement
    RW_reg                  TASKS_BCSTART;      // 0x01C Start the bit counter
    RW_reg                  TASKS_BCSTOP;       // 0x020 Stop the bit counter
    RO_reg                  RESERVED_A[0x37];
    RO_reg                  EVENTS_READY;       // 0x100 Radio has ramped up and is ready to be started
    RO_reg                  EVENTS_ADDRESS;     // 0x104 Address sent or received
    RO_reg                  EVENTS_PAYLOAD;     // 0x108 Packet payload sent or received
    RO_reg                  EVENTS_END;         // 0x10C Packet sent or received
    RO_reg                  EVENTS_DISABLED;    // 0x110 Radio has been disabled
    RO_reg                  EVENTS_DEVMATCH;    // 0x114 A device address match occurred on the last received packet
    RO_reg                  EVENTS_DEVMISS;     // 0x118 No device address match occurred on the last received packet
    RO_reg                  EVENTS_RSSIEND;     // 0x11C Sampling of receive signal strength complete
    RO_reg                  RESERVED_B[2];
    RO_reg                  EVENTS_BCMATCH;     // 0x128 Bit counter reached bit count value
    RO_reg                  EVENTS_CRCOK;       // 0x130 Packet received with CRC OK
    RO_reg                  EVENTS_CRCERROR;    // 0x134 Packet received with CRC error
    RO_reg                  RESERVED_C[0x32];
    tRadio_shortsReg        SHORTS;             // 0x200 Shortcuts register
    RO_reg                  RESERVED_D[0x40];
    tRadio_intEnReg         INTENSET;           // 0x304 Interrupt enable register
    tRadio_intEnReg         INTENCLR;           // 0x308 Interrupt clear register
    RO_reg                  RESERVED_E[0x3D];
    RO_reg                  CRCSTATUS;          // 0x400 CRC status register
    RO_reg                  RESERVED_F;
    const tRadio_logAddr    RXMATCH;            // 0x408 Received address logical match register
    RO_reg                  RXCRC;              // 0x40C CRC field of previously received packet (24 bits)
    const tRadio_logAddr    DAI;                // 0x410 Device address match index
    RO_reg                  RESERVED_G[0x3C];
    RW_reg                  PACKETPTR;          // 0x504 RAM address of memory in which packet is stored
    tRadio_frequencyReg     FREQUNECY;          // 0x508 Frequency setting register
    tRadio_txPower          TXPOWER;            // 0x50C Transmission power register
    tRadio_mode             MODE;               // 0x510 Radio data rate and modulation
    tRadio_pCnfRegs         PCNF;               // 0x514-518 Packet configuration registers
    RW_reg                  BASE[2];            // 0x51C-520 Radio base address registers
    tRadio_prefixRegs       PREFIX;             // 0x524-528 Prefix bytes for logical addresses
    tRadio_logAddr          TXADDRESS;          // 0x52C Transmit logical address select
    tRadio_rxAddressReg     RXADDRESS;          // 0x530 Receive logical address select
    tRadio_crcCnf           CRCCNF;             // 0x534 CRC configuration register
    RW_reg                  CRCPOLY;            // 0x538 CRC polynomial register (24 bits)
    RW_reg                  CRCINIT;            // 0x53C Initial value for CRC (24 bits)
    RO_reg                  RESERVED_H;
    RW_reg                  TIFS;               // 0x544 Inter-frame spacing in us (8 bits)
    RO_reg                  RSSISAMPLE;         // 0x548 RSSI sample register (read as -A dbm, 7 bits)
    RO_reg                  RESERVED_I;
    const tRadio_state      STATE;              // 0x550 Current radio state
    RW_reg                  DATAWHITEIV;        // 0x554 Data whitening initial value register (7 bits)
    RO_reg                  RESERVED_J[2];
    RW_reg                  BCC;                // 0x560 Bit counter compare
    RO_reg                  RESERVED_K[0x27];
    RW_reg                  DAB[8];             // 0x600-61C Device address base segment registers
    RW_reg                  DAP[8];             // 0x620-63C Device address prefix segment registers
    tRadio_daCnfReg         DACNF;              // 0x640 Device address match configuration
    RO_reg                  RESERVED_L[3];
    tRadio_modeCnf0Reg      MODECNF0;           // 0x650 Radio mode configuration register 0
    RO_reg                  RESERVED_M[0x26A];
    RW_reg                  POWER;              // 0xFFC Peripheral power control. Registers will be reset if peripheral power is toggled
} tRadio_regMap;

#endif // RADIO_H
