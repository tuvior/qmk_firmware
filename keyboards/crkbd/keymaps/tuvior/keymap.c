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
#include "oled/layout.generated.h"
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

#ifdef OLED_ENABLE
static uint8_t  displayed_wpm                         = 0;
static uint8_t  wpm_history[OLED_LAYOUT_HISTORY_SIZE] = {};
static uint32_t wpm_display_timer                     = 0;
static uint32_t wpm_history_timer                     = 0;
static bool     performance_display_dirty             = true;
static bool     wpm_chart_dirty                       = true;
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

static bool is_mac_profile(void) {
  return keymap_config.swap_lctl_lgui && keymap_config.swap_rctl_rgui;
}

static bool is_windows_profile(void) {
  return get_unicode_input_mode() == UNICODE_MODE_WINCOMPOSE;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

static void render_bitmap_P(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const uint8_t *bitmap) {
  for (uint8_t pixel_y = 0; pixel_y < height; pixel_y++) {
    for (uint8_t column = 0; column < width; column++) {
      uint16_t source_index = (pixel_y / 8) * width + column;
      uint8_t  source_byte  = pgm_read_byte(&bitmap[source_index]);
      oled_write_pixel(x + column, y + pixel_y, source_byte & (1 << (pixel_y % 8)));
    }
  }
}

static void clear_pixel_region(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
  for (uint8_t pixel_y = y; pixel_y < y + height; pixel_y++) {
    for (uint8_t column = 0; column < width; column++) {
      oled_write_pixel(x + column, pixel_y, false);
    }
  }
}

static void render_modifier_pair(uint8_t modifiers, uint8_t first_mask, uint8_t second_mask, const char *off_off, const char *on_off, const char *off_on, const char *on_on) {
  if ((modifiers & first_mask) && (modifiers & second_mask)) {
    oled_write_P(on_on, false);
  } else if (modifiers & first_mask) {
    oled_write_P(on_off, false);
  } else if (modifiers & second_mask) {
    oled_write_P(off_on, false);
  } else {
    oled_write_P(off_off, false);
  }
}

static void render_state_display(void) {
  static uint8_t previous_layout      = UINT8_MAX;
  static uint8_t previous_host        = UINT8_MAX;
  static uint8_t previous_layer       = UINT8_MAX;
  static uint8_t previous_modifiers   = UINT8_MAX;
  uint8_t        layout               = get_highest_layer(default_layer_state) == _COLEMAK;
  uint8_t        host                 = is_mac_profile() ? 0 : (is_windows_profile() ? 2 : 1);
  uint8_t        highest_layer        = get_highest_layer(layer_state);
  uint8_t        layer                = highest_layer == _LOWER ? 1 : (highest_layer == _RAISE ? 2 : (highest_layer == _ADJUST ? 3 : 0));
  uint8_t        modifiers            = get_mods() | get_oneshot_mods();

  if (layout == previous_layout && host == previous_host && layer == previous_layer && modifiers == previous_modifiers) {
    return;
  }

  render_bitmap_P(
    OLED_LAYOUT_CORNE_LOGO_X,
    OLED_LAYOUT_CORNE_LOGO_Y,
    OLED_BITMAP_CORNE_LOGO_WIDTH,
    OLED_BITMAP_CORNE_LOGO_HEIGHT,
    oled_bitmap_corne_logo
  );

  if (layout) {
    render_bitmap_P(
      OLED_LAYOUT_LAYOUT_LABEL_X,
      OLED_LAYOUT_LAYOUT_LABEL_Y,
      OLED_BITMAP_LABEL_LAYOUT_COLEMAK_WIDTH,
      OLED_BITMAP_LABEL_LAYOUT_COLEMAK_HEIGHT,
      oled_bitmap_label_layout_colemak
    );
  } else {
    render_bitmap_P(
      OLED_LAYOUT_LAYOUT_LABEL_X,
      OLED_LAYOUT_LAYOUT_LABEL_Y,
      OLED_BITMAP_LABEL_LAYOUT_QWERTY_WIDTH,
      OLED_BITMAP_LABEL_LAYOUT_QWERTY_HEIGHT,
      oled_bitmap_label_layout_qwerty
    );
  }

  if (host == 0) {
    render_bitmap_P(OLED_LAYOUT_OS_BITMAP_X, OLED_LAYOUT_OS_BITMAP_Y, OLED_BITMAP_OS_MACOS_WIDTH, OLED_BITMAP_OS_MACOS_HEIGHT, oled_bitmap_os_macos);
  } else if (host == 2) {
    render_bitmap_P(OLED_LAYOUT_OS_BITMAP_X, OLED_LAYOUT_OS_BITMAP_Y, OLED_BITMAP_OS_WINDOWS_WIDTH, OLED_BITMAP_OS_WINDOWS_HEIGHT, oled_bitmap_os_windows);
  } else {
    render_bitmap_P(OLED_LAYOUT_OS_BITMAP_X, OLED_LAYOUT_OS_BITMAP_Y, OLED_BITMAP_OS_LINUX_WIDTH, OLED_BITMAP_OS_LINUX_HEIGHT, oled_bitmap_os_linux);
  }

  oled_set_cursor(OLED_LAYOUT_LAYER_COLUMN, OLED_LAYOUT_LAYER_ROW);
  if (layer == 1) {
    oled_write_P(oled_layer_lower, false);
    render_bitmap_P(OLED_LAYOUT_LAYER_LABEL_X, OLED_LAYOUT_LAYER_LABEL_Y, OLED_BITMAP_LABEL_LAYER_LOWER_WIDTH, OLED_BITMAP_LABEL_LAYER_LOWER_HEIGHT, oled_bitmap_label_layer_lower);
  } else if (layer == 2) {
    oled_write_P(oled_layer_raise, false);
    render_bitmap_P(OLED_LAYOUT_LAYER_LABEL_X, OLED_LAYOUT_LAYER_LABEL_Y, OLED_BITMAP_LABEL_LAYER_RAISE_WIDTH, OLED_BITMAP_LABEL_LAYER_RAISE_HEIGHT, oled_bitmap_label_layer_raise);
  } else if (layer == 3) {
    oled_write_P(oled_layer_adjust, false);
    render_bitmap_P(OLED_LAYOUT_LAYER_LABEL_X, OLED_LAYOUT_LAYER_LABEL_Y, OLED_BITMAP_LABEL_LAYER_ADJUST_WIDTH, OLED_BITMAP_LABEL_LAYER_ADJUST_HEIGHT, oled_bitmap_label_layer_adjust);
  } else {
    oled_write_P(oled_layer_default, false);
    render_bitmap_P(OLED_LAYOUT_LAYER_LABEL_X, OLED_LAYOUT_LAYER_LABEL_Y, OLED_BITMAP_LABEL_LAYER_DEFAULT_WIDTH, OLED_BITMAP_LABEL_LAYER_DEFAULT_HEIGHT, oled_bitmap_label_layer_default);
  }

  oled_set_cursor(OLED_LAYOUT_GUI_ALT_COLUMN, OLED_LAYOUT_GUI_ALT_ROW);
  render_modifier_pair(modifiers, MOD_MASK_GUI, MOD_MASK_ALT, oled_gui_alt_off_off, oled_gui_alt_on_off, oled_gui_alt_off_on, oled_gui_alt_on_on);
  oled_set_cursor(OLED_LAYOUT_CTRL_SHIFT_COLUMN, OLED_LAYOUT_CTRL_SHIFT_ROW);
  render_modifier_pair(modifiers, MOD_MASK_CTRL, MOD_MASK_SHIFT, oled_ctrl_shift_off_off, oled_ctrl_shift_on_off, oled_ctrl_shift_off_on, oled_ctrl_shift_on_on);

  previous_layout    = layout;
  previous_host      = host;
  previous_layer     = layer;
  previous_modifiers = modifiers;
}

static uint8_t digit_count(uint8_t value) {
  if (value >= 100) {
    return 3;
  }
  if (value >= 10) {
    return 2;
  }
  return 1;
}

static void render_large_number(uint8_t value, uint8_t y) {
  uint8_t digits[3] = {};
  uint8_t count     = digit_count(value);
  uint8_t scale     = count <= 2 ? 3 : 2;
  uint8_t width     = count * OLED_LAYOUT_DIGIT_WIDTH * scale + count - 1;
  uint8_t x         = (OLED_LAYOUT_PIXEL_WIDTH - width) / 2;

  clear_pixel_region(0, y, OLED_LAYOUT_PIXEL_WIDTH, 24);

  for (uint8_t index = count; index > 0; index--) {
    digits[index - 1] = value % 10;
    value /= 10;
  }

  y += (24 - OLED_LAYOUT_DIGIT_HEIGHT * scale) / 2;
  for (uint8_t index = 0; index < count; index++) {
    for (uint8_t row = 0; row < OLED_LAYOUT_DIGIT_HEIGHT; row++) {
      uint8_t pixels = pgm_read_byte(&oled_digit_rows[digits[index]][row]);

      for (uint8_t column = 0; column < OLED_LAYOUT_DIGIT_WIDTH; column++) {
        if (!(pixels & (1 << column))) {
          continue;
        }

        for (uint8_t offset_y = 0; offset_y < scale; offset_y++) {
          for (uint8_t offset_x = 0; offset_x < scale; offset_x++) {
            oled_write_pixel(x + column * scale + offset_x, y + row * scale + offset_y, true);
          }
        }
      }
    }
    x += OLED_LAYOUT_DIGIT_WIDTH * scale + 1;
  }
}

static uint8_t chart_y(uint8_t value, uint8_t scale_max) {
  uint8_t bottom     = OLED_LAYOUT_CHART_Y + OLED_LAYOUT_CHART_HEIGHT - 2;
  uint8_t plot_range = OLED_LAYOUT_CHART_HEIGHT - 3;

  if (value > scale_max) {
    value = scale_max;
  }
  return bottom - (uint16_t)value * plot_range / scale_max;
}

static void render_wpm_chart(void) {
  uint8_t scale_max = 60;
  uint8_t previous_y;

  for (uint8_t index = 0; index < OLED_LAYOUT_HISTORY_SIZE; index++) {
    if (wpm_history[index] > scale_max) {
      scale_max = wpm_history[index];
    }
  }

  clear_pixel_region(OLED_LAYOUT_CHART_X, OLED_LAYOUT_CHART_Y, OLED_LAYOUT_CHART_WIDTH, OLED_LAYOUT_CHART_HEIGHT);

  for (uint8_t x = OLED_LAYOUT_CHART_X; x < OLED_LAYOUT_CHART_X + OLED_LAYOUT_CHART_WIDTH; x += 2) {
    oled_write_pixel(x, OLED_LAYOUT_CHART_Y + OLED_LAYOUT_CHART_HEIGHT - 1, true);
  }

  previous_y = chart_y(wpm_history[0], scale_max);
  oled_write_pixel(OLED_LAYOUT_CHART_X, previous_y, true);
  for (uint8_t index = 1; index < OLED_LAYOUT_HISTORY_SIZE; index++) {
    uint8_t current_y = chart_y(wpm_history[index], scale_max);
    int8_t  step      = current_y >= previous_y ? 1 : -1;

    for (int16_t y = previous_y; y != (int16_t)current_y + step; y += step) {
      oled_write_pixel(OLED_LAYOUT_CHART_X + index, y, true);
    }
    previous_y = current_y;
  }
}

static void update_performance_data(void) {
  uint8_t wpm = get_current_wpm();

  if (timer_elapsed32(wpm_display_timer) >= 250) {
    if (wpm != displayed_wpm) {
      displayed_wpm             = wpm;
      performance_display_dirty = true;
    }
    if (wpm > maxWPM) {
      maxWPM                    = wpm;
      performance_display_dirty = true;
    }
    wpm_display_timer = timer_read32();
  }

  if (timer_elapsed32(wpm_history_timer) >= 1000) {
    memmove(wpm_history, wpm_history + 1, OLED_LAYOUT_HISTORY_SIZE - 1);
    wpm_history[OLED_LAYOUT_HISTORY_SIZE - 1] = wpm;
    wpm_history_timer                         = timer_read32();
    wpm_chart_dirty                           = true;
  }
}

static void render_performance_display(void) {
  if (performance_display_dirty) {
    render_large_number(displayed_wpm, OLED_LAYOUT_WPM_NUMBER_Y);
    render_bitmap_P(OLED_LAYOUT_WPM_LABEL_X, OLED_LAYOUT_WPM_LABEL_Y, OLED_BITMAP_LABEL_WPM_WIDTH, OLED_BITMAP_LABEL_WPM_HEIGHT, oled_bitmap_label_wpm);
    render_bitmap_P(OLED_LAYOUT_PEAK_LABEL_X, OLED_LAYOUT_PEAK_LABEL_Y, OLED_BITMAP_LABEL_PEAK_WIDTH, OLED_BITMAP_LABEL_PEAK_HEIGHT, oled_bitmap_label_peak);
    render_large_number(maxWPM, OLED_LAYOUT_PEAK_NUMBER_Y);
    performance_display_dirty = false;
  }

  if (wpm_chart_dirty) {
    render_wpm_chart();
    wpm_chart_dirty = false;
  }
}

bool oled_task_user(void) {
  update_performance_data();

  if (is_keyboard_master()) {
    render_state_display();
  } else {
    render_performance_display();
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
    case AIGU:
      if (is_windows_profile()) {
        return true;
      }
      if (record->event.pressed) {
        tap_code16(RALT(is_mac_profile() ? KC_K : KC_F));
      }
      return false;
    case GRAVE:
      if (is_windows_profile()) {
        return true;
      }
      if (record->event.pressed) {
        tap_code16(RALT(is_mac_profile() ? KC_GRV : KC_S));
      }
      return false;
    case CIRC:
      if (record->event.pressed) {
        if (is_windows_profile()) {
          register_code(KC_RALT);
          tap_code(KC_6);
          unregister_code(KC_RALT);
        } else {
          tap_code16(RALT(is_mac_profile() ? KC_L : KC_X));
        }
      }
      return false;
    case UMLAUT:
      if (is_windows_profile()) {
        return true;
      }
      if (record->event.pressed) {
        tap_code16(RALT(is_mac_profile() ? KC_I : KC_G));
      }
      return false;
    case CCDL:
      if (is_windows_profile()) {
        return true;
      }
      if (record->event.pressed) {
        tap_code16(RALT(KC_C));
      }
      return false;
    case S_UPL:
      if (!is_mac_profile()) {
        return true;
      }
      if (record->event.pressed) {
        // macOS: open the Screenshot app (the closest equivalent to upload/options).
        tap_code16(LGUI(LSFT(KC_5)));
      }
      return false;
    case S_WIN:
      if (!is_mac_profile()) {
        return true;
      }
      if (record->event.pressed) {
        // macOS window capture is Command-Shift-4 followed by Space.
        tap_code16(LGUI(LSFT(KC_4)));
        tap_code(KC_SPC);
      }
      return false;
    case S_SCR:
      if (!is_mac_profile()) {
        return true;
      }
      if (record->event.pressed) {
        tap_code16(LGUI(LSFT(KC_3)));
      }
      return false;
    case KC_PSCR:
      if (!is_mac_profile()) {
        return true;
      }
      if (record->event.pressed) {
        tap_code16(LGUI(LSFT(KC_4)));
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
