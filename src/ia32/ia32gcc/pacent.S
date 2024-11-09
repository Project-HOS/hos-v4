/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*   プロセッサ抽象化コンポーネント (IA32用)  割込み関連処理                */
/*                                            (割込みエントリ)              */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#define ASM 1
#include "ia32gcc/linkage.h"     /*  gcc 固有リンケージ定義  */
#include "ia32gcc/hosexp.h"
#include "pic.h"     /*  gcc 固有リンケージ定義  */
	
.bss
ALIGN
WVAR(_kernel_ia32__intrcnt)
WVAR(_kernel_ia32__ktsksp)	
.text
.globl kernel_int_sp			; 

ENTRY(_kernel_ia32__common_intr)
	common_prologue(kernel_sta_int,kernel_exe_int)
	call SYMBOL_NAME(_kernel_ia32__send_eoi)
	common_epilogue(kernel_end_int)	

ENTRY(_kernel_ia32__common_exc)
	common_prologue(kernel_sta_exc,kernel_exe_exc)
	common_epilogue(kernel_end_exc)	

				
ENTRY(_kernel_ia32__exc_divfault)
	exception(0)

ENTRY(_kernel_ia32__exc_debug)
	exception(1)

ENTRY(_kernel_ia32__exc_nmi)
	exception(2)

ENTRY(_kernel_ia32__exc_int3)
	exception(3)

ENTRY(_kernel_ia32__exc_overflow)
	exception(4)

ENTRY(_kernel_ia32__exc_bound)
	exception(5)

ENTRY(_kernel_ia32__exc_opcode)
	exception(6)

ENTRY(_kernel_ia32__exc_device_not_available)
	exception(7)

ENTRY(_kernel_ia32__exc_double_fault)
	exception(8)

ENTRY(_kernel_ia32__exc_coprocessor_segment_overrun)
	exception(9)

ENTRY(_kernel_ia32__exc_invalid_TSS)
	exception(10)

ENTRY(_kernel_ia32__exc_segment_not_present)
	exception(11)

ENTRY(_kernel_ia32__exc_stack_segment)
	exception(12)

ENTRY(_kernel_ia32__exc_general_protection)
	exception(13)

ENTRY(_kernel_ia32__exc_page_fault)
	exception(14)

ENTRY(_kernel_ia32__exc_intel_reserved)
	exception(15)

ENTRY(_kernel_ia32__exc_coprocessor_error)
	exception(16)

ENTRY(_kernel_ia32__exc_alignment_check)
	exception(17)

ENTRY(_kernel_ia32__exc_machine_check)
	exception(18)
		
ENTRY(_kernel_ia32__exc_simd_coprocessor)
	exception(19)
		
ENTRY(_kernel_ia32__intr0)
	intr(0x0)

ENTRY(_kernel_ia32__intr1)
	intr(0x1)

ENTRY(_kernel_ia32__intr2)
	intr(0x2)

ENTRY(_kernel_ia32__intr3)
	intr(0x3)

ENTRY(_kernel_ia32__intr4)
	intr(0x4)

ENTRY(_kernel_ia32__intr5)
	intr(0x5)

ENTRY(_kernel_ia32__intr6)
	intr(0x6)

ENTRY(_kernel_ia32__intr7)
	intr(0x7)

ENTRY(_kernel_ia32__intr8)
	intr(0x8)

ENTRY(_kernel_ia32__intr9)
	intr(0x9)

ENTRY(_kernel_ia32__intr10)
	intr(0xa)

ENTRY(_kernel_ia32__intr11)
	intr(0xb)

ENTRY(_kernel_ia32__intr12)
	intr(0xc)

ENTRY(_kernel_ia32__intr13)
	intr(0xd)

ENTRY(_kernel_ia32__intr14)
	intr(0xe)	

ENTRY(_kernel_ia32__intr15)
	intr(0xf)

/*  User Trap No 48  */
ENTRY(_kernel_ia32__user_trap_30)
exception(0x30)
/*  User Trap No 49  */
ENTRY(_kernel_ia32__user_trap_31)
exception(0x31)
/*  User Trap No 50  */
ENTRY(_kernel_ia32__user_trap_32)
exception(0x32)
/*  User Trap No 51  */
ENTRY(_kernel_ia32__user_trap_33)
exception(0x33)
/*  User Trap No 52  */
ENTRY(_kernel_ia32__user_trap_34)
exception(0x34)
/*  User Trap No 53  */
ENTRY(_kernel_ia32__user_trap_35)
exception(0x35)
/*  User Trap No 54  */
ENTRY(_kernel_ia32__user_trap_36)
exception(0x36)
/*  User Trap No 55  */
ENTRY(_kernel_ia32__user_trap_37)
exception(0x37)
/*  User Trap No 56  */
ENTRY(_kernel_ia32__user_trap_38)
exception(0x38)
/*  User Trap No 57  */
ENTRY(_kernel_ia32__user_trap_39)
exception(0x39)
/*  User Trap No 58  */
ENTRY(_kernel_ia32__user_trap_3a)
exception(0x3a)
/*  User Trap No 59  */
ENTRY(_kernel_ia32__user_trap_3b)
exception(0x3b)
/*  User Trap No 60  */
ENTRY(_kernel_ia32__user_trap_3c)
exception(0x3c)
/*  User Trap No 61  */
ENTRY(_kernel_ia32__user_trap_3d)
exception(0x3d)
/*  User Trap No 62  */
ENTRY(_kernel_ia32__user_trap_3e)
exception(0x3e)
/*  User Trap No 63  */
ENTRY(_kernel_ia32__user_trap_3f)
exception(0x3f)
/*  User Trap No 64  */
ENTRY(_kernel_ia32__user_trap_40)
exception(0x40)
/*  User Trap No 65  */
ENTRY(_kernel_ia32__user_trap_41)
exception(0x41)
/*  User Trap No 66  */
ENTRY(_kernel_ia32__user_trap_42)
exception(0x42)
/*  User Trap No 67  */
ENTRY(_kernel_ia32__user_trap_43)
exception(0x43)
/*  User Trap No 68  */
ENTRY(_kernel_ia32__user_trap_44)
exception(0x44)
/*  User Trap No 69  */
ENTRY(_kernel_ia32__user_trap_45)
exception(0x45)
/*  User Trap No 70  */
ENTRY(_kernel_ia32__user_trap_46)
exception(0x46)
/*  User Trap No 71  */
ENTRY(_kernel_ia32__user_trap_47)
exception(0x47)
/*  User Trap No 72  */
ENTRY(_kernel_ia32__user_trap_48)
exception(0x48)
/*  User Trap No 73  */
ENTRY(_kernel_ia32__user_trap_49)
exception(0x49)
/*  User Trap No 74  */
ENTRY(_kernel_ia32__user_trap_4a)
exception(0x4a)
/*  User Trap No 75  */
ENTRY(_kernel_ia32__user_trap_4b)
exception(0x4b)
/*  User Trap No 76  */
ENTRY(_kernel_ia32__user_trap_4c)
exception(0x4c)
/*  User Trap No 77  */
ENTRY(_kernel_ia32__user_trap_4d)
exception(0x4d)
/*  User Trap No 78  */
ENTRY(_kernel_ia32__user_trap_4e)
exception(0x4e)
/*  User Trap No 79  */
ENTRY(_kernel_ia32__user_trap_4f)
exception(0x4f)
/*  User Trap No 80  */
ENTRY(_kernel_ia32__user_trap_50)
exception(0x50)
/*  User Trap No 81  */
ENTRY(_kernel_ia32__user_trap_51)
exception(0x51)
/*  User Trap No 82  */
ENTRY(_kernel_ia32__user_trap_52)
exception(0x52)
/*  User Trap No 83  */
ENTRY(_kernel_ia32__user_trap_53)
exception(0x53)
/*  User Trap No 84  */
ENTRY(_kernel_ia32__user_trap_54)
exception(0x54)
/*  User Trap No 85  */
ENTRY(_kernel_ia32__user_trap_55)
exception(0x55)
/*  User Trap No 86  */
ENTRY(_kernel_ia32__user_trap_56)
exception(0x56)
/*  User Trap No 87  */
ENTRY(_kernel_ia32__user_trap_57)
exception(0x57)
/*  User Trap No 88  */
ENTRY(_kernel_ia32__user_trap_58)
exception(0x58)
/*  User Trap No 89  */
ENTRY(_kernel_ia32__user_trap_59)
exception(0x59)
/*  User Trap No 90  */
ENTRY(_kernel_ia32__user_trap_5a)
exception(0x5a)
/*  User Trap No 91  */
ENTRY(_kernel_ia32__user_trap_5b)
exception(0x5b)
/*  User Trap No 92  */
ENTRY(_kernel_ia32__user_trap_5c)
exception(0x5c)
/*  User Trap No 93  */
ENTRY(_kernel_ia32__user_trap_5d)
exception(0x5d)
/*  User Trap No 94  */
ENTRY(_kernel_ia32__user_trap_5e)
exception(0x5e)
/*  User Trap No 95  */
ENTRY(_kernel_ia32__user_trap_5f)
exception(0x5f)
/*  User Trap No 96  */
ENTRY(_kernel_ia32__user_trap_60)
exception(0x60)
/*  User Trap No 97  */
ENTRY(_kernel_ia32__user_trap_61)
exception(0x61)
/*  User Trap No 98  */
ENTRY(_kernel_ia32__user_trap_62)
exception(0x62)
/*  User Trap No 99  */
ENTRY(_kernel_ia32__user_trap_63)
exception(0x63)
/*  User Trap No 100  */
ENTRY(_kernel_ia32__user_trap_64)
exception(0x64)
/*  User Trap No 101  */
ENTRY(_kernel_ia32__user_trap_65)
exception(0x65)
/*  User Trap No 102  */
ENTRY(_kernel_ia32__user_trap_66)
exception(0x66)
/*  User Trap No 103  */
ENTRY(_kernel_ia32__user_trap_67)
exception(0x67)
/*  User Trap No 104  */
ENTRY(_kernel_ia32__user_trap_68)
exception(0x68)
/*  User Trap No 105  */
ENTRY(_kernel_ia32__user_trap_69)
exception(0x69)
/*  User Trap No 106  */
ENTRY(_kernel_ia32__user_trap_6a)
exception(0x6a)
/*  User Trap No 107  */
ENTRY(_kernel_ia32__user_trap_6b)
exception(0x6b)
/*  User Trap No 108  */
ENTRY(_kernel_ia32__user_trap_6c)
exception(0x6c)
/*  User Trap No 109  */
ENTRY(_kernel_ia32__user_trap_6d)
exception(0x6d)
/*  User Trap No 110  */
ENTRY(_kernel_ia32__user_trap_6e)
exception(0x6e)
/*  User Trap No 111  */
ENTRY(_kernel_ia32__user_trap_6f)
exception(0x6f)
/*  User Trap No 112  */
ENTRY(_kernel_ia32__user_trap_70)
exception(0x70)
/*  User Trap No 113  */
ENTRY(_kernel_ia32__user_trap_71)
exception(0x71)
/*  User Trap No 114  */
ENTRY(_kernel_ia32__user_trap_72)
exception(0x72)
/*  User Trap No 115  */
ENTRY(_kernel_ia32__user_trap_73)
exception(0x73)
/*  User Trap No 116  */
ENTRY(_kernel_ia32__user_trap_74)
exception(0x74)
/*  User Trap No 117  */
ENTRY(_kernel_ia32__user_trap_75)
exception(0x75)
/*  User Trap No 118  */
ENTRY(_kernel_ia32__user_trap_76)
exception(0x76)
/*  User Trap No 119  */
ENTRY(_kernel_ia32__user_trap_77)
exception(0x77)
/*  User Trap No 120  */
ENTRY(_kernel_ia32__user_trap_78)
exception(0x78)
/*  User Trap No 121  */
ENTRY(_kernel_ia32__user_trap_79)
exception(0x79)
/*  User Trap No 122  */
ENTRY(_kernel_ia32__user_trap_7a)
exception(0x7a)
/*  User Trap No 123  */
ENTRY(_kernel_ia32__user_trap_7b)
exception(0x7b)
/*  User Trap No 124  */
ENTRY(_kernel_ia32__user_trap_7c)
exception(0x7c)
/*  User Trap No 125  */
ENTRY(_kernel_ia32__user_trap_7d)
exception(0x7d)
/*  User Trap No 126  */
ENTRY(_kernel_ia32__user_trap_7e)
exception(0x7e)
/*  User Trap No 127  */
ENTRY(_kernel_ia32__user_trap_7f)
exception(0x7f)
/*  User Trap No 128  */
ENTRY(_kernel_ia32__user_trap_80)
exception(0x80)
/*  User Trap No 129  */
ENTRY(_kernel_ia32__user_trap_81)
exception(0x81)
/*  User Trap No 130  */
ENTRY(_kernel_ia32__user_trap_82)
exception(0x82)
/*  User Trap No 131  */
ENTRY(_kernel_ia32__user_trap_83)
exception(0x83)
/*  User Trap No 132  */
ENTRY(_kernel_ia32__user_trap_84)
exception(0x84)
/*  User Trap No 133  */
ENTRY(_kernel_ia32__user_trap_85)
exception(0x85)
/*  User Trap No 134  */
ENTRY(_kernel_ia32__user_trap_86)
exception(0x86)
/*  User Trap No 135  */
ENTRY(_kernel_ia32__user_trap_87)
exception(0x87)
/*  User Trap No 136  */
ENTRY(_kernel_ia32__user_trap_88)
exception(0x88)
/*  User Trap No 137  */
ENTRY(_kernel_ia32__user_trap_89)
exception(0x89)
/*  User Trap No 138  */
ENTRY(_kernel_ia32__user_trap_8a)
exception(0x8a)
/*  User Trap No 139  */
ENTRY(_kernel_ia32__user_trap_8b)
exception(0x8b)
/*  User Trap No 140  */
ENTRY(_kernel_ia32__user_trap_8c)
exception(0x8c)
/*  User Trap No 141  */
ENTRY(_kernel_ia32__user_trap_8d)
exception(0x8d)
/*  User Trap No 142  */
ENTRY(_kernel_ia32__user_trap_8e)
exception(0x8e)
/*  User Trap No 143  */
ENTRY(_kernel_ia32__user_trap_8f)
exception(0x8f)
/*  User Trap No 144  */
ENTRY(_kernel_ia32__user_trap_90)
exception(0x90)
/*  User Trap No 145  */
ENTRY(_kernel_ia32__user_trap_91)
exception(0x91)
/*  User Trap No 146  */
ENTRY(_kernel_ia32__user_trap_92)
exception(0x92)
/*  User Trap No 147  */
ENTRY(_kernel_ia32__user_trap_93)
exception(0x93)
/*  User Trap No 148  */
ENTRY(_kernel_ia32__user_trap_94)
exception(0x94)
/*  User Trap No 149  */
ENTRY(_kernel_ia32__user_trap_95)
exception(0x95)
/*  User Trap No 150  */
ENTRY(_kernel_ia32__user_trap_96)
exception(0x96)
/*  User Trap No 151  */
ENTRY(_kernel_ia32__user_trap_97)
exception(0x97)
/*  User Trap No 152  */
ENTRY(_kernel_ia32__user_trap_98)
exception(0x98)
/*  User Trap No 153  */
ENTRY(_kernel_ia32__user_trap_99)
exception(0x99)
/*  User Trap No 154  */
ENTRY(_kernel_ia32__user_trap_9a)
exception(0x9a)
/*  User Trap No 155  */
ENTRY(_kernel_ia32__user_trap_9b)
exception(0x9b)
/*  User Trap No 156  */
ENTRY(_kernel_ia32__user_trap_9c)
exception(0x9c)
/*  User Trap No 157  */
ENTRY(_kernel_ia32__user_trap_9d)
exception(0x9d)
/*  User Trap No 158  */
ENTRY(_kernel_ia32__user_trap_9e)
exception(0x9e)
/*  User Trap No 159  */
ENTRY(_kernel_ia32__user_trap_9f)
exception(0x9f)
/*  User Trap No 160  */
ENTRY(_kernel_ia32__user_trap_a0)
exception(0xa0)
/*  User Trap No 161  */
ENTRY(_kernel_ia32__user_trap_a1)
exception(0xa1)
/*  User Trap No 162  */
ENTRY(_kernel_ia32__user_trap_a2)
exception(0xa2)
/*  User Trap No 163  */
ENTRY(_kernel_ia32__user_trap_a3)
exception(0xa3)
/*  User Trap No 164  */
ENTRY(_kernel_ia32__user_trap_a4)
exception(0xa4)
/*  User Trap No 165  */
ENTRY(_kernel_ia32__user_trap_a5)
exception(0xa5)
/*  User Trap No 166  */
ENTRY(_kernel_ia32__user_trap_a6)
exception(0xa6)
/*  User Trap No 167  */
ENTRY(_kernel_ia32__user_trap_a7)
exception(0xa7)
/*  User Trap No 168  */
ENTRY(_kernel_ia32__user_trap_a8)
exception(0xa8)
/*  User Trap No 169  */
ENTRY(_kernel_ia32__user_trap_a9)
exception(0xa9)
/*  User Trap No 170  */
ENTRY(_kernel_ia32__user_trap_aa)
exception(0xaa)
/*  User Trap No 171  */
ENTRY(_kernel_ia32__user_trap_ab)
exception(0xab)
/*  User Trap No 172  */
ENTRY(_kernel_ia32__user_trap_ac)
exception(0xac)
/*  User Trap No 173  */
ENTRY(_kernel_ia32__user_trap_ad)
exception(0xad)
/*  User Trap No 174  */
ENTRY(_kernel_ia32__user_trap_ae)
exception(0xae)
/*  User Trap No 175  */
ENTRY(_kernel_ia32__user_trap_af)
exception(0xaf)
/*  User Trap No 176  */
ENTRY(_kernel_ia32__user_trap_b0)
exception(0xb0)
/*  User Trap No 177  */
ENTRY(_kernel_ia32__user_trap_b1)
exception(0xb1)
/*  User Trap No 178  */
ENTRY(_kernel_ia32__user_trap_b2)
exception(0xb2)
/*  User Trap No 179  */
ENTRY(_kernel_ia32__user_trap_b3)
exception(0xb3)
/*  User Trap No 180  */
ENTRY(_kernel_ia32__user_trap_b4)
exception(0xb4)
/*  User Trap No 181  */
ENTRY(_kernel_ia32__user_trap_b5)
exception(0xb5)
/*  User Trap No 182  */
ENTRY(_kernel_ia32__user_trap_b6)
exception(0xb6)
/*  User Trap No 183  */
ENTRY(_kernel_ia32__user_trap_b7)
exception(0xb7)
/*  User Trap No 184  */
ENTRY(_kernel_ia32__user_trap_b8)
exception(0xb8)
/*  User Trap No 185  */
ENTRY(_kernel_ia32__user_trap_b9)
exception(0xb9)
/*  User Trap No 186  */
ENTRY(_kernel_ia32__user_trap_ba)
exception(0xba)
/*  User Trap No 187  */
ENTRY(_kernel_ia32__user_trap_bb)
exception(0xbb)
/*  User Trap No 188  */
ENTRY(_kernel_ia32__user_trap_bc)
exception(0xbc)
/*  User Trap No 189  */
ENTRY(_kernel_ia32__user_trap_bd)
exception(0xbd)
/*  User Trap No 190  */
ENTRY(_kernel_ia32__user_trap_be)
exception(0xbe)
/*  User Trap No 191  */
ENTRY(_kernel_ia32__user_trap_bf)
exception(0xbf)
/*  User Trap No 192  */
ENTRY(_kernel_ia32__user_trap_c0)
exception(0xc0)
/*  User Trap No 193  */
ENTRY(_kernel_ia32__user_trap_c1)
exception(0xc1)
/*  User Trap No 194  */
ENTRY(_kernel_ia32__user_trap_c2)
exception(0xc2)
/*  User Trap No 195  */
ENTRY(_kernel_ia32__user_trap_c3)
exception(0xc3)
/*  User Trap No 196  */
ENTRY(_kernel_ia32__user_trap_c4)
exception(0xc4)
/*  User Trap No 197  */
ENTRY(_kernel_ia32__user_trap_c5)
exception(0xc5)
/*  User Trap No 198  */
ENTRY(_kernel_ia32__user_trap_c6)
exception(0xc6)
/*  User Trap No 199  */
ENTRY(_kernel_ia32__user_trap_c7)
exception(0xc7)
/*  User Trap No 200  */
ENTRY(_kernel_ia32__user_trap_c8)
exception(0xc8)
/*  User Trap No 201  */
ENTRY(_kernel_ia32__user_trap_c9)
exception(0xc9)
/*  User Trap No 202  */
ENTRY(_kernel_ia32__user_trap_ca)
exception(0xca)
/*  User Trap No 203  */
ENTRY(_kernel_ia32__user_trap_cb)
exception(0xcb)
/*  User Trap No 204  */
ENTRY(_kernel_ia32__user_trap_cc)
exception(0xcc)
/*  User Trap No 205  */
ENTRY(_kernel_ia32__user_trap_cd)
exception(0xcd)
/*  User Trap No 206  */
ENTRY(_kernel_ia32__user_trap_ce)
exception(0xce)
/*  User Trap No 207  */
ENTRY(_kernel_ia32__user_trap_cf)
exception(0xcf)
/*  User Trap No 208  */
ENTRY(_kernel_ia32__user_trap_d0)
exception(0xd0)
/*  User Trap No 209  */
ENTRY(_kernel_ia32__user_trap_d1)
exception(0xd1)
/*  User Trap No 210  */
ENTRY(_kernel_ia32__user_trap_d2)
exception(0xd2)
/*  User Trap No 211  */
ENTRY(_kernel_ia32__user_trap_d3)
exception(0xd3)
/*  User Trap No 212  */
ENTRY(_kernel_ia32__user_trap_d4)
exception(0xd4)
/*  User Trap No 213  */
ENTRY(_kernel_ia32__user_trap_d5)
exception(0xd5)
/*  User Trap No 214  */
ENTRY(_kernel_ia32__user_trap_d6)
exception(0xd6)
/*  User Trap No 215  */
ENTRY(_kernel_ia32__user_trap_d7)
exception(0xd7)
/*  User Trap No 216  */
ENTRY(_kernel_ia32__user_trap_d8)
exception(0xd8)
/*  User Trap No 217  */
ENTRY(_kernel_ia32__user_trap_d9)
exception(0xd9)
/*  User Trap No 218  */
ENTRY(_kernel_ia32__user_trap_da)
exception(0xda)
/*  User Trap No 219  */
ENTRY(_kernel_ia32__user_trap_db)
exception(0xdb)
/*  User Trap No 220  */
ENTRY(_kernel_ia32__user_trap_dc)
exception(0xdc)
/*  User Trap No 221  */
ENTRY(_kernel_ia32__user_trap_dd)
exception(0xdd)
/*  User Trap No 222  */
ENTRY(_kernel_ia32__user_trap_de)
exception(0xde)
/*  User Trap No 223  */
ENTRY(_kernel_ia32__user_trap_df)
exception(0xdf)
/*  User Trap No 224  */
ENTRY(_kernel_ia32__user_trap_e0)
exception(0xe0)
/*  User Trap No 225  */
ENTRY(_kernel_ia32__user_trap_e1)
exception(0xe1)
/*  User Trap No 226  */
ENTRY(_kernel_ia32__user_trap_e2)
exception(0xe2)
/*  User Trap No 227  */
ENTRY(_kernel_ia32__user_trap_e3)
exception(0xe3)
/*  User Trap No 228  */
ENTRY(_kernel_ia32__user_trap_e4)
exception(0xe4)
/*  User Trap No 229  */
ENTRY(_kernel_ia32__user_trap_e5)
exception(0xe5)
/*  User Trap No 230  */
ENTRY(_kernel_ia32__user_trap_e6)
exception(0xe6)
/*  User Trap No 231  */
ENTRY(_kernel_ia32__user_trap_e7)
exception(0xe7)
/*  User Trap No 232  */
ENTRY(_kernel_ia32__user_trap_e8)
exception(0xe8)
/*  User Trap No 233  */
ENTRY(_kernel_ia32__user_trap_e9)
exception(0xe9)
/*  User Trap No 234  */
ENTRY(_kernel_ia32__user_trap_ea)
exception(0xea)
/*  User Trap No 235  */
ENTRY(_kernel_ia32__user_trap_eb)
exception(0xeb)
/*  User Trap No 236  */
ENTRY(_kernel_ia32__user_trap_ec)
exception(0xec)
/*  User Trap No 237  */
ENTRY(_kernel_ia32__user_trap_ed)
exception(0xed)
/*  User Trap No 238  */
ENTRY(_kernel_ia32__user_trap_ee)
exception(0xee)
/*  User Trap No 239  */
ENTRY(_kernel_ia32__user_trap_ef)
exception(0xef)
/*  User Trap No 240  */
ENTRY(_kernel_ia32__user_trap_f0)
exception(0xf0)
/*  User Trap No 241  */
ENTRY(_kernel_ia32__user_trap_f1)
exception(0xf1)
/*  User Trap No 242  */
ENTRY(_kernel_ia32__user_trap_f2)
exception(0xf2)
/*  User Trap No 243  */
ENTRY(_kernel_ia32__user_trap_f3)
exception(0xf3)
/*  User Trap No 244  */
ENTRY(_kernel_ia32__user_trap_f4)
exception(0xf4)
/*  User Trap No 245  */
ENTRY(_kernel_ia32__user_trap_f5)
exception(0xf5)
/*  User Trap No 246  */
ENTRY(_kernel_ia32__user_trap_f6)
exception(0xf6)
/*  User Trap No 247  */
ENTRY(_kernel_ia32__user_trap_f7)
exception(0xf7)
/*  User Trap No 248  */
ENTRY(_kernel_ia32__user_trap_f8)
exception(0xf8)
/*  User Trap No 249  */
ENTRY(_kernel_ia32__user_trap_f9)
exception(0xf9)
/*  User Trap No 250  */
ENTRY(_kernel_ia32__user_trap_fa)
exception(0xfa)
/*  User Trap No 251  */
ENTRY(_kernel_ia32__user_trap_fb)
exception(0xfb)
/*  User Trap No 252  */
ENTRY(_kernel_ia32__user_trap_fc)
exception(0xfc)
/*  User Trap No 253  */
ENTRY(_kernel_ia32__user_trap_fd)
exception(0xfd)
/*  User Trap No 254  */
ENTRY(_kernel_ia32__user_trap_fe)
exception(0xfe)
/*  User Trap No 255  */
ENTRY(_kernel_ia32__user_trap_ff)
exception(0xff)

ENTRY(_kernel_ia32__ext_exc)
	restore_context


/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
