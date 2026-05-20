/* { dg-do compile } */
/* { dg-options "-O3 -march=rv64gcv_zvfbfmin_zvfofp8min -mabi=lp64d" } */
/* { dg-additional-options "-fno-schedule-insns -fno-schedule-insns2" } */

#include "riscv_vector.h"

/* a -> need alt.  */
/* n -> do not need alt.  */
/* d -> do not care alt.  */

vbfloat16mf4_t
test_a_n_interleave (vbfloat16mf4_t src_bf16, size_t vl)
{
  vfloat8e5m2mf8_t a = __riscv_vfncvt_f_f_w_bf16mf4_f8e5m2mf8 (src_bf16, vl);
  vuint8mf8_t bits = __riscv_vreinterpret_v_f8e5m2mf8_u8mf8 (a);
  vfloat8e4m3mf8_t n = __riscv_vreinterpret_v_u8mf8_f8e4m3mf8 (bits);
  return __riscv_vfwcvt_f_f_v_f8e4m3mf8_bf16mf4 (n, vl);
}

vfloat8e5m2mf8_t
test_a_n_a_interleave (vbfloat16mf4_t src_bf16, size_t vl)
{
  vfloat8e5m2mf8_t a0 = __riscv_vfncvt_f_f_w_bf16mf4_f8e5m2mf8 (src_bf16, vl);
  vuint8mf8_t bits = __riscv_vreinterpret_v_f8e5m2mf8_u8mf8 (a0);
  vfloat8e4m3mf8_t n0 = __riscv_vreinterpret_v_u8mf8_f8e4m3mf8 (bits);
  vbfloat16mf4_t n = __riscv_vfwcvt_f_f_v_f8e4m3mf8_bf16mf4 (n0, vl);
  return __riscv_vfncvt_f_f_w_bf16mf4_f8e5m2mf8 (n, vl);
}

vuint8mf8_t
test_a_n_d_interleave (vfloat8e5m2mf8_t src_f8, size_t vl)
{
  vbfloat16mf4_t a = __riscv_vfwcvt_f_f_v_f8e5m2mf8_bf16mf4 (src_f8, vl);
  vfloat8e4m3mf8_t n = __riscv_vfncvt_f_f_w_bf16mf4_f8e4m3mf8 (a, vl);
  vuint8mf8_t bits = __riscv_vreinterpret_v_f8e4m3mf8_u8mf8 (n);
  return __riscv_vadd_vv_u8mf8 (bits, bits, vl);
}

vuint8mf8_t
test_a_n_a_d_interleave (vbfloat16mf4_t src_bf16, size_t vl)
{
  vfloat8e5m2mf8_t a0 = __riscv_vfncvt_f_f_w_bf16mf4_f8e5m2mf8 (src_bf16, vl);
  vuint8mf8_t bits0 = __riscv_vreinterpret_v_f8e5m2mf8_u8mf8 (a0);
  vfloat8e4m3mf8_t n0 = __riscv_vreinterpret_v_u8mf8_f8e4m3mf8 (bits0);
  vbfloat16mf4_t n = __riscv_vfwcvt_f_f_v_f8e4m3mf8_bf16mf4 (n0, vl);
  vfloat8e5m2mf8_t a1 = __riscv_vfncvt_f_f_w_bf16mf4_f8e5m2mf8 (n, vl);
  vuint8mf8_t bits1 = __riscv_vreinterpret_v_f8e5m2mf8_u8mf8 (a1);
  return __riscv_vadd_vv_u8mf8 (bits1, bits1, vl);
}

vbfloat16mf4_t
test_n_a_interleave (vbfloat16mf4_t src_bf16, size_t vl)
{
  vfloat8e4m3mf8_t n = __riscv_vfncvt_f_f_w_bf16mf4_f8e4m3mf8 (src_bf16, vl);
  vuint8mf8_t bits = __riscv_vreinterpret_v_f8e4m3mf8_u8mf8 (n);
  vfloat8e5m2mf8_t a = __riscv_vreinterpret_v_u8mf8_f8e5m2mf8 (bits);
  return __riscv_vfwcvt_f_f_v_f8e5m2mf8_bf16mf4 (a, vl);
}

vfloat8e4m3mf8_t
test_n_a_n_interleave (vbfloat16mf4_t src_bf16, size_t vl)
{
  vfloat8e4m3mf8_t n0 = __riscv_vfncvt_f_f_w_bf16mf4_f8e4m3mf8 (src_bf16, vl);
  vuint8mf8_t bits = __riscv_vreinterpret_v_f8e4m3mf8_u8mf8 (n0);
  vfloat8e5m2mf8_t a0 = __riscv_vreinterpret_v_u8mf8_f8e5m2mf8 (bits);
  vbfloat16mf4_t a = __riscv_vfwcvt_f_f_v_f8e5m2mf8_bf16mf4 (a0, vl);
  return __riscv_vfncvt_f_f_w_bf16mf4_f8e4m3mf8 (a, vl);
}

vuint8mf8_t
test_n_a_d_interleave (vfloat8e4m3mf8_t src_f8, size_t vl)
{
  vbfloat16mf4_t n = __riscv_vfwcvt_f_f_v_f8e4m3mf8_bf16mf4 (src_f8, vl);
  vfloat8e5m2mf8_t a = __riscv_vfncvt_f_f_w_bf16mf4_f8e5m2mf8 (n, vl);
  vuint8mf8_t bits = __riscv_vreinterpret_v_f8e5m2mf8_u8mf8 (a);
  return __riscv_vadd_vv_u8mf8 (bits, bits, vl);
}

vuint8mf8_t
test_n_a_n_d_interleave (vbfloat16mf4_t src_bf16, size_t vl)
{
  vfloat8e4m3mf8_t n0 = __riscv_vfncvt_f_f_w_bf16mf4_f8e4m3mf8 (src_bf16, vl);
  vuint8mf8_t bits0 = __riscv_vreinterpret_v_f8e4m3mf8_u8mf8 (n0);
  vfloat8e5m2mf8_t a0 = __riscv_vreinterpret_v_u8mf8_f8e5m2mf8 (bits0);
  vbfloat16mf4_t a = __riscv_vfwcvt_f_f_v_f8e5m2mf8_bf16mf4 (a0, vl);
  vfloat8e4m3mf8_t n1 = __riscv_vfncvt_f_f_w_bf16mf4_f8e4m3mf8 (a, vl);
  vuint8mf8_t bits1 = __riscv_vreinterpret_v_f8e4m3mf8_u8mf8 (n1);
  return __riscv_vadd_vv_u8mf8 (bits1, bits1, vl);
}

/* { dg-final { scan-assembler-times {vsetvli\s+zero,\s*(zero|[a-x0-9]+),\s*e8alt,\s*mf8,\s*t[au],\s*m[au]} 10 } } */
/* { dg-final { scan-assembler-times {vsetvli\s+zero,\s*(zero|[a-x0-9]+),\s*e8,\s*mf8,\s*t[au],\s*m[au]} 10 } } */
