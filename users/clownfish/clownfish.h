// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"
#include "action.h"
#include "quantum_keycodes.h"
#include "version.h"

enum clownfish_keycodes {
    KC_MAKE = QK_KB_0,
    ALT_TAB,
    EXTEND,
    CHROME,
    SPAM,
    VENV,
    CLANGD,
    DBL_0,
    KC_KEYLOCK,
    CLOWNFISH_RANGE
};
#ifdef RGB_MATRIX_ENABLE
    #include "rgb_keys.h"
#else
    #define MY_SAFE_RANGE CLOWNFISH_RANGE
#endif
