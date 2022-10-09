#include "radio.h"

#include "core_nvic.h"
#include "utils.h"

#include <stddef.h>

#define RADIO_BASE_ADDR 0x40001000

/**
 * @brief Radio tasks enum
 *
 */
typedef enum
{
    RADIO_TASKS_TXEN,         // Enable the radio in tx mode
    RADIO_TASKS_RXEN,         // Enable the radio in rx mode
    RADIO_TASKS_START,        // Start radio tx or rx
    RADIO_TASKS_STOP,         // Stop radio tx or rx
    RADIO_TASKS_DISABLE,      // Disable radio
    RADIO_TASKS_RSSISTART,    // Start RSSI measurement and take one sample
    RADIO_TASKS_RSSISTOP,     // Stop RSSI measurement
    RADIO_TASKS_BCSTART,      // Start the bit counter
    RADIO_TASKS_BCSTOP,       // Stop the bit counter
    RADIO_TASKS_MAX
} tRadio_tasks;

/**
 * @brief Definition of the interrupt enable registers
 *
 */
typedef struct
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

/**
 * @brief Definition of the frequency setting register
 *
 */
typedef struct
{
    RW_reg  FREQUENCY           : 7; // Bit[0-6] Radio channel frequency (2400 + FREQUENCY) MHz [0-100]
    const uint8_t               : 0;
    RW_reg  MAP                 : 1; // Bit[8] Base frequency 0: 2360 MHz, 1: 2400 MHz
    RO_reg                      : 0;
} tRadio_frequencyReg;

/**
 * @brief Definition of the packet config registers
 *
 */
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
    tEnableState   WHITEEN             : 1; // Bit[25] 0: disable, or 1: enable packet whitening
    RO_reg                          : 0;
} tRadio_pCnfRegs;

/**
 * @brief Definition of the CRC config register
 *
 */
typedef struct
{
    RW_reg  LEN                 : 3; // Bit[0-2] CRC length in number of bytes
    uint8_t                     : 0;
    RW_reg  SKIPADDR            : 1; // Bit[8] 0: include, or 1: skip address field in CRC calculation
    RW_reg                      : 0;
} tRadio_crcCnfReg;

/**
 * @brief Radio power enum
 *
 */
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

/**
 * @brief Radio state enum
 *
 */
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

/**
 * @brief Definition of the device address register
 *
 */
typedef struct
{
    tEnableState   ENA0    : 1;    // Bit[0] 0: disable, or 1: enable device address matching using address 0
    tEnableState   ENA1    : 1;    // Bit[1] 0: disable, or 1: enable device address matching using address 1
    tEnableState   ENA2    : 1;    // Bit[2] 0: disable, or 1: enable device address matching using address 2
    tEnableState   ENA3    : 1;    // Bit[3] 0: disable, or 1: enable device address matching using address 3
    tEnableState   ENA4    : 1;    // Bit[4] 0: disable, or 1: enable device address matching using address 4
    tEnableState   ENA5    : 1;    // Bit[5] 0: disable, or 1: enable device address matching using address 5
    tEnableState   ENA6    : 1;    // Bit[6] 0: disable, or 1: enable device address matching using address 6
    tEnableState   ENA7    : 1;    // Bit[7] 0: disable, or 1: enable device address matching using address 7
    tEnableState   TXADD0  : 1;    // Bit[8] Txadd for device address 0
    tEnableState   TXADD1  : 1;    // Bit[9] Txadd for device address 1
    tEnableState   TXADD2  : 1;    // Bit[10] Txadd for device address 2
    tEnableState   TXADD3  : 1;    // Bit[11] Txadd for device address 3
    tEnableState   TXADD4  : 1;    // Bit[12] Txadd for device address 4
    tEnableState   TXADD5  : 1;    // Bit[13] Txadd for device address 5
    tEnableState   TXADD6  : 1;    // Bit[14] Txadd for device address 6
    tEnableState   TXADD7  : 1;    // Bit[15] Txadd for device address 7
    RO_reg          : 0;
} tRadio_daCnfReg;

/**
 * @brief Radio default transmission frequency register
 *
 */
typedef enum
{
    B1,         // Transmit '1'
    B0,         // Transmit '0'
    CENTER,     // Transmit center frequency
} tRadio_dtx;

/**
 * @brief Radio mode config register
 *
 */
typedef struct
{
    RW_reg      RU      : 1;    // Bit[0] Radio ramp up time 0: Default, 1: Fast
    uint8_t             : 0;
    tRadio_dtx  DTX     : 2;    // Bit[8-9] Default TX value - specifies what is transmitted when radio is up but not started
} tRadio_modeCnf0Reg;

/**
 * @brief Radio register map
 *
 */
typedef struct
{
    RW_reg                  TASKS[RADIO_TASKS_MAX];     // 0x000-020 Tasks registers
    RO_reg                  RESERVED_A[0x37];
    RW_reg                  EVENTS[RADIO_EVENTS_MAX];   // 0x100-134 Events registers
    RO_reg                  RESERVED_B[0x32];
    RW_reg                  SHORTS;                     // 0x200 Shortcuts register
    RO_reg                  RESERVED_C[0x40];
    RW_reg                  INTENSET;                   // 0x304 Interrupt enable register
    RW_reg                  INTENCLR;                   // 0x308 Interrupt clear register
    RO_reg                  RESERVED_D[0x3D];
    RO_reg                  CRCSTATUS;                  // 0x400 CRC status register
    RO_reg                  RESERVED_E;
    RO_reg                  RXMATCH;                    // 0x408 Received address logical match register
    RO_reg                  RXCRC;                      // 0x40C CRC field of previously received packet (24 bits)
    RO_reg                  DAI;                        // 0x410 Device address match index
    RO_reg                  RESERVED_F[0x3C];
    RW_reg                  PACKETPTR;                  // 0x504 RAM address of memory in which packet is stored
    tRadio_frequencyReg     FREQUENCY;                  // 0x508 Frequency setting register
    RW_reg                  TXPOWER;                    // 0x50C Transmission power register
    RW_reg                  MODE;                       // 0x510 Radio data rate and modulation
    tRadio_pCnfRegs         PCNF;                       // 0x514-518 Packet configuration registers
    RW_reg                  BASE[2];                    // 0x51C-520 Radio base address registers
    RW_reg                  PREFIX[2];                  // 0x524-528 Prefix bytes for logical addresses
    RW_reg                  TXADDRESS;                  // 0x52C Transmit logical address select
    RW_reg                  RXADDRESSES;                // 0x530 Receive logical address select
    tRadio_crcCnfReg        CRCCNF;                     // 0x534 CRC configuration register
    RW_reg                  CRCPOLY;                    // 0x538 CRC polynomial register (24 bits)
    RW_reg                  CRCINIT;                    // 0x53C Initial value for CRC (24 bits)
    RO_reg                  RESERVED_G;
    RW_reg                  TIFS;                       // 0x544 Inter-frame spacing in us (8 bits)
    RO_reg                  RSSISAMPLE;                 // 0x548 RSSI sample register (read as -A dbm, 7 bits)
    RO_reg                  RESERVED_H;
    RO_reg                  STATE;                      // 0x550 Current radio state
    RW_reg                  DATAWHITEIV;                // 0x554 Data whitening initial value register (7 bits)
    RO_reg                  RESERVED_I[2];
    RW_reg                  BCC;                        // 0x560 Bit counter compare
    RO_reg                  RESERVED_J[0x27];
    RW_reg                  DAB[8];                     // 0x600-61C Device address base segment registers
    RW_reg                  DAP[8];                     // 0x620-63C Device address prefix segment registers
    tRadio_daCnfReg         DACNF;                      // 0x640 Device address match configuration
    RO_reg                  RESERVED_K[3];
    tRadio_modeCnf0Reg      MODECNF0;                   // 0x650 Radio mode configuration register 0
    RO_reg                  RESERVED_L[0x26A];
    RW_reg                  POWER;                      // 0xFFC Peripheral power control. Registers will be reset if peripheral power is toggled
} tRadio_regMap;

#define RADIO   (*((tRadio_regMap *)RADIO_BASE_ADDR))

typedef struct
{
    tRadio_eventHandler pfEventHandlers[RADIO_SHORTS_MAX];
} tRadio_context;

#define RADIO_LENGTH_FIELD_MAX_LENGTH_BITS  8u
#define RADIO_S0_FIELD_MAX_LENGTH_BYTES     1u
#define RADIO_S1_FIELD_MAX_LENGTH_BITS      8u

#define RADIO_PREFIXES_PER_REGISTER         4u

/**
 * @brief Get the Context object
 *
 * @return tRadio_context* pointer to the context object
 */
static tRadio_context *getContext( void )
{
    static tRadio_context radio_context = { 0 };
    return &radio_context;
}

typedef enum { RADIO_NONE } tRadio_regFieldEnum;

typedef union
{
    tRadio_shorts           shortcut;
    tRadio_events           event;
    tRadio_regFieldEnum     field;
} tRadio_regFieldEnumUnion;

 /**
  * @brief Generate register bit pattern for a given array of register field enums
  *
  * @param array array of field enums
  * @param arrayLen length of the array
  * @return Register bit pattern
  */
static RW_reg regFieldArrayToReg( const tRadio_regFieldEnumUnion array[], const uint8_t arrayLen )
{
    const tRadio_regFieldEnum *abstractedArray = (tRadio_regFieldEnum *)array;
    RW_reg reg = { 0u };
    for( uint8_t arrayIdx = 0u; arrayIdx < arrayLen; ++arrayIdx )
    {
        reg |= (1u << abstractedArray[arrayIdx]);
    }
    return reg;
}

static void setLogicalAddressPrefix( const uint8_t logicalAddress, const uint8_t prefix )
{
    const uint8_t regNum = logicalAddress / RADIO_PREFIXES_PER_REGISTER;
    const uint8_t byteNum = logicalAddress % RADIO_PREFIXES_PER_REGISTER;

    RADIO.PREFIX[regNum] = ( prefix << (byteNum * BYTE_SIZE_BITS ) );
}

void radio_init( void )
{
    RADIO.POWER = ENABLED;
}

void radio_setMode( const tRadio_mode mode )
{
    RADIO.MODE = mode;
}

void (radio_enableShorts)( const tRadio_shorts shorts[], const uint8_t arrayLen )
{
    RW_reg shortsReg = regFieldArrayToReg( (tRadio_regFieldEnumUnion *)shorts, arrayLen );
    RADIO.SHORTS |= shortsReg;
}

void (radio_disableShorts)( const tRadio_shorts shorts[], const uint8_t arrayLen )
{
    RW_reg shortsReg = regFieldArrayToReg( (tRadio_regFieldEnumUnion *)shorts, arrayLen );
    RADIO.SHORTS &= ~shortsReg;
}

void (radio_enableEvents)( const tRadio_event_handler_tableElement table[], const uint8_t tableLength )
{
    tRadio_context *pContext = getContext();

    nvic_changeInterruptState( NVIC_INT_RADIO, DISABLED );

    RW_reg enabledEvents = { 0 };
    for( uint8_t arrIdx = 0u; arrIdx < tableLength; ++arrIdx )
    {
        tRadio_events event = table[arrIdx].event;
        enabledEvents |= (1u << event);
        pContext->pfEventHandlers[event] = table[arrIdx].handler;
    }

    RADIO.INTENSET |= enabledEvents;

    nvic_changeInterruptState( NVIC_INT_RADIO, ENABLED );
}

void (radio_disableEvents)( const tRadio_events events[], const uint8_t arrayLen )
{
    tRadio_context *pContext = getContext();

    nvic_changeInterruptState( NVIC_INT_RADIO, DISABLED );

    RW_reg disabledEvents = regFieldArrayToReg( (tRadio_regFieldEnumUnion *)events, arrayLen );
    RADIO.INTENCLR |= disabledEvents;

    nvic_changeInterruptState( NVIC_INT_RADIO, ENABLED );
}


tRadio_retVal radio_setPacketConfiguration( const tRadio_packetConfig * const config )
{
    if( ( config->lengthFieldLen > RADIO_LENGTH_FIELD_MAX_LENGTH_BITS ) ||
        ( config->s0Len > RADIO_S0_FIELD_MAX_LENGTH_BYTES ) ||
        ( config->s1Len > RADIO_S1_FIELD_MAX_LENGTH_BITS ) )
    {
        return RADIO_INVALID_PARAM;
    }

    tRadio_pCnfRegs configReg =
    {
        .LFLEN      = config->lengthFieldLen,
        .S0LEN      = config->s0Len,
        .S1LEN      = config->s1Len,
        .S1INCL     = config->s1InclInRam,
        .PLEN       = config->preambleLen,
        .MAXLEN     = config->maxPayloadLen,
        .STATLEN    = config->staticLen,
        .BALEN      = config->baseAddrLen,
        .ENDIAN     = config->endian,
        .WHITEEN    = config->dataWhitening
    };

    memcpy( &RADIO.PCNF, &configReg, sizeof(configReg) );

    return RADIO_OK;
}

void radio_setPrimaryAddress( const uint8_t prefix, const uint32_t address )
{
    RADIO.BASE[0] = address;
    setLogicalAddressPrefix( 0u, prefix );
}

void radio_setSecondaryAddressBase( const uint32_t addressBase )
{
    RADIO.BASE[1] = addressBase;
}

void radio_setSecondaryAddressPrefix( const tRadio_logAddr logicalAddr, const uint8_t prefix )
{
    setLogicalAddressPrefix( logicalAddr, prefix );
}

void radio_setPacketAddress( const void * const pPacket )
{
    RADIO.PACKETPTR = (uint32_t)pPacket;
}

void radio_setTxAddress( const tRadio_logAddr logAddr )
{
    RADIO.TXADDRESS = logAddr;
}

void radio_setRxAddresses( const tRadio_logAddr logAddrs[], const uint8_t arrayLen )
{
    RW_reg regVal = { 0u };

    for( uint8_t idx = 0u; idx < arrayLen; ++idx )
    {
        regVal |= (1 << logAddrs[idx]);
    }
    RADIO.RXADDRESSES = regVal;
}

tRadio_retVal radio_enableTxMode( void )
{
    if( RADIO.STATE != RADIO_DISABLED )
    {
        return RADIO_INVALID_TASK;
    }

    RADIO.TASKS[RADIO_TASKS_TXEN] = ENABLED;
    return RADIO_OK;
}

tRadio_retVal radio_enableRxMode( void )
{
    if( RADIO.STATE != RADIO_DISABLED )
    {
        return RADIO_INVALID_TASK;
    }

    RADIO.TASKS[RADIO_TASKS_RXEN] = ENABLED;
    return RADIO_OK;
}

tRadio_retVal radio_start( void )
{
    tRadio_retVal retVal = RADIO_ERROR;

    if( ( RADIO.STATE == RADIO_TXIDLE ) ||
        ( RADIO.STATE == RADIO_RXIDLE ) )
    {
        RADIO.TASKS[RADIO_TASKS_START] = ENABLED;
        retVal = RADIO_OK;
    }
    else
    {
        retVal = RADIO_INVALID_TASK;
    }

    return retVal;
}

void radio_setWhiteningIV( uint8_t initVal )
{
    RADIO.DATAWHITEIV = initVal;
}

tRadio_retVal radio_configureCrc( tRadio_crcConfig *config )
{
    tRadio_retVal configStatus = RADIO_OK;
    uint32_t polyReg = 0u;
    uint8_t index = 0u;
    while( ( index < sizeof(config->polyArray) ) &&
            ( config->polyArray[index] != 0 ) &&
            ( RADIO_OK == configStatus ) )
    {
        if( config->polyArray[index] > 23u )
        {
            configStatus = RADIO_INVALID_PARAM;
        }
        polyReg |= ( 1u << config->polyArray[index] );
        ++index;
    }

    if( RADIO_OK == configStatus )
    {
        configStatus = config->initValue <= THREE_BYTE_MAX ? RADIO_OK : RADIO_INVALID_PARAM;
    }

    if( RADIO_OK == configStatus )
    {
        tRadio_crcCnfReg registerVal = {
            .LEN = config->crcLength,
            .SKIPADDR = config->addressBehaviour
        };
        RADIO.CRCCNF = registerVal;

        RADIO.CRCINIT = config->initValue;

        RADIO.CRCPOLY = polyReg;
    }

    return configStatus;
}

uint32_t radio_readCrc( void )
{
    return RADIO.RXCRC;
}

void Radio_isr( void )
{
    tRadio_context *pContext = getContext();
    for( tRadio_events event = 0u; event < RADIO_EVENTS_MAX; ++event )
    {
        if( RADIO.EVENTS[event] )
        {
            if( pContext->pfEventHandlers[event] != NULL )
            {
                pContext->pfEventHandlers[event]();
            }
            RADIO.EVENTS[event] = 0u;
        }

    }
}