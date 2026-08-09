#pragma once

#include "quantum.h"

enum layers {
  _QWERTY,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _NAV,
  _ADJUST,
};

enum keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  CIRC,
  OS_MAC,
  OS_LNX,
  OS_WIN,
  TMUX_PWIN,
  TMUX_PPANE,
  TMUX_NPANE,
  TMUX_NWIN
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define NUMPAD MO(_NUMPAD)

// Ctrl mod taps
#define CTL_ESC CTL_T(KC_ESC)
#define CTL_LBR CTL_T(KC_LBRC)
#define CTL_RBR CTL_T(KC_RBRC)
#define CTL_LPR CTL_T(KC_LPRN)
#define CTL_RPR CTL_T(KC_LPRN)

// GUI mod taps
#define GUI_LCB GUI_T(KC_RBRC)
#define GUI_ROB GUI_T(KC_LBRC)

// Shift - Caps
#define SFT_CPS SFT_T(KC_CAPS)

// Hyper []
#define HYPER_L ALL_T(KC_LBRC)
#define HYPER_R ALL_T(KC_RBRC)

// One-shot shift
#define CAPITAL OSM(MOD_LSFT)

// Nav
#define NAV_SCL LT(_NAV, KC_SCLN)
#define NAV_O LT(_NAV, KC_O)
#define NAV_DEL LT(_NAV, KC_DEL)

#define TMUX_PREFIX LCTL(KC_N)

// Screenshots
#define S_UPL LCTL(LSFT(KC_1))
#define S_WIN LCTL(LSFT(KC_2))
#define S_SCR LCTL(LSFT(KC_3))

// Windows English International accents
#define AIGU RALT(KC_QUOT)
#define GRAVE RALT(KC_GRV)
#define UMLAUT RALT(LSFT(KC_QUOT))

// Symbols that still require OS-specific Unicode input
enum unicode_names {
  C_CEDIL,
  C_CEDIL_U,
  BTCS,
  ETHS,
};

const uint32_t PROGMEM unicode_map[] = {
  [C_CEDIL] = 0x00E7,           // ç
  [C_CEDIL_U] = 0x00C7,         // Ç
  [BTCS] = 0x20BF,              // ₿
  [ETHS] = 0x039E,              // Ξ
};

#define CCDL UP(C_CEDIL, C_CEDIL_U)
#define BTC UM(BTCS)
#define ETH UM(ETHS)

#define LAYOUT_split_3x6_3_(...) LAYOUT_split_3x6_3(__VA_ARGS__)

// Letter rows
#define ________________QWERTY_L1________________ KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define ________________QWERTY_L2________________ KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define ________________QWERTY_L3________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define ________________QWERTY_R1________________ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define ________________QWERTY_R2________________ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define ________________QWERTY_R3________________ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define ________________COLEMAK_L1_______________ KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define ________________COLEMAK_L2_______________ KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define ________________COLEMAK_L3_______________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define ________________COLEMAK_R1_______________ KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define ________________COLEMAK_R2_______________ KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define ________________COLEMAK_R3_______________ KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define __________VOLUME_________ KC_VOLD, KC_VOLU, KC_MUTE
#define __________MEDIA__________ KC_MPRV, KC_MPLY, KC_MNXT
