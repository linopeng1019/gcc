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

;; Zvfofp8min extension.

(define_insn "@pred_extend_float8_to_<mode>"
  [(set
     (match_operand:VWEXTF_ZVFOFP8MIN 0 "register_operand" "=&vr,&vr")
     (if_then_else:VWEXTF_ZVFOFP8MIN
       (unspec:<VM>
	 [(match_operand:<VM> 1 "vector_mask_operand" "vmWc1,vmWc1")
	  (match_operand 4 "vector_length_operand" "rK,rK")
	  (match_operand 5 "const_int_operand" "i,i")
	  (match_operand 6 "const_int_operand" "i,i")
	  (match_operand 7 "const_int_operand" "i,i")
	  (match_operand 8 "const_int_operand" "i,i")
	  (reg:SI VL_REGNUM)
	  (reg:SI VTYPE_REGNUM)]
	 UNSPEC_VPREDICATE)
       (unspec:VWEXTF_ZVFOFP8MIN
	 [(match_operand:<VINDEX_DOUBLE_TRUNC> 3 "register_operand"  "vr,vr")] UNSPEC_F8)
       (match_operand:VWEXTF_ZVFOFP8MIN 2 "vector_merge_operand" "vu,0")))]
  "TARGET_ZVFOFP8MIN"
  "vfwcvtbf16.f.f.v\t%0,%3%p1"
  [(set_attr "type" "vfwcvtbf16")
   (set_attr "mode" "<VINDEX_DOUBLE_TRUNC>")
   (set (attr "altfmt")
	(symbol_ref "INTVAL (operands[8])"))])

(define_insn "@pred_trunc_<mode>_to_float8"
  [(set (match_operand:<VINDEX_DOUBLE_TRUNC> 0 "register_operand"   "=vd, vd, vr, vr,  &vr,  &vr")
     (if_then_else:<VINDEX_DOUBLE_TRUNC>
       (unspec:<VM>
         [(match_operand:<VM> 1 "vector_mask_operand"              " vm, vm,Wc1,Wc1,vmWc1,vmWc1")
          (match_operand 4 "vector_length_operand"                 " rK, rK, rK, rK,   rK,   rK")
          (match_operand 5 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 6 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 7 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 8 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 9 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (reg:SI VL_REGNUM)
          (reg:SI VTYPE_REGNUM)
          (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
       (unspec:<VINDEX_DOUBLE_TRUNC>
         [(match_operand:VWEXTF_ZVFOFP8MIN 3 "register_operand"    "  0,  0,  0,  0,   vr,   vr")] UNSPEC_F8)
       (match_operand:<VINDEX_DOUBLE_TRUNC> 2 "vector_merge_operand" " vu,  0, vu,  0,   vu,    0")))]
  "TARGET_ZVFOFP8MIN"
  "vfncvtbf16.f.f.w\t%0,%3%p1"
  [(set_attr "type" "vfncvtbf16")
   (set_attr "mode" "<VINDEX_DOUBLE_TRUNC>")
   (set (attr "altfmt")
	(symbol_ref "INTVAL (operands[8])"))
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[9])"))])

(define_insn "@pred_trunc_<mode>_to_float8_sat"
  [(set (match_operand:<VINDEX_DOUBLE_TRUNC> 0 "register_operand"   "=vd, vd, vr, vr,  &vr,  &vr")
     (if_then_else:<VINDEX_DOUBLE_TRUNC>
       (unspec:<VM>
         [(match_operand:<VM> 1 "vector_mask_operand"              " vm, vm,Wc1,Wc1,vmWc1,vmWc1")
          (match_operand 4 "vector_length_operand"                 " rK, rK, rK, rK,   rK,   rK")
          (match_operand 5 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 6 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 7 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 8 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 9 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (reg:SI VL_REGNUM)
          (reg:SI VTYPE_REGNUM)
          (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
       (unspec:<VINDEX_DOUBLE_TRUNC>
         [(match_operand:VWEXTF_ZVFOFP8MIN 3 "register_operand"    "  0,  0,  0,  0,   vr,   vr")] UNSPEC_F8_SAT)
       (match_operand:<VINDEX_DOUBLE_TRUNC> 2 "vector_merge_operand" " vu,  0, vu,  0,   vu,    0")))]
  "TARGET_ZVFOFP8MIN"
  "vfncvtbf16.sat.f.f.w\t%0,%3%p1"
  [(set_attr "type" "vfncvtbf16")
   (set_attr "mode" "<VINDEX_DOUBLE_TRUNC>")
   (set (attr "altfmt")
	(symbol_ref "INTVAL (operands[8])"))
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[9])"))])

;; FP32 to FP8 narrowing conversions.

(define_insn "@pred_quad_trunc_<mode>_to_float8"
  [(set (match_operand:<VINDEX_QUAD_TRUNC> 0 "register_operand"   "=vd, vd, vr, vr,  &vr,  &vr")
     (if_then_else:<VINDEX_QUAD_TRUNC>
       (unspec:<VM>
         [(match_operand:<VM> 1 "vector_mask_operand"              " vm, vm,Wc1,Wc1,vmWc1,vmWc1")
          (match_operand 4 "vector_length_operand"                 " rK, rK, rK, rK,   rK,   rK")
          (match_operand 5 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 6 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 7 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 8 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 9 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (reg:SI VL_REGNUM)
          (reg:SI VTYPE_REGNUM)
          (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
       (unspec:<VINDEX_QUAD_TRUNC>
         [(match_operand:VQEXTF_ZVFOFP8MIN 3 "register_operand"    "  0,  0,  0,  0,   vr,   vr")] UNSPEC_F8)
       (match_operand:<VINDEX_QUAD_TRUNC> 2 "vector_merge_operand" " vu,  0, vu,  0,   vu,    0")))]
  "TARGET_ZVFOFP8MIN"
  "vfncvt.f.f.q\t%0,%3%p1"
  [(set_attr "type" "vfncvtftof")
   (set_attr "mode" "<VINDEX_QUAD_TRUNC>")
   (set (attr "altfmt")
	(symbol_ref "INTVAL (operands[8])"))
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[9])"))])

(define_insn "@pred_quad_trunc_<mode>_to_float8_sat"
  [(set (match_operand:<VINDEX_QUAD_TRUNC> 0 "register_operand"   "=vd, vd, vr, vr,  &vr,  &vr")
     (if_then_else:<VINDEX_QUAD_TRUNC>
       (unspec:<VM>
         [(match_operand:<VM> 1 "vector_mask_operand"              " vm, vm,Wc1,Wc1,vmWc1,vmWc1")
          (match_operand 4 "vector_length_operand"                 " rK, rK, rK, rK,   rK,   rK")
          (match_operand 5 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 6 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 7 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 8 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (match_operand 9 "const_int_operand"                     "  i,  i,  i,  i,    i,    i")
          (reg:SI VL_REGNUM)
          (reg:SI VTYPE_REGNUM)
          (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
       (unspec:<VINDEX_QUAD_TRUNC>
         [(match_operand:VQEXTF_ZVFOFP8MIN 3 "register_operand"    "  0,  0,  0,  0,   vr,   vr")] UNSPEC_F8_SAT)
       (match_operand:<VINDEX_QUAD_TRUNC> 2 "vector_merge_operand" " vu,  0, vu,  0,   vu,    0")))]
  "TARGET_ZVFOFP8MIN"
  "vfncvt.sat.f.f.q\t%0,%3%p1"
  [(set_attr "type" "vfncvtftof")
   (set_attr "mode" "<VINDEX_QUAD_TRUNC>")
   (set (attr "altfmt")
	(symbol_ref "INTVAL (operands[8])"))
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[9])"))])
