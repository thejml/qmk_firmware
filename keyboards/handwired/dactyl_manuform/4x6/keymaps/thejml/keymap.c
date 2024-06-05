#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _RAISE 1
#define _LOWER 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  PASS,
  NOTRUN,
  KUBEWITHCONFIG,
  CSYNC,
  GPUSHO
};

// Fillers to make layering more clear

#define ____ KC_TRNS

#define SFT_ESC  SFT_T(KC_ESC)
#define CTL_BSPC CTL_T(KC_BSPC)
#define ALT_SPC  ALT_T(KC_SPC)
#define SFT_ENT  SFT_T(KC_ENT)

#define KC_SCR1 RALT(KC_1)
#define KC_SCR2 RALT(KC_2)
#define KC_SCR3 RALT(KC_3)
#define KC_SCR4 RALT(KC_4)
#define KC_SCR5 RALT(KC_5)

#define KC_DELWORD RCTL(KC_W)
#define KC_TMUTE SCMD(KC_M)

#define KC_ML KC_MS_LEFT
#define KC_MR KC_MS_RIGHT
#define KC_MU KC_MS_UP
#define KC_MD KC_MS_DOWN
#define KC_MB1 KC_MS_BTN1
#define KC_MB2 KC_MS_BTN1

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base (qwerty)
 * +-----------------------------------------+                             +-----------------------------------------+
 * | ESC  |   q  |   w  |   e  |   r  |   t  |                             |   y  |   u  |   i  |   o  |   p  |      |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * | TAB  |   a  |   s  |   d  |   f  |   g  |                             |   h  |   j  |   k  |   l  |   ;  |      |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * | SHFT |   z  |   x  |   c  |   v  |   b  |                             |   n  |   m  |   ,  |   .  |   /  |      |
 * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
 *               |  [   |   ]  |                                                         |      |      |
 *               +-------------+-------------+                             +-------------+-------------+
 *                             |      |      |                             |      |      |
 *                             |------+------|                             |------+------|=
 *                                           +-------------+ +-------------+
 *                                           |      |      | |      |      |
 *                                           |------+------| |------+------|
 *                                           |      |      | |      |      |
 *                                           +-------------+ +-------------+
 */

[_QWERTY] = LAYOUT( \
    KC_TAB,  KC_Q,  KC_W,   KC_E,   KC_R,   KC_T,               KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,    KC_BSPC,              \
    KC_ESC,  KC_A,  KC_S,   KC_D,   KC_F,   KC_G,               KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_QUOT,              \
    KC_LSFT, KC_Z,  KC_X,   KC_C,   KC_V,   KC_B,               KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_RCTL,              \
                 KC_LBRC,KC_RBRC,                                            KC_MINS,KC_EQL,                                \
                            LOWER,  KC_ENT,                             KC_SPC, RAISE,                                         \
                                    KC_LGUI,KC_LALT,            KC_RALT,KC_BSLASH,                                               \
                                    KC_MPLY, KC_GRV,            KC_RGUI,KC_DELWORD                                         \
),

[_LOWER] = LAYOUT(
    KC_GRV ,KC_MPLY,KC_PGDN, KC_UP, KC_PGUP,KC_VOLU,             KC_EQL,  KC_7,  KC_8,   KC_9,  KC_0,   KC_BSPC,               \
    BL_INC ,KC_MFFD,KC_LEFT,KC_DOWN,KC_RGHT,KC_VOLD,            KC_RPRN,  KC_4,  KC_5,   KC_6,  KC_MINS,KC_PIPE,               \
    _______,KC_MRWD,KC_HOME,KUBEWITHCONFIG,KC_END, KC_MUTE,             KC_DOT,  KC_1,  KC_2,   KC_3,  KC_EQL, _______,               \
                    BL_TOGG,KC_PSCR,                                             KC_0, KC_ENT,                                 \
                            _______,_______,                            _______,_______,                                       \
                                    _______,_______,            _______,_______,                                               \
                                    KC_TMUTE,CSYNC,            _______,PASS                                                \
),

[_RAISE] = LAYOUT(
    _______,KC_SCR1,KC_SCR2,KC_SCR3,KC_SCR4,KC_SCR5,            KC_F7,  KC_F8,  KC_F9,KC_F10,  KC_F11, KC_BSPC,
    _______,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,            KC_RPRN,SCMD(KC_LEFT), SCMD(KC_RGHT),_______,KC_PIPE ,KC_VOLU,   \
    _______,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10,            _______,RCTL(KC_LEFT), RCTL(KC_RGHT),_______,KC_BSLASH,KC_VOLD,   \
                     KC_F11, KC_F12,                                              KC_EQL, _______,                              \
                            _______,_______,                            _______,_______,                                       \
                                    _______,_______,            _______,_______,                                               \
                                    NOTRUN,  GPUSHO,            _______,_______                                                \
)
};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case PASS:
      if (record->event.pressed) {
          SEND_STRING("Bocci1%MyCuteRock!");
      }
      return false;
      break;
    case NOTRUN:
      if (record->event.pressed) {
        SEND_STRING(" get pods -A|grep -v Running" SS_TAP(X_ENTER));
      }
      return false;
      break;
    case KUBEWITHCONFIG:
      if (record->event.pressed) {
        SEND_STRING("k --kubeconfig ~/.kube/");
      }
      return false;
      break;
    case CSYNC:
      if (record->event.pressed) {
        SEND_STRING("cd ~/tfsRepos/costarSync" SS_TAP(X_ENTER));
      }
      return false;
      break;
    case GPUSHO:
      if (record->event.pressed) {
        SEND_STRING("git push --set-upstream origin" SS_TAP(X_ENTER));
      }
      return false;
      break;
  }
  return true;
}