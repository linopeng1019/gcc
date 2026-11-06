/* The spec defines __riscv_abs_u32 (INT32_MIN) as 0x80000000, so a clamp
   applied to the result must not be folded away as dead.  */

#include <stdint.h>
#include <riscv_packed_simd.h>

uint32_t __attribute__ ((noipa))
sat_abs32 (int32_t x)
{
  uint32_t a = __riscv_abs_u32 (x);
  return a < 0x7fffffffu ? a : 0x7fffffffu;
}

#if __riscv_xlen == 64
uint64_t __attribute__ ((noipa))
sat_abs64 (int64_t x)
{
  uint64_t a = __riscv_abs_u64 (x);
  return a < 0x7fffffffffffffffull ? a : 0x7fffffffffffffffull;
}
#endif

int
main (void)
{
  volatile int32_t min32 = INT32_MIN, neg32 = -5;

  /* Compare as unsigned long so RV64 also checks the zero extension.  */
  if ((unsigned long) __riscv_abs_u32 (min32) != 0x80000000ul)
    __builtin_abort ();
  if (sat_abs32 (min32) != 0x7fffffffu || sat_abs32 (neg32) != 5)
    __builtin_abort ();

#if __riscv_xlen == 64
  volatile int64_t min64 = INT64_MIN, neg64 = -5;

  if (__riscv_abs_u64 (min64) != 0x8000000000000000ull)
    __builtin_abort ();
  if (sat_abs64 (min64) != 0x7fffffffffffffffull || sat_abs64 (neg64) != 5)
    __builtin_abort ();
#endif
  return 0;
}
