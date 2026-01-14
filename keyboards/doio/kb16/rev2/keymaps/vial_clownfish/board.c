// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

void board_init(void) {
    gpio_set_pin_output(A10);
    gpio_write_pin_low(A10);
}
