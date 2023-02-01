#ifndef SRC_sfleta_DECIMAL_H_
#define SRC_sfleta_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdio.h>

#define EXP_MASK 0x00ff0000;
#define NULL_SCALE 0x80000000;
#define NULL_MASK 0x00000000;
#define DECIMAL_NORMAL {{0, 0, 0, 0}, sfleta_NORMAL_VALUE};
#define DECIMAL_NORMAL_SUPER {{0, 0, 0, 0, 0, 0, 0}, sfleta_NORMAL_VALUE};

enum { LOW, MID, HIGH, SCALE };
enum { NLOW, NMID, NHIGH, SLOW, SMID, SHIGH, SSCALE };

typedef enum {
  sfleta_NORMAL_VALUE = 0,
  sfleta_INFINITY = 1,
  sfleta_NEGATIVE_INFINITY = 2,
  sfleta_NAN = 3
} value_type_t;

typedef struct {
  unsigned int bits[4];
  value_type_t value_type;
} sfleta_decimal;

typedef struct {
  unsigned int bits[7];
  value_type_t value_type;
} sfleta_decimal_super;

//  Арифметические операторы
//  При ошибке во время операции в переменную value_type записывается тип ошибки
sfleta_decimal sfleta_add(sfleta_decimal, sfleta_decimal);
sfleta_decimal sfleta_sub(sfleta_decimal, sfleta_decimal);
sfleta_decimal sfleta_mul(sfleta_decimal, sfleta_decimal);
sfleta_decimal sfleta_div(sfleta_decimal, sfleta_decimal);
sfleta_decimal sfleta_mod(sfleta_decimal, sfleta_decimal);

//  Операторы сравнение
//  Возвращаемое значение: 0 - TRUE, 1 - FALSE
int sfleta_is_less(sfleta_decimal, sfleta_decimal);
int sfleta_is_less_or_equal(sfleta_decimal, sfleta_decimal);
int sfleta_is_greater(sfleta_decimal, sfleta_decimal);
int sfleta_is_greater_or_equal(sfleta_decimal, sfleta_decimal);
int sfleta_is_equal(sfleta_decimal, sfleta_decimal);
int sfleta_is_not_equal(sfleta_decimal, sfleta_decimal);

//  Преобразователи
//  Возвращаемое значение - код ошибки: 0 - SUCCESS, 1 - CONVERTING ERROR
int sfleta_from_int_to_decimal(int src, sfleta_decimal *dst);
int sfleta_from_float_to_decimal(float src, sfleta_decimal *dst);
int sfleta_from_decimal_to_int(sfleta_decimal src, int *dst);
int sfleta_from_decimal_to_float(sfleta_decimal src, float *dst);

//  Другие функции
sfleta_decimal sfleta_floor(sfleta_decimal);
sfleta_decimal sfleta_round(sfleta_decimal);
sfleta_decimal sfleta_truncate(sfleta_decimal);
sfleta_decimal sfleta_negate(sfleta_decimal);

//  Вспомогательные функции
void sfleta_decimal_set_default(sfleta_decimal *dst);

// Установка и получение bit, scale
int sfleta_getBit(sfleta_decimal src, int i);
void sfleta_setBit(sfleta_decimal *dst, int i, int value);
int sfleta_getScale(sfleta_decimal src);
void sfleta_setScale(sfleta_decimal *dst, int value);
int sfleta_getFloatExp(float src);
int sfleta_getBitFloat(float src, int i);

// Функции установки знака "-" или "+" в SCALE*/
void sfleta_setSign(sfleta_decimal *dst, int value);
int sfleta_getSign(sfleta_decimal src);  // функция получения знака числа

// Умножение decimal на 10 */
sfleta_decimal sfleta_multi_10(sfleta_decimal src);
// Сдвиг влево
sfleta_decimal sfleta_move_left(sfleta_decimal src, int shift);
// Функция установки в decimal inf + super decimal inf
sfleta_decimal sfleta_decimal_set_inf(int sign);

// Функции выравнивания scale
void sfleta_equality_scale(sfleta_decimal *dec1, sfleta_decimal *dec2);
sfleta_decimal sfleta_increase_scale(int diffScale, sfleta_decimal src);

// Функция деления decimal на 10
sfleta_decimal sfleta_div_10_decimal(sfleta_decimal);
int sfleta_decimal_equal_int(sfleta_decimal dec, unsigned int value);
int sfleta_move_left_for_div(sfleta_decimal dec1, sfleta_decimal *dec2);
sfleta_decimal sfleta_move_right(sfleta_decimal src, int shift);
int sfleta_mod_div_10(sfleta_decimal src_s);

/*------- super decimal fuctions start -----------*/
sfleta_decimal_super sfleta_convert_to_super(sfleta_decimal);
void sfleta_displayBits_super(sfleta_decimal_super);
void sfleta_equality_scale_super(sfleta_decimal_super *dec1_s,
                              sfleta_decimal_super *dec2_s);
sfleta_decimal_super sfleta_increase_scale_super(int diffScale,
                                           sfleta_decimal_super src_s);
sfleta_decimal_super sfleta_multi_10_super(sfleta_decimal_super src_s);
sfleta_decimal_super sfleta_move_left_super(sfleta_decimal_super src_s, int shift);
sfleta_decimal_super sfleta_super_set_inf(int sign);
sfleta_decimal_super sfleta_add_simple_super(sfleta_decimal_super dec1_s,
                                       sfleta_decimal_super dec2_s);

int sfleta_getBit_super(sfleta_decimal_super src_s, int i);
int sfleta_getSign_super(sfleta_decimal_super src_s);
void sfleta_setBit_super(sfleta_decimal_super *dst_s, int i, int value);
void sfleta_setScale_super(sfleta_decimal_super *dst_s, int value);
int sfleta_getScale_super(sfleta_decimal_super src);
void sfleta_setSign_super(sfleta_decimal_super *dst, int value);
sfleta_decimal sfleta_convert_to_decimal(sfleta_decimal_super);
sfleta_decimal_super sfleta_div_10_super(sfleta_decimal_super src_s);
sfleta_decimal_super sfleta_sub_simple_super(sfleta_decimal_super dec1_s, sfleta_decimal_super dec2_s);
int sfleta_mod_div_10_super(sfleta_decimal_super src_s);
sfleta_decimal_super sfleta_move_right_super(sfleta_decimal_super src, int shift);
int sfleta_move_left_for_div_super(sfleta_decimal_super dec1, sfleta_decimal_super *dec2);
sfleta_decimal_super sfleta_mod_super(sfleta_decimal_super dec1, sfleta_decimal_super dec2);
sfleta_decimal_super sfleta_div_simple_super(sfleta_decimal_super dec1, sfleta_decimal_super dec2);
int sfleta_is_greater_or_equal_super(sfleta_decimal_super dec1_s, sfleta_decimal_super dec2_s);
int sfleta_is_greater_super(sfleta_decimal_super dec1_s, sfleta_decimal_super dec2_s);
int sfleta_is_equal_super(sfleta_decimal_super dec1_s, sfleta_decimal_super dec2_s);
int sfleta_decimal_is_equal_null_super(sfleta_decimal_super dec);
/*------- super decimal fuctions end -----------*/

#endif  //  SRC_sfleta_DECIMAL_H_
