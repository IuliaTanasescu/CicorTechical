/*
 * LP5012 driver
 */

#include <nrfx_errors.h>

nrfx_err_t LP5012_twi_init(void);
void LP5012_twi_uninit(void);
void LP5012_global_on_off(bool enable);