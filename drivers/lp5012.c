/*
 * LP5012 driver
 */

#include <nrfx_twi.h>
#include <nrf_gpio.>
#include "lp5012.h"

/* Device config registers. */
#define LP5012_DEVICE_CONFIG0       0x00
#define LP5012_DEVICE_CONFIG1       0x01
#define LP5012_REGISTER_RESET       0x17

/* I2C slave address */
#define LP5012_ADDR                 0x14

#define LP5012_ENABLE               1 << 6

#define LP5012_RESET                0xFF

#define LED_GLOBAL_ON_BITMASK       ~(1 << 0)
#define LED_GLOBAL_OFF_BITMASK      1 << 0

/* TWI instance. */
#define TWI_INSTANCE_ID             0
static const nrfx_twi_t master_twi_instance = NRFX_TWI_INSTANCE(TWI_INSTANCE_ID);

/* TWI config. */
static const nrfx_twi_config_t twi_config = NRFX_TWI_DEFAULT_CONFIG(I2C_SCL, I2C_SDA);

nrfx_err_t LP5012_twi_init(void)
{
    nrfx_err_t err;

    /* Set enable pin. */
     nrf_gpio_cfg_output(EN_PIN);
     nrf_gpio_pin_set(EN_PIN);

    err = nrfx_twi_init(&master_twi_instance, &twi_config, NULL, context);

    if (err != NRFX_SUCCESS)
        return err;

    nrfx_twi_enable(&master_twi_instance);

    /* Set Chip_EN bit to enable chip. */
    LP5012_write_reg(LP5012_DEVICE_CONFIG0, LP5012_ENABLE);
}

void LP5012_twi_uninit(void)
{
    /* Reset registers. */
     LP5012_write_reg(LP5012_REGISTER_RESET, LP5012_RESET);

    nrfx_twi_disable(&master_twi_instance);
    nrfx_twi_uninit(&master_twi_instance);

    /* Clear enable pin. */
     nrf_gpio_pin_clear(EN_PIN);
}

static void LP5012_read_reg(uint8_t reg, uint8_t *value)
{
    uint32_t flags = NRF_DRV_TWI_FLAG_TX_NO_STOP;
    nrf_drv_twi_xfer_desc_t desc = NRFX_TWI_XFER_DESC_TXRX(LP5012_ADDR,
                                                &reg,               
                                                sizeof(reg)	,																
                                                value,
                                                sizeof(*value));

    /* Read register. */
    nrfx_twi_xfer(&master_twi_instance, &desc, flags);
}

static void LP5012_write_reg(uint8_t reg, uint8_t value)
{
    uint32_t flags = NRF_DRV_TWI_FLAG_TX_NO_STOP;
    nrf_drv_twi_xfer_desc_t desc = NRFX_TWI_XFER_DESC_TXTX(LP5012_ADDR,
                                                &reg,               
                                                sizeof(reg)	,																
                                                &value,
                                                sizeof(value));

    /* Write register. */
    nrfx_twi_xfer(&master_twi_instance, &desc, flags);
}

void LP5012_global_on_off(bool enable)
{
    uint8_t value;

    LP5012_read_reg(LP5012_DEVICE_CONFIG1, &value);

    if (enable)
        value &= LED_GLOBAL_ON_BITMASK;
    else
        value |= LED_GLOBAL_OFF_BITMASK;

    LP5012_write_reg(LP5012_DEVICE_CONFIG1, value);
}