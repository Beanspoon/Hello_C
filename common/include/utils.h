#ifndef UTILS_H
#define UTILS_H

#include <stdint-gcc.h>

#define ARRAY_SIZE( array )     ( sizeof(array)/sizeof(array[0]) )
#define BYTE_SIZE_BITS          8u

#define THREE_BYTE_MAX          0xFFFFFF

/**
 * @brief Copy data from address pSource to address pDest
 *
 * @param pDest pointer to the destination memory address
 * @param pSource pointer to the source memory address
 * @param length number of bytes to copy
 */
void memcpy( void *pDest, const void *pSource, uint32_t length );

#endif