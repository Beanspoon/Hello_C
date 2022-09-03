#include "core_ctrl.h"

#include "types.h"

/**
 * @brief Core context
 * 
 */
typedef struct
{
    uint32_t    tick_count;
} tCore_context;

/**
 * @brief Get a pointer to the core context
 * 
 * @return pointer to the core context
 */
static tCore_context* getContext( void )
{
    static tCore_context context = { 0 };
    return &context;
}

void Systick_handler( void )
{
    tCore_context *pContext = getContext();
    ++(pContext->tick_count);
}