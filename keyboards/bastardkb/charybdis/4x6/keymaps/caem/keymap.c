/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2026 Caem <me@caem.dev> (@caemputer)
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

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_FN,
};

enum td_custom_actions {
    TD_BTN3_SCRL = 0,
};

static bool drgscrl_active = true;
void td_mb_scrl_finish(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (!state->pressed) {
            register_code(KC_BTN3);
        } else {
            drgscrl_active = true;
            charybdis_set_pointer_dragscroll_enabled(true);
        }
    }
}

void td_mb_scrl_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (!drgscrl_active) {
            unregister_code(KC_BTN3);
        } else {
            charybdis_set_pointer_dragscroll_enabled(false);
            drgscrl_active = false;
        }
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_BTN3_SCRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_mb_scrl_finish, td_mb_scrl_reset)
};

#define BTN3_SCRL TD(TD_BTN3_SCRL)
#define FN MO(LAYER_FN)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_RALT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
            FN,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_LGUI,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                BTN3_SCRL, KC_BTN1, KC_BTN2,    KC_BSPC,  KC_SPACE,
                                           KC_LALT, KC_LCTL,    KC_ENT
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_FN] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, KC_MNXT, KC_VOLU,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_GRV,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_VOLD,    KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  KC_EQL, _______, // You can take the man out of vim, but you can't take vim out of the man
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_PSCR, XXXXXXX, XXXXXXX, KC_MPLY, KC_MUTE,    XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, _______,
                                           _______, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on
