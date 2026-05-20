/* { dg-do compile } */
/* { dg-options "-march=rv64gcv_zvfofp8min -mabi=lp64d -O3" } */

#include "riscv_vector.h"

vfloat8e4m3mf8_t
test_vreinterpret_v_u8mf8_f8e4m3mf8 (vuint8mf8_t src)
{
  return __riscv_vreinterpret_f8e4m3mf8 (src);
}

vfloat8e4m3mf4_t
test_vreinterpret_v_u8mf4_f8e4m3mf4 (vuint8mf4_t src)
{
  return __riscv_vreinterpret_f8e4m3mf4 (src);
}

vfloat8e4m3mf2_t
test_vreinterpret_v_u8mf2_f8e4m3mf2 (vuint8mf2_t src)
{
  return __riscv_vreinterpret_f8e4m3mf2 (src);
}

vfloat8e4m3m1_t
test_vreinterpret_v_u8m1_f8e4m3m1 (vuint8m1_t src)
{
  return __riscv_vreinterpret_f8e4m3m1 (src);
}

vfloat8e4m3m2_t
test_vreinterpret_v_u8m2_f8e4m3m2 (vuint8m2_t src)
{
  return __riscv_vreinterpret_f8e4m3m2 (src);
}

vfloat8e4m3m4_t
test_vreinterpret_v_u8m4_f8e4m3m4 (vuint8m4_t src)
{
  return __riscv_vreinterpret_f8e4m3m4 (src);
}

vfloat8e4m3m8_t
test_vreinterpret_v_u8m8_f8e4m3m8 (vuint8m8_t src)
{
  return __riscv_vreinterpret_f8e4m3m8 (src);
}

vuint8mf8_t
test_vreinterpret_v_f8e4m3mf8_u8mf8 (vfloat8e4m3mf8_t src)
{
  return __riscv_vreinterpret_u8mf8 (src);
}

vuint8mf4_t
test_vreinterpret_v_f8e4m3mf4_u8mf4 (vfloat8e4m3mf4_t src)
{
  return __riscv_vreinterpret_u8mf4 (src);
}

vuint8mf2_t
test_vreinterpret_v_f8e4m3mf2_u8mf2 (vfloat8e4m3mf2_t src)
{
  return __riscv_vreinterpret_u8mf2 (src);
}

vuint8m1_t
test_vreinterpret_v_f8e4m3m1_u8m1 (vfloat8e4m3m1_t src)
{
  return __riscv_vreinterpret_u8m1 (src);
}

vuint8m2_t
test_vreinterpret_v_f8e4m3m2_u8m2 (vfloat8e4m3m2_t src)
{
  return __riscv_vreinterpret_u8m2 (src);
}

vuint8m4_t
test_vreinterpret_v_f8e4m3m4_u8m4 (vfloat8e4m3m4_t src)
{
  return __riscv_vreinterpret_u8m4 (src);
}

vuint8m8_t
test_vreinterpret_v_f8e4m3m8_u8m8 (vfloat8e4m3m8_t src)
{
  return __riscv_vreinterpret_u8m8 (src);
}

vfloat8e5m2mf8_t
test_vreinterpret_v_u8mf8_f8e5m2mf8 (vuint8mf8_t src)
{
  return __riscv_vreinterpret_f8e5m2mf8 (src);
}

vfloat8e5m2mf4_t
test_vreinterpret_v_u8mf4_f8e5m2mf4 (vuint8mf4_t src)
{
  return __riscv_vreinterpret_f8e5m2mf4 (src);
}

vfloat8e5m2mf2_t
test_vreinterpret_v_u8mf2_f8e5m2mf2 (vuint8mf2_t src)
{
  return __riscv_vreinterpret_f8e5m2mf2 (src);
}

vfloat8e5m2m1_t
test_vreinterpret_v_u8m1_f8e5m2m1 (vuint8m1_t src)
{
  return __riscv_vreinterpret_f8e5m2m1 (src);
}

vfloat8e5m2m2_t
test_vreinterpret_v_u8m2_f8e5m2m2 (vuint8m2_t src)
{
  return __riscv_vreinterpret_f8e5m2m2 (src);
}

vfloat8e5m2m4_t
test_vreinterpret_v_u8m4_f8e5m2m4 (vuint8m4_t src)
{
  return __riscv_vreinterpret_f8e5m2m4 (src);
}

vfloat8e5m2m8_t
test_vreinterpret_v_u8m8_f8e5m2m8 (vuint8m8_t src)
{
  return __riscv_vreinterpret_f8e5m2m8 (src);
}

vuint8mf8_t
test_vreinterpret_v_f8e5m2mf8_u8mf8 (vfloat8e5m2mf8_t src)
{
  return __riscv_vreinterpret_u8mf8 (src);
}

vuint8mf4_t
test_vreinterpret_v_f8e5m2mf4_u8mf4 (vfloat8e5m2mf4_t src)
{
  return __riscv_vreinterpret_u8mf4 (src);
}

vuint8mf2_t
test_vreinterpret_v_f8e5m2mf2_u8mf2 (vfloat8e5m2mf2_t src)
{
  return __riscv_vreinterpret_u8mf2 (src);
}

vuint8m1_t
test_vreinterpret_v_f8e5m2m1_u8m1 (vfloat8e5m2m1_t src)
{
  return __riscv_vreinterpret_u8m1 (src);
}

vuint8m2_t
test_vreinterpret_v_f8e5m2m2_u8m2 (vfloat8e5m2m2_t src)
{
  return __riscv_vreinterpret_u8m2 (src);
}

vuint8m4_t
test_vreinterpret_v_f8e5m2m4_u8m4 (vfloat8e5m2m4_t src)
{
  return __riscv_vreinterpret_u8m4 (src);
}

vuint8m8_t
test_vreinterpret_v_f8e5m2m8_u8m8 (vfloat8e5m2m8_t src)
{
  return __riscv_vreinterpret_u8m8 (src);
}

/* { dg-final { scan-assembler-times {\mret\M} 28 } } */
