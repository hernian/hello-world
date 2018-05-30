// usjp.c

#include "usjp.h"
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "debug.h"
#include "report.h"
#include "host.h"

#define ARRAY_LENGTH_OF(a)  (sizeof(a) / sizeof((a)[0]))

#define INVALID_INDEX   static_cast<size_t>(-1)

typedef uint16_t    size_t;


const uint8_t   MODIFIER_BIT_L_CTRL     = 0x01;
const uint8_t   MODIFIER_BIT_L_SHIFT    = 0x02;
const uint8_t   MODIFIER_BIT_L_ALT      = 0x04;
const uint8_t   MODIFIER_BIT_L_GUI      = 0x08;
const uint8_t   MODIFIER_BIT_R_CTRL     = 0x10;
const uint8_t   MODIFIER_BIT_R_SHIFT    = 0x20;
const uint8_t   MODIFIER_BIT_R_ALT      = 0x40;
const uint8_t   MODIFIER_BIT_R_GUI      = 0x80;

const uint8_t   MODIFIER_BIT_CTRL       = MODIFIER_BIT_L_CTRL | MODIFIER_BIT_R_CTRL;
const uint8_t   MODIFIER_BIT_SHIFT      = MODIFIER_BIT_L_SHIFT | MODIFIER_BIT_R_SHIFT;
const uint8_t   MODIFIER_BIT_ALT        = MODIFIER_BIT_L_ALT | MODIFIER_BIT_R_ALT;
const uint8_t   MODIFIER_BIT_GUI        = MODIFIER_BIT_L_GUI | MODIFIER_BIT_R_GUI;

const uint8_t   KC_US_A             = 0x04;
const uint8_t   KC_US_B             = 0x05;
const uint8_t   KC_US_C             = 0x06;
const uint8_t   KC_US_D             = 0x07;
const uint8_t   KC_US_E             = 0x08;
const uint8_t   KC_US_F             = 0x09;
const uint8_t   KC_US_G             = 0x0a;
const uint8_t   KC_US_H             = 0x0b;
const uint8_t   KC_US_I             = 0x0c;
const uint8_t   KC_US_J             = 0x0d;
const uint8_t   KC_US_K             = 0x0e;
const uint8_t   KC_US_L             = 0x0f;
const uint8_t   KC_US_M             = 0x10;
const uint8_t   KC_US_N             = 0x11;
const uint8_t   KC_US_O             = 0x12;
const uint8_t   KC_US_P             = 0x13;
const uint8_t   KC_US_Q             = 0x14;
const uint8_t   KC_US_R             = 0x15;
const uint8_t   KC_US_S             = 0x16;
const uint8_t   KC_US_T             = 0x17;
const uint8_t   KC_US_U             = 0x18;
const uint8_t   KC_US_V             = 0x19;
const uint8_t   KC_US_W             = 0x1a;
const uint8_t   KC_US_X             = 0x1b;
const uint8_t   KC_US_Y             = 0x1c;
const uint8_t   KC_US_Z             = 0x1d;
const uint8_t   KC_US_1             = 0x1e;
const uint8_t   KC_US_2             = 0x1f;
const uint8_t   KC_US_3             = 0x20;
const uint8_t   KC_US_4             = 0x21;
const uint8_t   KC_US_5             = 0x22;
const uint8_t   KC_US_6             = 0x23;
const uint8_t   KC_US_7             = 0x24;
const uint8_t   KC_US_8             = 0x25;
const uint8_t   KC_US_9             = 0x26;
const uint8_t   KC_US_0             = 0x27;
const uint8_t   KC_US_BASKSPACE     = 0x2a;
const uint8_t   KC_US_SPACE         = 0x2c;
const uint8_t   KC_US_MINUS         = 0x2d;
const uint8_t   KC_US_EQUAL         = 0x2e;
const uint8_t   KC_US_LEFT_BRACKET  = 0x2f;
const uint8_t   KC_US_RIGHT_BRACKET = 0x30;
const uint8_t   KC_US_BACK_SLASH    = 0x31;
const uint8_t   KC_US_SEMI_COLON    = 0x33;
const uint8_t   KC_US_APOSTROPHE    = 0x34;
const uint8_t   KC_US_GRAVE_ACCENT  = 0x35;
const uint8_t   KC_US_COMMA         = 0x36;
const uint8_t   KC_US_DOT           = 0x37;
const uint8_t   KC_US_SLASH         = 0x38;
const uint8_t   KC_US_HOME          = 0x4a;
const uint8_t   KC_US_PAGE_UP       = 0x4b;
const uint8_t   KC_US_DEL           = 0x4c;
const uint8_t   KC_US_END           = 0x4d;
const uint8_t   KC_US_PAGE_DOWN     = 0x4e;
const uint8_t   KC_US_RIGHT_ARROW   = 0x4f;
const uint8_t   KC_US_LEFT_ARROW    = 0x50;
const uint8_t   KC_US_DOWN_ARROW    = 0x51;
const uint8_t   KC_US_UP_ARROW      = 0x52;
const uint8_t   KC_US_XFER          = 0x8a;
const uint8_t   KC_US_LEFT_SHIFT    = 0xe1;
const uint8_t   KC_US_LEFT_ALT      = 0xe2;
const uint8_t   KC_US_RIGHT_SHIFT   = 0xe5;
const uint8_t   KC_US_RIGHT_ALT     = 0xe6;



const uint8_t   KC_JP_A             = 0x04;
const uint8_t   KC_JP_B             = 0x05;
const uint8_t   KC_JP_C             = 0x06;
const uint8_t   KC_JP_D             = 0x07;
const uint8_t   KC_JP_E             = 0x08;
const uint8_t   KC_JP_F             = 0x09;
const uint8_t   KC_JP_G             = 0x0a;
const uint8_t   KC_JP_H             = 0x0b;
const uint8_t   KC_JP_I             = 0x0c;
const uint8_t   KC_JP_J             = 0x0d;
const uint8_t   KC_JP_K             = 0x0e;
const uint8_t   KC_JP_L             = 0x0f;
const uint8_t   KC_JP_M             = 0x10;
const uint8_t   KC_JP_N             = 0x11;
const uint8_t   KC_JP_O             = 0x12;
const uint8_t   KC_JP_P             = 0x13;
const uint8_t   KC_JP_Q             = 0x14;
const uint8_t   KC_JP_R             = 0x15;
const uint8_t   KC_JP_S             = 0x16;
const uint8_t   KC_JP_T             = 0x17;
const uint8_t   KC_JP_U             = 0x18;
const uint8_t   KC_JP_V             = 0x19;
const uint8_t   KC_JP_W             = 0x1a;
const uint8_t   KC_JP_X             = 0x1b;
const uint8_t   KC_JP_Y             = 0x1c;
const uint8_t   KC_JP_Z             = 0x1d;
const uint8_t   KC_JP_1             = 0x1e;
const uint8_t   KC_JP_2             = 0x1f;
const uint8_t   KC_JP_6             = 0x23;
const uint8_t   KC_JP_7             = 0x24;
const uint8_t   KC_JP_8             = 0x25;
const uint8_t   KC_JP_9             = 0x26;
const uint8_t   KC_JP_0             = 0x27;
const uint8_t   KC_JP_BACKSPACE     = 0x2a;
const uint8_t   KC_JP_SPACE         = 0x2c;
const uint8_t   KC_JP_MINUS         = 0x2d;
const uint8_t   KC_JP_CARET         = 0x2e;
const uint8_t   KC_JP_AT_MARK       = 0x2f;
const uint8_t   KC_JP_LEFT_BRACKET  = 0x30;
const uint8_t   KC_JP_RIGHT_BRACKET = 0x32;
const uint8_t   KC_JP_SEMI_COLON    = 0x33;
const uint8_t   KC_JP_COLON         = 0x34;
const uint8_t   KC_JP_ZENKAKU       = 0x35;
const uint8_t   KC_JP_COMMA         = 0x36;
const uint8_t   KC_JP_DOT           = 0x37;
const uint8_t   KC_JP_SLASH         = 0x38;
const uint8_t   KC_JP_EISUU         = 0x39;
const uint8_t   KC_JP_F1            = 0x3a;
const uint8_t   KC_JP_F2            = 0x3b;
const uint8_t   KC_JP_F3            = 0x3c;
const uint8_t   KC_JP_F4            = 0x3d;
const uint8_t   KC_JP_F5            = 0x3e;
const uint8_t   KC_JP_F6            = 0x3f;
const uint8_t   KC_JP_F7            = 0x40;
const uint8_t   KC_JP_F8            = 0x41;
const uint8_t   KC_JP_F9            = 0x42;
const uint8_t   KC_JP_F10           = 0x43;
const uint8_t   KC_JP_F11           = 0x44;
const uint8_t   KC_JP_F12           = 0x45;
const uint8_t   KC_JP_PRINT_SCREEN  = 0x46;
const uint8_t   KC_JP_INS           = 0x49;
const uint8_t   KC_JP_HOME          = 0x4a;
const uint8_t   KC_JP_PAGE_UP       = 0x4b;
const uint8_t   KC_JP_DEL           = 0x4c;
const uint8_t   KC_JP_END           = 0x4d;
const uint8_t   KC_JP_PAGE_DOWN     = 0x4e;
const uint8_t   KC_JP_RIGHT_ARROW   = 0x4f;
const uint8_t   KC_JP_LEFT_ARROW    = 0x50;
const uint8_t   KC_JP_DOWN_ARROW    = 0x51;
const uint8_t   KC_JP_UP_ARROW      = 0x52;
const uint8_t   KC_JP_BACK_SLASH    = 0x87;
const uint8_t   KC_JP_HIRAGANA      = 0x88;
const uint8_t   KC_JP_YEN           = 0x89;
const uint8_t   KC_JP_XFER          = 0x8a;
const uint8_t   KC_JP_NFER          = 0x8b;
const uint8_t   KC_JP_MENU          = 0x65;


struct KeyboardReport;
typedef void (*SendKeyboardFunc)(KeyboardReport*);



////////////////////////////////////////////////////////////////////////////////
// KeyboardReport

/**
 * USB規格で定義されているキーボードレポート
 * @note USB規格で決められたキーボードレポートの形式から万が一にも逸脱しないようにメンバー関数は持たない。
 * 代わりにstatic関数を使うようにした。
 */
struct KeyboardReport {
    enum { COUNT_KEY = 6 };
    uint8_t modifiers;              /**< モディファイアのビット集合 */
    uint8_t reserve;                /**< リザーブ */
    uint8_t keys[COUNT_KEY];        /**< 押下されたキーのキーコード */

    /**
     * 初期化する
     * @param[in] キーボードレポート
     */
    static void     Clear(KeyboardReport& keyRept);
    
    /**
     * 指定されたキーが押下されているか調べる
     * @param[in] key キーコード
     * @return keyで指定されたキーが押下されているならkeys[]内のインデックス。そうでないならINVALID_INDEX。
     */
    static size_t  FindKey(const KeyboardReport& keyRept, uint8_t key);
    
    /**
     * キーボードレポートの内容が一致するか調べる
     * @param[in] keyReptA 比較対象1
     * @param[in] keyReptB 比較対象2
     * @retval true keyReptAとkeyReptBは一致する
     * @retval false keyReptAとkeyReptBは不一致
     */
    static bool     Equals(const KeyboardReport& keyReptA, const KeyboardReport& keyReptB);

    /**
     * キーがすべて解放されているか調べる
     * @param[in] keyRept   調べるキーレポート
     * @retval true    全てのキーが解放されている
     * @retval false   いずれかのキーが押下されている
     */
    static bool     IsAllKeysReleased(const KeyboardReport& keyRept);
};

// static
void KeyboardReport::Clear(KeyboardReport& keyRept)
{
    keyRept.modifiers = 0x00;
    keyRept.reserve = 0;
    for (size_t i = 0; i < COUNT_KEY; ++i){
        keyRept.keys[i] = 0x00;
    }
}

// static
size_t KeyboardReport::FindKey(const KeyboardReport& keyRept, uint8_t key)
{
    for (size_t i = 0; i < COUNT_KEY; ++i){
        if (keyRept.keys[i] == key){
            return i;
        }
    }
    return INVALID_INDEX;
}

// static
bool KeyboardReport::Equals(const KeyboardReport& keyReptA, const KeyboardReport& keyReptB)
{
    if (keyReptA.modifiers != keyReptB.modifiers){
         return false;
    }
    for (size_t i = 0; i < COUNT_KEY; ++i){
        if (keyReptA.keys[i] != keyReptB.keys[i]){
            return false;
        }
    }
    return true;
}

// static
bool KeyboardReport::IsAllKeysReleased(const KeyboardReport& keyRept)
{
    if (keyRept.modifiers != 0){
        return false;
    }
    for (size_t i = 0; i < COUNT_KEY; ++i){
        if (keyRept.keys[i] != 0){
            return false;
        }
    }
    return true;
}



// KeyboardReport
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
// JpUsConvDesc


/**
 * US配列→JP配列変換定義
 * @note UsJpConvDescのインスタンスはPROGMEM上に配置すること
 */
struct UsJpConvDesc {
    /**
     * モディファイアの状態
     * @note 例えばUS配列で@を入力するのに Shfit+2を押下するが、このShiftは左右の
     * シフトキーのいずれでも可能である。なのでMODIFIER_BIT_x_SHIFT等とは別にモディファイアの
     * 状態を定義できるようにした。
     */
    enum ModifierType : uint8_t {
        SHIFT,                  /**< Shiftキーが必要 */
        NO_SHIFT,               /**< Shiftキーは不要 */
        ALT,                    /**< ALTキーが必要 */ 
        NO_ALT                  /**< ALTキーは不要 */
    };

    uint8_t       keyCode;          /**< 入力キーコード */
    ModifierType  modifierTypeIn;   /**< 入力モディファイアの状態 */
    uint8_t       keyCodeOut;       /**< 出力キーコード */
    ModifierType  modifierTypeOut;  /**< 出力モディファイアの状態 */

    /**
     * 変換テーブル
     */
    static const UsJpConvDesc USJP_CONV_DESCS[] PROGMEM;
    /**
     * 変換テーブルの要素数
     */
    static const size_t COUNT_USJP_CONV;

    /**
     * 入力されたキーコード・モディファイアにマッチする変換定義を取得する
     * @param[in] キーコード
     * @param[in] モディファイア
     * @return マッチした変換定義のインデックス。マッチ無しならINVALID_INDEX。
     */
    static size_t  Find(uint8_t keyCode, uint8_t modifiers);
    
    /**
     * 入力キーコードを取得する
     * @return 入力キーコードの値
     */
    uint8_t GetKeyCode() const {
        return pgm_read_byte(&keyCode);
    }

    /**
     * 入力モディファイアの状態を取得する
     * @reutrn 入力モディファイアの状態
     */
    ModifierType GetModifierTypeIn() const {
        uint8_t temp = pgm_read_byte(&modifierTypeIn);
        return static_cast<ModifierType>(temp);
    }

    /**
     * 出力キーコードを取得する
     * @return 出力キーコードの値
     */
    uint8_t GetKeyCodeOut() const {
        return pgm_read_byte(&keyCodeOut);
    }

    /**
     * 出力モディファイアの状態を取得する
     * @return 出力モディファイアの状態
     */
    ModifierType GetModifierTypeOut() const {
        uint8_t temp = pgm_read_byte(&modifierTypeOut);
        return static_cast<ModifierType>(temp);
    }

    /**
     * 入力されたキーコード・モディファイアとマッチするか調べる
     * @retval true マッチする
     * @retval false マッチしない
     */
    bool    Matchs(uint8_t keyCode, uint8_t modifiers) const;
    
    /**
     * 出力モディファイアのビット集合を取得する
     * 
     * 例えば&文字のためShift+7が入力された場合、Shift+6 を出力する。
     * 出力するShiftは、入力された左右いずれかのShiftキーを優先して出力する。
     * そのため出力するモディファイアは静的に決められず、実行時に変換定義に従って生成する。
     * @param[in] modifiersIn 入力されたモディファイア
     * @param[out] modifiersLock モディファイアのロックビット集合
     * @return 出力モディファイアのビット集合
     */
    uint8_t GetModifiersOut(uint8_t modifiersIn, uint8_t& modifiersLock) const;
};


// static 
const UsJpConvDesc UsJpConvDesc::USJP_CONV_DESCS[] PROGMEM = {
    { KC_US_GRAVE_ACCENT,    ALT,       KC_JP_ZENKAKU,          ALT  },        // Alt+`�̓X���[ �� JP��Alt+���p/�S�p�ɑ���
    { KC_US_2,               SHIFT,     KC_JP_AT_MARK,          NO_SHIFT },    // @:Shift+2 �� @
    { KC_US_6,               SHIFT,     KC_JP_CARET,            NO_SHIFT },    // ^:Shift+6 �� ^
    { KC_US_7,               SHIFT,     KC_JP_6,                SHIFT },       // &:Shift+7 �� Shift+6
    { KC_US_8,               SHIFT,     KC_JP_COLON,            SHIFT },       // *:Shift+8 �� Shift+:
    { KC_US_9,               SHIFT,     KC_JP_8,                SHIFT },       // (:Shift+9 �� Shift+8
    { KC_US_0,               SHIFT,     KC_JP_9,                SHIFT },       // ):Shift+0 �� Shift+9
    { KC_US_MINUS,           SHIFT,     KC_JP_BACK_SLASH,       SHIFT },       // _:Shift+- �� Shift+�_
    { KC_US_EQUAL,           SHIFT,     KC_JP_SEMI_COLON,       SHIFT },       // +:Shift+= �� Shift+;
    { KC_US_BACK_SLASH,      SHIFT,     KC_JP_YEN,              SHIFT },       // |:Shift+\ �� Shift+\ ��US��JP�ł�\�̃L�[�R�[�h���قȂ�
    { KC_US_GRAVE_ACCENT,    SHIFT,     KC_JP_CARET,            SHIFT },       // ~:Shift+` �� Shift+^
    { KC_US_LEFT_BRACKET,    SHIFT,     KC_JP_LEFT_BRACKET,     SHIFT },       // {:Shift+[ �� Shift+[ ��US��JP�ł�[�̃L�[�R�[�h���قȂ�
    { KC_US_RIGHT_BRACKET,   SHIFT,     KC_JP_RIGHT_BRACKET,    SHIFT },       // }:Shift+] �� Shift+] ��US��JP�ł�]�̃L�[�R�[�h���قȂ�
    { KC_US_SEMI_COLON,      SHIFT,     KC_JP_COLON,            NO_SHIFT },    // ::Shift+; �� :
    { KC_US_APOSTROPHE,      SHIFT,     KC_JP_2,                SHIFT },       // ":Shift+' �� Shift+2
    { KC_US_BACK_SLASH,      NO_SHIFT,  KC_JP_YEN,              NO_SHIFT }, // \:\ �� \ ��US��JP�ł�\�̃L�[�R�[�h���قȂ�
    { KC_US_LEFT_BRACKET,    NO_SHIFT,  KC_JP_LEFT_BRACKET,     NO_SHIFT }, // [: [ �� [ ��US��JP�ł�[�̃L�[�R�[�h���قȂ�
    { KC_US_RIGHT_BRACKET,   NO_SHIFT,  KC_JP_RIGHT_BRACKET,    NO_SHIFT }, // ]: ] �� ] ��US��JP�ł�]�̃L�[�R�[�h���قȂ�
    { KC_US_EQUAL,           NO_SHIFT,  KC_JP_MINUS,            SHIFT },    // =:= �� Shift+-
    { KC_US_GRAVE_ACCENT,    NO_SHIFT,  KC_JP_AT_MARK,          SHIFT },    // `:` �� Shift+@
    { KC_US_APOSTROPHE,      NO_SHIFT,  KC_JP_7,                SHIFT }     // ': ' �� Shift+7
};

// static
const size_t UsJpConvDesc::COUNT_USJP_CONV = ARRAY_LENGTH_OF(USJP_CONV_DESCS);

// static
size_t UsJpConvDesc::Find(uint8_t keyCode, uint8_t modifiers)
{
    for (size_t i = 0; i < COUNT_USJP_CONV; ++i){
        const UsJpConvDesc& ujcd = USJP_CONV_DESCS[i];
        bool match = ujcd.Matchs(keyCode, modifiers);
        if (match){
            return i;
        }
    }
    return INVALID_INDEX;
}

// static
bool UsJpConvDesc::Matchs(uint8_t keyCode, uint8_t modifiers) const
{
    uint8_t kc = GetKeyCode();
    if (kc != keyCode){
        return false;
    }
    bool m = false;
    ModifierType mtIn = GetModifierTypeIn();
    switch (mtIn){
      case SHIFT:
        m = ((modifiers & MODIFIER_BIT_SHIFT) != 0x00);
        break;
      case ALT:
        m = ((modifiers & MODIFIER_BIT_ALT) != 0x00);
        break;
      case NO_SHIFT:
        m = ((modifiers & MODIFIER_BIT_SHIFT) == 0x00);
        break;
      case NO_ALT:
        m = ((modifiers & MODIFIER_BIT_ALT) == 0x00);
        break;
      default:
        m = false;
        break;
    }
    return m;
}

uint8_t UsJpConvDesc::GetModifiersOut(uint8_t modifiersIn, uint8_t& modifiersLock) const
{
    uint8_t modifiersOut = 0x00;
    ModifierType mtOut = GetModifierTypeOut();
    switch (mtOut){
      case SHIFT:
        modifiersOut = ((modifiersIn & MODIFIER_BIT_SHIFT) != 0x00) ? modifiersIn: modifiersIn | MODIFIER_BIT_L_SHIFT;
        modifiersLock = ((modifiersIn & MODIFIER_BIT_R_SHIFT) != 0x00) ? MODIFIER_BIT_R_SHIFT: MODIFIER_BIT_L_SHIFT;
        break;
      case ALT:
        modifiersOut = ((modifiersIn & MODIFIER_BIT_ALT) != 0x00) ? modifiersIn: modifiersIn | MODIFIER_BIT_L_ALT;
        modifiersLock = ((modifiersIn & MODIFIER_BIT_R_ALT) != 0x00) ? MODIFIER_BIT_R_ALT: MODIFIER_BIT_L_ALT;
        break;
      case NO_SHIFT:
        modifiersOut = modifiersIn & ~MODIFIER_BIT_SHIFT;
        modifiersLock = MODIFIER_BIT_SHIFT;
        break;
      case NO_ALT:
        modifiersOut = modifiersIn & ~MODIFIER_BIT_ALT;
        modifiersLock = MODIFIER_BIT_ALT;
        break;
      break;
        modifiersOut = modifiersIn;
        modifiersLock = 0x00;
        break;
    }
    return modifiersOut;
}


// JpUsConvDesc
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
// KeyStat

/**
 * キーの状態を表す
 *
 * キーボードレポートによって現在押下されているキーが一括で通知されるが、
 * 押下されたままなのか、新しく押下されたのか、あるは開放されたキーがあるのかを
 * 知る必要がある。そのため、KeyStatは、キーボードレポートの通知にまたがってキーの
 * 状態を管理する。
 * また、キーが拡張モディファイアである場合や、拡張モディファイアで変換されたキーで
 * ある場合に必要となる追加情報を保持する。
 */
struct KeyStat {
    uint8_t             keyCode;            /**< 入力キーコード */
    uint8_t             keyCodeOut;         /**< 出力キーコード */
    uint8_t             modifiersOut;       /**< 出力モディファイアのビット集合 */
    uint8_t             modifiersLock;      /**< 出力モディファイアのロックビット集合 */
    size_t              idxExModifier;      /**< isExModifierがtrueのときに拡張モディファイアのインデックスを示す */
    bool                down:1;             /**< true:押下, false:開放 */
    bool                send:1;             /**< true:出力として送信する対象, false:対象外 */
    bool                isExModifier:1;     /**< true:拡張モディファイア, false:通常キー */

    /**
     * 内容をクリアする
     */
    void    Clear();
};


void KeyStat::Clear()
{
    memset(this, 0, sizeof(KeyStat));
    idxExModifier = INVALID_INDEX;
}

// KeyStat
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// KeyConv

class KeyConv {
  public:
    /**
     * 初期化
     */
    void    Begin(SendKeyboardFunc sendKeyboardFunc);
    
    /**
     * 状態更新
     * @note loop()から常に呼び出すこと
     */
    void    Update();
    
    /**
     * 受信したキーボードレポートの解釈
     * @param[in] pKeyRept 入力されたキーボードレポート
     * @param[in] len 入力されたキーボードレポートのサイズ
     */
    void    ParseKeyboardReport(const KeyboardReport& krp);

  private:
    uint8_t UpdateHeldKeys(const KeyboardReport& krp);
    void    ParseUpKeys();
    void    CompactKeyStats();
    void    SetModifiers(uint8_t modifiers);
    void    ParseKeyDown(KeyStat& ks);
    void    AddNewKeys(const KeyboardReport& krp, uint8_t bitsUsedKey);
    bool    ConflictsModifiers(uint8_t mods1, uint8_t modsLock1, uint8_t mods2, uint8_t modsLock2);
    void    SendReport(size_t idxEnd);
    void    UpConflictKeys(size_t idxEnd, uint8_t modsCheck, uint8_t modsLockCheck, uint8_t& modifiers, uint8_t& modifiersLock);
    void    TryToSendReport();
    void    HandleKeyboardReport(const KeyboardReport& krp);

  private:
    enum ExModStat {
        EXMOD_STAT_NORMAL,
        EXMOD_STAT_PENDING,
        EXMOD_STAT_ACTIVE
    };

  private:
    enum : size_t{
        COUNT_KEY_REPT = 8,
        COUNT_KEY_STAT = 6 * 2  /**< _keyStats[]の要素数。前回までと今回のキーボードレポート2つ分のキー状態 */
    };

    SendKeyboardFunc        _sendKeyboardFunc;
    KeyboardReport          _krpPending;
    uint8_t                 _keyCodeExMod;
    ExModStat               _exModStat;

    uint8_t                 _countKeyStat;              /**< _keyStats[]の有効な要素の数 */
    KeyStat                 _keyStats[COUNT_KEY_STAT];  /**< キー状態の配列 */
    uint8_t                 _modifiers;                 /**< 入力されたモディファイアのビット集合 */
    KeyboardReport          _keyboardReport;            /**< 最後に出力したキーボードレポート */
};



void KeyConv::Begin(SendKeyboardFunc skf)
{
    _sendKeyboardFunc = skf;
    _countKeyStat = 0;
    memset(_keyStats, 0, sizeof(_keyStats));
    _modifiers = 0;
    memset(&_keyboardReport, 0, sizeof(_keyboardReport));
}


uint8_t KeyConv::UpdateHeldKeys(const KeyboardReport& krp)
{
    uint8_t bitsUsedKey = 0x00;
    for (size_t i = 0; i < _countKeyStat; ++i){
        KeyStat& ks = _keyStats[i];
        int16_t idxKeyCode = KeyboardReport::FindKey(krp, ks.keyCode);
        if (idxKeyCode != -1){
            bitsUsedKey |= 0x01 << idxKeyCode;
        }
        else{
            ks.down = false;
            ks.send = false;
        }
    }
    return bitsUsedKey;
}


#if 0
void KeyConv::ParseUpKeys()
{
    for (size_t i = 0; i < _countKeyStat; ++i){
        KeyStat& ks = _keyStats[i];
        if (ks.down){
            continue;
        }
        if (ks.isExModifier){
            ExModifierStat& ems = _pExModifierStats[ks.idxExModifier];
                        ems.SetEnabled(false);
        }
    }
}
#endif


void KeyConv::CompactKeyStats()
{
    size_t idxDst = 0;
    for (size_t i = 0; i < _countKeyStat; ++i){
        KeyStat& ks = _keyStats[i];
        if (ks.down){
            if (i != idxDst){
                _keyStats[idxDst] = ks;
            }
            ++idxDst;
        }
    }
    _countKeyStat = idxDst;
}


void KeyConv::SetModifiers(uint8_t modifiers)
{
    if (_modifiers == modifiers){
        return;
    }
    const uint8_t modifiersLock = 0xff;
    for (size_t i = 0; i < _countKeyStat; ++i){
        const KeyStat& ks = _keyStats[i];
        if (ks.send == false){
            continue;
        }
        bool conflicts = ConflictsModifiers(ks.modifiersOut, ks.modifiersLock, modifiers, modifiersLock);
        if (conflicts){
            size_t idxEnd = i + 1;
            SendReport(idxEnd);
            uint8_t temp1 = 0x00;
            uint8_t temp2 = 0x00;
            UpConflictKeys(idxEnd, modifiers, modifiersLock, temp1, temp2);
        }
    }
    _modifiers = modifiers;
}


void KeyConv::ParseKeyDown(KeyStat& ks)
{
    size_t idxUjc = UsJpConvDesc::Find(ks.keyCode, _modifiers);
//    xprintf("usjp:%d\r\n", idxUjc);

    if (idxUjc != INVALID_INDEX){
        const UsJpConvDesc& ujcd = UsJpConvDesc::USJP_CONV_DESCS[idxUjc];
        ks.keyCodeOut = ujcd.GetKeyCodeOut();
        ks.modifiersOut = ujcd.GetModifiersOut(_modifiers, ks.modifiersLock);
        ks.send = true;
        return;
    }

    ks.keyCodeOut = ks.keyCode;
    ks.modifiersOut = 0x00;
    ks.modifiersLock = 0x00;
    ks.send = true;
}


const uint8_t keyCodesReject[] PROGMEM = {
    KC_US_RIGHT_ARROW,
    KC_US_LEFT_ARROW,
    KC_US_UP_ARROW,
    KC_US_DOWN_ARROW,
    KC_US_BASKSPACE
};


const size_t LENGTH_KEY_CODES_REJECT = ARRAY_LENGTH_OF(keyCodesReject);


bool isRejectKeyCode(uint8_t keyCode)
{
    for (size_t i = 0; i < LENGTH_KEY_CODES_REJECT; ++i){
        uint8_t kc = pgm_read_byte(&keyCodesReject[i]);
        if (keyCode == kc){
            return true;
        }
    }
    return false;
}


void KeyConv::AddNewKeys(const KeyboardReport& krp, uint8_t bitsUsedKey)
{
    for (size_t i = 0; i < KeyboardReport::COUNT_KEY; ++i){
        uint8_t mask = 0x01 << i;
        if ((mask & bitsUsedKey) != 0){
            continue;
        }
        uint8_t keyCode = krp.keys[i];
        if (keyCode == 0x00){
            continue;
        }
        // 矯正モード
//        if (isRejectKeyCode(keyCode)){
//            continue;
//        }
        if (_countKeyStat >= COUNT_KEY_STAT){
            break;
        }
        KeyStat& ks = _keyStats[_countKeyStat];
        ks.Clear();
        ks.keyCode = keyCode;
        ks.down = true;
        ParseKeyDown(ks);
        if (ks.keyCode != 0x00){
            ++_countKeyStat;
        }
   }
}


bool  KeyConv::ConflictsModifiers(uint8_t mods1, uint8_t modsLock1, uint8_t mods2, uint8_t modsLock2)
{
    uint8_t mask = modsLock1 & modsLock2;
    uint8_t temp1 = mods1 & mask;
    uint8_t temp2 = mods2 & mask;
    return (temp1 != temp2);
}


void KeyConv::SendReport(size_t idxEnd)
{
    KeyboardReport krp;
    KeyboardReport::Clear(krp);
    krp.modifiers = _modifiers;
    size_t idxKey = 0;
    for (size_t i = 0; i < idxEnd; ++i){
        const KeyStat& ks = _keyStats[i];
        if (ks.send == false){
            continue;
        }
        krp.keys[idxKey++] = ks.keyCodeOut;
        krp.modifiers = (krp.modifiers & ~ks.modifiersLock) | ks.modifiersOut;
    }
    bool equals = KeyboardReport::Equals(krp, _keyboardReport);
    if (equals){
        return;
    }
    _sendKeyboardFunc(&krp);
    _keyboardReport = krp;
}


void KeyConv::UpConflictKeys(size_t idxEnd, uint8_t modsCheck, uint8_t modsLockCheck, uint8_t& modifiers, uint8_t& modifiersLock)
{
    modifiers = _modifiers;
    modifiersLock = 0x00;
    for (size_t i = 0; i < idxEnd; ++i){
        KeyStat& ks = _keyStats[i];
        if (ks.send == false){
            continue;
        }
        bool conflicts = ConflictsModifiers(modsCheck, modsLockCheck, ks.modifiersOut, ks.modifiersLock);
        if (conflicts){
            ks.send = false;
            continue;
        }
        modifiers = (modifiers & ~ks.modifiersLock) | ks.modifiersOut;
        modifiersLock |= ks.modifiersLock;
    }
}


void KeyConv::TryToSendReport()
{
    uint8_t modifiers = _modifiers;
    uint8_t modifiersLock = 0x00;
    for (size_t i = 0; i < _countKeyStat; ++i){
        const KeyStat& ks = _keyStats[i];
        if (ks.send == false){
            continue;
        }
        bool conflicts = ConflictsModifiers(modifiers, modifiersLock, ks.modifiersOut, ks.modifiersLock);
        if (conflicts){
            SendReport(i);
            UpConflictKeys(i, ks.modifiersOut, ks.modifiersLock, modifiers, modifiersLock);
        }
        modifiers = (modifiers & ~ks.modifiersLock) | ks.modifiersOut;
        modifiersLock |= ks.modifiersLock;
    }
    SendReport(_countKeyStat);
}



void KeyConv::ParseKeyboardReport(const KeyboardReport& krp)
{
    uint8_t bitsUsedKeys = UpdateHeldKeys(krp);
//  ParseUpKeys();
    CompactKeyStats();
    SetModifiers(krp.modifiers);
    AddNewKeys(krp, bitsUsedKeys);
    TryToSendReport();
}



// KeyConv
////////////////////////////////////////////////////////////////////



static KeyConv g_keyConv;


void usjp_send_keyboard(report_keyboard_t* rep_src)
{
    KeyboardReport* pkrp = reinterpret_cast<KeyboardReport*>(rep_src);
    g_keyConv.ParseKeyboardReport(*pkrp);
}



void usjp_init()
{
//    debug_enable=true;
    println("usjp_init");

    host_driver_t* driver = host_get_driver();
    SendKeyboardFunc orgSendKeyboardFunc = reinterpret_cast<SendKeyboardFunc>(driver->send_keyboard);
    g_keyConv.Begin(orgSendKeyboardFunc);
    driver->send_keyboard = usjp_send_keyboard;
}


