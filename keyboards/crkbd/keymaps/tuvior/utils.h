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
  CIRC
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

#define NXT_TRM LSFT(KC_RIGHT)
#define PRV_TRM LSFT(KC_LEFT)
#define NXT_STR LALT(KC_RIGHT)
#define PRV_STR LALT(KC_LEFT)

// Screenshots
#define S_UPL LCTL(LSFT(KC_1))
#define S_WIN LCTL(LSFT(KC_2))
#define S_SCR LCTL(LSFT(KC_3))
#define S_REG LCTL(LSFT(KC_4))

#define AIGU RALT(KC_QUOT)
#define GRAVE RALT(KC_GRV)


// Accented characters
enum unicode_names {
  E_GRAVE,
  E_GRAVE_U,
  E_AIGU,
  E_AIGU_U,
  A_GRAVE,
  A_GRAVE_U,
  E_CIRC,
  E_CIRC_U,
  A_CIRC,
  A_CIRC_U,
  I_CIRC,
  I_CIRC_U,
  C_CEDIL,
  C_CEDIL_U
};

const uint32_t PROGMEM unicode_map[] = {
  [E_GRAVE]  = 0x00E8,          // è
  [E_GRAVE_U]  = 0x00E8 - 32,   // È
  [E_AIGU]  = 0x00E9,           // é
  [E_AIGU_U]  = 0x00E9 - 32,    // É
  [A_GRAVE]  = 0x00E0,          // à
  [A_GRAVE_U]  = 0x00E0 - 32,   // À
  [E_CIRC]  = 0x00EA,           // ê
  [E_CIRC_U]  = 0x00EA - 32,    // Ê
  [A_CIRC]  = 0x00E2,           // â
  [A_CIRC_U]  = 0x00E2 - 32,    // Â
  [I_CIRC]  = 0x00EE,           // î
  [I_CIRC_U]  = 0x00EE - 32,    // Î
  [C_CEDIL]  = 0x00E7,          // ç
  [C_CEDIL_U]  = 0x00E7 - 32,   // Ç
};

#define ULETTER(L) XP(L, (L + 1))

#define EGRV ULETTER(E_GRAVE)
#define EAIG ULETTER(E_AIGU)
#define AGRV ULETTER(A_GRAVE)
#define ECRC ULETTER(E_CIRC)
#define ACRC ULETTER(A_CIRC)
#define ICRC ULETTER(I_CIRC)
#define CCDL ULETTER(C_CEDIL)


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
