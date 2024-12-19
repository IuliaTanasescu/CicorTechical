/*
 * MAX17260 driver
 */

#include <nrfx_twi.h>
#include "max17260.h"

/* Reported Capacity Register. */
#define MAX1726X_REPCAP_REG     0x05

/* I2C slave address. */
#define MAX17260_ADDR           0x6C

/* TWI instance. */
#define TWI_INSTANCE_ID         0
static const nrfx_twi_t master_twi_instance = NRFX_TWI_INSTANCE(TWI_INSTANCE_ID);

/* TWI config. */
static const nrfx_twi_config_t twi_config = NRFX_TWI_DEFAULT_CONFIG(I2C_SCL, I2C_SDA);

nrfx_err_t MAX17260_twi_init(void *context)
{
    nrfx_err_t err;

    err = nrfx_twi_init(&master_twi_instance, &twi_config, NULL, context);

    if (err != NRFX_SUCCESS)
        return err;

    nrfx_twi_enable(&master_twi_instance);
}

void MAX17260_twi_uninit(void)
{
    nrfx_twi_disable(&master_twi_instance);
    nrfx_twi_uninit(&master_twi_instance);
}

void MAX17260_Read_RepCap(uint16_t *battery_cap)
{
    uint8_t reg = MAX1726X_REPCAP_REG;
    uint32_t flags = NRF_DRV_TWI_FLAG_TX_NO_STOP;
    nrf_drv_twi_xfer_desc_t desc = NRFX_TWI_XFER_DESC_TXRX(MAX17260_ADDR,
                                                &reg,               
                                                sizeof(reg)	,																
                                                battery_cap,
                                                sizeof(*battery_cap));

    /* Read battery capacity. */
    nrfx_twi_xfer(&master_twi_instance, &desc, flags);
}