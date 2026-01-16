// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "clownfish.h"

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
__attribute__((weak)) bool process_record_rgb(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
            if (!record->event.pressed) {
                uint8_t temp_mod = get_mods();
                uint8_t temp_osm = get_oneshot_mods();
                clear_mods(); clear_oneshot_mods();
                SEND_STRING("qmk compile -kb " QMK_KEYBOARD " -km " QMK_KEYMAP);
                if ((temp_mod | temp_osm) & MOD_MASK_SHIFT){
                    SEND_STRING(" --compiledb");
                }
                if ((temp_mod | temp_osm) & MOD_MASK_CTRL) {
                    SEND_STRING(" -j 8");
                }
                tap_code(KC_ENT);
                set_mods(temp_mod);
                }
            break;
        case ALT_TAB:  // Sends Alt+Tab to switch applications
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
                } else {
                unregister_code(KC_TAB);
                }
            break;
        case EXTEND:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("P") SS_DELAY(400) SS_TAP(X_DOWN) SS_DELAY(100) SS_TAP(X_DOWN) SS_DELAY(200) SS_TAP(X_ENT) SS_DELAY(200) SS_TAP(X_ESC) );
            }
            return false;
        case CHROME:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(" ") SS_DELAY(200) ">chrome.exe" SS_DELAY(200) SS_TAP(X_ENT));
            }
            return false;
        case SPAM:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("acvvvvv"));
            }
            return false;
        case VENV:
            if (record->event.pressed) {
                SEND_STRING("source .venv/bin/activate\n"); // Activates Python virtual environment
            }
            return false;
        case CLANGD:
            if (record->event.pressed) {
                SEND_STRING("qmk compile --compiledb -kb  -km " SS_DOWN(X_LCTL) SS_TAP(X_LEFT) SS_UP(X_LCTL) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
            }
            return false;
        case DBL_0:
            if (record->event.pressed) {
                SEND_STRING("00");
            }
            return false;
        case KC_KEYLOCK:
            if (record->event.pressed) {
                // Trigger QK_LOCK by simulating a keypress
                // We need to process QK_LOCK through the action system
                // Create a synthetic keyrecord for QK_LOCK
                keyrecord_t lock_record = *record;
                // Process QK_LOCK action
                action_t action = action_for_keycode(QK_LOCK);
                if (action.kind.id != ACTION_NO) {
                    // Process press
                    lock_record.event.pressed = true;
                    process_action(&lock_record, action);
                    // Process release immediately after
                    lock_record.event.pressed = false;
                    process_action(&lock_record, action);
                }
            }
            return false;
    }
#ifdef RGB_MATRIX_ENABLE
    return process_record_rgb(keycode, record);
#else
    return process_record_keymap(keycode, record);
#endif
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
