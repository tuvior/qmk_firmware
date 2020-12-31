#ifdef QMK_KEYBOARD_H
  #include QMK_KEYBOARD_H
  #include "utils.h"
#else
  #define UNICODEMAP_ENABLE
  #define LEADER_ENABLE
  #define STENO_ENABLE
  #include "../niu_mini.h"
  #include "../config.h"
  #include "config.h"
  #include "utils.h"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty Base
    * ,-----------------------------------------------------------------------------------.
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bkspc|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctl/E|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |EntSft|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Hyper|  GUI | Lead |  Alt |Lower |    Space    |Raise |  Alt | Caps |  GUI |Numpad|
    * `-----------------------------------------------------------------------------------'
    */
  [_QWERTY] = LAYOUT_planck_mit_(
      KC_TAB,  ________________QWERTY_L1________________,   ________________QWERTY_R1________________, KC_BSPC,
      CTL_ESC, ________________QWERTY_L2________________,   ________________QWERTY_R2________________, KC_QUOT,
      KC_LSFT, ________________QWERTY_L3________________,   ________________QWERTY_R3________________, KC_SFTENT,
      HYPER_L, GUI_LCB, KC_LEAD, KC_LALT, LOWER,       KC_SPC,     RAISE,   KC_RALT, KC_CAPS, GUI_ROB, NUMPAD
  ),

  /* Colemak Base
    * ,-----------------------------------------------------------------------------------.
    * |      |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
  [_COLEMAK] = LAYOUT_planck_mit_(
    _______, ________________COLEMAK_L1_______________,   ________________COLEMAK_R1_______________,  _______,
    _______, ________________COLEMAK_L2_______________,   ________________COLEMAK_R2_______________,  _______,
    _______, ________________COLEMAK_L3_______________,   ________________COLEMAK_R3_______________,  _______,
    _______, _______, _______, _______, _______,     _______,    _______, _______, _______, _______,  _______
  ),

  /* RotMG Override
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |RotMG |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
  [_ROTMG_RAISE] = LAYOUT_planck_mit(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,     _______,      ROTMG,   _______, _______, _______, _______
  ),

  /* RotMG
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      |      |      |      |   ]  |   7  |   8  |   9  |   \  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |   [  |   4  |   5  |   6  |   =  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |   0  |   1  |   2  |   3  |   -  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | EXIT |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
  [_ROTMG] = LAYOUT_planck_mit(
    _______, _______, _______, _______, _______, _______, KC_RBRC, KC_P7,   KC_P8,   KC_P9,   KC_BSLS, _______,
    _______, _______, _______, _______, _______, _______, KC_LBRC, KC_P4,   KC_P5,   KC_P6,   KC_EQL,  _______,
    _______, _______, _______, _______, _______, _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_MINS, _______,
    ROTMG_L, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
  ),

    /* Numpad
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      |      |      |      |   ]  |   7  |   8  |   9  |   \  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |   [  |   4  |   5  |   6  |   =  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |   0  |   1  |   2  |   3  |   -  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
  [_NUMPAD] = LAYOUT_planck_mit(
    _______, _______, _______, _______, _______, _______, KC_RBRC, KC_P7,   KC_P8,   KC_P9,   KC_BSLS, _______,
    _______, _______, _______, _______, _______, _______, KC_LBRC, KC_P4,   KC_P5,   KC_P6,   KC_EQL,  _______,
    _______, _______, _______, _______, _______, _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_MINS, _______,
    _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
  ),

  /* Lower
    * ,-----------------------------------------------------------------------------------.
    * |      |  F1  |  F2  |  F3  |  F4  |      |   /  |   7  |   8  |   9  |   -  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |  F5  |  F6  |  F7  |  F8  |      |   =  |   4  |   5  |   6  |   +  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |  F9  |  F10 |  F11 |  F12 |      |   0  |   1  |   2  |   3  |   .  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |  Backspace  |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
  [_LOWER] = LAYOUT_planck_mit(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX, KC_SLSH, KC_7,    KC_8,    KC_9,    KC_MINS, _______,
      _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX, KC_EQL,  KC_4,    KC_5,    KC_6,    KC_PLUS, _______,
      _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, KC_0,    KC_1,    KC_2,    KC_3,    KC_DOT,  _______,
      _______, _______, _______, _______, _______,      KC_BSPC,     _______, _______, _______, _______, _______
  ),

  /* Raise
    * ,-----------------------------------------------------------------------------------.
    * |   `  |   [  |   ]  |   {  |   }  |   <  |   >  |   `  |   \  |   ~  |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |   d` |   d´ |   d^ |      |      |      |   Ç  |   |  |   _  |   +  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |    Delete   |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
  [_RAISE] = LAYOUT_planck_mit(
      KC_GRV,  KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_LABK, KC_RABK, KC_GRV,  KC_BSLS, KC_TILD, XXXXXXX, _______,
      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
      _______, GRAVE,   AIGU,    CIRC,    XXXXXXX, XXXXXXX, XXXXXXX, CCDL,    KC_PIPE, KC_UNDS, XXXXXXX, _______,
      _______, _______, _______, _______, _______,     KC_DELETE,    _______, _______, _______, _______, _______
  ),

    /* Navigation
    * ,-----------------------------------------------------------------------------------.
    * |      |Upload|CapWin|CapScr|CapReg|      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      | Home | PgUp | PgDn | End  | Left | Down |  Up  |Right |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |< Term|< STer|Ster >|Term >|      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
  [_NAV] = LAYOUT_planck_mit(
    _______, S_UPL,   S_WIN,   S_SCR,   S_REG,   _______, _______, _______, _______, _______, _______, _______,
    _______, XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, _______,
    _______, _______, _______, _______, _______, _______, PRV_TRM, PRV_STR, NXT_STR, NXT_TRM, _______, _______,
    _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
  ),

    /* Camel case
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Exit |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |     (⇧)     |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
  [_CAMEL] = LAYOUT_planck_mit(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    STCH_EX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,     CAPITAL,      _______, _______, _______, _______, _______
  ),

  /* Kebab case
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Exit |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      -      |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
  [_KEBAB] = LAYOUT_planck_mit(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    STCH_EX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,      KC_MINS,     _______, _______, _______, _______, _______
  ),

  /* Snake case
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Exit |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      _      |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
  [_SNAKE] = LAYOUT_planck_mit(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    STCH_EX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,      KC_UNDS,     _______, _______, _______, _______, _______
  ),

  /* Stenography
    * ,-----------------------------------------------------------------------------------.
    * |      |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |   T  |   P  |   H  |      |      |   F  |   P  |   L  |   T  |   D  |
    * |------|   S  |------+------+------|   *  |   *  |------+------+------+------+------|
    * |      |      |   K  |   W  |   R  |      |      |   R  |   B  |   G  |   S  |   Z  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Exit |      |  Alt |   A  |   O  |             |   E  |   U  |  GUI |  Alt |      |
    * `-----------------------------------------------------------------------------------'
    */
  [_STENO] = LAYOUT_planck_mit_(
    _______, _________________STENO_L1__________________,  ________________STENO_R1__________________________,
    _______, _________________STENO_L2__________________,  ________________STENO_R2__________________________,
    XXXXXXX, _________________STENO_L3__________________,  ________________STENO_R3__________________________,
    STN_EX,  _______, KC_LALT, ____STENO_AO____,      XXXXXXX,    ____STENO_EU____, KC_RGUI, KC_RALT, XXXXXXX
  ),

  /* Adjust
    * ,-----------------------------------------------------------------------------------.
    * |Reset |Qwerty|Colemak|Steno|RotMG |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |UniLin|UniWin|      |      |      |      | Prev | Play | Next |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      | Vol -| Vol +| Mute |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
  [_ADJUST] = LAYOUT_planck_mit_(
      RESET  , QWERTY,  COLEMAK, STENO,   ROTMG_L, _______, _______, _______, _______, _______, _______, _______,
      _______, UC_M_LN, UC_M_WC, _______, _______, _______, _______, __________MEDIA__________, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, __________VOLUME_________, _______, _______,
      _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
  )
};

void matrix_init_user() {
#ifdef STENO_ENABLE
  steno_set_mode(STENO_MODE_GEMINI);
#endif
}

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

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
    case STENO:
      if (record->event.pressed) {
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_NUMPAD);
        layer_off(_ADJUST);
        layer_on(_STENO);
      }
      return false;
    case STCH_EX:
      if (record->event.pressed) {
        layer_off(_CAMEL);
        layer_off(_KEBAB);
        layer_off(_SNAKE);
      }
      return false;
    case STN_EX:
      if (record->event.pressed) {
        layer_off(_STENO);
      }
      return false;
    case CIRC:
      if (record->event.pressed) {
        register_code(KC_RALT);
        // register_code(KC_LSHIFT);
        tap_code(KC_6);
        // unregister_code(KC_LSHIFT);
        unregister_code(KC_RALT);
      }
      return false;
    default:
      return true;
  }
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_TWO_KEYS(KC_SPC, KC_C) {
      layer_on(_CAMEL);
    }

    SEQ_TWO_KEYS(KC_SPC, KC_K) {
      layer_on(_KEBAB);
    }

    SEQ_TWO_KEYS(KC_SPC, KC_S) {
      layer_on(_SNAKE);
    }
  }
}
