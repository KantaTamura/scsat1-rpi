/*
 * Copyright (c) 2024 Space Cubics, LLC.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>

#define CONSOLE_DEVICE DEVICE_DT_GET(DT_CHOSEN(zephyr_console))

int main(void)
{
    const struct device *dev = CONSOLE_DEVICE;
    uint32_t dtr = 0;

    while (!dtr) {
        int status = uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
        if (status != 0) {
            /* if returing not 0 then "API is not enable" or
             * "this function is not implemented"
             * ref.
             *   https://docs.zephyrproject.org/latest/hardware/peripherals/uart.html#c.uart_line_ctrl_get
             */
            break;
        }
        k_sleep(K_MSEC(100));
    }

    while (1) {
        printk("Hello World!\n");
        k_sleep(K_MSEC(1000));
    }

    return 0;
}
