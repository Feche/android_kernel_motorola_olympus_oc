/*
 * arch/arm/mach-tegra/board-olympus-kbc.c
 *
 * Copyright 2013: Olympus Kernel Project
 * <http://forum.xda-developers.com/showthread.php?t=2016837>
 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/device.h>

#include <mach/clk.h>
#include <mach/iomap.h>
#include <mach/irqs.h>
#include <mach/pinmux.h>
#include <mach/iomap.h>
#include <mach/io.h>
#include <mach/kbc.h>

#include <asm/mach-types.h>
#include <asm/mach/arch.h>

#define OLYMPUS_ROW_COUNT	3
#define OLYMPUS_COL_COUNT	3

static const u32 olympus_keymap[] = {
	KEY(0, 0, 115), //KEY_VOLUMEUP
	KEY(0, 1, 211), //KEY_HP
	KEY(0, 1, 116), //KEY_POWER
	KEY(0, 2, 139), //KEY_MENU
	KEY(1, 0, 114), //KEY_VOLUMEDOWN
	KEY(1, 1, 212), //KEY_CAMERA
	KEY(1, 2, 102), //KEY_HOME
	KEY(2, 0, 000), //KEY_RESERVED
	KEY(2, 1, 217), //KEY_SEARCH
	KEY(2, 2, 158), //KEY_BACK
};

static const struct matrix_keymap_data olympus_keymap_data = {
	.keymap = olympus_keymap,
	.keymap_size = ARRAY_SIZE(olympus_keymap),
};

static struct tegra_kbc_wake_key olympus_wake_cfg[] = {
	[0] = {
		.row = 0,
		.col = 0,
	},
	[1] = {
		.row = 1,
		.col = 0,
	},
#if 0
	[2] = {
		.row = 1,
		.col = 1,
	},
	[3] = {
		.row = 2,
		//.col = 0,
	},
	[4] = {
		.row = 2,
		.col = 1,
	},
#endif
};

static struct tegra_kbc_platform_data olympus_kbc_platform_data = {
	.debounce_cnt = 20, //5,
	.repeat_cnt = 1600, //1024,
	.wake_cnt = 2, //5,
	.wake_cfg = &olympus_wake_cfg[0],
	.keymap_data = &olympus_keymap_data,
	.use_fn_map = false,
	.wakeup = true,
/*
#ifdef CONFIG_ANDROID
	.disable_ev_rep = true,
#endif*/
};

static struct resource olympus_kbc_resources[] = {
	[0] = {
		.start = TEGRA_KBC_BASE,
		.end   = TEGRA_KBC_BASE + TEGRA_KBC_SIZE - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = INT_KBC,
		.end   = INT_KBC,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device olympus_kbc_device = {
	.name = "tegra-kbc",
	.id = -1,
	.dev = {
		.platform_data = &olympus_kbc_platform_data,
	},
	.resource = olympus_kbc_resources,
	.num_resources = ARRAY_SIZE(olympus_kbc_resources),
};

int __init olympus_kbc_init(void)
{
	struct tegra_kbc_platform_data *data = &olympus_kbc_platform_data;
	int i;

	pr_info("KBC: olympus_kbc_init\n");
	for (i = 0; i < OLYMPUS_ROW_COUNT; i++) {
		data->pin_cfg[i].num = i;
		data->pin_cfg[i].is_row = true;
		data->pin_cfg[i].en = true;
	}
	for (i = 0; i < OLYMPUS_COL_COUNT; i++) {
		data->pin_cfg[i + 16].num = i;
		data->pin_cfg[i + 16].en = true;
	}

	platform_device_register(&olympus_kbc_device);
	return 0;
}
