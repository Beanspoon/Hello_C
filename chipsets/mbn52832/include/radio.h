#ifndef RADIO_H
#define RADIO_H

#include "types.h"
#include "utils.h"

/**
 * @brief Radio shortcuts enum
 *
 */
typedef enum
{
    RADIO_SHORTS_READY_START,
    RADIO_SHORTS_END_DISABLE,
    RADIO_SHORTS_DISABLED_TXEN,
    RADIO_SHORTS_DISABLED_RXEN,
    RADIO_SHORTS_ADDRESS_RSSISTART,
    RADIO_SHORTS_END_START,
    RADIO_SHORTS_ADDRESS_BCSTART,
    RADIO_SHORTS_DISABLED_RSSISTOP = 8u,
    RADIO_SHORTS_MAX
} tRadio_shorts;

/**
 * @brief Radio events enum
 *
 */
typedef enum
{
    RADIO_EVENTS_READY    = 0,    // Radio has ramped up and is ready for tx or rx
    RADIO_EVENTS_ADDRESS  = 1,    // Address transmitted or received
    RADIO_EVENTS_PAYLOAD  = 2,    // Payload transmitted or recieved
    RADIO_EVENTS_END      = 3,    // Tx or rx complete
    RADIO_EVENTS_DISABLED = 4,    // Radio has been disabled
    RADIO_EVENTS_DEVMATCH = 5,    // Address match occurred on the last recevied packet
    RADIO_EVENTS_DEVMISS  = 6,    // No address match occurred on the last recevied packet
    RADIO_EVENTS_RSSIEND  = 7,    // RSSI sampling is complete

    RADIO_EVENTS_BCMATCH  = 10,   // Bit counter reached bit count match value

    RADIO_EVENTS_CRCOK    = 12,   // Packet recieved with CRC OK
    RADIO_EVENTS_CRCERROR = 13,   // Packet recieved with CRC error
    RADIO_EVENTS_MAX
} tRadio_events;

/**
 * @brief Typedef for event handler
 *  Called by radio interrupt
 *
 */
typedef void (*tRadio_eventHandler)( void );

/**
 * @brief Table element pairing events with pointers to handler functions
 *
 */
typedef struct
{
    tRadio_events       event;
    tRadio_eventHandler handler;
} tRadio_event_handler_tableElement;

/**
 * @brief Packet configuration S1 include enum
 *
 */
typedef enum
{
    RADIO_S1INCL_AUTO,
    RADIO_S1INCL_ALWAYS
} tRadio_s1Incl;

/**
 * @brief Packet configuration preamble length enum
 *
 */
typedef enum
{
    RADIO_PLEN_8BIT,
    RADIO_PLEN_16BIT
} tRadio_pLen;

/**
 * @brief Packet configuration base address length enum
 *
 */
typedef enum
{
    RADIO_2_BYTE_BASE_ADDR = 2,
    RADIO_3_BYTE_BASE_ADDR = 3,
    RADIO_4_BYTE_BASE_ADDR = 4
} tRadio_baseAddrLen;

/**
 * @brief Packet configuration endianness of S0, length, S1 and payload sections
 *
 */
typedef enum
{
    RADIO_LITTLE_ENDIAN,
    RADIO_BIG_ENDIAN,
} tRadio_endianness;

/**
 * @brief Logical address enum
 *
 */
typedef enum
{
    RADIO_LOGADDR_PRIMARY,
    RADIO_LOGADDR1,
    RADIO_LOGADDR2,
    RADIO_LOGADDR3,
    RADIO_LOGADDR4,
    RADIO_LOGADDR5,
    RADIO_LOGADDR6,
    RADIO_LOGADDR7
} tRadio_logAddr;

/**
 * @brief Radio mode enum
 *
 */
typedef enum
{
    RADIO_MODE_NRF1MBIT,
    RADIO_MODE_NRF2MBIT,
    RADIO_MODE_BLE1MBIT = 3,
    RADIO_MODE_BLE2MBIT,
} tRadio_mode;

/**
 * @brief Radio CRC length enum
 *
 */
typedef enum
{
    RADIO_CRC_DISABLED,
    RADIO_1_BYTE_CRC,
    RADIO_2_BYTE_CRC,
    RADIO_3_BYTE_CRC
} tRadio_crcLen;

/**
 * @brief Radio CRC behaviour
 *
 */
typedef enum
{
    RADIO_CRC_INCLUDE_ADDRESS,
    RADIO_CRC_SKIP_ADDRESS
} tRadio_crcAddrBehaviour;

/**
 * @brief Packet configuration structure
 *
 */
typedef struct
{
    uint8_t             lengthFieldLen; // Length (on-air) in bits of the packet length field (max 8)
    uint8_t             s0Len;          // Length (on-air) in bytes of the s0 field (max 1)
    uint8_t             s1Len;          // Length (on-air) in bits of the s1 field (max 8)
    tRadio_s1Incl       s1InclInRam;    // Setting for including S1 in RAM: "automatic" or "always"
    tRadio_pLen         preambleLen;    // Preamble length: 8-bit or 16-bit
    uint8_t             maxPayloadLen;  // Maximum length of packet payload in bytes. Larger payloads will be truncated to maxPayloadLen
    uint8_t             staticLen;      // Static length added to payload in bytes. If staticLen = N, radio will send/receive N bytes more than length field
    tRadio_baseAddrLen  baseAddrLen;    // Base address length in bytes
    tRadio_endianness   endian;         // On-air endianness of S0, LENGTH, S1 and PAYLOAD fields
    tEnableState        dataWhitening;  // Enable or disable packet whitening
} tRadio_packetConfig;

/**
 * @brief CRC configuration structure
 *
 */
typedef struct
{
    tRadio_crcLen           crcLength;          // Length of the CRC
    tRadio_crcAddrBehaviour addressBehaviour;   // Include or skip address in CRC calculation
    uint32_t                initValue;          // Init value for CRC calculation
    uint8_t                 polyArray[24u];     // Array of terms for CRC calculation
} tRadio_crcConfig;

/**
 * @brief Radio return value used to indicate success or failure of a radio function
 *
 */
typedef enum
{
    RADIO_OK,               // Success
    RADIO_INVALID_PARAM,    // Parameters supplied were invalid
    RADIO_INVALID_TASK,     // Task is not valid for current radio state
    RADIO_ERROR,            // An error occurred
} tRadio_retVal;

/**
 * @brief Initialise radio peripheral
 *
 */
void radio_init( void );

void (radio_enableShorts)( const tRadio_shorts shorts[], const uint8_t arrayLen );
/**
 * @brief Enables the target shorts
 *
 * @param[in] shortsArray Shortcuts to be enabled
 */
#define radio_enableShorts( shortsArray )   radio_enableShorts( shortsArray, ARRAY_SIZE( shortsArray ) )

void (radio_disableShorts)( const tRadio_shorts shorts[], const uint8_t arrayLen );
/**
 * @brief Disables the target shorts
 *
 * @param[in] shortsArray Shortcuts to be disabled
 */
#define radio_disableShorts( shortsArray )  radio_disableShorts( shortsArray, ARRAY_SIZE( shortsArray ) )

void (radio_enableEvents)( const tRadio_event_handler_tableElement table[], const uint8_t tableLen);
/**
 * @brief Enables radio events with associated handlers
 *  Handlers of enabled events will be called when that event occurs
 *
 * @param[in] event_handlerTable Table of events to be enabled along with event handler
 */
#define radio_enableEvents( event_handler_table )    radio_enableEvents( event_handler_table, ARRAY_SIZE( event_handler_table ) )

void (radio_disableEvents)( const tRadio_events events[], const uint8_t arrayLen );
/**
 * @brief Disables events
 *  Handlers for diabled events will be set to NULL
 *
 * @param[in] events Array of events to disable
 */
#define radio_disableEvents( events )   radio_disableEvents( events, ARRAY_SIZE( events ) )

/**
 * @brief Set the radio mode to use
 *
 * @param[in] mode Radio mode setting
 */
void radio_setMode( const tRadio_mode mode );

/**
 * @brief Sets the packet configuration
 *
 * @param[in] config Packet config structure for defining packet configuration
 *
 * @return tRadio_retVal describing the status of the operation
 */
tRadio_retVal radio_setPacketConfiguration( const tRadio_packetConfig * const config );

/**
 * @brief Sets the primary address
 *
 * @param[in] baseAddr Base address to set
 * @param[in] address Value to set the base address to
 */
void radio_setPrimaryAddress( const uint8_t prefix, const uint32_t address );

/**
 * @brief Sets the base for the secondary addresses
 *
 * @param[in] addressBase Value of the address base
 */
void radio_setSecondaryAddressBase( const uint32_t addressBase );

/**
 * @brief Sets the target logical address prefix
 * Logical addresses use the secondary address base plus a prefix
 *
 * @param[in] logicalAddr Logical address prefix to set
 * @param[in] prefix Value of the prefix
 */
void radio_setAddressPrefix( const tRadio_logAddr logicalAddr, const uint8_t prefix );

/**
 * @brief Assigns the memory address of the packet to be transmitted
 *
 * @param[in] pPacket pointer to the packet in memory
 */
void radio_setPacketAddress( const void * const pPacket );

/**
 * @brief Sets the logical address to use in transmission
 *
 * @param[in] logAddr the logical address to be used
 */
void radio_setTxAddress( const tRadio_logAddr logAddr );

void radio_setRxAddresses( const tRadio_logAddr logAddrs[], const uint8_t arrayLen );

/**
 * @brief Ramps up the radio in TX mode. Event READY will trigger when complete
 *
 * @return tRadio_retVal indicating success or failure of setting the task
 */
tRadio_retVal radio_enableTxMode( void );

/**
 * @brief Ramps up the radio in RX mode. Event READY will trigger when complete
 *
 * @return tRadio_retVal RADIO_INVALID_TASK if radio is not in correct state else RADIO_OK
 */
tRadio_retVal radio_enableRxMode( void );

/**
 * @brief Starts transmission or reception
 *
 * @return tRadio_retVal indicating success or failure of settin the task
 */
tRadio_retVal radio_start( void );

/**
 * @brief Sets the initial value for data whitening
 *
 * @param[in] initVal Initial value for data whitening
 */
void radio_setWhiteningIV( uint8_t initVal );

/**
 * @brief Configure the radio's CRC check
 *
 * @param[in] crcLength Length of the CRC in bytes
 * @param[in] addressBehaviour Include or skip address in CRC calculation
 */
tRadio_retVal radio_configureCrc( tRadio_crcConfig *config );

/**
 * @brief Reads the CRC value of a received packet
 *
 * @return uint32_t containing the CRC value
 */
uint32_t radio_readCrc( void );

#endif // RADIO_H
