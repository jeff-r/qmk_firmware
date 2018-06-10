#include "jr2.h"

enum {
  JR_CTL_GUI,
  JR_CTL_ALT,
  JR_SHIFT,
  JR_LAYER_TOGGLE,
  JR_LAYER_ONCE,
  JR_NERDTREE,
  JR_TMUX_COPY,
  JR_TMUX_PASTE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = { /* Base */
        {KC_VOLD,  KC_VOLU,  KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,      KC_MINUS,    KC_EQUAL,    KC_BSPC },
        {KC_HOME,  KC_PGUP,  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,      KC_LBRACKET, KC_RBRACKET, F(JR_CTL_GUI)},
        {KC_END,   KC_PGDN,  KC_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,     KC_SCOLON, KC_QUOTE,    KC_ENTER,    F(JR_CTL_ALT) },
        {KC_UP,    KC_DOWN,  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLASH,  KC_RSFT,     KC_BSLASH,   KC_BSLASH },
        {KC_LEFT,  KC_RIGHT, KC_LCTL,  KC_LGUI, KC_LALT, F(JR_LAYER_ONCE),  KC_BSPC,  KC_SPC,  KC_SPC,  F(JR_LAYER_TOGGLE),  KC_RALT, KC_RGUI,  KC_RCTL,   KC_RALT,     KC_RGUI,     KC_RCTL }
        // {KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6 },
    },
    [1] = { /* toggle */
        {KC_ESC,   KC_ESC,   KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_TRNS,  KC_TRNS },
        {KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  F(JR_TMUX_COPY),  F(JR_TMUX_PASTE),  F(JR_NERDTREE)  },
        {KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS },
        {KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS },
        {KC_VOLU,  KC_VOLD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS }
    }
};

const uint16_t PROGMEM fn_actions[] = {
  [JR_CTL_GUI] = ACTION_MODS_ONESHOT(MOD_LCTL | MOD_LGUI),  // apply ctrl-gui to next key
  [JR_CTL_ALT] = ACTION_MODS_ONESHOT(MOD_LCTL | MOD_LALT),  // apply ctrl-alt to next key
  [JR_SHIFT]   = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_SPC),     // Shift if combined with another key; otherwise, space
  // [JR_LAYER_TOGGLE] = ACTION_LAYER_TOGGLE(1),                  // Toggle layer 1
  [JR_LAYER_TOGGLE] = ACTION_LAYER_TAP_KEY(1, ACTION_LAYER_ONESHOT(1)),                  // Toggle layer 1
  [JR_LAYER_ONCE]   = ACTION_LAYER_ONESHOT(1),
  [JR_NERDTREE]     = ACTION_MACRO_TAP(JR_NERDTREE),
  [JR_TMUX_COPY]    = ACTION_MACRO_TAP(JR_TMUX_COPY),
  [JR_TMUX_PASTE]   = ACTION_MACRO_TAP(JR_TMUX_PASTE)
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // MACRODOWN only works in this function
{
  switch (id) {
    case JR_NERDTREE:
      return ( record->event.pressed ?
                 MACRO( T(BSLASH), T(N), T(T), END ) :
                 MACRO_NONE);
    case JR_TMUX_COPY:
      return ( record->event.pressed ?
                 MACRO( D(LCTL), T(A), U(LCTL), T(LBRACKET), END ) :
                 MACRO_NONE);
    case JR_TMUX_PASTE:
      return ( record->event.pressed ?
                 MACRO( D(LCTL), T(A), U(LCTL), T(RBRACKET), END ) :
                 MACRO_NONE);
  }
  return MACRO_NONE;
};
