/*
 *  Simcom A7672G driver
 */

#include <nrfx_uart.h>
#include "simcom.h"

/* UART instance. */
#define UART_INSTANCE_ID         0
static const nrfx_uart_t uart_instance = NRFX_UART_INSTANCE(UART_INSTANCE_ID);

/* UART config. */
static struct nrfx_uart_config_t uart_config =
            NRFX_UART_DEFAULT_CONFIG(UART_LTE_TXD, UART_LTE_RXD);

nrfx_err_t SIMCOM_uart_init(void)
{
    return nrfx_uart_init(&uart_instance, &uart_config, NULL);
}

void SIMCOM_uart_uninit(void)
{
    nrfx_uart_uninit(&uart_instance);
}

nrfx_err_t SIMCOM_uart_tx(uint8_t *data, size_t len)
{
    return nrfx_uart_tx(&uart_instance, data, len);
}