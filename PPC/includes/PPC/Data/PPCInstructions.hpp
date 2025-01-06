#pragma once

//the big fuck list of Power PC instructions, taken from a XBox list

#include <string>

namespace PPC::Data::ASM
{
	//the big fuck enum list of instructions
	enum EInstruction
	{
		eInstruction_nop = 0,

		// move register (with move to/from special registers)
		InstructionGroup_MoveRegister_Start,
		eInstruction_mr = InstructionGroup_MoveRegister_Start,
		eInstruction_mfspr,
		eInstruction_mfsprg,
		eInstruction_mfsrr0,
		eInstruction_mfsrr1,
		eInstruction_mtspr,
		eInstruction_mfmsr,
		eInstruction_mtsrr0,
		eInstruction_mtsrr1,
		eInstruction_mtsprg,
		eInstruction_mfmsrg,
		eInstruction_mtmsr,
		eInstruction_mtdar,
		eInstruction_mtdsisr,
		eInstruction_mtmsrd,
		eInstruction_mtmsree,
		eInstruction_mtxer,
		eInstruction_mfcr,
		eInstruction_mtcrf,
		eInstruction_mfocrf,
		eInstruction_mtocrf,
		eInstruction_mcrf,
		eInstruction_mftb,
		eInstruction_mflr,
		eInstruction_mtctr,
		eInstruction_mfdar,
		InstructionGroup_MoveRegister_End = eInstruction_mfdar,

		// load memory
		InstructionGroup_LoadMemory_Start,
		eInstruction_lbz = InstructionGroup_LoadMemory_Start,
		eInstruction_lhz,
		eInstruction_lwz,
		eInstruction_lbzu,
		eInstruction_lhzu,
		eInstruction_lwzu,
		eInstruction_lba,
		eInstruction_lha,
		eInstruction_lwa,
		eInstruction_lbau,
		eInstruction_lhau,
		eInstruction_lwau,
		eInstruction_ld,
		eInstruction_ldu,
		eInstruction_lmw,
		InstructionGroup_LoadMemory_End = eInstruction_lmw,

		// load memory indexed
		InstructionGroup_LoadMemoryIndexed_Start,
		eInstruction_lbzx = InstructionGroup_LoadMemoryIndexed_Start,
		eInstruction_lhzx,
		eInstruction_lwzx,
		eInstruction_lbzux,
		eInstruction_lhzux,
		eInstruction_lwzux,
		eInstruction_lbax,
		eInstruction_lhax,
		eInstruction_lwax,
		eInstruction_lbaux,
		eInstruction_lhaux,
		eInstruction_lwaux,
		eInstruction_ldx,
		eInstruction_ldux,
		InstructionGroup_LoadMemoryIndexed_End = eInstruction_ldux,

		// store memory
		InstructionGroup_StoreMemory_Start,
		eInstruction_stb = InstructionGroup_StoreMemory_Start,
		eInstruction_sth,
		eInstruction_stw,
		eInstruction_std,
		eInstruction_slwi,
		eInstruction_stbu,
		eInstruction_sthu,
		eInstruction_stwu,
		eInstruction_stdu,
		InstructionGroup_StoreMemory_End = eInstruction_stdu,

		// store memory indexed
		InstructionGroup_StoreMemoryIndexed_Start,
		eInstruction_stbx = InstructionGroup_StoreMemoryIndexed_Start,
		eInstruction_sthx,
		eInstruction_stwx,
		eInstruction_stdx,
		eInstruction_stbux,
		eInstruction_sthux,
		eInstruction_stwux,
		eInstruction_stdux,
		InstructionGroup_StoreMemoryIndexed_End = eInstruction_stdux,

		//quantized store
		eInstruction_psq_stx,
		eInstruction_psq_lx,
		eInstruction_psq_st,
		eInstruction_psq_l,

		//idk
		eInstruction_twui,

		// branch instructions
		InstructionGroup_Branch_Start,
		eInstruction_b = InstructionGroup_Branch_Start,
		eInstruction_bdnz,
		eInstruction_ba,
		eInstruction_bl,
		eInstruction_ble,
		eInstruction_blt,
		eInstruction_bla,
		eInstruction_bc,
		eInstruction_bcl,
		eInstruction_bca,
		eInstruction_bcla,
		eInstruction_bclr,
		eInstruction_bclrl,
		eInstruction_bcctr,
		eInstruction_bcctrl,
		eInstruction_beq,
		eInstruction_beq_plus,
		eInstruction_beqlr,
		eInstruction_blr,
		eInstruction_bltlr,
		eInstruction_bne,
		eInstruction_bnelr,
		eInstruction_bge,
		eInstruction_bgelr,
		eInstruction_bgt,
		eInstruction_bctr,
		eInstruction_bctrl,
		InstructionGroup_Branch_End = eInstruction_bctrl,

		// lwarx/stwcx
		eInstruction_lwarx,
		eInstruction_ldarx,
		eInstruction_stwcx_Dot, //.
		eInstruction_stdcx_Dot, //.

		// memory bariers
		eInstruction_isync,
		eInstruction_sync,
		eInstruction_lwsync,
		eInstruction_ptesync,
		eInstruction_eieio,

		// custom
		//eInstruction_cmp,
		eInstruction_fcmpu,
		eInstruction_fcmpo,
		eInstruction_twi,
		eInstruction_tdi,
		eInstruction_tw,
		eInstruction_td,

		// generic instructions
		eInstruction_sc,

		// condition register operators
		eInstruction_crand,
		eInstruction_cror,
		eInstruction_crxor,
		eInstruction_crnand,
		eInstruction_crnor,
		eInstruction_creqv,
		eInstruction_crandc,
		eInstruction_crorc,
		eInstruction_crclr,

		// load immediate
		eInstruction_li,
		eInstruction_lis,

		// math with immediate value
		eInstruction_addic,
		eInstruction_addic_Dot,
		eInstruction_addi,
		eInstruction_addis,
		eInstruction_subfic,
		eInstruction_mulli,

		// add XO-form
		eInstruction_add,
		eInstruction_add_Dot,
		eInstruction_addo,
		eInstruction_addo_Dot,

		// subtract grom XO-form
		eInstruction_subi,
		eInstruction_subic,
		eInstruction_subf,
		eInstruction_subf_Dot,
		eInstruction_subfo,
		eInstruction_subfo_Dot,

		// add carrying XO-form
		eInstruction_addc,
		eInstruction_addc_Dot,
		eInstruction_addco,
		eInstruction_addco_Dot,

		// subtract From carrying XO-form
		eInstruction_subfc,
		eInstruction_subfc_Dot,
		eInstruction_subfco,
		eInstruction_subfco_Dot,

		// add extended XO-form
		eInstruction_adde,
		eInstruction_adde_Dot,
		eInstruction_addeo,
		eInstruction_addeo_Dot,

		// subtract from extended XO-form
		eInstruction_subfe,
		eInstruction_subfe_Dot,
		eInstruction_subfeo,
		eInstruction_subfeo_Dot,
		eInstruction_subis,

		// add to minus one extended XO-form
		eInstruction_addme,
		eInstruction_addme_Dot,
		eInstruction_addmeo,
		eInstruction_addmeo_Dot,

		// subtract from minus one extended XO-form
		eInstruction_subfme,
		eInstruction_subfme_Dot,
		eInstruction_subfmeo,
		eInstruction_subfmeo_Dot,

		// add to zero extended XO-form
		eInstruction_addze,
		eInstruction_addze_Dot,
		eInstruction_addzeo,
		eInstruction_addzeo_Dot,

		// subtract from zero extended XO-form
		eInstruction_subfze,
		eInstruction_subfze_Dot,
		eInstruction_subfzeo,
		eInstruction_subfzeo_Dot,

		// negate
		eInstruction_neg,
		eInstruction_neg_Dot,
		eInstruction_nego,
		eInstruction_nego_Dot,

		// multiply low doubleword XO-form
		eInstruction_mulld,
		eInstruction_mulld_Dot,
		eInstruction_mulldo,
		eInstruction_mulldo_Dot,

		// multiply low word XO-form
		eInstruction_mullw,
		eInstruction_mullw_Dot,
		eInstruction_mullwo,
		eInstruction_mullwo_Dot,

		// multiply high doubleword XO-form
		eInstruction_mullhd,
		eInstruction_mullhd_Dot,

		// multiply High Word XO-form
		eInstruction_mullhw,
		eInstruction_mullhw_Dot,

		// multiply high doubleword unsigned XO-form
		eInstruction_mulhdu,
		eInstruction_mulhdu_Dot,

		// multiply High Word Unsigned XO-form
		eInstruction_mulhwu,
		eInstruction_mulhwu_Dot,

		// divide doubleword XO-form
		eInstruction_divd,
		eInstruction_divd_Dot,
		eInstruction_divdo,
		eInstruction_divdo_Dot,

		// divide word XO-form
		eInstruction_divw,
		eInstruction_divw_Dot,
		eInstruction_divwo,
		eInstruction_divwo_Dot,

		// divide doubleword unsigned XO-form
		eInstruction_divdu,
		eInstruction_divdu_Dot,
		eInstruction_divduo,
		eInstruction_divduo_Dot,

		// divide word unsigned XO-form
		eInstruction_divwu,
		eInstruction_divwu_Dot,
		eInstruction_divwuo,
		eInstruction_divwuo_Dot,

		// compare
		InstructionGroup_Compare_Start,
		eInstruction_cmpwi = InstructionGroup_Compare_Start,
		eInstruction_cmpdi,
		eInstruction_cmplwi,
		eInstruction_cmpldi,
		eInstruction_cmpw,
		eInstruction_cmpd,
		eInstruction_cmplw,
		eInstruction_cmpld,
		InstructionGroup_Compare_End = eInstruction_cmpld,

		// logical instructions with immediate values
		eInstruction_andi,
		eInstruction_andis,
		eInstruction_andi_Dot,
		eInstruction_andis_Dot,
		eInstruction_ori,
		eInstruction_oris,
		eInstruction_xori,
		eInstruction_xoris,

		// logical instructions
		InstructionGroup_Bitshift_Start,
		eInstruction_and = InstructionGroup_Bitshift_Start,
		eInstruction_and_Dot,
		eInstruction_or,
		eInstruction_or_Dot,
		eInstruction_xor,
		eInstruction_xor_Dot,
		eInstruction_nand,
		eInstruction_nand_Dot,
		eInstruction_nor,
		eInstruction_nor_Dot,
		eInstruction_eqv,
		eInstruction_eqv_Dot,
		eInstruction_andc,
		eInstruction_andc_Dot,
		eInstruction_orc,
		eInstruction_orc_Dot,
		InstructionGroup_Bitshift_End = eInstruction_orc_Dot,

		// byte extend
		eInstruction_extsb,
		eInstruction_extsb_Dot,
		eInstruction_extsh,
		eInstruction_extsh_Dot,
		eInstruction_extsw,
		eInstruction_extsw_Dot,
		eInstruction_extrwi,

		// population count
		eInstruction_popcntb,
		eInstruction_cntlzw,
		eInstruction_cntlzw_Dot,
		eInstruction_cntlzd,
		eInstruction_cntlzd_Dot,

		// Shift instructions with immediate params -->
		// REG,REG,IMM,IMM
		eInstruction_rldicl,
		eInstruction_rldicl_Dot,
		eInstruction_rldicr,
		eInstruction_rldicr_Dot,
		eInstruction_rldic,
		eInstruction_rldic_Dot,
		eInstruction_rldimi,
		eInstruction_rldimi_Dot,
		eInstruction_clrlwi,
		eInstruction_clrrwi,
		eInstruction_clrlslwi,

		// REG,REG,IMM,IMM,IMM
		eInstruction_rlwinm,
		eInstruction_rlwinm_Dot,
		eInstruction_rlwimi,
		eInstruction_rlwimi_Dot,

		// REG,REG,REG,IMM
		eInstruction_rldcl,
		eInstruction_rldcl_Dot,
		eInstruction_rldcr,
		eInstruction_rldcr_Dot,

		// REG,REG,REG,IMM,IMM
		eInstruction_rlwnm,
		eInstruction_rlwnm_Dot,

		// Extended shifts
		eInstruction_sld,
		eInstruction_sld_Dot,
		eInstruction_slw,
		eInstruction_slw_Dot,
		eInstruction_srd,
		eInstruction_srd_Dot,
		eInstruction_srw,
		eInstruction_srwi,
		eInstruction_srw_Dot,
		eInstruction_srad,
		eInstruction_srad_Dot,
		eInstruction_sraw,
		eInstruction_sraw_Dot,

		// Extended shifts with immediate... geez..
		eInstruction_srawi,
		eInstruction_srawi_Dot,
		eInstruction_sradi,
		eInstruction_sradi_Dot,

		// Cache operation instructions
		eInstruction_dcbi,
		eInstruction_dcbf,
		eInstruction_dcbst,
		eInstruction_dcbt,
		eInstruction_dcbtst,
		eInstruction_dcbz,

		//  Floating point load instructions
		eInstruction_lfs,
		eInstruction_lfsu,
		eInstruction_lfsx,
		eInstruction_lfsux,
		eInstruction_lfd,
		eInstruction_lfdu,
		eInstruction_lfdx,
		eInstruction_lfdux,

		//  Floating point store instructions
		eInstruction_stfs,
		eInstruction_stfsu,
		eInstruction_stfsx,
		eInstruction_stfsux,
		eInstruction_stfd,
		eInstruction_stfdu,
		eInstruction_stfdx,
		eInstruction_stfdux,

		// Store float point as integer word indexed
		eInstruction_stfiwx,

		//store move register
		eInstruction_stmw,

		// Floating point move and single op instructions
		eInstruction_fmr,
		eInstruction_fmr_Dot,
		eInstruction_fneg,
		eInstruction_fneg_Dot,
		eInstruction_fabs,
		eInstruction_fabs_Dot,
		eInstruction_fnabs,
		eInstruction_fnabs_Dot,

		// Floating point arithmetic instructions
		eInstruction_fadd,
		eInstruction_fadd_Dot,
		eInstruction_fadds,
		eInstruction_fadds_Dot,
		eInstruction_fsub,
		eInstruction_fsub_Dot,
		eInstruction_fsubs,
		eInstruction_fsubs_Dot,
		eInstruction_fmul,
		eInstruction_fmul_Dot,
		eInstruction_fmuls,
		eInstruction_fmuls_Dot,
		eInstruction_fdiv,
		eInstruction_fdiv_Dot,
		eInstruction_fdivs,
		eInstruction_fdivs_Dot,
		eInstruction_fsqrt,
		eInstruction_fsqrt_Dot,
		eInstruction_frsqrtx,
		eInstruction_frsqrtx_Dot,
		eInstruction_frsqrte,
		eInstruction_fre,
		eInstruction_fre_Dot,

		// Floating point mad instructions
		eInstruction_fmadd,
		eInstruction_fmadd_Dot,
		eInstruction_fmadds,
		eInstruction_fmadds_Dot,
		eInstruction_fmsub,
		eInstruction_fmsub_Dot,
		eInstruction_fmsubs,
		eInstruction_fmsubs_Dot,
		eInstruction_fnmadd,
		eInstruction_fnmadd_Dot,
		eInstruction_fnmadds,
		eInstruction_fnmadds_Dot,
		eInstruction_fnmsub,
		eInstruction_fnmsub_Dot,
		eInstruction_fnmsubs,
		eInstruction_fnmsubs_Dot,

		// Floating point rounding and conversion
		eInstruction_frsp,
		eInstruction_frsp_Dot,
		eInstruction_fctid,
		eInstruction_fctid_Dot,
		eInstruction_fctidz,
		eInstruction_fctidz_Dot,
		eInstruction_fctiw,
		eInstruction_fctiw_Dot,
		eInstruction_fctiwz,
		eInstruction_fctiwz_Dot,
		eInstruction_fcfid,
		eInstruction_fcfid_Dot,

		// Floating point select
		eInstruction_fsel,
		eInstruction_fsel_Dot,

		// Floating point control registers
		eInstruction_mffs,
		eInstruction_mffs_Dot,
		eInstruction_mcrfs,
		eInstruction_mtfsfi,
		eInstruction_mtfsfi_Dot,
		eInstruction_mtfsf,
		eInstruction_mtfsf_Dot,
		eInstruction_mtfsb0,
		eInstruction_mtfsb0_Dot,
		eInstruction_mtfsb1,
		eInstruction_mtfsb1_Dot,
		eInstruction_mtlr,

		// VMX instructions
		eInstruction_lvebx,
		eInstruction_lvehx,
		eInstruction_lvewx,		//+
		eInstruction_lvlx,		//+
		eInstruction_lvlxl,		//+
		eInstruction_lvrx,		//+
		eInstruction_lvrxl,		//+
		eInstruction_lvsl,
		eInstruction_lvsr,
		eInstruction_lvx,			//+
		eInstruction_lvxl,		//+
		eInstruction_mfvscr,
		eInstruction_mtvscr,
		eInstruction_stvebx,
		eInstruction_stvehx,
		eInstruction_stvewx,		//+
		eInstruction_stvlx,		//+
		eInstruction_stvlxl,		//+
		eInstruction_stvrx,		//+
		eInstruction_stvrxl,		//+
		eInstruction_stvx,		//+
		eInstruction_stvxl,		//+
		eInstruction_lhbrx,
		eInstruction_lwbrx,
		eInstruction_sthbrx,
		eInstruction_stwbrx,
		eInstruction_lswi,
		eInstruction_lswx,
		eInstruction_stswi,
		eInstruction_stswx,
		eInstruction_vaddcuw,
		eInstruction_vaddfp,		//+
		eInstruction_vaddsbs,
		eInstruction_vaddshs,
		eInstruction_vaddsws,
		eInstruction_vaddubm,
		eInstruction_vaddubs,
		eInstruction_vadduhm,
		eInstruction_vadduhs,
		eInstruction_vadduwm,
		eInstruction_vadduws,
		eInstruction_vand,		//+
		eInstruction_vandc,		//+
		eInstruction_vavgsb,
		eInstruction_vavgsh,
		eInstruction_vavgsw,
		eInstruction_vavgub,
		eInstruction_vavguh,
		eInstruction_vavguw,
		eInstruction_vcfpsxws,	//+
		eInstruction_vcfpuxws,	//+
		eInstruction_vcsxwfp, //+
		eInstruction_vcuxwfp, //+
		eInstruction_vctsxs,	//+
		eInstruction_vctuxs,		//+
		eInstruction_vcfsx,	//+
		eInstruction_vcfux,	//+
		eInstruction_vcmpbfp,
		eInstruction_vcmpbfp_Dot,
		eInstruction_vcmpeqfp,
		eInstruction_vcmpeqfp_Dot,
		eInstruction_vcmpequb,
		eInstruction_vcmpequb_Dot,
		eInstruction_vcmpequh,
		eInstruction_vcmpequh_Dot,
		eInstruction_vcmpequw,
		eInstruction_vcmpequw_Dot,
		eInstruction_vcmpgefp,
		eInstruction_vcmpgefp_Dot,
		eInstruction_vcmpgtfp,
		eInstruction_vcmpgtfp_Dot,
		eInstruction_vcmpgtsb,
		eInstruction_vcmpgtsb_Dot,
		eInstruction_vcmpgtsh,
		eInstruction_vcmpgtsh_Dot,
		eInstruction_vcmpgtsw,
		eInstruction_vcmpgtsw_Dot,
		eInstruction_vcmpgtub,
		eInstruction_vcmpgtub_Dot,
		eInstruction_vcmpgtuh,
		eInstruction_vcmpgtuh_Dot,
		eInstruction_vcmpgtuw,
		eInstruction_vcmpgtuw_Dot,
		eInstruction_vexptefp,	//+
		eInstruction_vlogefp,		//+
		eInstruction_vmaddcfp128,
		eInstruction_vmaddfp,		//+
		eInstruction_vmaxfp,		//+
		eInstruction_vmaxsb,
		eInstruction_vmaxsh,
		eInstruction_vmaxsw,
		eInstruction_vmaxub,
		eInstruction_vmaxuh,
		eInstruction_vmaxuw,
		eInstruction_vminfp,		//+
		eInstruction_vminsb,
		eInstruction_vminsh,
		eInstruction_vminsw,
		eInstruction_vminub,
		eInstruction_vminuh,
		eInstruction_vminuw,
		eInstruction_vmrghb,
		eInstruction_vmrghh,
		eInstruction_vmrghw,		//+
		eInstruction_vmrglb,
		eInstruction_vmrglh,
		eInstruction_vmrglw,		//+
		eInstruction_vdot3fp,		//+
		eInstruction_vdot4fp,		//+
		eInstruction_vmulfp128,
		eInstruction_vnmsubfp,	//+
		eInstruction_vnor,		//+
		eInstruction_vor,			//+
		eInstruction_vperm,		//+
		eInstruction_vpermwi128,
		eInstruction_vpkd3d128,
		eInstruction_vpkpx,
		eInstruction_vpkshss,		//+
		eInstruction_vpkshus,		//+
		eInstruction_vpkswss,		//+
		eInstruction_vpkswus,		//+
		eInstruction_vpkuhum,		//+
		eInstruction_vpkuhus,		//+
		eInstruction_vpkuwum,		//+
		eInstruction_vpkuwus,		//+
		eInstruction_vrefp,		//+
		eInstruction_rfi,
		eInstruction_vrfim,		//+
		eInstruction_vrfin,		//+
		eInstruction_vrfip,		//+
		eInstruction_vrfiz,		//+
		eInstruction_vrlb,
		eInstruction_vrlh,
		eInstruction_vrlimi128,
		eInstruction_vrlw,		//+
		eInstruction_vrsqrtefp,	//+
		eInstruction_vsel,		//+
		eInstruction_vsl,
		eInstruction_vslb,
		eInstruction_vsldoi,		//+
		eInstruction_vslh,
		eInstruction_vslo,		//+
		eInstruction_vslw,		//+
		eInstruction_vspltb,
		eInstruction_vsplth,
		eInstruction_vspltisb,
		eInstruction_vspltish,
		eInstruction_vspltisw,	//+
		eInstruction_vspltw,		//+
		eInstruction_vsr,
		eInstruction_vsrab,
		eInstruction_vsrah,
		eInstruction_vsraw,		//+
		eInstruction_vsrb,
		eInstruction_vsrh,
		eInstruction_vsro,		//+
		eInstruction_vsrw,		//+
		eInstruction_vsubcuw,
		eInstruction_vsubfp,		//+
		eInstruction_vsubsbs,
		eInstruction_vsubshs,
		eInstruction_vsubsws,
		eInstruction_vsububm,
		eInstruction_vsububs,
		eInstruction_vsubuhm,
		eInstruction_vsubuhs,
		eInstruction_vsubuwm,
		eInstruction_vsubuws,
		eInstruction_vupkd3d128,
		eInstruction_vupkhpx,
		eInstruction_vupkhsb,		//+
		eInstruction_vupkhsh,	//+
		eInstruction_vupklpx,
		eInstruction_vupklsb,		//+
		eInstruction_vupklsh,		//+
		eInstruction_vxor,		//+

		//extra
		eInstruction_icbi,
		eInstruction_rotlwi,
		eInstruction_rotrwi,

		eInstruction_MAX
	};

	//the big fuck string version
	static const char* POWER_PC_ASSEMBLY_INSTRUCTIONS_KEYWORD_STRS[eInstruction_MAX] = {
		"nop",

		// move register (with move to/from special registers)
		"mr",
		"mfspr",
		"mfsprg",
		"mfsrr0",
		"mfsrr1",
		"mtspr",
		"mfmsr",
		"mtsrr0",
		"mtsrr1",
		"mtsprg",
		"mfmsrg",
		"mtmsr",
		"mtdar",
		"mtdsisr",
		"mtmsrd",
		"mtmsree",
		"mtxer",
		"mfcr",
		"mtcrf",
		"mfocrf",
		"mtocrf",
		"mcrf",
		"mftb",
		"mflr",
		"mtctr",
		"mfdar",

		// load memory
		"lbz",
		"lhz",
		"lwz",
		"lbzu",
		"lhzu",
		"lwzu",
		"lba",
		"lha",
		"lwa",
		"lbau",
		"lhau",
		"lwau",
		"ld",
		"ldu",
		"lmw",

		// load memory indexed
		"lbzx",
		"lhzx",
		"lwzx",
		"lbzux",
		"lhzux",
		"lwzux",
		"lbax",
		"lhax",
		"lwax",
		"lbaux",
		"lhaux",
		"lwaux",
		"ldx",
		"ldux",

		// store memory
		"stb",
		"sth",
		"stw",
		"std",
		"slwi",
		"stbu",
		"sthu",
		"stwu",
		"stdu",

		// store memory indexed
		"stbx",
		"sthx",
		"stwx",
		"stdx",
		"stbux",
		"sthux",
		"stwux",
		"stdux",

		//quantized store
		"psq_stx",
		"psq_lx",
		"psq_st",
		"psq_l",

		//idk
		"twui",

		// branch instructions
		"b",
		"bdnz",
		"ba",
		"bl",
		"ble",
		"blt",
		"bla",
		"bc",
		"bcl",
		"bca",
		"bcla",
		"bclr",
		"bclrl",
		"bcctr",
		"bcctrl",
		"beq",
		"beq_plus",
		"beqlr",
		"blr",
		"bltlr",
		"bne",
		"bnelr",
		"bge",
		"bgelr",
		"bgt",
		"bctr",
		"bctrl",

		// lwarx/stwcx
		"lwarx",
		"ldarx",
		"stwcx.", //.
		"stdcx.", //.

		// memory bariers
		"isync",
		"sync",
		"lwsync",
		"ptesync",
		"eieio",

		// custom
		//"cmp",
		"fcmpu",
		"fcmpo",
		"twi",
		"tdi",
		"tw",
		"td",

		// generic instructions
		"sc",

		// condition register operators
		"crand",
		"cror",
		"crxor",
		"crnand",
		"crnor",
		"creqv",
		"crandc",
		"crorc",
		"crclr",

		// load immediate
		"li",
		"lis",

		// math with immediate value
		"addic",
		"addic.",
		"addi",
		"addis",
		"subfic",
		"mulli",

		// add XO-form
		"add",
		"add.",
		"addo",
		"addo.",

		// subtract grom XO-form
		"subi",
		"subic",
		"subf",
		"subf.",
		"subfo",
		"subfo.",

		// add carrying XO-form
		"addc",
		"addc.",
		"addco",
		"addco.",

		// subtract From carrying XO-form
		"subfc",
		"subfc.",
		"subfco",
		"subfco.",

		// add extended XO-form
		"adde",
		"adde.",
		"addeo",
		"addeo.",

		// subtract from extended XO-form
		"subfe",
		"subfe.",
		"subfeo",
		"subfeo.",
		"subis",

		// add to minus one extended XO-form
		"addme",
		"addme.",
		"addmeo",
		"addmeo.",

		// subtract from minus one extended XO-form
		"subfme",
		"subfme.",
		"subfmeo",
		"subfmeo.",

		// add to zero extended XO-form
		"addze",
		"addze.",
		"addzeo",
		"addzeo.",

		// subtract from zero extended XO-form
		"subfze",
		"subfze.",
		"subfzeo",
		"subfzeo.",

		// negate
		"neg",
		"neg.",
		"nego",
		"nego.",

		// multiply low doubleword XO-form
		"mulld",
		"mulld.",
		"mulldo",
		"mulldo.",

		// multiply low word XO-form
		"mullw",
		"mullw.",
		"mullwo",
		"mullwo.",

		// multiply high doubleword XO-form
		"mullhd",
		"mullhd.",

		// multiply High Word XO-form
		"mullhw",
		"mullhw.",

		// multiply high doubleword unsigned XO-form
		"mulhdu",
		"mulhdu.",

		// multiply High Word Unsigned XO-form
		"mulhwu",
		"mulhwu.",

		// divide doubleword XO-form
		"divd",
		"divd.",
		"divdo",
		"divdo.",

		// divide word XO-form
		"divw",
		"divw.",
		"divwo",
		"divwo.",

		// divide doubleword unsigned XO-form
		"divdu",
		"divdu.",
		"divduo",
		"divduo.",

		// divide word unsigned XO-form
		"divwu",
		"divwu.",
		"divwuo",
		"divwuo.",

		// compare
		"cmpwi",
		"cmpdi",
		"cmplwi",
		"cmpldi",
		"cmpw",
		"cmpd",
		"cmplw",
		"cmpld",

		// logical instructions with immediate values
		"andi",
		"andis",
		"andi.",
		"andis.",
		"ori",
		"oris",
		"xori",
		"xoris",

		// logical instructions
		"and",
		"and.",
		"or",
		"or.",
		"xor",
		"xor.",
		"nand",
		"nand.",
		"nor",
		"nor.",
		"eqv",
		"eqv.",
		"andc",
		"andc.",
		"orc",
		"orc.",

		// byte extend
		"extsb",
		"extsb.",
		"extsh",
		"extsh.",
		"extsw",
		"extsw.",
		"extrwi",

		// population count
		"popcntb",
		"cntlzw",
		"cntlzw.",
		"cntlzd",
		"cntlzd.",

		// Shift instructions with immediate params -->
		// REG",REG",IMM",IMM
		"rldicl",
		"rldicl.",
		"rldicr",
		"rldicr.",
		"rldic",
		"rldic.",
		"rldimi",
		"rldimi.",
		"clrlwi",
		"clrrwi",
		"clrlslwi",

		// REG",REG",IMM",IMM",IMM
		"rlwinm",
		"rlwinm.",
		"rlwimi",
		"rlwimi.",

		// REG",REG",REG",IMM
		"rldcl",
		"rldcl.",
		"rldcr",
		"rldcr.",

		// REG",REG",REG",IMM",IMM
		"rlwnm",
		"rlwnm.",

		// Extended shifts
		"sld",
		"sld.",
		"slw",
		"slw.",
		"srd",
		"srd.",
		"srw",
		"srwi",
		"srw.",
		"srad",
		"srad.",
		"sraw",
		"sraw.",

		// Extended shifts with immediate... geez..
		"srawi",
		"srawi.",
		"sradi",
		"sradi.",

		// Cache operation instructions
		"dcbi",
		"dcbf",
		"dcbst",
		"dcbt",
		"dcbtst",
		"dcbz",

		//  Floating point load instructions
		"lfs",
		"lfsu",
		"lfsx",
		"lfsux",
		"lfd",
		"lfdu",
		"lfdx",
		"lfdux",

		//  Floating point store instructions
		"stfs",
		"stfsu",
		"stfsx",
		"stfsux",
		"stfd",
		"stfdu",
		"stfdx",
		"stfdux",

		// Store float point as integer word indexed
		"stfiwx",

		//store move register
		"stmw",

		// Floating point move and single op instructions
		"fmr",
		"fmr.",
		"fneg",
		"fneg.",
		"fabs",
		"fabs.",
		"fnabs",
		"fnabs.",

		// Floating point arithmetic instructions
		"fadd",
		"fadd.",
		"fadds",
		"fadds.",
		"fsub",
		"fsub.",
		"fsubs",
		"fsubs.",
		"fmul",
		"fmul.",
		"fmuls",
		"fmuls.",
		"fdiv",
		"fdiv.",
		"fdivs",
		"fdivs.",
		"fsqrt",
		"fsqrt.",
		"frsqrtx",
		"frsqrtx.",
		"frsqrte",
		"fre",
		"fre.",

		// Floating point mad instructions
		"fmadd",
		"fmadd.",
		"fmadds",
		"fmadds.",
		"fmsub",
		"fmsub.",
		"fmsubs",
		"fmsubs.",
		"fnmadd",
		"fnmadd.",
		"fnmadds",
		"fnmadds.",
		"fnmsub",
		"fnmsub.",
		"fnmsubs",
		"fnmsubs.",

		// Floating point rounding and conversion
		"frsp",
		"frsp.",
		"fctid",
		"fctid.",
		"fctidz",
		"fctidz.",
		"fctiw",
		"fctiw.",
		"fctiwz",
		"fctiwz.",
		"fcfid",
		"fcfid.",

		// Floating point select
		"fsel",
		"fsel.",

		// Floating point control registers
		"mffs",
		"mffs.",
		"mcrfs",
		"mtfsfi",
		"mtfsfi.",
		"mtfsf",
		"mtfsf.",
		"mtfsb0",
		"mtfsb0.",
		"mtfsb1",
		"mtfsb1.",
		"mtlr",

		// VMX instructions
		"lvebx",
		"lvehx",
		"lvewx",		//+
		"lvlx",		//+
		"lvlxl",		//+
		"lvrx",		//+
		"lvrxl",		//+
		"lvsl",
		"lvsr",
		"lvx",			//+
		"lvxl",		//+
		"mfvscr",
		"mtvscr",
		"stvebx",
		"stvehx",
		"stvewx",		//+
		"stvlx",		//+
		"stvlxl",		//+
		"stvrx",		//+
		"stvrxl",		//+
		"stvx",		//+
		"stvxl",		//+
		"lhbrx",
		"lwbrx",
		"sthbrx",
		"stwbrx",
		"lswi",
		"lswx",
		"stswi",
		"stswx",
		"vaddcuw",
		"vaddfp",		//+
		"vaddsbs",
		"vaddshs",
		"vaddsws",
		"vaddubm",
		"vaddubs",
		"vadduhm",
		"vadduhs",
		"vadduwm",
		"vadduws",
		"vand",		//+
		"vandc",		//+
		"vavgsb",
		"vavgsh",
		"vavgsw",
		"vavgub",
		"vavguh",
		"vavguw",
		"vcfpsxws",	//+
		"vcfpuxws",	//+
		"vcsxwfp", //+
		"vcuxwfp", //+
		"vctsxs",	//+
		"vctuxs",		//+
		"vcfsx",	//+
		"vcfux",	//+
		"vcmpbfp",
		"vcmpbfp.",
		"vcmpeqfp",
		"vcmpeqfp.",
		"vcmpequb",
		"vcmpequb.",
		"vcmpequh",
		"vcmpequh.",
		"vcmpequw",
		"vcmpequw.",
		"vcmpgefp",
		"vcmpgefp.",
		"vcmpgtfp",
		"vcmpgtfp.",
		"vcmpgtsb",
		"vcmpgtsb.",
		"vcmpgtsh",
		"vcmpgtsh.",
		"vcmpgtsw",
		"vcmpgtsw.",
		"vcmpgtub",
		"vcmpgtub.",
		"vcmpgtuh",
		"vcmpgtuh.",
		"vcmpgtuw",
		"vcmpgtuw.",
		"vexptefp",	//+
		"vlogefp",		//+
		"vmaddcfp128",
		"vmaddfp",		//+
		"vmaxfp",		//+
		"vmaxsb",
		"vmaxsh",
		"vmaxsw",
		"vmaxub",
		"vmaxuh",
		"vmaxuw",
		"vminfp",		//+
		"vminsb",
		"vminsh",
		"vminsw",
		"vminub",
		"vminuh",
		"vminuw",
		"vmrghb",
		"vmrghh",
		"vmrghw",		//+
		"vmrglb",
		"vmrglh",
		"vmrglw",		//+
		"vdot3fp",		//+
		"vdot4fp",		//+
		"vmulfp128",
		"vnmsubfp",	//+
		"vnor",		//+
		"vor",			//+
		"vperm",		//+
		"vpermwi128",
		"vpkd3d128",
		"vpkpx",
		"vpkshss",		//+
		"vpkshus",		//+
		"vpkswss",		//+
		"vpkswus",		//+
		"vpkuhum",		//+
		"vpkuhus",		//+
		"vpkuwum",		//+
		"vpkuwus",		//+
		"vrefp",		//+
		"rfi",
		"vrfim",		//+
		"vrfin",		//+
		"vrfip",		//+
		"vrfiz",		//+
		"vrlb",
		"vrlh",
		"vrlimi128",
		"vrlw",		//+
		"vrsqrtefp",	//+
		"vsel",		//+
		"vsl",
		"vslb",
		"vsldoi",		//+
		"vslh",
		"vslo",		//+
		"vslw",		//+
		"vspltb",
		"vsplth",
		"vspltisb",
		"vspltish",
		"vspltisw",	//+
		"vspltw",		//+
		"vsr",
		"vsrab",
		"vsrah",
		"vsraw",		//+
		"vsrb",
		"vsrh",
		"vsro",		//+
		"vsrw",		//+
		"vsubcuw",
		"vsubfp",		//+
		"vsubsbs",
		"vsubshs",
		"vsubsws",
		"vsububm",
		"vsububs",
		"vsubuhm",
		"vsubuhs",
		"vsubuwm",
		"vsubuws",
		"vupkd3d128",
		"vupkhpx",
		"vupkhsb",		//+
		"vupkhsh",	//+
		"vupklpx",
		"vupklsb",		//+
		"vupklsh",		//+
		"vxor",		//+

		//extra
		"icbi",
		"rotlwi",
		"rotrwi"
	};

	//checks if a string keyword is a assembly instruction
	static inline bool IsASMInstructionStr(const char* keyword, uint32_t& arrayIndex, EInstruction& instruction)
	{
		for (uint32_t i = 0; i < eInstruction_MAX; ++i)
		{
			if (!strcmp(keyword, POWER_PC_ASSEMBLY_INSTRUCTIONS_KEYWORD_STRS[i]))
			{
				arrayIndex = i;
				instruction = (EInstruction)i;
				return true;
			}
		}

		return false;
	}

	//defines specific ASM instruction types
	enum class ASMInstructionKind
	{
		MoveSpecialRegister = 0, //move special register

		Store,
		Load,

		Compare,
		Brach,

		Bitshift,

		Max
	};

	//maps specfic assembly instructions to branch variant
	static inline bool IsASMInstructionKind_Branch(const EInstruction& inst)
	{
		//if it's within the specified, it is one of thoses so we return it
		return (inst >= InstructionGroup_Branch_Start && inst <= InstructionGroup_Branch_End);
	}

	//maps specfic assembly instructions to move special regsiter variant
	static inline bool IsASMInstructionKind_MoveSpecialRegister(const EInstruction& inst)
	{
		//if it's within the specified, it is one of thoses so we return it
		return (inst >= InstructionGroup_MoveRegister_Start && inst <= InstructionGroup_MoveRegister_End);
	}

	//maps specfic assembly instructions to load variant

	//maps specfic assembly instructions to store variant

	//maps specfic assembly instructions to compare variant
	static inline bool IsASMInstructionKind_Compare(const EInstruction& inst)
	{
		//if it's within the specified, it is one of thoses so we return it
		return (inst >= InstructionGroup_Compare_Start && inst <= InstructionGroup_Compare_End);
	}

	//maps specfic assembly instructions to bitshift
	static inline bool IsASMInstructionKind_Bitshift(const EInstruction& inst)
	{
		//if it's within the specified, it is one of thoses so we return it
		return (inst >= InstructionGroup_Bitshift_Start && inst <= InstructionGroup_Bitshift_End);
	}

	//gets the specific kind of ASM instruction it is
	static inline void GetASMInstructionKind(const EInstruction& inst, ASMInstructionKind& kind)
	{
		if (IsASMInstructionKind_MoveSpecialRegister(inst))
			kind = ASMInstructionKind::MoveSpecialRegister;
		else if (IsASMInstructionKind_Branch(inst))
			kind = ASMInstructionKind::Brach;
		else if (IsASMInstructionKind_Compare(inst))
			kind = ASMInstructionKind::Compare;
		else if (IsASMInstructionKind_Bitshift(inst))
			kind = ASMInstructionKind::Bitshift;
		else
			kind = ASMInstructionKind::Max;
	}
}