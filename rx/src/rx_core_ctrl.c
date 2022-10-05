#include "rx_core_ctrl.h"

#include <stdint-gcc.h>

/**
 * @brief Core context
 *
 */
typedef struct
{
    uint32_t    tick_count;
} tCoreCtrl_context;

/**
 * @brief Get a pointer to the core context
 *
 * @return pointer to the core context
 */
static tCoreCtrl_context *getContext( void )
{
    static tCoreCtrl_context coreCtrl_context = { 0 };
    return &coreCtrl_context;
}

void Systick_handler( void )
{
    tCoreCtrl_context *pContext = getContext();
    ++(pContext->tick_count);
}