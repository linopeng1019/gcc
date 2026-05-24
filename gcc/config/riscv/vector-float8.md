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
