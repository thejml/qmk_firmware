#include QMK_KEYBOARD_H

enum layer {
    LAYER_FIRST,
    LAYER_SECOND,
    LAYER_THIRD
};

/* Switch to second layer when held. */
#define LY_SECND MO(LAYER_SECOND)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* First layer (F1-F6) */
    [LAYER_FIRST] = LAYOUT(
        KC_MUTE,  RCMD(KC_BSPC), BL_TOGG,
        KC_F4,    KC_F5,    KC_F6,
        RCMD(KC_LEFT),  LY_SECND,    RCMD(KC_RIGHT)
    ),

    /* Second layer (F7-F12) */
    [LAYER_SECOND] = LAYOUT(
        _______,  _______,  _______,
        KC_F10,   KC_F11,   KC_F12,
        KC_F7,    KC_F8,    KC_F9
    ),

        /* Second layer (F7-F12) */
    [LAYER_THIRD] = LAYOUT(
        _______,   KC_U,     _______,
        KC_J,      KC_UP,    KC_L,
        KC_LEFT,   KC_DOWN,   KC_RIGHT
    ),
};

// clockwise is backwords...
// void encoder_update_user(uint8_t index, bool clockwise) {
//     switch (index) {
//         /* Top-left encoder (volume): */
//         case 0:
//             tap_code(clockwise ? KC_VOLD : KC_VOLU);
//     }
// }

uint8_t selected_layer = 0;
void encoder_update_user(uint8_t index, bool clockwise) {
  switch (index) {
    case 0:
      if (!clockwise && selected_layer  < 10) {
        selected_layer ++;
      } else if (clockwise && selected_layer  > 0){
        selected_layer --;
      }
      layer_clear();
      layer_on(selected_layer);
    case 1:
      tap_code(clockwise ? KC_VOLD : KC_VOLU);
  }
}