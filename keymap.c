#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define LAYER_COLEMAK 	0
#define LAYER_LOWER 	1
#define LAYER_RAISE 	2


#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_LOWR MO(LAYER_LOWER)
#define KC_RAIS MO(LAYER_RAISE)
#define KC_RST RESET
#define KC_BL_S BL_STEP
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD
#define KC_ZNHN 0x35
#define KC_EISU 0x39
#define KC_HIRA 0x88
#define KC_XFER 0x8a
#define KC_NFER 0x8b
#define KC_xxxx KC_NO




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [LAYER_COLEMAK] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , Q  , W  , F  , P  , G  ,                J  , L  , U  , Y  ,SCLN,MINS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , A  , R  , S  , T  , D  ,                H  , N  , E  , I  , O  ,QUOT,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     BSPC, Z  , X  , C  , V  , B  ,                K  , M  ,COMM,DOT ,SLSH,ENT ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LEFT,DOWN, UP ,RGHT,LOWR,LSFT,SPC ,     SPC ,RSFT,LOWR,RGUI,xxxx,xxxx,xxxx,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       NFER,LCTL,LALT,         RALT,RCTL,XFER
  //                  `----+----+----'        `----+----+----'
  ),

  [LAYER_LOWER] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     TILD,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,ASTR,LPRN,RPRN,UNDS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     GRV , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,DQUO,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     DEL ,PIPE,LCBR,RCBR,BSLS,xxxx,               xxxx,PLUS,MINS,EQL ,QUES,xxxx,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     HOME,PGDN,PGUP,END ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,    
  //                  `----+----+----'        `----+----+----'
  ),

  [LAYER_RAISE] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     xxxx, F1 , F2 , F3 , F4 , F5 ,               INS ,xxxx,BSPC,DEL ,xxxx,PSCR,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     xxxx, F6 , F7 , F8 , F9 , F10,               LEFT,DOWN, UP ,RGHT,xxxx,xxxx,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     xxxx, F11, F12,ZNHN,HIRA,EISU,               HOME,PGDN,PGUP,END ,xxxx,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,    
  //                  `----+----+----'        `----+----+----'
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#if 0
  switch (keycode) {
//    case QWERTY:
//      if (record->event.pressed) {
//        persistent_default_layer_set(1UL<<_QWERTY);
//      }
//      return false;
//      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
//        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
//        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
//        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
//        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
//    case ADJUST:
//      if (record->event.pressed) {
//        layer_on(_ADJUST);
//      } else {
//        layer_off(_ADJUST);
//      }
//      return false;
//      break;
  }
#endif
  return true;
}
