/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keycode_config.h"
#include "utils.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3_(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,   ________________QWERTY_L1________________,                        ________________QWERTY_R1________________, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CTL_ESC,   ________________QWERTY_L2________________,                        ________________QWERTY_R2________________, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   ________________QWERTY_L3________________,                        ________________QWERTY_R3________________, SC_SENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_LGUI,  LOWER,    NAV_DEL,      KC_SPC, RAISE, KC_LALT
                                      //`--------------------------'  `--------------------------'

  ),

  [_COLEMAK] = LAYOUT_split_3x6_3_(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,   ________________COLEMAK_L1_______________,                        ________________COLEMAK_R1_______________, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   ________________COLEMAK_L2_______________,                        ________________COLEMAK_R2_______________, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   ________________COLEMAK_L3_______________,                        ________________COLEMAK_R3_______________, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX,                      KC_SLSH, KC_7,    KC_8,    KC_9,    KC_MINS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, XXXXXXX,                      KC_EQL,  KC_4,    KC_5,    KC_6,    KC_PLUS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX,                      KC_0,    KC_1,    KC_2,    KC_3,    KC_DOT,  _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  _______,   _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_GRV,  KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_LABK,                      KC_RABK, KC_GRV , KC_BSLS, KC_TILD, BTC    , _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, ETH    ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, AIGU,    GRAVE,      CIRC, UMLAUT,  XXXXXXX,                      XXXXXXX, CCDL,    KC_PIPE, KC_UNDS, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, S_UPL,   S_WIN,   S_SCR,   KC_PSCR,   _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN, KC_END,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      TMUX_PWIN, TMUX_PPANE, TMUX_NPANE, TMUX_NWIN, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3_(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       QK_BOOT, QWERTY, COLEMAK, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, UC_MAC,  UC_LINX, UC_WINC, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, OS_MAC,  OS_LNX,  OS_WIN,  XXXXXXX, XXXXXXX,                      XXXXXXX, __________MEDIA__________, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, __________VOLUME_________, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

uint8_t maxWPM = 0;

char wpm_str[5] = {};
char max_wpm_str[5] = {};

#ifdef OLED_ENABLE
static uint32_t wpm_display_timer = 0;
#endif

static void set_host_profile(bool mac_mode, uint8_t unicode_mode) {
  eeconfig_read_keymap(&keymap_config);
  keymap_config.swap_lctl_lgui = mac_mode;
  keymap_config.swap_rctl_rgui = mac_mode;
  eeconfig_update_keymap(&keymap_config);
  set_unicode_input_mode(unicode_mode);
}

static void tap_tmux_key(uint16_t keycode) {
  tap_code16(TMUX_PREFIX);
  tap_code16(keycode);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

void render_space(void) {
  oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
  static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
  static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
  static const char PROGMEM gui_on_1[]  = {0x8d, 0x8e, 0};
  static const char PROGMEM gui_on_2[]  = {0xad, 0xae, 0};

  static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
  static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
  static const char PROGMEM alt_on_1[]  = {0x8f, 0x90, 0};
  static const char PROGMEM alt_on_2[]  = {0xaf, 0xb0, 0};

  // fillers between the modifier icons bleed into the icon frames
  static const char PROGMEM off_off_1[] = {0xc5, 0};
  static const char PROGMEM off_off_2[] = {0xc6, 0};
  static const char PROGMEM on_off_1[]  = {0xc7, 0};
  static const char PROGMEM on_off_2[]  = {0xc8, 0};
  static const char PROGMEM off_on_1[]  = {0xc9, 0};
  static const char PROGMEM off_on_2[]  = {0xca, 0};
  static const char PROGMEM on_on_1[]   = {0xcb, 0};
  static const char PROGMEM on_on_2[]   = {0xcc, 0};

  if (modifiers & MOD_MASK_GUI) {
    oled_write_P(gui_on_1, false);
  } else {
    oled_write_P(gui_off_1, false);
  }

  if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
    oled_write_P(on_on_1, false);
  } else if (modifiers & MOD_MASK_GUI) {
    oled_write_P(on_off_1, false);
  } else if (modifiers & MOD_MASK_ALT) {
    oled_write_P(off_on_1, false);
  } else {
    oled_write_P(off_off_1, false);
  }

  if (modifiers & MOD_MASK_ALT) {
    oled_write_P(alt_on_1, false);
  } else {
    oled_write_P(alt_off_1, false);
  }

  if (modifiers & MOD_MASK_GUI) {
    oled_write_P(gui_on_2, false);
  } else {
    oled_write_P(gui_off_2, false);
  }

  if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
    oled_write_P(on_on_2, false);
  } else if (modifiers & MOD_MASK_GUI) {
    oled_write_P(on_off_2, false);
  } else if (modifiers & MOD_MASK_ALT) {
    oled_write_P(off_on_2, false);
  } else {
    oled_write_P(off_off_2, false);
  }

  if (modifiers & MOD_MASK_ALT) {
    oled_write_P(alt_on_2, false);
  } else {
    oled_write_P(alt_off_2, false);
  }
}

void render_wpm(void) {
  oled_write_ln(wpm_str, false);
}

void render_max_wpm(void) {
  oled_write_ln(max_wpm_str, false);
}

void update_wpm_display(void) {
  uint8_t wpm = get_current_wpm();

  if (wpm > maxWPM) maxWPM = wpm;

  if (timer_elapsed32(wpm_display_timer) < 500) {
    return;
  }

  snprintf(wpm_str, sizeof(wpm_str), "%4d", wpm);
  snprintf(max_wpm_str, sizeof(max_wpm_str), "%4d", maxWPM);
  wpm_display_timer = timer_read32();
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
  static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
  static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
  static const char PROGMEM ctrl_on_1[]  = {0x91, 0x92, 0};
  static const char PROGMEM ctrl_on_2[]  = {0xb1, 0xb2, 0};

  static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
  static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
  static const char PROGMEM shift_on_1[]  = {0xcd, 0xce, 0};
  static const char PROGMEM shift_on_2[]  = {0xcf, 0xd0, 0};

  // fillers between the modifier icons bleed into the icon frames
  static const char PROGMEM off_off_1[] = {0xc5, 0};
  static const char PROGMEM off_off_2[] = {0xc6, 0};
  static const char PROGMEM on_off_1[]  = {0xc7, 0};
  static const char PROGMEM on_off_2[]  = {0xc8, 0};
  static const char PROGMEM off_on_1[]  = {0xc9, 0};
  static const char PROGMEM off_on_2[]  = {0xca, 0};
  static const char PROGMEM on_on_1[]   = {0xcb, 0};
  static const char PROGMEM on_on_2[]   = {0xcc, 0};

  if (modifiers & MOD_MASK_CTRL) {
    oled_write_P(ctrl_on_1, false);
  } else {
    oled_write_P(ctrl_off_1, false);
  }

  if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
    oled_write_P(on_on_1, false);
  } else if (modifiers & MOD_MASK_CTRL) {
    oled_write_P(on_off_1, false);
  } else if (modifiers & MOD_MASK_SHIFT) {
    oled_write_P(off_on_1, false);
  } else {
    oled_write_P(off_off_1, false);
  }

  if (modifiers & MOD_MASK_SHIFT) {
    oled_write_P(shift_on_1, false);
  } else {
    oled_write_P(shift_off_1, false);
  }

  if (modifiers & MOD_MASK_CTRL) {
    oled_write_P(ctrl_on_2, false);
  } else {
    oled_write_P(ctrl_off_2, false);
  }

  if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
    oled_write_P(on_on_2, false);
  } else if (modifiers & MOD_MASK_CTRL) {
    oled_write_P(on_off_2, false);
  } else if (modifiers & MOD_MASK_SHIFT) {
    oled_write_P(off_on_2, false);
  } else {
    oled_write_P(off_off_2, false);
  }

  if (modifiers & MOD_MASK_SHIFT) {
    oled_write_P(shift_on_2, false);
  } else {
    oled_write_P(shift_off_2, false);
  }
}

void render_logo(void) {
  static const char PROGMEM corne_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
  oled_write_P(corne_logo, false);
  oled_write_P(PSTR("corne"), false);
}

void render_layer_state(void) {
  static const char PROGMEM default_layer[] = {0x20, 0x94, 0x95, 0x96, 0x20, 0x20, 0xb4, 0xb5, 0xb6, 0x20, 0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
  static const char PROGMEM raise_layer[]   = {0x20, 0x97, 0x98, 0x99, 0x20, 0x20, 0xb7, 0xb8, 0xb9, 0x20, 0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
  static const char PROGMEM lower_layer[]   = {0x20, 0x9a, 0x9b, 0x9c, 0x20, 0x20, 0xba, 0xbb, 0xbc, 0x20, 0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
  static const char PROGMEM adjust_layer[]  = {0x20, 0x9d, 0x9e, 0x9f, 0x20, 0x20, 0xbd, 0xbe, 0xbf, 0x20, 0x20, 0xdd, 0xde, 0xdf, 0x20, 0};

  switch(get_highest_layer(layer_state)) {
    case _LOWER:
      oled_write_P(lower_layer, false);
      break;
    case _RAISE:
      oled_write_P(raise_layer, false);
      break;
    case _ADJUST:
      oled_write_P(adjust_layer, false);
      break;
    default:
      oled_write_P(default_layer, false);
  }
}

void render_status_main(void) {
  render_logo();
  render_space();
  render_layer_state();
  render_space();
  render_mod_status_gui_alt(get_mods() | get_oneshot_mods());
  render_mod_status_ctrl_shift(get_mods() | get_oneshot_mods());
  render_space();
  render_wpm();
}

void render_status_secondary(void) {
  render_logo();
  render_space();
  render_layer_state();
  render_space();
  render_mod_status_gui_alt(get_mods() | get_oneshot_mods());
  render_mod_status_ctrl_shift(get_mods() | get_oneshot_mods());
  render_space();
  render_max_wpm();
}

bool oled_task_user(void) {
  update_wpm_display();

  if (is_keyboard_master()) {
    render_status_main();
  } else {
    render_status_secondary();
  }

  return false;
}

#endif // OLED_ENABLE


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case CIRC:
      if (record->event.pressed) {
        register_code(KC_RALT);
        tap_code(KC_6);
        unregister_code(KC_RALT);
      }
      return false;
    case OS_MAC:
      if (record->event.pressed) {
        set_host_profile(true, UNICODE_MODE_MACOS);
      }
      return false;
    case OS_LNX:
      if (record->event.pressed) {
        set_host_profile(false, UNICODE_MODE_LINUX);
      }
      return false;
    case OS_WIN:
      if (record->event.pressed) {
        set_host_profile(false, UNICODE_MODE_WINCOMPOSE);
      }
      return false;
    case TMUX_PWIN:
      if (record->event.pressed) {
        tap_tmux_key(KC_P);
      }
      return false;
    case TMUX_PPANE:
      if (record->event.pressed) {
        tap_tmux_key(KC_SCLN);
      }
      return false;
    case TMUX_NPANE:
      if (record->event.pressed) {
        tap_tmux_key(KC_O);
      }
      return false;
    case TMUX_NWIN:
      if (record->event.pressed) {
        tap_tmux_key(KC_N);
      }
      return false;
    default:
      return true;
  }
}
