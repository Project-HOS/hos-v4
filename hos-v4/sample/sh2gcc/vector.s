/* ------------------------------------------------------------------------ */
/*  HOS-V4 サンプルプログラム                                               */
/*    割り込みベクタテーブル (日立 SH2 gcc 用)                              */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



				.section	.vector

				.long	_pwr_reset			/* パワーオンリセット */
				.long	_STACK_END
				.long	_man_reset			/* マニュアルリセット */
				.long	_STACK_END
				.long	_hos_vecter004
				.long	_hos_vecter005
				.long	_hos_vecter006
				.long	_hos_vecter007
				.long	_hos_vecter008
				.long	_hos_vecter009
				.long	_hos_vecter010
				.long	_hos_vecter011
				.long	_hos_vecter012
				.long	_hos_vecter013
				.long	_hos_vecter014
				.long	_hos_vecter015
				.long	_hos_vecter016
				.long	_hos_vecter017
				.long	_hos_vecter018
				.long	_hos_vecter019
				.long	_hos_vecter020
				.long	_hos_vecter021
				.long	_hos_vecter022
				.long	_hos_vecter023
				.long	_hos_vecter024
				.long	_hos_vecter025
				.long	_hos_vecter026
				.long	_hos_vecter027
				.long	_hos_vecter028
				.long	_hos_vecter029
				.long	_hos_vecter030
				.long	_hos_vecter031
				.long	_hos_vecter032
				.long	_hos_vecter033
				.long	_hos_vecter034
				.long	_hos_vecter035
				.long	_hos_vecter036
				.long	_hos_vecter037
				.long	_hos_vecter038
				.long	_hos_vecter039
				.long	_hos_vecter040
				.long	_hos_vecter041
				.long	_hos_vecter042
				.long	_hos_vecter043
				.long	_hos_vecter044
				.long	_hos_vecter045
				.long	_hos_vecter046
				.long	_hos_vecter047
				.long	_hos_vecter048
				.long	_hos_vecter049
				.long	_hos_vecter050
				.long	_hos_vecter051
				.long	_hos_vecter052
				.long	_hos_vecter053
				.long	_hos_vecter054
				.long	_hos_vecter055
				.long	_hos_vecter056
				.long	_hos_vecter057
				.long	_hos_vecter058
				.long	_hos_vecter059
				.long	_hos_vecter060
				.long	_hos_vecter061
				.long	_hos_vecter062
				.long	_hos_vecter063
				.long	_hos_vecter064
				.long	_hos_vecter065
				.long	_hos_vecter066
				.long	_hos_vecter067
				.long	_hos_vecter068
				.long	_hos_vecter069
				.long	_hos_vecter070
				.long	_hos_vecter071
				.long	_hos_vecter072
				.long	_hos_vecter073
				.long	_hos_vecter074
				.long	_hos_vecter075
				.long	_hos_vecter076
				.long	_hos_vecter077
				.long	_hos_vecter078
				.long	_hos_vecter079
				.long	_hos_vecter080
				.long	_hos_vecter081
				.long	_hos_vecter082
				.long	_hos_vecter083
				.long	_hos_vecter084
				.long	_hos_vecter085
				.long	_hos_vecter086
				.long	_hos_vecter087
				.long	_hos_vecter088
				.long	_hos_vecter089
				.long	_hos_vecter090
				.long	_hos_vecter091
				.long	_hos_vecter092
				.long	_hos_vecter093
				.long	_hos_vecter094
				.long	_hos_vecter095
				.long	_hos_vecter096
				.long	_hos_vecter097
				.long	_hos_vecter098
				.long	_hos_vecter099
				.long	_hos_vecter100
				.long	_hos_vecter101
				.long	_hos_vecter102
				.long	_hos_vecter103
				.long	_hos_vecter104
				.long	_hos_vecter105
				.long	_hos_vecter106
				.long	_hos_vecter107
				.long	_hos_vecter108
				.long	_hos_vecter109
				.long	_hos_vecter110
				.long	_hos_vecter111
				.long	_hos_vecter112
				.long	_hos_vecter113
				.long	_hos_vecter114
				.long	_hos_vecter115
				.long	_hos_vecter116
				.long	_hos_vecter117
				.long	_hos_vecter118
				.long	_hos_vecter119
				.long	_hos_vecter120
				.long	_hos_vecter121
				.long	_hos_vecter122
				.long	_hos_vecter123
				.long	_hos_vecter124
				.long	_hos_vecter125
				.long	_hos_vecter126
				.long	_hos_vecter127
				.long	_hos_vecter128
				.long	_hos_vecter129
				.long	_hos_vecter130
				.long	_hos_vecter131
				.long	_hos_vecter132
				.long	_hos_vecter133
				.long	_hos_vecter134
				.long	_hos_vecter135
				.long	_hos_vecter136
				.long	_hos_vecter137
				.long	_hos_vecter138
				.long	_hos_vecter139
				.long	_hos_vecter140
				.long	_hos_vecter141
				.long	_hos_vecter142
				.long	_hos_vecter143
				.long	_hos_vecter144
/*				.long	_Cmt0_Handler */
				.long	_hos_vecter145
				.long	_hos_vecter146
				.long	_hos_vecter147
				.long	_hos_vecter148
				.long	_hos_vecter149
				.long	_hos_vecter150
				.long	_hos_vecter151
				.long	_hos_vecter152
				.long	_hos_vecter153
				.long	_hos_vecter154
				.long	_hos_vecter155
				.long	_hos_vecter156



				.end



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
