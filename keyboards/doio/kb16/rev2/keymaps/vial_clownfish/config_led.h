// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "rgb_matrix.h"

led_config_t g_led_config = {
  {
    { 0,  1,  2,  3,  NO_LED },
    { 4,  5,  6,  7,  NO_LED },
    { 8,  9,  10, 11, NO_LED },
    { 12, 13, 14, 15, NO_LED },
  },
  { {0, 0},  {21, 0},  {43, 0},  {64, 0},
    {0, 21}, {21, 21}, {43, 21}, {64, 21},
    {0, 43}, {21, 43}, {43, 43}, {64, 43},
    {0, 64}, {21, 64}, {43, 64}, {64, 64}
  },
  { 1, 1, 1, 1,
    1, 4, 4, 1,
    1, 4, 4, 1,
    1, 1, 1, 1
  },
};
