#ifndef UTILS_H
#define UTILS_H

#include "types.h"

/**
 * @brief Copy data from address pSource to address pDest
 * 
 * @param pDest pointer to the destination memory address
 * @param pSource pointer to the source memory address
 * @param length number of bytes to copy
 */
void memcpy( void *pDest, const void * pSource, uint32_t length );

#endif