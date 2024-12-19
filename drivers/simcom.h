/*
 *  Simcom A7672G driver
 */

#include <nrfx_errors.h>

nrfx_err_t SIMCOM_uart_init(void);
void SIMCOM_uart_uninit(void);
nrfx_err_t SIMCOM_uart_tx(uint8_t *data, size_t len);