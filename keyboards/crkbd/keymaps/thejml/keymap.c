#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

//extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  PRIMARY,
  EH,
  GC,
  GP,
  NOTRUN,
  WRDL,
  WRDR,
  KPSE,
  KPSW,
  KPRE,
  KPRW,
  PASSRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______  KC_TRNS
#define KC_XXXXX  KC_NO
#define KC_LOWER  LOWER
#define KC_RAISE  RAISE
#define KC_RST    RESET
#define KC_LRST   RGBRST
#define KC_CPRI   PRIMARY
#define KC_CGC    GC
#define KC_CGP    GP
#define KC_CEH    EH
#define KC_CNR    NOTRUN
#define KC_WRDL   WRDL
#define KC_WRDR   WRDR
#define KC_KPSE   KPSE
#define KC_KPSW   KPSW
#define KC_KPRE   KPRE
#define KC_KPRW   KPRW
#define KC_PRST   PASSRST
#define KC_LTOG   RGB_TOG
#define KC_LHUI   RGB_HUI
#define KC_LHUD   RGB_HUD
#define KC_LSAI   RGB_SAI
#define KC_LSAD   RGB_SAD
#define KC_LVAI   RGB_VAI
#define KC_LVAD   RGB_VAD
#define KC_LMOD   RGB_MOD
#define KC_GUIEI  GUI_T(KC_LANG2)
#define KC_ALTKN  ALT_T(KC_LANG1)
#define KC_AZERO  MT(MOD_RALT,KC_0)
#define KC_AMINS  MT(MOD_RALT,KC_MINS)
#define KC_SLEFT  SCMD(KC_LEFT)
#define KC_SRIGHT SCMD(KC_RIGHT)
#define KC_RLEFT  RCTL(KC_LEFT)
#define KC_RRIGHT RCTL(KC_RIGHT)
#define KC_SCR1 LALT(KC_1)
#define KC_SCR2 LALT(KC_2)
#define KC_SCR3 LALT(KC_3)
#define KC_SCR4 LALT(KC_4)
#define KC_SCR5 LALT(KC_5)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        ESC,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RCTL,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  GUIEI, LOWER,   ENT,      SPC, RAISE, AMINS
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,----------------------------------------------.                ,-----------------------------------------.
        GRV,    MPLY,  PGUP,    UP,   PGDN,    VOLU,                    EQL,     7,     8,     9,     0,  BSPC,
  //|------+--------+------+------+-------+--------|                |------+------+------+------+------+------|
        ESC,    MPRV,  LEFT,  DOWN,  RIGHT,    VOLD,                   MINS,     4,     5,     6,  LBRC,  RBRC,
  //|------+--------+------+------+-------+--------|                |------+------+------+------+------+------|
       LSFT,    MSTP,  LTOG,    F8,   MNXT,    MUTE,                    DOT,     1,     2,     3,  LPRN,  RPRN,
  //|------+--------+------+------+-------+--------+-------|  |------+------+------+------+------+------+------|
                                     GUIEI,   LOWER,   ENT,      SPC, RAISE, AZERO
                               //`-------------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,---------------------------------------------.
        GRV,  SCR1,  SCR2,  SCR3,  SCR4,  SCR5,                   CIRC,  AMPR,    ASTR,   LPRN,  RPRN,  BSPC,\
  //|------+------+------+------+------+------|                |------+---------+-------+------+------+------|
        ESC,    F1,    F2,    F3,    F4,    F5,                   MINS,  SLEFT,  SRIGHT,  RCBR,  PIPE,   GRV,\
  //|------+------+------+------+------+------|                |------+---------+-------+------+------+------|
       LSFT,    F6,    F7,    F8,    F9,   F10,                   UNDS,  RLEFT,  RRIGHT,  RBRC,  BSLS,  RCTL,\
  //|------+------+------+------+------+------+------|  |------+------+---------+-------+------+------+------|
                                  GUIEI, LOWER,   ENT,      SPC, RAISE, AMINS \
                              //`--------------------'  `--------------------'

  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX,    XXXXX,  KPRW,  KPRE, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |--------+-------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI,    F8,   F12,                     CPRI,    CNR,  KPSW,  KPSE,   CGC, XXXXX,\
  //|------+------+------+------+------+------|                |--------+-------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD,   ESC,   DEL,                      CEH,   WRDL,  WRDR, XXXXX,   CGP, RCTL,\
  //|------+------+------+------+------+------+------|  |------+--------+-------+------+------+------+------|
                                  GUIEI, LOWER,   SPC,      ENT, RAISE, RALT \
                              //`--------------------'  `--------------------'
  )
};
        // _______,  _______,  KC_MPLY,  KC_VOLU,  KC_MSTP,  _______,                      EEP_RST,  RESET,    _______,  _______,  _______,  _______,
        // _______,  _______,  KC_MPRV,  KC_VOLD,  KC_MNXT,  _______,                      RGB_RMOD, RGB_VAD,  RGB_VAI,  RGB_MOD,  RGB_SPI,  _______,
        // _______,  _______,  _______,  KC_MUTE,  _______,  _______,                      RGB_HUI,  RGB_SAD,  RGB_SAI,  RGB_HUD,  RGB_SPD,  _______,

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    case PRIMARY:
      if (record->event.pressed) {
        SEND_STRING("Asuka1%MyCuteWaifu!");
      }
      return false;
    case EH:
      if (record->event.pressed) {
        SEND_STRING("3BzDXpEJjzIJ7pTOF0MX5aRE");
      }
      return false;
    case NOTRUN:
      if (record->event.pressed) {
        SEND_STRING(" get pods -A|grep -v Running" SS_TAP(X_ENTER));
      }
      return false;
    case GC:
      if (record->event.pressed) {
        SEND_STRING("git commit ");
      }
      return false;
    case GP:
      if (record->event.pressed) {
        SEND_STRING("git push" SS_TAP(X_ENTER));
      }
      return false;
    case WRDR:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(ESC) "F");
      }
      return false;
    case WRDL:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(ESC) "B"); //prints KSCB ... 
      }
      return false;
    case KPSE:
      if (record->event.pressed) {
        SEND_STRING("k --kubeconfig ~/.kube/shuse1-dmzsql-eds-prd ");
      }
      return false;
    case KPSW:
      if (record->event.pressed) {
        SEND_STRING("k --kubeconfig ~/.kube/shusw2-dmzsql-eds-prd ");
      }
      return false;
    case KPRE:
      if (record->event.pressed) {
        SEND_STRING("k --kubeconfig ~/.kube/rnuse1-dmz-residential-prd ");
      }
      return false;
    case KPRW:
      if (record->event.pressed) {
        SEND_STRING("k --kubeconfig ~/.kube/rnusw2-dmz-residential-prd ");
      }
      return false;
    case PASSRST:
      if (record->event.pressed) {
        SEND_STRING(""); // fn + Control + Option + Backspace => Somehow...
      }     
      return false;
  }
  return true;
}
