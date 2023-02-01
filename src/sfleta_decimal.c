#include "sfleta_decimal.h"

/******* Арифметические операторы *******/
sfleta_decimal sfleta_add(sfleta_decimal dec1, sfleta_decimal dec2) {
  sfleta_decimal dec = DECIMAL_NORMAL;
  if (dec1.value_type == sfleta_NAN || dec2.value_type == sfleta_NAN ||
      (dec1.value_type == sfleta_INFINITY &&
       dec2.value_type == sfleta_NEGATIVE_INFINITY) ||
      (dec1.value_type == sfleta_NEGATIVE_INFINITY &&
       dec2.value_type == sfleta_INFINITY)) {
      dec.value_type = sfleta_NAN;
  } else if (dec1.value_type == sfleta_INFINITY ||
             dec2.value_type == sfleta_INFINITY) {
      dec.value_type = sfleta_INFINITY;
  } else if (dec1.value_type == sfleta_NEGATIVE_INFINITY ||
             dec2.value_type == sfleta_NEGATIVE_INFINITY) {
      dec.value_type = sfleta_NEGATIVE_INFINITY;
  } else if (dec1.value_type == sfleta_NORMAL_VALUE &&
             dec2.value_type == sfleta_NORMAL_VALUE) {
      sfleta_decimal_super dec1_s = sfleta_convert_to_super(dec1);
      sfleta_decimal_super dec2_s = sfleta_convert_to_super(dec2);
      int dec1_s_sign = sfleta_getSign(dec1);
      int dec2_s_sign = sfleta_getSign(dec2);

      sfleta_equality_scale_super(&dec1_s, &dec2_s);

      sfleta_decimal_super dec_s = DECIMAL_NORMAL_SUPER;
      int scale_s = sfleta_getScale_super(dec1_s);
      if (dec1_s_sign == 0 && dec2_s_sign == 0) {
        dec_s = sfleta_add_simple_super(dec1_s, dec2_s);
      } else if (dec1_s_sign == 1 && dec2_s_sign == 1) {
        sfleta_setSign_super(&dec1_s, 0);
        sfleta_setSign_super(&dec2_s, 0);
        dec_s = sfleta_add_simple_super(dec1_s, dec2_s);
        sfleta_setSign_super(&dec_s, 1);
      } else if (dec1_s_sign == 0 && dec2_s_sign == 1) {
        sfleta_setSign_super(&dec2_s, 0);
        dec_s = sfleta_sub_simple_super(dec1_s, dec2_s);
      } else if (dec1_s_sign == 1 && dec2_s_sign == 0) {
        sfleta_setSign_super(&dec1_s, 0);
        dec_s = sfleta_sub_simple_super(dec2_s, dec1_s);
      }
      sfleta_setScale_super(&dec_s, scale_s);
      dec = sfleta_convert_to_decimal(dec_s);
  }
  return dec;
}

sfleta_decimal sfleta_sub(sfleta_decimal dec1, sfleta_decimal dec2) {
  sfleta_decimal dec = DECIMAL_NORMAL;
  if (dec1.value_type == sfleta_NAN || dec2.value_type == sfleta_NAN ||
      (dec1.value_type == sfleta_INFINITY && dec2.value_type == sfleta_INFINITY) ||
      (dec1.value_type == sfleta_NEGATIVE_INFINITY &&
       dec2.value_type == sfleta_NEGATIVE_INFINITY)) {
    dec.value_type = sfleta_NAN;
  } else if ((dec1.value_type == sfleta_INFINITY &&
              dec2.value_type == sfleta_NEGATIVE_INFINITY) ||
             (dec1.value_type == sfleta_INFINITY &&
              dec2.value_type == sfleta_NORMAL_VALUE) ||
             (dec1.value_type == sfleta_NORMAL_VALUE &&
              dec2.value_type == sfleta_NEGATIVE_INFINITY)) {
    dec.value_type = sfleta_INFINITY;
  } else if ((dec1.value_type == sfleta_NEGATIVE_INFINITY &&
              dec2.value_type == sfleta_INFINITY) ||
             (dec1.value_type == sfleta_NEGATIVE_INFINITY &&
              dec2.value_type == sfleta_NORMAL_VALUE) ||
             (dec1.value_type == sfleta_NORMAL_VALUE &&
              dec2.value_type == sfleta_INFINITY)) {
    dec.value_type = sfleta_NEGATIVE_INFINITY;
  } else if (dec1.value_type == sfleta_NORMAL_VALUE &&
             dec2.value_type == sfleta_NORMAL_VALUE) {
    int dec1_s_sign = sfleta_getSign(dec1);
    int dec2_s_sign = sfleta_getSign(dec2);
    sfleta_decimal_super dec1_s = sfleta_convert_to_super(dec1);
    sfleta_decimal_super dec2_s = sfleta_convert_to_super(dec2);
    sfleta_equality_scale_super(&dec1_s, &dec2_s);
    sfleta_decimal_super dec_s = DECIMAL_NORMAL_SUPER;
    int scale_s = sfleta_getScale_super(dec1_s);

    if (dec1_s_sign == 0 && dec2_s_sign == 0) {
      dec_s = sfleta_sub_simple_super(dec1_s, dec2_s);
    } else if (dec1_s_sign == 1 && dec2_s_sign == 1) {
      sfleta_setSign_super(&dec2_s, 0);
      dec_s = sfleta_sub_simple_super(dec2_s, dec1_s);
    } else if (dec1_s_sign == 1 && dec2_s_sign == 0) {
      sfleta_setSign_super(&dec1_s, 0);
      sfleta_setSign_super(&dec2_s, 0);
      dec_s = sfleta_add_simple_super(dec1_s, dec2_s);
      sfleta_setSign_super(&dec_s, 1);
    } else if (dec1_s_sign == 0 && dec2_s_sign == 1) {
      dec_s = sfleta_add_simple_super(dec1_s, dec2_s);
    }
    sfleta_setScale_super(&dec_s, scale_s);
    dec = sfleta_convert_to_decimal(dec_s);
  }
  return dec;
}

sfleta_decimal sfleta_mul(sfleta_decimal dec1, sfleta_decimal dec2) {
  sfleta_decimal res_D = DECIMAL_NORMAL;
  sfleta_decimal_super res = DECIMAL_NORMAL_SUPER;
  sfleta_decimal_super dec1_S = sfleta_convert_to_super(dec1);
  int resSign = sfleta_getSign(dec1) ^ sfleta_getSign(dec2);
  if (dec1.value_type == sfleta_NAN || dec2.value_type == sfleta_NAN) {
    res_D.value_type = sfleta_NAN;
  } else if (dec1.value_type == sfleta_INFINITY ||
             dec2.value_type == sfleta_INFINITY) {
    if ((!sfleta_decimal_equal_int(dec1, 0) && !dec1.value_type) ||
        (!sfleta_decimal_equal_int(dec2, 0) && !dec2.value_type)) {
      res_D.value_type = sfleta_NAN;
    } else if (resSign || dec1.value_type == sfleta_NEGATIVE_INFINITY ||
               dec2.value_type == sfleta_NEGATIVE_INFINITY) {
      res_D.value_type = sfleta_NEGATIVE_INFINITY;
    } else {
      res_D.value_type = sfleta_INFINITY;
    }
  } else if (dec1.value_type == sfleta_NEGATIVE_INFINITY ||
             dec2.value_type == sfleta_NEGATIVE_INFINITY) {
    if ((!sfleta_decimal_equal_int(dec1, 0) && !dec1.value_type) ||
        (!sfleta_decimal_equal_int(dec2, 0) && !dec2.value_type)) {
      res_D.value_type = sfleta_NAN;
    } else if (resSign || (dec1.value_type == sfleta_NEGATIVE_INFINITY &&
                           dec2.value_type == sfleta_NEGATIVE_INFINITY)) {
      res_D.value_type = sfleta_INFINITY;
    } else {
      res_D.value_type = sfleta_NEGATIVE_INFINITY;
    }
  } else if (!sfleta_decimal_equal_int(dec1, 0) ||
             !sfleta_decimal_equal_int(dec2, 0)) {
    if (!sfleta_decimal_equal_int(dec1, 0)) {
      sfleta_setScale(&res_D, sfleta_getScale(dec1));
    } else {
      sfleta_setScale(&res_D, sfleta_getScale(dec2));
    }
    sfleta_setSign(&res_D, resSign);
  } else {
    int resScale = sfleta_getScale(dec1) + sfleta_getScale(dec2);
    while (sfleta_decimal_equal_int(dec2, 0)) {
      if (dec2.bits[0] & 1) res = sfleta_add_simple_super(res, dec1_S);
      dec1_S = sfleta_move_left_super(dec1_S, 1);
      dec2 = sfleta_move_right(dec2, 1);
    }
    sfleta_setScale_super(&res, resScale);
    res_D = sfleta_convert_to_decimal(res);
    if (!res_D.value_type) {
      sfleta_setSign(&res_D, resSign);
    } else {
      res_D.value_type = resSign ? sfleta_NEGATIVE_INFINITY : sfleta_INFINITY;
    }
  }
  return res_D;
}

sfleta_decimal sfleta_div(sfleta_decimal dec1, sfleta_decimal dec2) {
  sfleta_decimal res = DECIMAL_NORMAL;
  int resSign = sfleta_getSign(dec1) ^ sfleta_getSign(dec2);
  if (dec1.value_type || dec2.value_type) {
    if ((dec1.value_type && dec2.value_type) || dec1.value_type == sfleta_NAN ||
        dec2.value_type == sfleta_NAN) {
      res.value_type = sfleta_NAN;
    } else if (dec1.value_type == sfleta_INFINITY) {
      res.value_type = sfleta_getSign(dec2) ? sfleta_NEGATIVE_INFINITY : sfleta_INFINITY;
    } else if (dec1.value_type == sfleta_NEGATIVE_INFINITY) {
      res.value_type = sfleta_getSign(dec2) ? sfleta_INFINITY : sfleta_NEGATIVE_INFINITY;
    } else if (dec2.value_type == sfleta_INFINITY) {
      sfleta_setSign(&res, sfleta_getSign(dec1));
    } else if (dec2.value_type == sfleta_NEGATIVE_INFINITY) {
      sfleta_setSign(&res, !sfleta_getSign(dec1));
    }
  } else if (!sfleta_decimal_equal_int(dec2, 0)) {
    if (!sfleta_decimal_equal_int(dec1, 0)) {
      res.value_type = sfleta_NAN;
    } else {
      res.value_type = resSign ? sfleta_NEGATIVE_INFINITY : sfleta_INFINITY;
    }
  } else if (!sfleta_decimal_equal_int(dec1, 0)) {
    if (!sfleta_decimal_equal_int(dec2, 0)) {
      res.value_type = sfleta_NAN;
    } else {
      resSign ? sfleta_setSign(&res, 1) : sfleta_setSign(&res, 0);
      sfleta_setScale(&res, sfleta_getScale(dec1));
    }
  } else if (!sfleta_decimal_equal_int(dec2, 1) ||
             !sfleta_decimal_equal_int(dec2, (unsigned)(-1))) {
    if (!sfleta_getScale(dec1)) sfleta_equality_scale(&dec1, &dec2);
    res = dec1;
    int errorScale = sfleta_getScale(dec1) > sfleta_getScale(dec2)
                         ? sfleta_getScale(dec1) - sfleta_getScale(dec2)
                         : 0;
    sfleta_setScale(&res, errorScale);
    resSign ? sfleta_setSign(&res, 1) : sfleta_setSign(&res, 0);
  } else {
    sfleta_decimal_super dec1_S = sfleta_convert_to_super(dec1);
    sfleta_decimal_super dec2_S = sfleta_convert_to_super(dec2);
    sfleta_equality_scale_super(&dec1_S, &dec2_S);
    sfleta_decimal_super res_S = sfleta_div_simple_super(dec1_S, dec2_S);
    dec1_S = sfleta_mod_super(dec1_S, dec2_S);
    int tmpScale = 0;
    for (sfleta_decimal_super tmpDec = {{10, 0, 0, 0, 0, 0, 0}, 0};
         !sfleta_is_greater_or_equal_super(res_S, tmpDec);
         tmpDec = sfleta_multi_10_super(tmpDec), tmpScale++) {
    }
    int resScale = 0;
    for (; resScale + tmpScale < 29 && sfleta_decimal_is_equal_null_super(dec1_S);
         resScale++) {
      dec1_S = sfleta_multi_10_super(dec1_S);
      res_S = sfleta_multi_10_super(res_S);
      res_S = sfleta_add_simple_super(res_S, sfleta_div_simple_super(dec1_S, dec2_S));
      dec1_S = sfleta_mod_super(dec1_S, dec2_S);
    }
    sfleta_setScale_super(&res_S, resScale);
    res = sfleta_convert_to_decimal(res_S);
    if (!sfleta_mod_div_10(res) && resScale) {
      resScale = sfleta_getScale(res);
      for (; !sfleta_mod_div_10(res); res = sfleta_div_10_decimal(res), resScale--) {
      }
      sfleta_setScale(&res, resScale);
    }
    if (!res.value_type) {
      sfleta_setSign(&res, resSign);
    } else {
      res.value_type = resSign ? sfleta_NEGATIVE_INFINITY : sfleta_INFINITY;
    }
  }
  return res;
}

sfleta_decimal sfleta_mod(sfleta_decimal dec1, sfleta_decimal dec2) {
  sfleta_decimal oneBitPositive = {{1, 0, 0, 0}, sfleta_NORMAL_VALUE};
  sfleta_decimal oneBitNegative = {{1, 0, 0, 0}, sfleta_NORMAL_VALUE};
  sfleta_setSign(&oneBitNegative, 1);
  int resSign = sfleta_getSign(dec1);
  sfleta_setSign(&dec1, 0);
  sfleta_setSign(&dec2, 0);
  int resScale = sfleta_getScale(dec1) >= sfleta_getScale(dec2) ? sfleta_getScale(dec1)
                                                          : sfleta_getScale(dec2);
  if (dec1.value_type || dec2.value_type == sfleta_NAN ||
      (!sfleta_decimal_equal_int(dec2, 0) && !dec2.value_type)) {
    sfleta_decimal_set_default(&dec1);
    dec1.value_type = sfleta_NAN;
  } else if (!sfleta_decimal_equal_int(dec1, 0)) {
    sfleta_decimal_set_default(&dec1);
  } else if (!sfleta_decimal_equal_int(dec2, 1) ||
             !sfleta_decimal_equal_int(dec2, (unsigned int)(-1))) {
    sfleta_decimal_set_default(&dec1);
    sfleta_setScale(&dec1, resScale);
    sfleta_setSign(&dec1, resSign);
  } else if (!sfleta_decimal_equal_int(dec1, 1) ||
             !sfleta_decimal_equal_int(dec1, (unsigned int)(-1))) {
    dec1 = resSign ? oneBitNegative : oneBitPositive;
    sfleta_setSign(&dec1, resSign);
    sfleta_setScale(&dec1, resScale);
  } else if (dec2.value_type == sfleta_INFINITY ||
             dec2.value_type == sfleta_NEGATIVE_INFINITY) {
    dec1 = resSign ? oneBitNegative : oneBitPositive;
  } else {
    if (!sfleta_is_greater_or_equal(dec1, dec2)) {
      sfleta_decimal_super dec1_S = sfleta_convert_to_super(dec1);
      sfleta_decimal_super dec2_S = sfleta_convert_to_super(dec2);
      sfleta_equality_scale_super(&dec1_S, &dec2_S);
      int scale = sfleta_move_left_for_div_super(dec1_S, &dec2_S);
      for (; scale >= 0; scale--) {
        if (!sfleta_is_greater_or_equal_super(dec1_S, dec2_S))
          dec1_S = sfleta_sub_simple_super(dec1_S, dec2_S);
        dec2_S = sfleta_move_right_super(dec2_S, 1);
      }
      dec1 = sfleta_convert_to_decimal(dec1_S);
    } else {
      resScale = sfleta_getScale(dec1);
    }
    sfleta_setScale(&dec1, resScale);
    sfleta_setSign(&dec1, resSign);
  }
  return dec1;
}

/********** Операторы сравнения *********/
int sfleta_is_equal(sfleta_decimal dec1, sfleta_decimal dec2) {
  int result = 0;
  int sign_dec1 = sfleta_getSign(dec1);
  int sign_dec2 = sfleta_getSign(dec2);
  if (dec1.value_type == sfleta_INFINITY && dec2.value_type == sfleta_INFINITY) {
    result = 0;
  } else if (dec1.value_type == sfleta_NEGATIVE_INFINITY &&
             dec2.value_type == sfleta_NEGATIVE_INFINITY) {
    result = 0;
  } else if (dec1.value_type == sfleta_NAN || dec2.value_type == sfleta_NAN ||
             dec1.value_type == sfleta_INFINITY ||
             dec2.value_type == sfleta_INFINITY ||
             dec1.value_type == sfleta_NEGATIVE_INFINITY ||
             dec2.value_type == sfleta_NEGATIVE_INFINITY) {
    result = 1;
  } else if ((!dec1.bits[0] && !dec1.bits[1] && !dec1.bits[2])
              && (!dec2.bits[0] && !dec2.bits[1] && !dec2.bits[2])) {
    result = 0;
  } else if (sign_dec1 != sign_dec2) {
    result = 1;
  } else {
    sfleta_decimal_super dec1_s = sfleta_convert_to_super(dec1);
    sfleta_decimal_super dec2_s = sfleta_convert_to_super(dec2);
    sfleta_equality_scale_super(&dec1_s, &dec2_s);
    for (int i = SHIGH; i >= NLOW && !result; i--) {
      if (dec1_s.bits[i] != dec2_s.bits[i]) {
        result = 1;
      }
    }
  }
  return result;
}

int sfleta_is_not_equal(sfleta_decimal dec1, sfleta_decimal dec2) {
  int result = 0;
  if (sfleta_is_equal(dec1, dec2) == 1) {
    result = 1;
  }
  return !result;
}

int sfleta_is_less(sfleta_decimal dec1, sfleta_decimal dec2) {
  int result = 1;
  int dec1_sign = sfleta_getSign(dec1);
  int dec2_sign = sfleta_getSign(dec2);
  sfleta_decimal_super dec1_s = sfleta_convert_to_super(dec1);
  sfleta_decimal_super dec2_s = sfleta_convert_to_super(dec2);
  sfleta_equality_scale_super(&dec1_s, &dec2_s);
  if (dec1.value_type == sfleta_NORMAL_VALUE && dec2.value_type == sfleta_NORMAL_VALUE) {
    if (!dec1.bits[0] && !dec1.bits[1] && !dec1.bits[2] && dec1_sign) dec1_sign &= 0;
    if (!dec2.bits[0] && !dec2.bits[1] && !dec2.bits[2] && dec2_sign) dec2_sign &= 0;
    for (int i = SHIGH; i >= NLOW && result; i--) {
      if (!(dec1_sign & dec2_sign)) {
        if (dec1_sign) {
          result = 0;
        } else if (dec2_sign) {
          break;
        } else {
          if (dec1_s.bits[i] < dec2_s.bits[i]) {
            result = 0;
          } else if (dec1_s.bits[i] > dec2_s.bits[i]) {
              break;
          }
        }
      } else {
        if (dec1_s.bits[i] > dec2_s.bits[i]) {
          result = 0;
        } else if (dec1_s.bits[i] < dec2_s.bits[i]) {
          break;
        }
      }
    }
  } else {
    if ((dec1.value_type == sfleta_NEGATIVE_INFINITY)
          && ((dec2.value_type != sfleta_NEGATIVE_INFINITY) && (dec2.value_type != sfleta_NAN))) {
      result = 0;
    }
    if ((dec2.value_type == sfleta_INFINITY) && ((dec1.value_type != sfleta_INFINITY)
          && (dec1.value_type != sfleta_NAN))) {
      result = 0;
    }
  }
  return result;
}

int sfleta_is_less_or_equal(sfleta_decimal dec1, sfleta_decimal dec2) {
  int result = 1;
  if (sfleta_is_less(dec1, dec2) == 0 || sfleta_is_equal(dec1, dec2) == 0) {
    result = 0;
  }
  return result;
}

int sfleta_is_greater(sfleta_decimal dec1, sfleta_decimal dec2) {
  int result = 1;
  int dec1_sign = sfleta_getSign(dec1);
  int dec2_sign = sfleta_getSign(dec2);
  sfleta_decimal_super dec1_s = sfleta_convert_to_super(dec1);
  sfleta_decimal_super dec2_s = sfleta_convert_to_super(dec2);
  sfleta_equality_scale_super(&dec1_s, &dec2_s);
  if (dec1.value_type == sfleta_NORMAL_VALUE && dec2.value_type == sfleta_NORMAL_VALUE) {
    if (!dec1.bits[0] && !dec1.bits[1] && !dec1.bits[2] && dec1_sign) dec1_sign &= 0;
    if (!dec2.bits[0] && !dec2.bits[1] && !dec2.bits[2] && dec2_sign) dec2_sign &= 0;
    for (int i = SHIGH; i >= NLOW && result; i--) {
      if (!(dec1_sign & dec2_sign)) {
        if (dec2_sign) {
          result = 0;
        } else if (dec1_sign) {
          break;
        } else {
          if (dec1_s.bits[i] > dec2_s.bits[i]) {
            result = 0;
          } else if (dec1_s.bits[i] < dec2_s.bits[i]) {
            break;
          }
        }
      } else {
        if (dec1_s.bits[i] < dec2_s.bits[i]) {
          result = 0;
        } else if (dec1_s.bits[i] > dec2_s.bits[i]) {
          break;
        }
      }
    }
  } else {
    if ((dec2.value_type == sfleta_NEGATIVE_INFINITY)
          && ((dec1.value_type != sfleta_NEGATIVE_INFINITY) && (dec1.value_type != sfleta_NAN))) {
      result = 0;
    }
    if ((dec1.value_type == sfleta_INFINITY)
          && ((dec2.value_type != sfleta_INFINITY) && (dec2.value_type != sfleta_NAN))) {
      result = 0;
    }
  }
  return result;
}

int sfleta_is_greater_or_equal(sfleta_decimal dec1, sfleta_decimal dec2) {
    int result = 1;
    if (sfleta_is_greater(dec1, dec2) == 0 || sfleta_is_equal(dec1, dec2) == 0) {
      result = 0;
    }
    return result;
}

/************ Преобразователи ***********/
int sfleta_from_int_to_decimal(int src, sfleta_decimal *dst) {
  int result = 0;
  sfleta_decimal_set_default(dst);
  if (src < 0) {
    src *= -1;
    sfleta_setSign(dst, 1);
  }
  dst->bits[LOW] = src;
  result = 0;
  return result;
}

int sfleta_from_decimal_to_int(sfleta_decimal src, int *dst) {
  int result = 1;
  if (src.value_type == sfleta_NORMAL_VALUE) {
    src = sfleta_truncate(src);
        if (!src.bits[MID] && !src.bits[HIGH]) {
          if (sfleta_getSign(src) == 1) {
            if (src.bits[LOW] <= ((unsigned int)INT_MAX + 1)) {
              *dst = (int)src.bits[LOW] * (-1);
              result = 0;
            }
          } else {
            if (src.bits[LOW] <= ((unsigned int)INT_MAX)) {
              *dst = src.bits[LOW];
              result = 0;
            }
          }
        }
  }
  return result;
}

int sfleta_from_decimal_to_float(sfleta_decimal src, float *dst) {
  int result = 1;
  int srcScale = sfleta_getScale(src);
  int srcSign = sfleta_getSign(src);
  if (src.value_type == sfleta_NORMAL_VALUE) {
    double tmp = 0.0;
    for (int i = 0; i < 96; i++) {
      if (sfleta_getBit(src, i) == 1) {
        tmp += pow(2, i);
      }
    }
    if (srcScale != 0) {
      for (int i = srcScale; i > 0; i--) {
        tmp /= 10.0;
      }
    }
    if (srcSign == 0) {
      *dst = (float)tmp;
    } else {
      *dst = (float)tmp * (-1);
    }
    result = 0;
  }
  return result;
}

int sfleta_from_float_to_decimal(float src, sfleta_decimal *dst) {
  int convertRes = 0;
  sfleta_decimal_set_default(dst);
  int bitExp = sfleta_getFloatExp(src);
  int resSign = sfleta_getBitFloat(src, 31);
  if (isnan(src)) {
      dst->value_type = sfleta_NAN;
      convertRes = 1;
    } else if (bitExp > 95) {
      dst->value_type = resSign ? sfleta_NEGATIVE_INFINITY : sfleta_INFINITY;
      convertRes = 1;
    } else if (bitExp > -95) {
      if (resSign) src *= -1;
      int mask = 0x400000;
      unsigned int fbits = *((unsigned int *)&src);
      double result = 1;
      int scale = 0;
      for (; !(int)src; src *= 10, scale++) {}
      for (; src > 10; src /= 10, scale--) {}
      for (int i = 1; mask; mask >>= 1, i++) {
        if (fbits & mask) result += pow(2, -i);
      }
      result *= pow(2, bitExp) * pow(10, 8 + scale);
      if (scale > 0) {
        for (; result < 10000000; result *= 10) {}
      }
      long int tmp = 0L;
      tmp = round(result);
      int mod = 0;
      for (; tmp >= 10000000;) {
        mod = tmp % 10;
        tmp = round(tmp);
        tmp /= 10;
      }
      for (; scale + 7 > 29; mod = tmp % 10, tmp /= 10, scale--) {}
      if (mod > 4) tmp++;
      for (; tmp % 10 == 0; mod = tmp % 10, tmp /= 10, scale--) {}
      sfleta_from_int_to_decimal((int)tmp, dst);
      for (; scale + 7 <= 0; *dst = sfleta_multi_10(*dst), scale++) {}
      sfleta_setSign(dst, resSign);
      sfleta_setScale(dst, scale + 6);
  }
  return convertRes;
}

/******* Другие функции ********/
sfleta_decimal sfleta_floor(sfleta_decimal src) {
  sfleta_decimal dec = DECIMAL_NORMAL;
  if (src.value_type == sfleta_NORMAL_VALUE) {
    int srcSign = sfleta_getSign(src);
    dec = sfleta_truncate(src);
    int isNotEqual = sfleta_is_not_equal(src, dec);
    if (srcSign == 1 && isNotEqual == 0) {
      sfleta_decimal dec_1 = {{1, 0, 0, 0}, sfleta_NORMAL_VALUE};
      dec = sfleta_sub(dec, dec_1);
    }
  } else {
    dec.value_type = src.value_type;
  }
  return dec;
}

sfleta_decimal sfleta_round(sfleta_decimal src) {
  sfleta_decimal dec = DECIMAL_NORMAL;
  if (src.value_type == sfleta_NORMAL_VALUE) {
    dec = src;
    int srcScale = sfleta_getScale(src);
    if (srcScale > 0) {
      int srcSign = sfleta_getSign(src);
      sfleta_setSign(&dec, 0);
      if (srcScale > 1) {
        for (int i = srcScale; i > 1; i--) {
          dec = sfleta_div_10_decimal(dec);
        }
      } else if (srcScale == 1) {
        sfleta_setScale(&dec, 0);
      }
      sfleta_decimal decTmp = sfleta_truncate(src);
      sfleta_setSign(&decTmp, 0);
      decTmp = sfleta_multi_10(decTmp);
      sfleta_decimal dec_sub = sfleta_sub(dec, decTmp);
      int res_sub = 0;
      int flag = sfleta_from_decimal_to_int(dec_sub, &res_sub);
      if (flag == 0) {
        dec = sfleta_truncate(src);
        sfleta_setSign(&dec, 0);
        if (res_sub >= 5 && res_sub <= 9) {
          sfleta_decimal dec_1 = {{1, 0, 0, 0}, sfleta_NORMAL_VALUE};
          dec = sfleta_add(dec, dec_1);
        }
      }
      sfleta_setSign(&dec, srcSign);
    }
  } else {
    dec.value_type = src.value_type;
  }
  return dec;
}

sfleta_decimal sfleta_truncate(sfleta_decimal src) {
  sfleta_decimal dst = DECIMAL_NORMAL;
  if (src.value_type == sfleta_INFINITY) {
    dst.value_type = sfleta_INFINITY;
  } else if (src.value_type == sfleta_NEGATIVE_INFINITY) {
    dst.value_type = sfleta_NEGATIVE_INFINITY;
  } else if (src.value_type == sfleta_NAN) {
    dst.value_type = sfleta_NAN;
  } else if (src.value_type == sfleta_NORMAL_VALUE) {
    dst = src;
    int srcScale = sfleta_getScale(src);
    int srcSign = sfleta_getSign(src);
    if (srcScale > 0 && srcScale <= 28) {
      for (int i = srcScale; i > 0; i--) {
        dst = sfleta_div_10_decimal(dst);
      }
    }
    sfleta_setSign(&dst, srcSign);
  }
  return dst;
}

sfleta_decimal sfleta_negate(sfleta_decimal src) {
  sfleta_decimal dst = DECIMAL_NORMAL;
  if (src.value_type == sfleta_INFINITY) {
    dst.value_type = sfleta_NEGATIVE_INFINITY;
  } else if (src.value_type == sfleta_NEGATIVE_INFINITY) {
    dst.value_type = sfleta_INFINITY;
  } else if (src.value_type == sfleta_NAN) {
    dst.value_type = sfleta_NAN;
  } else if (src.value_type == sfleta_NORMAL_VALUE) {
    dst = src;
    int srcSign = sfleta_getSign(src);
    if (srcSign == 0)
      sfleta_setSign(&dst, 1);
    else if (srcSign == 1)
      sfleta_setSign(&dst, 0);
  }
  return dst;
}

/******* Вспомогательные функции ********/
void sfleta_decimal_set_default(sfleta_decimal *decimal) {
  decimal->bits[LOW] = 0;
  decimal->bits[MID] = 0;
  decimal->bits[HIGH] = 0;
  decimal->bits[SCALE] = 0;
  decimal->value_type = sfleta_NORMAL_VALUE;
}

int sfleta_getBit(sfleta_decimal src, int i) {
  unsigned int getMask = 1u << (i % 32);
  return !!(src.bits[i / 32] & getMask);
}

void sfleta_setBit(sfleta_decimal *dst, int i, int value) {
  unsigned int setMask = 1u << (i % 32);

  if (value == 1) {
    (*dst).bits[i / 32] |= setMask;
  } else {
    (*dst).bits[i / 32] &= ~setMask;
  }
}

int sfleta_getScale(sfleta_decimal src) {
  int exp = src.bits[SCALE] & EXP_MASK;
  exp >>= 16;
  return exp;
}

void sfleta_setScale(sfleta_decimal *dst, int value) {
  dst->bits[SCALE] &= NULL_SCALE;
  value <<= 16;
  dst->bits[SCALE] |= value;
}

void sfleta_setSign(sfleta_decimal *dst, int value) {
  unsigned int setSign = 1u << 31;
  if (value == 1) {
    dst->bits[SCALE] |= setSign;
  } else if (value == 0) {
    dst->bits[SCALE] &= ~setSign;
  }
}

int sfleta_getSign(sfleta_decimal src) {
  unsigned int getSign = 1u << 31;
  src.bits[SCALE] &= getSign;
  return !!(src.bits[SCALE] >>= 31);
}

/* Умножение decimal на 10 */
sfleta_decimal sfleta_multi_10(sfleta_decimal src) {
  sfleta_decimal dec = DECIMAL_NORMAL;
  if (src.value_type == sfleta_NORMAL_VALUE) {
    dec.bits[SCALE] = src.bits[SCALE];
    int inf_flag = 0;
    for (int i = 1; i <= 2 && !inf_flag; i++) {
      src = sfleta_move_left(src, i);
      if (src.value_type == sfleta_NEGATIVE_INFINITY ||
          src.value_type == sfleta_INFINITY) {
        inf_flag = 1;
      }
      if (!inf_flag) {
        dec = sfleta_add(dec, src);
      }
      if (inf_flag) {
        dec.value_type = src.value_type;
      }
    }
  } else {
    dec.value_type = src.value_type;
  }
  return dec;
}

// Сдвиг влево на количество shift битов */
sfleta_decimal sfleta_move_left(sfleta_decimal src, int shift) {
  int inf_flag = 0;
  sfleta_decimal dec = DECIMAL_NORMAL;
  dec.bits[SCALE] = src.bits[SCALE];

  for (int i = 95; i > 95 - shift; i--) {
    if (sfleta_getBit(src, i)) {
      inf_flag = 1;
    }
  }
  if (inf_flag) {
    dec = sfleta_decimal_set_inf(sfleta_getSign(src));
  }
  if (!inf_flag) {
    for (int pos = 95; pos >= shift; pos--) {
      int bit = sfleta_getBit(src, pos - shift);
      sfleta_setBit(&dec, pos, bit);
    }
  }
  return dec;
}

// Функция установки в decimal inf в зависимости от знака sing -inf или +inf
sfleta_decimal sfleta_decimal_set_inf(int sign) {
  sfleta_decimal dec = DECIMAL_NORMAL;
  if (sign == 0) {
    dec.value_type = sfleta_INFINITY;
  } else if (sign == 1) {
    dec.value_type = sfleta_NEGATIVE_INFINITY;
  }
  return dec;
}

// Функция деления decimal на 10
sfleta_decimal sfleta_div_10_decimal(sfleta_decimal src) {
  sfleta_decimal dst = DECIMAL_NORMAL;
  sfleta_decimal revChast = DECIMAL_NORMAL;
  int delimoeTmp = 0;
  int pos = 0;
  int startStep = 0;
  for (int i = 95; i >= 0; i--) {
    delimoeTmp <<= 1;
    delimoeTmp |= sfleta_getBit(src, i);
    if (delimoeTmp >= 10) {
      sfleta_setBit(&revChast, pos, 1);
      delimoeTmp -= 10;
      startStep = 1;
    }
    if (startStep == 1) {
      pos += 1;
    }
  }
  for (int i = pos - 1, j = 0; i >= 0; i--, j++) {
    int bit = sfleta_getBit(revChast, i);
    sfleta_setBit(&dst, j, bit);
  }
  return dst;
}

int sfleta_mod_div_10(sfleta_decimal src_s) {
  int delimoeTmp = 0;
  for (int i = 96; i >= 0; i--) {
    delimoeTmp <<= 1;
    delimoeTmp |= sfleta_getBit(src_s, i);
    if (delimoeTmp >= 10) {
      delimoeTmp -= 10;
    }
  }
  return delimoeTmp;
}

int sfleta_getFloatExp(float src) {
  unsigned int fbits = *((unsigned int *)&src);
  int exp = (fbits >> 23) & 0xFF;
  return exp - 127;
}

int sfleta_getBitFloat(float src, int i) {
    unsigned int fbits = *((unsigned int *)&src);
    unsigned int getMask = 1u << i;
    return !!(fbits & getMask);
}

void sfleta_equality_scale(sfleta_decimal *dec1, sfleta_decimal *dec2) {
  int dec1Scale = sfleta_getScale(*dec1);
  int dec2Scale = sfleta_getScale(*dec2);
  int diffScale = dec1Scale - dec2Scale;

  if (diffScale < 0) {
    diffScale *= -1;
    *dec1 = sfleta_increase_scale(diffScale, *dec1);
  } else if (diffScale > 0) {
    *dec2 = sfleta_increase_scale(diffScale, *dec2);
  }
}

sfleta_decimal sfleta_increase_scale(int diffScale, sfleta_decimal src) {
  sfleta_decimal dec = src;
  int newScale = sfleta_getScale(src);
  for (int i = diffScale; i > 0 && dec.value_type == sfleta_NORMAL_VALUE; i--) {
    dec = sfleta_multi_10(dec);
    newScale++;
  }
  if (dec.value_type == sfleta_NORMAL_VALUE) {
    sfleta_setScale(&dec, newScale);
  }
  return dec;
}

sfleta_decimal sfleta_move_right(sfleta_decimal src, int shift) {
  sfleta_decimal res;
  sfleta_decimal_set_default(&res);
  for (int i = 0; i < 95; sfleta_setBit(&res, i, sfleta_getBit(src, shift + i)), i++) {}
  return res;
}

int sfleta_decimal_equal_int(sfleta_decimal dec, unsigned int value) {
  int res = (value != dec.bits[0]) | dec.bits[1] | dec.bits[2];
  return res;
}

/*------- super decimal fuctions start -----------*/
sfleta_decimal_super sfleta_convert_to_super(sfleta_decimal src) {
  sfleta_decimal_super dst = DECIMAL_NORMAL_SUPER;
  if (src.value_type == sfleta_NORMAL_VALUE) {
    for (int i = 0; i < 3; i++) {
      dst.bits[i] = src.bits[i];
    }
    dst.bits[SSCALE] = src.bits[SCALE];
  } else {
    dst.value_type = src.value_type;
  }
  return dst;
}

sfleta_decimal sfleta_convert_to_decimal(sfleta_decimal_super src_s) {
  sfleta_decimal dec = DECIMAL_NORMAL;
  int sign_src_s = sfleta_getSign_super(src_s);
  if (src_s.value_type == sfleta_NORMAL_VALUE) {
    int scale = sfleta_getScale_super(src_s);
    int mod_s = 0;
    for (; scale > 28;) {
      mod_s = sfleta_mod_div_10_super(src_s);
      src_s = sfleta_div_10_super(src_s);
      scale--;
    }
    int emptyFlag = 1;
    if (src_s.bits[SHIGH] == 0 && src_s.bits[SMID] == 0 &&
        src_s.bits[SLOW] == 0)
      emptyFlag = 0;
    while (scale > 0 && emptyFlag) {
      mod_s = sfleta_mod_div_10_super(src_s);
      src_s = sfleta_div_10_super(src_s);
      scale--;
      if (src_s.bits[SHIGH] == 0 && src_s.bits[SMID] == 0 &&
          src_s.bits[SLOW] == 0)
        emptyFlag = 0;
    }
    if (!emptyFlag) {
      if (mod_s >= 5 && mod_s <= 9) {
        sfleta_decimal_super dec_s_1 = {{1, 0, 0, 0, 0, 0, 0}, sfleta_NORMAL_VALUE};
        sfleta_decimal_super tmp = src_s;
        tmp = sfleta_add_simple_super(tmp, dec_s_1);
        int checkBit96 = sfleta_getBit_super(tmp, 96);
        if (checkBit96 == 1 && scale == 0) {
          dec = sfleta_decimal_set_inf(sign_src_s);
        } else if (checkBit96 == 1 && scale > 0) {
          mod_s = sfleta_mod_div_10_super(src_s);
          src_s = sfleta_div_10_super(src_s);
          scale--;
          if (mod_s >= 5) {
            src_s = sfleta_add_simple_super(tmp, dec_s_1);
            for (int i = 2; i >= 0; i--) {
              dec.bits[i] = src_s.bits[i];
            }
            sfleta_setScale(&dec, scale);
            sfleta_setSign(&dec, sign_src_s);
          } else {
            for (int i = 2; i >= 0; i--) {
              dec.bits[i] = src_s.bits[i];
            }
            sfleta_setScale(&dec, scale);
            sfleta_setSign(&dec, sign_src_s);
          }
        } else {
          for (int i = 2; i >= 0; i--) {
            dec.bits[i] = tmp.bits[i];
          }
          sfleta_setScale(&dec, scale);
          sfleta_setSign(&dec, sign_src_s);
        }
      } else {
        for (int i = 2; i >= 0; i--) {
          dec.bits[i] = src_s.bits[i];
        }
        sfleta_setScale(&dec, scale);
        sfleta_setSign(&dec, sign_src_s);
      }
    } else {
      dec = sfleta_decimal_set_inf(sign_src_s);
    }
  } else {
    dec.value_type = src_s.value_type;
  }
  return dec;
}

void sfleta_equality_scale_super(sfleta_decimal_super *dec1_s,
                              sfleta_decimal_super *dec2_s) {
  int dec1Scale = sfleta_getScale_super(*dec1_s);
  int dec2Scale = sfleta_getScale_super(*dec2_s);
  int diffScale = dec1Scale - dec2Scale;

  if (diffScale < 0) {
    diffScale *= -1;
    *dec1_s = sfleta_increase_scale_super(diffScale, *dec1_s);
  } else if (diffScale > 0) {
    *dec2_s = sfleta_increase_scale_super(diffScale, *dec2_s);
  }
}

sfleta_decimal_super sfleta_increase_scale_super(int diffScale, sfleta_decimal_super src_s) {
  sfleta_decimal_super dec_s = src_s;
  int newScale = sfleta_getScale_super(src_s);
  for (int i = diffScale; i > 0 && dec_s.value_type == sfleta_NORMAL_VALUE; i--) {
    dec_s = sfleta_multi_10_super(dec_s);
    newScale++;
  }
  if (dec_s.value_type == sfleta_NORMAL_VALUE) {
    sfleta_setScale_super(&dec_s, newScale);
  }
  return dec_s;
}

sfleta_decimal_super sfleta_multi_10_super(sfleta_decimal_super src_s) {
  sfleta_decimal_super dec_s = DECIMAL_NORMAL_SUPER;
  if (src_s.value_type == sfleta_NORMAL_VALUE) {
    dec_s.bits[SSCALE] = src_s.bits[SSCALE];
    int inf_flag = 0;
    for (int i = 1; i <= 2 && !inf_flag; i++) {
      src_s = sfleta_move_left_super(src_s, i);
      if (src_s.value_type == sfleta_NEGATIVE_INFINITY ||
          src_s.value_type == sfleta_INFINITY) {
        inf_flag = 1;
      }
      if (!inf_flag) {
        dec_s = sfleta_add_simple_super(dec_s, src_s);
      }
      if (inf_flag) {
        dec_s.value_type = src_s.value_type;
      }
    }
  } else {
    dec_s.value_type = src_s.value_type;
  }

  return dec_s;
}

sfleta_decimal_super sfleta_move_right_super(sfleta_decimal_super src, int shift) {
  sfleta_decimal_super res = DECIMAL_NORMAL_SUPER;
  for (int i = 0; i < 191; sfleta_setBit_super(&res, i, sfleta_getBit_super(src, shift + i)), i++) {}
  return res;
}

int sfleta_move_left_for_div_super(sfleta_decimal_super dec1, sfleta_decimal_super *dec2) {
  int shift = 0;
  for (; !sfleta_getBit_super(dec1, 192 - shift); shift++) {
  }
  for (int j = 0; !sfleta_getBit_super(*dec2, 192 - j); j++, shift--) {
  }
  if (shift < 0) *dec2 = sfleta_move_left_super(*dec2, -shift);
  return -shift;
}

sfleta_decimal_super sfleta_move_left_super(sfleta_decimal_super src_s, int shift) {
  int inf_flag = 0;
  sfleta_decimal_super dec_s = DECIMAL_NORMAL_SUPER;
  dec_s.bits[SSCALE] = src_s.bits[SSCALE];

  for (int i = 191; i > 191 - shift; i--) {
    if (sfleta_getBit_super(src_s, i)) {
      inf_flag = 1;
    }
  }
  if (inf_flag) {
    dec_s = sfleta_super_set_inf(sfleta_getSign_super(src_s));
  }
  if (!inf_flag) {
    for (int pos = 191; pos >= shift; pos--) {
      int bit = sfleta_getBit_super(src_s, pos - shift);
      sfleta_setBit_super(&dec_s, pos, bit);
    }
  }
  return dec_s;
}

sfleta_decimal_super sfleta_super_set_inf(int sign) {
  sfleta_decimal_super dec_s = DECIMAL_NORMAL_SUPER;
  if (sign == 0) {
    dec_s.value_type = sfleta_INFINITY;
  } else if (sign == 1) {
    dec_s.value_type = sfleta_NEGATIVE_INFINITY;
  }
  return dec_s;
}

sfleta_decimal_super sfleta_add_simple_super(sfleta_decimal_super dec1_s, sfleta_decimal_super dec2_s) {
  sfleta_decimal_super dec_s = DECIMAL_NORMAL_SUPER;
  if (dec1_s.value_type == sfleta_NORMAL_VALUE &&
      dec2_s.value_type == sfleta_NORMAL_VALUE) {
    int tmp = 0;
    for (int i = 0; i < 192; i++) {
      int dec1Bit = sfleta_getBit_super(dec1_s, i);
      int dec2Bit = sfleta_getBit_super(dec2_s, i);
      if (dec1Bit && dec2Bit) {
        if (tmp == 1) {
          sfleta_setBit_super(&dec_s, i, 1);
          tmp = 1;
        }
        if (tmp == 0) {
          sfleta_setBit_super(&dec_s, i, 0);
          tmp = 1;
        }
      }
      if (dec1Bit ^ dec2Bit) {
        if (tmp == 0) {
          sfleta_setBit_super(&dec_s, i, 1);
          tmp = 0;
        } else if (tmp == 1) {
          sfleta_setBit_super(&dec_s, i, 0);
          tmp = 1;
        }
      }
      if (!dec1Bit && !dec2Bit) {
        if (tmp == 1) {
          sfleta_setBit_super(&dec_s, i, 1);
          tmp = 0;
        } else if (tmp == 0) {
          sfleta_setBit_super(&dec_s, i, 0);
        }
      }
    }
  }
  return dec_s;
}

sfleta_decimal_super sfleta_sub_simple_super(sfleta_decimal_super dec1_s, sfleta_decimal_super dec2_s) {
  sfleta_decimal_super dec_1_s = {{1, 0, 0, 0, 0, 0, 0}, sfleta_NORMAL_VALUE};
  sfleta_decimal_super tmp_s = DECIMAL_NORMAL_SUPER;
  int signFlag = sfleta_is_greater_or_equal_super(dec1_s, dec2_s);
  tmp_s.bits[NLOW] = ~dec2_s.bits[NLOW];
  tmp_s.bits[NMID] = ~dec2_s.bits[NMID];
  tmp_s.bits[NHIGH] = ~dec2_s.bits[NHIGH];
  tmp_s.bits[SLOW] = ~dec2_s.bits[SLOW];
  tmp_s.bits[SMID] = ~dec2_s.bits[SMID];
  tmp_s.bits[SHIGH] = ~dec2_s.bits[SHIGH];

  tmp_s = sfleta_add_simple_super(tmp_s, dec_1_s);
  sfleta_decimal_super dec_s = sfleta_add_simple_super(dec1_s, tmp_s);
  if (signFlag == 1) {
    dec_s.bits[NLOW] = ~dec_s.bits[NLOW];
    dec_s.bits[NMID] = ~dec_s.bits[NMID];
    dec_s.bits[NHIGH] = ~dec_s.bits[NHIGH];
    dec_s.bits[SLOW] = ~dec_s.bits[SLOW];
    dec_s.bits[SMID] = ~dec_s.bits[SMID];
    dec_s.bits[SHIGH] = ~dec_s.bits[SHIGH];
    dec_s = sfleta_add_simple_super(dec_s, dec_1_s);
    sfleta_setSign_super(&dec_s, 1);
  }
  return dec_s;
}

int sfleta_is_greater_or_equal_super(sfleta_decimal_super dec1_s, sfleta_decimal_super dec2_s) {
  int result = 0;
  int greater = sfleta_is_greater_super(dec1_s, dec2_s);
  int equal = sfleta_is_equal_super(dec1_s, dec2_s);
  if (greater == 1 && equal == 1) {
    result = 1;
  }
  return result;
}

int sfleta_is_greater_super(sfleta_decimal_super dec1_s, sfleta_decimal_super dec2_s) {
  int result = 1;
  int flag = 1;

  for (int i = SHIGH; i >= NLOW && flag; i--) {
    if (dec1_s.bits[i] < dec2_s.bits[i]) {
      flag = 0;
    } else if (dec1_s.bits[i] > dec2_s.bits[i]) {
      result = 0;
      flag = 0;
    }
  }
  return result;
}

int sfleta_is_equal_super(sfleta_decimal_super dec1_s, sfleta_decimal_super dec2_s) {
  int result = 0;
  for (int i = 0; i < SSCALE && !result; i++) {
    if (dec1_s.bits[i] != dec2_s.bits[i]) {
      result = 1;
    }
  }
  return result;
}

sfleta_decimal_super sfleta_div_10_super(sfleta_decimal_super src_s) {
  sfleta_decimal_super dst_s = DECIMAL_NORMAL_SUPER;
  sfleta_decimal_super revChast_s = DECIMAL_NORMAL_SUPER;
  int delimoeTmp = 0;
  int pos = 0;
  int startStep = 0;
  for (int i = 191; i >= 0; i--) {
    delimoeTmp <<= 1;
    delimoeTmp |= sfleta_getBit_super(src_s, i);
    if (delimoeTmp >= 10) {
      sfleta_setBit_super(&revChast_s, pos, 1);
      delimoeTmp -= 10;
      startStep = 1;
    }
    if (startStep == 1) {
      pos += 1;
    }
  }
  for (int i = pos - 1, j = 0; i >= 0; i--, j++) {
    int bit = sfleta_getBit_super(revChast_s, i);
    sfleta_setBit_super(&dst_s, j, bit);
  }
  return dst_s;
}

int sfleta_mod_div_10_super(sfleta_decimal_super src_s) {
  int delimoeTmp = 0;
  for (int i = 191; i >= 0; i--) {
    delimoeTmp <<= 1;
    delimoeTmp |= sfleta_getBit_super(src_s, i);
    if (delimoeTmp >= 10) {
      delimoeTmp -= 10;
    }
  }
  return delimoeTmp;
}

sfleta_decimal_super sfleta_mod_super(sfleta_decimal_super dec1, sfleta_decimal_super dec2) {
  int scale = sfleta_move_left_for_div_super(dec1, &dec2);
  for (; scale >= 0; scale--) {
    if (!sfleta_is_greater_or_equal_super(dec1, dec2)) {
      dec1 = sfleta_sub_simple_super(dec1, dec2);
    }
    dec2 = sfleta_move_right_super(dec2, 1);
    }
    return dec1;
}

int sfleta_decimal_is_equal_null_super(sfleta_decimal_super dec) {
  int res = dec.bits[0] | dec.bits[1] | dec.bits[2] | dec.bits[3]
              | dec.bits[4] | dec.bits[5];
  return res;
}

sfleta_decimal_super sfleta_div_simple_super(sfleta_decimal_super dec1, sfleta_decimal_super dec2) {
  sfleta_decimal_super res = DECIMAL_NORMAL_SUPER;
  for (int scale = sfleta_move_left_for_div_super(dec1, &dec2); scale >= 0; scale--) {
    sfleta_setBit_super(&res, 0, !sfleta_is_greater_or_equal_super(dec1, dec2));
    if (sfleta_getBit_super(res, 0)) {
      dec1 = sfleta_sub_simple_super(dec1, dec2);
    }
    dec2 = sfleta_move_right_super(dec2, 1);
    res = sfleta_move_left_super(res, 1);
  }
  res = sfleta_move_right_super(res, 1);
  return res;
}

int sfleta_getBit_super(sfleta_decimal_super src_s, int i) {
  unsigned int getMask = 1u << (i % 32);
  return !!(src_s.bits[i / 32] & getMask);
}

void sfleta_setBit_super(sfleta_decimal_super *dst_s, int i, int value) {
  unsigned int setMask = 1u << (i % 32);
  if (value == 1) {
    (*dst_s).bits[i / 32] |= setMask;
  } else {
    (*dst_s).bits[i / 32] &= ~setMask;
  }
}

int sfleta_getSign_super(sfleta_decimal_super src_s) {
  unsigned int getSign = 1u << 31;
  src_s.bits[SSCALE] &= getSign;
  return !!(src_s.bits[SSCALE] >>= 31);
}

void sfleta_setSign_super(sfleta_decimal_super *dst, int value) {
  unsigned int setSign = 1u << 31;
  if (value == 1) {
    dst->bits[SSCALE] |= setSign;
  } else if (value == 0) {
    dst->bits[SSCALE] &= ~setSign;
  }
}

void sfleta_setScale_super(sfleta_decimal_super *dst_s, int value) {
  dst_s->bits[SSCALE] &= NULL_SCALE;
  value <<= 16;
  dst_s->bits[SSCALE] |= value;
}

int sfleta_getScale_super(sfleta_decimal_super src) {
  int exp = src.bits[SSCALE] & EXP_MASK;
  exp >>= 16;
  return exp;
}
/*------- super decimal fuctions end -----------*/
