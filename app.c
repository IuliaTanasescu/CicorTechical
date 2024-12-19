#include "simcom.h"
#include "max17260.h"
#include "lp5012.h"

#define BATTERY_CAP_THRESHOLD

int main(void)
{
    uint16_t battery_cap;
    nrfx_err_t err;

    err = MAX17260_twi_init();
    if (err != NRFX_SUCCESS)
        return -1;

    err = LP5012_twi_init();
    if (err != NRFX_SUCCESS)
        return -1;

    err = SIMCOM_uart_init();
    if (err != NRFX_SUCCESS)
        return -1;

    for (;; )
    {
		nrf_delay_ms(5000);

        /* Read battery capacity. */
        MAX17260_Read_RepCap(&battery_cap);

        if (battery_cap < BATTERY_CAP_THRESHOLD)
            /* Turn OFF LEDS. */
            LP5012_global_on_off(false);
        else
            /* Turn ON LEDS. */
            LP5012_global_on_off(true);

        /* Send battery capacity to LTE module. */
        SIMCOM_uart_tx((uint8_t *)&battery_cap, sizeof(battery_cap));
    }

    MAX17260_twi_uninit();
    LP5012_twi_uninit();
    SIMCOM_uart_uninit();
}