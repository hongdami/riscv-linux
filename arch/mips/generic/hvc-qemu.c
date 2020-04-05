/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2008 David Gibson, IBM Corporation
 * Copyright (C) 2012 Regents of the University of California
 * Copyright (C) 2017 SiFive
 */

#include <linux/console.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/types.h>

#include "../../drivers/tty/hvc/hvc_console.h"

static int hvc_qemu_tty_put(uint32_t vtermno, const char *buf, int count)
{
	int i;

	for (i = 0; i < count; i++) {
    outb(buf[i], 0x3f8);
  }

	return i;
}

static int hvc_qemu_tty_get(uint32_t vtermno, char *buf, int count)
{
  return 0;

#if 0
	int i, c;
	for (i = 0; i < count; i++) {
		c = qemu_console_getchar();
		if (c < 0)
			break;
		buf[i] = c;
	}

	return i;
#endif
}

static const struct hv_ops hvc_qemu_ops = {
	.get_chars = hvc_qemu_tty_get,
	.put_chars = hvc_qemu_tty_put,
};

static int __init hvc_qemu_init(void)
{
	return PTR_ERR_OR_ZERO(hvc_alloc(0, 0, &hvc_qemu_ops, 16));
}
device_initcall(hvc_qemu_init);

static int __init hvc_qemu_console_init(void)
{
	hvc_instantiate(0, 0, &hvc_qemu_ops);
	add_preferred_console("hvc", 0, NULL);

	return 0;
}
console_initcall(hvc_qemu_console_init);
