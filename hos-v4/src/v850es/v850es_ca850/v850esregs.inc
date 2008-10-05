#	------------------------------------------------------------------------
#		�ץ����å��쥸�������
#								Copyright (C) 1998-2008 by Project HOS
#								http://sourceforge.jp/projects/hos/
#	------------------------------------------------------------------------
#	************************************************************************
#		�����å��ե졼�����
#	************************************************************************
	.set	pt_r0,		0		--  0*4	-- �����쥸����
	.set	pt_r1,		4		--  1*4	-- ������֥�ͽ��쥸����
	.set	pt_r2,		8		--  2*4
	.set	pt_r3,		12		--  3*4	-- sp �����å��ݥ���
	.set	pt_r4,		16		--  4*4	-- gp �������Х�ݥ���
	.set	pt_r5,		20		--  5*4	-- tp �ƥ����ȥݥ���
	.set	pt_r6,		24		--  6*4
	.set	pt_r7,		28		--  7*4
	.set	pt_r8,		32		--  8*4
	.set	pt_r9,		36		--  9*4
	.set	pt_r10,		40		-- 10*4
	.set	pt_r11,		44		-- 11*4
	.set	pt_r12,		48		-- 12*4
	.set	pt_r13,		52		-- 13*4
	.set	pt_r14,		56		-- 14*4
	.set	pt_r15,		60		-- 15*4
	.set	pt_r16,		64		-- 16*4
	.set	pt_r17,		68		-- 17*4
	.set	pt_r18,		72		-- 18*4
	.set	pt_r19,		76		-- 19*4
	.set	pt_r20,		80		-- 20*4
	.set	pt_r21,		84		-- 21*4
	.set	pt_r22,		88		-- 22*4
	.set	pt_r23,		92		-- 23*4
	.set	pt_r24,		96		-- 24*4
	.set	pt_r25,		100		-- 25*4
	.set	pt_r26,		104		-- 26*4
	.set	pt_r27,		108		-- 27*4
	.set	pt_r28,		112		-- 28*4
	.set	pt_r29,		116		-- 29*4
	.set	pt_r30,		120		-- 30*4	-- ep ������ȥݥ����
	.set	pt_r31,		124		-- 31*4	-- lp ��󥯥ݥ���
	.set	pt_eipc,	128		-- 32*4	-- eipc ����߻���������쥸����
	.set	pt_eipsw,	132		-- 33*4	-- eipsw ����߻���������쥸����
	.set	pt_fepc,	136		-- 34*4	-- NMI����������쥸����
	.set	pt_fepsw,	140		-- 35*4	-- NMI����������쥸����
	.set	pt_ecr,		144		-- 36*4	-- ������װ��쥸����
	.set	pt_psw,		148		-- 37*4	-- �ץ�����ॹ�ơ��������
	.set	pt_ctpc,	152		-- 38*4	-- CALLT�¹Ի���������쥸����
	.set	pt_ctpsw,	156		-- 39*4	-- CALLT�¹Ի���������쥸����
	.set	pt_dbpc,	160		-- 40*4	-- �㳰/�ǥХå����ȥ�å׻���������쥸����
	.set	pt_dbpsw,	164		-- 41*4	-- �㳰/�ǥХå����ȥ�å׻���������쥸����
	.set	pt_ctbp,	168		-- 42*4	-- CALLT�١����ݥ���
	.set	pt_ssf,		172		-- 43*4	-- �����å��ե졼�ॵ���� (40*4=160�Х���)
	.set	pt_sp,		pt_r3	--  3*4	-- 12
	.set	pt_ep,		pt_r30	-- 30*4	-- 120
	.set	pt_lp,		pt_r31	-- 31*4	-- 124
#	************************************************************************
#		�쥸����̾���
#	************************************************************************
	.set	eipc,		0				-- ����߻���������쥸����
	.set	eipsw,		1				-- ����߻���������쥸����
	.set	fepc,		2				-- NMI ����������쥸����
	.set	fepsw,		3				-- NMI ����������쥸����
	.set	ecr,		4				-- ������װ��쥸����
	.set	psw,		5				-- �ץ�����ࡦ���ơ����������
	.set	ctpc,		16				-- �ơ��֥뻲�ȥ��������������쥸����
	.set	ctpsw,		17				-- �ơ��֥뻲�ȥ��������������쥸����
	.set	dbpc,		18				-- ����̿���㳰����������쥸����
	.set	dbpsw,		19				-- ����̿���㳰����������쥸����
	.set	ctbp,		20				-- CALLT�ѥ١������ݥ���
#	************************************************************************
#		�쥸��������ޥ���
#	************************************************************************
.macro	pushall
		st.w	r10, pt_r10-pt_ssf[sp]	-- r10 ��ǽ������
		stsr	psw, r10				-- �ץ�����ॹ�ơ��ȥ��
		andi	0b00011111, r10, r10
		st.w	r10, pt_psw-pt_ssf[sp]
		st.w	ep, pt_ep-pt_ssf[sp]	-- ep(r30) �쥸������ǽ������
		addi	-pt_ssf, sp, ep			-- ep(r30) �쥸�����˥����å��ե졼������
	.if 0
		stsr	eipc, r10				-- ����߻���������쥸����
		sst.w	r10, pt_eipc[ep]
	.endif
	.if 0
		stsr	eipsw, r10				-- ����߻���������쥸����
		sst.w	r10, pt_eipsw[ep]
	.endif
	.if 0
		stsr	fepc, r10				-- NMI �����������쥸����
		sst.w	r10, pt_fepc[ep]
	.endif
	.if 0
		stsr	fepsw, r10				-- NMI �����������쥸����
		sst.w	r10, pt_fepsw[ep]
	.endif
	.if 0
		stsr	ecr, r10				-- ������װ��쥸����
		sst.w	r10, pt_ecr[ep]
	.endif
		stsr	ctpc, r10				-- CALLT�¹Ի���������쥸����
		sst.w	r10, pt_ctpc[ep]
		stsr	ctpsw, r10				-- CALLT�¹Ի���������쥸����
		sst.w	r10, pt_ctpsw[ep]
	.if 0
		stsr	ctbp, r10				-- CALLT�١����ݥ���
		sst.w	r10, pt_ctbp[ep]
	.endif
#		sst.w	r0,  pt_r0[ep]			-- �����쥸����
	.option nowarning
		sst.w	r1,  pt_r1[ep]
	.option warning
#		sst.w	r2,  pt_r2[ep]			-- RTOS���ѥ쥸����(HOS�Ǥ������������ʤ�)
		sst.w	r3,  pt_r3[ep]			-- sp(r3) �����å��ݥ���
		sst.w	r4,  pt_r4[ep]			-- gp(r4) �������Х�ݥ���
		sst.w	r5,  pt_r5[ep]			-- tp(r4) �ƥ����ȥݥ���
		sst.w	r6,  pt_r6[ep]
		sst.w	r7,  pt_r7[ep]
		sst.w	r8,  pt_r8[ep]
		sst.w	r9,  pt_r9[ep]
#		sst.w	r10, pt_r10[ep]			-- �ǽ������
		sst.w	r11, pt_r11[ep]
		sst.w	r12, pt_r12[ep]
		sst.w	r13, pt_r13[ep]
		sst.w	r14, pt_r14[ep]
		sst.w	r15, pt_r15[ep]
		sst.w	r16, pt_r16[ep]
		sst.w	r17, pt_r17[ep]
		sst.w	r18, pt_r18[ep]
		sst.w	r19, pt_r19[ep]
		sst.w	r20, pt_r20[ep]
		sst.w	r21, pt_r21[ep]
		sst.w	r22, pt_r22[ep]
		sst.w	r23, pt_r23[ep]
		sst.w	r24, pt_r24[ep]
		sst.w	r25, pt_r25[ep]
		sst.w	r26, pt_r26[ep]
		sst.w	r27, pt_r27[ep]
		sst.w	r28, pt_r28[ep]
		sst.w	r29, pt_r29[ep]
#		sst.w	r30, pt_r30[ep]			-- ep(r30) �ǽ������
		sst.w	r31, pt_r31[ep]			-- lp(r31)
		mov		ep, sp
.endm
#	************************************************************************
#		�쥸���������ޥ���
#	************************************************************************
.macro	popall
		mov		sp, ep					-- ep �쥸������ sp �쥸�����ͤ�����
#		sld.w	pt_r0[ep],  r0			-- �����쥸����
	.option nowarning
		sld.w	pt_r1[ep],  r1
	.option warning
#		sld.w	pt_r2[ep],  r2			-- RTOS���ѥ쥸����(HOS�Ǥ������������ʤ�)
		sld.w	pt_r3[ep],  r3			-- sp(r3) �����å��ݥ���
		sld.w	pt_r4[ep],  r4			-- gp(r4) �������Х�ݥ���
		sld.w	pt_r5[ep],  r5			-- tp(r5) �ƥ����ȥݥ���
		sld.w	pt_r6[ep],  r6
		sld.w	pt_r7[ep],  r7
		sld.w	pt_r8[ep],  r8
		sld.w	pt_r9[ep],  r9
#		sld.w	pt_r10[ep], r10			-- �Ǹ������
		sld.w	pt_r11[ep], r11
		sld.w	pt_r12[ep], r12
		sld.w	pt_r13[ep], r13
		sld.w	pt_r14[ep], r14
		sld.w	pt_r15[ep], r15
		sld.w	pt_r16[ep], r16
		sld.w	pt_r17[ep], r17
		sld.w	pt_r18[ep], r18
		sld.w	pt_r19[ep], r19
		sld.w	pt_r20[ep], r20
		sld.w	pt_r21[ep], r21
		sld.w	pt_r22[ep], r22
		sld.w	pt_r23[ep], r23
		sld.w	pt_r24[ep], r24
		sld.w	pt_r25[ep], r25
		sld.w	pt_r26[ep], r26
		sld.w	pt_r27[ep], r27
		sld.w	pt_r28[ep], r28
		sld.w	pt_r29[ep], r29
#		sld.w	pt_r30[ep], r30			-- ep(r30) �Ǹ������
		sld.w	pt_r31[ep], r31			-- lp(r31)
	.if 0
		sld.w	pt_eipc[ep], r10
		ldsr	r10, eipc				-- ����߻���������쥸����
	.endif
	.if 0
		sld.w	pt_eipsw[ep], r10
		ldsr	r10, eipsw				-- ����߻���������쥸����
	.endif
	.if 0
		sld.w	pt_fepc[ep], r10
		ldsr	r10, fepc				-- NMI �����������쥸����
	.endif
	.if 0
		sld.w	pt_fepsw[ep], r10
		ldsr	r10, fepsw				-- NMI �����������쥸����
	.endif
	.if 0
		sld.w	pt_ecr[ep], r10
		ldsr	r10, ecr				-- ������װ��쥸����
	.endif
		sld.w	pt_ctpc[ep], r10
		ldsr	r10, ctpc				-- CALLT�¹Ի���������쥸����
		sld.w	pt_ctpsw[ep], r10
		ldsr	r10, ctpsw				-- CALLT�¹Ի���������쥸����
	.if 0
		sld.w	pt_ctbp[ep], r10
		ldsr	r10, ctbp				-- CALLT�١����ݥ���
	.endif
	.if 0
		sld.w	pt_psw[ep], r10
		ldsr	r10, psw				-- �ץ�����ॹ�ơ��ȥ��
	.endif
		sld.w	pt_r10[ep], r10			-- r10 ��Ǹ������
		sld.w	pt_r30[ep], r30			-- ep(r30) ��Ǹ�˹���
.endm
#	------------------------------------------------------------------------
#		Copyright (C) 1998-2008 by Project HOS
#	------------------------------------------------------------------------