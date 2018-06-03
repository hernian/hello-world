#include "helix.h"
#include "bootloader.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#include "LUFA/Drivers/Peripheral/TWI.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


#define HERNIAN_KEYMAP( \
    L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, R45, \
    L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, R44, \
    L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
    L30, L31, L32, L33, L34, L35, L36, R36, R30, R31, R32, R33, R34, R35, \
              L42, L43, L44, L45, L46, R46, R40, R41, R42, R43            \
    ) \
    { \
      { KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05, KC_NO    }, \
      { KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15, KC_NO    }, \
      { KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25, KC_NO    }, \
      { KC_##L30, KC_##L31, KC_##L32, KC_##L33, KC_##L34, KC_##L35, KC_##L36 }, \
      { KC_NO,    KC_NO,    KC_##L42, KC_##L43, KC_##L44, KC_##L45, KC_##L46 }, \
      { KC_##R05, KC_##R04, KC_##R03, KC_##R02, KC_##R01, KC_##R00, KC_NO    }, \
      { KC_##R15, KC_##R14, KC_##R13, KC_##R12, KC_##R11, KC_##R10, KC_NO    }, \
      { KC_##R25, KC_##R24, KC_##R23, KC_##R22, KC_##R21, KC_##R20, KC_NO    }, \
      { KC_##R35, KC_##R34, KC_##R33, KC_##R32, KC_##R31, KC_##R30, KC_##R36 }, \
      { KC_##R45, KC_##R44, KC_##R43, KC_##R42, KC_##R41, KC_##R40, KC_##R46 }  \
    }


extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define KC_ZNHN 0x35
#define KC_EISU 0x39
#define KC_HIRA 0x88
#define KC_XFER 0x8a
#define KC_NFER 0x8b

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define LAYER_COLEMAK 0
#define LAYER_LOWER   1
#define LAYER_RAISE   2


#define KC_		KC_TRNS
#define KC_XXXX	KC_NO
#define KC_LOWR	MO(LAYER_LOWER)
#define KC_RASE	MO(LAYER_RAISE)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  [LAYER_COLEMAK] = HERNIAN_KEYMAP( \
// ,-----------------------------------.             ,-----------------------------------.
     ESC ,  Q  ,  W  ,  F  ,  P  ,  G  ,                J  ,  L  ,  U  ,  Y  , SCLN, MINS, XXXX,  \
// |-----+-----+-----+-----+-----+-----|             |-----+-----+-----+-----+-----+-----|
     TAB ,  A  ,  R  ,  S  ,  T  ,  D  ,                H  ,  N  ,  E  ,  I  ,  O  , QUOT, XXXX,  \
// |-----+-----+-----+-----+-----+-----|             |-----+-----+-----+-----+-----+-----|
     BSPC,  Z  ,  X  ,  C  ,  V  ,  B  ,                K  ,  M  , COMM, DOT , SLSH, ENT ,        \
// |-----+-----+-----+-----+-----+-----+-----. ,-----+-----+-----+-----+-----+-----+-----|
     LEFT, DOWN,  UP , DOWN, LOWR, LSFT, SPC ,    SPC, RSFT, LOWR, XXXX, XXXX, XXXX, XXXX,        \
// |-----+-----+-----+-----+-----+-----+-----| |-----+-----+-----+-----+-----+-----+-----'
                 LGUI, LALT, NFER, RASE, LCTL,   RCTL, RASE, XFER, RALT, RGUI                     \
//             `-----+-----+-----+-----+-----' `-----+-----+-----+-----+-----'
  ),

  [LAYER_LOWER] = HERNIAN_KEYMAP( \
// ,-----------------------------------.             ,-----------------------------------.
     TILD, EXLM,  AT , HASH, DLR , PERC,               CIRC, AMPR, ASTR, LPRN, RPRN, UNDS, XXXX,  \
// |-----+-----+-----+-----+-----+-----|             |-----+-----+-----+-----+-----+-----|
     GRV ,  1  ,  2  ,  3  ,  4  ,  5  ,                6  ,  7  ,  8  ,  9  ,  0  , DQUO, XXXX,  \
// |-----+-----+-----+-----+-----+-----|             |-----+-----+-----+-----+-----+-----|
     DEL , LBRC, RBRC, LCBR, RCBR, PIPE,               PLUS, MINS,  LT ,  GT , QUES,     ,        \
// |-----+-----+-----+-----+-----+-----+-----. ,-----+-----+-----+-----+-----+-----+-----|
     HOME, PGDN, PGUP, END ,     ,     ,     ,   BSLS, EQL ,     ,     ,     ,     ,     ,        \
// |-----+-----+-----+-----+-----+-----+-----| |-----+-----+-----+-----+-----+-----+-----'
                     ,     ,     ,     ,     ,       ,     ,     ,     ,                          \
//             `-----+-----+-----+-----+-----' `-----+-----+-----+-----+-----'
  ),

  [LAYER_RAISE] = HERNIAN_KEYMAP( \
// ,-----------------------------------.             ,-----------------------------------.
         ,  F1 ,  F2 ,  F3 ,  F4 ,  F5 ,               INS , XXXX, BSPC, DEL , ZNHN, PSCR, XXXX,  \
// |-----+-----+-----+-----+-----+-----|             |-----+-----+-----+-----+-----+-----|
         ,  F6 ,  F7 ,  F8 ,  F9 ,  F10,               LEFT, DOWN, UP,   RGHT, HIRA, XXXX, XXXX,  \
// |-----+-----+-----+-----+-----+-----|             |-----+-----+-----+-----+-----+-----|
         ,  F11,  F12,     ,     ,     ,               HOME, PGDN, PGUP, END,  EISU,     ,        \
// |-----+-----+-----+-----+-----+-----+-----. ,-----+-----+-----+-----+-----+-----+-----|
         ,     ,     ,     ,     ,     ,     ,       ,     ,     ,     ,     ,     ,     ,        \
// |-----+-----+-----+-----+-----+-----+-----| |-----+-----+-----+-----+-----+-----+-----'
                     ,     ,     ,     ,     ,       ,     ,     ,     ,                          \
//             `-----+-----+-----+-----+-----' `-----+-----+-----+-----+-----'
  )
};



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}



//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER 8
#define L_RAISE 16
#define L_FNLAYER 64
#define L_NUMLAY 128
#define L_NLOWER 136
#define L_NFNLAYER 192
#define L_MOUSECURSOR 256
#define L_ADJUST 65536
#define L_ADJUST_TRI 65560

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_RAISE:
           matrix_write_P(matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
