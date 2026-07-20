;; Machine description for RISC-V vector float8 extensions.
;; Copyright (C) 2026 Free Software Foundation, Inc.

;; This file is part of GCC.

;; GCC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.

;; GCC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

;; The two OCP FP8 formats have dedicated element modes (FP8E4M3 and
;; FP8E5M2) and dedicated vector modes, so the conversions below are
;; ordinary float_extend/float_truncate operations, one pattern per
;; FP8 format.  The same instruction encoding serves both formats; the
;; executed format is selected by the vtype "altfmt" bit, which each
;; pattern advertises through a constant "altfmt" attribute
;; (ALTFMT_NONE for E4M3, ALTFMT_ALT for E5M2) that the vsetvl pass
;; turns into e8/e8alt vsetvls.  Only the saturating narrowing
;; conversions keep an unspec (UNSPEC_F8_SAT): there is no RTL code
;; for a saturating float truncation.

(define_mode_iterator VWEXTF_ZVFOFP8MIN [
  (RVVM8BF  "TARGET_ZVFOFP8MIN && TARGET_VECTOR_ELEN_BF_16")
  (RVVM4BF  "TARGET_ZVFOFP8MIN && TARGET_VECTOR_ELEN_BF_16")
  (RVVM2BF  "TARGET_ZVFOFP8MIN && TARGET_VECTOR_ELEN_BF_16")
  (RVVM1BF  "TARGET_ZVFOFP8MIN && TARGET_VECTOR_ELEN_BF_16")
  (RVVMF2BF "TARGET_ZVFOFP8MIN && TARGET_VECTOR_ELEN_BF_16")
  (RVVMF4BF "TARGET_ZVFOFP8MIN && TARGET_VECTOR_ELEN_BF_16 && TARGET_VECTOR_ELEN_64")
])

(define_mode_iterator VQEXTF_ZVFOFP8MIN [
  (RVVM8SF  "TARGET_ZVFOFP8MIN && TARGET_VECTOR_ELEN_FP_32")
  (RVVM4SF  "TARGET_ZVFOFP8MIN && TARGET_VECTOR_ELEN_FP_32")
  (RVVM2SF  "TARGET_ZVFOFP8MIN && TARGET_VECTOR_ELEN_FP_32")
  (RVVM1SF  "TARGET_ZVFOFP8MIN && TARGET_VECTOR_ELEN_FP_32")
  (RVVMF2SF "TARGET_ZVFOFP8MIN && TARGET_VECTOR_ELEN_FP_32 && TARGET_VECTOR_ELEN_64")
])

;; BF16 vector mode -> FP8 vector mode with the same element count
;; (half the LMUL).
(define_mode_attr V_BF16TOF8E4M3 [
  (RVVM8BF "RVVM4FP8E4M3") (RVVM4BF "RVVM2FP8E4M3") (RVVM2BF "RVVM1FP8E4M3")
  (RVVM1BF "RVVMF2FP8E4M3") (RVVMF2BF "RVVMF4FP8E4M3")
  (RVVMF4BF "RVVMF8FP8E4M3")
])

(define_mode_attr V_BF16TOF8E5M2 [
  (RVVM8BF "RVVM4FP8E5M2") (RVVM4BF "RVVM2FP8E5M2") (RVVM2BF "RVVM1FP8E5M2")
  (RVVM1BF "RVVMF2FP8E5M2") (RVVMF2BF "RVVMF4FP8E5M2")
  (RVVMF4BF "RVVMF8FP8E5M2")
])

;; FP32 vector mode -> FP8 vector mode with the same element count
;; (a quarter of the LMUL).
(define_mode_attr V_FP32TOF8E4M3 [
  (RVVM8SF "RVVM2FP8E4M3") (RVVM4SF "RVVM1FP8E4M3") (RVVM2SF "RVVMF2FP8E4M3")
  (RVVM1SF "RVVMF4FP8E4M3") (RVVMF2SF "RVVMF8FP8E4M3")
])

(define_mode_attr V_FP32TOF8E5M2 [
  (RVVM8SF "RVVM2FP8E5M2") (RVVM4SF "RVVM1FP8E5M2") (RVVM2SF "RVVMF2FP8E5M2")
  (RVVM1SF "RVVMF4FP8E5M2") (RVVMF2SF "RVVMF8FP8E5M2")
])

;; FP8 to BF16 widening conversions.

(define_insn "@pred_extend_f8e4m3_to_<mode>"
  [(set (match_operand:VWEXTF_ZVFOFP8MIN 0 "register_operand"          "=&vr,  &vr")
    (if_then_else:VWEXTF_ZVFOFP8MIN
      (unspec:<VM>
        [(match_operand:<VM> 1 "vector_mask_operand"                   "vmWc1,vmWc1")
         (match_operand 4 "vector_length_operand"                      "   rK,   rK")
         (match_operand 5 "const_int_operand"                          "    i,    i")
         (match_operand 6 "const_int_operand"                          "    i,    i")
         (match_operand 7 "const_int_operand"                          "    i,    i")
         (reg:SI VL_REGNUM)
         (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
      (float_extend:VWEXTF_ZVFOFP8MIN
         (match_operand:<V_BF16TOF8E4M3> 3 "register_operand"          "   vr,   vr"))
      (match_operand:VWEXTF_ZVFOFP8MIN 2 "vector_merge_operand"        "   vu,    0")))]
  "TARGET_ZVFOFP8MIN"
  "vfwcvtbf16.f.f.v\t%0,%3%p1"
  [(set_attr "type" "vfwcvtbf16")
   (set_attr "mode" "<V_BF16TOF8E4M3>")
   (set (attr "altfmt") (symbol_ref "riscv_vector::ALTFMT_NONE"))])

(define_insn "@pred_extend_f8e5m2_to_<mode>"
  [(set (match_operand:VWEXTF_ZVFOFP8MIN 0 "register_operand"          "=&vr,  &vr")
    (if_then_else:VWEXTF_ZVFOFP8MIN
      (unspec:<VM>
        [(match_operand:<VM> 1 "vector_mask_operand"                   "vmWc1,vmWc1")
         (match_operand 4 "vector_length_operand"                      "   rK,   rK")
         (match_operand 5 "const_int_operand"                          "    i,    i")
         (match_operand 6 "const_int_operand"                          "    i,    i")
         (match_operand 7 "const_int_operand"                          "    i,    i")
         (reg:SI VL_REGNUM)
         (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
      (float_extend:VWEXTF_ZVFOFP8MIN
         (match_operand:<V_BF16TOF8E5M2> 3 "register_operand"          "   vr,   vr"))
      (match_operand:VWEXTF_ZVFOFP8MIN 2 "vector_merge_operand"        "   vu,    0")))]
  "TARGET_ZVFOFP8MIN"
  "vfwcvtbf16.f.f.v\t%0,%3%p1"
  [(set_attr "type" "vfwcvtbf16")
   (set_attr "mode" "<V_BF16TOF8E5M2>")
   (set (attr "altfmt") (symbol_ref "riscv_vector::ALTFMT_ALT"))])

;; BF16 to FP8 narrowing conversions.

(define_insn "@pred_trunc_<mode>_to_f8e4m3"
  [(set (match_operand:<V_BF16TOF8E4M3> 0 "register_operand"       "=vd, vd, vr, vr,  &vr,  &vr")
     (if_then_else:<V_BF16TOF8E4M3>
       (unspec:<VM>
         [(match_operand:<VM> 1 "vector_mask_operand"              " vm, vm,Wc1,Wc1,vmWc1,vmWc1")
          (match_operand 4 "vector_length_operand"                 " rK, rK, rK, rK,   rK,   rK")
          (match_operand 5 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 6 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 7 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 8 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (reg:SI VL_REGNUM)
          (reg:SI VTYPE_REGNUM)
          (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
       (float_truncate:<V_BF16TOF8E4M3>
          (match_operand:VWEXTF_ZVFOFP8MIN 3 "register_operand"    "  0,  0,  0,  0,   vr,   vr"))
       (match_operand:<V_BF16TOF8E4M3> 2 "vector_merge_operand"    " vu,  0, vu,  0,   vu,    0")))]
  "TARGET_ZVFOFP8MIN"
  "vfncvtbf16.f.f.w\t%0,%3%p1"
  [(set_attr "type" "vfncvtbf16")
   (set_attr "mode" "<V_BF16TOF8E4M3>")
   (set (attr "altfmt") (symbol_ref "riscv_vector::ALTFMT_NONE"))
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[8])"))])

(define_insn "@pred_trunc_<mode>_to_f8e5m2"
  [(set (match_operand:<V_BF16TOF8E5M2> 0 "register_operand"       "=vd, vd, vr, vr,  &vr,  &vr")
     (if_then_else:<V_BF16TOF8E5M2>
       (unspec:<VM>
         [(match_operand:<VM> 1 "vector_mask_operand"              " vm, vm,Wc1,Wc1,vmWc1,vmWc1")
          (match_operand 4 "vector_length_operand"                 " rK, rK, rK, rK,   rK,   rK")
          (match_operand 5 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 6 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 7 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 8 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (reg:SI VL_REGNUM)
          (reg:SI VTYPE_REGNUM)
          (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
       (float_truncate:<V_BF16TOF8E5M2>
          (match_operand:VWEXTF_ZVFOFP8MIN 3 "register_operand"    "  0,  0,  0,  0,   vr,   vr"))
       (match_operand:<V_BF16TOF8E5M2> 2 "vector_merge_operand"    " vu,  0, vu,  0,   vu,    0")))]
  "TARGET_ZVFOFP8MIN"
  "vfncvtbf16.f.f.w\t%0,%3%p1"
  [(set_attr "type" "vfncvtbf16")
   (set_attr "mode" "<V_BF16TOF8E5M2>")
   (set (attr "altfmt") (symbol_ref "riscv_vector::ALTFMT_ALT"))
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[8])"))])

;; Saturating variants.  There is no RTL code for a saturating float
;; truncation, so these keep UNSPEC_F8_SAT.

(define_insn "@pred_trunc_<mode>_to_f8e4m3_sat"
  [(set (match_operand:<V_BF16TOF8E4M3> 0 "register_operand"       "=vd, vd, vr, vr,  &vr,  &vr")
     (if_then_else:<V_BF16TOF8E4M3>
       (unspec:<VM>
         [(match_operand:<VM> 1 "vector_mask_operand"              " vm, vm,Wc1,Wc1,vmWc1,vmWc1")
          (match_operand 4 "vector_length_operand"                 " rK, rK, rK, rK,   rK,   rK")
          (match_operand 5 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 6 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 7 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 8 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (reg:SI VL_REGNUM)
          (reg:SI VTYPE_REGNUM)
          (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
       (unspec:<V_BF16TOF8E4M3>
         [(match_operand:VWEXTF_ZVFOFP8MIN 3 "register_operand"    "  0,  0,  0,  0,   vr,   vr")] UNSPEC_F8_SAT)
       (match_operand:<V_BF16TOF8E4M3> 2 "vector_merge_operand"    " vu,  0, vu,  0,   vu,    0")))]
  "TARGET_ZVFOFP8MIN"
  "vfncvtbf16.sat.f.f.w\t%0,%3%p1"
  [(set_attr "type" "vfncvtbf16")
   (set_attr "mode" "<V_BF16TOF8E4M3>")
   (set (attr "altfmt") (symbol_ref "riscv_vector::ALTFMT_NONE"))
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[8])"))])

(define_insn "@pred_trunc_<mode>_to_f8e5m2_sat"
  [(set (match_operand:<V_BF16TOF8E5M2> 0 "register_operand"       "=vd, vd, vr, vr,  &vr,  &vr")
     (if_then_else:<V_BF16TOF8E5M2>
       (unspec:<VM>
         [(match_operand:<VM> 1 "vector_mask_operand"              " vm, vm,Wc1,Wc1,vmWc1,vmWc1")
          (match_operand 4 "vector_length_operand"                 " rK, rK, rK, rK,   rK,   rK")
          (match_operand 5 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 6 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 7 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 8 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (reg:SI VL_REGNUM)
          (reg:SI VTYPE_REGNUM)
          (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
       (unspec:<V_BF16TOF8E5M2>
         [(match_operand:VWEXTF_ZVFOFP8MIN 3 "register_operand"    "  0,  0,  0,  0,   vr,   vr")] UNSPEC_F8_SAT)
       (match_operand:<V_BF16TOF8E5M2> 2 "vector_merge_operand"    " vu,  0, vu,  0,   vu,    0")))]
  "TARGET_ZVFOFP8MIN"
  "vfncvtbf16.sat.f.f.w\t%0,%3%p1"
  [(set_attr "type" "vfncvtbf16")
   (set_attr "mode" "<V_BF16TOF8E5M2>")
   (set (attr "altfmt") (symbol_ref "riscv_vector::ALTFMT_ALT"))
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[8])"))])

;; FP32 to FP8 narrowing conversions.

(define_insn "@pred_quad_trunc_<mode>_to_f8e4m3"
  [(set (match_operand:<V_FP32TOF8E4M3> 0 "register_operand"       "=vd, vd, vr, vr,  &vr,  &vr")
     (if_then_else:<V_FP32TOF8E4M3>
       (unspec:<VM>
         [(match_operand:<VM> 1 "vector_mask_operand"              " vm, vm,Wc1,Wc1,vmWc1,vmWc1")
          (match_operand 4 "vector_length_operand"                 " rK, rK, rK, rK,   rK,   rK")
          (match_operand 5 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 6 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 7 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 8 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (reg:SI VL_REGNUM)
          (reg:SI VTYPE_REGNUM)
          (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
       (float_truncate:<V_FP32TOF8E4M3>
          (match_operand:VQEXTF_ZVFOFP8MIN 3 "register_operand"    "  0,  0,  0,  0,   vr,   vr"))
       (match_operand:<V_FP32TOF8E4M3> 2 "vector_merge_operand"    " vu,  0, vu,  0,   vu,    0")))]
  "TARGET_ZVFOFP8MIN"
  "vfncvt.f.f.q\t%0,%3%p1"
  [(set_attr "type" "vfncvtftof")
   (set_attr "mode" "<V_FP32TOF8E4M3>")
   (set (attr "altfmt") (symbol_ref "riscv_vector::ALTFMT_NONE"))
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[8])"))])

(define_insn "@pred_quad_trunc_<mode>_to_f8e5m2"
  [(set (match_operand:<V_FP32TOF8E5M2> 0 "register_operand"       "=vd, vd, vr, vr,  &vr,  &vr")
     (if_then_else:<V_FP32TOF8E5M2>
       (unspec:<VM>
         [(match_operand:<VM> 1 "vector_mask_operand"              " vm, vm,Wc1,Wc1,vmWc1,vmWc1")
          (match_operand 4 "vector_length_operand"                 " rK, rK, rK, rK,   rK,   rK")
          (match_operand 5 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 6 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 7 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 8 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (reg:SI VL_REGNUM)
          (reg:SI VTYPE_REGNUM)
          (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
       (float_truncate:<V_FP32TOF8E5M2>
          (match_operand:VQEXTF_ZVFOFP8MIN 3 "register_operand"    "  0,  0,  0,  0,   vr,   vr"))
       (match_operand:<V_FP32TOF8E5M2> 2 "vector_merge_operand"    " vu,  0, vu,  0,   vu,    0")))]
  "TARGET_ZVFOFP8MIN"
  "vfncvt.f.f.q\t%0,%3%p1"
  [(set_attr "type" "vfncvtftof")
   (set_attr "mode" "<V_FP32TOF8E5M2>")
   (set (attr "altfmt") (symbol_ref "riscv_vector::ALTFMT_ALT"))
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[8])"))])

(define_insn "@pred_quad_trunc_<mode>_to_f8e4m3_sat"
  [(set (match_operand:<V_FP32TOF8E4M3> 0 "register_operand"       "=vd, vd, vr, vr,  &vr,  &vr")
     (if_then_else:<V_FP32TOF8E4M3>
       (unspec:<VM>
         [(match_operand:<VM> 1 "vector_mask_operand"              " vm, vm,Wc1,Wc1,vmWc1,vmWc1")
          (match_operand 4 "vector_length_operand"                 " rK, rK, rK, rK,   rK,   rK")
          (match_operand 5 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 6 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 7 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 8 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (reg:SI VL_REGNUM)
          (reg:SI VTYPE_REGNUM)
          (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
       (unspec:<V_FP32TOF8E4M3>
         [(match_operand:VQEXTF_ZVFOFP8MIN 3 "register_operand"    "  0,  0,  0,  0,   vr,   vr")] UNSPEC_F8_SAT)
       (match_operand:<V_FP32TOF8E4M3> 2 "vector_merge_operand"    " vu,  0, vu,  0,   vu,    0")))]
  "TARGET_ZVFOFP8MIN"
  "vfncvt.sat.f.f.q\t%0,%3%p1"
  [(set_attr "type" "vfncvtftof")
   (set_attr "mode" "<V_FP32TOF8E4M3>")
   (set (attr "altfmt") (symbol_ref "riscv_vector::ALTFMT_NONE"))
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[8])"))])

(define_insn "@pred_quad_trunc_<mode>_to_f8e5m2_sat"
  [(set (match_operand:<V_FP32TOF8E5M2> 0 "register_operand"       "=vd, vd, vr, vr,  &vr,  &vr")
     (if_then_else:<V_FP32TOF8E5M2>
       (unspec:<VM>
         [(match_operand:<VM> 1 "vector_mask_operand"              " vm, vm,Wc1,Wc1,vmWc1,vmWc1")
          (match_operand 4 "vector_length_operand"                 " rK, rK, rK, rK,   rK,   rK")
          (match_operand 5 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 6 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 7 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 8 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (reg:SI VL_REGNUM)
          (reg:SI VTYPE_REGNUM)
          (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
       (unspec:<V_FP32TOF8E5M2>
         [(match_operand:VQEXTF_ZVFOFP8MIN 3 "register_operand"    "  0,  0,  0,  0,   vr,   vr")] UNSPEC_F8_SAT)
       (match_operand:<V_FP32TOF8E5M2> 2 "vector_merge_operand"    " vu,  0, vu,  0,   vu,    0")))]
  "TARGET_ZVFOFP8MIN"
  "vfncvt.sat.f.f.q\t%0,%3%p1"
  [(set_attr "type" "vfncvtftof")
   (set_attr "mode" "<V_FP32TOF8E5M2>")
   (set (attr "altfmt") (symbol_ref "riscv_vector::ALTFMT_ALT"))
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[8])"))])
