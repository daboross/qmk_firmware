/*
 * daboross callum-based keymap. Based entirely on jurgen-kluft's work at
 * https://github.com/jurgen-kluft/qmk_firmware/tree/jurgen/keyboards/kyria/keymaps/jurgen-kluft,
 * revision a6e2595245bcc6615a015950bd3597d67067130d.
 *
 */
#include QMK_KEYBOARD_H
#include "oled.h"
#include "smart.h"
#include "oneshot.h"
#include "layers.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_REDO LGUI(LSFT(KC_Z))
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_REDO LCTL(LSFT(KC_Z))
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)

#ifdef OS_MAC
#    define KC_UNDO KC_MAC_UNDO
#    define KC_REDO KC_MAC_REDO
#    define KC_CUT KC_MAC_CUT
#    define KC_COPY KC_MAC_COPY
#    define KC_PASTE KC_MAC_PASTE
#    define KC_TRANS KC_TRANSPARENT
#    define KC_NDT C(KC_RIGHT)
#    define KC_PDT C(KC_LEFT)
#    define KC_CLOSE LGUI(KC_W)
#    define KC_SAVE LGUI(KC_S)
#else
#    define KC_UNDO KC_PC_UNDO
#    define KC_REDO KC_PC_REDO
#    define KC_CUT KC_PC_CUT
#    define KC_COPY KC_PC_COPY
#    define KC_PASTE KC_PC_PASTE
#    define KC_TRANS KC_TRANSPARENT
#    define KC_NDT LCTL(LGUI(KC_RIGHT))
#    define KC_PDT LCTL(LGUI(KC_LEFT))
#    define KC_CLOSE LCTL(KC_W)
#    define KC_SAVE LCTL(KC_S)
#endif

#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)

enum custom_keycodes {
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
};

#ifdef COMBO_ENABLE
#define COMBO_COUNT 3
const uint16_t PROGMEM nav_combo[] = {KC_SPACE, LA_NAV, COMBO_END};
const uint16_t PROGMEM sym_combo[] = {KC_SPACE, LA_SYM, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(nav_combo, LA_NAV),
    COMBO(sym_combo, LA_SYM),
};
uint16_t COMBO_LEN = 2;
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Esc   |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |     ' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |      |  |      |      |   N  |   M  | ,  < | . >  | /  ? | ~ `    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | [enc]| Alt  | Nav  | Space| Shift|  | Cmd  | Space| Sym  | AltGr| [enc]|
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y   , KC_U   , KC_I   , KC_O   , KC_P    , KC_BSPC,
     KC_ESC , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN , KC_QUOT,
     KC_LSFT, KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , _______, _______,    _______, _______, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH , KC_GRV ,
                                KC_NO , KC_LALT, LA_NAV , KC_SPC , KC_LSFT,    KC_LGUI, KC_SPC , LA_SYM , KC_ALGR, KC_NO
    ),

/*
 * Nav Layer: navigation
 *
 * ,-------------------------------------------.                              ,------------------------------------------.
 * |        | Tab  |      | Esc  |      |      |                              |      | PgUp |   ↑  | PgDn | Del  |       |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+-------|
 * |        | shift| ctrl | alt  | cmd  |      |                              |      |  ←   |   ↓  |  →   | Bspc |       |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+-------|
 * |        |      |      |      |      |      |      |      |  |      |      |      | Home | End  | Ins  | Enter| PrtSc |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+---------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, KC_NO  , KC_TAB, KC_ESC  , KC_NO  , KC_NO  ,                                     KC_NO  , KC_PGUP, KC_UP  , KC_PGDN, KC_DEL , _______,
      _______, OS_SHFT, OS_CTRL, OS_ALT , OS_CMD , KC_NO  ,                                     KC_NO  , KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, _______,
      _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______, _______, _______, _______, KC_NO  , KC_HOME, KC_END , KC_INS , KC_ENT , KC_PSCR,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),


/*
 * Sym Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |  [   |  {   |  (   |  ~   |                              |   `  |  )   |  }   |  ]   |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  -   |  *   |  =   |  _   |  $   |                              |   #  | cmd  | alt  | ctrl | shift|        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  +   |  |   |  @   |  /   |  %   |      |      |  |      |      |   ^  |  \   |  &   |  ?   |  !   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
      _______, KC_NO  , KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,                                     KC_GRV , KC_RPRN, KC_RCBR, KC_RBRC, KC_NO  , _______,
      _______, KC_MINS, KC_ASTR, KC_EQL , KC_UNDS, KC_DLR ,                                     KC_HASH, OS_CMD , OS_ALT , OS_CTRL, OS_SHFT, _______,
      _______, KC_PLUS, KC_PIPE, KC_AT  , KC_SLSH, KC_PERC, _______, _______, _______, _______, KC_CIRC, KC_BSLS, KC_AMPR, KC_QUES, KC_EXLM, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Raised layer: numbers and f-keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  1   |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | shift| ctrl | alt  | cmd  | F11  |                              | F12  | cmd  | alt  | ctrl | shift|        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |  |      |      |  F6  |  F7  |  F8  |  F9  | F10  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT(
      _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
      _______, OS_SHFT, OS_CTRL, OS_ALT , OS_CMD , KC_F11 ,                                     KC_F12 , OS_CMD , OS_ALT , OS_CTRL, OS_SHFT, _______,
      _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______, _______, _______, _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _NAV, _SYM, _RAISE); }

#ifdef ENABLE_ONESHOT

bool is_oneshot_modifier_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case LA_NAV:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_modifier_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_NAV:
            return true;
    }
    return false;
}

oneshot_mod get_modifier_for_trigger_key(uint16_t keycode) {
    switch (keycode) {
        case OS_SHFT:
            return ONESHOT_LSFT;
        case OS_CTRL:
            return ONESHOT_LCTL;
        case OS_ALT:
            return ONESHOT_LALT;
        case OS_CMD:
            return ONESHOT_LGUI;
    }
    return ONESHOT_NONE;
}

#endif

bool smart_feature_cancel_key(uint16_t keycode, keyrecord_t* recor) {
    switch (keycode) {
        case LA_SYM:
        case LA_NAV:
            return true;
    }
    return false;
}

int8_t la_nav_taps = 0;
int8_t la_sym_taps = 0;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    process_record_oled(keycode, record);

    switch (keycode) {
        case LA_NAV:
            if (record->event.pressed) {
                la_nav_taps += 1;
            } else {
                la_nav_taps += 1;
            }
            break;
        case LA_SYM:
            if (record->event.pressed) {
                la_sym_taps += 1;
            } else {
                la_sym_taps += 1;
            }
            break;
        default:
            // Reset double tap detection
            la_nav_taps = 0;
            la_sym_taps = 0;
            break;
    }

    uint8_t const layer = default_layer_state + 1;  // Warning: QWERTY and RSTHD and their CAPSLOCK layers have a dependency

    // Still have a free trigger to use for something
    // if (la_nav_taps == 2 && la_sym_taps == 2) {
    //     // some other layer can be activated
    // }

    if (la_nav_taps >= 4 && ((la_nav_taps & 1) == 0)) {
        smart_feature_toggle(SMART_CAPSLOCK, layer);
    }
    if (la_sym_taps >= 4 && ((la_sym_taps & 1) == 0)) {
        smart_feature_toggle(SMART_NUMBERS, _NUM);
    }

    int8_t keycode_consumed = 0;

    if ((smart_feature_cancel_key(keycode, record)) || (keycode < QK_MODS_MAX && !IS_MOD(keycode))) {
        if (smart_feature_state(SMART_CAPSLOCK)) {
            keycode_consumed = 1;
            smart_capslock_process(keycode, record);
        }
        if (smart_feature_state(SMART_NUMBERS)) {
            keycode_consumed = 1;
            smart_numbers_process(keycode, record);
        }
    }

#ifdef ENABLE_ONESHOT
    keycode_consumed += update_oneshot_modifiers(keycode, record, keycode_consumed);
#endif

    return true;
};

// Layer-specific encoder knob functions
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    uint16_t layers = (layer_state | default_layer_state);
    if (index == 0) {  // left knob
        switch (get_highest_layer(layers)) {
            case _SYM:  // Desktop switching
                if (clockwise) {
                    tap_code16(KC_NDT);
                } else {
                    tap_code16(KC_PDT);
                }
                break;
            default:  // Volume Up/Down
                if (clockwise) {
                    tap_code(KC_VOLD);
                } else {
                    tap_code(KC_VOLU);
                }
                break;
        }
    } else if (index == 1) {  // right knob
        switch (get_highest_layer(layers)) {
            case _NAV:  // Undo/Redo
                if (clockwise) {
                    tap_code16(KC_UNDO);
                } else {
                    tap_code16(KC_REDO);
                }
                break;
            default:
                break;
        }
    } else {
        tap_code16(S(KC_SLASH));
    }
    return false;
}
#endif

/*
qmk-keyboard-format:json:begin
{
  "name": "Kyria",
  "numkeys": 50,
  "rows": [
      [ -3,  0,  1,  2,  3,  4,  5, -1, -1, -2, -1, -1,  6,  7,  8,  9, 10, 11 ],
      [ -3, 12, 13, 14, 15, 16, 17, -1, -1, -2, -1, -1, 18, 19, 20, 21, 22, 23 ],
      [ -3, 24, 25, 26, 27, 28, 29, 30, 31, -2, 32, 33, 34, 35, 36, 37, 38, 39 ],
      [ -3, -1, -1, -1, 40, 41, 42, 43, 44, -2, 45, 46, 47, 48, 49, -1, -1, -1 ]
  ],
  "spacing": [
      0,
      0,
      0,
      2
  ],
  "vizcellwidth": 5,
  "vizemits": [
      { "line": "[_QWERTY] = LAYOUT(", "layer": "_QWERTY" }
  ],
  "vizline": "//#",
  "vizboard": [
      "    //#                         ╭───────╮                                                                        ╭───────╮                          ",
      "    //#                 ╭───────╯ _003_ ╰───────╮                                                        ╭───────╯ _008_ ╰───────╮                  ",
      "    //#                 │ _002_ │       │ _004_ ╭───────╮                                        ╭───────╮ _007_ │       │ _009_ │                  ",
      "    //# ╭───────╮───────╯       ╰───────╯       │ _005_ │                                        │ _006_ │       ╰───────╯       ╰───────╭───────╮  ",
      "    //# │ _000_ │ _001_ ╰───────╯ _015_ ╰───────╯       │                                        │       ╰───────╯ _020_ ╰───────╯ _010_ │ _011_ │  ",
      "    //# │       │       │ _014_ │       │ _016_ ╰───────╯                                        ╰───────╯ _019_ │       │ _021_ │       │       │  ",
      "    //# ╰───────╯───────╯       ╰───────╯       │ _017_ │                                        │ _018_ │       ╰───────╯       ╰───────╰───────╯  ",
      "    //# │ _012_ │ _013_ ╰───────╯ _027_ ╰───────╯       │                                        │       ╰───────╯ _036_ ╰───────╯ _022_ │ _023_ │  ",
      "    //# │       │       │ _026_ │       │ _028_ ╰───────╯                                        ╰───────╯ _035_ │       │ _037_ │       │       │  ",
      "    //# ╰───────╯───────╯       ╰───────╯       │ _029_ │ ╭───────╮                    ╭───────╮ │ _034_ │       ╰───────╯       ╰───────╰───────╯  ",
      "    //# │ _024_ │ _025_ ╰───────╯       ╰───────╯       │ │ _030_ ╰───────╮    ╭───────╯ _033_ │ │       ╰───────╯       ╰───────╯ _038_ │ _039_ │  ",
      "    //# │       │       │              ╭───────╮╰───────╯ │       │ _031_ │    │ _032_ │       │ ╰───────╯╭───────╮              │       │       │  ",
      "    //# ╰───────╯───────╯     ╭───────╮│ _041_ ╰───────╮  ╰───────╯       │    │       ╰───────╯  ╭───────╯ _048_ │╭───────╮     ╰───────╰───────╯  ",
      "    //#                       │ _040_ ││       │ _042_ ╰───────╮  ╰───────╯    ╰───────╯  ╭───────╯ _047_ │       ││ _049_ │                        ",
      "    //#                       │       │╰───────╯       │ _043_ ╰───────╮          ╭───────╯ _046_ │       ╰───────╯│       │                        ",
      "    //#                       ╰encodr─╯        ╰───────╯       │ _044_ │          │ _045_ │       ╰───────╯        ╰encodr─╯                        ",
      "    //#                                                ╰───────╯       │          │       ╰───────╯                                                 ",
      "    //#                                                        ╰───────╯          ╰───────╯                                                         "
  ],
  "vizsymbols": {
      "TG(_MOUS)": "MOUSE",
      "TG(_SYSTEM)": " SYS ",
      "MO(_NAV)": "NAVI ",
      "MO(_FNC)": "FUNC ",
      "MO(_SYM)": " SYM ",
      "TG(_QWERTY_CAPS)": "CAPS ",
      "TG(_RSTHD_CAPS)": "CAPS ",
      "KC_SMART_NUMBER": "SMNUM",
      "KC_SMART_CAPSLOCK": "SMCAP",
      "OSM(MOD_LSFT)": "SHIFT",
      "_______": "     ",
      "KC_TRANS": "     ",
      "KC_0": "  0  " ,
      "KC_1": "  1  " ,
      "KC_2": "  2  " ,
      "KC_3": "  3  " ,
      "KC_4": "  4  " ,
      "KC_5": "  5  " ,
      "KC_6": "  6  " ,
      "KC_7": "  7  " ,
      "KC_8": "  8  " ,
      "KC_9": "  9  " ,
      "KC_A": "  A  " ,
      "KC_B": "  B  " ,
      "KC_C": "  C  " ,
      "KC_D": "  D  " ,
      "KC_E": "  E  " ,
      "KC_F": "  F  " ,
      "KC_G": "  G  " ,
      "KC_H": "  H  " ,
      "KC_I": "  I  " ,
      "KC_J": "  J  " ,
      "KC_K": "  K  " ,
      "KC_L": "  L  " ,
      "KC_M": "  M  " ,
      "KC_N": "  N  " ,
      "KC_O": "  O  " ,
      "KC_P": "  P  " ,
      "KC_Q": "  Q  " ,
      "KC_R": "  R  " ,
      "KC_S": "  S  " ,
      "KC_T": "  T  " ,
      "KC_U": "  U  " ,
      "KC_V": "  V  " ,
      "KC_W": "  W  " ,
      "KC_X": "  X  " ,
      "KC_Y": "  Y  " ,
      "KC_Z": "  Z  " ,
      "KC_COMMA": "  ,  ",
      "KC_COMM": "  ,  ",
      "KC_DOT": "  .  ",
      "KC_COLN": "  :  ",
      "KC_SCOLON": "  ;  ",
      "KC_SCLN": "  ;  ",
      "KC_SLASH": "  \/  ",
      "KC_SLSH": "  \/  ",
      "KC_BSLASH": "  \\  ",
      "KC_BSLS": "  \\  ",
      "KC_EXLM": "  !  ",
      "KC_QUES": "  ?  ",
      "KC_PIPE": "  |  ",
      "KC_QUOT": "  '  ",
      "KC_QUOTE": "  '  ",
      "KC_DQUO": "  \"  ",
      "KC_DQT": "  \"  ",
      "KC_HASH": "  #  ",
      "KC_AMPR": "  &  ",
      "KC_PERC": "  %  ",
      "KC_TILDE": "  ~  ",
      "KC_AT": "  @  ",
      "KC_DLR": "  $  ",
      "KC_CIRC": "  ^  ",
      "KC_EQL": "  =  ",
      "KC_EQUAL": "  =  ",
      "KC_ASTR": "  *  ",
      "KC_MINS": "  -  ",
      "KC_MINUS": "  -  ",
      "KC_UNDS": "  _  ",
      "KC_PLUS": "  +  ",
      "KC_LCBR": "  {  ",
      "KC_LBRACKET": "  {  ",
      "KC_RCBR": "  }  ",
      "KC_RBRACKET": "  }  ",
      "KC_LPRN": "  (  ",
      "KC_RPRN": "  )  ",
      "KC_GRV": "  `  ",
      "KC_LBRC": "  [  ",
      "KC_RBRC": "  ]  ",
      "KC_LABK": "  <  ",
      "KC_RABK": "  >  ",
      "KC_TILD": "  ~  ",
      "KC_ESC": " ESC " ,
      "KC_ESCAPE": " ESC " ,
      "KC_COPY": " Copy",
      "KC_PASTE": "Paste",
      "KC_CUT":    " Cut " ,
      "KC_UNDO":   " Undo" ,
      "KC_REDO": " Redo " ,
      "KC_VOLU": "  🕪  " ,
      "KC_VOLD": "  🕩  " ,
      "KC_MUTE":   "  🕨  " ,
      "KC_TAB": " TAB " ,
      "KC_MENU": "  𝌆  " ,
      "KC_CAPSLOCK": "  ⇪  " ,
      "KC_NUMLK": "  ⇭  " ,
      "KC_SCRLK": "  ⇳  " ,
      "KC_PRSCR": "  ⎙  " ,
      "KC_PAUSE": "  ⎉  " ,
      "KC_BREAK": "  ⎊  " ,
      "KC_ENTER": "  ⏎  " ,
      "KC_BSPACE": "  ⌫  " ,
      "KC_DELETE": "  ⌦  " ,
      "KC_INSERT": "Insrt" ,
      "KC_LEFT":  "  L  " ,
      "KC_RIGHT": "  R  " ,
      "KC_UP":    "  U  " ,
      "KC_DOWN":  "  D  " ,
      "KC_HOME": "  ⇤  " ,
      "KC_END": "  ⇥  " ,
      "KC_PGUP": "  ⇞  " ,
      "KC_PGDOWN": "  ⇟  " ,
      "KC_LSFT": "  ⇧  " ,
      "KC_RSFT": "  ⇧  " ,
      "OS_SHFT": "  ⇧  " ,
      "KC_LCTL": "  ^  " ,
      "KC_RCTL": "  ^  " ,
      "OS_CTRL": "  ^  " ,
      "KC_LALT": "  ⎇  " ,
      "KC_RALT": "  ⎇  " ,
      "OS_ALT": "  ⎇  " ,
      "KC_HYPER": "  ✧  " ,
      "KC_LGUI": "  ⌘  " ,
      "KC_RGUI": "  ⌘  ",
      "OS_CMD": "  ⌘  "
  }
}
qmk-keyboard-format:json:end
*/

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void oled_task_user(void) {
   // if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        // static const char PROGMEM qmk_logo[] = {
        //     0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        //     0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        //     0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        // oled_write_P(qmk_logo, false);
        // oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

        // Host Keyboard Layer Status
        //oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                // oled_write_P(PSTR("QWERTY\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("navigation\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("symbols\n"), false);
                break;
            case _RAISE:
                oled_write_P(PSTR("numbers\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    //} else {
/*        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
*/    //}
}
#endif
