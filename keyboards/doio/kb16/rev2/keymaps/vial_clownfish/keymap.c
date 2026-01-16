/* Copyright 2022 DOIO
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "rgb_keys.h"

// OLED animation
#include "oled_layers.h"

#include "elpekenin/ledmap.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum my_layers {
    NUM,
    WIN,
    WIN_FN,
    MAC,
    MAC_FN,
    MEDIA,
    BROWSER,
    DISCORD,
    MOUSE,
    GAME,
    GAME_FN,
    LIGHT
};
// const char *layers[] = {
//     "NUMPAD",
//     "WINDOWS",
//     "WIN_FN",
//     "MACOS",
//     "MAC_FN",
//     "MEDIA",
//     "BROWSER",
//     "DISCORD",
//     "MOUSE",
//     "GAME",
//     "GAME_FN",
//     "LIGHTING"
// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*  NUM
       ┌────┬────┬────┬────┐  LIGHT|WIN       WHL↑|WHL↓
       │ 7  │ 8  │ 9  │Num │    ┌────┐         ┌────┐
       ├────┼────┼────┼────┤    │Togg│         │MS 3│
       │ 4  │ 5  │ 6  │ -  │    └────┘         └────┘
       ├────┼────┼────┼────┤
       │ 1  │ 2  │ 3  │ +  │          Vol-|Vol+
       ├────┼────┼────┼────┤           ┌────┐
       │ 0  │ 00 │ .  │Ent │           │Mute│
       └────┴────┴────┴────┘           └────┘
*/
    [NUM] = LAYOUT(
                MO(1),     KC_P1,    KC_P4,     KC_7,   RM_TOGG,
                KC_P0,     KC_P2,    KC_P5,     KC_8,  MS_BTN3,
                KC_PDOT,   KC_P3,    KC_P6,     KC_9,  KC_MUTE,
                KC_ENT,    C(S(KC_PGUP)),    KC_KP_PLUS,   KC_KP_MINUS
            ),

/*  WIN
       ┌────┬────┬────┬────┐    NUM|MAC       Vol-|Vol+
       │Esc │Copy│Pste│Bksp│    ┌────┐         ┌────┐
       ├────┼────┼────┼────┤    │Togg│         │Mute│
       │ATab│Tab │ ↑  │Ent │    └────┘         └────┘
       ├────┼────┼────┼────┤
       │Shft│ ←  │ ↓  │ →  │          WHL↑|WHL↓
       ├────┼────┼────┼────┤           ┌────┐
       │Ctrl│Win │Lock│ Fn │           │MS 3│
       └────┴────┴────┴────┘           └────┘
*/
    [WIN] = LAYOUT(
                KC_ESC,  C(KC_C), C(KC_V),        QK_BOOT, RM_TOGG,
                ALT_TAB, KC_TAB,  KC_UP,          KC_MS_L,  KC_MUTE,
                KC_LSFT, KC_LEFT, KC_DOWN,        KC_MS_R, MS_BTN3,
                KC_LCTL, QK_LOCK, KC_KP_ASTERISK, KC_KP_SLASH
            ),

/*  WIN_FN
       ┌────┬────┬────┬────┐    NUM|MAC      Scrn-|Scrn+
       │Dktp│Cut │Undo│Sett│    ┌────┐         ┌────┐
       ├────┼────┼────┼────┤    │Togg│         │Ext │
       │Calc│Expl│Max │Actn│    └────┘         └────┘
       ├────┼────┼────┼────┤
       │SSht│Zon-│Min │Zon+│          Vol-|Vol+
       ├────┼────┼────┼────┤           ┌────┐
       │VDT-│nVDT│VDT+│ ▼  │           │Mute│
       └────┴────┴────┴────┘           └────┘
*/
    [WIN_FN] = LAYOUT(
                G(KC_D),       C(KC_X),    C(KC_Z),       G(KC_I),    RM_TOGG,
                KC_CALC,       G(KC_E),    G(S(KC_UP)),   G(KC_A),    EXTEND,
                G(S(KC_S)),    G(KC_LEFT), G(S(KC_DOWN)), G(KC_RGHT), KC_MUTE,
                G(C(KC_LEFT)), G(C(KC_D)), G(C(KC_RGHT)), KC_TRNS
            ),

/*  MAC
       ┌────┬────┬────┬────┐    WIN|MEDIA     Vol-|Vol+
       │Esc │Copy│Pste│Bksp│    ┌────┐         ┌────┐
       ├────┼────┼────┼────┤    │Togg│         │Mute│
       │ATab│Tab │ ↑  │Ent │    └────┘         └────┘
       ├────┼────┼────┼────┤
       │Shft│ ←  │ ↓  │ →  │          WHL↑|WHL↓
       ├────┼────┼────┼────┤           ┌────┐
       │Ctrl│Opt │Lock│ Fn │           │MS 3│
       └────┴────┴────┴────┘           └────┘
*/
    [MAC] = LAYOUT(
                KC_ESC,  G(KC_C), G(KC_V), KC_BSPC, RM_TOGG,
                ALT_TAB, KC_TAB,  KC_UP,   KC_ENT,  KC_MUTE,
                KC_LSFT, KC_LEFT, KC_DOWN, KC_RGHT, MS_BTN3,
                KC_LCTL, KC_LOPT, QK_LOCK, MO(MAC_FN)
            ),

/*  MAC_FN
       ┌────┬────┬────┬────┐    WIN|MEDIA    Scrn-|Scrn+
       │Dktp│Cut │Undo│Sptl│    ┌────┐         ┌────┐
       ├────┼────┼────┼────┤    │Togg│         │MS 3│
       │Wndw│Lpad│ZonT│MCtl│    └────┘         └────┘
       ├────┼────┼────┼────┤
       │SSht│ZonL│Min │ZonR│          Vol-|Vol+
       ├────┼────┼────┼────┤           ┌────┐
       │VDT-│nVDT│VDT+│ ▼  │           │Mute│
       └────┴────┴────┴────┘           └────┘
*/
    [MAC_FN] = LAYOUT(
                G(A(KC_M)),    G(KC_X),       G(KC_Z),       G(A(KC_SPC)),  RM_TOGG,
                G(KC_GRV),     KC_LPAD,       C(A(KC_UP)),   KC_MCTL,       MS_BTN3,
                G(S(KC_4)),    C(A(KC_LEFT)), G(KC_M),       C(A(KC_LEFT)), KC_MUTE,
                C(KC_LEFT),    C(KC_UP),      C(KC_RGHT),    KC_TRNS
            ),

/*  MEDIA
       ┌────┬────┬────┬────┐    MAC|BROWSER   Prev|Next
       │Esc │Tab │Stop│MPlr│    ┌────┐         ┌────┐
       ├────┼────┼────┼────┤    │Togg│         │Play│
       │Ejct│ RW │ ↑  │ FF │    └────┘         └────┘
       ├────┼────┼────┼────┤
       │Ent │ ←  │ ↓  │ →  │          Vol-|Vol+
       ├────┼────┼────┼────┤           ┌────┐
       │Spce│Prev│Play│Next│           │Mute│
       └────┴────┴────┴────┘           └────┘
*/
    [MEDIA] = LAYOUT(
                KC_ESC,  KC_TAB,  KC_MSTP, KC_MSEL, RM_TOGG,
                KC_EJCT, KC_MRWD, KC_UP,   KC_MFFD, KC_MPLY,
                KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT, KC_MUTE,
                KC_SPC,  KC_MPRV, KC_MPLY, KC_MNXT
            ),

/*  BROWSER
       ┌────┬────┬────┬────┐  MEDIA|DISCORD   Back|Fwd
       │Home│Srch│Favs│Find│    ┌────┐         ┌────┐
       ├────┼────┼────┼────┤    │Togg│         │Home│
       │Refr│FlSc│Srce│DVew│    └────┘         └────┘
       ├────┼────┼────┼────┤
       │Refr│Stop│Back│Fwd │         Tabs-|Tabs+
       ├────┼────┼────┼────┤           ┌────┐
       │nTab│nWin│Addr│rTab│           │NTab│
       └────┴────┴────┴────┘           └────┘
*/
    [BROWSER] = LAYOUT(
                KC_WHOM, KC_WSCH, KC_WFAV, C(KC_F), RM_TOGG,
                KC_F5,   KC_F11,  C(KC_U), KC_F12,  KC_WHOM,
                KC_WREF, KC_WSTP, KC_WBAK, KC_WFWD, C(KC_TAB),
                C(KC_T), C(KC_N), KC_F6,   C(S(KC_T))
            ),

/*  DISCORD
       ┌────┬────┬────┬────┐BROWSER|MOUSE     Vol-|Vol+
       │Esc │Reac│DMs │Unrd│    ┌────┐         ┌────┐
       ├────┼────┼────┼────┤    │Togg│         │Mute│
       │Svr-│Ch- │ChU-│PgUp│    └────┘         └────┘
       ├────┼────┼────┼────┤
       │Svr+│Ch+ │ChU+│PgDn│          WHL↑|WHL↓
       ├────┼────┼────┼────┤           ┌────┐
       │Mtn-│Mtn+│Reac│Curr│           │MS 1│
       └────┴────┴────┴────┘           └────┘
*/
    [DISCORD] = LAYOUT(
                KC_ESC,         KC_PPLS,          C(A(KC_RGHT)), S(KC_PGUP),  RM_TOGG,
                C(A(KC_UP)),    A(KC_UP),         S(A(KC_UP)),   KC_PGUP,     KC_MUTE,
                C(A(KC_DOWN)),  A(KC_DOWN),       S(A(KC_DOWN)), KC_PGDN,     MS_BTN1,
                C(A(S(KC_UP))), C(A(S(KC_DOWN))), KC_PPLS,       S(KC_PGDN)
            ),

/*  MOUSE
       ┌────┬────┬────┬────┐DISCORD|GAME      WHL←|WHL→
       │Btn7│Acl0│Acl1│Acl2│    ┌────┐         ┌────┐
       ├────┼────┼────┼────┤    │Togg│         │MS 3│
       │Btn6│Btn1│Ms↑ │Btn2│    └────┘         └────┘
       ├────┼────┼────┼────┤
       │Btn5│Ms← │Ms↓ │Ms→ │          WHL↑|WHL↓
       ├────┼────┼────┼────┤           ┌────┐
       │Btn4│Btn1│Btn3│Btn2│           │MS 3│
       └────┴────┴────┴────┘           └────┘
*/
    [MOUSE] = LAYOUT(
                MS_BTN7, MS_ACL0, MS_ACL1, MS_ACL2, RM_TOGG,
                MS_BTN6, MS_BTN1, MS_UP,   MS_BTN2, MS_BTN3,
                MS_BTN5, MS_LEFT, MS_DOWN, MS_RGHT, MS_BTN3,
                MS_BTN4, MS_BTN1, MS_BTN3, MS_BTN2
            ),

/*  GAME
       ┌────┬────┬────┬────┐ MOUSE|LIGHT      WHL←|WHL→
       │    │    │    │    │    ┌────┐         ┌────┐
       ├────┼────┼────┼────┤    │Togg│         │    │
       │    │    │    │    │    └────┘         └────┘
       ├────┼────┼────┼────┤
       │    │    │    │    │          WHL↑|WHL↓
       ├────┼────┼────┼────┤           ┌────┐
       │    │    │    │    │           │    │
       └────┴────┴────┴────┘           └────┘
*/
    [GAME] = LAYOUT(
                _______, _______, _______, _______, RM_TOGG,
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______, _______,
                _______, _______, _______, MO(GAME_FN)
            ),

/*  GAME_FN
       ┌────┬────┬────┬────┐  MOUSE|LIGHT     WHL←|WHL→
       │    │    │    │    │    ┌────┐         ┌────┐
       ├────┼────┼────┼────┤    │Togg│         │    │
       │    │    │    │    │    └────┘         └────┘
       ├────┼────┼────┼────┤
       │    │    │    │    │          Vol-|Vol+
       ├────┼────┼────┼────┤           ┌────┐
       │    │    │    │ ▼  │           │Mute│
       └────┴────┴────┴────┘           └────┘
*/
    [GAME_FN] = LAYOUT(
                _______, _______, _______, _______, RM_TOGG,
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______, KC_MUTE,
                _______, _______, _______, KC_TRNS
            ),

/*  LIGHT
       ┌────┬────┬────┬────┐   GAME|NUM       Ani-|Ani+
       │Sat+│Val+│Spd+│Togg│    ┌────┐         ┌────┐
       ├────┼────┼────┼────┤    │Togg│         │Simp│
       │Hue-│Simp│Hue+│Ani+│    └────┘         └────┘
       ├────┼────┼────┼────┤
       │Sat-│Val-│Spd-│Ani-│          Val-|Val+
       ├────┼────┼────┼────┤           ┌────┐
       │Pln │Box │Swrl│Cent│           │Togg│
       └────┴────┴────┴────┘           └────┘
*/
    [LIGHT] = LAYOUT(
                RM_SATU, RM_VALU, RM_SPDU, RM_TOGG, RM_TOGG,
                RM_HUED, SIMPLGT, RM_HUEU, RM_NEXT, SIMPLGT,
                RM_SATD, RM_VALD, RM_SPDD, RM_PREV, RM_TOGG,
                RM_M_PL, RM_M_AM, RM_M_RB, RM_M_CN
            ),
};

const ledmap_color_t PROGMEM ledmap[][MATRIX_ROWS][MATRIX_COLS] = {
    [NUM] = LAYOUT(
                VIOLET, TRNS, TRNS, TRNS, BLACK,
                TRNS,   TRNS, TRNS, TRNS, BLACK,
                TRNS,   TRNS, TRNS, TRNS, BLACK,
                TRNS,  RED,  TRNS, TRNS
            ),
    [WIN] = LAYOUT(
                VIOLET, TRNS,   TRNS,     TRNS,   BLACK,
                TRNS,   TRNS,   TRNS,     VIOLET, BLACK,
                TRNS,   TRNS,   TRNS,     VIOLET, BLACK,
                RED,    WHITE,  ORANGE,   ORANGE
            ),
    [WIN_FN] = LAYOUT(
                CYAN, CYAN, CYAN, CYAN, BLACK,
                CYAN, CYAN, CYAN, CYAN, BLACK,
                CYAN, CYAN, CYAN, CYAN, BLACK,
                CYAN, CYAN, CYAN, CYAN
            ),
    [MAC] = LAYOUT(
                CYAN,    CYAN,    CYAN,    MAGENTA,   BLACK,
                CYAN,    CYAN,    CYAN,    MAGENTA,   BLACK,
                CYAN,    CYAN,    CYAN,    MAGENTA,   BLACK,
                MAGENTA, MAGENTA, MAGENTA, MAGENTA
            ),
    [MAC_FN] = LAYOUT(
                RED, RED, RED, RED,   BLACK,
                RED, RED, RED, RED,   BLACK,
                RED, RED, RED, RED,   BLACK,
                RED, RED, RED, RED
            ),
    [MEDIA] = LAYOUT(
                ORANGE, ORANGE, ORANGE, ORANGE, BLACK,
                ORANGE, ORANGE, ORANGE, ORANGE, BLACK,
                ORANGE, ORANGE, ORANGE, ORANGE, BLACK,
                ORANGE, ORANGE, ORANGE, ORANGE
            ),
    [BROWSER] = LAYOUT(
                TRNS,   TRNS,   TRNS,   TRNS,   TRNS,
                TRNS,   TRNS,   TRNS,   TRNS,   TRNS,
                TRNS,   TRNS,   TRNS,   TRNS,   TRNS,
                TRNS,   TRNS,   TRNS,   TRNS
            ),
    [DISCORD] = LAYOUT(
                TRNS,   TRNS,   TRNS,   TRNS,   TRNS,
                TRNS,   TRNS,   TRNS,   TRNS,   TRNS,
                TRNS,   TRNS,   TRNS,   TRNS,   TRNS,
                WHITE,  WHITE,  WHITE,  WHITE
            ),
    [MOUSE] = LAYOUT(
                VIOLET, VIOLET, VIOLET, VIOLET, TRNS,
                VIOLET, VIOLET, VIOLET, VIOLET, TRNS,
                VIOLET, VIOLET, VIOLET, VIOLET, TRNS,
                VIOLET, VIOLET, VIOLET, VIOLET
            ),
    [GAME] = LAYOUT(
        VIOLET, GREEN,   ORANGE, CYAN,   TRNS,
                MAGENTA, GREEN,  ORANGE, CYAN, TRNS,
                MAGENTA, GREEN,  ORANGE, CYAN, TRNS,
                MAGENTA, GREEN,  ORANGE, CYAN
            ),
    [GAME_FN] = LAYOUT(
                TRNS,   TRNS,   TRNS,   TRNS,   TRNS,
                TRNS,   TRNS,   TRNS,   TRNS,   TRNS,
                TRNS,   TRNS,   TRNS,   TRNS,   TRNS,
                TRNS,   TRNS,   TRNS,   TRNS
            ),
    [LIGHT] = LAYOUT(
                TRNS,   TRNS,   TRNS,   TRNS,   TRNS,
                TRNS,   TRNS,   TRNS,   TRNS,   TRNS,
                TRNS,   TRNS,   TRNS,   TRNS,   TRNS,
                TRNS,   TRNS,   TRNS,   TRNS
            ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [NUM]      = { ENCODER_CCW_CW(TO(LIGHT),   TO(WIN)),     ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN]      = { ENCODER_CCW_CW(TO(NUM),     TO(MAC)),     ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [WIN_FN]   = { ENCODER_CCW_CW(TO(NUM),     TO(MAC)),     ENCODER_CCW_CW(KC_BRID, KC_BRIU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC]      = { ENCODER_CCW_CW(TO(WIN),     TO(MEDIA)),   ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [MAC_FN]   = { ENCODER_CCW_CW(TO(WIN),     TO(MEDIA)),   ENCODER_CCW_CW(KC_SCRL, KC_PAUS), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MEDIA]    = { ENCODER_CCW_CW(TO(MAC),     TO(BROWSER)), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [BROWSER]  = { ENCODER_CCW_CW(TO(MEDIA),   TO(DISCORD)), ENCODER_CCW_CW(KC_WBAK, KC_WFWD), ENCODER_CCW_CW(C(S(KC_TAB)), C(KC_TAB)) },
    [DISCORD]  = { ENCODER_CCW_CW(TO(BROWSER), TO(MOUSE)),   ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [MOUSE]    = { ENCODER_CCW_CW(TO(DISCORD), TO(GAME)),    ENCODER_CCW_CW(MS_WHLL, MS_WHLR), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [GAME]     = { ENCODER_CCW_CW(TO(MOUSE),   TO(LIGHT)),   ENCODER_CCW_CW(MS_WHLL, MS_WHLR), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [GAME_FN]  = { ENCODER_CCW_CW(TO(MOUSE),   TO(LIGHT)),   ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [LIGHT]    = { ENCODER_CCW_CW(TO(GAME),    TO(NUM)),     ENCODER_CCW_CW(RM_PREV, RM_NEXT), ENCODER_CCW_CW(RM_VALD, RM_VALU) },

};
#endif

#ifdef OLED_ENABLE
    bool oled_task_user(void) {
        // oled_write_ln(layers[get_highest_layer(layer_state)], false);
        render_oled_layers();

        return true;
    }
#endif
