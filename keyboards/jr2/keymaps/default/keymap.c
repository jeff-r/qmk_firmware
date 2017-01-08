#include "jr2.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = { /* Base */
        {KC_ESC,   KC_ESC,   KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,    KC_F11,      KC_F12,      KC_RSHIFT },
        {KC_GRAVE, KC_GRAVE, KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,      KC_MINUS,    KC_EQUAL,    KC_BSPC },
        {KC_HOME,  KC_PGUP,  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,      KC_LBRACKET, KC_RBRACKET, KC_BSLASH },
        {KC_END,   KC_PGDN,  KC_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,     KC_SCOLON, KC_QUOTE,    KC_ENTER,    KC_CAPSLOCK  },
        {KC_UP,    KC_DOWN,  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLASH,  KC_RSFT,     KC_BSLASH,   KC_BSLASH },
        {KC_LEFT,  KC_RIGHT, KC_LCTL,  KC_LGUI, KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, KC_RGUI,  KC_RCTL,   KC_RALT,     KC_RGUI,     KC_RCTL }
    },
    [1] = { /* LOWER */
        {KC_ESC,   KC_ESC,   KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,    KC_F11,      KC_F12,      KC_RSHIFT },
        {KC_GRAVE, KC_1,     KC_1,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,      KC_MINUS,    KC_EQUAL,    KC_BSPC },
        {KC_HOME,  KC_PGUP,  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,      KC_LBRACKET, KC_RBRACKET, KC_BSLASH },
        {KC_END,   KC_DOWN,  KC_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,     KC_SCOLON, KC_QUOTE,    KC_ENTER,    KC_BSLASH  },
        {KC_DOWN,  KC_UP,    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLASH,  KC_RSFT,     KC_BSLASH,   KC_BSLASH },
        {KC_LEFT,  KC_RIGHT, KC_LCTL,  KC_LGUI, KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, KC_RGUI,  KC_RCTL,   KC_RALT,     KC_RGUI,     KC_RCTL }
    },
    [2] = { /* RAISE */
        {KC_ESC,   KC_ESC,   KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,    KC_F11,      KC_F12,      KC_RSHIFT },
        {KC_GRAVE, KC_1,     KC_1,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,      KC_MINUS,    KC_EQUAL,    KC_BSPC },
        {KC_HOME,  KC_PGUP,  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,      KC_LBRACKET, KC_RBRACKET, KC_BSLASH },
        {KC_END,   KC_DOWN,  KC_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,     KC_SCOLON, KC_QUOTE,    KC_ENTER,    KC_BSLASH  },
        {KC_DOWN,  KC_UP,    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLASH,  KC_RSFT,     KC_BSLASH,   KC_BSLASH },
        {KC_LEFT,  KC_RIGHT, KC_LCTL,  KC_LGUI, KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, KC_RGUI,  KC_RCTL,   KC_RALT,     KC_RGUI,     KC_RCTL }
    }
};

const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // MACRODOWN only works in this function
{
    return MACRO_NONE;
};

    /*
    [1] =
        {KC_ESC,  KC_1,    KC_2,     KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DELT },
        {KC_TAB,  KC_MPRV, KC_MPLY,  KC_MNXT, KC_GRV,  KC_BSLS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_NO,   KC_ENT  },
        {KC_CAPS, KC_LSFT, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NO,   KC_HOME, KC_PGUP, KC_RSFT },
        {KC_LCTL, KC_LGUI, KC_LALT,  KC_NO,   KC_TRNS, KC_NO,   KC_SPC,  KC_NO,   KC_TRNS, KC_END,  KC_PGDN, KC_EXLM }
    },
    [2] =
        {KC_ESC,  KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DELT },
        {KC_TAB,  KC_MUTE, KC_VOLD,  KC_VOLU, KC_TILD, KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_NO,   KC_ENT  },
        {KC_CAPS, KC_LSFT, KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,   KC_UP,   KC_RSFT },
        {KC_LCTL, KC_LGUI, KC_LALT,  KC_NO,   KC_TRNS, KC_NO,   KC_SPC,  KC_NO,   KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT }
    }
    */
/*
 * From earlier pic-based version
uint8_t keys[NUMROWS][NUMCOLS]  = {
   {   vkLeft,  vkRight,     vkLC,     vkLG,    vkLA, vkSpace, vkSpace, vkSpace, vkSpace, vkSpace,     vkRA,    vkRG,    vkRC,    vkRA,     vkRG,     vkRC },
   {     vkUp,   vkDown,     vkLS,      vkZ,     vkX,     vkC,     vkV,     vkB,     vkN,     vkM,  vkComma,   vkDot, vkSlash,    vkRS, vkBSlash,     vkRS },
   {    vkEnd,   vkPgDn, vkEscape,      vkA,     vkS,     vkD,     vkF,     vkG,     vkH,     vkJ,      vkK,     vkL, vkColon, vkQuote, vkReturn,  vkBSlash },
   {   vkHome,   vkPgUp,    vkTab,      vkQ,     vkW,     vkE,     vkR,     vkT,     vkY,     vkU,      vkI,     vkO,     vkP,    vkLB,     vkRB, vkBSlash },
   {  vkTilde,  vkTilde,  vkTilde,      vk1,     vk2,     vk3,     vk4,     vk5,     vk6,     vk7,      vk8,     vk9,     vk0,  vkDash,   vkPlus,     vkBS },
   { vkEscape, vkEscape, vkEscape,     vkF1,    vkF2,    vkF3,    vkF4,    vkF5,   vkF6,      vkF7,    vkF8,    vkF9,   vkF10,   vkF11,   vkF12,      vkRS }
};
*/
