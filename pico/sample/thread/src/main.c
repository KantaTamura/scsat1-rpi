/*
 * Copyright (c) 2024 Space Cubics, LLC.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel/thread.h>
#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, CONFIG_MAIN_LOG_LEVEL);

#define MY_STACK_SIZE 200
#define MY_PRIORITY   5

void my_entry_point(void *arg1, void *arg2, void *arg3)
{
	LOG_INF("insert thread!!");
}

K_THREAD_STACK_DEFINE(my_stack_area, MY_STACK_SIZE);

int main(void)
{
	LOG_INF("start application");
	struct k_thread my_thread_data;
	k_tid_t my_tid = k_thread_create(&my_thread_data, my_stack_area,
					 K_THREAD_STACK_SIZEOF(my_stack_area), my_entry_point, NULL,
					 NULL, NULL, MY_PRIORITY, 0, K_NO_WAIT);
	LOG_INF("end application");
	k_sleep(K_MSEC(1000));
	return 0;
}
