/*
 * MAX17260 driver
 */

#include <nrfx_errors.h>

nrfx_err_t MAX17260_twi_init(void);
void MAX17260_twi_uninit(void);
void MAX17260_Read_RepCap(uint16_t *battery_cap);