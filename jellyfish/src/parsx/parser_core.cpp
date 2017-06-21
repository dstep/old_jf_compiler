parsx_symbol_state(298,FunctionBody,FunctionBody*);
parsx_symbol_state(405,SrcMarker,SrcLoc);
parsx_symbol_state(22,Stmts,List<Stmt>);
parsx_symbol_state(45,Expr,Expr*);
parsx_symbol_state(53,Type,Type*);
parsx_symbol_state(445,TypeUnion,List<TypeList>);
parsx_symbol_state(401,TypePrim,Type*);
parsx_symbol_state(289,TypeReference,WithSrcLoc<TypeReferenceNode*>);
parsx_symbol_state(75,TypeList,List<TypeList>);
parsx_symbol_state(321,TypeList2,List<TypeList>);
parsx_symbol_state(283,ExprList,List<ExprList>);
parsx_symbol_state(99,ElseExpr,Expr*);
parsx_symbol_state(314,ExprCases,List< MatchCase<Expr> >);
parsx_symbol_state(318,ExprCase,MatchCase<Expr>*);
parsx_symbol_state(140,PatternList,List<Pattern>);
parsx_symbol_state(327,PatternList1,List<Pattern>);
parsx_symbol_state(450,Pattern,Pattern*);
parsx_symbol_state(444,QualID2,QualID*);
parsx_symbol_state(202,MPattern6,Pattern*);
parsx_symbol_state(458,EnumCons,EnumConstructorNumber);
parsx_symbol_state(100,CountVBars1,int);
parsx_symbol_state(243,CountVBars,int);
parsx_symbol_state(145,ExprCaseBranches,MatchBranch<Expr>*);
parsx_symbol_state(14,ExprCaseElseBranches,MatchBranch<Expr>*);
parsx_symbol_state(25,ExprPrim,Expr*);
parsx_symbol_state(46,QualID,QualID*);
parsx_symbol_state(207,ConstructorStringFromQualID,List<ConstructorStringPart>);
parsx_symbol_state(241,FunctionSignature,FunctionSignature*);
parsx_symbol_state(64,ParamGroups,List<ParamGroup>);
parsx_symbol_state(69,ParamGroup,ParamGroup*);
parsx_symbol_state(72,Names,List<Name>);
parsx_symbol_state(252,MTypeBinder,Type*);
parsx_symbol_state(62,LambdaBody,FunctionBody*);
parsx_symbol_state(379,ElseStmt,List<Stmt>);
parsx_symbol_state(392,Initializer,Expr*);
parsx_symbol_state(2,MInitializer,Expr*);
parsx_symbol_state(84,StmtCases,List< MatchCase<Stmt> >);
parsx_symbol_state(18,StmtCase,MatchCase<Stmt>*);
parsx_symbol_state(21,StmtCaseBranches,MatchBranch<Stmt>*);
parsx_symbol_state(112,StmtCaseElseBranches,MatchBranch<Stmt>*);
parsx_symbol_state(36,ConstructorString,List<ConstructorStringPart>);
parsx_symbol_state(153,AssignPairs,List<AssignPair>);
parsx_symbol_state(293,ClassMember,ClassMember*);
parsx_symbol_state(232,TypeBinding,Type*);
parsx_symbol_state(342,WithClause,QualID*);
parsx_symbol_state(198,FunctionSignatureNoRV,FunctionSignature*);
parsx_symbol_state(395,TopLevel,TopLevel*);
parsx_symbol_state(219,EnumConstructors,List<EnumConstructor>);
parsx_symbol_state(223,EnumConstructor,EnumConstructor*);
parsx_symbol_state(404,InterfaceExtends,List<Implements>);
parsx_symbol_state(406,InterfaceMethods,List<InterfaceMethod>);
parsx_symbol_state(417,Extends,Extends*);
parsx_symbol_state(210,Implements,List<Implements>);
parsx_symbol_state(426,ClassMembers,List<ClassMember>);
parsx_symbol_state(262,StructFields,List<StructField>);
parsx_symbol_state(439,StructField,StructField*);
parsx_symbol_state(209,Import,Import*);
parsx_symbol_state(449,ImportAs,StringRef);
parsx_symbol_state(447,Imports,List<Import>);
parsx_symbol_state(455,Module,Module*);
parsx_symbol_state(461,TopLevels,List<TopLevel>);
#if defined(parsx_impl)
	short parsx_table[parsx_max_token_id + 3][471] = {0};
	const unsigned char parsx_sync_cost_table[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
	};
	struct parsx_parse_table_gen{parsx_parse_table_gen(){
		parsx_table[parsx_max_token_id + 1][1] = 1;
		parsx_table[parsx_max_token_id + 1][2] = 2;
		parsx_table[parsx_max_token_id + 1][3] = 3;
		parsx_table[parsx_max_token_id + 1][4] = 4;
		parsx_table[parsx_max_token_id + 1][5] = 5;
		parsx_table[parsx_max_token_id + 1][6] = 6;
		parsx_table[parsx_max_token_id + 1][7] = 7;
		parsx_table[parsx_max_token_id + 1][8] = 8;
		parsx_table[parsx_max_token_id + 1][9] = 9;
		parsx_table[parsx_max_token_id + 1][10] = 10;
		parsx_table[parsx_max_token_id + 1][11] = 11;
		parsx_table[parsx_max_token_id + 1][12] = 12;
		parsx_table[parsx_max_token_id + 1][13] = 13;
		parsx_table[parsx_max_token_id + 1][14] = 14;
		parsx_table[parsx_max_token_id + 1][15] = 15;
		parsx_table[parsx_max_token_id + 1][16] = 16;
		parsx_table[parsx_max_token_id + 1][17] = 17;
		parsx_table[parsx_max_token_id + 1][19] = 18;
		parsx_table[parsx_max_token_id + 1][20] = 19;
		parsx_table[parsx_max_token_id + 1][22] = 20;
		parsx_table[parsx_max_token_id + 1][23] = 21;
		parsx_table[parsx_max_token_id + 1][24] = 22;
		parsx_table[parsx_max_token_id + 1][26] = 23;
		parsx_table[parsx_max_token_id + 1][27] = 24;
		parsx_table[parsx_max_token_id + 1][28] = 25;
		parsx_table[parsx_max_token_id + 1][29] = 26;
		parsx_table[parsx_max_token_id + 1][30] = 27;
		parsx_table[parsx_max_token_id + 1][31] = 28;
		parsx_table[parsx_max_token_id + 1][32] = 29;
		parsx_table[parsx_max_token_id + 1][33] = 30;
		parsx_table[parsx_max_token_id + 1][34] = 31;
		parsx_table[parsx_max_token_id + 1][35] = 32;
		parsx_table[parsx_max_token_id + 1][36] = 33;
		parsx_table[parsx_max_token_id + 1][37] = 34;
		parsx_table[parsx_max_token_id + 1][38] = 35;
		parsx_table[parsx_max_token_id + 1][39] = 36;
		parsx_table[parsx_max_token_id + 1][40] = 37;
		parsx_table[parsx_max_token_id + 1][41] = 38;
		parsx_table[parsx_max_token_id + 1][42] = 39;
		parsx_table[parsx_max_token_id + 1][43] = 40;
		parsx_table[parsx_max_token_id + 1][44] = 41;
		parsx_table[parsx_max_token_id + 1][48] = 42;
		parsx_table[parsx_max_token_id + 1][49] = 43;
		parsx_table[parsx_max_token_id + 1][50] = 44;
		parsx_table[parsx_max_token_id + 1][51] = 45;
		parsx_table[parsx_max_token_id + 1][52] = 46;
		parsx_table[parsx_max_token_id + 1][54] = 47;
		parsx_table[parsx_max_token_id + 1][56] = 48;
		parsx_table[parsx_max_token_id + 1][57] = 49;
		parsx_table[parsx_max_token_id + 1][58] = 50;
		parsx_table[parsx_max_token_id + 1][59] = 51;
		parsx_table[parsx_max_token_id + 1][60] = 52;
		parsx_table[parsx_max_token_id + 1][61] = 53;
		parsx_table[parsx_max_token_id + 1][64] = 54;
		parsx_table[parsx_max_token_id + 1][65] = 55;
		parsx_table[parsx_max_token_id + 1][66] = 56;
		parsx_table[parsx_max_token_id + 1][67] = 57;
		parsx_table[parsx_max_token_id + 1][68] = 58;
		parsx_table[parsx_max_token_id + 1][70] = 59;
		parsx_table[parsx_max_token_id + 1][71] = 60;
		parsx_table[parsx_max_token_id + 1][73] = 61;
		parsx_table[parsx_max_token_id + 1][74] = 62;
		parsx_table[parsx_max_token_id + 1][75] = 63;
		parsx_table[parsx_max_token_id + 1][82] = 64;
		parsx_table[parsx_max_token_id + 1][83] = 65;
		parsx_table[parsx_max_token_id + 1][84] = 66;
		parsx_table[parsx_max_token_id + 1][91] = 67;
		parsx_table[parsx_max_token_id + 1][94] = 68;
		parsx_table[parsx_max_token_id + 1][95] = 69;
		parsx_table[parsx_max_token_id + 1][96] = 70;
		parsx_table[parsx_max_token_id + 1][97] = 71;
		parsx_table[parsx_max_token_id + 1][98] = 72;
		parsx_table[parsx_max_token_id + 1][101] = 73;
		parsx_table[parsx_max_token_id + 1][102] = 74;
		parsx_table[parsx_max_token_id + 1][103] = 75;
		parsx_table[parsx_max_token_id + 1][104] = 76;
		parsx_table[parsx_max_token_id + 1][105] = 77;
		parsx_table[parsx_max_token_id + 1][106] = 78;
		parsx_table[parsx_max_token_id + 1][107] = 79;
		parsx_table[parsx_max_token_id + 1][108] = 80;
		parsx_table[parsx_max_token_id + 1][109] = 81;
		parsx_table[parsx_max_token_id + 1][110] = 82;
		parsx_table[parsx_max_token_id + 1][111] = 83;
		parsx_table[parsx_max_token_id + 1][112] = 84;
		parsx_table[parsx_max_token_id + 1][113] = 85;
		parsx_table[parsx_max_token_id + 1][114] = 86;
		parsx_table[parsx_max_token_id + 1][115] = 87;
		parsx_table[parsx_max_token_id + 1][116] = 88;
		parsx_table[parsx_max_token_id + 1][117] = 89;
		parsx_table[parsx_max_token_id + 1][118] = 90;
		parsx_table[parsx_max_token_id + 1][119] = 91;
		parsx_table[parsx_max_token_id + 1][120] = 92;
		parsx_table[parsx_max_token_id + 1][121] = 93;
		parsx_table[parsx_max_token_id + 1][122] = 94;
		parsx_table[parsx_max_token_id + 1][123] = 95;
		parsx_table[parsx_max_token_id + 1][124] = 96;
		parsx_table[parsx_max_token_id + 1][125] = 97;
		parsx_table[parsx_max_token_id + 1][126] = 98;
		parsx_table[parsx_max_token_id + 1][127] = 99;
		parsx_table[parsx_max_token_id + 1][128] = 100;
		parsx_table[parsx_max_token_id + 1][129] = 101;
		parsx_table[parsx_max_token_id + 1][130] = 102;
		parsx_table[parsx_max_token_id + 1][131] = 103;
		parsx_table[parsx_max_token_id + 1][132] = 104;
		parsx_table[parsx_max_token_id + 1][133] = 105;
		parsx_table[parsx_max_token_id + 1][134] = 106;
		parsx_table[parsx_max_token_id + 1][135] = 107;
		parsx_table[parsx_max_token_id + 1][136] = 108;
		parsx_table[parsx_max_token_id + 1][137] = 109;
		parsx_table[parsx_max_token_id + 1][138] = 110;
		parsx_table[parsx_max_token_id + 1][139] = 111;
		parsx_table[parsx_max_token_id + 1][140] = 112;
		parsx_table[parsx_max_token_id + 1][141] = 113;
		parsx_table[parsx_max_token_id + 1][142] = 114;
		parsx_table[parsx_max_token_id + 1][144] = 115;
		parsx_table[parsx_max_token_id + 1][147] = 116;
		parsx_table[parsx_max_token_id + 1][149] = 117;
		parsx_table[parsx_max_token_id + 1][150] = 118;
		parsx_table[parsx_max_token_id + 1][152] = 119;
		parsx_table[parsx_max_token_id + 1][153] = 120;
		parsx_table[parsx_max_token_id + 1][155] = 121;
		parsx_table[parsx_max_token_id + 1][156] = 122;
		parsx_table[parsx_max_token_id + 1][157] = 123;
		parsx_table[parsx_max_token_id + 1][159] = 124;
		parsx_table[parsx_max_token_id + 1][160] = 125;
		parsx_table[parsx_max_token_id + 1][161] = 126;
		parsx_table[parsx_max_token_id + 1][163] = 127;
		parsx_table[parsx_max_token_id + 1][164] = 128;
		parsx_table[parsx_max_token_id + 1][165] = 129;
		parsx_table[parsx_max_token_id + 1][166] = 130;
		parsx_table[parsx_max_token_id + 1][168] = 131;
		parsx_table[parsx_max_token_id + 1][169] = 132;
		parsx_table[parsx_max_token_id + 1][170] = 133;
		parsx_table[parsx_max_token_id + 1][171] = 134;
		parsx_table[parsx_max_token_id + 1][173] = 135;
		parsx_table[parsx_max_token_id + 1][174] = 136;
		parsx_table[parsx_max_token_id + 1][175] = 137;
		parsx_table[parsx_max_token_id + 1][176] = 138;
		parsx_table[parsx_max_token_id + 1][177] = 139;
		parsx_table[parsx_max_token_id + 1][178] = 140;
		parsx_table[parsx_max_token_id + 1][179] = 141;
		parsx_table[parsx_max_token_id + 1][180] = 142;
		parsx_table[parsx_max_token_id + 1][181] = 143;
		parsx_table[parsx_max_token_id + 1][182] = 144;
		parsx_table[parsx_max_token_id + 1][183] = 145;
		parsx_table[parsx_max_token_id + 1][184] = 146;
		parsx_table[parsx_max_token_id + 1][186] = 147;
		parsx_table[parsx_max_token_id + 1][187] = 148;
		parsx_table[parsx_max_token_id + 1][188] = 149;
		parsx_table[parsx_max_token_id + 1][190] = 150;
		parsx_table[parsx_max_token_id + 1][191] = 151;
		parsx_table[parsx_max_token_id + 1][192] = 152;
		parsx_table[parsx_max_token_id + 1][193] = 153;
		parsx_table[parsx_max_token_id + 1][194] = 154;
		parsx_table[parsx_max_token_id + 1][195] = 155;
		parsx_table[parsx_max_token_id + 1][196] = 156;
		parsx_table[parsx_max_token_id + 1][197] = 157;
		parsx_table[parsx_max_token_id + 1][199] = 158;
		parsx_table[parsx_max_token_id + 1][200] = 159;
		parsx_table[parsx_max_token_id + 1][201] = 160;
		parsx_table[parsx_max_token_id + 1][202] = 161;
		parsx_table[parsx_max_token_id + 1][203] = 162;
		parsx_table[parsx_max_token_id + 1][204] = 163;
		parsx_table[parsx_max_token_id + 1][205] = 164;
		parsx_table[parsx_max_token_id + 1][206] = 165;
		parsx_table[parsx_max_token_id + 1][208] = 166;
		parsx_table[parsx_max_token_id + 1][210] = 167;
		parsx_table[parsx_max_token_id + 1][211] = 168;
		parsx_table[parsx_max_token_id + 1][212] = 169;
		parsx_table[parsx_max_token_id + 1][213] = 170;
		parsx_table[parsx_max_token_id + 1][214] = 171;
		parsx_table[parsx_max_token_id + 1][215] = 172;
		parsx_table[parsx_max_token_id + 1][216] = 173;
		parsx_table[parsx_max_token_id + 1][217] = 174;
		parsx_table[parsx_max_token_id + 1][218] = 175;
		parsx_table[parsx_max_token_id + 1][219] = 176;
		parsx_table[parsx_max_token_id + 1][220] = 177;
		parsx_table[parsx_max_token_id + 1][221] = 178;
		parsx_table[parsx_max_token_id + 1][222] = 179;
		parsx_table[parsx_max_token_id + 1][224] = 180;
		parsx_table[parsx_max_token_id + 1][225] = 181;
		parsx_table[parsx_max_token_id + 1][226] = 182;
		parsx_table[parsx_max_token_id + 1][227] = 183;
		parsx_table[parsx_max_token_id + 1][228] = 184;
		parsx_table[parsx_max_token_id + 1][229] = 185;
		parsx_table[parsx_max_token_id + 1][231] = 186;
		parsx_table[parsx_max_token_id + 1][233] = 187;
		parsx_table[parsx_max_token_id + 1][234] = 188;
		parsx_table[parsx_max_token_id + 1][235] = 189;
		parsx_table[parsx_max_token_id + 1][237] = 190;
		parsx_table[parsx_max_token_id + 1][238] = 191;
		parsx_table[parsx_max_token_id + 1][239] = 192;
		parsx_table[parsx_max_token_id + 1][240] = 193;
		parsx_table[parsx_max_token_id + 1][242] = 194;
		parsx_table[parsx_max_token_id + 1][243] = 195;
		parsx_table[parsx_max_token_id + 1][244] = 196;
		parsx_table[parsx_max_token_id + 1][245] = 197;
		parsx_table[parsx_max_token_id + 1][246] = 198;
		parsx_table[parsx_max_token_id + 1][247] = 199;
		parsx_table[parsx_max_token_id + 1][248] = 200;
		parsx_table[parsx_max_token_id + 1][250] = 201;
		parsx_table[parsx_max_token_id + 1][252] = 202;
		parsx_table[parsx_max_token_id + 1][253] = 203;
		parsx_table[parsx_max_token_id + 1][255] = 204;
		parsx_table[parsx_max_token_id + 1][256] = 205;
		parsx_table[parsx_max_token_id + 1][257] = 206;
		parsx_table[parsx_max_token_id + 1][258] = 207;
		parsx_table[parsx_max_token_id + 1][259] = 208;
		parsx_table[parsx_max_token_id + 1][260] = 209;
		parsx_table[parsx_max_token_id + 1][262] = 210;
		parsx_table[parsx_max_token_id + 1][263] = 211;
		parsx_table[parsx_max_token_id + 1][264] = 212;
		parsx_table[parsx_max_token_id + 1][265] = 213;
		parsx_table[parsx_max_token_id + 1][267] = 214;
		parsx_table[parsx_max_token_id + 1][268] = 215;
		parsx_table[parsx_max_token_id + 1][270] = 216;
		parsx_table[parsx_max_token_id + 1][271] = 217;
		parsx_table[parsx_max_token_id + 1][272] = 218;
		parsx_table[parsx_max_token_id + 1][273] = 219;
		parsx_table[parsx_max_token_id + 1][274] = 220;
		parsx_table[parsx_max_token_id + 1][275] = 221;
		parsx_table[parsx_max_token_id + 1][276] = 222;
		parsx_table[parsx_max_token_id + 1][277] = 223;
		parsx_table[parsx_max_token_id + 1][278] = 224;
		parsx_table[parsx_max_token_id + 1][279] = 225;
		parsx_table[parsx_max_token_id + 1][280] = 226;
		parsx_table[parsx_max_token_id + 1][281] = 227;
		parsx_table[parsx_max_token_id + 1][282] = 228;
		parsx_table[parsx_max_token_id + 1][283] = 229;
		parsx_table[parsx_max_token_id + 1][284] = 230;
		parsx_table[parsx_max_token_id + 1][285] = 231;
		parsx_table[parsx_max_token_id + 1][286] = 232;
		parsx_table[parsx_max_token_id + 1][287] = 233;
		parsx_table[parsx_max_token_id + 1][288] = 234;
		parsx_table[parsx_max_token_id + 1][290] = 235;
		parsx_table[parsx_max_token_id + 1][291] = 236;
		parsx_table[parsx_max_token_id + 1][292] = 237;
		parsx_table[parsx_max_token_id + 1][294] = 238;
		parsx_table[parsx_max_token_id + 1][295] = 239;
		parsx_table[parsx_max_token_id + 1][296] = 240;
		parsx_table[parsx_max_token_id + 1][297] = 241;
		parsx_table[parsx_max_token_id + 1][299] = 242;
		parsx_table[parsx_max_token_id + 1][300] = 243;
		parsx_table[parsx_max_token_id + 1][301] = 244;
		parsx_table[parsx_max_token_id + 1][302] = 245;
		parsx_table[parsx_max_token_id + 1][303] = 246;
		parsx_table[parsx_max_token_id + 1][304] = 247;
		parsx_table[parsx_max_token_id + 1][305] = 248;
		parsx_table[parsx_max_token_id + 1][306] = 249;
		parsx_table[parsx_max_token_id + 1][307] = 250;
		parsx_table[parsx_max_token_id + 1][308] = 251;
		parsx_table[parsx_max_token_id + 1][309] = 252;
		parsx_table[parsx_max_token_id + 1][310] = 253;
		parsx_table[parsx_max_token_id + 1][311] = 254;
		parsx_table[parsx_max_token_id + 1][312] = 255;
		parsx_table[parsx_max_token_id + 1][313] = 256;
		parsx_table[parsx_max_token_id + 1][314] = 257;
		parsx_table[parsx_max_token_id + 1][315] = 258;
		parsx_table[parsx_max_token_id + 1][316] = 259;
		parsx_table[parsx_max_token_id + 1][317] = 260;
		parsx_table[parsx_max_token_id + 1][319] = 261;
		parsx_table[parsx_max_token_id + 1][320] = 262;
		parsx_table[parsx_max_token_id + 1][322] = 263;
		parsx_table[parsx_max_token_id + 1][323] = 264;
		parsx_table[parsx_max_token_id + 1][324] = 265;
		parsx_table[parsx_max_token_id + 1][325] = 266;
		parsx_table[parsx_max_token_id + 1][326] = 267;
		parsx_table[parsx_max_token_id + 1][328] = 268;
		parsx_table[parsx_max_token_id + 1][329] = 269;
		parsx_table[parsx_max_token_id + 1][331] = 270;
		parsx_table[parsx_max_token_id + 1][332] = 271;
		parsx_table[parsx_max_token_id + 1][333] = 272;
		parsx_table[parsx_max_token_id + 1][334] = 273;
		parsx_table[parsx_max_token_id + 1][335] = 274;
		parsx_table[parsx_max_token_id + 1][336] = 275;
		parsx_table[parsx_max_token_id + 1][337] = 276;
		parsx_table[parsx_max_token_id + 1][338] = 277;
		parsx_table[parsx_max_token_id + 1][339] = 278;
		parsx_table[parsx_max_token_id + 1][340] = 279;
		parsx_table[parsx_max_token_id + 1][341] = 280;
		parsx_table[parsx_max_token_id + 1][342] = 281;
		parsx_table[parsx_max_token_id + 1][343] = 282;
		parsx_table[parsx_max_token_id + 1][344] = 283;
		parsx_table[parsx_max_token_id + 1][345] = 284;
		parsx_table[parsx_max_token_id + 1][346] = 285;
		parsx_table[parsx_max_token_id + 1][347] = 286;
		parsx_table[parsx_max_token_id + 1][348] = 287;
		parsx_table[parsx_max_token_id + 1][349] = 288;
		parsx_table[parsx_max_token_id + 1][350] = 289;
		parsx_table[parsx_max_token_id + 1][351] = 290;
		parsx_table[parsx_max_token_id + 1][352] = 291;
		parsx_table[parsx_max_token_id + 1][353] = 292;
		parsx_table[parsx_max_token_id + 1][354] = 293;
		parsx_table[parsx_max_token_id + 1][355] = 294;
		parsx_table[parsx_max_token_id + 1][357] = 295;
		parsx_table[parsx_max_token_id + 1][358] = 296;
		parsx_table[parsx_max_token_id + 1][359] = 297;
		parsx_table[parsx_max_token_id + 1][360] = 298;
		parsx_table[parsx_max_token_id + 1][361] = 299;
		parsx_table[parsx_max_token_id + 1][362] = 300;
		parsx_table[parsx_max_token_id + 1][363] = 301;
		parsx_table[parsx_max_token_id + 1][364] = 302;
		parsx_table[parsx_max_token_id + 1][365] = 303;
		parsx_table[parsx_max_token_id + 1][368] = 304;
		parsx_table[parsx_max_token_id + 1][369] = 305;
		parsx_table[parsx_max_token_id + 1][370] = 306;
		parsx_table[parsx_max_token_id + 1][371] = 307;
		parsx_table[parsx_max_token_id + 1][372] = 308;
		parsx_table[parsx_max_token_id + 1][376] = 309;
		parsx_table[parsx_max_token_id + 1][377] = 310;
		parsx_table[parsx_max_token_id + 1][378] = 311;
		parsx_table[parsx_max_token_id + 1][380] = 312;
		parsx_table[parsx_max_token_id + 1][381] = 313;
		parsx_table[parsx_max_token_id + 1][382] = 314;
		parsx_table[parsx_max_token_id + 1][384] = 315;
		parsx_table[parsx_max_token_id + 1][385] = 316;
		parsx_table[parsx_max_token_id + 1][386] = 317;
		parsx_table[parsx_max_token_id + 1][387] = 318;
		parsx_table[parsx_max_token_id + 1][388] = 319;
		parsx_table[parsx_max_token_id + 1][389] = 320;
		parsx_table[parsx_max_token_id + 1][390] = 321;
		parsx_table[parsx_max_token_id + 1][391] = 322;
		parsx_table[parsx_max_token_id + 1][393] = 323;
		parsx_table[parsx_max_token_id + 1][394] = 324;
		parsx_table[parsx_max_token_id + 1][396] = 325;
		parsx_table[parsx_max_token_id + 1][397] = 326;
		parsx_table[parsx_max_token_id + 1][398] = 327;
		parsx_table[parsx_max_token_id + 1][399] = 328;
		parsx_table[parsx_max_token_id + 1][400] = 329;
		parsx_table[parsx_max_token_id + 1][402] = 330;
		parsx_table[parsx_max_token_id + 1][403] = 331;
		parsx_table[parsx_max_token_id + 1][404] = 332;
		parsx_table[parsx_max_token_id + 1][405] = 333;
		parsx_table[parsx_max_token_id + 1][406] = 334;
		parsx_table[parsx_max_token_id + 1][407] = 335;
		parsx_table[parsx_max_token_id + 1][408] = 336;
		parsx_table[parsx_max_token_id + 1][409] = 337;
		parsx_table[parsx_max_token_id + 1][410] = 338;
		parsx_table[parsx_max_token_id + 1][411] = 339;
		parsx_table[parsx_max_token_id + 1][412] = 340;
		parsx_table[parsx_max_token_id + 1][413] = 341;
		parsx_table[parsx_max_token_id + 1][414] = 342;
		parsx_table[parsx_max_token_id + 1][415] = 343;
		parsx_table[parsx_max_token_id + 1][417] = 344;
		parsx_table[parsx_max_token_id + 1][418] = 345;
		parsx_table[parsx_max_token_id + 1][419] = 346;
		parsx_table[parsx_max_token_id + 1][420] = 347;
		parsx_table[parsx_max_token_id + 1][421] = 348;
		parsx_table[parsx_max_token_id + 1][422] = 349;
		parsx_table[parsx_max_token_id + 1][423] = 350;
		parsx_table[parsx_max_token_id + 1][424] = 351;
		parsx_table[parsx_max_token_id + 1][425] = 352;
		parsx_table[parsx_max_token_id + 1][426] = 353;
		parsx_table[parsx_max_token_id + 1][427] = 354;
		parsx_table[parsx_max_token_id + 1][428] = 355;
		parsx_table[parsx_max_token_id + 1][429] = 356;
		parsx_table[parsx_max_token_id + 1][430] = 357;
		parsx_table[parsx_max_token_id + 1][431] = 358;
		parsx_table[parsx_max_token_id + 1][433] = 359;
		parsx_table[parsx_max_token_id + 1][434] = 360;
		parsx_table[parsx_max_token_id + 1][435] = 361;
		parsx_table[parsx_max_token_id + 1][436] = 362;
		parsx_table[parsx_max_token_id + 1][437] = 363;
		parsx_table[parsx_max_token_id + 1][438] = 364;
		parsx_table[parsx_max_token_id + 1][440] = 365;
		parsx_table[parsx_max_token_id + 1][441] = 366;
		parsx_table[parsx_max_token_id + 1][442] = 367;
		parsx_table[parsx_max_token_id + 1][443] = 368;
		parsx_table[parsx_max_token_id + 1][446] = 369;
		parsx_table[parsx_max_token_id + 1][447] = 370;
		parsx_table[parsx_max_token_id + 1][448] = 371;
		parsx_table[parsx_max_token_id + 1][449] = 372;
		parsx_table[parsx_max_token_id + 1][451] = 373;
		parsx_table[parsx_max_token_id + 1][453] = 374;
		parsx_table[parsx_max_token_id + 1][454] = 375;
		parsx_table[parsx_max_token_id + 1][456] = 376;
		parsx_table[parsx_max_token_id + 1][457] = 377;
		parsx_table[parsx_max_token_id + 1][459] = 378;
		parsx_table[parsx_max_token_id + 1][460] = 379;
		parsx_table[parsx_max_token_id + 1][461] = 380;
		parsx_table[parsx_max_token_id + 1][462] = 381;
		parsx_table[parsx_max_token_id + 1][464] = 382;
		parsx_table[parsx_max_token_id + 1][465] = 383;
		parsx_table[parsx_max_token_id + 1][466] = 384;
		parsx_table[parsx_max_token_id + 1][467] = 385;
		parsx_table[parsx_max_token_id + 1][468] = 386;
		parsx_table[parsx_max_token_id + 1][469] = 387;
		parsx_table[parsx_max_token_id + 1][470] = 388;
		parsx_table[parsx_max_token_id + 1][471] = 389;
		parsx_table[parsx_token(OAssign)][2] = 390;
		parsx_table[parsx_token(KAnd)][5] = 391;
		parsx_table[parsx_token(OConcat)][5] = 392;
		parsx_table[parsx_token(OLT)][5] = 393;
		parsx_table[parsx_token(KOr)][5] = 394;
		parsx_table[parsx_token(OGT)][5] = 395;
		parsx_table[parsx_token(OLE)][5] = 396;
		parsx_table[parsx_token(OGE)][5] = 397;
		parsx_table[parsx_token(OEQ)][5] = 398;
		parsx_table[parsx_token(OColon)][5] = 399;
		parsx_table[parsx_token(ONE)][5] = 400;
		parsx_table[parsx_token(KOr)][10] = 401;
		parsx_table[parsx_token(KAnd)][10] = 402;
		parsx_table[parsx_token(OColon)][10] = 403;
		parsx_table[parsx_token(KElseIf)][14] = 404;
		parsx_table[parsx_token(KElse)][14] = 405;
		parsx_table[parsx_token(OLParen)][16] = 406;
		parsx_table[parsx_token(OPeriod)][16] = 407;
		parsx_table[parsx_token(KCase)][18] = 408;
		parsx_table[parsx_token(KIf)][21] = 409;
		parsx_table[parsx_token(KThen)][21] = 410;
		parsx_table[parsx_token(KNot)][22] = 411;
		parsx_table[parsx_token(KIf)][22] = 412;
		parsx_table[parsx_token(KConstruct)][22] = 413;
		parsx_table[parsx_token(OLParen)][22] = 414;
		parsx_table[parsx_token(OLBrace)][22] = 415;
		parsx_table[parsx_token(KFor)][22] = 416;
		parsx_table[parsx_token(KWhile)][22] = 417;
		parsx_table[parsx_token(KDo)][22] = 418;
		parsx_table[parsx_token(KVar)][22] = 419;
		parsx_table[parsx_token(KLet)][22] = 420;
		parsx_table[parsx_token(KReturn)][22] = 421;
		parsx_table[parsx_token(KEval)][22] = 422;
		parsx_table[parsx_token(KRaise)][22] = 423;
		parsx_table[parsx_token(OMinus)][22] = 424;
		parsx_table[parsx_token(KMatch)][22] = 425;
		parsx_table[parsx_token(KRepeat)][22] = 426;
		parsx_table[parsx_token(KLambda)][22] = 427;
		parsx_table[parsx_token(KNew)][22] = 428;
		parsx_table[parsx_token(KUnit)][22] = 429;
		parsx_table[parsx_token(KNull)][22] = 430;
		parsx_table[parsx_token(Identifier)][22] = 431;
		parsx_table[parsx_token(StringLiteral)][22] = 432;
		parsx_table[parsx_token(NumberLiteral)][22] = 433;
		parsx_table[parsx_token(KTrue)][22] = 434;
		parsx_table[parsx_token(KFalse)][22] = 435;
		parsx_table[parsx_token(OLBrace)][25] = 436;
		parsx_table[parsx_token(KNull)][25] = 437;
		parsx_table[parsx_token(Identifier)][25] = 438;
		parsx_table[parsx_token(KLambda)][25] = 439;
		parsx_table[parsx_token(StringLiteral)][25] = 440;
		parsx_table[parsx_token(KNew)][25] = 441;
		parsx_table[parsx_token(NumberLiteral)][25] = 442;
		parsx_table[parsx_token(KTrue)][25] = 443;
		parsx_table[parsx_token(KUnit)][25] = 444;
		parsx_table[parsx_token(KFalse)][25] = 445;
		parsx_table[parsx_token(OVBar)][27] = 446;
		parsx_table[parsx_token(OMinus)][32] = 447;
		parsx_table[parsx_token(OMult)][32] = 448;
		parsx_table[parsx_token(OConcat)][32] = 449;
		parsx_table[parsx_token(ODiv)][32] = 450;
		parsx_table[parsx_token(KOr)][32] = 451;
		parsx_table[parsx_token(ORem)][32] = 452;
		parsx_table[parsx_token(OLT)][32] = 453;
		parsx_table[parsx_token(OLE)][32] = 454;
		parsx_table[parsx_token(OGE)][32] = 455;
		parsx_table[parsx_token(OEQ)][32] = 456;
		parsx_table[parsx_token(OColon)][32] = 457;
		parsx_table[parsx_token(ONE)][32] = 458;
		parsx_table[parsx_token(KAnd)][32] = 459;
		parsx_table[parsx_token(OGT)][32] = 460;
		parsx_table[parsx_token(OPlus)][32] = 461;
		parsx_table[parsx_token(Identifier)][36] = 462;
		parsx_table[parsx_token(OPeriod)][36] = 463;
		parsx_table[parsx_token(KOr)][42] = 464;
		parsx_table[parsx_token(KAnd)][42] = 465;
		parsx_table[parsx_token(OColon)][42] = 466;
		parsx_table[parsx_token(OMinus)][45] = 467;
		parsx_table[parsx_token(KMatch)][45] = 468;
		parsx_table[parsx_token(KNull)][45] = 469;
		parsx_table[parsx_token(OLBrace)][45] = 470;
		parsx_table[parsx_token(KIf)][45] = 471;
		parsx_table[parsx_token(Identifier)][45] = 472;
		parsx_table[parsx_token(KLambda)][45] = 473;
		parsx_table[parsx_token(StringLiteral)][45] = 474;
		parsx_table[parsx_token(KNew)][45] = 475;
		parsx_table[parsx_token(OLParen)][45] = 476;
		parsx_table[parsx_token(NumberLiteral)][45] = 477;
		parsx_table[parsx_token(KTrue)][45] = 478;
		parsx_table[parsx_token(KUnit)][45] = 479;
		parsx_table[parsx_token(KNot)][45] = 480;
		parsx_table[parsx_token(KFalse)][45] = 481;
		parsx_table[parsx_token(Identifier)][46] = 482;
		parsx_table[parsx_token(KWith)][47] = 483;
		parsx_table[parsx_token(ORem)][50] = 484;
		parsx_table[parsx_token(OMult)][50] = 485;
		parsx_table[parsx_token(ODiv)][50] = 486;
		parsx_table[parsx_token(OLBrace)][53] = 487;
		parsx_table[parsx_token(KBool)][53] = 488;
		parsx_table[parsx_token(KInt)][53] = 489;
		parsx_table[parsx_token(KFloat)][53] = 490;
		parsx_table[parsx_token(KDouble)][53] = 491;
		parsx_table[parsx_token(Identifier)][53] = 492;
		parsx_table[parsx_token(KString)][53] = 493;
		parsx_table[parsx_token(KBytes)][53] = 494;
		parsx_table[parsx_token(OLParen)][53] = 495;
		parsx_table[parsx_token(KUnit)][53] = 496;
		parsx_table[parsx_token(KUndef)][53] = 497;
		parsx_table[parsx_token(OMinus)][55] = 498;
		parsx_table[parsx_token(KMatch)][55] = 499;
		parsx_table[parsx_token(KNull)][55] = 500;
		parsx_table[parsx_token(OLBrace)][55] = 501;
		parsx_table[parsx_token(KIf)][55] = 502;
		parsx_table[parsx_token(Identifier)][55] = 503;
		parsx_table[parsx_token(KLambda)][55] = 504;
		parsx_table[parsx_token(StringLiteral)][55] = 505;
		parsx_table[parsx_token(OComma)][55] = 506;
		parsx_table[parsx_token(KNew)][55] = 507;
		parsx_table[parsx_token(OLParen)][55] = 508;
		parsx_table[parsx_token(NumberLiteral)][55] = 509;
		parsx_table[parsx_token(KTrue)][55] = 510;
		parsx_table[parsx_token(KUnit)][55] = 511;
		parsx_table[parsx_token(KNot)][55] = 512;
		parsx_table[parsx_token(KFalse)][55] = 513;
		parsx_table[parsx_token(OPeriod)][61] = 514;
		parsx_table[parsx_token(OBigArrow)][62] = 515;
		parsx_table[parsx_token(KNot)][62] = 516;
		parsx_table[parsx_token(KIf)][62] = 517;
		parsx_table[parsx_token(KConstruct)][62] = 518;
		parsx_table[parsx_token(OLParen)][62] = 519;
		parsx_table[parsx_token(KEnd)][62] = 520;
		parsx_table[parsx_token(OLBrace)][62] = 521;
		parsx_table[parsx_token(KFor)][62] = 522;
		parsx_table[parsx_token(KWhile)][62] = 523;
		parsx_table[parsx_token(KDo)][62] = 524;
		parsx_table[parsx_token(KVar)][62] = 525;
		parsx_table[parsx_token(KLet)][62] = 526;
		parsx_table[parsx_token(KReturn)][62] = 527;
		parsx_table[parsx_token(KEval)][62] = 528;
		parsx_table[parsx_token(KRaise)][62] = 529;
		parsx_table[parsx_token(OMinus)][62] = 530;
		parsx_table[parsx_token(KMatch)][62] = 531;
		parsx_table[parsx_token(KRepeat)][62] = 532;
		parsx_table[parsx_token(KLambda)][62] = 533;
		parsx_table[parsx_token(KNew)][62] = 534;
		parsx_table[parsx_token(KUnit)][62] = 535;
		parsx_table[parsx_token(KNull)][62] = 536;
		parsx_table[parsx_token(Identifier)][62] = 537;
		parsx_table[parsx_token(StringLiteral)][62] = 538;
		parsx_table[parsx_token(NumberLiteral)][62] = 539;
		parsx_table[parsx_token(KTrue)][62] = 540;
		parsx_table[parsx_token(KFalse)][62] = 541;
		parsx_table[parsx_token(OLBrace)][63] = 542;
		parsx_table[parsx_token(KBool)][63] = 543;
		parsx_table[parsx_token(KInt)][63] = 544;
		parsx_table[parsx_token(KFloat)][63] = 545;
		parsx_table[parsx_token(KDouble)][63] = 546;
		parsx_table[parsx_token(Identifier)][63] = 547;
		parsx_table[parsx_token(KString)][63] = 548;
		parsx_table[parsx_token(KBytes)][63] = 549;
		parsx_table[parsx_token(OLParen)][63] = 550;
		parsx_table[parsx_token(KUnit)][63] = 551;
		parsx_table[parsx_token(KUndef)][63] = 552;
		parsx_table[parsx_token(OLBrace)][64] = 553;
		parsx_table[parsx_token(KBool)][64] = 554;
		parsx_table[parsx_token(KInt)][64] = 555;
		parsx_table[parsx_token(KFloat)][64] = 556;
		parsx_table[parsx_token(KDouble)][64] = 557;
		parsx_table[parsx_token(Identifier)][64] = 558;
		parsx_table[parsx_token(KString)][64] = 559;
		parsx_table[parsx_token(KBytes)][64] = 560;
		parsx_table[parsx_token(OLParen)][64] = 561;
		parsx_table[parsx_token(KUnit)][64] = 562;
		parsx_table[parsx_token(KUndef)][64] = 563;
		parsx_table[parsx_token(OMinus)][67] = 564;
		parsx_table[parsx_token(KAnd)][67] = 565;
		parsx_table[parsx_token(OConcat)][67] = 566;
		parsx_table[parsx_token(OLT)][67] = 567;
		parsx_table[parsx_token(KOr)][67] = 568;
		parsx_table[parsx_token(OGT)][67] = 569;
		parsx_table[parsx_token(OLE)][67] = 570;
		parsx_table[parsx_token(OGE)][67] = 571;
		parsx_table[parsx_token(OEQ)][67] = 572;
		parsx_table[parsx_token(OColon)][67] = 573;
		parsx_table[parsx_token(ONE)][67] = 574;
		parsx_table[parsx_token(OPlus)][67] = 575;
		parsx_table[parsx_token(OLBrace)][69] = 576;
		parsx_table[parsx_token(KBool)][69] = 577;
		parsx_table[parsx_token(KInt)][69] = 578;
		parsx_table[parsx_token(KFloat)][69] = 579;
		parsx_table[parsx_token(KDouble)][69] = 580;
		parsx_table[parsx_token(Identifier)][69] = 581;
		parsx_table[parsx_token(KString)][69] = 582;
		parsx_table[parsx_token(KBytes)][69] = 583;
		parsx_table[parsx_token(OLParen)][69] = 584;
		parsx_table[parsx_token(KUnit)][69] = 585;
		parsx_table[parsx_token(KUndef)][69] = 586;
		parsx_table[parsx_token(Identifier)][72] = 587;
		parsx_table[parsx_token(OLBrace)][75] = 588;
		parsx_table[parsx_token(KBool)][75] = 589;
		parsx_table[parsx_token(KInt)][75] = 590;
		parsx_table[parsx_token(KFloat)][75] = 591;
		parsx_table[parsx_token(KDouble)][75] = 592;
		parsx_table[parsx_token(Identifier)][75] = 593;
		parsx_table[parsx_token(KString)][75] = 594;
		parsx_table[parsx_token(KBytes)][75] = 595;
		parsx_table[parsx_token(OLParen)][75] = 596;
		parsx_table[parsx_token(KUnit)][75] = 597;
		parsx_table[parsx_token(KUndef)][75] = 598;
		parsx_table[parsx_token(OPeriod)][76] = 599;
		parsx_table[parsx_token(OColon)][77] = 600;
		parsx_table[parsx_token(OLParen)][78] = 601;
		parsx_table[parsx_token(ORParen)][79] = 602;
		parsx_table[parsx_token(ORBrace)][80] = 603;
		parsx_table[parsx_token(OGT)][81] = 604;
		parsx_table[parsx_token(KCase)][84] = 605;
		parsx_table[parsx_token(OMult)][85] = 606;
		parsx_table[parsx_token(OArrow)][86] = 607;
		parsx_table[parsx_token(OVBar)][87] = 608;
		parsx_table[parsx_token(OComma)][88] = 609;
		parsx_table[parsx_token(OAssign)][89] = 610;
		parsx_table[parsx_token(OQuote)][90] = 611;
		parsx_table[parsx_token(Identifier)][92] = 612;
		parsx_table[parsx_token(StringLiteral)][93] = 613;
		parsx_table[parsx_token(OMinus)][94] = 614;
		parsx_table[parsx_token(OMult)][94] = 615;
		parsx_table[parsx_token(OGT)][94] = 616;
		parsx_table[parsx_token(OConcat)][94] = 617;
		parsx_table[parsx_token(ODiv)][94] = 618;
		parsx_table[parsx_token(KOr)][94] = 619;
		parsx_table[parsx_token(ORem)][94] = 620;
		parsx_table[parsx_token(OLT)][94] = 621;
		parsx_table[parsx_token(OGE)][94] = 622;
		parsx_table[parsx_token(OLE)][94] = 623;
		parsx_table[parsx_token(OPeriod)][94] = 624;
		parsx_table[parsx_token(OEQ)][94] = 625;
		parsx_table[parsx_token(OColon)][94] = 626;
		parsx_table[parsx_token(ONE)][94] = 627;
		parsx_table[parsx_token(KAnd)][94] = 628;
		parsx_table[parsx_token(OLParen)][94] = 629;
		parsx_table[parsx_token(OPlus)][94] = 630;
		parsx_table[parsx_token(OMinus)][96] = 631;
		parsx_table[parsx_token(OMult)][96] = 632;
		parsx_table[parsx_token(OConcat)][96] = 633;
		parsx_table[parsx_token(ODiv)][96] = 634;
		parsx_table[parsx_token(ORem)][96] = 635;
		parsx_table[parsx_token(OPeriod)][96] = 636;
		parsx_table[parsx_token(OLParen)][96] = 637;
		parsx_table[parsx_token(OPlus)][96] = 638;
		parsx_table[parsx_token(KElseIf)][99] = 639;
		parsx_table[parsx_token(KElse)][99] = 640;
		parsx_table[parsx_token(OVBar)][100] = 641;
		parsx_table[parsx_token(OMinus)][106] = 642;
		parsx_table[parsx_token(OPlus)][106] = 643;
		parsx_table[parsx_token(OConcat)][106] = 644;
		parsx_table[parsx_token(Identifier)][110] = 645;
		parsx_table[parsx_token(OArrow)][110] = 646;
		parsx_table[parsx_token(OPeriod)][110] = 647;
		parsx_table[parsx_token(OVBar)][110] = 648;
		parsx_table[parsx_token(OColon)][110] = 649;
		parsx_table[parsx_token(OQuestion)][110] = 650;
		parsx_table[parsx_token(KElseIf)][112] = 651;
		parsx_table[parsx_token(KElse)][112] = 652;
		parsx_table[parsx_token(Identifier)][115] = 653;
		parsx_table[parsx_token(OComma)][132] = 654;
		parsx_table[parsx_token(Identifier)][133] = 655;
		parsx_table[parsx_token(OSemicolon)][133] = 656;
		parsx_table[parsx_token(OLBrace)][140] = 657;
		parsx_table[parsx_token(KNull)][140] = 658;
		parsx_table[parsx_token(OMult)][140] = 659;
		parsx_table[parsx_token(Identifier)][140] = 660;
		parsx_table[parsx_token(OQuote)][140] = 661;
		parsx_table[parsx_token(StringLiteral)][140] = 662;
		parsx_table[parsx_token(OVBar)][140] = 663;
		parsx_table[parsx_token(OLParen)][140] = 664;
		parsx_table[parsx_token(NumberLiteral)][140] = 665;
		parsx_table[parsx_token(KTrue)][140] = 666;
		parsx_table[parsx_token(KUnit)][140] = 667;
		parsx_table[parsx_token(KFalse)][140] = 668;
		parsx_table[parsx_token(Identifier)][143] = 669;
		parsx_table[parsx_token(OLT)][143] = 670;
		parsx_table[parsx_token(KIf)][145] = 671;
		parsx_table[parsx_token(KThen)][145] = 672;
		parsx_table[parsx_token(Identifier)][146] = 673;
		parsx_table[parsx_token(OLT)][146] = 674;
		parsx_table[parsx_token(Identifier)][148] = 675;
		parsx_table[parsx_token(OLT)][148] = 676;
		parsx_table[parsx_token(Identifier)][151] = 677;
		parsx_table[parsx_token(OLT)][151] = 678;
		parsx_table[parsx_token(Identifier)][153] = 679;
		parsx_table[parsx_token(OSemicolon)][153] = 680;
		parsx_table[parsx_token(OComma)][154] = 681;
		parsx_table[parsx_token(ORParen)][154] = 682;
		parsx_table[parsx_token(OLParen)][157] = 683;
		parsx_table[parsx_token(OPeriod)][157] = 684;
		parsx_table[parsx_token(Identifier)][158] = 685;
		parsx_table[parsx_token(ONE)][158] = 686;
		parsx_table[parsx_token(OLT)][158] = 687;
		parsx_table[parsx_token(OMinus)][159] = 688;
		parsx_table[parsx_token(OMult)][159] = 689;
		parsx_table[parsx_token(OGT)][159] = 690;
		parsx_table[parsx_token(OConcat)][159] = 691;
		parsx_table[parsx_token(ODiv)][159] = 692;
		parsx_table[parsx_token(KOr)][159] = 693;
		parsx_table[parsx_token(ORem)][159] = 694;
		parsx_table[parsx_token(OLT)][159] = 695;
		parsx_table[parsx_token(OGE)][159] = 696;
		parsx_table[parsx_token(OLE)][159] = 697;
		parsx_table[parsx_token(OPeriod)][159] = 698;
		parsx_table[parsx_token(OEQ)][159] = 699;
		parsx_table[parsx_token(OColon)][159] = 700;
		parsx_table[parsx_token(ONE)][159] = 701;
		parsx_table[parsx_token(KAnd)][159] = 702;
		parsx_table[parsx_token(OLParen)][159] = 703;
		parsx_table[parsx_token(OPlus)][159] = 704;
		parsx_table[parsx_token(Identifier)][162] = 705;
		parsx_table[parsx_token(OLT)][162] = 706;
		parsx_table[parsx_token(Identifier)][167] = 707;
		parsx_table[parsx_token(OLT)][167] = 708;
		parsx_table[parsx_token(Identifier)][172] = 709;
		parsx_table[parsx_token(OLBrace)][185] = 710;
		parsx_table[parsx_token(OMinus)][185] = 711;
		parsx_table[parsx_token(KNull)][185] = 712;
		parsx_table[parsx_token(KNot)][185] = 713;
		parsx_table[parsx_token(Identifier)][185] = 714;
		parsx_table[parsx_token(KLambda)][185] = 715;
		parsx_table[parsx_token(StringLiteral)][185] = 716;
		parsx_table[parsx_token(KNew)][185] = 717;
		parsx_table[parsx_token(OLParen)][185] = 718;
		parsx_table[parsx_token(NumberLiteral)][185] = 719;
		parsx_table[parsx_token(KTrue)][185] = 720;
		parsx_table[parsx_token(KUnit)][185] = 721;
		parsx_table[parsx_token(KFalse)][185] = 722;
		parsx_table[parsx_token(Identifier)][189] = 723;
		parsx_table[parsx_token(OLT)][189] = 724;
		parsx_table[parsx_token(OLParen)][198] = 725;
		parsx_table[parsx_token(OLBrace)][202] = 726;
		parsx_table[parsx_token(KNull)][202] = 727;
		parsx_table[parsx_token(OMult)][202] = 728;
		parsx_table[parsx_token(Identifier)][202] = 729;
		parsx_table[parsx_token(OQuote)][202] = 730;
		parsx_table[parsx_token(StringLiteral)][202] = 731;
		parsx_table[parsx_token(OLParen)][202] = 732;
		parsx_table[parsx_token(NumberLiteral)][202] = 733;
		parsx_table[parsx_token(KTrue)][202] = 734;
		parsx_table[parsx_token(KUnit)][202] = 735;
		parsx_table[parsx_token(KFalse)][202] = 736;
		parsx_table[parsx_token(KStruct)][205] = 737;
		parsx_table[parsx_token(KInterface)][205] = 738;
		parsx_table[parsx_token(KClass)][205] = 739;
		parsx_table[parsx_token(KEnum)][205] = 740;
		parsx_table[parsx_token(KFunction)][205] = 741;
		parsx_table[parsx_token(KGlobal)][205] = 742;
		parsx_table[parsx_token(OLParen)][207] = 743;
		parsx_table[parsx_token(KImport)][209] = 744;
		parsx_table[parsx_token(KImplements)][210] = 745;
		parsx_table[parsx_token(KWith)][214] = 746;
		parsx_table[parsx_token(Identifier)][216] = 747;
		parsx_table[parsx_token(Identifier)][219] = 748;
		parsx_table[parsx_token(Identifier)][223] = 749;
		parsx_table[parsx_token(KOr)][228] = 750;
		parsx_table[parsx_token(OColon)][228] = 751;
		parsx_table[parsx_token(OLBrace)][230] = 752;
		parsx_table[parsx_token(KBool)][230] = 753;
		parsx_table[parsx_token(KInt)][230] = 754;
		parsx_table[parsx_token(KFloat)][230] = 755;
		parsx_table[parsx_token(KDouble)][230] = 756;
		parsx_table[parsx_token(Identifier)][230] = 757;
		parsx_table[parsx_token(KString)][230] = 758;
		parsx_table[parsx_token(KBytes)][230] = 759;
		parsx_table[parsx_token(OLParen)][230] = 760;
		parsx_table[parsx_token(KUnit)][230] = 761;
		parsx_table[parsx_token(KUndef)][230] = 762;
		parsx_table[parsx_token(OColon)][232] = 763;
		parsx_table[parsx_token(OAssign)][236] = 764;
		parsx_table[parsx_token(OSemicolon)][236] = 765;
		parsx_table[parsx_token(OColon)][236] = 766;
		parsx_table[parsx_token(OLParen)][239] = 767;
		parsx_table[parsx_token(OPeriod)][239] = 768;
		parsx_table[parsx_token(KAnd)][240] = 769;
		parsx_table[parsx_token(OLT)][240] = 770;
		parsx_table[parsx_token(OGT)][240] = 771;
		parsx_table[parsx_token(OLE)][240] = 772;
		parsx_table[parsx_token(OGE)][240] = 773;
		parsx_table[parsx_token(OEQ)][240] = 774;
		parsx_table[parsx_token(ONE)][240] = 775;
		parsx_table[parsx_token(OLParen)][241] = 776;
		parsx_table[parsx_token(OVBar)][243] = 777;
		parsx_table[parsx_token(OBigArrow)][249] = 778;
		parsx_table[parsx_token(KNot)][249] = 779;
		parsx_table[parsx_token(KIf)][249] = 780;
		parsx_table[parsx_token(KConstruct)][249] = 781;
		parsx_table[parsx_token(OLParen)][249] = 782;
		parsx_table[parsx_token(KEnd)][249] = 783;
		parsx_table[parsx_token(OLBrace)][249] = 784;
		parsx_table[parsx_token(KFor)][249] = 785;
		parsx_table[parsx_token(KWhile)][249] = 786;
		parsx_table[parsx_token(KDo)][249] = 787;
		parsx_table[parsx_token(KVar)][249] = 788;
		parsx_table[parsx_token(KLet)][249] = 789;
		parsx_table[parsx_token(KReturn)][249] = 790;
		parsx_table[parsx_token(KEval)][249] = 791;
		parsx_table[parsx_token(KRaise)][249] = 792;
		parsx_table[parsx_token(OMinus)][249] = 793;
		parsx_table[parsx_token(KMatch)][249] = 794;
		parsx_table[parsx_token(KRepeat)][249] = 795;
		parsx_table[parsx_token(KLambda)][249] = 796;
		parsx_table[parsx_token(KNew)][249] = 797;
		parsx_table[parsx_token(KImport)][249] = 798;
		parsx_table[parsx_token(KUnit)][249] = 799;
		parsx_table[parsx_token(KNull)][249] = 800;
		parsx_table[parsx_token(Identifier)][249] = 801;
		parsx_table[parsx_token(StringLiteral)][249] = 802;
		parsx_table[parsx_token(NumberLiteral)][249] = 803;
		parsx_table[parsx_token(KTrue)][249] = 804;
		parsx_table[parsx_token(KFalse)][249] = 805;
		parsx_table[parsx_token(OMinus)][251] = 806;
		parsx_table[parsx_token(KMatch)][251] = 807;
		parsx_table[parsx_token(KNull)][251] = 808;
		parsx_table[parsx_token(OLBrace)][251] = 809;
		parsx_table[parsx_token(KIf)][251] = 810;
		parsx_table[parsx_token(Identifier)][251] = 811;
		parsx_table[parsx_token(KLambda)][251] = 812;
		parsx_table[parsx_token(StringLiteral)][251] = 813;
		parsx_table[parsx_token(KNew)][251] = 814;
		parsx_table[parsx_token(OLParen)][251] = 815;
		parsx_table[parsx_token(NumberLiteral)][251] = 816;
		parsx_table[parsx_token(KTrue)][251] = 817;
		parsx_table[parsx_token(KUnit)][251] = 818;
		parsx_table[parsx_token(KNot)][251] = 819;
		parsx_table[parsx_token(KFalse)][251] = 820;
		parsx_table[parsx_token(OColon)][252] = 821;
		parsx_table[parsx_token(OLParen)][253] = 822;
		parsx_table[parsx_token(OPeriod)][253] = 823;
		parsx_table[parsx_token(OLBrace)][254] = 824;
		parsx_table[parsx_token(KMatch)][254] = 825;
		parsx_table[parsx_token(OMinus)][254] = 826;
		parsx_table[parsx_token(KNull)][254] = 827;
		parsx_table[parsx_token(KNot)][254] = 828;
		parsx_table[parsx_token(KIf)][254] = 829;
		parsx_table[parsx_token(Identifier)][254] = 830;
		parsx_table[parsx_token(KLambda)][254] = 831;
		parsx_table[parsx_token(StringLiteral)][254] = 832;
		parsx_table[parsx_token(KNew)][254] = 833;
		parsx_table[parsx_token(OLParen)][254] = 834;
		parsx_table[parsx_token(NumberLiteral)][254] = 835;
		parsx_table[parsx_token(KTrue)][254] = 836;
		parsx_table[parsx_token(KUnit)][254] = 837;
		parsx_table[parsx_token(KFalse)][254] = 838;
		parsx_table[parsx_token(OComma)][255] = 839;
		parsx_table[parsx_token(OPeriod)][257] = 840;
		parsx_table[parsx_token(OPeriod)][258] = 841;
		parsx_table[parsx_token(OMinus)][260] = 842;
		parsx_table[parsx_token(KAnd)][260] = 843;
		parsx_table[parsx_token(OConcat)][260] = 844;
		parsx_table[parsx_token(OLT)][260] = 845;
		parsx_table[parsx_token(KOr)][260] = 846;
		parsx_table[parsx_token(OGT)][260] = 847;
		parsx_table[parsx_token(OLE)][260] = 848;
		parsx_table[parsx_token(OGE)][260] = 849;
		parsx_table[parsx_token(OEQ)][260] = 850;
		parsx_table[parsx_token(OColon)][260] = 851;
		parsx_table[parsx_token(ONE)][260] = 852;
		parsx_table[parsx_token(OPlus)][260] = 853;
		parsx_table[parsx_token(OLBrace)][261] = 854;
		parsx_table[parsx_token(KMatch)][261] = 855;
		parsx_table[parsx_token(OMinus)][261] = 856;
		parsx_table[parsx_token(KNull)][261] = 857;
		parsx_table[parsx_token(KNot)][261] = 858;
		parsx_table[parsx_token(KIf)][261] = 859;
		parsx_table[parsx_token(Identifier)][261] = 860;
		parsx_table[parsx_token(KLambda)][261] = 861;
		parsx_table[parsx_token(StringLiteral)][261] = 862;
		parsx_table[parsx_token(KNew)][261] = 863;
		parsx_table[parsx_token(OLParen)][261] = 864;
		parsx_table[parsx_token(NumberLiteral)][261] = 865;
		parsx_table[parsx_token(KTrue)][261] = 866;
		parsx_table[parsx_token(KUnit)][261] = 867;
		parsx_table[parsx_token(KFalse)][261] = 868;
		parsx_table[parsx_token(KField)][262] = 869;
		parsx_table[parsx_token(OComma)][263] = 870;
		parsx_table[parsx_token(OLBrace)][266] = 871;
		parsx_table[parsx_token(OMinus)][266] = 872;
		parsx_table[parsx_token(KMatch)][266] = 873;
		parsx_table[parsx_token(KNot)][266] = 874;
		parsx_table[parsx_token(KIf)][266] = 875;
		parsx_table[parsx_token(Identifier)][266] = 876;
		parsx_table[parsx_token(KLambda)][266] = 877;
		parsx_table[parsx_token(StringLiteral)][266] = 878;
		parsx_table[parsx_token(KNew)][266] = 879;
		parsx_table[parsx_token(OLParen)][266] = 880;
		parsx_table[parsx_token(NumberLiteral)][266] = 881;
		parsx_table[parsx_token(KTrue)][266] = 882;
		parsx_table[parsx_token(KUnit)][266] = 883;
		parsx_table[parsx_token(KNull)][266] = 884;
		parsx_table[parsx_token(KFalse)][266] = 885;
		parsx_table[parsx_token(KCase)][267] = 886;
		parsx_table[parsx_token(OLBrace)][269] = 887;
		parsx_table[parsx_token(KMatch)][269] = 888;
		parsx_table[parsx_token(KNull)][269] = 889;
		parsx_table[parsx_token(KUnit)][269] = 890;
		parsx_table[parsx_token(KNot)][269] = 891;
		parsx_table[parsx_token(OMinus)][269] = 892;
		parsx_table[parsx_token(Identifier)][269] = 893;
		parsx_table[parsx_token(KLambda)][269] = 894;
		parsx_table[parsx_token(StringLiteral)][269] = 895;
		parsx_table[parsx_token(KNew)][269] = 896;
		parsx_table[parsx_token(OLParen)][269] = 897;
		parsx_table[parsx_token(NumberLiteral)][269] = 898;
		parsx_table[parsx_token(KTrue)][269] = 899;
		parsx_table[parsx_token(KIf)][269] = 900;
		parsx_table[parsx_token(KFalse)][269] = 901;
		parsx_table[parsx_token(OPeriod)][271] = 902;
		parsx_table[parsx_token(OVBar)][273] = 903;
		parsx_table[parsx_token(OComma)][275] = 904;
		parsx_table[parsx_token(OComma)][277] = 905;
		parsx_table[parsx_token(KOr)][278] = 906;
		parsx_table[parsx_token(OColon)][278] = 907;
		parsx_table[parsx_token(OMinus)][279] = 908;
		parsx_table[parsx_token(OPlus)][279] = 909;
		parsx_table[parsx_token(OMinus)][283] = 910;
		parsx_table[parsx_token(KMatch)][283] = 911;
		parsx_table[parsx_token(KNull)][283] = 912;
		parsx_table[parsx_token(OLBrace)][283] = 913;
		parsx_table[parsx_token(KIf)][283] = 914;
		parsx_table[parsx_token(Identifier)][283] = 915;
		parsx_table[parsx_token(KLambda)][283] = 916;
		parsx_table[parsx_token(StringLiteral)][283] = 917;
		parsx_table[parsx_token(OComma)][283] = 918;
		parsx_table[parsx_token(KNew)][283] = 919;
		parsx_table[parsx_token(OLParen)][283] = 920;
		parsx_table[parsx_token(NumberLiteral)][283] = 921;
		parsx_table[parsx_token(KTrue)][283] = 922;
		parsx_table[parsx_token(KUnit)][283] = 923;
		parsx_table[parsx_token(KNot)][283] = 924;
		parsx_table[parsx_token(KFalse)][283] = 925;
		parsx_table[parsx_token(OMinus)][285] = 926;
		parsx_table[parsx_token(OMult)][285] = 927;
		parsx_table[parsx_token(OGT)][285] = 928;
		parsx_table[parsx_token(OConcat)][285] = 929;
		parsx_table[parsx_token(ODiv)][285] = 930;
		parsx_table[parsx_token(KOr)][285] = 931;
		parsx_table[parsx_token(ORem)][285] = 932;
		parsx_table[parsx_token(OLT)][285] = 933;
		parsx_table[parsx_token(OGE)][285] = 934;
		parsx_table[parsx_token(OLE)][285] = 935;
		parsx_table[parsx_token(OPeriod)][285] = 936;
		parsx_table[parsx_token(OEQ)][285] = 937;
		parsx_table[parsx_token(OColon)][285] = 938;
		parsx_table[parsx_token(ONE)][285] = 939;
		parsx_table[parsx_token(KAnd)][285] = 940;
		parsx_table[parsx_token(OLParen)][285] = 941;
		parsx_table[parsx_token(OPlus)][285] = 942;
		parsx_table[parsx_token(OVBar)][286] = 943;
		parsx_table[parsx_token(OMult)][287] = 944;
		parsx_table[parsx_token(ODiv)][287] = 945;
		parsx_table[parsx_token(ORem)][287] = 946;
		parsx_table[parsx_token(OPeriod)][287] = 947;
		parsx_table[parsx_token(OLParen)][287] = 948;
		parsx_table[parsx_token(Identifier)][289] = 949;
		parsx_table[parsx_token(OLBrace)][290] = 950;
		parsx_table[parsx_token(KNull)][290] = 951;
		parsx_table[parsx_token(OMult)][290] = 952;
		parsx_table[parsx_token(Identifier)][290] = 953;
		parsx_table[parsx_token(OPeriod)][290] = 954;
		parsx_table[parsx_token(OQuote)][290] = 955;
		parsx_table[parsx_token(StringLiteral)][290] = 956;
		parsx_table[parsx_token(OLParen)][290] = 957;
		parsx_table[parsx_token(NumberLiteral)][290] = 958;
		parsx_table[parsx_token(KTrue)][290] = 959;
		parsx_table[parsx_token(KUnit)][290] = 960;
		parsx_table[parsx_token(KFalse)][290] = 961;
		parsx_table[parsx_token(KField)][293] = 962;
		parsx_table[parsx_token(KMethod)][293] = 963;
		parsx_table[parsx_token(KAbstract)][293] = 964;
		parsx_table[parsx_token(KConstructor)][293] = 965;
		parsx_table[parsx_token(KOverride)][293] = 966;
		parsx_table[parsx_token(KAnd)][294] = 967;
		parsx_table[parsx_token(OConcat)][294] = 968;
		parsx_table[parsx_token(OLT)][294] = 969;
		parsx_table[parsx_token(KOr)][294] = 970;
		parsx_table[parsx_token(OGT)][294] = 971;
		parsx_table[parsx_token(OLE)][294] = 972;
		parsx_table[parsx_token(OGE)][294] = 973;
		parsx_table[parsx_token(OEQ)][294] = 974;
		parsx_table[parsx_token(OColon)][294] = 975;
		parsx_table[parsx_token(ONE)][294] = 976;
		parsx_table[parsx_token(KCase)][296] = 977;
		parsx_table[parsx_token(OLParen)][297] = 978;
		parsx_table[parsx_token(OPeriod)][297] = 979;
		parsx_table[parsx_token(OBigArrow)][298] = 980;
		parsx_table[parsx_token(KNot)][298] = 981;
		parsx_table[parsx_token(KIf)][298] = 982;
		parsx_table[parsx_token(KConstruct)][298] = 983;
		parsx_table[parsx_token(OLParen)][298] = 984;
		parsx_table[parsx_token(KEnd)][298] = 985;
		parsx_table[parsx_token(OLBrace)][298] = 986;
		parsx_table[parsx_token(KFor)][298] = 987;
		parsx_table[parsx_token(KWhile)][298] = 988;
		parsx_table[parsx_token(KDo)][298] = 989;
		parsx_table[parsx_token(KVar)][298] = 990;
		parsx_table[parsx_token(KLet)][298] = 991;
		parsx_table[parsx_token(KReturn)][298] = 992;
		parsx_table[parsx_token(KEval)][298] = 993;
		parsx_table[parsx_token(KRaise)][298] = 994;
		parsx_table[parsx_token(OMinus)][298] = 995;
		parsx_table[parsx_token(KMatch)][298] = 996;
		parsx_table[parsx_token(KRepeat)][298] = 997;
		parsx_table[parsx_token(KLambda)][298] = 998;
		parsx_table[parsx_token(KNew)][298] = 999;
		parsx_table[parsx_token(KImport)][298] = 1000;
		parsx_table[parsx_token(KUnit)][298] = 1001;
		parsx_table[parsx_token(KNull)][298] = 1002;
		parsx_table[parsx_token(Identifier)][298] = 1003;
		parsx_table[parsx_token(StringLiteral)][298] = 1004;
		parsx_table[parsx_token(NumberLiteral)][298] = 1005;
		parsx_table[parsx_token(KTrue)][298] = 1006;
		parsx_table[parsx_token(KFalse)][298] = 1007;
		parsx_table[parsx_token(OMult)][299] = 1008;
		parsx_table[parsx_token(ODiv)][299] = 1009;
		parsx_table[parsx_token(ORem)][299] = 1010;
		parsx_table[parsx_token(OPeriod)][299] = 1011;
		parsx_table[parsx_token(OLParen)][299] = 1012;
		parsx_table[parsx_token(OComma)][303] = 1013;
		parsx_table[parsx_token(ORem)][306] = 1014;
		parsx_table[parsx_token(OMult)][306] = 1015;
		parsx_table[parsx_token(ODiv)][306] = 1016;
		parsx_table[parsx_token(OComma)][308] = 1017;
		parsx_table[parsx_token(KCase)][314] = 1018;
		parsx_table[parsx_token(OMinus)][316] = 1019;
		parsx_table[parsx_token(OMult)][316] = 1020;
		parsx_table[parsx_token(OConcat)][316] = 1021;
		parsx_table[parsx_token(ODiv)][316] = 1022;
		parsx_table[parsx_token(KOr)][316] = 1023;
		parsx_table[parsx_token(ORem)][316] = 1024;
		parsx_table[parsx_token(OLT)][316] = 1025;
		parsx_table[parsx_token(OLE)][316] = 1026;
		parsx_table[parsx_token(OGE)][316] = 1027;
		parsx_table[parsx_token(OEQ)][316] = 1028;
		parsx_table[parsx_token(OColon)][316] = 1029;
		parsx_table[parsx_token(ONE)][316] = 1030;
		parsx_table[parsx_token(KAnd)][316] = 1031;
		parsx_table[parsx_token(OGT)][316] = 1032;
		parsx_table[parsx_token(OPlus)][316] = 1033;
		parsx_table[parsx_token(KCase)][318] = 1034;
		parsx_table[parsx_token(OLBrace)][321] = 1035;
		parsx_table[parsx_token(KBool)][321] = 1036;
		parsx_table[parsx_token(KInt)][321] = 1037;
		parsx_table[parsx_token(KFloat)][321] = 1038;
		parsx_table[parsx_token(KDouble)][321] = 1039;
		parsx_table[parsx_token(Identifier)][321] = 1040;
		parsx_table[parsx_token(KString)][321] = 1041;
		parsx_table[parsx_token(KBytes)][321] = 1042;
		parsx_table[parsx_token(OLParen)][321] = 1043;
		parsx_table[parsx_token(KUnit)][321] = 1044;
		parsx_table[parsx_token(KUndef)][321] = 1045;
		parsx_table[parsx_token(OConcat)][322] = 1046;
		parsx_table[parsx_token(OMinus)][326] = 1047;
		parsx_table[parsx_token(OMult)][326] = 1048;
		parsx_table[parsx_token(ODiv)][326] = 1049;
		parsx_table[parsx_token(ORem)][326] = 1050;
		parsx_table[parsx_token(OPeriod)][326] = 1051;
		parsx_table[parsx_token(OLParen)][326] = 1052;
		parsx_table[parsx_token(OPlus)][326] = 1053;
		parsx_table[parsx_token(OLBrace)][327] = 1054;
		parsx_table[parsx_token(KNull)][327] = 1055;
		parsx_table[parsx_token(OMult)][327] = 1056;
		parsx_table[parsx_token(Identifier)][327] = 1057;
		parsx_table[parsx_token(OQuote)][327] = 1058;
		parsx_table[parsx_token(StringLiteral)][327] = 1059;
		parsx_table[parsx_token(OVBar)][327] = 1060;
		parsx_table[parsx_token(OLParen)][327] = 1061;
		parsx_table[parsx_token(NumberLiteral)][327] = 1062;
		parsx_table[parsx_token(KTrue)][327] = 1063;
		parsx_table[parsx_token(KUnit)][327] = 1064;
		parsx_table[parsx_token(KFalse)][327] = 1065;
		parsx_table[parsx_token(OLBrace)][330] = 1066;
		parsx_table[parsx_token(KUndef)][330] = 1067;
		parsx_table[parsx_token(KBool)][330] = 1068;
		parsx_table[parsx_token(KInt)][330] = 1069;
		parsx_table[parsx_token(KFloat)][330] = 1070;
		parsx_table[parsx_token(KDouble)][330] = 1071;
		parsx_table[parsx_token(Identifier)][330] = 1072;
		parsx_table[parsx_token(KString)][330] = 1073;
		parsx_table[parsx_token(KBytes)][330] = 1074;
		parsx_table[parsx_token(OLParen)][330] = 1075;
		parsx_table[parsx_token(KUnit)][330] = 1076;
		parsx_table[parsx_token(ORParen)][330] = 1077;
		parsx_table[parsx_token(KAnd)][332] = 1078;
		parsx_table[parsx_token(OConcat)][332] = 1079;
		parsx_table[parsx_token(OLT)][332] = 1080;
		parsx_table[parsx_token(KOr)][332] = 1081;
		parsx_table[parsx_token(OGT)][332] = 1082;
		parsx_table[parsx_token(OLE)][332] = 1083;
		parsx_table[parsx_token(OGE)][332] = 1084;
		parsx_table[parsx_token(OEQ)][332] = 1085;
		parsx_table[parsx_token(OColon)][332] = 1086;
		parsx_table[parsx_token(ONE)][332] = 1087;
		parsx_table[parsx_token(OArrow)][333] = 1088;
		parsx_table[parsx_token(OMinus)][334] = 1089;
		parsx_table[parsx_token(OMult)][334] = 1090;
		parsx_table[parsx_token(ODiv)][334] = 1091;
		parsx_table[parsx_token(ORem)][334] = 1092;
		parsx_table[parsx_token(OPlus)][334] = 1093;
		parsx_table[parsx_token(KWith)][342] = 1094;
		parsx_table[parsx_token(KImplements)][349] = 1095;
		parsx_table[parsx_token(KConstructor)][351] = 1096;
		parsx_table[parsx_token(KAbstract)][351] = 1097;
		parsx_table[parsx_token(KField)][351] = 1098;
		parsx_table[parsx_token(KMethod)][351] = 1099;
		parsx_table[parsx_token(KOverride)][351] = 1100;
		parsx_table[parsx_token(KField)][352] = 1101;
		parsx_table[parsx_token(OAssign)][356] = 1102;
		parsx_table[parsx_token(OSemicolon)][356] = 1103;
		parsx_table[parsx_token(OColon)][356] = 1104;
		parsx_table[parsx_token(KImport)][360] = 1105;
		parsx_table[parsx_token(OLParen)][363] = 1106;
		parsx_table[parsx_token(OVBar)][365] = 1107;
		parsx_table[parsx_token(Identifier)][366] = 1108;
		parsx_table[parsx_token(KWith)][366] = 1109;
		parsx_table[parsx_token(OLParen)][366] = 1110;
		parsx_table[parsx_token(KThen)][367] = 1111;
		parsx_table[parsx_token(Identifier)][369] = 1112;
		parsx_table[parsx_token(OPeriod)][369] = 1113;
		parsx_table[parsx_token(KWith)][369] = 1114;
		parsx_table[parsx_token(KDo)][373] = 1115;
		parsx_table[parsx_token(KIn)][374] = 1116;
		parsx_table[parsx_token(OLBrace)][375] = 1117;
		parsx_table[parsx_token(KMatch)][375] = 1118;
		parsx_table[parsx_token(OMinus)][375] = 1119;
		parsx_table[parsx_token(KNull)][375] = 1120;
		parsx_table[parsx_token(KNot)][375] = 1121;
		parsx_table[parsx_token(KIf)][375] = 1122;
		parsx_table[parsx_token(Identifier)][375] = 1123;
		parsx_table[parsx_token(KLambda)][375] = 1124;
		parsx_table[parsx_token(StringLiteral)][375] = 1125;
		parsx_table[parsx_token(KNew)][375] = 1126;
		parsx_table[parsx_token(OLParen)][375] = 1127;
		parsx_table[parsx_token(NumberLiteral)][375] = 1128;
		parsx_table[parsx_token(KTrue)][375] = 1129;
		parsx_table[parsx_token(KUnit)][375] = 1130;
		parsx_table[parsx_token(KFalse)][375] = 1131;
		parsx_table[parsx_token(KMethod)][376] = 1132;
		parsx_table[parsx_token(KElseIf)][379] = 1133;
		parsx_table[parsx_token(KEnd)][379] = 1134;
		parsx_table[parsx_token(KElse)][379] = 1135;
		parsx_table[parsx_token(KUntil)][383] = 1136;
		parsx_table[parsx_token(OPeriod)][385] = 1137;
		parsx_table[parsx_token(OMinus)][387] = 1138;
		parsx_table[parsx_token(OMult)][387] = 1139;
		parsx_table[parsx_token(OConcat)][387] = 1140;
		parsx_table[parsx_token(ODiv)][387] = 1141;
		parsx_table[parsx_token(KOr)][387] = 1142;
		parsx_table[parsx_token(ORem)][387] = 1143;
		parsx_table[parsx_token(OLT)][387] = 1144;
		parsx_table[parsx_token(OLE)][387] = 1145;
		parsx_table[parsx_token(OGE)][387] = 1146;
		parsx_table[parsx_token(OEQ)][387] = 1147;
		parsx_table[parsx_token(OColon)][387] = 1148;
		parsx_table[parsx_token(ONE)][387] = 1149;
		parsx_table[parsx_token(KAnd)][387] = 1150;
		parsx_table[parsx_token(OGT)][387] = 1151;
		parsx_table[parsx_token(OPlus)][387] = 1152;
		parsx_table[parsx_token(OArrow)][389] = 1153;
		parsx_table[parsx_token(OQuestion)][389] = 1154;
		parsx_table[parsx_token(OAssign)][392] = 1155;
		parsx_table[parsx_token(KStruct)][395] = 1156;
		parsx_table[parsx_token(KInterface)][395] = 1157;
		parsx_table[parsx_token(KClass)][395] = 1158;
		parsx_table[parsx_token(KEnum)][395] = 1159;
		parsx_table[parsx_token(KFunction)][395] = 1160;
		parsx_table[parsx_token(KGlobal)][395] = 1161;
		parsx_table[parsx_token(OComma)][396] = 1162;
		parsx_table[parsx_token(OComma)][397] = 1163;
		parsx_table[parsx_token(OAssign)][397] = 1164;
		parsx_table[parsx_token(OMinus)][399] = 1165;
		parsx_table[parsx_token(OMult)][399] = 1166;
		parsx_table[parsx_token(OConcat)][399] = 1167;
		parsx_table[parsx_token(ODiv)][399] = 1168;
		parsx_table[parsx_token(ORem)][399] = 1169;
		parsx_table[parsx_token(OPlus)][399] = 1170;
		parsx_table[parsx_token(OLBrace)][401] = 1171;
		parsx_table[parsx_token(KBool)][401] = 1172;
		parsx_table[parsx_token(KInt)][401] = 1173;
		parsx_table[parsx_token(KFloat)][401] = 1174;
		parsx_table[parsx_token(KDouble)][401] = 1175;
		parsx_table[parsx_token(Identifier)][401] = 1176;
		parsx_table[parsx_token(KString)][401] = 1177;
		parsx_table[parsx_token(KBytes)][401] = 1178;
		parsx_table[parsx_token(KUnit)][401] = 1179;
		parsx_table[parsx_token(KUndef)][401] = 1180;
		parsx_table[parsx_token(KWith)][402] = 1181;
		parsx_table[parsx_token(KExtends)][404] = 1182;
		parsx_table[parsx_token(KMethod)][406] = 1183;
		parsx_table[parsx_token(OLParen)][409] = 1184;
		parsx_table[parsx_token(OPeriod)][409] = 1185;
		parsx_table[parsx_token(KAnd)][410] = 1186;
		parsx_table[parsx_token(KExtends)][411] = 1187;
		parsx_table[parsx_token(KNot)][413] = 1188;
		parsx_table[parsx_token(KIf)][413] = 1189;
		parsx_table[parsx_token(KConstruct)][413] = 1190;
		parsx_table[parsx_token(OLBrace)][413] = 1191;
		parsx_table[parsx_token(KFor)][413] = 1192;
		parsx_table[parsx_token(KWhile)][413] = 1193;
		parsx_table[parsx_token(KDo)][413] = 1194;
		parsx_table[parsx_token(KVar)][413] = 1195;
		parsx_table[parsx_token(KLet)][413] = 1196;
		parsx_table[parsx_token(KReturn)][413] = 1197;
		parsx_table[parsx_token(KEval)][413] = 1198;
		parsx_table[parsx_token(KRaise)][413] = 1199;
		parsx_table[parsx_token(KMatch)][413] = 1200;
		parsx_table[parsx_token(KRepeat)][413] = 1201;
		parsx_table[parsx_token(OSemicolon)][413] = 1202;
		parsx_table[parsx_token(KLambda)][413] = 1203;
		parsx_table[parsx_token(KNew)][413] = 1204;
		parsx_table[parsx_token(KUnit)][413] = 1205;
		parsx_table[parsx_token(KNull)][413] = 1206;
		parsx_table[parsx_token(Identifier)][413] = 1207;
		parsx_table[parsx_token(StringLiteral)][413] = 1208;
		parsx_table[parsx_token(NumberLiteral)][413] = 1209;
		parsx_table[parsx_token(KTrue)][413] = 1210;
		parsx_table[parsx_token(KFalse)][413] = 1211;
		parsx_table[parsx_token(OAssign)][416] = 1212;
		parsx_table[parsx_token(KExtends)][417] = 1213;
		parsx_table[parsx_token(KOr)][420] = 1214;
		parsx_table[parsx_token(OColon)][420] = 1215;
		parsx_table[parsx_token(OArrow)][421] = 1216;
		parsx_table[parsx_token(OVBar)][421] = 1217;
		parsx_table[parsx_token(OQuestion)][421] = 1218;
		parsx_table[parsx_token(OComma)][422] = 1219;
		parsx_table[parsx_token(OAssign)][422] = 1220;
		parsx_table[parsx_token(OLParen)][424] = 1221;
		parsx_table[parsx_token(OPeriod)][424] = 1222;
		parsx_table[parsx_token(KConstructor)][426] = 1223;
		parsx_table[parsx_token(KAbstract)][426] = 1224;
		parsx_table[parsx_token(KField)][426] = 1225;
		parsx_table[parsx_token(KMethod)][426] = 1226;
		parsx_table[parsx_token(KOverride)][426] = 1227;
		parsx_table[parsx_token(OMinus)][428] = 1228;
		parsx_table[parsx_token(OPlus)][428] = 1229;
		parsx_table[parsx_token(Identifier)][432] = 1230;
		parsx_table[parsx_token(KAnd)][433] = 1231;
		parsx_table[parsx_token(OLT)][433] = 1232;
		parsx_table[parsx_token(KOr)][433] = 1233;
		parsx_table[parsx_token(OGT)][433] = 1234;
		parsx_table[parsx_token(OLE)][433] = 1235;
		parsx_table[parsx_token(OGE)][433] = 1236;
		parsx_table[parsx_token(OEQ)][433] = 1237;
		parsx_table[parsx_token(OColon)][433] = 1238;
		parsx_table[parsx_token(ONE)][433] = 1239;
		parsx_table[parsx_token(OMinus)][434] = 1240;
		parsx_table[parsx_token(KAnd)][434] = 1241;
		parsx_table[parsx_token(OConcat)][434] = 1242;
		parsx_table[parsx_token(OLT)][434] = 1243;
		parsx_table[parsx_token(KOr)][434] = 1244;
		parsx_table[parsx_token(OGT)][434] = 1245;
		parsx_table[parsx_token(OLE)][434] = 1246;
		parsx_table[parsx_token(OGE)][434] = 1247;
		parsx_table[parsx_token(OEQ)][434] = 1248;
		parsx_table[parsx_token(OColon)][434] = 1249;
		parsx_table[parsx_token(ONE)][434] = 1250;
		parsx_table[parsx_token(OPlus)][434] = 1251;
		parsx_table[parsx_token(KField)][439] = 1252;
		parsx_table[parsx_token(Identifier)][444] = 1253;
		parsx_table[parsx_token(OLBrace)][445] = 1254;
		parsx_table[parsx_token(KBool)][445] = 1255;
		parsx_table[parsx_token(KInt)][445] = 1256;
		parsx_table[parsx_token(KFloat)][445] = 1257;
		parsx_table[parsx_token(KDouble)][445] = 1258;
		parsx_table[parsx_token(Identifier)][445] = 1259;
		parsx_table[parsx_token(KString)][445] = 1260;
		parsx_table[parsx_token(KBytes)][445] = 1261;
		parsx_table[parsx_token(OLParen)][445] = 1262;
		parsx_table[parsx_token(KUnit)][445] = 1263;
		parsx_table[parsx_token(KUndef)][445] = 1264;
		parsx_table[parsx_token(KImport)][447] = 1265;
		parsx_table[parsx_token(KAs)][449] = 1266;
		parsx_table[parsx_token(OLBrace)][450] = 1267;
		parsx_table[parsx_token(KNull)][450] = 1268;
		parsx_table[parsx_token(OMult)][450] = 1269;
		parsx_table[parsx_token(Identifier)][450] = 1270;
		parsx_table[parsx_token(OQuote)][450] = 1271;
		parsx_table[parsx_token(StringLiteral)][450] = 1272;
		parsx_table[parsx_token(OVBar)][450] = 1273;
		parsx_table[parsx_token(OLParen)][450] = 1274;
		parsx_table[parsx_token(NumberLiteral)][450] = 1275;
		parsx_table[parsx_token(KTrue)][450] = 1276;
		parsx_table[parsx_token(KUnit)][450] = 1277;
		parsx_table[parsx_token(KFalse)][450] = 1278;
		parsx_table[parsx_token(KEnd)][452] = 1279;
		parsx_table[parsx_token(OMinus)][453] = 1280;
		parsx_table[parsx_token(KMatch)][453] = 1281;
		parsx_table[parsx_token(KNull)][453] = 1282;
		parsx_table[parsx_token(OLBrace)][453] = 1283;
		parsx_table[parsx_token(KIf)][453] = 1284;
		parsx_table[parsx_token(Identifier)][453] = 1285;
		parsx_table[parsx_token(KLambda)][453] = 1286;
		parsx_table[parsx_token(StringLiteral)][453] = 1287;
		parsx_table[parsx_token(KNew)][453] = 1288;
		parsx_table[parsx_token(OLParen)][453] = 1289;
		parsx_table[parsx_token(NumberLiteral)][453] = 1290;
		parsx_table[parsx_token(KTrue)][453] = 1291;
		parsx_table[parsx_token(KUnit)][453] = 1292;
		parsx_table[parsx_token(KNot)][453] = 1293;
		parsx_table[parsx_token(KFalse)][453] = 1294;
		parsx_table[parsx_token(OComma)][454] = 1295;
		parsx_table[parsx_token(KStruct)][455] = 1296;
		parsx_table[parsx_token(KInterface)][455] = 1297;
		parsx_table[parsx_token(KClass)][455] = 1298;
		parsx_table[parsx_token(KEnum)][455] = 1299;
		parsx_table[parsx_token(KImport)][455] = 1300;
		parsx_table[parsx_token(KFunction)][455] = 1301;
		parsx_table[parsx_token(EndOfFile)][455] = 1302;
		parsx_table[parsx_token(KGlobal)][455] = 1303;
		parsx_table[parsx_token(OMult)][458] = 1304;
		parsx_table[parsx_token(OVBar)][458] = 1305;
		parsx_table[parsx_token(KStruct)][461] = 1306;
		parsx_table[parsx_token(KInterface)][461] = 1307;
		parsx_table[parsx_token(KClass)][461] = 1308;
		parsx_table[parsx_token(KEnum)][461] = 1309;
		parsx_table[parsx_token(KFunction)][461] = 1310;
		parsx_table[parsx_token(KGlobal)][461] = 1311;
		parsx_table[parsx_token(KOr)][462] = 1312;
		parsx_table[parsx_token(KAnd)][462] = 1313;
		parsx_table[parsx_token(OColon)][462] = 1314;
		parsx_table[parsx_token(EndOfFile)][463] = 1315;
		parsx_table[parsx_token(OMinus)][465] = 1316;
		parsx_table[parsx_token(KMatch)][465] = 1317;
		parsx_table[parsx_token(KNull)][465] = 1318;
		parsx_table[parsx_token(OLBrace)][465] = 1319;
		parsx_table[parsx_token(KIf)][465] = 1320;
		parsx_table[parsx_token(Identifier)][465] = 1321;
		parsx_table[parsx_token(KLambda)][465] = 1322;
		parsx_table[parsx_token(StringLiteral)][465] = 1323;
		parsx_table[parsx_token(KNew)][465] = 1324;
		parsx_table[parsx_token(OLParen)][465] = 1325;
		parsx_table[parsx_token(NumberLiteral)][465] = 1326;
		parsx_table[parsx_token(KTrue)][465] = 1327;
		parsx_table[parsx_token(KUnit)][465] = 1328;
		parsx_table[parsx_token(KNot)][465] = 1329;
		parsx_table[parsx_token(KFalse)][465] = 1330;
		parsx_table[parsx_token(KAs)][466] = 1331;
		parsx_table[parsx_token(Identifier)][468] = 1332;
		parsx_table[parsx_token(OPeriod)][468] = 1333;
		parsx_table[parsx_token(KWith)][468] = 1334;
		parsx_table[parsx_token(OLT)][469] = 1335;
		parsx_table[parsx_token(OGT)][469] = 1336;
		parsx_table[parsx_token(OLE)][469] = 1337;
		parsx_table[parsx_token(OGE)][469] = 1338;
		parsx_table[parsx_token(OEQ)][469] = 1339;
		parsx_table[parsx_token(ONE)][469] = 1340;
		parsx_table[parsx_token(OQuestion)][470] = 1341;
		parsx_table[parsx_token(OConcat)][471] = 1342;
		parsx_table[parsx_max_token_id + 2][1] = -1;
		parsx_table[parsx_max_token_id + 2][2] = -2;
		parsx_table[parsx_max_token_id + 2][3] = -3;
		parsx_table[parsx_max_token_id + 2][4] = -4;
		parsx_table[parsx_max_token_id + 2][5] = -5;
		parsx_table[parsx_max_token_id + 2][6] = -6;
		parsx_table[parsx_max_token_id + 2][7] = -7;
		parsx_table[parsx_max_token_id + 2][8] = -8;
		parsx_table[parsx_max_token_id + 2][9] = -9;
		parsx_table[parsx_max_token_id + 2][10] = -10;
		parsx_table[parsx_max_token_id + 2][11] = -11;
		parsx_table[parsx_max_token_id + 2][12] = -12;
		parsx_table[parsx_max_token_id + 2][13] = -13;
		parsx_table[parsx_max_token_id + 2][14] = -14;
		parsx_table[parsx_max_token_id + 2][15] = -15;
		parsx_table[parsx_max_token_id + 2][16] = -16;
		parsx_table[parsx_max_token_id + 2][17] = -17;
		parsx_table[parsx_max_token_id + 2][18] = -18;
		parsx_table[parsx_max_token_id + 2][19] = -19;
		parsx_table[parsx_max_token_id + 2][20] = -20;
		parsx_table[parsx_max_token_id + 2][21] = -21;
		parsx_table[parsx_max_token_id + 2][22] = -22;
		parsx_table[parsx_max_token_id + 2][23] = -23;
		parsx_table[parsx_max_token_id + 2][24] = -24;
		parsx_table[parsx_max_token_id + 2][25] = -25;
		parsx_table[parsx_max_token_id + 2][26] = -26;
		parsx_table[parsx_max_token_id + 2][27] = -27;
		parsx_table[parsx_max_token_id + 2][28] = -28;
		parsx_table[parsx_max_token_id + 2][29] = -29;
		parsx_table[parsx_max_token_id + 2][30] = -30;
		parsx_table[parsx_max_token_id + 2][31] = -31;
		parsx_table[parsx_max_token_id + 2][32] = -32;
		parsx_table[parsx_max_token_id + 2][33] = -33;
		parsx_table[parsx_max_token_id + 2][34] = -34;
		parsx_table[parsx_max_token_id + 2][35] = -35;
		parsx_table[parsx_max_token_id + 2][36] = -36;
		parsx_table[parsx_max_token_id + 2][37] = -37;
		parsx_table[parsx_max_token_id + 2][38] = -38;
		parsx_table[parsx_max_token_id + 2][39] = -39;
		parsx_table[parsx_max_token_id + 2][40] = -40;
		parsx_table[parsx_max_token_id + 2][41] = -41;
		parsx_table[parsx_max_token_id + 2][42] = -42;
		parsx_table[parsx_max_token_id + 2][43] = -43;
		parsx_table[parsx_max_token_id + 2][44] = -44;
		parsx_table[parsx_max_token_id + 2][45] = -45;
		parsx_table[parsx_max_token_id + 2][46] = -46;
		parsx_table[parsx_max_token_id + 2][47] = -47;
		parsx_table[parsx_max_token_id + 2][48] = -48;
		parsx_table[parsx_max_token_id + 2][49] = -49;
		parsx_table[parsx_max_token_id + 2][50] = -50;
		parsx_table[parsx_max_token_id + 2][51] = -51;
		parsx_table[parsx_max_token_id + 2][52] = -52;
		parsx_table[parsx_max_token_id + 2][53] = -53;
		parsx_table[parsx_max_token_id + 2][54] = -54;
		parsx_table[parsx_max_token_id + 2][55] = -55;
		parsx_table[parsx_max_token_id + 2][56] = -56;
		parsx_table[parsx_max_token_id + 2][57] = -57;
		parsx_table[parsx_max_token_id + 2][58] = -58;
		parsx_table[parsx_max_token_id + 2][59] = -59;
		parsx_table[parsx_max_token_id + 2][60] = -60;
		parsx_table[parsx_max_token_id + 2][61] = -61;
		parsx_table[parsx_max_token_id + 2][62] = -62;
		parsx_table[parsx_max_token_id + 2][63] = -63;
		parsx_table[parsx_max_token_id + 2][64] = -64;
		parsx_table[parsx_max_token_id + 2][65] = -65;
		parsx_table[parsx_max_token_id + 2][66] = -66;
		parsx_table[parsx_max_token_id + 2][67] = -67;
		parsx_table[parsx_max_token_id + 2][68] = -68;
		parsx_table[parsx_max_token_id + 2][69] = -69;
		parsx_table[parsx_max_token_id + 2][70] = -70;
		parsx_table[parsx_max_token_id + 2][71] = -71;
		parsx_table[parsx_max_token_id + 2][72] = -72;
		parsx_table[parsx_max_token_id + 2][73] = -73;
		parsx_table[parsx_max_token_id + 2][74] = -74;
		parsx_table[parsx_max_token_id + 2][75] = -75;
		parsx_table[parsx_max_token_id + 2][76] = -76;
		parsx_table[parsx_max_token_id + 2][77] = -77;
		parsx_table[parsx_max_token_id + 2][78] = -78;
		parsx_table[parsx_max_token_id + 2][79] = -79;
		parsx_table[parsx_max_token_id + 2][80] = -80;
		parsx_table[parsx_max_token_id + 2][81] = -81;
		parsx_table[parsx_max_token_id + 2][82] = -82;
		parsx_table[parsx_max_token_id + 2][83] = -83;
		parsx_table[parsx_max_token_id + 2][84] = -84;
		parsx_table[parsx_max_token_id + 2][85] = -85;
		parsx_table[parsx_max_token_id + 2][86] = -86;
		parsx_table[parsx_max_token_id + 2][87] = -87;
		parsx_table[parsx_max_token_id + 2][88] = -88;
		parsx_table[parsx_max_token_id + 2][89] = -89;
		parsx_table[parsx_max_token_id + 2][90] = -90;
		parsx_table[parsx_max_token_id + 2][91] = -91;
		parsx_table[parsx_max_token_id + 2][92] = -92;
		parsx_table[parsx_max_token_id + 2][93] = -93;
		parsx_table[parsx_max_token_id + 2][94] = -94;
		parsx_table[parsx_max_token_id + 2][95] = -95;
		parsx_table[parsx_max_token_id + 2][96] = -96;
		parsx_table[parsx_max_token_id + 2][97] = -97;
		parsx_table[parsx_max_token_id + 2][98] = -98;
		parsx_table[parsx_max_token_id + 2][99] = -99;
		parsx_table[parsx_max_token_id + 2][100] = -100;
		parsx_table[parsx_max_token_id + 2][101] = -101;
		parsx_table[parsx_max_token_id + 2][102] = -102;
		parsx_table[parsx_max_token_id + 2][103] = -103;
		parsx_table[parsx_max_token_id + 2][104] = -104;
		parsx_table[parsx_max_token_id + 2][105] = -105;
		parsx_table[parsx_max_token_id + 2][106] = -106;
		parsx_table[parsx_max_token_id + 2][107] = -107;
		parsx_table[parsx_max_token_id + 2][108] = -108;
		parsx_table[parsx_max_token_id + 2][109] = -109;
		parsx_table[parsx_max_token_id + 2][110] = -110;
		parsx_table[parsx_max_token_id + 2][111] = -111;
		parsx_table[parsx_max_token_id + 2][112] = -112;
		parsx_table[parsx_max_token_id + 2][113] = -113;
		parsx_table[parsx_max_token_id + 2][114] = -114;
		parsx_table[parsx_max_token_id + 2][115] = -115;
		parsx_table[parsx_max_token_id + 2][116] = -116;
		parsx_table[parsx_max_token_id + 2][117] = -117;
		parsx_table[parsx_max_token_id + 2][118] = -118;
		parsx_table[parsx_max_token_id + 2][119] = -119;
		parsx_table[parsx_max_token_id + 2][120] = -120;
		parsx_table[parsx_max_token_id + 2][121] = -121;
		parsx_table[parsx_max_token_id + 2][122] = -122;
		parsx_table[parsx_max_token_id + 2][123] = -123;
		parsx_table[parsx_max_token_id + 2][124] = -124;
		parsx_table[parsx_max_token_id + 2][125] = -125;
		parsx_table[parsx_max_token_id + 2][126] = -126;
		parsx_table[parsx_max_token_id + 2][127] = -127;
		parsx_table[parsx_max_token_id + 2][128] = -128;
		parsx_table[parsx_max_token_id + 2][129] = -129;
		parsx_table[parsx_max_token_id + 2][130] = -130;
		parsx_table[parsx_max_token_id + 2][131] = -131;
		parsx_table[parsx_max_token_id + 2][132] = -132;
		parsx_table[parsx_max_token_id + 2][133] = -133;
		parsx_table[parsx_max_token_id + 2][134] = -134;
		parsx_table[parsx_max_token_id + 2][135] = -135;
		parsx_table[parsx_max_token_id + 2][136] = -136;
		parsx_table[parsx_max_token_id + 2][137] = -137;
		parsx_table[parsx_max_token_id + 2][138] = -138;
		parsx_table[parsx_max_token_id + 2][139] = -139;
		parsx_table[parsx_max_token_id + 2][140] = -140;
		parsx_table[parsx_max_token_id + 2][141] = -141;
		parsx_table[parsx_max_token_id + 2][142] = -142;
		parsx_table[parsx_max_token_id + 2][143] = -143;
		parsx_table[parsx_max_token_id + 2][144] = -144;
		parsx_table[parsx_max_token_id + 2][145] = -145;
		parsx_table[parsx_max_token_id + 2][146] = -146;
		parsx_table[parsx_max_token_id + 2][147] = -147;
		parsx_table[parsx_max_token_id + 2][148] = -148;
		parsx_table[parsx_max_token_id + 2][149] = -149;
		parsx_table[parsx_max_token_id + 2][150] = -150;
		parsx_table[parsx_max_token_id + 2][151] = -151;
		parsx_table[parsx_max_token_id + 2][152] = -152;
		parsx_table[parsx_max_token_id + 2][153] = -153;
		parsx_table[parsx_max_token_id + 2][154] = -154;
		parsx_table[parsx_max_token_id + 2][155] = -155;
		parsx_table[parsx_max_token_id + 2][156] = -156;
		parsx_table[parsx_max_token_id + 2][157] = -157;
		parsx_table[parsx_max_token_id + 2][158] = -158;
		parsx_table[parsx_max_token_id + 2][159] = -159;
		parsx_table[parsx_max_token_id + 2][160] = -160;
		parsx_table[parsx_max_token_id + 2][161] = -161;
		parsx_table[parsx_max_token_id + 2][162] = -162;
		parsx_table[parsx_max_token_id + 2][163] = -163;
		parsx_table[parsx_max_token_id + 2][164] = -164;
		parsx_table[parsx_max_token_id + 2][165] = -165;
		parsx_table[parsx_max_token_id + 2][166] = -166;
		parsx_table[parsx_max_token_id + 2][167] = -167;
		parsx_table[parsx_max_token_id + 2][168] = -168;
		parsx_table[parsx_max_token_id + 2][169] = -169;
		parsx_table[parsx_max_token_id + 2][170] = -170;
		parsx_table[parsx_max_token_id + 2][171] = -171;
		parsx_table[parsx_max_token_id + 2][172] = -172;
		parsx_table[parsx_max_token_id + 2][173] = -173;
		parsx_table[parsx_max_token_id + 2][174] = -174;
		parsx_table[parsx_max_token_id + 2][175] = -175;
		parsx_table[parsx_max_token_id + 2][176] = -176;
		parsx_table[parsx_max_token_id + 2][177] = -177;
		parsx_table[parsx_max_token_id + 2][178] = -178;
		parsx_table[parsx_max_token_id + 2][179] = -179;
		parsx_table[parsx_max_token_id + 2][180] = -180;
		parsx_table[parsx_max_token_id + 2][181] = -181;
		parsx_table[parsx_max_token_id + 2][182] = -182;
		parsx_table[parsx_max_token_id + 2][183] = -183;
		parsx_table[parsx_max_token_id + 2][184] = -184;
		parsx_table[parsx_max_token_id + 2][185] = -185;
		parsx_table[parsx_max_token_id + 2][186] = -186;
		parsx_table[parsx_max_token_id + 2][187] = -187;
		parsx_table[parsx_max_token_id + 2][188] = -188;
		parsx_table[parsx_max_token_id + 2][189] = -189;
		parsx_table[parsx_max_token_id + 2][190] = -190;
		parsx_table[parsx_max_token_id + 2][191] = -191;
		parsx_table[parsx_max_token_id + 2][192] = -192;
		parsx_table[parsx_max_token_id + 2][193] = -193;
		parsx_table[parsx_max_token_id + 2][194] = -194;
		parsx_table[parsx_max_token_id + 2][195] = -195;
		parsx_table[parsx_max_token_id + 2][196] = -196;
		parsx_table[parsx_max_token_id + 2][197] = -197;
		parsx_table[parsx_max_token_id + 2][198] = -198;
		parsx_table[parsx_max_token_id + 2][199] = -199;
		parsx_table[parsx_max_token_id + 2][200] = -200;
		parsx_table[parsx_max_token_id + 2][201] = -201;
		parsx_table[parsx_max_token_id + 2][202] = -202;
		parsx_table[parsx_max_token_id + 2][203] = -203;
		parsx_table[parsx_max_token_id + 2][204] = -204;
		parsx_table[parsx_max_token_id + 2][205] = -205;
		parsx_table[parsx_max_token_id + 2][206] = -206;
		parsx_table[parsx_max_token_id + 2][207] = -207;
		parsx_table[parsx_max_token_id + 2][208] = -208;
		parsx_table[parsx_max_token_id + 2][209] = -209;
		parsx_table[parsx_max_token_id + 2][210] = -210;
		parsx_table[parsx_max_token_id + 2][211] = -211;
		parsx_table[parsx_max_token_id + 2][212] = -212;
		parsx_table[parsx_max_token_id + 2][213] = -213;
		parsx_table[parsx_max_token_id + 2][214] = -214;
		parsx_table[parsx_max_token_id + 2][215] = -215;
		parsx_table[parsx_max_token_id + 2][216] = -216;
		parsx_table[parsx_max_token_id + 2][217] = -217;
		parsx_table[parsx_max_token_id + 2][218] = -218;
		parsx_table[parsx_max_token_id + 2][219] = -219;
		parsx_table[parsx_max_token_id + 2][220] = -220;
		parsx_table[parsx_max_token_id + 2][221] = -221;
		parsx_table[parsx_max_token_id + 2][222] = -222;
		parsx_table[parsx_max_token_id + 2][223] = -223;
		parsx_table[parsx_max_token_id + 2][224] = -224;
		parsx_table[parsx_max_token_id + 2][225] = -225;
		parsx_table[parsx_max_token_id + 2][226] = -226;
		parsx_table[parsx_max_token_id + 2][227] = -227;
		parsx_table[parsx_max_token_id + 2][228] = -228;
		parsx_table[parsx_max_token_id + 2][229] = -229;
		parsx_table[parsx_max_token_id + 2][230] = -230;
		parsx_table[parsx_max_token_id + 2][231] = -231;
		parsx_table[parsx_max_token_id + 2][232] = -232;
		parsx_table[parsx_max_token_id + 2][233] = -233;
		parsx_table[parsx_max_token_id + 2][234] = -234;
		parsx_table[parsx_max_token_id + 2][235] = -235;
		parsx_table[parsx_max_token_id + 2][236] = -236;
		parsx_table[parsx_max_token_id + 2][237] = -237;
		parsx_table[parsx_max_token_id + 2][238] = -238;
		parsx_table[parsx_max_token_id + 2][239] = -239;
		parsx_table[parsx_max_token_id + 2][240] = -240;
		parsx_table[parsx_max_token_id + 2][241] = -241;
		parsx_table[parsx_max_token_id + 2][242] = -242;
		parsx_table[parsx_max_token_id + 2][243] = -243;
		parsx_table[parsx_max_token_id + 2][244] = -244;
		parsx_table[parsx_max_token_id + 2][245] = -245;
		parsx_table[parsx_max_token_id + 2][246] = -246;
		parsx_table[parsx_max_token_id + 2][247] = -247;
		parsx_table[parsx_max_token_id + 2][248] = -248;
		parsx_table[parsx_max_token_id + 2][249] = -249;
		parsx_table[parsx_max_token_id + 2][250] = -250;
		parsx_table[parsx_max_token_id + 2][251] = -251;
		parsx_table[parsx_max_token_id + 2][252] = -252;
		parsx_table[parsx_max_token_id + 2][253] = -253;
		parsx_table[parsx_max_token_id + 2][254] = -254;
		parsx_table[parsx_max_token_id + 2][255] = -255;
		parsx_table[parsx_max_token_id + 2][256] = -256;
		parsx_table[parsx_max_token_id + 2][257] = -257;
		parsx_table[parsx_max_token_id + 2][258] = -258;
		parsx_table[parsx_max_token_id + 2][259] = -259;
		parsx_table[parsx_max_token_id + 2][260] = -260;
		parsx_table[parsx_max_token_id + 2][261] = -261;
		parsx_table[parsx_max_token_id + 2][262] = -262;
		parsx_table[parsx_max_token_id + 2][263] = -263;
		parsx_table[parsx_max_token_id + 2][264] = -264;
		parsx_table[parsx_max_token_id + 2][265] = -265;
		parsx_table[parsx_max_token_id + 2][266] = -266;
		parsx_table[parsx_max_token_id + 2][267] = -267;
		parsx_table[parsx_max_token_id + 2][268] = -268;
		parsx_table[parsx_max_token_id + 2][269] = -269;
		parsx_table[parsx_max_token_id + 2][270] = -270;
		parsx_table[parsx_max_token_id + 2][271] = -271;
		parsx_table[parsx_max_token_id + 2][272] = -272;
		parsx_table[parsx_max_token_id + 2][273] = -273;
		parsx_table[parsx_max_token_id + 2][274] = -274;
		parsx_table[parsx_max_token_id + 2][275] = -275;
		parsx_table[parsx_max_token_id + 2][276] = -276;
		parsx_table[parsx_max_token_id + 2][277] = -277;
		parsx_table[parsx_max_token_id + 2][278] = -278;
		parsx_table[parsx_max_token_id + 2][279] = -279;
		parsx_table[parsx_max_token_id + 2][280] = -280;
		parsx_table[parsx_max_token_id + 2][281] = -281;
		parsx_table[parsx_max_token_id + 2][282] = -282;
		parsx_table[parsx_max_token_id + 2][283] = -283;
		parsx_table[parsx_max_token_id + 2][284] = -284;
		parsx_table[parsx_max_token_id + 2][285] = -285;
		parsx_table[parsx_max_token_id + 2][286] = -286;
		parsx_table[parsx_max_token_id + 2][287] = -287;
		parsx_table[parsx_max_token_id + 2][288] = -288;
		parsx_table[parsx_max_token_id + 2][289] = -289;
		parsx_table[parsx_max_token_id + 2][290] = -290;
		parsx_table[parsx_max_token_id + 2][291] = -291;
		parsx_table[parsx_max_token_id + 2][292] = -292;
		parsx_table[parsx_max_token_id + 2][293] = -293;
		parsx_table[parsx_max_token_id + 2][294] = -294;
		parsx_table[parsx_max_token_id + 2][295] = -295;
		parsx_table[parsx_max_token_id + 2][296] = -296;
		parsx_table[parsx_max_token_id + 2][297] = -297;
		parsx_table[parsx_max_token_id + 2][298] = -298;
		parsx_table[parsx_max_token_id + 2][299] = -299;
		parsx_table[parsx_max_token_id + 2][300] = -300;
		parsx_table[parsx_max_token_id + 2][301] = -301;
		parsx_table[parsx_max_token_id + 2][302] = -302;
		parsx_table[parsx_max_token_id + 2][303] = -303;
		parsx_table[parsx_max_token_id + 2][304] = -304;
		parsx_table[parsx_max_token_id + 2][305] = -305;
		parsx_table[parsx_max_token_id + 2][306] = -306;
		parsx_table[parsx_max_token_id + 2][307] = -307;
		parsx_table[parsx_max_token_id + 2][308] = -308;
		parsx_table[parsx_max_token_id + 2][309] = -309;
		parsx_table[parsx_max_token_id + 2][310] = -310;
		parsx_table[parsx_max_token_id + 2][311] = -311;
		parsx_table[parsx_max_token_id + 2][312] = -312;
		parsx_table[parsx_max_token_id + 2][313] = -313;
		parsx_table[parsx_max_token_id + 2][314] = -314;
		parsx_table[parsx_max_token_id + 2][315] = -315;
		parsx_table[parsx_max_token_id + 2][316] = -316;
		parsx_table[parsx_max_token_id + 2][317] = -317;
		parsx_table[parsx_max_token_id + 2][318] = -318;
		parsx_table[parsx_max_token_id + 2][319] = -319;
		parsx_table[parsx_max_token_id + 2][320] = -320;
		parsx_table[parsx_max_token_id + 2][321] = -321;
		parsx_table[parsx_max_token_id + 2][322] = -322;
		parsx_table[parsx_max_token_id + 2][323] = -323;
		parsx_table[parsx_max_token_id + 2][324] = -324;
		parsx_table[parsx_max_token_id + 2][325] = -325;
		parsx_table[parsx_max_token_id + 2][326] = -326;
		parsx_table[parsx_max_token_id + 2][327] = -327;
		parsx_table[parsx_max_token_id + 2][328] = -328;
		parsx_table[parsx_max_token_id + 2][329] = -329;
		parsx_table[parsx_max_token_id + 2][330] = -330;
		parsx_table[parsx_max_token_id + 2][331] = -331;
		parsx_table[parsx_max_token_id + 2][332] = -332;
		parsx_table[parsx_max_token_id + 2][333] = -333;
		parsx_table[parsx_max_token_id + 2][334] = -334;
		parsx_table[parsx_max_token_id + 2][335] = -335;
		parsx_table[parsx_max_token_id + 2][336] = -336;
		parsx_table[parsx_max_token_id + 2][337] = -337;
		parsx_table[parsx_max_token_id + 2][338] = -338;
		parsx_table[parsx_max_token_id + 2][339] = -339;
		parsx_table[parsx_max_token_id + 2][340] = -340;
		parsx_table[parsx_max_token_id + 2][341] = -341;
		parsx_table[parsx_max_token_id + 2][342] = -342;
		parsx_table[parsx_max_token_id + 2][343] = -343;
		parsx_table[parsx_max_token_id + 2][344] = -344;
		parsx_table[parsx_max_token_id + 2][345] = -345;
		parsx_table[parsx_max_token_id + 2][346] = -346;
		parsx_table[parsx_max_token_id + 2][347] = -347;
		parsx_table[parsx_max_token_id + 2][348] = -348;
		parsx_table[parsx_max_token_id + 2][349] = -349;
		parsx_table[parsx_max_token_id + 2][350] = -350;
		parsx_table[parsx_max_token_id + 2][351] = -351;
		parsx_table[parsx_max_token_id + 2][352] = -352;
		parsx_table[parsx_max_token_id + 2][353] = -353;
		parsx_table[parsx_max_token_id + 2][354] = -354;
		parsx_table[parsx_max_token_id + 2][355] = -355;
		parsx_table[parsx_max_token_id + 2][356] = -356;
		parsx_table[parsx_max_token_id + 2][357] = -357;
		parsx_table[parsx_max_token_id + 2][358] = -358;
		parsx_table[parsx_max_token_id + 2][359] = -359;
		parsx_table[parsx_max_token_id + 2][360] = -360;
		parsx_table[parsx_max_token_id + 2][361] = -361;
		parsx_table[parsx_max_token_id + 2][362] = -362;
		parsx_table[parsx_max_token_id + 2][363] = -363;
		parsx_table[parsx_max_token_id + 2][364] = -364;
		parsx_table[parsx_max_token_id + 2][365] = -365;
		parsx_table[parsx_max_token_id + 2][366] = -366;
		parsx_table[parsx_max_token_id + 2][367] = -367;
		parsx_table[parsx_max_token_id + 2][368] = -368;
		parsx_table[parsx_max_token_id + 2][369] = -369;
		parsx_table[parsx_max_token_id + 2][370] = -370;
		parsx_table[parsx_max_token_id + 2][371] = -371;
		parsx_table[parsx_max_token_id + 2][372] = -372;
		parsx_table[parsx_max_token_id + 2][373] = -373;
		parsx_table[parsx_max_token_id + 2][374] = -374;
		parsx_table[parsx_max_token_id + 2][375] = -375;
		parsx_table[parsx_max_token_id + 2][376] = -376;
		parsx_table[parsx_max_token_id + 2][377] = -377;
		parsx_table[parsx_max_token_id + 2][378] = -378;
		parsx_table[parsx_max_token_id + 2][379] = -379;
		parsx_table[parsx_max_token_id + 2][380] = -380;
		parsx_table[parsx_max_token_id + 2][381] = -381;
		parsx_table[parsx_max_token_id + 2][382] = -382;
		parsx_table[parsx_max_token_id + 2][383] = -383;
		parsx_table[parsx_max_token_id + 2][384] = -384;
		parsx_table[parsx_max_token_id + 2][385] = -385;
		parsx_table[parsx_max_token_id + 2][386] = -386;
		parsx_table[parsx_max_token_id + 2][387] = -387;
		parsx_table[parsx_max_token_id + 2][388] = -388;
		parsx_table[parsx_max_token_id + 2][389] = -389;
		parsx_table[parsx_max_token_id + 2][390] = -390;
		parsx_table[parsx_max_token_id + 2][391] = -391;
		parsx_table[parsx_max_token_id + 2][392] = -392;
		parsx_table[parsx_max_token_id + 2][393] = -393;
		parsx_table[parsx_max_token_id + 2][394] = -394;
		parsx_table[parsx_max_token_id + 2][395] = -395;
		parsx_table[parsx_max_token_id + 2][396] = -396;
		parsx_table[parsx_max_token_id + 2][397] = -397;
		parsx_table[parsx_max_token_id + 2][398] = -398;
		parsx_table[parsx_max_token_id + 2][399] = -399;
		parsx_table[parsx_max_token_id + 2][400] = -400;
		parsx_table[parsx_max_token_id + 2][401] = -401;
		parsx_table[parsx_max_token_id + 2][402] = -402;
		parsx_table[parsx_max_token_id + 2][403] = -403;
		parsx_table[parsx_max_token_id + 2][404] = -404;
		parsx_table[parsx_max_token_id + 2][405] = -405;
		parsx_table[parsx_max_token_id + 2][406] = -406;
		parsx_table[parsx_max_token_id + 2][407] = -407;
		parsx_table[parsx_max_token_id + 2][408] = -408;
		parsx_table[parsx_max_token_id + 2][409] = -409;
		parsx_table[parsx_max_token_id + 2][410] = -410;
		parsx_table[parsx_max_token_id + 2][411] = -411;
		parsx_table[parsx_max_token_id + 2][412] = -412;
		parsx_table[parsx_max_token_id + 2][413] = -413;
		parsx_table[parsx_max_token_id + 2][414] = -414;
		parsx_table[parsx_max_token_id + 2][415] = -415;
		parsx_table[parsx_max_token_id + 2][416] = -416;
		parsx_table[parsx_max_token_id + 2][417] = -417;
		parsx_table[parsx_max_token_id + 2][418] = -418;
		parsx_table[parsx_max_token_id + 2][419] = -419;
		parsx_table[parsx_max_token_id + 2][420] = -420;
		parsx_table[parsx_max_token_id + 2][421] = -421;
		parsx_table[parsx_max_token_id + 2][422] = -422;
		parsx_table[parsx_max_token_id + 2][423] = -423;
		parsx_table[parsx_max_token_id + 2][424] = -424;
		parsx_table[parsx_max_token_id + 2][425] = -425;
		parsx_table[parsx_max_token_id + 2][426] = -426;
		parsx_table[parsx_max_token_id + 2][427] = -427;
		parsx_table[parsx_max_token_id + 2][428] = -428;
		parsx_table[parsx_max_token_id + 2][429] = -429;
		parsx_table[parsx_max_token_id + 2][430] = -430;
		parsx_table[parsx_max_token_id + 2][431] = -431;
		parsx_table[parsx_max_token_id + 2][432] = -432;
		parsx_table[parsx_max_token_id + 2][433] = -433;
		parsx_table[parsx_max_token_id + 2][434] = -434;
		parsx_table[parsx_max_token_id + 2][435] = -435;
		parsx_table[parsx_max_token_id + 2][436] = -436;
		parsx_table[parsx_max_token_id + 2][437] = -437;
		parsx_table[parsx_max_token_id + 2][438] = -438;
		parsx_table[parsx_max_token_id + 2][439] = -439;
		parsx_table[parsx_max_token_id + 2][440] = -440;
		parsx_table[parsx_max_token_id + 2][441] = -441;
		parsx_table[parsx_max_token_id + 2][442] = -442;
		parsx_table[parsx_max_token_id + 2][443] = -443;
		parsx_table[parsx_max_token_id + 2][444] = -444;
		parsx_table[parsx_max_token_id + 2][445] = -445;
		parsx_table[parsx_max_token_id + 2][446] = -446;
		parsx_table[parsx_max_token_id + 2][447] = -447;
		parsx_table[parsx_max_token_id + 2][448] = -448;
		parsx_table[parsx_max_token_id + 2][449] = -449;
		parsx_table[parsx_max_token_id + 2][450] = -450;
		parsx_table[parsx_max_token_id + 2][451] = -451;
		parsx_table[parsx_max_token_id + 2][452] = -452;
		parsx_table[parsx_max_token_id + 2][453] = -453;
		parsx_table[parsx_max_token_id + 2][454] = -454;
		parsx_table[parsx_max_token_id + 2][455] = -455;
		parsx_table[parsx_max_token_id + 2][456] = -456;
		parsx_table[parsx_max_token_id + 2][457] = -457;
		parsx_table[parsx_max_token_id + 2][458] = -458;
		parsx_table[parsx_max_token_id + 2][459] = -459;
		parsx_table[parsx_max_token_id + 2][460] = -460;
		parsx_table[parsx_max_token_id + 2][461] = -461;
		parsx_table[parsx_max_token_id + 2][462] = -462;
		parsx_table[parsx_max_token_id + 2][463] = -463;
		parsx_table[parsx_max_token_id + 2][464] = -464;
		parsx_table[parsx_max_token_id + 2][465] = -465;
		parsx_table[parsx_max_token_id + 2][466] = -466;
		parsx_table[parsx_max_token_id + 2][467] = -467;
		parsx_table[parsx_max_token_id + 2][468] = -468;
		parsx_table[parsx_max_token_id + 2][469] = -469;
		parsx_table[parsx_max_token_id + 2][470] = -470;
		parsx_table[parsx_max_token_id + 2][471] = -471;
	}};
	const parsx_parse_table_gen parsx_init_table;
	const short parsx_rule_state_table[] = {
		1, 0, 
		2, 0, 
		3, 0, 
		4, 0, 
		5, 0, 
		6, 0, 
		7, 0, 
		8, 0, 
		9, 0, 
		10, 0, 
		11, 0, 
		12, 0, 
		13, 0, 
		14, 0, 
		15, 0, 
		16, 0, 
		17, 0, 
		19, 0, 
		20, 0, 
		22, 0, 
		23, 0, 
		24, 0, 
		26, 0, 
		27, 0, 
		28, 0, 
		29, 0, 
		30, 0, 
		31, 0, 
		32, 0, 
		33, 0, 
		34, 0, 
		35, 0, 
		36, 0, 
		37, 0, 
		38, 0, 
		39, 0, 
		40, 0, 
		41, 0, 
		42, 0, 
		43, 0, 
		44, 0, 
		48, 0, 
		49, 0, 
		50, 0, 
		51, 0, 
		52, 0, 
		54, 0, 
		56, 0, 
		57, 0, 
		58, 0, 
		59, 0, 
		60, 0, 
		61, 0, 
		64, 0, 
		65, 0, 
		66, 0, 
		67, 0, 
		68, 0, 
		70, 0, 
		71, 0, 
		73, 0, 
		74, 0, 
		75, 0, 
		82, 0, 
		83, 0, 
		84, 0, 
		91, 0, 
		94, 0, 
		95, 0, 
		96, 0, 
		97, 0, 
		98, 0, 
		101, 0, 
		102, 0, 
		103, 0, 
		104, 0, 
		105, 0, 
		106, 0, 
		107, 0, 
		108, 0, 
		109, 0, 
		110, 0, 
		111, 0, 
		112, 0, 
		113, 0, 
		114, 0, 
		115, 0, 
		116, 0, 
		117, 0, 
		118, 0, 
		119, 0, 
		120, 0, 
		121, 0, 
		122, 0, 
		123, 0, 
		124, 0, 
		125, 0, 
		126, 0, 
		127, 0, 
		128, 0, 
		129, 0, 
		130, 0, 
		131, 0, 
		132, 0, 
		133, 0, 
		134, 0, 
		135, 0, 
		136, 0, 
		137, 0, 
		138, 0, 
		139, 0, 
		140, 0, 
		141, 0, 
		142, 0, 
		144, 0, 
		147, 0, 
		149, 0, 
		150, 0, 
		152, 0, 
		153, 0, 
		155, 0, 
		156, 0, 
		157, 0, 
		159, 0, 
		160, 0, 
		161, 0, 
		163, 0, 
		164, 0, 
		165, 0, 
		166, 0, 
		168, 0, 
		169, 0, 
		170, 0, 
		171, 0, 
		173, 0, 
		174, 0, 
		175, 0, 
		176, 0, 
		177, 0, 
		178, 0, 
		179, 0, 
		180, 0, 
		181, 0, 
		182, 0, 
		183, 0, 
		184, 0, 
		186, 0, 
		187, 0, 
		188, 0, 
		190, 0, 
		191, 0, 
		192, 0, 
		193, 0, 
		194, 0, 
		195, 0, 
		196, 0, 
		197, 0, 
		199, 0, 
		200, 0, 
		201, 0, 
		202, 0, 
		203, 0, 
		204, 0, 
		205, 0, 
		206, 0, 
		208, 0, 
		210, 0, 
		211, 0, 
		212, 0, 
		213, 0, 
		214, 0, 
		215, 0, 
		216, 0, 
		217, 0, 
		218, 0, 
		219, 0, 
		220, 0, 
		221, 0, 
		222, 0, 
		224, 0, 
		225, 0, 
		226, 0, 
		227, 0, 
		228, 0, 
		229, 0, 
		231, 0, 
		233, 0, 
		234, 0, 
		235, 0, 
		237, 0, 
		238, 0, 
		239, 0, 
		240, 0, 
		242, 0, 
		243, 0, 
		244, 0, 
		245, 0, 
		246, 0, 
		247, 0, 
		248, 0, 
		250, 0, 
		252, 0, 
		253, 0, 
		255, 0, 
		256, 0, 
		257, 0, 
		258, 0, 
		259, 0, 
		260, 0, 
		262, 0, 
		263, 0, 
		264, 0, 
		265, 0, 
		267, 0, 
		268, 0, 
		270, 0, 
		271, 0, 
		272, 0, 
		273, 0, 
		274, 0, 
		275, 0, 
		276, 0, 
		277, 0, 
		278, 0, 
		279, 0, 
		280, 0, 
		281, 0, 
		282, 0, 
		283, 0, 
		284, 0, 
		285, 0, 
		286, 0, 
		287, 0, 
		288, 0, 
		290, 0, 
		291, 0, 
		292, 0, 
		294, 0, 
		295, 0, 
		296, 0, 
		297, 0, 
		299, 0, 
		300, 0, 
		301, 0, 
		302, 0, 
		303, 0, 
		304, 0, 
		305, 0, 
		306, 0, 
		307, 0, 
		308, 0, 
		309, 0, 
		310, 0, 
		311, 0, 
		312, 0, 
		313, 0, 
		314, 0, 
		315, 0, 
		316, 0, 
		317, 0, 
		319, 0, 
		320, 0, 
		322, 0, 
		323, 0, 
		324, 0, 
		325, 0, 
		326, 0, 
		328, 0, 
		329, 0, 
		331, 0, 
		332, 0, 
		333, 0, 
		334, 0, 
		335, 0, 
		336, 0, 
		337, 0, 
		338, 0, 
		339, 0, 
		340, 0, 
		341, 0, 
		342, 0, 
		343, 0, 
		344, 0, 
		345, 0, 
		346, 0, 
		347, 0, 
		348, 0, 
		349, 0, 
		350, 0, 
		351, 0, 
		352, 0, 
		353, 0, 
		354, 0, 
		355, 0, 
		357, 0, 
		358, 0, 
		359, 0, 
		360, 0, 
		361, 0, 
		362, 0, 
		363, 0, 
		364, 0, 
		365, 0, 
		368, 0, 
		369, 0, 
		370, 0, 
		371, 0, 
		372, 0, 
		376, 0, 
		377, 0, 
		378, 0, 
		380, 0, 
		381, 0, 
		382, 0, 
		384, 0, 
		385, 0, 
		386, 0, 
		387, 0, 
		388, 0, 
		389, 0, 
		390, 0, 
		391, 0, 
		393, 0, 
		394, 0, 
		396, 0, 
		397, 0, 
		398, 0, 
		399, 0, 
		400, 0, 
		402, 0, 
		403, 0, 
		404, 0, 
		405, 0, 
		406, 0, 
		407, 0, 
		408, 0, 
		409, 0, 
		410, 0, 
		411, 0, 
		412, 0, 
		413, 0, 
		414, 0, 
		415, 0, 
		417, 0, 
		418, 0, 
		419, 0, 
		420, 0, 
		421, 0, 
		422, 0, 
		423, 0, 
		424, 0, 
		425, 0, 
		426, 0, 
		427, 0, 
		428, 0, 
		429, 0, 
		430, 0, 
		431, 0, 
		433, 0, 
		434, 0, 
		435, 0, 
		436, 0, 
		437, 0, 
		438, 0, 
		440, 0, 
		441, 0, 
		442, 0, 
		443, 0, 
		446, 0, 
		447, 0, 
		448, 0, 
		449, 0, 
		451, 0, 
		453, 0, 
		454, 0, 
		456, 0, 
		457, 0, 
		459, 0, 
		460, 0, 
		461, 0, 
		462, 0, 
		464, 0, 
		465, 0, 
		466, 0, 
		467, 0, 
		468, 0, 
		469, 0, 
		470, 0, 
		471, 0, 
		2, 394, 45, 0, 
		5, 42, 203, 254, 0, 
		5, 5, 408, 261, 0, 
		5, 42, 372, 375, 0, 
		5, 228, 197, 251, 0, 
		5, 42, 3, 375, 0, 
		5, 42, 368, 375, 0, 
		5, 42, 370, 375, 0, 
		5, 42, 393, 375, 0, 
		5, 228, 194, 53, 0, 
		5, 42, 364, 375, 0, 
		10, 420, 338, 251, 0, 
		10, 10, 353, 254, 0, 
		10, 420, 225, 53, 0, 
		14, 17, 14, 45, 367, 45, 0, 
		14, 19, 45, 0, 
		16, 16, 95, 79, 283, 0, 
		16, 167, 0, 
		18, 20, 21, 140, 0, 
		21, 24, 112, 22, 367, 45, 0, 
		21, 23, 22, 0, 
		22, 413, 238, 422, 159, 116, 254, 0, 
		22, 413, 238, 378, 379, 22, 367, 45, 0, 
		22, 413, 238, 468, 0, 
		22, 413, 238, 422, 159, 361, 79, 45, 0, 
		22, 413, 238, 422, 159, 43, 80, 283, 0, 
		22, 413, 238, 337, 452, 22, 373, 45, 374, 72, 0, 
		22, 413, 238, 144, 452, 22, 373, 45, 0, 
		22, 413, 238, 156, 452, 22, 0, 
		22, 413, 238, 432, 0, 
		22, 413, 238, 160, 185, 89, 327, 0, 
		22, 413, 238, 465, 0, 
		22, 413, 238, 66, 45, 0, 
		22, 413, 238, 246, 45, 0, 
		22, 413, 238, 422, 159, 301, 269, 0, 
		22, 413, 238, 163, 452, 84, 47, 55, 0, 
		22, 413, 238, 114, 45, 383, 22, 0, 
		22, 413, 238, 422, 159, 59, 62, 241, 0, 
		22, 413, 238, 422, 159, 193, 207, 46, 0, 
		22, 413, 238, 422, 159, 117, 0, 
		22, 413, 238, 422, 159, 33, 0, 
		22, 413, 238, 422, 159, 40, 0, 
		22, 413, 238, 422, 159, 142, 0, 
		22, 413, 238, 422, 159, 37, 0, 
		22, 413, 238, 422, 159, 29, 0, 
		22, 413, 238, 422, 159, 31, 0, 
		25, 43, 80, 283, 0, 
		25, 33, 0, 
		25, 40, 0, 
		25, 59, 62, 241, 0, 
		25, 142, 0, 
		25, 193, 207, 46, 0, 
		25, 37, 0, 
		25, 29, 0, 
		25, 117, 0, 
		25, 31, 0, 
		27, 457, 202, 459, 286, 423, 0, 
		32, 260, 221, 266, 0, 
		32, 32, 56, 269, 0, 
		32, 294, 259, 261, 0, 
		32, 32, 58, 269, 0, 
		32, 420, 338, 251, 0, 
		32, 32, 60, 269, 0, 
		32, 10, 250, 375, 0, 
		32, 10, 347, 375, 0, 
		32, 10, 348, 375, 0, 
		32, 10, 256, 375, 0, 
		32, 420, 225, 53, 0, 
		32, 10, 340, 375, 0, 
		32, 10, 353, 254, 0, 
		32, 10, 350, 375, 0, 
		32, 260, 354, 266, 0, 
		36, 61, 41, 79, 283, 78, 0, 
		36, 61, 161, 79, 283, 78, 92, 0, 
		42, 228, 197, 251, 0, 
		42, 42, 203, 254, 0, 
		42, 228, 194, 53, 0, 
		45, 94, 301, 269, 0, 
		45, 94, 111, 452, 314, 47, 55, 0, 
		45, 94, 33, 0, 
		45, 94, 43, 80, 283, 0, 
		45, 94, 109, 99, 45, 367, 45, 0, 
		45, 94, 40, 0, 
		45, 94, 59, 62, 241, 0, 
		45, 94, 142, 0, 
		45, 94, 193, 207, 46, 0, 
		45, 94, 113, 79, 45, 0, 
		45, 94, 37, 0, 
		45, 94, 29, 0, 
		45, 94, 117, 0, 
		45, 94, 116, 254, 0, 
		45, 94, 31, 0, 
		46, 258, 49, 0, 
		47, 0, 
		50, 50, 60, 269, 0, 
		50, 50, 56, 269, 0, 
		50, 50, 58, 269, 0, 
		53, 365, 333, 470, 313, 80, 75, 0, 
		53, 365, 333, 470, 272, 0, 
		53, 365, 333, 470, 274, 0, 
		53, 365, 333, 470, 467, 0, 
		53, 365, 333, 470, 280, 0, 
		53, 365, 333, 470, 288, 271, 311, 0, 
		53, 365, 333, 470, 281, 0, 
		53, 365, 333, 470, 284, 0, 
		53, 365, 330, 0, 
		53, 365, 333, 470, 268, 0, 
		53, 365, 333, 470, 270, 0, 
		55, 396, 295, 294, 428, 299, 301, 269, 0, 
		55, 396, 295, 294, 428, 299, 111, 452, 314, 47, 55, 0, 
		55, 396, 295, 294, 428, 299, 33, 0, 
		55, 396, 295, 294, 428, 299, 43, 80, 283, 0, 
		55, 396, 295, 294, 428, 299, 109, 99, 45, 367, 45, 0, 
		55, 396, 295, 294, 428, 299, 40, 0, 
		55, 396, 295, 294, 428, 299, 59, 62, 241, 0, 
		55, 396, 295, 294, 428, 299, 142, 0, 
		55, 396, 292, 45, 0, 
		55, 396, 295, 294, 428, 299, 193, 207, 46, 0, 
		55, 396, 295, 294, 428, 299, 113, 79, 45, 0, 
		55, 396, 295, 294, 428, 299, 37, 0, 
		55, 396, 295, 294, 428, 299, 29, 0, 
		55, 396, 295, 294, 428, 299, 117, 0, 
		55, 396, 295, 294, 428, 299, 116, 254, 0, 
		55, 396, 295, 294, 428, 299, 31, 0, 
		61, 61, 161, 79, 283, 78, 92, 0, 
		62, 177, 45, 0, 
		62, 164, 452, 413, 238, 422, 159, 116, 254, 0, 
		62, 164, 452, 413, 238, 378, 379, 22, 367, 45, 0, 
		62, 164, 452, 413, 238, 468, 0, 
		62, 164, 452, 413, 238, 422, 159, 361, 79, 45, 0, 
		62, 164, 0, 
		62, 164, 452, 413, 238, 422, 159, 43, 80, 283, 0, 
		62, 164, 452, 413, 238, 337, 452, 22, 373, 45, 374, 72, 0, 
		62, 164, 452, 413, 238, 144, 452, 22, 373, 45, 0, 
		62, 164, 452, 413, 238, 156, 452, 22, 0, 
		62, 164, 452, 413, 238, 432, 0, 
		62, 164, 452, 413, 238, 160, 185, 89, 327, 0, 
		62, 164, 452, 413, 238, 465, 0, 
		62, 164, 452, 413, 238, 66, 45, 0, 
		62, 164, 452, 413, 238, 246, 45, 0, 
		62, 164, 452, 413, 238, 422, 159, 301, 269, 0, 
		62, 164, 452, 413, 238, 163, 452, 84, 47, 55, 0, 
		62, 164, 452, 413, 238, 114, 45, 383, 22, 0, 
		62, 164, 452, 413, 238, 422, 159, 59, 62, 241, 0, 
		62, 164, 452, 413, 238, 422, 159, 193, 207, 46, 0, 
		62, 164, 452, 413, 238, 422, 159, 117, 0, 
		62, 164, 452, 413, 238, 422, 159, 33, 0, 
		62, 164, 452, 413, 238, 422, 159, 40, 0, 
		62, 164, 452, 413, 238, 422, 159, 142, 0, 
		62, 164, 452, 413, 238, 422, 159, 37, 0, 
		62, 164, 452, 413, 238, 422, 159, 29, 0, 
		62, 164, 452, 413, 238, 422, 159, 31, 0, 
		63, 333, 470, 313, 80, 75, 0, 
		63, 333, 470, 272, 0, 
		63, 333, 470, 274, 0, 
		63, 333, 470, 467, 0, 
		63, 333, 470, 280, 0, 
		63, 333, 470, 288, 271, 311, 0, 
		63, 333, 470, 281, 0, 
		63, 333, 470, 284, 0, 
		63, 330, 0, 
		63, 333, 470, 268, 0, 
		63, 333, 470, 270, 0, 
		64, 255, 150, 184, 421, 313, 80, 75, 0, 
		64, 255, 150, 184, 421, 272, 0, 
		64, 255, 150, 184, 421, 274, 0, 
		64, 255, 150, 184, 421, 467, 0, 
		64, 255, 150, 184, 421, 280, 0, 
		64, 255, 150, 110, 0, 
		64, 255, 150, 184, 421, 281, 0, 
		64, 255, 150, 184, 421, 284, 0, 
		64, 255, 150, 184, 365, 330, 0, 
		64, 255, 150, 184, 421, 268, 0, 
		64, 255, 150, 184, 421, 270, 0, 
		67, 67, 201, 266, 0, 
		67, 462, 187, 254, 0, 
		67, 332, 328, 261, 0, 
		67, 462, 229, 375, 0, 
		67, 278, 182, 251, 0, 
		67, 462, 176, 375, 0, 
		67, 462, 170, 375, 0, 
		67, 462, 173, 375, 0, 
		67, 462, 305, 375, 0, 
		67, 278, 180, 53, 0, 
		67, 462, 165, 375, 0, 
		67, 67, 199, 266, 0, 
		69, 184, 421, 313, 80, 75, 0, 
		69, 184, 421, 272, 0, 
		69, 184, 421, 274, 0, 
		69, 184, 421, 467, 0, 
		69, 184, 421, 280, 0, 
		69, 110, 0, 
		69, 184, 421, 281, 0, 
		69, 184, 421, 284, 0, 
		69, 184, 365, 330, 0, 
		69, 184, 421, 268, 0, 
		69, 184, 421, 270, 0, 
		72, 115, 147, 0, 
		75, 454, 304, 421, 313, 80, 75, 0, 
		75, 454, 304, 421, 272, 0, 
		75, 454, 304, 421, 274, 0, 
		75, 454, 304, 421, 467, 0, 
		75, 454, 304, 421, 280, 0, 
		75, 454, 304, 421, 288, 271, 311, 0, 
		75, 454, 304, 421, 281, 0, 
		75, 454, 304, 421, 284, 0, 
		75, 454, 304, 365, 330, 0, 
		75, 454, 304, 421, 268, 0, 
		75, 454, 304, 421, 270, 0, 
		76, 0, 
		77, 0, 
		78, 0, 
		79, 0, 
		80, 0, 
		81, 0, 
		84, 296, 91, 20, 21, 140, 0, 
		85, 0, 
		86, 0, 
		87, 0, 
		88, 0, 
		89, 0, 
		90, 0, 
		92, 0, 
		93, 0, 
		94, 260, 221, 266, 0, 
		94, 32, 56, 269, 0, 
		94, 10, 350, 375, 0, 
		94, 294, 259, 261, 0, 
		94, 32, 58, 269, 0, 
		94, 420, 338, 251, 0, 
		94, 32, 60, 269, 0, 
		94, 10, 250, 375, 0, 
		94, 10, 348, 375, 0, 
		94, 10, 347, 375, 0, 
		94, 32, 189, 0, 
		94, 10, 256, 375, 0, 
		94, 420, 225, 53, 0, 
		94, 10, 340, 375, 0, 
		94, 10, 353, 254, 0, 
		94, 94, 324, 79, 283, 0, 
		94, 260, 354, 266, 0, 
		96, 106, 120, 266, 0, 
		96, 399, 123, 269, 0, 
		96, 322, 118, 261, 0, 
		96, 399, 124, 269, 0, 
		96, 399, 125, 269, 0, 
		96, 399, 162, 0, 
		96, 96, 129, 79, 283, 0, 
		96, 106, 119, 266, 0, 
		99, 312, 99, 45, 367, 45, 0, 
		99, 310, 452, 45, 0, 
		100, 286, 423, 0, 
		106, 106, 120, 266, 0, 
		106, 106, 119, 266, 0, 
		106, 322, 118, 261, 0, 
		110, 71, 53, 77, 115, 107, 0, 
		110, 184, 365, 345, 230, 0, 
		110, 184, 421, 288, 158, 0, 
		110, 184, 235, 273, 331, 63, 0, 
		110, 71, 53, 0, 
		110, 184, 421, 265, 0, 
		112, 26, 112, 22, 367, 45, 0, 
		112, 122, 22, 0, 
		115, 115, 107, 0, 
		132, 132, 282, 45, 0, 
		133, 133, 48, 45, 89, 115, 147, 0, 
		133, 133, 51, 0, 
		140, 303, 7, 466, 441, 80, 140, 0, 
		140, 303, 7, 466, 231, 0, 
		140, 303, 7, 466, 27, 0, 
		140, 303, 7, 466, 290, 0, 
		140, 303, 7, 466, 437, 90, 45, 0, 
		140, 303, 7, 466, 446, 0, 
		140, 303, 7, 466, 457, 202, 436, 243, 85, 286, 423, 0, 
		140, 303, 7, 466, 276, 79, 450, 0, 
		140, 303, 7, 466, 245, 0, 
		140, 303, 7, 466, 224, 0, 
		140, 303, 7, 466, 418, 0, 
		140, 303, 7, 466, 425, 0, 
		143, 297, 192, 0, 
		143, 297, 195, 81, 75, 0, 
		145, 82, 14, 45, 367, 45, 0, 
		145, 12, 45, 0, 
		146, 409, 380, 0, 
		146, 409, 152, 81, 75, 0, 
		148, 239, 358, 0, 
		148, 239, 359, 81, 75, 0, 
		151, 157, 83, 0, 
		151, 157, 300, 81, 75, 0, 
		153, 133, 48, 45, 89, 115, 147, 0, 
		153, 133, 51, 0, 
		154, 319, 230, 86, 79, 277, 325, 53, 0, 
		154, 333, 470, 121, 0, 
		157, 157, 440, 79, 283, 0, 
		157, 151, 0, 
		158, 271, 291, 0, 
		158, 271, 309, 0, 
		158, 271, 73, 81, 75, 0, 
		159, 434, 220, 266, 0, 
		159, 316, 343, 269, 0, 
		159, 42, 3, 375, 0, 
		159, 5, 408, 261, 0, 
		159, 316, 233, 269, 0, 
		159, 228, 197, 251, 0, 
		159, 316, 346, 269, 0, 
		159, 42, 372, 375, 0, 
		159, 42, 370, 375, 0, 
		159, 42, 368, 375, 0, 
		159, 316, 148, 0, 
		159, 42, 393, 375, 0, 
		159, 228, 194, 53, 0, 
		159, 42, 364, 375, 0, 
		159, 42, 203, 254, 0, 
		159, 159, 355, 79, 283, 0, 
		159, 434, 218, 266, 0, 
		162, 424, 131, 0, 
		162, 424, 134, 81, 75, 0, 
		167, 16, 97, 0, 
		167, 16, 102, 81, 75, 0, 
		172, 356, 115, 147, 0, 
		185, 132, 191, 159, 43, 80, 283, 0, 
		185, 132, 191, 159, 301, 269, 0, 
		185, 132, 191, 159, 33, 0, 
		185, 132, 191, 159, 116, 254, 0, 
		185, 132, 191, 159, 40, 0, 
		185, 132, 191, 159, 59, 62, 241, 0, 
		185, 132, 191, 159, 142, 0, 
		185, 132, 191, 159, 193, 207, 46, 0, 
		185, 132, 191, 159, 361, 79, 45, 0, 
		185, 132, 191, 159, 37, 0, 
		185, 132, 191, 159, 29, 0, 
		185, 132, 191, 159, 117, 0, 
		185, 132, 191, 159, 31, 0, 
		189, 253, 104, 0, 
		189, 253, 105, 81, 75, 0, 
		198, 371, 79, 64, 0, 
		202, 441, 80, 140, 0, 
		202, 231, 0, 
		202, 429, 0, 
		202, 430, 0, 
		202, 437, 90, 45, 0, 
		202, 446, 0, 
		202, 276, 79, 450, 0, 
		202, 245, 0, 
		202, 224, 0, 
		202, 418, 0, 
		202, 425, 0, 
		205, 205, 464, 435, 452, 262, 92, 0, 
		205, 205, 464, 403, 452, 406, 404, 92, 0, 
		205, 205, 464, 237, 452, 426, 210, 417, 92, 0, 
		205, 205, 464, 443, 452, 219, 92, 0, 
		205, 205, 464, 398, 249, 241, 92, 0, 
		205, 205, 464, 212, 416, 232, 92, 0, 
		207, 385, 57, 79, 283, 0, 
		209, 448, 449, 46, 0, 
		210, 349, 427, 46, 0, 
		214, 190, 452, 153, 0, 
		216, 216, 222, 363, 0, 
		219, 216, 222, 363, 0, 
		223, 363, 0, 
		228, 228, 197, 251, 0, 
		228, 228, 194, 53, 0, 
		230, 333, 470, 313, 80, 75, 0, 
		230, 333, 470, 272, 0, 
		230, 333, 470, 274, 0, 
		230, 333, 470, 467, 0, 
		230, 333, 470, 280, 0, 
		230, 333, 470, 288, 271, 311, 0, 
		230, 333, 470, 281, 0, 
		230, 333, 470, 284, 0, 
		230, 330, 0, 
		230, 333, 470, 268, 0, 
		230, 333, 470, 270, 0, 
		232, 179, 53, 0, 
		236, 126, 394, 45, 0, 
		236, 138, 0, 
		236, 130, 2, 53, 0, 
		239, 239, 355, 79, 283, 0, 
		239, 148, 0, 
		240, 410, 353, 254, 0, 
		240, 410, 250, 375, 0, 
		240, 410, 350, 375, 0, 
		240, 410, 347, 375, 0, 
		240, 410, 348, 375, 0, 
		240, 410, 256, 375, 0, 
		240, 410, 340, 375, 0, 
		241, 339, 252, 79, 64, 0, 
		243, 286, 423, 0, 
		249, 188, 226, 45, 0, 
		249, 188, 15, 452, 413, 238, 422, 159, 116, 254, 0, 
		249, 188, 15, 452, 413, 238, 378, 379, 22, 367, 45, 0, 
		249, 188, 15, 452, 413, 238, 468, 0, 
		249, 188, 15, 452, 413, 238, 422, 159, 361, 79, 45, 0, 
		249, 188, 15, 0, 
		249, 188, 15, 452, 413, 238, 422, 159, 43, 80, 283, 0, 
		249, 188, 15, 452, 413, 238, 337, 452, 22, 373, 45, 374, 72, 0, 
		249, 188, 15, 452, 413, 238, 144, 452, 22, 373, 45, 0, 
		249, 188, 15, 452, 413, 238, 156, 452, 22, 0, 
		249, 188, 15, 452, 413, 238, 432, 0, 
		249, 188, 15, 452, 413, 238, 160, 185, 89, 327, 0, 
		249, 188, 15, 452, 413, 238, 465, 0, 
		249, 188, 15, 452, 413, 238, 66, 45, 0, 
		249, 188, 15, 452, 413, 238, 246, 45, 0, 
		249, 188, 15, 452, 413, 238, 422, 159, 301, 269, 0, 
		249, 188, 15, 452, 413, 238, 163, 452, 84, 47, 55, 0, 
		249, 188, 15, 452, 413, 238, 114, 45, 383, 22, 0, 
		249, 188, 15, 452, 413, 238, 422, 159, 59, 62, 241, 0, 
		249, 188, 15, 452, 413, 238, 422, 159, 193, 207, 46, 0, 
		249, 188, 357, 93, 0, 
		249, 188, 15, 452, 413, 238, 422, 159, 117, 0, 
		249, 188, 15, 452, 413, 238, 422, 159, 33, 0, 
		249, 188, 15, 452, 413, 238, 422, 159, 40, 0, 
		249, 188, 15, 452, 413, 238, 422, 159, 142, 0, 
		249, 188, 15, 452, 413, 238, 422, 159, 37, 0, 
		249, 188, 15, 452, 413, 238, 422, 159, 29, 0, 
		249, 188, 15, 452, 413, 238, 422, 159, 31, 0, 
		251, 240, 471, 428, 299, 301, 269, 0, 
		251, 240, 471, 428, 299, 111, 452, 314, 47, 55, 0, 
		251, 240, 471, 428, 299, 33, 0, 
		251, 240, 471, 428, 299, 43, 80, 283, 0, 
		251, 240, 471, 428, 299, 109, 99, 45, 367, 45, 0, 
		251, 240, 471, 428, 299, 40, 0, 
		251, 240, 471, 428, 299, 59, 62, 241, 0, 
		251, 240, 471, 428, 299, 142, 0, 
		251, 240, 471, 428, 299, 193, 207, 46, 0, 
		251, 240, 471, 428, 299, 113, 79, 45, 0, 
		251, 240, 471, 428, 299, 37, 0, 
		251, 240, 471, 428, 299, 29, 0, 
		251, 240, 471, 428, 299, 117, 0, 
		251, 240, 471, 428, 299, 116, 254, 0, 
		251, 240, 471, 428, 299, 31, 0, 
		252, 155, 53, 0, 
		253, 253, 324, 79, 283, 0, 
		253, 189, 0, 
		254, 469, 471, 428, 299, 43, 80, 283, 0, 
		254, 469, 471, 428, 299, 111, 452, 314, 47, 55, 0, 
		254, 469, 471, 428, 299, 301, 269, 0, 
		254, 469, 471, 428, 299, 33, 0, 
		254, 469, 471, 428, 299, 116, 254, 0, 
		254, 469, 471, 428, 299, 109, 99, 45, 367, 45, 0, 
		254, 469, 471, 428, 299, 40, 0, 
		254, 469, 471, 428, 299, 59, 62, 241, 0, 
		254, 469, 471, 428, 299, 142, 0, 
		254, 469, 471, 428, 299, 193, 207, 46, 0, 
		254, 469, 471, 428, 299, 113, 79, 45, 0, 
		254, 469, 471, 428, 299, 37, 0, 
		254, 469, 471, 428, 299, 29, 0, 
		254, 469, 471, 428, 299, 117, 0, 
		254, 469, 471, 428, 299, 31, 0, 
		255, 255, 68, 69, 0, 
		257, 257, 248, 92, 0, 
		258, 258, 52, 92, 0, 
		260, 260, 221, 266, 0, 
		260, 10, 353, 254, 0, 
		260, 294, 259, 261, 0, 
		260, 10, 250, 375, 0, 
		260, 420, 338, 251, 0, 
		260, 10, 350, 375, 0, 
		260, 10, 347, 375, 0, 
		260, 10, 348, 375, 0, 
		260, 10, 256, 375, 0, 
		260, 420, 225, 53, 0, 
		260, 10, 340, 375, 0, 
		260, 260, 354, 266, 0, 
		261, 326, 43, 80, 283, 0, 
		261, 326, 30, 452, 314, 47, 55, 0, 
		261, 326, 38, 269, 0, 
		261, 326, 33, 0, 
		261, 326, 183, 261, 0, 
		261, 326, 28, 99, 45, 367, 45, 0, 
		261, 326, 40, 0, 
		261, 326, 59, 62, 241, 0, 
		261, 326, 142, 0, 
		261, 326, 193, 207, 46, 0, 
		261, 326, 34, 79, 45, 0, 
		261, 326, 37, 0, 
		261, 326, 29, 0, 
		261, 326, 117, 0, 
		261, 326, 31, 0, 
		262, 352, 438, 442, 232, 72, 0, 
		263, 263, 263, 292, 45, 0, 
		266, 287, 43, 80, 283, 0, 
		266, 287, 213, 269, 0, 
		266, 287, 204, 452, 314, 47, 55, 0, 
		266, 287, 217, 266, 0, 
		266, 287, 362, 99, 45, 367, 45, 0, 
		266, 287, 40, 0, 
		266, 287, 59, 62, 241, 0, 
		266, 287, 142, 0, 
		266, 287, 193, 207, 46, 0, 
		266, 287, 108, 79, 45, 0, 
		266, 287, 37, 0, 
		266, 287, 29, 0, 
		266, 287, 117, 0, 
		266, 287, 33, 0, 
		266, 287, 31, 0, 
		267, 267, 127, 135, 145, 140, 0, 
		269, 157, 43, 80, 283, 0, 
		269, 157, 315, 452, 314, 47, 55, 0, 
		269, 157, 33, 0, 
		269, 157, 117, 0, 
		269, 157, 174, 269, 0, 
		269, 157, 171, 269, 0, 
		269, 157, 40, 0, 
		269, 157, 59, 62, 241, 0, 
		269, 157, 142, 0, 
		269, 157, 193, 207, 46, 0, 
		269, 157, 196, 79, 45, 0, 
		269, 157, 37, 0, 
		269, 157, 29, 0, 
		269, 157, 101, 99, 45, 367, 45, 0, 
		269, 157, 31, 0, 
		271, 158, 0, 
		273, 273, 244, 63, 0, 
		275, 263, 396, 396, 292, 45, 0, 
		277, 277, 323, 53, 0, 
		278, 278, 182, 251, 0, 
		278, 278, 180, 53, 0, 
		279, 279, 168, 266, 0, 
		279, 279, 264, 266, 0, 
		283, 275, 295, 94, 301, 269, 0, 
		283, 275, 295, 94, 111, 452, 314, 47, 55, 0, 
		283, 275, 295, 94, 33, 0, 
		283, 275, 295, 94, 43, 80, 283, 0, 
		283, 275, 295, 94, 109, 99, 45, 367, 45, 0, 
		283, 275, 295, 94, 40, 0, 
		283, 275, 295, 94, 59, 62, 241, 0, 
		283, 275, 295, 94, 142, 0, 
		283, 275, 292, 45, 0, 
		283, 275, 295, 94, 193, 207, 46, 0, 
		283, 275, 295, 94, 113, 79, 45, 0, 
		283, 275, 295, 94, 37, 0, 
		283, 275, 295, 94, 29, 0, 
		283, 275, 295, 94, 117, 0, 
		283, 275, 295, 94, 116, 254, 0, 
		283, 275, 295, 94, 31, 0, 
		285, 67, 201, 266, 0, 
		285, 387, 208, 269, 0, 
		285, 462, 176, 375, 0, 
		285, 332, 328, 261, 0, 
		285, 387, 211, 269, 0, 
		285, 278, 182, 251, 0, 
		285, 387, 39, 269, 0, 
		285, 462, 229, 375, 0, 
		285, 462, 173, 375, 0, 
		285, 462, 170, 375, 0, 
		285, 387, 146, 0, 
		285, 462, 305, 375, 0, 
		285, 278, 180, 53, 0, 
		285, 462, 165, 375, 0, 
		285, 462, 187, 254, 0, 
		285, 285, 149, 79, 283, 0, 
		285, 67, 199, 266, 0, 
		286, 286, 128, 0, 
		287, 306, 414, 269, 0, 
		287, 306, 215, 269, 0, 
		287, 306, 178, 269, 0, 
		287, 306, 143, 0, 
		287, 287, 307, 79, 283, 0, 
		289, 271, 311, 0, 
		290, 415, 441, 80, 140, 0, 
		290, 415, 231, 0, 
		290, 415, 429, 0, 
		290, 415, 430, 0, 
		290, 139, 202, 257, 227, 92, 0, 
		290, 415, 437, 90, 45, 0, 
		290, 415, 446, 0, 
		290, 415, 276, 79, 450, 0, 
		290, 415, 245, 0, 
		290, 415, 224, 0, 
		290, 415, 418, 0, 
		290, 415, 425, 0, 
		293, 175, 232, 72, 0, 
		293, 247, 249, 241, 92, 0, 
		293, 242, 241, 92, 0, 
		293, 366, 0, 
		293, 320, 249, 241, 92, 0, 
		294, 10, 353, 254, 0, 
		294, 294, 259, 261, 0, 
		294, 10, 250, 375, 0, 
		294, 420, 338, 251, 0, 
		294, 10, 350, 375, 0, 
		294, 10, 347, 375, 0, 
		294, 10, 348, 375, 0, 
		294, 10, 256, 375, 0, 
		294, 420, 225, 53, 0, 
		294, 10, 340, 375, 0, 
		296, 296, 91, 20, 21, 140, 0, 
		297, 297, 307, 79, 283, 0, 
		297, 143, 0, 
		298, 226, 45, 0, 
		298, 15, 452, 413, 238, 422, 159, 116, 254, 0, 
		298, 15, 452, 413, 238, 378, 379, 22, 367, 45, 0, 
		298, 15, 452, 413, 238, 468, 0, 
		298, 15, 452, 413, 238, 422, 159, 361, 79, 45, 0, 
		298, 15, 0, 
		298, 15, 452, 413, 238, 422, 159, 43, 80, 283, 0, 
		298, 15, 452, 413, 238, 337, 452, 22, 373, 45, 374, 72, 0, 
		298, 15, 452, 413, 238, 144, 452, 22, 373, 45, 0, 
		298, 15, 452, 413, 238, 156, 452, 22, 0, 
		298, 15, 452, 413, 238, 432, 0, 
		298, 15, 452, 413, 238, 160, 185, 89, 327, 0, 
		298, 15, 452, 413, 238, 465, 0, 
		298, 15, 452, 413, 238, 66, 45, 0, 
		298, 15, 452, 413, 238, 246, 45, 0, 
		298, 15, 452, 413, 238, 422, 159, 301, 269, 0, 
		298, 15, 452, 413, 238, 163, 452, 84, 47, 55, 0, 
		298, 15, 452, 413, 238, 114, 45, 383, 22, 0, 
		298, 15, 452, 413, 238, 422, 159, 59, 62, 241, 0, 
		298, 15, 452, 413, 238, 422, 159, 193, 207, 46, 0, 
		298, 357, 93, 0, 
		298, 15, 452, 413, 238, 422, 159, 117, 0, 
		298, 15, 452, 413, 238, 422, 159, 33, 0, 
		298, 15, 452, 413, 238, 422, 159, 40, 0, 
		298, 15, 452, 413, 238, 422, 159, 142, 0, 
		298, 15, 452, 413, 238, 422, 159, 37, 0, 
		298, 15, 452, 413, 238, 422, 159, 29, 0, 
		298, 15, 452, 413, 238, 422, 159, 31, 0, 
		299, 50, 56, 269, 0, 
		299, 50, 58, 269, 0, 
		299, 50, 60, 269, 0, 
		299, 50, 189, 0, 
		299, 299, 324, 79, 283, 0, 
		303, 303, 329, 450, 0, 
		306, 306, 178, 269, 0, 
		306, 306, 414, 269, 0, 
		306, 306, 215, 269, 0, 
		308, 308, 186, 45, 0, 
		314, 267, 127, 135, 145, 140, 0, 
		316, 434, 220, 266, 0, 
		316, 316, 343, 269, 0, 
		316, 5, 408, 261, 0, 
		316, 316, 233, 269, 0, 
		316, 228, 197, 251, 0, 
		316, 316, 346, 269, 0, 
		316, 42, 372, 375, 0, 
		316, 42, 368, 375, 0, 
		316, 42, 370, 375, 0, 
		316, 42, 393, 375, 0, 
		316, 228, 194, 53, 0, 
		316, 42, 364, 375, 0, 
		316, 42, 203, 254, 0, 
		316, 42, 3, 375, 0, 
		316, 434, 218, 266, 0, 
		318, 135, 145, 140, 0, 
		321, 277, 325, 53, 88, 421, 313, 80, 75, 0, 
		321, 277, 325, 53, 88, 421, 272, 0, 
		321, 277, 325, 53, 88, 421, 274, 0, 
		321, 277, 325, 53, 88, 421, 467, 0, 
		321, 277, 325, 53, 88, 421, 280, 0, 
		321, 277, 325, 53, 88, 421, 288, 271, 311, 0, 
		321, 277, 325, 53, 88, 421, 281, 0, 
		321, 277, 325, 53, 88, 421, 284, 0, 
		321, 277, 325, 53, 88, 365, 330, 0, 
		321, 277, 325, 53, 88, 421, 268, 0, 
		321, 277, 325, 53, 88, 421, 270, 0, 
		322, 322, 118, 261, 0, 
		326, 279, 168, 266, 0, 
		326, 334, 1, 269, 0, 
		326, 334, 4, 269, 0, 
		326, 334, 6, 269, 0, 
		326, 334, 167, 0, 
		326, 326, 95, 79, 283, 0, 
		326, 279, 264, 266, 0, 
		327, 303, 7, 466, 441, 80, 140, 0, 
		327, 303, 7, 466, 231, 0, 
		327, 303, 7, 466, 27, 0, 
		327, 303, 7, 466, 290, 0, 
		327, 303, 7, 466, 437, 90, 45, 0, 
		327, 303, 7, 466, 446, 0, 
		327, 303, 7, 466, 457, 202, 436, 243, 85, 286, 423, 0, 
		327, 303, 7, 466, 276, 79, 450, 0, 
		327, 303, 7, 466, 245, 0, 
		327, 303, 7, 466, 224, 0, 
		327, 303, 7, 466, 418, 0, 
		327, 303, 7, 466, 425, 0, 
		330, 154, 365, 333, 470, 313, 80, 75, 0, 
		330, 154, 365, 333, 470, 270, 0, 
		330, 154, 365, 333, 470, 272, 0, 
		330, 154, 365, 333, 470, 274, 0, 
		330, 154, 365, 333, 470, 467, 0, 
		330, 154, 365, 333, 470, 280, 0, 
		330, 154, 365, 333, 470, 288, 271, 311, 0, 
		330, 154, 365, 333, 470, 281, 0, 
		330, 154, 365, 333, 470, 284, 0, 
		330, 154, 365, 330, 0, 
		330, 154, 365, 333, 470, 268, 0, 
		330, 317, 230, 86, 0, 
		332, 462, 187, 254, 0, 
		332, 332, 328, 261, 0, 
		332, 462, 229, 375, 0, 
		332, 278, 182, 251, 0, 
		332, 462, 176, 375, 0, 
		332, 462, 170, 375, 0, 
		332, 462, 173, 375, 0, 
		332, 462, 305, 375, 0, 
		332, 278, 180, 53, 0, 
		332, 462, 165, 375, 0, 
		333, 345, 230, 0, 
		334, 279, 168, 266, 0, 
		334, 334, 1, 269, 0, 
		334, 334, 4, 269, 0, 
		334, 334, 6, 269, 0, 
		334, 279, 264, 266, 0, 
		342, 200, 46, 0, 
		349, 349, 427, 46, 0, 
		351, 351, 431, 366, 0, 
		351, 351, 431, 242, 241, 92, 0, 
		351, 351, 431, 175, 232, 72, 0, 
		351, 351, 431, 247, 249, 241, 92, 0, 
		351, 351, 431, 320, 249, 241, 92, 0, 
		352, 352, 438, 442, 232, 72, 0, 
		356, 391, 394, 45, 0, 
		356, 8, 0, 
		356, 103, 2, 53, 0, 
		360, 360, 456, 448, 449, 46, 0, 
		363, 400, 371, 79, 64, 0, 
		365, 235, 273, 331, 63, 0, 
		366, 335, 249, 198, 342, 0, 
		366, 206, 249, 198, 200, 46, 0, 
		366, 206, 249, 371, 79, 64, 0, 
		367, 0, 
		369, 402, 61, 41, 79, 283, 78, 0, 
		369, 402, 61, 161, 79, 283, 78, 92, 0, 
		369, 35, 452, 153, 0, 
		373, 0, 
		374, 0, 
		375, 96, 43, 80, 283, 0, 
		375, 96, 137, 452, 314, 47, 55, 0, 
		375, 96, 341, 269, 0, 
		375, 96, 33, 0, 
		375, 96, 344, 375, 0, 
		375, 96, 136, 99, 45, 367, 45, 0, 
		375, 96, 40, 0, 
		375, 96, 59, 62, 241, 0, 
		375, 96, 142, 0, 
		375, 96, 193, 207, 46, 0, 
		375, 96, 141, 79, 45, 0, 
		375, 96, 37, 0, 
		375, 96, 29, 0, 
		375, 96, 117, 0, 
		375, 96, 31, 0, 
		376, 376, 412, 241, 92, 0, 
		379, 384, 379, 22, 367, 45, 0, 
		379, 381, 0, 
		379, 382, 452, 22, 0, 
		383, 0, 
		385, 385, 54, 79, 283, 78, 92, 0, 
		387, 67, 201, 266, 0, 
		387, 387, 208, 269, 0, 
		387, 332, 328, 261, 0, 
		387, 387, 211, 269, 0, 
		387, 278, 182, 251, 0, 
		387, 387, 39, 269, 0, 
		387, 462, 229, 375, 0, 
		387, 462, 170, 375, 0, 
		387, 462, 173, 375, 0, 
		387, 462, 305, 375, 0, 
		387, 278, 180, 53, 0, 
		387, 462, 165, 375, 0, 
		387, 462, 187, 254, 0, 
		387, 462, 176, 375, 0, 
		387, 67, 199, 266, 0, 
		389, 345, 230, 0, 
		389, 389, 265, 0, 
		392, 394, 45, 0, 
		395, 435, 452, 262, 92, 0, 
		395, 403, 452, 406, 404, 92, 0, 
		395, 237, 452, 426, 210, 417, 92, 0, 
		395, 443, 452, 219, 92, 0, 
		395, 398, 249, 241, 92, 0, 
		395, 212, 416, 232, 92, 0, 
		396, 396, 396, 292, 45, 0, 
		397, 181, 185, 89, 308, 186, 45, 0, 
		397, 181, 185, 0, 
		399, 106, 120, 266, 0, 
		399, 399, 123, 269, 0, 
		399, 322, 118, 261, 0, 
		399, 399, 124, 269, 0, 
		399, 399, 125, 269, 0, 
		399, 106, 119, 266, 0, 
		401, 313, 80, 75, 0, 
		401, 272, 0, 
		401, 274, 0, 
		401, 467, 0, 
		401, 280, 0, 
		401, 288, 271, 311, 0, 
		401, 281, 0, 
		401, 284, 0, 
		401, 268, 0, 
		401, 270, 0, 
		402, 35, 452, 153, 0, 
		404, 411, 407, 46, 0, 
		406, 376, 412, 241, 92, 0, 
		409, 409, 149, 79, 283, 0, 
		409, 146, 0, 
		410, 410, 353, 254, 0, 
		411, 411, 407, 46, 0, 
		413, 413, 169, 397, 285, 166, 254, 0, 
		413, 413, 169, 377, 379, 22, 367, 45, 0, 
		413, 413, 169, 369, 0, 
		413, 413, 169, 397, 285, 43, 80, 283, 0, 
		413, 413, 169, 390, 452, 22, 373, 45, 374, 72, 0, 
		413, 413, 169, 386, 452, 22, 373, 45, 0, 
		413, 413, 169, 11, 452, 22, 0, 
		413, 413, 169, 172, 0, 
		413, 413, 169, 74, 185, 89, 327, 0, 
		413, 413, 169, 453, 0, 
		413, 413, 169, 98, 45, 0, 
		413, 413, 169, 44, 45, 0, 
		413, 413, 169, 13, 452, 84, 47, 55, 0, 
		413, 413, 169, 388, 45, 383, 22, 0, 
		413, 413, 234, 0, 
		413, 413, 169, 397, 285, 59, 62, 241, 0, 
		413, 413, 169, 397, 285, 193, 207, 46, 0, 
		413, 413, 169, 397, 285, 117, 0, 
		413, 413, 169, 397, 285, 33, 0, 
		413, 413, 169, 397, 285, 40, 0, 
		413, 413, 169, 397, 285, 142, 0, 
		413, 413, 169, 397, 285, 37, 0, 
		413, 413, 169, 397, 285, 29, 0, 
		413, 413, 169, 397, 285, 31, 0, 
		416, 188, 394, 45, 0, 
		417, 419, 46, 0, 
		420, 420, 338, 251, 0, 
		420, 420, 225, 53, 0, 
		421, 365, 345, 230, 0, 
		421, 235, 273, 331, 63, 0, 
		421, 421, 265, 0, 
		422, 70, 185, 89, 132, 282, 45, 0, 
		422, 70, 185, 0, 
		424, 424, 129, 79, 283, 0, 
		424, 162, 0, 
		426, 351, 431, 366, 0, 
		426, 351, 431, 242, 241, 92, 0, 
		426, 351, 431, 175, 232, 72, 0, 
		426, 351, 431, 247, 249, 241, 92, 0, 
		426, 351, 431, 320, 249, 241, 92, 0, 
		428, 428, 221, 266, 0, 
		428, 428, 354, 266, 0, 
		432, 236, 115, 147, 0, 
		433, 10, 353, 254, 0, 
		433, 10, 250, 375, 0, 
		433, 420, 338, 251, 0, 
		433, 10, 350, 375, 0, 
		433, 10, 347, 375, 0, 
		433, 10, 348, 375, 0, 
		433, 10, 256, 375, 0, 
		433, 420, 225, 53, 0, 
		433, 10, 340, 375, 0, 
		434, 434, 220, 266, 0, 
		434, 42, 203, 254, 0, 
		434, 5, 408, 261, 0, 
		434, 42, 372, 375, 0, 
		434, 228, 197, 251, 0, 
		434, 42, 3, 375, 0, 
		434, 42, 368, 375, 0, 
		434, 42, 370, 375, 0, 
		434, 42, 393, 375, 0, 
		434, 228, 194, 53, 0, 
		434, 42, 364, 375, 0, 
		434, 434, 218, 266, 0, 
		439, 442, 232, 72, 0, 
		444, 257, 227, 92, 76, 0, 
		445, 273, 331, 63, 87, 389, 313, 80, 75, 0, 
		445, 273, 331, 63, 87, 389, 272, 0, 
		445, 273, 331, 63, 87, 389, 274, 0, 
		445, 273, 331, 63, 87, 389, 467, 0, 
		445, 273, 331, 63, 87, 389, 280, 0, 
		445, 273, 331, 63, 87, 389, 288, 271, 311, 0, 
		445, 273, 331, 63, 87, 389, 281, 0, 
		445, 273, 331, 63, 87, 389, 284, 0, 
		445, 273, 331, 63, 87, 330, 0, 
		445, 273, 331, 63, 87, 389, 268, 0, 
		445, 273, 331, 63, 87, 389, 270, 0, 
		447, 360, 456, 448, 449, 46, 0, 
		449, 451, 92, 0, 
		450, 466, 441, 80, 140, 0, 
		450, 466, 231, 0, 
		450, 466, 27, 0, 
		450, 466, 290, 0, 
		450, 466, 437, 90, 45, 0, 
		450, 466, 446, 0, 
		450, 466, 457, 202, 436, 243, 85, 286, 423, 0, 
		450, 466, 276, 79, 450, 0, 
		450, 466, 245, 0, 
		450, 466, 224, 0, 
		450, 466, 418, 0, 
		450, 466, 425, 0, 
		452, 0, 
		453, 9, 433, 471, 428, 299, 301, 269, 0, 
		453, 9, 433, 471, 428, 299, 111, 452, 314, 47, 55, 0, 
		453, 9, 433, 471, 428, 299, 33, 0, 
		453, 9, 433, 471, 428, 299, 43, 80, 283, 0, 
		453, 9, 433, 471, 428, 299, 109, 99, 45, 367, 45, 0, 
		453, 9, 433, 471, 428, 299, 40, 0, 
		453, 9, 433, 471, 428, 299, 59, 62, 241, 0, 
		453, 9, 433, 471, 428, 299, 142, 0, 
		453, 9, 433, 471, 428, 299, 193, 207, 46, 0, 
		453, 9, 433, 471, 428, 299, 113, 79, 45, 0, 
		453, 9, 433, 471, 428, 299, 37, 0, 
		453, 9, 433, 471, 428, 299, 29, 0, 
		453, 9, 433, 471, 428, 299, 117, 0, 
		453, 9, 433, 471, 428, 299, 116, 254, 0, 
		453, 9, 433, 471, 428, 299, 31, 0, 
		454, 454, 302, 53, 0, 
		455, 460, 463, 205, 464, 435, 452, 262, 92, 0, 
		455, 460, 463, 205, 464, 403, 452, 406, 404, 92, 0, 
		455, 460, 463, 205, 464, 237, 452, 426, 210, 417, 92, 0, 
		455, 460, 463, 205, 464, 443, 452, 219, 92, 0, 
		455, 460, 463, 461, 360, 456, 448, 449, 46, 0, 
		455, 460, 463, 205, 464, 398, 249, 241, 92, 0, 
		455, 460, 0, 
		455, 460, 463, 205, 464, 212, 416, 232, 92, 0, 
		458, 459, 100, 0, 
		458, 436, 243, 85, 286, 423, 0, 
		461, 205, 464, 435, 452, 262, 92, 0, 
		461, 205, 464, 403, 452, 406, 404, 92, 0, 
		461, 205, 464, 237, 452, 426, 210, 417, 92, 0, 
		461, 205, 464, 443, 452, 219, 92, 0, 
		461, 205, 464, 398, 249, 241, 92, 0, 
		461, 205, 464, 212, 416, 232, 92, 0, 
		462, 278, 182, 251, 0, 
		462, 462, 187, 254, 0, 
		462, 278, 180, 53, 0, 
		463, 0, 
		465, 65, 433, 471, 428, 299, 301, 269, 0, 
		465, 65, 433, 471, 428, 299, 111, 452, 314, 47, 55, 0, 
		465, 65, 433, 471, 428, 299, 33, 0, 
		465, 65, 433, 471, 428, 299, 43, 80, 283, 0, 
		465, 65, 433, 471, 428, 299, 109, 99, 45, 367, 45, 0, 
		465, 65, 433, 471, 428, 299, 40, 0, 
		465, 65, 433, 471, 428, 299, 59, 62, 241, 0, 
		465, 65, 433, 471, 428, 299, 142, 0, 
		465, 65, 433, 471, 428, 299, 193, 207, 46, 0, 
		465, 65, 433, 471, 428, 299, 113, 79, 45, 0, 
		465, 65, 433, 471, 428, 299, 37, 0, 
		465, 65, 433, 471, 428, 299, 29, 0, 
		465, 65, 433, 471, 428, 299, 117, 0, 
		465, 65, 433, 471, 428, 299, 116, 254, 0, 
		465, 65, 433, 471, 428, 299, 31, 0, 
		466, 336, 92, 0, 
		468, 214, 61, 41, 79, 283, 78, 0, 
		468, 214, 61, 161, 79, 283, 78, 92, 0, 
		468, 190, 452, 153, 0, 
		469, 250, 375, 0, 
		469, 350, 375, 0, 
		469, 347, 375, 0, 
		469, 348, 375, 0, 
		469, 256, 375, 0, 
		469, 340, 375, 0, 
		470, 470, 265, 0, 
		471, 471, 259, 261, 0, 
	};
	const short parsx_rule_state_table_index[] = {
		0, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182, 184, 186, 188, 190, 192, 194, 196, 198, 200, 202, 204, 206, 208, 210, 212, 214, 216, 218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 238, 240, 242, 244, 246, 248, 250, 252, 254, 256, 258, 260, 262, 264, 266, 268, 270, 272, 274, 276, 278, 280, 282, 284, 286, 288, 290, 292, 294, 296, 298, 300, 302, 304, 306, 308, 310, 312, 314, 316, 318, 320, 322, 324, 326, 328, 330, 332, 334, 336, 338, 340, 342, 344, 346, 348, 350, 352, 354, 356, 358, 360, 362, 364, 366, 368, 370, 372, 374, 376, 378, 380, 382, 384, 386, 388, 390, 392, 394, 396, 398, 400, 402, 404, 406, 408, 410, 412, 414, 416, 418, 420, 422, 424, 426, 428, 430, 432, 434, 436, 438, 440, 442, 444, 446, 448, 450, 452, 454, 456, 458, 460, 462, 464, 466, 468, 470, 472, 474, 476, 478, 480, 482, 484, 486, 488, 490, 492, 494, 496, 498, 500, 502, 504, 506, 508, 510, 512, 514, 516, 518, 520, 522, 524, 526, 528, 530, 532, 534, 536, 538, 540, 542, 544, 546, 548, 550, 552, 554, 556, 558, 560, 562, 564, 566, 568, 570, 572, 574, 576, 578, 580, 582, 584, 586, 588, 590, 592, 594, 596, 598, 600, 602, 604, 606, 608, 610, 612, 614, 616, 618, 620, 622, 624, 626, 628, 630, 632, 634, 636, 638, 640, 642, 644, 646, 648, 650, 652, 654, 656, 658, 660, 662, 664, 666, 668, 670, 672, 674, 676, 678, 680, 682, 684, 686, 688, 690, 692, 694, 696, 698, 700, 702, 704, 706, 708, 710, 712, 714, 716, 718, 720, 722, 724, 726, 728, 730, 732, 734, 736, 738, 740, 742, 744, 746, 748, 750, 752, 754, 756, 758, 760, 762, 764, 766, 768, 770, 772, 774, 776, 778, 782, 787, 792, 797, 802, 807, 812, 817, 822, 827, 832, 837, 842, 847, 854, 858, 864, 867, 872, 879, 883, 891, 900, 905, 914, 923, 934, 943, 950, 955, 963, 968, 974, 980, 988, 997, 1005, 1014, 1023, 1030, 1037, 1044, 1051, 1058, 1065, 1072, 1077, 1080, 1083, 1088, 1091, 1096, 1099, 1102, 1105, 1108, 1115, 1120, 1125, 1130, 1135, 1140, 1145, 1150, 1155, 1160, 1165, 1170, 1175, 1180, 1185, 1190, 1197, 1205, 1210, 1215, 1220, 1225, 1233, 1237, 1243, 1251, 1255, 1261, 1265, 1271, 1277, 1281, 1285, 1289, 1294, 1298, 1302, 1304, 1309, 1314, 1319, 1327, 1333, 1339, 1345, 1351, 1359, 1365, 1371, 1375, 1381, 1387, 1396, 1408, 1416, 1426, 1438, 1446, 1456, 1464, 1469, 1479, 1489, 1497, 1505, 1513, 1522, 1530, 1538, 1542, 1552, 1563, 1570, 1581, 1584, 1595, 1608, 1619, 1628, 1635, 1645, 1652, 1660, 1668, 1678, 1689, 1699, 1710, 1721, 1730, 1739, 1748, 1757, 1766, 1775, 1784, 1791, 1796, 1801, 1806, 1811, 1818, 1823, 1828, 1831, 1836, 1841, 1850, 1857, 1864, 1871, 1878, 1883, 1890, 1897, 1904, 1911, 1918, 1923, 1928, 1933, 1938, 1943, 1948, 1953, 1958, 1963, 1968, 1973, 1978, 1985, 1990, 1995, 2000, 2005, 2008, 2013, 2018, 2023, 2028, 2033, 2037, 2045, 2051, 2057, 2063, 2069, 2077, 2083, 2089, 2095, 2101, 2107, 2109, 2111, 2113, 2115, 2117, 2119, 2126, 2128, 2130, 2132, 2134, 2136, 2138, 2140, 2142, 2147, 2152, 2157, 2162, 2167, 2172, 2177, 2182, 2187, 2192, 2196, 2201, 2206, 2211, 2216, 2222, 2227, 2232, 2237, 2242, 2247, 2252, 2256, 2262, 2267, 2274, 2279, 2283, 2288, 2293, 2298, 2305, 2311, 2317, 2324, 2328, 2333, 2340, 2344, 2348, 2353, 2361, 2365, 2373, 2379, 2385, 2391, 2399, 2405, 2417, 2425, 2431, 2437, 2443, 2449, 2453, 2459, 2466, 2470, 2474, 2480, 2484, 2490, 2494, 2500, 2508, 2512, 2521, 2526, 2532, 2535, 2539, 2543, 2549, 2554, 2559, 2564, 2569, 2574, 2579, 2584, 2589, 2594, 2599, 2603, 2608, 2613, 2618, 2623, 2629, 2634, 2638, 2644, 2648, 2654, 2659, 2667, 2674, 2680, 2687, 2693, 2701, 2707, 2715, 2723, 2729, 2735, 2741, 2747, 2751, 2757, 2762, 2767, 2770, 2773, 2776, 2781, 2784, 2789, 2792, 2795, 2798, 2801, 2809, 2818, 2828, 2836, 2844, 2852, 2858, 2863, 2868, 2873, 2878, 2883, 2886, 2891, 2896, 2903, 2908, 2913, 2918, 2923, 2930, 2935, 2940, 2943, 2948, 2953, 2957, 2962, 2965, 2970, 2976, 2979, 2984, 2989, 2994, 2999, 3004, 3009, 3014, 3020, 3024, 3029, 3040, 3052, 3060, 3072, 3076, 3088, 3102, 3114, 3124, 3132, 3143, 3151, 3160, 3169, 3180, 3192, 3203, 3215, 3227, 3232, 3242, 3252, 3262, 3272, 3282, 3292, 3302, 3310, 3321, 3328, 3337, 3348, 3355, 3364, 3371, 3380, 3389, 3396, 3403, 3410, 3418, 3425, 3429, 3435, 3438, 3447, 3458, 3466, 3473, 3481, 3492, 3499, 3508, 3515, 3524, 3533, 3540, 3547, 3554, 3561, 3566, 3571, 3576, 3581, 3586, 3591, 3596, 3601, 3606, 3611, 3616, 3621, 3626, 3631, 3636, 3642, 3650, 3655, 3659, 3664, 3672, 3676, 3682, 3686, 3692, 3698, 3702, 3706, 3710, 3714, 3721, 3727, 3733, 3738, 3746, 3751, 3759, 3763, 3769, 3773, 3779, 3785, 3789, 3793, 3797, 3801, 3805, 3812, 3818, 3826, 3830, 3834, 3839, 3844, 3848, 3854, 3858, 3864, 3870, 3874, 3878, 3886, 3890, 3893, 3898, 3905, 3910, 3915, 3920, 3925, 3930, 3937, 3947, 3953, 3961, 3971, 3977, 3985, 3991, 3996, 4004, 4012, 4018, 4024, 4030, 4037, 4043, 4048, 4053, 4058, 4063, 4068, 4073, 4078, 4083, 4088, 4093, 4097, 4102, 4107, 4112, 4117, 4123, 4128, 4132, 4137, 4142, 4147, 4151, 4157, 4161, 4167, 4171, 4175, 4179, 4186, 4192, 4196, 4202, 4206, 4210, 4214, 4218, 4223, 4229, 4234, 4237, 4243, 4248, 4253, 4258, 4263, 4268, 4273, 4278, 4283, 4288, 4293, 4300, 4306, 4309, 4313, 4323, 4334, 4341, 4352, 4355, 4366, 4379, 4390, 4399, 4406, 4416, 4423, 4431, 4439, 4449, 4460, 4470, 4481, 4492, 4496, 4505, 4514, 4523, 4532, 4541, 4550, 4559, 4564, 4569, 4574, 4578, 4584, 4589, 4594, 4599, 4604, 4609, 4616, 4621, 4626, 4631, 4636, 4641, 4646, 4651, 4656, 4661, 4666, 4671, 4676, 4681, 4686, 4691, 4696, 4706, 4714, 4722, 4730, 4738, 4748, 4756, 4764, 4772, 4780, 4788, 4793, 4798, 4803, 4808, 4813, 4817, 4823, 4828, 4836, 4842, 4848, 4854, 4862, 4868, 4880, 4888, 4894, 4900, 4906, 4912, 4921, 4928, 4935, 4942, 4949, 4956, 4965, 4972, 4979, 4984, 4991, 4996, 5001, 5006, 5011, 5016, 5021, 5026, 5031, 5036, 5041, 5046, 5050, 5055, 5060, 5065, 5070, 5075, 5079, 5084, 5089, 5096, 5103, 5111, 5119, 5126, 5131, 5134, 5139, 5146, 5152, 5158, 5164, 5171, 5178, 5180, 5188, 5197, 5202, 5204, 5206, 5212, 5220, 5225, 5229, 5234, 5242, 5246, 5252, 5256, 5262, 5268, 5272, 5276, 5280, 5284, 5290, 5297, 5300, 5305, 5307, 5315, 5320, 5325, 5330, 5335, 5340, 5345, 5350, 5355, 5360, 5365, 5370, 5375, 5380, 5385, 5390, 5394, 5398, 5402, 5408, 5415, 5423, 5429, 5435, 5441, 5447, 5455, 5459, 5464, 5469, 5474, 5479, 5484, 5489, 5494, 5497, 5500, 5503, 5506, 5511, 5514, 5517, 5520, 5523, 5528, 5533, 5539, 5545, 5548, 5553, 5558, 5566, 5575, 5580, 5589, 5600, 5609, 5616, 5621, 5629, 5634, 5640, 5646, 5655, 5663, 5667, 5676, 5685, 5692, 5699, 5706, 5713, 5720, 5727, 5734, 5739, 5743, 5748, 5753, 5758, 5764, 5768, 5776, 5780, 5786, 5789, 5794, 5801, 5808, 5816, 5824, 5829, 5834, 5839, 5844, 5849, 5854, 5859, 5864, 5869, 5874, 5879, 5884, 5889, 5894, 5899, 5904, 5909, 5914, 5919, 5924, 5929, 5934, 5939, 5944, 5949, 5955, 5965, 5973, 5981, 5989, 5997, 6007, 6015, 6023, 6030, 6038, 6046, 6053, 6057, 6063, 6067, 6071, 6075, 6081, 6085, 6095, 6101, 6105, 6109, 6113, 6117, 6119, 6128, 6140, 6148, 6158, 6170, 6178, 6188, 6196, 6206, 6216, 6224, 6232, 6240, 6249, 6257, 6262, 6272, 6283, 6295, 6305, 6315, 6325, 6328, 6338, 6342, 6349, 6357, 6366, 6376, 6384, 6392, 6400, 6405, 6410, 6415, 6417, 6426, 6438, 6446, 6456, 6468, 6476, 6486, 6494, 6504, 6514, 6522, 6530, 6538, 6547, 6555, 6559, 6567, 6576, 6581, 6585, 6589, 6593, 6597, 6601, 6605, 6609, 
	};
	parsx_step_func_begin()
		while( parsx_has_state ){
			State parsx_current_state_ = parsx_current_state;
			Action parsx_taken_action = parsx_table[parsx_lookahead_token][parsx_current_state_];
			if ( parsx_taken_action <= 0 ) { parsx_taken_action = parsx_table[parsx_max_token_id + 1][parsx_current_state_];
			if ( parsx_taken_action <= 0 ) return false; }
			parsx_queue_action(parsx_taken_action);
			parsx_pop_state();
			const short* parsx_pushed_states = parsx_rule_state_table + parsx_rule_state_table_index[parsx_taken_action];
			while ( *(++parsx_pushed_states) ) parsx_push_state(*parsx_pushed_states);
			if ( parsx_taken_action > 389 ) { parsx_shift_token(); return true; }
		}
	parsx_step_func_end()
	parsx_commit_func_begin()
		while ( parsx_has_queued_action ){
			Action parsx_action = parsx_pop_queued_action;
			switch ( parsx_action ){
				case 0:{
				}break;
				case 1:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Mult, _parsx_1, _parsx_3));
					}
				}break;
				case 2:{
					{
						parsx_push_value(Expr*, nullptr);
					}
				}break;
				case 3:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::GT, _parsx_1, _parsx_3));
					}
				}break;
				case 4:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Div, _parsx_1, _parsx_3));
					}
				}break;
				case 5:{
				}break;
				case 6:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Rem, _parsx_1, _parsx_3));
					}
				}break;
				case 7:{
					{
						Pattern* _parsx_1 = parsx_pop_value(Pattern*);
						parsx_push_value(List<Pattern>, List<Pattern>(_parsx_1));
					}
				}break;
				case 8:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Name> _parsx_2 = parsx_pop_value(List<Name>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, nullptr, nullptr));
					}
				}break;
				case 9:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Return, _parsx_2));
					}
				}break;
				case 10:{
				}break;
				case 11:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtBlock)(SrcSpan(_parsx_1.where, _parsx_3.where), _parsx_2));
					}
				}break;
				case 12:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(MatchBranch<Expr>*, alloc(MatchBranch<Expr>)(_parsx_1.where, nullptr, _parsx_2));
					}
				}break;
				case 13:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List< MatchCase<Stmt> > _parsx_4 = parsx_pop_value(List< MatchCase<Stmt> >);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtMatch)(SrcSpan(_parsx_1.where, _parsx_5.where), _parsx_2, _parsx_4));
					}
				}break;
				case 14:{
					{
						parsx_push_value(MatchBranch<Expr>*, nullptr);
					}
				}break;
				case 15:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
						SrcLoc _parsx_1 = parsx_pop_value(SrcLoc);
						parsx_push_value(FunctionBody*, alloc(FunctionBodyDefined)(to_here(_parsx_1), _parsx_2));
					}
				}break;
				case 16:{
				}break;
				case 17:{
					{
						MatchBranch<Expr>* _parsx_5 = parsx_pop_value(MatchBranch<Expr>*);
						Expr* _parsx_4 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(MatchBranch<Expr>*, alloc(MatchBranch<Expr>)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
					}
				}break;
				case 18:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(MatchBranch<Expr>*, alloc(MatchBranch<Expr>)(_parsx_1.where, nullptr, _parsx_2));
					}
				}break;
				case 19:{
					{
						MatchBranch<Stmt>* _parsx_3 = parsx_pop_value(MatchBranch<Stmt>*);
						List<Pattern> _parsx_2 = parsx_pop_value(List<Pattern>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(MatchCase<Stmt>*, alloc(MatchCase<Stmt>)(_parsx_1.where, _parsx_2, _parsx_3));
					}
				}break;
				case 20:{
					{
						parsx_push_value(List<Stmt>, List<Stmt>());
					}
				}break;
				case 21:{
					{
						List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(MatchBranch<Stmt>*, alloc(MatchBranch<Stmt>)(_parsx_1.where, nullptr, _parsx_2));
					}
				}break;
				case 22:{
					{
						MatchBranch<Stmt>* _parsx_5 = parsx_pop_value(MatchBranch<Stmt>*);
						List<Stmt> _parsx_4 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(MatchBranch<Stmt>*, alloc(MatchBranch<Stmt>)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
					}
				}break;
				case 23:{
					{
						MatchBranch<Stmt>* _parsx_5 = parsx_pop_value(MatchBranch<Stmt>*);
						List<Stmt> _parsx_4 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(MatchBranch<Stmt>*, alloc(MatchBranch<Stmt>)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
					}
				}break;
				case 24:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Pattern*, alloc(PatternPrim)(_parsx_1.where, PatternPrim::Wildcard));
					}
				}break;
				case 25:{
					{
						Expr* _parsx_5 = parsx_pop_value(Expr*);
						Expr* _parsx_4 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
					}
				}break;
				case 26:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprTrue)(_parsx_1.where));
					}
				}break;
				case 27:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List< MatchCase<Expr> > _parsx_4 = parsx_pop_value(List< MatchCase<Expr> >);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprMatch)(SrcSpan(_parsx_1.where, _parsx_5.where), _parsx_2, _parsx_4));
					}
				}break;
				case 28:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprFalse)(_parsx_1.where));
					}
				}break;
				case 29:{
				}break;
				case 30:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprNull)(_parsx_1.where));
					}
				}break;
				case 31:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, _parsx_2);
					}
				}break;
				case 32:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List<AssignPair> _parsx_4 = parsx_pop_value(List<AssignPair>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<ConstructorStringPart> _parsx_2 = parsx_pop_value(List<ConstructorStringPart>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtConstruct)(_parsx_1.where, _parsx_2, _parsx_4));
					}
				}break;
				case 33:{
					{
						parsx_push_value(List<ConstructorStringPart>, nullptr);
					}
				}break;
				case 34:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprNumber)(_parsx_1.where, sym(_parsx_1)));
					}
				}break;
				case 35:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Negate, _parsx_2));
					}
				}break;
				case 36:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Rem, _parsx_1, _parsx_3));
					}
				}break;
				case 37:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprID)(_parsx_1.where, sym(_parsx_1)));
					}
				}break;
				case 38:{
					{
						parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(List<ConstructorStringPart>, alloc(ConstructorStringPart)(nullptr, _parsx_1.where, sym(_parsx_1), _parsx_3));
					}
				}break;
				case 39:{
				}break;
				case 40:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprTuple)(SrcSpan(_parsx_1.where, _parsx_3.where), _parsx_2));
					}
				}break;
				case 41:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Raise, _parsx_2));
					}
				}break;
				case 42:{
					{
						Expr* _parsx_4 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Name> _parsx_2 = parsx_pop_value(List<Name>);
						List<AssignPair> _parsx_1 = parsx_pop_value(List<AssignPair>);
						parsx_push_value(List<AssignPair>, _parsx_1.append(alloc(AssignPair)(_parsx_2, _parsx_4)));
					}
				}break;
				case 43:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(QualID*, alloc(QualID)(_parsx_1.where, sym(_parsx_1)));
					}
				}break;
				case 44:{
				}break;
				case 45:{
					{
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<AssignPair> _parsx_1 = parsx_pop_value(List<AssignPair>);
						parsx_push_value(List<AssignPair>, _parsx_1);
					}
				}break;
				case 46:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						QualID* _parsx_1 = parsx_pop_value(QualID*);
						parsx_push_value(QualID*, alloc(QualID)(jf::SrcSpan(_parsx_1->where.from(), _parsx_3.where.to()), _parsx_1, sym(_parsx_3)));
					}
				}break;
				case 47:{
					{
						parsx_token_type _parsx_6 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_5 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<ConstructorStringPart> _parsx_1 = parsx_pop_value(List<ConstructorStringPart>);
						parsx_push_value(List<ConstructorStringPart>, alloc(ConstructorStringPart)(_parsx_1, _parsx_3.where, sym(_parsx_3), _parsx_5));
					}
				}break;
				case 48:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Mult, _parsx_1, _parsx_3));
					}
				}break;
				case 49:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(List<ConstructorStringPart>, alloc(ConstructorStringPart)(nullptr, SrcSpan(_parsx_1.where, _parsx_3.where), StringRef(), _parsx_2));
					}
				}break;
				case 50:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Div, _parsx_1, _parsx_3));
					}
				}break;
				case 51:{
					{
						FunctionBody* _parsx_3 = parsx_pop_value(FunctionBody*);
						FunctionSignature* _parsx_2 = parsx_pop_value(FunctionSignature*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprLambda)(_parsx_1.where, _parsx_2, _parsx_3));
					}
				}break;
				case 52:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Rem, _parsx_1, _parsx_3));
					}
				}break;
				case 53:{
				}break;
				case 54:{
					{
						parsx_push_value(List<ParamGroup>, nullptr);
					}
				}break;
				case 55:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Return, _parsx_2));
					}
				}break;
				case 56:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Eval, _parsx_2));
					}
				}break;
				case 57:{
				}break;
				case 58:{
					{
						ParamGroup* _parsx_3 = parsx_pop_value(ParamGroup*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<ParamGroup> _parsx_1 = parsx_pop_value(List<ParamGroup>);
						parsx_push_value(List<ParamGroup>, _parsx_1.append(_parsx_3));
					}
				}break;
				case 59:{
					{
						List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_1 = parsx_pop_value(List<ExprList>);
						parsx_push_value(Stmt*, alloc(StmtAssign)(SrcSpan(_parsx_1.first->expr->where, _parsx_3.last->expr->where), _parsx_1, _parsx_3));
					}
				}break;
				case 60:{
					{
						Type* _parsx_3 = parsx_pop_value(Type*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<Name> _parsx_1 = parsx_pop_value(List<Name>);
						parsx_push_value(ParamGroup*, alloc(ParamGroup)(_parsx_1, _parsx_3));
					}
				}break;
				case 61:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						WithSrcLoc<TypeReferenceNode*> _parsx_1 = parsx_pop_value(WithSrcLoc<TypeReferenceNode*>);
						parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1, alloc(TypeReferenceInstance)(_parsx_1, _parsx_4)));
					}
				}break;
				case 62:{
					{
						List<ExprList> _parsx_4 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Pattern> _parsx_2 = parsx_pop_value(List<Pattern>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtLet)(SrcSpan(_parsx_1.where, _parsx_4.last->expr->where), _parsx_2, _parsx_4));
					}
				}break;
				case 63:{
					{
						parsx_push_value(List<TypeList>, List<TypeList>());
					}
				}break;
				case 64:{
					{
						MatchBranch<Expr>* _parsx_5 = parsx_pop_value(MatchBranch<Expr>*);
						Expr* _parsx_4 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(MatchBranch<Expr>*, alloc(MatchBranch<Expr>)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
					}
				}break;
				case 65:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
					}
				}break;
				case 66:{
					{
						parsx_push_value(List< MatchCase<Stmt> >, List< MatchCase<Stmt> >());
					}
				}break;
				case 67:{
					{
						MatchCase<Stmt>* _parsx_2 = parsx_pop_value(MatchCase<Stmt>*);
						List< MatchCase<Stmt> > _parsx_1 = parsx_pop_value(List< MatchCase<Stmt> >);
						parsx_push_value(List< MatchCase<Stmt> >, _parsx_1.append(_parsx_2));
					}
				}break;
				case 68:{
				}break;
				case 69:{
					{
						parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprCall)(SrcSpan(_parsx_2.where, _parsx_4.where), _parsx_1, _parsx_3));
					}
				}break;
				case 70:{
				}break;
				case 71:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
					}
				}break;
				case 72:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Eval, _parsx_2));
					}
				}break;
				case 73:{
					{
						Expr* _parsx_5 = parsx_pop_value(Expr*);
						Expr* _parsx_4 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
					}
				}break;
				case 74:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprInstance)(SrcSpan(_parsx_2.where, _parsx_5.where), _parsx_1, _parsx_4));
					}
				}break;
				case 75:{
					{
						Expr* _parsx_5 = parsx_pop_value(Expr*);
						Type* _parsx_4 = parsx_pop_value(Type*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Name> _parsx_2 = parsx_pop_value(List<Name>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
					}
				}break;
				case 76:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
					}
				}break;
				case 77:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprInstance)(SrcSpan(_parsx_2.where, _parsx_5.where), _parsx_1, _parsx_4));
					}
				}break;
				case 78:{
				}break;
				case 79:{
					{
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<Name> _parsx_1 = parsx_pop_value(List<Name>);
						parsx_push_value(List<Name>, _parsx_1.append(alloc(Name)(_parsx_2.where, sym(_parsx_2))));
					}
				}break;
				case 80:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, _parsx_2);
					}
				}break;
				case 81:{
					{
						Expr* _parsx_5 = parsx_pop_value(Expr*);
						Expr* _parsx_4 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
					}
				}break;
				case 82:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1.where.from(), alloc(TypeReferenceLeaf)(sym(_parsx_1))));
					}
					{
						WithSrcLoc<TypeReferenceNode*> _parsx_1 = parsx_pop_value(WithSrcLoc<TypeReferenceNode*>);
						parsx_push_value(Type*, alloc(TypeReference)(to_here(_parsx_1), _parsx_1));
					}
					{
						Type* _parsx_1 = parsx_pop_value(Type*);
						parsx_push_value(ParamGroup*, alloc(ParamGroup)(nullptr, _parsx_1));
					}
				}break;
				case 83:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List< MatchCase<Expr> > _parsx_4 = parsx_pop_value(List< MatchCase<Expr> >);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprMatch)(SrcSpan(_parsx_1.where, _parsx_5.where), _parsx_2, _parsx_4));
					}
				}break;
				case 84:{
					{
						parsx_push_value(MatchBranch<Stmt>*, nullptr);
					}
				}break;
				case 85:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, _parsx_2);
					}
				}break;
				case 86:{
					{
						Expr* _parsx_4 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtRepeat)(_parsx_1.where, _parsx_2, _parsx_4));
					}
				}break;
				case 87:{
				}break;
				case 88:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Not, _parsx_2));
					}
				}break;
				case 89:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
					}
				}break;
				case 90:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Concat, _parsx_1, _parsx_3));
					}
				}break;
				case 91:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Plus, _parsx_1, _parsx_3));
					}
				}break;
				case 92:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Minus, _parsx_1, _parsx_3));
					}
				}break;
				case 93:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Type* _parsx_2 = parsx_pop_value(Type*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Type*, _parsx_2);
					}
				}break;
				case 94:{
					{
						List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(MatchBranch<Stmt>*, alloc(MatchBranch<Stmt>)(_parsx_1.where, nullptr, _parsx_2));
					}
				}break;
				case 95:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Mult, _parsx_1, _parsx_3));
					}
				}break;
				case 96:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Div, _parsx_1, _parsx_3));
					}
				}break;
				case 97:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Rem, _parsx_1, _parsx_3));
					}
				}break;
				case 98:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						List<Name> _parsx_2 = parsx_pop_value(List<Name>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, nullptr, _parsx_3));
					}
				}break;
				case 99:{
					{
						MatchCase<Expr>* _parsx_2 = parsx_pop_value(MatchCase<Expr>*);
						List< MatchCase<Expr> > _parsx_1 = parsx_pop_value(List< MatchCase<Expr> >);
						parsx_push_value(List< MatchCase<Expr> >, _parsx_1.append(_parsx_2));
					}
				}break;
				case 100:{
					{
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						int _parsx_1 = parsx_pop_value(int);
						parsx_push_value(int, _parsx_1 + 1);
					}
				}break;
				case 101:{
					{
						parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprCall)(SrcSpan(_parsx_2.where, _parsx_4.where), _parsx_1, _parsx_3));
					}
				}break;
				case 102:{
					{
						Expr* _parsx_5 = parsx_pop_value(Expr*);
						Type* _parsx_4 = parsx_pop_value(Type*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Name> _parsx_2 = parsx_pop_value(List<Name>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
					}
				}break;
				case 103:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
					}
				}break;
				case 104:{
				}break;
				case 105:{
				}break;
				case 106:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprInstance)(SrcSpan(_parsx_2.where, _parsx_5.where), _parsx_1, _parsx_4));
					}
				}break;
				case 107:{
					{
						MatchBranch<Expr>* _parsx_3 = parsx_pop_value(MatchBranch<Expr>*);
						List<Pattern> _parsx_2 = parsx_pop_value(List<Pattern>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(MatchCase<Expr>*, alloc(MatchCase<Expr>)(_parsx_1.where, _parsx_2, _parsx_3));
					}
				}break;
				case 108:{
					{
						Expr* _parsx_5 = parsx_pop_value(Expr*);
						Expr* _parsx_4 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
					}
				}break;
				case 109:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List< MatchCase<Expr> > _parsx_4 = parsx_pop_value(List< MatchCase<Expr> >);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprMatch)(SrcSpan(_parsx_1.where, _parsx_5.where), _parsx_2, _parsx_4));
					}
				}break;
				case 110:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Name> _parsx_2 = parsx_pop_value(List<Name>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, nullptr, nullptr));
					}
				}break;
				case 111:{
					{
						Pattern* _parsx_2 = parsx_pop_value(Pattern*);
						QualID* _parsx_1 = parsx_pop_value(QualID*);
						parsx_push_value(Pattern*, alloc(PatternCons)(_parsx_1->where, _parsx_1, _parsx_2));
					}
				}break;
				case 112:{
					{
						parsx_push_value(List<Pattern>, List<Pattern>());
					}
				}break;
				case 113:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, _parsx_2);
					}
				}break;
				case 114:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprString)(_parsx_1.where, lit(_parsx_1)));
					}
				}break;
				case 115:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List<Stmt> _parsx_4 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtWhile)(_parsx_1.where, _parsx_2, _parsx_4));
					}
				}break;
				case 116:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(List<Name>, alloc(Name)(_parsx_1.where, sym(_parsx_1)));
					}
				}break;
				case 117:{
					{
						parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprCall)(SrcSpan(_parsx_2.where, _parsx_4.where), _parsx_1, _parsx_3));
					}
				}break;
				case 118:{
					{
						ParamGroup* _parsx_1 = parsx_pop_value(ParamGroup*);
						parsx_push_value(List<ParamGroup>, List<ParamGroup>(_parsx_1));
					}
				}break;
				case 119:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprInstance)(SrcSpan(_parsx_2.where, _parsx_5.where), _parsx_1, _parsx_4));
					}
				}break;
				case 120:{
					{
						parsx_push_value(List<AssignPair>, List<AssignPair>());
					}
				}break;
				case 121:{
					{
						Type* _parsx_2 = parsx_pop_value(Type*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Type*, _parsx_2);
					}
				}break;
				case 122:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtBlock)(SrcSpan(_parsx_1.where, _parsx_3.where), _parsx_2));
					}
				}break;
				case 123:{
				}break;
				case 124:{
				}break;
				case 125:{
					{
						List<ExprList> _parsx_4 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Pattern> _parsx_2 = parsx_pop_value(List<Pattern>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtLet)(SrcSpan(_parsx_1.where, _parsx_4.last->expr->where), _parsx_2, _parsx_4));
					}
				}break;
				case 126:{
					{
						parsx_token_type _parsx_6 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_5 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<ConstructorStringPart> _parsx_1 = parsx_pop_value(List<ConstructorStringPart>);
						parsx_push_value(List<ConstructorStringPart>, alloc(ConstructorStringPart)(_parsx_1, _parsx_3.where, sym(_parsx_3), _parsx_5));
					}
				}break;
				case 127:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List< MatchCase<Stmt> > _parsx_4 = parsx_pop_value(List< MatchCase<Stmt> >);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtMatch)(SrcSpan(_parsx_1.where, _parsx_5.where), _parsx_2, _parsx_4));
					}
				}break;
				case 128:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
						SrcLoc _parsx_1 = parsx_pop_value(SrcLoc);
						parsx_push_value(FunctionBody*, alloc(FunctionBodyDefined)(to_here(_parsx_1), _parsx_2));
					}
				}break;
				case 129:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::NE, _parsx_1, _parsx_3));
					}
				}break;
				case 130:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Not, _parsx_2));
					}
				}break;
				case 131:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Minus, _parsx_1, _parsx_3));
					}
				}break;
				case 132:{
					{
						Stmt* _parsx_2 = parsx_pop_value(Stmt*);
						List<Stmt> _parsx_1 = parsx_pop_value(List<Stmt>);
						parsx_push_value(List<Stmt>, _parsx_1.append(_parsx_2));
					}
				}break;
				case 133:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::LE, _parsx_1, _parsx_3));
					}
				}break;
				case 134:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Negate, _parsx_2));
					}
				}break;
				case 135:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::GE, _parsx_1, _parsx_3));
					}
				}break;
				case 136:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Not, _parsx_2));
					}
				}break;
				case 137:{
					{
						Type* _parsx_3 = parsx_pop_value(Type*);
						List<Name> _parsx_2 = parsx_pop_value(List<Name>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(ClassMember*, alloc(ClassField)(_parsx_2, _parsx_3));
					}
				}break;
				case 138:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::GT, _parsx_1, _parsx_3));
					}
				}break;
				case 139:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(FunctionBody*, alloc(FunctionBodyExpr)(_parsx_1.where, _parsx_2));
					}
				}break;
				case 140:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Rem, _parsx_1, _parsx_3));
					}
				}break;
				case 141:{
					{
						Type* _parsx_2 = parsx_pop_value(Type*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Type*, _parsx_2);
					}
				}break;
				case 142:{
					{
						Type* _parsx_3 = parsx_pop_value(Type*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprCoerce)(SrcSpan(_parsx_1->where, _parsx_3->where), _parsx_1, _parsx_3));
					}
				}break;
				case 143:{
					{
						List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_1 = parsx_pop_value(List<ExprList>);
						parsx_push_value(Stmt*, alloc(StmtAssign)(SrcSpan(_parsx_1.first->expr->where, _parsx_3.last->expr->where), _parsx_1, _parsx_3));
					}
				}break;
				case 144:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Or, _parsx_1, _parsx_3));
					}
				}break;
				case 145:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Not, _parsx_2));
					}
				}break;
				case 146:{
					{
						Type* _parsx_1 = parsx_pop_value(Type*);
						parsx_push_value(ParamGroup*, alloc(ParamGroup)(nullptr, _parsx_1));
					}
				}break;
				case 147:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_1 = parsx_pop_value(List<ExprList>);
						parsx_push_value(List<ExprList>, _parsx_1.append(alloc(ExprList)(_parsx_3)));
					}
				}break;
				case 148:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::And, _parsx_1, _parsx_3));
					}
				}break;
				case 149:{
					{
						use_decl
					}
				}break;
				case 150:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List<AssignPair> _parsx_4 = parsx_pop_value(List<AssignPair>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<ConstructorStringPart> _parsx_2 = parsx_pop_value(List<ConstructorStringPart>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtConstruct)(_parsx_1.where, _parsx_2, _parsx_4));
					}
				}break;
				case 151:{
					{
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(List<ExprList>, alloc(ExprList)(_parsx_1));
					}
				}break;
				case 152:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
					}
				}break;
				case 153:{
					{
						List<ConstructorStringPart> _parsx_3 = parsx_pop_value(List<ConstructorStringPart>);
						QualID* _parsx_2 = parsx_pop_value(QualID*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprNew)(SrcSpan(_parsx_1.where), _parsx_2, _parsx_3));
					}
				}break;
				case 154:{
					{
						Type* _parsx_3 = parsx_pop_value(Type*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprCoerce)(SrcSpan(_parsx_1->where, _parsx_3->where), _parsx_1, _parsx_3));
					}
				}break;
				case 155:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprInstance)(SrcSpan(_parsx_2.where, _parsx_5.where), _parsx_1, _parsx_4));
					}
				}break;
				case 156:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, _parsx_2);
					}
				}break;
				case 157:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Or, _parsx_1, _parsx_3));
					}
				}break;
				case 158:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Plus, _parsx_1, _parsx_3));
					}
				}break;
				case 159:{
					{
						QualID* _parsx_2 = parsx_pop_value(QualID*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(QualID*, _parsx_2);
					}
				}break;
				case 160:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Minus, _parsx_1, _parsx_3));
					}
				}break;
				case 161:{
					{
						parsx_push_value(Pattern*, nullptr);
					}
				}break;
				case 162:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::And, _parsx_1, _parsx_3));
					}
				}break;
				case 163:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List< MatchCase<Expr> > _parsx_4 = parsx_pop_value(List< MatchCase<Expr> >);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprMatch)(SrcSpan(_parsx_1.where, _parsx_5.where), _parsx_2, _parsx_4));
					}
				}break;
				case 164:{
				}break;
				case 165:{
					{
						FunctionBody* _parsx_4 = parsx_pop_value(FunctionBody*);
						FunctionSignature* _parsx_3 = parsx_pop_value(FunctionSignature*);
						QualID* _parsx_2 = parsx_pop_value(QualID*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(ClassMember*, alloc(ClassConstructor)(_parsx_1.where, StringRef(), _parsx_2, _parsx_3, _parsx_4));
					}
				}break;
				case 166:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Mult, _parsx_1, _parsx_3));
					}
				}break;
				case 167:{
					{
						parsx_push_value(List<Implements>, List<Implements>());
					}
				}break;
				case 168:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Div, _parsx_1, _parsx_3));
					}
				}break;
				case 169:{
					{
						Expr* _parsx_4 = parsx_pop_value(Expr*);
						Type* _parsx_3 = parsx_pop_value(Type*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(TopLevel*, alloc(GlobalVariable)(_parsx_2.where, sym(_parsx_2), _parsx_3, _parsx_4));
					}
				}break;
				case 170:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Negate, _parsx_2));
					}
				}break;
				case 171:{
					{
						List<ConstructorStringPart> _parsx_2 = parsx_pop_value(List<ConstructorStringPart>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtConstructPass)(_parsx_1.where, _parsx_2));
					}
				}break;
				case 172:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Div, _parsx_1, _parsx_3));
					}
				}break;
				case 173:{
				}break;
				case 174:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Not, _parsx_2));
					}
				}break;
				case 175:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Plus, _parsx_1, _parsx_3));
					}
				}break;
				case 176:{
					{
						parsx_push_value(List<EnumConstructor>, List<EnumConstructor>());
					}
				}break;
				case 177:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Minus, _parsx_1, _parsx_3));
					}
				}break;
				case 178:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Minus, _parsx_1, _parsx_3));
					}
				}break;
				case 179:{
					{
						EnumConstructor* _parsx_2 = parsx_pop_value(EnumConstructor*);
						List<EnumConstructor> _parsx_1 = parsx_pop_value(List<EnumConstructor>);
						parsx_push_value(List<EnumConstructor>, _parsx_1.append(_parsx_2));
					}
				}break;
				case 180:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Pattern*, alloc(PatternPrim)(_parsx_1.where, PatternPrim::True));
					}
				}break;
				case 181:{
					{
						Type* _parsx_3 = parsx_pop_value(Type*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprCoerce)(SrcSpan(_parsx_1->where, _parsx_3->where), _parsx_1, _parsx_3));
					}
				}break;
				case 182:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(FunctionBody*, alloc(FunctionBodyExpr)(_parsx_1.where, _parsx_2));
					}
				}break;
				case 183:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(QualID*, alloc(QualID)(SrcSpan(_parsx_1.where, _parsx_3.where), alloc(QualID)(SrcSpan(_parsx_1.where), sym(_parsx_1)), sym(_parsx_3)));
					}
				}break;
				case 184:{
				}break;
				case 185:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::LT, _parsx_1, _parsx_3));
					}
				}break;
				case 186:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Pattern*, alloc(PatternPrim)(_parsx_1.where, PatternPrim::Null));
					}
				}break;
				case 187:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Div, _parsx_1, _parsx_3));
					}
				}break;
				case 188:{
					{
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<Stmt> _parsx_1 = parsx_pop_value(List<Stmt>);
						parsx_push_value(List<Stmt>, _parsx_1);
					}
				}break;
				case 189:{
					{
						List<TypeList> _parsx_1 = parsx_pop_value(List<TypeList>);
						parsx_push_value(Type*, alloc(TypeUnion)(SrcSpan(_parsx_1.first->type->where.from(), _parsx_1.last->type->where.to()), _parsx_1));
					}
				}break;
				case 190:{
					{
						parsx_token_type _parsx_6 = parsx_pop_value(parsx_token_type);
						List<ClassMember> _parsx_5 = parsx_pop_value(List<ClassMember>);
						List<Implements> _parsx_4 = parsx_pop_value(List<Implements>);
						Extends* _parsx_3 = parsx_pop_value(Extends*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(TopLevel*, alloc(Class)(_parsx_2.where, sym(_parsx_2), _parsx_3, _parsx_4, _parsx_5));
					}
				}break;
				case 191:{
					{
						Stmt* _parsx_1 = parsx_pop_value(Stmt*);
						parsx_push_value(List<Stmt>, List<Stmt>(_parsx_1));
					}
				}break;
				case 192:{
				}break;
				case 193:{
				}break;
				case 194:{
					{
						FunctionSignature* _parsx_3 = parsx_pop_value(FunctionSignature*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(ClassMember*, alloc(ClassMethod)(ClassMethod::Abstract, _parsx_2.where, sym(_parsx_2), _parsx_3, nullptr));
					}
				}break;
				case 195:{
					{
						parsx_push_value(int, 0);
					}
				}break;
				case 196:{
					{
						Type* _parsx_3 = parsx_pop_value(Type*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<TypeList> _parsx_1 = parsx_pop_value(List<TypeList>);
						parsx_push_value(List<TypeList>, _parsx_1.append(alloc(TypeList)(_parsx_3)));
					}
				}break;
				case 197:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Pattern*, alloc(PatternNumber)(_parsx_1.where, sym(_parsx_1)));
					}
				}break;
				case 198:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Raise, _parsx_2));
					}
				}break;
				case 199:{
					{
						FunctionBody* _parsx_4 = parsx_pop_value(FunctionBody*);
						FunctionSignature* _parsx_3 = parsx_pop_value(FunctionSignature*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(ClassMember*, alloc(ClassMethod)(ClassMethod::Method, _parsx_2.where, sym(_parsx_2), _parsx_3, _parsx_4));
					}
				}break;
				case 200:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						QualID* _parsx_1 = parsx_pop_value(QualID*);
						parsx_push_value(QualID*, alloc(QualID)(jf::SrcSpan(_parsx_1->where.from(), _parsx_3.where.to()), _parsx_1, sym(_parsx_3)));
					}
				}break;
				case 201:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::LT, _parsx_1, _parsx_3));
					}
				}break;
				case 202:{
					{
						parsx_push_value(Type*, nullptr);
					}
				}break;
				case 203:{
				}break;
				case 204:{
				}break;
				case 205:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::EQ, _parsx_1, _parsx_3));
					}
				}break;
				case 206:{
				}break;
				case 207:{
				}break;
				case 208:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Concat, _parsx_1, _parsx_3));
					}
				}break;
				case 209:{
				}break;
				case 210:{
					{
						parsx_push_value(List<StructField>, List<StructField>());
					}
				}break;
				case 211:{
				}break;
				case 212:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Plus, _parsx_1, _parsx_3));
					}
				}break;
				case 213:{
					{
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Type* _parsx_1 = parsx_pop_value(Type*);
						parsx_push_value(Type*, alloc(TypeOptional)(SrcSpan(_parsx_1->where.from(), _parsx_2.where.to()), _parsx_1));
					}
				}break;
				case 214:{
				}break;
				case 215:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Unit));
					}
				}break;
				case 216:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Undef));
					}
				}break;
				case 217:{
				}break;
				case 218:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Bool));
					}
				}break;
				case 219:{
				}break;
				case 220:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Int));
					}
				}break;
				case 221:{
				}break;
				case 222:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Pattern* _parsx_2 = parsx_pop_value(Pattern*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Pattern*, _parsx_2);
					}
				}break;
				case 223:{
				}break;
				case 224:{
				}break;
				case 225:{
				}break;
				case 226:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Double));
					}
				}break;
				case 227:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::String));
					}
				}break;
				case 228:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_1 = parsx_pop_value(List<ExprList>);
						parsx_push_value(List<ExprList>, _parsx_1.append(alloc(ExprList)(_parsx_3)));
					}
				}break;
				case 229:{
					{
						parsx_push_value(List<ExprList>, List<ExprList>());
					}
				}break;
				case 230:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Bytes));
					}
				}break;
				case 231:{
				}break;
				case 232:{
				}break;
				case 233:{
				}break;
				case 234:{
					{
						WithSrcLoc<TypeReferenceNode*> _parsx_1 = parsx_pop_value(WithSrcLoc<TypeReferenceNode*>);
						parsx_push_value(Type*, alloc(TypeReference)(to_here(_parsx_1), _parsx_1));
					}
				}break;
				case 235:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Pattern*, alloc(PatternVar)(_parsx_1.where, sym(_parsx_1)));
					}
				}break;
				case 236:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						WithSrcLoc<TypeReferenceNode*> _parsx_1 = parsx_pop_value(WithSrcLoc<TypeReferenceNode*>);
						parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1, alloc(TypeReferenceSubscript)(_parsx_1, sym(_parsx_3))));
					}
				}break;
				case 237:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_1 = parsx_pop_value(List<ExprList>);
						parsx_push_value(List<ExprList>, _parsx_1.append(alloc(ExprList)(_parsx_3)));
					}
				}break;
				case 238:{
				}break;
				case 239:{
					{
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(List<ExprList>, alloc(ExprList)(_parsx_1));
					}
				}break;
				case 240:{
				}break;
				case 241:{
				}break;
				case 242:{
				}break;
				case 243:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprInstance)(SrcSpan(_parsx_2.where, _parsx_5.where), _parsx_1, _parsx_4));
					}
				}break;
				case 244:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Negate, _parsx_2));
					}
				}break;
				case 245:{
					{
						Type* _parsx_3 = parsx_pop_value(Type*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<TypeList> _parsx_1 = parsx_pop_value(List<TypeList>);
						parsx_push_value(List<TypeList>, _parsx_1.append(alloc(TypeList)(_parsx_3)));
					}
				}break;
				case 246:{
				}break;
				case 247:{
					{
						Type* _parsx_1 = parsx_pop_value(Type*);
						parsx_push_value(List<TypeList>, alloc(TypeList)(_parsx_1));
					}
				}break;
				case 248:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::EQ, _parsx_1, _parsx_3));
					}
				}break;
				case 249:{
				}break;
				case 250:{
					{
						parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprCall)(SrcSpan(_parsx_2.where, _parsx_4.where), _parsx_1, _parsx_3));
					}
				}break;
				case 251:{
				}break;
				case 252:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						WithSrcLoc<TypeReferenceNode*> _parsx_1 = parsx_pop_value(WithSrcLoc<TypeReferenceNode*>);
						parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1, alloc(TypeReferenceInstance)(_parsx_1, List<TypeList>())));
					}
				}break;
				case 253:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, _parsx_2);
					}
				}break;
				case 254:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1.where.from(), alloc(TypeReferenceLeaf)(sym(_parsx_1))));
					}
				}break;
				case 255:{
					{
						Expr* _parsx_5 = parsx_pop_value(Expr*);
						Expr* _parsx_4 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
					}
				}break;
				case 256:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<TypeList> _parsx_2 = parsx_pop_value(List<TypeList>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Type*, alloc(TypeTuple)(SrcSpan(_parsx_1.where.from(), _parsx_3.where.to()), _parsx_2));
					}
				}break;
				case 257:{
					{
						parsx_push_value(List< MatchCase<Expr> >, List< MatchCase<Expr> >());
					}
				}break;
				case 258:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List< MatchCase<Expr> > _parsx_4 = parsx_pop_value(List< MatchCase<Expr> >);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprMatch)(SrcSpan(_parsx_1.where, _parsx_5.where), _parsx_2, _parsx_4));
					}
				}break;
				case 259:{
				}break;
				case 260:{
					{
						Type* _parsx_4 = parsx_pop_value(Type*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Type*, alloc(TypeFunction)(SrcSpan(_parsx_1.where, _parsx_4->where), nullptr, _parsx_4));
					}
				}break;
				case 261:{
					{
						Type* _parsx_5 = parsx_pop_value(Type*);
						parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<TypeList> _parsx_2 = parsx_pop_value(List<TypeList>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Type*, alloc(TypeFunction)(SrcSpan(_parsx_1.where, _parsx_5->where), _parsx_2, _parsx_5));
					}
				}break;
				case 262:{
					{
						FunctionBody* _parsx_4 = parsx_pop_value(FunctionBody*);
						FunctionSignature* _parsx_3 = parsx_pop_value(FunctionSignature*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(ClassMember*, alloc(ClassMethod)(ClassMethod::Override, _parsx_2.where, sym(_parsx_2), _parsx_3, _parsx_4));
					}
				}break;
				case 263:{
				}break;
				case 264:{
					{
						Type* _parsx_3 = parsx_pop_value(Type*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<TypeList> _parsx_1 = parsx_pop_value(List<TypeList>);
						parsx_push_value(List<TypeList>, _parsx_1.append(alloc(TypeList)(_parsx_3)));
					}
				}break;
				case 265:{
					{
						parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprCall)(SrcSpan(_parsx_2.where, _parsx_4.where), _parsx_1, _parsx_3));
					}
				}break;
				case 266:{
					{
						Type* _parsx_3 = parsx_pop_value(Type*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Type* _parsx_1 = parsx_pop_value(Type*);
						parsx_push_value(List<TypeList>, List<TypeList>(alloc(TypeList)(_parsx_1)).append(alloc(TypeList)(_parsx_3)));
					}
				}break;
				case 267:{
				}break;
				case 268:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Concat, _parsx_1, _parsx_3));
					}
				}break;
				case 269:{
					{
						Pattern* _parsx_3 = parsx_pop_value(Pattern*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<Pattern> _parsx_1 = parsx_pop_value(List<Pattern>);
						parsx_push_value(List<Pattern>, _parsx_1.append(_parsx_3));
					}
				}break;
				case 270:{
					{
						Type* _parsx_3 = parsx_pop_value(Type*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Type* _parsx_1 = parsx_pop_value(Type*);
						parsx_push_value(List<TypeList>, List<TypeList>(alloc(TypeList)(_parsx_1)).append(alloc(TypeList)(_parsx_3)));
					}
				}break;
				case 271:{
				}break;
				case 272:{
				}break;
				case 273:{
				}break;
				case 274:{
					{
						FunctionBody* _parsx_5 = parsx_pop_value(FunctionBody*);
						FunctionSignature* _parsx_4 = parsx_pop_value(FunctionSignature*);
						QualID* _parsx_3 = parsx_pop_value(QualID*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(ClassMember*, alloc(ClassConstructor)(_parsx_2.where, sym(_parsx_2), _parsx_3, _parsx_4, _parsx_5));
					}
				}break;
				case 275:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Pattern* _parsx_1 = parsx_pop_value(Pattern*);
						parsx_push_value(Pattern*, alloc(PatternRemember)(_parsx_3.where, _parsx_1, sym(_parsx_3)));
					}
				}break;
				case 276:{
					{
						parsx_token_type _parsx_7 = parsx_pop_value(parsx_token_type);
						List<Stmt> _parsx_6 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_4 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Name> _parsx_2 = parsx_pop_value(List<Name>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtFor)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_6));
					}
				}break;
				case 277:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Or, _parsx_1, _parsx_3));
					}
				}break;
				case 278:{
					{
						Type* _parsx_4 = parsx_pop_value(Type*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<ParamGroup> _parsx_2 = parsx_pop_value(List<ParamGroup>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(FunctionSignature*, alloc(FunctionSignature)(to_here(_parsx_1.where.from()), _parsx_2, _parsx_4));
					}
				}break;
				case 279:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::NE, _parsx_1, _parsx_3));
					}
				}break;
				case 280:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Negate, _parsx_2));
					}
				}break;
				case 281:{
					{
						parsx_push_value(QualID*, nullptr);
					}
				}break;
				case 282:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Mult, _parsx_1, _parsx_3));
					}
				}break;
				case 283:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Not, _parsx_2));
					}
				}break;
				case 284:{
					{
						Type* _parsx_3 = parsx_pop_value(Type*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Type* _parsx_1 = parsx_pop_value(Type*);
						parsx_push_value(Type*, alloc(TypeFunction)(SrcSpan(_parsx_1->where, _parsx_3->where), alloc(TypeList)(_parsx_1), _parsx_3));
					}
				}break;
				case 285:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Rem, _parsx_1, _parsx_3));
					}
				}break;
				case 286:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::LE, _parsx_1, _parsx_3));
					}
				}break;
				case 287:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::GE, _parsx_1, _parsx_3));
					}
				}break;
				case 288:{
				}break;
				case 289:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::GT, _parsx_1, _parsx_3));
					}
				}break;
				case 290:{
				}break;
				case 291:{
				}break;
				case 292:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::And, _parsx_1, _parsx_3));
					}
				}break;
				case 293:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Plus, _parsx_1, _parsx_3));
					}
				}break;
				case 294:{
					{
						parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprCall)(SrcSpan(_parsx_2.where, _parsx_4.where), _parsx_1, _parsx_3));
					}
				}break;
				case 295:{
					{
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(FunctionBody*, alloc(FunctionBodyImport)(_parsx_2.where, lit(_parsx_2)));
					}
				}break;
				case 296:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
					}
				}break;
				case 297:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprInstance)(SrcSpan(_parsx_2.where, _parsx_5.where), _parsx_1, _parsx_4));
					}
				}break;
				case 298:{
				}break;
				case 299:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, _parsx_2);
					}
				}break;
				case 300:{
					{
						Expr* _parsx_5 = parsx_pop_value(Expr*);
						Expr* _parsx_4 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, alloc(ExprIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
					}
				}break;
				case 301:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(EnumConstructor*, alloc(EnumConstructor)(_parsx_1.where, sym(_parsx_1), nullptr));
					}
				}break;
				case 302:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::NE, _parsx_1, _parsx_3));
					}
				}break;
				case 303:{
				}break;
				case 304:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::LE, _parsx_1, _parsx_3));
					}
				}break;
				case 305:{
					{
						parsx_push_value(List<ConstructorStringPart>, nullptr);
					}
					{
						List<ConstructorStringPart> _parsx_2 = parsx_pop_value(List<ConstructorStringPart>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtConstructPass)(_parsx_1.where, _parsx_2));
					}
				}break;
				case 306:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::GE, _parsx_1, _parsx_3));
					}
				}break;
				case 307:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<ParamGroup> _parsx_2 = parsx_pop_value(List<ParamGroup>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(FunctionSignature*, alloc(FunctionSignature)(to_here(_parsx_1.where.from()), _parsx_2, nullptr));
					}
				}break;
				case 308:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::LT, _parsx_1, _parsx_3));
					}
				}break;
				case 309:{
				}break;
				case 310:{
					{
						List<Stmt> _parsx_5 = parsx_pop_value(List<Stmt>);
						List<Stmt> _parsx_4 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
					}
				}break;
				case 311:{
					{
						List<Stmt> _parsx_5 = parsx_pop_value(List<Stmt>);
						List<Stmt> _parsx_4 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
					}
				}break;
				case 312:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
					}
				}break;
				case 313:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(List<Stmt>, nullptr);
					}
				}break;
				case 314:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(List<Stmt>, _parsx_2);
					}
				}break;
				case 315:{
					{
						List<Stmt> _parsx_5 = parsx_pop_value(List<Stmt>);
						List<Stmt> _parsx_4 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(List<Stmt>, alloc(StmtIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
					}
				}break;
				case 316:{
				}break;
				case 317:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List<Stmt> _parsx_4 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtWhile)(_parsx_1.where, _parsx_2, _parsx_4));
					}
				}break;
				case 318:{
				}break;
				case 319:{
					{
						Expr* _parsx_4 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtRepeat)(_parsx_1.where, _parsx_2, _parsx_4));
					}
				}break;
				case 320:{
				}break;
				case 321:{
					{
						parsx_token_type _parsx_7 = parsx_pop_value(parsx_token_type);
						List<Stmt> _parsx_6 = parsx_pop_value(List<Stmt>);
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_4 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Name> _parsx_2 = parsx_pop_value(List<Name>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtFor)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_6));
					}
				}break;
				case 322:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						List<Name> _parsx_2 = parsx_pop_value(List<Name>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, nullptr, _parsx_3));
					}
				}break;
				case 323:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::EQ, _parsx_1, _parsx_3));
					}
				}break;
				case 324:{
					{
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Expr*, _parsx_2);
					}
				}break;
				case 325:{
				}break;
				case 326:{
					{
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1->where, StmtEval::Naked, _parsx_1));
					}
				}break;
				case 327:{
					{
						FunctionBody* _parsx_4 = parsx_pop_value(FunctionBody*);
						FunctionSignature* _parsx_3 = parsx_pop_value(FunctionSignature*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(TopLevel*, alloc(GlobalFunction)(_parsx_2.where, sym(_parsx_2), _parsx_3, _parsx_4));
					}
				}break;
				case 328:{
				}break;
				case 329:{
					{
						FunctionSignature* _parsx_2 = parsx_pop_value(FunctionSignature*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(EnumConstructor*, alloc(EnumConstructor)(_parsx_1.where, sym(_parsx_1), _parsx_2));
					}
				}break;
				case 330:{
					{
						List<ConstructorStringPart> _parsx_2 = parsx_pop_value(List<ConstructorStringPart>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtConstructPass)(_parsx_1.where, _parsx_2));
					}
				}break;
				case 331:{
					{
						parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
						List<InterfaceMethod> _parsx_4 = parsx_pop_value(List<InterfaceMethod>);
						List<Implements> _parsx_3 = parsx_pop_value(List<Implements>);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(TopLevel*, alloc(Interface)(_parsx_2.where, sym(_parsx_2), _parsx_3, _parsx_4));
					}
				}break;
				case 332:{
					{
						parsx_push_value(List<Implements>, List<Implements>());
					}
				}break;
				case 333:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
				}break;
				case 334:{
					{
						parsx_push_value(List<InterfaceMethod>, List<InterfaceMethod>());
					}
				}break;
				case 335:{
					{
						QualID* _parsx_3 = parsx_pop_value(QualID*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<Implements> _parsx_1 = parsx_pop_value(List<Implements>);
						parsx_push_value(List<Implements>, _parsx_1.append(alloc(Implements)(_parsx_3->where, _parsx_3)));
					}
				}break;
				case 336:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Concat, _parsx_1, _parsx_3));
					}
				}break;
				case 337:{
				}break;
				case 338:{
				}break;
				case 339:{
				}break;
				case 340:{
					{
						FunctionSignature* _parsx_4 = parsx_pop_value(FunctionSignature*);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<InterfaceMethod> _parsx_1 = parsx_pop_value(List<InterfaceMethod>);
						parsx_push_value(List<InterfaceMethod>, _parsx_1.append(alloc(InterfaceMethod)(_parsx_3.where, sym(_parsx_3), _parsx_4)));
					}
				}break;
				case 341:{
				}break;
				case 342:{
					{
						Expr* _parsx_3 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Mult, _parsx_1, _parsx_3));
					}
				}break;
				case 343:{
					{
						Pattern* _parsx_2 = parsx_pop_value(Pattern*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Pattern*, alloc(PatternCons)(to_here(_parsx_1.where.from()), alloc(QualID)(_parsx_1.where, sym(_parsx_1)), _parsx_2));
					}
				}break;
				case 344:{
					{
						parsx_push_value(Extends*, nullptr);
					}
				}break;
				case 345:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Pattern*, alloc(PatternPrim)(_parsx_1.where, PatternPrim::Unit));
					}
				}break;
				case 346:{
					{
						QualID* _parsx_2 = parsx_pop_value(QualID*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Extends*, alloc(Extends)(_parsx_2->where, _parsx_2));
					}
				}break;
				case 347:{
				}break;
				case 348:{
				}break;
				case 349:{
					{
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1->where, StmtEval::Naked, _parsx_1));
					}
				}break;
				case 350:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(int, 1);
					}
				}break;
				case 351:{
				}break;
				case 352:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Pattern*, alloc(PatternPrim)(_parsx_1.where, PatternPrim::False));
					}
				}break;
				case 353:{
					{
						parsx_push_value(List<ClassMember>, List<ClassMember>());
					}
				}break;
				case 354:{
					{
						QualID* _parsx_3 = parsx_pop_value(QualID*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						List<Implements> _parsx_1 = parsx_pop_value(List<Implements>);
						parsx_push_value(List<Implements>, _parsx_1.append(alloc(Implements)(_parsx_3->where, _parsx_3)));
					}
				}break;
				case 355:{
				}break;
				case 356:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Pattern*, alloc(PatternPrim)(_parsx_1.where, PatternPrim::Wildcard));
					}
				}break;
				case 357:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Pattern*, alloc(PatternVar)(_parsx_1.where, sym(_parsx_1)));
					}
				}break;
				case 358:{
					{
						ClassMember* _parsx_2 = parsx_pop_value(ClassMember*);
						List<ClassMember> _parsx_1 = parsx_pop_value(List<ClassMember>);
						parsx_push_value(List<ClassMember>, _parsx_1.append(_parsx_2));
					}
				}break;
				case 359:{
				}break;
				case 360:{
				}break;
				case 361:{
					{
						parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
						List<StructField> _parsx_3 = parsx_pop_value(List<StructField>);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(TopLevel*, alloc(Struct)(_parsx_2.where, sym(_parsx_2), _parsx_3));
					}
				}break;
				case 362:{
					{
						int _parsx_4 = parsx_pop_value(int);
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						int _parsx_2 = parsx_pop_value(int);
						SrcLoc _parsx_1 = parsx_pop_value(SrcLoc);
						parsx_push_value(EnumConstructorNumber, EnumConstructorNumber(to_here(_parsx_1), _parsx_2, _parsx_2 + _parsx_4));
					}
				}break;
				case 363:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_2 = parsx_pop_value(Expr*);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Pattern*, alloc(PatternQuote)(_parsx_2->where, _parsx_2));
					}
				}break;
				case 364:{
					{
						StructField* _parsx_2 = parsx_pop_value(StructField*);
						List<StructField> _parsx_1 = parsx_pop_value(List<StructField>);
						parsx_push_value(List<StructField>, _parsx_1.append(_parsx_2));
					}
				}break;
				case 365:{
					{
						parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
						List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(Expr*, alloc(ExprCall)(SrcSpan(_parsx_2.where, _parsx_4.where), _parsx_1, _parsx_3));
					}
				}break;
				case 366:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<Pattern> _parsx_2 = parsx_pop_value(List<Pattern>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Pattern*, alloc(PatternTuple)(SrcSpan(_parsx_1.where, _parsx_3.where), _parsx_2));
					}
				}break;
				case 367:{
					{
						Type* _parsx_3 = parsx_pop_value(Type*);
						List<Name> _parsx_2 = parsx_pop_value(List<Name>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(StructField*, alloc(StructField)(_parsx_2, _parsx_3));
					}
				}break;
				case 368:{
					{
						parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
						List<EnumConstructor> _parsx_3 = parsx_pop_value(List<EnumConstructor>);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(TopLevel*, alloc(Enum)(_parsx_2.where, sym(_parsx_2), _parsx_3));
					}
				}break;
				case 369:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Pattern*, alloc(PatternString)(_parsx_1.where, lit(_parsx_1)));
					}
				}break;
				case 370:{
					{
						parsx_push_value(List<Import>, List<Import>());
					}
				}break;
				case 371:{
					{
						StringRef _parsx_4 = parsx_pop_value(StringRef);
						QualID* _parsx_3 = parsx_pop_value(QualID*);
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						SrcLoc _parsx_1 = parsx_pop_value(SrcLoc);
						parsx_push_value(Import*, alloc(Import)(to_here(_parsx_1), _parsx_3, _parsx_4));
					}
				}break;
				case 372:{
					{
						parsx_push_value(StringRef, StringRef());
					}
				}break;
				case 373:{
					{
						parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(StringRef, sym(_parsx_2));
					}
				}break;
				case 374:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Return, alloc(ExprUnit)(_parsx_1.where)));
					}
				}break;
				case 375:{
				}break;
				case 376:{
					{
						Import* _parsx_2 = parsx_pop_value(Import*);
						List<Import> _parsx_1 = parsx_pop_value(List<Import>);
						parsx_push_value(List<Import>, _parsx_1.append(_parsx_2));
					}
				}break;
				case 377:{
					{
						Pattern* _parsx_2 = parsx_pop_value(Pattern*);
						EnumConstructorNumber _parsx_1 = parsx_pop_value(EnumConstructorNumber);
						parsx_push_value(Pattern*, alloc(PatternEnum)(_parsx_1.where, _parsx_1, _parsx_2));
					}
				}break;
				case 378:{
					{
						int _parsx_2 = parsx_pop_value(int);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(EnumConstructorNumber, EnumConstructorNumber(to_here(_parsx_1.where.from()), 0, _parsx_2));
					}
				}break;
				case 379:{
					{
						parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
						List<TopLevel> _parsx_2 = parsx_pop_value(List<TopLevel>);
						List<Import> _parsx_1 = parsx_pop_value(List<Import>);
						parsx_push_value(Module*, alloc(Module)(_parsx_1,_parsx_2));
					}
				}break;
				case 380:{
					{
						parsx_push_value(List<TopLevel>, List<TopLevel>());
					}
				}break;
				case 381:{
				}break;
				case 382:{
					{
						TopLevel* _parsx_2 = parsx_pop_value(TopLevel*);
						List<TopLevel> _parsx_1 = parsx_pop_value(List<TopLevel>);
						parsx_push_value(List<TopLevel>, _parsx_1.append(_parsx_2));
					}
				}break;
				case 383:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Return, alloc(ExprUnit)(_parsx_1.where)));
					}
				}break;
				case 384:{
				}break;
				case 385:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Float));
					}
				}break;
				case 386:{
					{
						parsx_push_value(List<ConstructorStringPart>, nullptr);
					}
					{
						List<ConstructorStringPart> _parsx_2 = parsx_pop_value(List<ConstructorStringPart>);
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(Stmt*, alloc(StmtConstructPass)(_parsx_1.where, _parsx_2));
					}
				}break;
				case 387:{
				}break;
				case 388:{
				}break;
				case 389:{
				}break;
				case 390:{
					parsx_commit_token();
				}break;
				case 391:{
					parsx_commit_token();
				}break;
				case 392:{
					parsx_commit_token();
				}break;
				case 393:{
					parsx_commit_token();
				}break;
				case 394:{
					parsx_commit_token();
				}break;
				case 395:{
					parsx_commit_token();
				}break;
				case 396:{
					parsx_commit_token();
				}break;
				case 397:{
					parsx_commit_token();
				}break;
				case 398:{
					parsx_commit_token();
				}break;
				case 399:{
					parsx_commit_token();
				}break;
				case 400:{
					parsx_commit_token();
				}break;
				case 401:{
					parsx_commit_token();
				}break;
				case 402:{
					parsx_commit_token();
				}break;
				case 403:{
					parsx_commit_token();
				}break;
				case 404:{
					parsx_commit_token();
				}break;
				case 405:{
					parsx_commit_token();
				}break;
				case 406:{
					parsx_commit_token();
				}break;
				case 407:{
					parsx_commit_token();
				}break;
				case 408:{
					parsx_commit_token();
				}break;
				case 409:{
					parsx_commit_token();
				}break;
				case 410:{
					parsx_commit_token();
				}break;
				case 411:{
					parsx_commit_token();
				}break;
				case 412:{
					parsx_commit_token();
				}break;
				case 413:{
					parsx_commit_token();
				}break;
				case 414:{
					parsx_commit_token();
				}break;
				case 415:{
					parsx_commit_token();
				}break;
				case 416:{
					parsx_commit_token();
				}break;
				case 417:{
					parsx_commit_token();
				}break;
				case 418:{
					parsx_commit_token();
				}break;
				case 419:{
					parsx_commit_token();
				}break;
				case 420:{
					parsx_commit_token();
				}break;
				case 421:{
					parsx_commit_token();
				}break;
				case 422:{
					parsx_commit_token();
				}break;
				case 423:{
					parsx_commit_token();
				}break;
				case 424:{
					parsx_commit_token();
				}break;
				case 425:{
					parsx_commit_token();
				}break;
				case 426:{
					parsx_commit_token();
				}break;
				case 427:{
					parsx_commit_token();
				}break;
				case 428:{
					parsx_commit_token();
				}break;
				case 429:{
					parsx_commit_token();
				}break;
				case 430:{
					parsx_commit_token();
				}break;
				case 431:{
					parsx_commit_token();
				}break;
				case 432:{
					parsx_commit_token();
				}break;
				case 433:{
					parsx_commit_token();
				}break;
				case 434:{
					parsx_commit_token();
				}break;
				case 435:{
					parsx_commit_token();
				}break;
				case 436:{
					parsx_commit_token();
				}break;
				case 437:{
					parsx_commit_token();
				}break;
				case 438:{
					parsx_commit_token();
				}break;
				case 439:{
					parsx_commit_token();
				}break;
				case 440:{
					parsx_commit_token();
				}break;
				case 441:{
					parsx_commit_token();
				}break;
				case 442:{
					parsx_commit_token();
				}break;
				case 443:{
					parsx_commit_token();
				}break;
				case 444:{
					parsx_commit_token();
				}break;
				case 445:{
					parsx_commit_token();
				}break;
				case 446:{
					parsx_commit_token();
				}break;
				case 447:{
					parsx_commit_token();
				}break;
				case 448:{
					parsx_commit_token();
				}break;
				case 449:{
					parsx_commit_token();
				}break;
				case 450:{
					parsx_commit_token();
				}break;
				case 451:{
					parsx_commit_token();
				}break;
				case 452:{
					parsx_commit_token();
				}break;
				case 453:{
					parsx_commit_token();
				}break;
				case 454:{
					parsx_commit_token();
				}break;
				case 455:{
					parsx_commit_token();
				}break;
				case 456:{
					parsx_commit_token();
				}break;
				case 457:{
					parsx_commit_token();
				}break;
				case 458:{
					parsx_commit_token();
				}break;
				case 459:{
					parsx_commit_token();
				}break;
				case 460:{
					parsx_commit_token();
				}break;
				case 461:{
					parsx_commit_token();
				}break;
				case 462:{
					parsx_commit_token();
				}break;
				case 463:{
					{
						parsx_push_value(List<ConstructorStringPart>, nullptr);
					}
					parsx_commit_token();
				}break;
				case 464:{
					parsx_commit_token();
				}break;
				case 465:{
					parsx_commit_token();
				}break;
				case 466:{
					parsx_commit_token();
				}break;
				case 467:{
					parsx_commit_token();
				}break;
				case 468:{
					parsx_commit_token();
				}break;
				case 469:{
					parsx_commit_token();
				}break;
				case 470:{
					parsx_commit_token();
				}break;
				case 471:{
					parsx_commit_token();
				}break;
				case 472:{
					parsx_commit_token();
				}break;
				case 473:{
					parsx_commit_token();
				}break;
				case 474:{
					parsx_commit_token();
				}break;
				case 475:{
					parsx_commit_token();
				}break;
				case 476:{
					parsx_commit_token();
				}break;
				case 477:{
					parsx_commit_token();
				}break;
				case 478:{
					parsx_commit_token();
				}break;
				case 479:{
					parsx_commit_token();
				}break;
				case 480:{
					parsx_commit_token();
				}break;
				case 481:{
					parsx_commit_token();
				}break;
				case 482:{
					parsx_commit_token();
				}break;
				case 483:{
					parsx_commit_token();
				}break;
				case 484:{
					parsx_commit_token();
				}break;
				case 485:{
					parsx_commit_token();
				}break;
				case 486:{
					parsx_commit_token();
				}break;
				case 487:{
					parsx_commit_token();
				}break;
				case 488:{
					parsx_commit_token();
				}break;
				case 489:{
					parsx_commit_token();
				}break;
				case 490:{
					parsx_commit_token();
				}break;
				case 491:{
					parsx_commit_token();
				}break;
				case 492:{
					parsx_commit_token();
				}break;
				case 493:{
					parsx_commit_token();
				}break;
				case 494:{
					parsx_commit_token();
				}break;
				case 495:{
					parsx_commit_token();
				}break;
				case 496:{
					parsx_commit_token();
				}break;
				case 497:{
					parsx_commit_token();
				}break;
				case 498:{
					parsx_commit_token();
				}break;
				case 499:{
					parsx_commit_token();
				}break;
				case 500:{
					parsx_commit_token();
				}break;
				case 501:{
					parsx_commit_token();
				}break;
				case 502:{
					parsx_commit_token();
				}break;
				case 503:{
					parsx_commit_token();
				}break;
				case 504:{
					parsx_commit_token();
				}break;
				case 505:{
					parsx_commit_token();
				}break;
				case 506:{
					{
						parsx_push_value(List<ExprList>, List<ExprList>());
					}
					parsx_commit_token();
				}break;
				case 507:{
					parsx_commit_token();
				}break;
				case 508:{
					parsx_commit_token();
				}break;
				case 509:{
					parsx_commit_token();
				}break;
				case 510:{
					parsx_commit_token();
				}break;
				case 511:{
					parsx_commit_token();
				}break;
				case 512:{
					parsx_commit_token();
				}break;
				case 513:{
					parsx_commit_token();
				}break;
				case 514:{
					parsx_commit_token();
				}break;
				case 515:{
					parsx_commit_token();
				}break;
				case 516:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 517:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 518:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 519:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 520:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					{
						parsx_push_value(List<Stmt>, List<Stmt>());
					}
					parsx_commit_token();
				}break;
				case 521:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 522:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 523:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 524:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 525:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 526:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 527:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 528:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 529:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 530:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 531:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 532:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 533:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 534:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 535:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 536:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 537:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 538:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 539:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 540:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 541:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 542:{
					parsx_commit_token();
				}break;
				case 543:{
					parsx_commit_token();
				}break;
				case 544:{
					parsx_commit_token();
				}break;
				case 545:{
					parsx_commit_token();
				}break;
				case 546:{
					parsx_commit_token();
				}break;
				case 547:{
					parsx_commit_token();
				}break;
				case 548:{
					parsx_commit_token();
				}break;
				case 549:{
					parsx_commit_token();
				}break;
				case 550:{
					parsx_commit_token();
				}break;
				case 551:{
					parsx_commit_token();
				}break;
				case 552:{
					parsx_commit_token();
				}break;
				case 553:{
					parsx_commit_token();
				}break;
				case 554:{
					parsx_commit_token();
				}break;
				case 555:{
					parsx_commit_token();
				}break;
				case 556:{
					parsx_commit_token();
				}break;
				case 557:{
					parsx_commit_token();
				}break;
				case 558:{
					parsx_commit_token();
				}break;
				case 559:{
					parsx_commit_token();
				}break;
				case 560:{
					parsx_commit_token();
				}break;
				case 561:{
					parsx_commit_token();
				}break;
				case 562:{
					parsx_commit_token();
				}break;
				case 563:{
					parsx_commit_token();
				}break;
				case 564:{
					parsx_commit_token();
				}break;
				case 565:{
					parsx_commit_token();
				}break;
				case 566:{
					parsx_commit_token();
				}break;
				case 567:{
					parsx_commit_token();
				}break;
				case 568:{
					parsx_commit_token();
				}break;
				case 569:{
					parsx_commit_token();
				}break;
				case 570:{
					parsx_commit_token();
				}break;
				case 571:{
					parsx_commit_token();
				}break;
				case 572:{
					parsx_commit_token();
				}break;
				case 573:{
					parsx_commit_token();
				}break;
				case 574:{
					parsx_commit_token();
				}break;
				case 575:{
					parsx_commit_token();
				}break;
				case 576:{
					parsx_commit_token();
				}break;
				case 577:{
					parsx_commit_token();
				}break;
				case 578:{
					parsx_commit_token();
				}break;
				case 579:{
					parsx_commit_token();
				}break;
				case 580:{
					parsx_commit_token();
				}break;
				case 581:{
					parsx_commit_token();
				}break;
				case 582:{
					parsx_commit_token();
				}break;
				case 583:{
					parsx_commit_token();
				}break;
				case 584:{
					parsx_commit_token();
				}break;
				case 585:{
					parsx_commit_token();
				}break;
				case 586:{
					parsx_commit_token();
				}break;
				case 587:{
					parsx_commit_token();
				}break;
				case 588:{
					parsx_commit_token();
				}break;
				case 589:{
					parsx_commit_token();
				}break;
				case 590:{
					parsx_commit_token();
				}break;
				case 591:{
					parsx_commit_token();
				}break;
				case 592:{
					parsx_commit_token();
				}break;
				case 593:{
					parsx_commit_token();
				}break;
				case 594:{
					parsx_commit_token();
				}break;
				case 595:{
					parsx_commit_token();
				}break;
				case 596:{
					parsx_commit_token();
				}break;
				case 597:{
					parsx_commit_token();
				}break;
				case 598:{
					parsx_commit_token();
				}break;
				case 599:{
					parsx_commit_token();
				}break;
				case 600:{
					parsx_commit_token();
				}break;
				case 601:{
					parsx_commit_token();
				}break;
				case 602:{
					parsx_commit_token();
				}break;
				case 603:{
					parsx_commit_token();
				}break;
				case 604:{
					parsx_commit_token();
				}break;
				case 605:{
					{
						parsx_push_value(List< MatchCase<Stmt> >, List< MatchCase<Stmt> >());
					}
					parsx_commit_token();
				}break;
				case 606:{
					parsx_commit_token();
				}break;
				case 607:{
					parsx_commit_token();
				}break;
				case 608:{
					parsx_commit_token();
				}break;
				case 609:{
					parsx_commit_token();
				}break;
				case 610:{
					parsx_commit_token();
				}break;
				case 611:{
					parsx_commit_token();
				}break;
				case 612:{
					parsx_commit_token();
				}break;
				case 613:{
					parsx_commit_token();
				}break;
				case 614:{
					parsx_commit_token();
				}break;
				case 615:{
					parsx_commit_token();
				}break;
				case 616:{
					parsx_commit_token();
				}break;
				case 617:{
					parsx_commit_token();
				}break;
				case 618:{
					parsx_commit_token();
				}break;
				case 619:{
					parsx_commit_token();
				}break;
				case 620:{
					parsx_commit_token();
				}break;
				case 621:{
					parsx_commit_token();
				}break;
				case 622:{
					parsx_commit_token();
				}break;
				case 623:{
					parsx_commit_token();
				}break;
				case 624:{
					parsx_commit_token();
				}break;
				case 625:{
					parsx_commit_token();
				}break;
				case 626:{
					parsx_commit_token();
				}break;
				case 627:{
					parsx_commit_token();
				}break;
				case 628:{
					parsx_commit_token();
				}break;
				case 629:{
					parsx_commit_token();
				}break;
				case 630:{
					parsx_commit_token();
				}break;
				case 631:{
					parsx_commit_token();
				}break;
				case 632:{
					parsx_commit_token();
				}break;
				case 633:{
					parsx_commit_token();
				}break;
				case 634:{
					parsx_commit_token();
				}break;
				case 635:{
					parsx_commit_token();
				}break;
				case 636:{
					parsx_commit_token();
				}break;
				case 637:{
					parsx_commit_token();
				}break;
				case 638:{
					parsx_commit_token();
				}break;
				case 639:{
					parsx_commit_token();
				}break;
				case 640:{
					parsx_commit_token();
				}break;
				case 641:{
					parsx_commit_token();
				}break;
				case 642:{
					parsx_commit_token();
				}break;
				case 643:{
					parsx_commit_token();
				}break;
				case 644:{
					parsx_commit_token();
				}break;
				case 645:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(List<Name>, alloc(Name)(_parsx_1.where, sym(_parsx_1)));
					}
					parsx_commit_token();
				}break;
				case 646:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1.where.from(), alloc(TypeReferenceLeaf)(sym(_parsx_1))));
					}
					{
						WithSrcLoc<TypeReferenceNode*> _parsx_1 = parsx_pop_value(WithSrcLoc<TypeReferenceNode*>);
						parsx_push_value(Type*, alloc(TypeReference)(to_here(_parsx_1), _parsx_1));
					}
					parsx_commit_token();
				}break;
				case 647:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1.where.from(), alloc(TypeReferenceLeaf)(sym(_parsx_1))));
					}
					parsx_commit_token();
				}break;
				case 648:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1.where.from(), alloc(TypeReferenceLeaf)(sym(_parsx_1))));
					}
					{
						WithSrcLoc<TypeReferenceNode*> _parsx_1 = parsx_pop_value(WithSrcLoc<TypeReferenceNode*>);
						parsx_push_value(Type*, alloc(TypeReference)(to_here(_parsx_1), _parsx_1));
					}
					parsx_commit_token();
				}break;
				case 649:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(List<Name>, alloc(Name)(_parsx_1.where, sym(_parsx_1)));
					}
					parsx_commit_token();
				}break;
				case 650:{
					{
						parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
						parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1.where.from(), alloc(TypeReferenceLeaf)(sym(_parsx_1))));
					}
					{
						WithSrcLoc<TypeReferenceNode*> _parsx_1 = parsx_pop_value(WithSrcLoc<TypeReferenceNode*>);
						parsx_push_value(Type*, alloc(TypeReference)(to_here(_parsx_1), _parsx_1));
					}
					parsx_commit_token();
				}break;
				case 651:{
					parsx_commit_token();
				}break;
				case 652:{
					parsx_commit_token();
				}break;
				case 653:{
					parsx_commit_token();
				}break;
				case 654:{
					parsx_commit_token();
				}break;
				case 655:{
					parsx_commit_token();
				}break;
				case 656:{
					parsx_commit_token();
				}break;
				case 657:{
					parsx_commit_token();
				}break;
				case 658:{
					parsx_commit_token();
				}break;
				case 659:{
					parsx_commit_token();
				}break;
				case 660:{
					parsx_commit_token();
				}break;
				case 661:{
					parsx_commit_token();
				}break;
				case 662:{
					parsx_commit_token();
				}break;
				case 663:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 664:{
					parsx_commit_token();
				}break;
				case 665:{
					parsx_commit_token();
				}break;
				case 666:{
					parsx_commit_token();
				}break;
				case 667:{
					parsx_commit_token();
				}break;
				case 668:{
					parsx_commit_token();
				}break;
				case 669:{
					parsx_commit_token();
				}break;
				case 670:{
					parsx_commit_token();
				}break;
				case 671:{
					parsx_commit_token();
				}break;
				case 672:{
					parsx_commit_token();
				}break;
				case 673:{
					parsx_commit_token();
				}break;
				case 674:{
					parsx_commit_token();
				}break;
				case 675:{
					parsx_commit_token();
				}break;
				case 676:{
					parsx_commit_token();
				}break;
				case 677:{
					parsx_commit_token();
				}break;
				case 678:{
					parsx_commit_token();
				}break;
				case 679:{
					{
						parsx_push_value(List<AssignPair>, List<AssignPair>());
					}
					parsx_commit_token();
				}break;
				case 680:{
					{
						parsx_push_value(List<AssignPair>, List<AssignPair>());
					}
					parsx_commit_token();
				}break;
				case 681:{
					parsx_commit_token();
				}break;
				case 682:{
					parsx_commit_token();
				}break;
				case 683:{
					parsx_commit_token();
				}break;
				case 684:{
					parsx_commit_token();
				}break;
				case 685:{
					parsx_commit_token();
				}break;
				case 686:{
					parsx_commit_token();
				}break;
				case 687:{
					parsx_commit_token();
				}break;
				case 688:{
					parsx_commit_token();
				}break;
				case 689:{
					parsx_commit_token();
				}break;
				case 690:{
					parsx_commit_token();
				}break;
				case 691:{
					parsx_commit_token();
				}break;
				case 692:{
					parsx_commit_token();
				}break;
				case 693:{
					parsx_commit_token();
				}break;
				case 694:{
					parsx_commit_token();
				}break;
				case 695:{
					parsx_commit_token();
				}break;
				case 696:{
					parsx_commit_token();
				}break;
				case 697:{
					parsx_commit_token();
				}break;
				case 698:{
					parsx_commit_token();
				}break;
				case 699:{
					parsx_commit_token();
				}break;
				case 700:{
					parsx_commit_token();
				}break;
				case 701:{
					parsx_commit_token();
				}break;
				case 702:{
					parsx_commit_token();
				}break;
				case 703:{
					parsx_commit_token();
				}break;
				case 704:{
					parsx_commit_token();
				}break;
				case 705:{
					parsx_commit_token();
				}break;
				case 706:{
					parsx_commit_token();
				}break;
				case 707:{
					parsx_commit_token();
				}break;
				case 708:{
					parsx_commit_token();
				}break;
				case 709:{
					parsx_commit_token();
				}break;
				case 710:{
					parsx_commit_token();
				}break;
				case 711:{
					parsx_commit_token();
				}break;
				case 712:{
					parsx_commit_token();
				}break;
				case 713:{
					parsx_commit_token();
				}break;
				case 714:{
					parsx_commit_token();
				}break;
				case 715:{
					parsx_commit_token();
				}break;
				case 716:{
					parsx_commit_token();
				}break;
				case 717:{
					parsx_commit_token();
				}break;
				case 718:{
					parsx_commit_token();
				}break;
				case 719:{
					parsx_commit_token();
				}break;
				case 720:{
					parsx_commit_token();
				}break;
				case 721:{
					parsx_commit_token();
				}break;
				case 722:{
					parsx_commit_token();
				}break;
				case 723:{
					parsx_commit_token();
				}break;
				case 724:{
					parsx_commit_token();
				}break;
				case 725:{
					parsx_commit_token();
				}break;
				case 726:{
					parsx_commit_token();
				}break;
				case 727:{
					parsx_commit_token();
				}break;
				case 728:{
					parsx_commit_token();
				}break;
				case 729:{
					parsx_commit_token();
				}break;
				case 730:{
					parsx_commit_token();
				}break;
				case 731:{
					parsx_commit_token();
				}break;
				case 732:{
					parsx_commit_token();
				}break;
				case 733:{
					parsx_commit_token();
				}break;
				case 734:{
					parsx_commit_token();
				}break;
				case 735:{
					parsx_commit_token();
				}break;
				case 736:{
					parsx_commit_token();
				}break;
				case 737:{
					parsx_commit_token();
				}break;
				case 738:{
					parsx_commit_token();
				}break;
				case 739:{
					parsx_commit_token();
				}break;
				case 740:{
					parsx_commit_token();
				}break;
				case 741:{
					parsx_commit_token();
				}break;
				case 742:{
					parsx_commit_token();
				}break;
				case 743:{
					parsx_commit_token();
				}break;
				case 744:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 745:{
					{
						parsx_push_value(List<Implements>, List<Implements>());
					}
					parsx_commit_token();
				}break;
				case 746:{
					parsx_commit_token();
				}break;
				case 747:{
					parsx_commit_token();
				}break;
				case 748:{
					{
						parsx_push_value(List<EnumConstructor>, List<EnumConstructor>());
					}
					parsx_commit_token();
				}break;
				case 749:{
					parsx_commit_token();
				}break;
				case 750:{
					parsx_commit_token();
				}break;
				case 751:{
					parsx_commit_token();
				}break;
				case 752:{
					parsx_commit_token();
				}break;
				case 753:{
					parsx_commit_token();
				}break;
				case 754:{
					parsx_commit_token();
				}break;
				case 755:{
					parsx_commit_token();
				}break;
				case 756:{
					parsx_commit_token();
				}break;
				case 757:{
					parsx_commit_token();
				}break;
				case 758:{
					parsx_commit_token();
				}break;
				case 759:{
					parsx_commit_token();
				}break;
				case 760:{
					parsx_commit_token();
				}break;
				case 761:{
					parsx_commit_token();
				}break;
				case 762:{
					parsx_commit_token();
				}break;
				case 763:{
					parsx_commit_token();
				}break;
				case 764:{
					parsx_commit_token();
				}break;
				case 765:{
					parsx_commit_token();
				}break;
				case 766:{
					parsx_commit_token();
				}break;
				case 767:{
					parsx_commit_token();
				}break;
				case 768:{
					parsx_commit_token();
				}break;
				case 769:{
					parsx_commit_token();
				}break;
				case 770:{
					parsx_commit_token();
				}break;
				case 771:{
					parsx_commit_token();
				}break;
				case 772:{
					parsx_commit_token();
				}break;
				case 773:{
					parsx_commit_token();
				}break;
				case 774:{
					parsx_commit_token();
				}break;
				case 775:{
					parsx_commit_token();
				}break;
				case 776:{
					parsx_commit_token();
				}break;
				case 777:{
					parsx_commit_token();
				}break;
				case 778:{
					{
						use_def
					}
					parsx_commit_token();
				}break;
				case 779:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 780:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 781:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 782:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 783:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					{
						parsx_push_value(List<Stmt>, List<Stmt>());
					}
					parsx_commit_token();
				}break;
				case 784:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 785:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 786:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 787:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 788:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 789:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 790:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 791:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 792:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 793:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 794:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 795:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 796:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 797:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 798:{
					{
						use_def
					}
					parsx_commit_token();
				}break;
				case 799:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 800:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 801:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 802:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 803:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 804:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 805:{
					{
						use_def
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 806:{
					parsx_commit_token();
				}break;
				case 807:{
					parsx_commit_token();
				}break;
				case 808:{
					parsx_commit_token();
				}break;
				case 809:{
					parsx_commit_token();
				}break;
				case 810:{
					parsx_commit_token();
				}break;
				case 811:{
					parsx_commit_token();
				}break;
				case 812:{
					parsx_commit_token();
				}break;
				case 813:{
					parsx_commit_token();
				}break;
				case 814:{
					parsx_commit_token();
				}break;
				case 815:{
					parsx_commit_token();
				}break;
				case 816:{
					parsx_commit_token();
				}break;
				case 817:{
					parsx_commit_token();
				}break;
				case 818:{
					parsx_commit_token();
				}break;
				case 819:{
					parsx_commit_token();
				}break;
				case 820:{
					parsx_commit_token();
				}break;
				case 821:{
					parsx_commit_token();
				}break;
				case 822:{
					parsx_commit_token();
				}break;
				case 823:{
					parsx_commit_token();
				}break;
				case 824:{
					parsx_commit_token();
				}break;
				case 825:{
					parsx_commit_token();
				}break;
				case 826:{
					parsx_commit_token();
				}break;
				case 827:{
					parsx_commit_token();
				}break;
				case 828:{
					parsx_commit_token();
				}break;
				case 829:{
					parsx_commit_token();
				}break;
				case 830:{
					parsx_commit_token();
				}break;
				case 831:{
					parsx_commit_token();
				}break;
				case 832:{
					parsx_commit_token();
				}break;
				case 833:{
					parsx_commit_token();
				}break;
				case 834:{
					parsx_commit_token();
				}break;
				case 835:{
					parsx_commit_token();
				}break;
				case 836:{
					parsx_commit_token();
				}break;
				case 837:{
					parsx_commit_token();
				}break;
				case 838:{
					parsx_commit_token();
				}break;
				case 839:{
					parsx_commit_token();
				}break;
				case 840:{
					parsx_commit_token();
				}break;
				case 841:{
					parsx_commit_token();
				}break;
				case 842:{
					parsx_commit_token();
				}break;
				case 843:{
					parsx_commit_token();
				}break;
				case 844:{
					parsx_commit_token();
				}break;
				case 845:{
					parsx_commit_token();
				}break;
				case 846:{
					parsx_commit_token();
				}break;
				case 847:{
					parsx_commit_token();
				}break;
				case 848:{
					parsx_commit_token();
				}break;
				case 849:{
					parsx_commit_token();
				}break;
				case 850:{
					parsx_commit_token();
				}break;
				case 851:{
					parsx_commit_token();
				}break;
				case 852:{
					parsx_commit_token();
				}break;
				case 853:{
					parsx_commit_token();
				}break;
				case 854:{
					parsx_commit_token();
				}break;
				case 855:{
					parsx_commit_token();
				}break;
				case 856:{
					parsx_commit_token();
				}break;
				case 857:{
					parsx_commit_token();
				}break;
				case 858:{
					parsx_commit_token();
				}break;
				case 859:{
					parsx_commit_token();
				}break;
				case 860:{
					parsx_commit_token();
				}break;
				case 861:{
					parsx_commit_token();
				}break;
				case 862:{
					parsx_commit_token();
				}break;
				case 863:{
					parsx_commit_token();
				}break;
				case 864:{
					parsx_commit_token();
				}break;
				case 865:{
					parsx_commit_token();
				}break;
				case 866:{
					parsx_commit_token();
				}break;
				case 867:{
					parsx_commit_token();
				}break;
				case 868:{
					parsx_commit_token();
				}break;
				case 869:{
					{
						parsx_push_value(List<StructField>, List<StructField>());
					}
					parsx_commit_token();
				}break;
				case 870:{
					parsx_commit_token();
				}break;
				case 871:{
					parsx_commit_token();
				}break;
				case 872:{
					parsx_commit_token();
				}break;
				case 873:{
					parsx_commit_token();
				}break;
				case 874:{
					parsx_commit_token();
				}break;
				case 875:{
					parsx_commit_token();
				}break;
				case 876:{
					parsx_commit_token();
				}break;
				case 877:{
					parsx_commit_token();
				}break;
				case 878:{
					parsx_commit_token();
				}break;
				case 879:{
					parsx_commit_token();
				}break;
				case 880:{
					parsx_commit_token();
				}break;
				case 881:{
					parsx_commit_token();
				}break;
				case 882:{
					parsx_commit_token();
				}break;
				case 883:{
					parsx_commit_token();
				}break;
				case 884:{
					parsx_commit_token();
				}break;
				case 885:{
					parsx_commit_token();
				}break;
				case 886:{
					parsx_commit_token();
				}break;
				case 887:{
					parsx_commit_token();
				}break;
				case 888:{
					parsx_commit_token();
				}break;
				case 889:{
					parsx_commit_token();
				}break;
				case 890:{
					parsx_commit_token();
				}break;
				case 891:{
					parsx_commit_token();
				}break;
				case 892:{
					parsx_commit_token();
				}break;
				case 893:{
					parsx_commit_token();
				}break;
				case 894:{
					parsx_commit_token();
				}break;
				case 895:{
					parsx_commit_token();
				}break;
				case 896:{
					parsx_commit_token();
				}break;
				case 897:{
					parsx_commit_token();
				}break;
				case 898:{
					parsx_commit_token();
				}break;
				case 899:{
					parsx_commit_token();
				}break;
				case 900:{
					parsx_commit_token();
				}break;
				case 901:{
					parsx_commit_token();
				}break;
				case 902:{
					parsx_commit_token();
				}break;
				case 903:{
					parsx_commit_token();
				}break;
				case 904:{
					parsx_commit_token();
				}break;
				case 905:{
					parsx_commit_token();
				}break;
				case 906:{
					parsx_commit_token();
				}break;
				case 907:{
					parsx_commit_token();
				}break;
				case 908:{
					parsx_commit_token();
				}break;
				case 909:{
					parsx_commit_token();
				}break;
				case 910:{
					parsx_commit_token();
				}break;
				case 911:{
					parsx_commit_token();
				}break;
				case 912:{
					parsx_commit_token();
				}break;
				case 913:{
					parsx_commit_token();
				}break;
				case 914:{
					parsx_commit_token();
				}break;
				case 915:{
					parsx_commit_token();
				}break;
				case 916:{
					parsx_commit_token();
				}break;
				case 917:{
					parsx_commit_token();
				}break;
				case 918:{
					{
						parsx_push_value(List<ExprList>, List<ExprList>());
					}
					parsx_commit_token();
				}break;
				case 919:{
					parsx_commit_token();
				}break;
				case 920:{
					parsx_commit_token();
				}break;
				case 921:{
					parsx_commit_token();
				}break;
				case 922:{
					parsx_commit_token();
				}break;
				case 923:{
					parsx_commit_token();
				}break;
				case 924:{
					parsx_commit_token();
				}break;
				case 925:{
					parsx_commit_token();
				}break;
				case 926:{
					parsx_commit_token();
				}break;
				case 927:{
					parsx_commit_token();
				}break;
				case 928:{
					parsx_commit_token();
				}break;
				case 929:{
					parsx_commit_token();
				}break;
				case 930:{
					parsx_commit_token();
				}break;
				case 931:{
					parsx_commit_token();
				}break;
				case 932:{
					parsx_commit_token();
				}break;
				case 933:{
					parsx_commit_token();
				}break;
				case 934:{
					parsx_commit_token();
				}break;
				case 935:{
					parsx_commit_token();
				}break;
				case 936:{
					parsx_commit_token();
				}break;
				case 937:{
					parsx_commit_token();
				}break;
				case 938:{
					parsx_commit_token();
				}break;
				case 939:{
					parsx_commit_token();
				}break;
				case 940:{
					parsx_commit_token();
				}break;
				case 941:{
					parsx_commit_token();
				}break;
				case 942:{
					parsx_commit_token();
				}break;
				case 943:{
					parsx_commit_token();
				}break;
				case 944:{
					parsx_commit_token();
				}break;
				case 945:{
					parsx_commit_token();
				}break;
				case 946:{
					parsx_commit_token();
				}break;
				case 947:{
					parsx_commit_token();
				}break;
				case 948:{
					parsx_commit_token();
				}break;
				case 949:{
					parsx_commit_token();
				}break;
				case 950:{
					parsx_commit_token();
				}break;
				case 951:{
					parsx_commit_token();
				}break;
				case 952:{
					parsx_commit_token();
				}break;
				case 953:{
					parsx_commit_token();
				}break;
				case 954:{
					parsx_commit_token();
				}break;
				case 955:{
					parsx_commit_token();
				}break;
				case 956:{
					parsx_commit_token();
				}break;
				case 957:{
					parsx_commit_token();
				}break;
				case 958:{
					parsx_commit_token();
				}break;
				case 959:{
					parsx_commit_token();
				}break;
				case 960:{
					parsx_commit_token();
				}break;
				case 961:{
					parsx_commit_token();
				}break;
				case 962:{
					parsx_commit_token();
				}break;
				case 963:{
					parsx_commit_token();
				}break;
				case 964:{
					parsx_commit_token();
				}break;
				case 965:{
					parsx_commit_token();
				}break;
				case 966:{
					parsx_commit_token();
				}break;
				case 967:{
					parsx_commit_token();
				}break;
				case 968:{
					parsx_commit_token();
				}break;
				case 969:{
					parsx_commit_token();
				}break;
				case 970:{
					parsx_commit_token();
				}break;
				case 971:{
					parsx_commit_token();
				}break;
				case 972:{
					parsx_commit_token();
				}break;
				case 973:{
					parsx_commit_token();
				}break;
				case 974:{
					parsx_commit_token();
				}break;
				case 975:{
					parsx_commit_token();
				}break;
				case 976:{
					parsx_commit_token();
				}break;
				case 977:{
					parsx_commit_token();
				}break;
				case 978:{
					parsx_commit_token();
				}break;
				case 979:{
					parsx_commit_token();
				}break;
				case 980:{
					parsx_commit_token();
				}break;
				case 981:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 982:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 983:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 984:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 985:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					{
						parsx_push_value(List<Stmt>, List<Stmt>());
					}
					parsx_commit_token();
				}break;
				case 986:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 987:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 988:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 989:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 990:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 991:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 992:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 993:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 994:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 995:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 996:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 997:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 998:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 999:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 1000:{
					parsx_commit_token();
				}break;
				case 1001:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 1002:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 1003:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 1004:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 1005:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 1006:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 1007:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 1008:{
					parsx_commit_token();
				}break;
				case 1009:{
					parsx_commit_token();
				}break;
				case 1010:{
					parsx_commit_token();
				}break;
				case 1011:{
					parsx_commit_token();
				}break;
				case 1012:{
					parsx_commit_token();
				}break;
				case 1013:{
					parsx_commit_token();
				}break;
				case 1014:{
					parsx_commit_token();
				}break;
				case 1015:{
					parsx_commit_token();
				}break;
				case 1016:{
					parsx_commit_token();
				}break;
				case 1017:{
					parsx_commit_token();
				}break;
				case 1018:{
					{
						parsx_push_value(List< MatchCase<Expr> >, List< MatchCase<Expr> >());
					}
					parsx_commit_token();
				}break;
				case 1019:{
					parsx_commit_token();
				}break;
				case 1020:{
					parsx_commit_token();
				}break;
				case 1021:{
					parsx_commit_token();
				}break;
				case 1022:{
					parsx_commit_token();
				}break;
				case 1023:{
					parsx_commit_token();
				}break;
				case 1024:{
					parsx_commit_token();
				}break;
				case 1025:{
					parsx_commit_token();
				}break;
				case 1026:{
					parsx_commit_token();
				}break;
				case 1027:{
					parsx_commit_token();
				}break;
				case 1028:{
					parsx_commit_token();
				}break;
				case 1029:{
					parsx_commit_token();
				}break;
				case 1030:{
					parsx_commit_token();
				}break;
				case 1031:{
					parsx_commit_token();
				}break;
				case 1032:{
					parsx_commit_token();
				}break;
				case 1033:{
					parsx_commit_token();
				}break;
				case 1034:{
					parsx_commit_token();
				}break;
				case 1035:{
					parsx_commit_token();
				}break;
				case 1036:{
					parsx_commit_token();
				}break;
				case 1037:{
					parsx_commit_token();
				}break;
				case 1038:{
					parsx_commit_token();
				}break;
				case 1039:{
					parsx_commit_token();
				}break;
				case 1040:{
					parsx_commit_token();
				}break;
				case 1041:{
					parsx_commit_token();
				}break;
				case 1042:{
					parsx_commit_token();
				}break;
				case 1043:{
					parsx_commit_token();
				}break;
				case 1044:{
					parsx_commit_token();
				}break;
				case 1045:{
					parsx_commit_token();
				}break;
				case 1046:{
					parsx_commit_token();
				}break;
				case 1047:{
					parsx_commit_token();
				}break;
				case 1048:{
					parsx_commit_token();
				}break;
				case 1049:{
					parsx_commit_token();
				}break;
				case 1050:{
					parsx_commit_token();
				}break;
				case 1051:{
					parsx_commit_token();
				}break;
				case 1052:{
					parsx_commit_token();
				}break;
				case 1053:{
					parsx_commit_token();
				}break;
				case 1054:{
					parsx_commit_token();
				}break;
				case 1055:{
					parsx_commit_token();
				}break;
				case 1056:{
					parsx_commit_token();
				}break;
				case 1057:{
					parsx_commit_token();
				}break;
				case 1058:{
					parsx_commit_token();
				}break;
				case 1059:{
					parsx_commit_token();
				}break;
				case 1060:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 1061:{
					parsx_commit_token();
				}break;
				case 1062:{
					parsx_commit_token();
				}break;
				case 1063:{
					parsx_commit_token();
				}break;
				case 1064:{
					parsx_commit_token();
				}break;
				case 1065:{
					parsx_commit_token();
				}break;
				case 1066:{
					parsx_commit_token();
				}break;
				case 1067:{
					parsx_commit_token();
				}break;
				case 1068:{
					parsx_commit_token();
				}break;
				case 1069:{
					parsx_commit_token();
				}break;
				case 1070:{
					parsx_commit_token();
				}break;
				case 1071:{
					parsx_commit_token();
				}break;
				case 1072:{
					parsx_commit_token();
				}break;
				case 1073:{
					parsx_commit_token();
				}break;
				case 1074:{
					parsx_commit_token();
				}break;
				case 1075:{
					parsx_commit_token();
				}break;
				case 1076:{
					parsx_commit_token();
				}break;
				case 1077:{
					parsx_commit_token();
				}break;
				case 1078:{
					parsx_commit_token();
				}break;
				case 1079:{
					parsx_commit_token();
				}break;
				case 1080:{
					parsx_commit_token();
				}break;
				case 1081:{
					parsx_commit_token();
				}break;
				case 1082:{
					parsx_commit_token();
				}break;
				case 1083:{
					parsx_commit_token();
				}break;
				case 1084:{
					parsx_commit_token();
				}break;
				case 1085:{
					parsx_commit_token();
				}break;
				case 1086:{
					parsx_commit_token();
				}break;
				case 1087:{
					parsx_commit_token();
				}break;
				case 1088:{
					parsx_commit_token();
				}break;
				case 1089:{
					parsx_commit_token();
				}break;
				case 1090:{
					parsx_commit_token();
				}break;
				case 1091:{
					parsx_commit_token();
				}break;
				case 1092:{
					parsx_commit_token();
				}break;
				case 1093:{
					parsx_commit_token();
				}break;
				case 1094:{
					parsx_commit_token();
				}break;
				case 1095:{
					parsx_commit_token();
				}break;
				case 1096:{
					parsx_commit_token();
				}break;
				case 1097:{
					parsx_commit_token();
				}break;
				case 1098:{
					parsx_commit_token();
				}break;
				case 1099:{
					parsx_commit_token();
				}break;
				case 1100:{
					parsx_commit_token();
				}break;
				case 1101:{
					parsx_commit_token();
				}break;
				case 1102:{
					parsx_commit_token();
				}break;
				case 1103:{
					parsx_commit_token();
				}break;
				case 1104:{
					parsx_commit_token();
				}break;
				case 1105:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 1106:{
					parsx_commit_token();
				}break;
				case 1107:{
					parsx_commit_token();
				}break;
				case 1108:{
					parsx_commit_token();
				}break;
				case 1109:{
					parsx_commit_token();
				}break;
				case 1110:{
					{
						parsx_push_value(QualID*, nullptr);
					}
					parsx_commit_token();
				}break;
				case 1111:{
					parsx_commit_token();
				}break;
				case 1112:{
					parsx_commit_token();
				}break;
				case 1113:{
					{
						parsx_push_value(List<ConstructorStringPart>, nullptr);
					}
					parsx_commit_token();
				}break;
				case 1114:{
					{
						parsx_push_value(List<ConstructorStringPart>, nullptr);
					}
					parsx_commit_token();
				}break;
				case 1115:{
					parsx_commit_token();
				}break;
				case 1116:{
					parsx_commit_token();
				}break;
				case 1117:{
					parsx_commit_token();
				}break;
				case 1118:{
					parsx_commit_token();
				}break;
				case 1119:{
					parsx_commit_token();
				}break;
				case 1120:{
					parsx_commit_token();
				}break;
				case 1121:{
					parsx_commit_token();
				}break;
				case 1122:{
					parsx_commit_token();
				}break;
				case 1123:{
					parsx_commit_token();
				}break;
				case 1124:{
					parsx_commit_token();
				}break;
				case 1125:{
					parsx_commit_token();
				}break;
				case 1126:{
					parsx_commit_token();
				}break;
				case 1127:{
					parsx_commit_token();
				}break;
				case 1128:{
					parsx_commit_token();
				}break;
				case 1129:{
					parsx_commit_token();
				}break;
				case 1130:{
					parsx_commit_token();
				}break;
				case 1131:{
					parsx_commit_token();
				}break;
				case 1132:{
					parsx_commit_token();
				}break;
				case 1133:{
					parsx_commit_token();
				}break;
				case 1134:{
					parsx_commit_token();
				}break;
				case 1135:{
					parsx_commit_token();
				}break;
				case 1136:{
					parsx_commit_token();
				}break;
				case 1137:{
					parsx_commit_token();
				}break;
				case 1138:{
					parsx_commit_token();
				}break;
				case 1139:{
					parsx_commit_token();
				}break;
				case 1140:{
					parsx_commit_token();
				}break;
				case 1141:{
					parsx_commit_token();
				}break;
				case 1142:{
					parsx_commit_token();
				}break;
				case 1143:{
					parsx_commit_token();
				}break;
				case 1144:{
					parsx_commit_token();
				}break;
				case 1145:{
					parsx_commit_token();
				}break;
				case 1146:{
					parsx_commit_token();
				}break;
				case 1147:{
					parsx_commit_token();
				}break;
				case 1148:{
					parsx_commit_token();
				}break;
				case 1149:{
					parsx_commit_token();
				}break;
				case 1150:{
					parsx_commit_token();
				}break;
				case 1151:{
					parsx_commit_token();
				}break;
				case 1152:{
					parsx_commit_token();
				}break;
				case 1153:{
					parsx_commit_token();
				}break;
				case 1154:{
					parsx_commit_token();
				}break;
				case 1155:{
					parsx_commit_token();
				}break;
				case 1156:{
					parsx_commit_token();
				}break;
				case 1157:{
					parsx_commit_token();
				}break;
				case 1158:{
					parsx_commit_token();
				}break;
				case 1159:{
					parsx_commit_token();
				}break;
				case 1160:{
					parsx_commit_token();
				}break;
				case 1161:{
					parsx_commit_token();
				}break;
				case 1162:{
					parsx_commit_token();
				}break;
				case 1163:{
					{
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(List<ExprList>, alloc(ExprList)(_parsx_1));
					}
					parsx_commit_token();
				}break;
				case 1164:{
					{
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(List<ExprList>, alloc(ExprList)(_parsx_1));
					}
					parsx_commit_token();
				}break;
				case 1165:{
					parsx_commit_token();
				}break;
				case 1166:{
					parsx_commit_token();
				}break;
				case 1167:{
					parsx_commit_token();
				}break;
				case 1168:{
					parsx_commit_token();
				}break;
				case 1169:{
					parsx_commit_token();
				}break;
				case 1170:{
					parsx_commit_token();
				}break;
				case 1171:{
					parsx_commit_token();
				}break;
				case 1172:{
					parsx_commit_token();
				}break;
				case 1173:{
					parsx_commit_token();
				}break;
				case 1174:{
					parsx_commit_token();
				}break;
				case 1175:{
					parsx_commit_token();
				}break;
				case 1176:{
					parsx_commit_token();
				}break;
				case 1177:{
					parsx_commit_token();
				}break;
				case 1178:{
					parsx_commit_token();
				}break;
				case 1179:{
					parsx_commit_token();
				}break;
				case 1180:{
					parsx_commit_token();
				}break;
				case 1181:{
					parsx_commit_token();
				}break;
				case 1182:{
					{
						parsx_push_value(List<Implements>, List<Implements>());
					}
					parsx_commit_token();
				}break;
				case 1183:{
					{
						parsx_push_value(List<InterfaceMethod>, List<InterfaceMethod>());
					}
					parsx_commit_token();
				}break;
				case 1184:{
					parsx_commit_token();
				}break;
				case 1185:{
					parsx_commit_token();
				}break;
				case 1186:{
					parsx_commit_token();
				}break;
				case 1187:{
					parsx_commit_token();
				}break;
				case 1188:{
					parsx_commit_token();
				}break;
				case 1189:{
					parsx_commit_token();
				}break;
				case 1190:{
					parsx_commit_token();
				}break;
				case 1191:{
					parsx_commit_token();
				}break;
				case 1192:{
					parsx_commit_token();
				}break;
				case 1193:{
					parsx_commit_token();
				}break;
				case 1194:{
					parsx_commit_token();
				}break;
				case 1195:{
					parsx_commit_token();
				}break;
				case 1196:{
					parsx_commit_token();
				}break;
				case 1197:{
					parsx_commit_token();
				}break;
				case 1198:{
					parsx_commit_token();
				}break;
				case 1199:{
					parsx_commit_token();
				}break;
				case 1200:{
					parsx_commit_token();
				}break;
				case 1201:{
					parsx_commit_token();
				}break;
				case 1202:{
					parsx_commit_token();
				}break;
				case 1203:{
					parsx_commit_token();
				}break;
				case 1204:{
					parsx_commit_token();
				}break;
				case 1205:{
					parsx_commit_token();
				}break;
				case 1206:{
					parsx_commit_token();
				}break;
				case 1207:{
					parsx_commit_token();
				}break;
				case 1208:{
					parsx_commit_token();
				}break;
				case 1209:{
					parsx_commit_token();
				}break;
				case 1210:{
					parsx_commit_token();
				}break;
				case 1211:{
					parsx_commit_token();
				}break;
				case 1212:{
					{
						use_def
					}
					parsx_commit_token();
				}break;
				case 1213:{
					parsx_commit_token();
				}break;
				case 1214:{
					parsx_commit_token();
				}break;
				case 1215:{
					parsx_commit_token();
				}break;
				case 1216:{
					parsx_commit_token();
				}break;
				case 1217:{
					parsx_commit_token();
				}break;
				case 1218:{
					parsx_commit_token();
				}break;
				case 1219:{
					{
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(List<ExprList>, alloc(ExprList)(_parsx_1));
					}
					parsx_commit_token();
				}break;
				case 1220:{
					{
						Expr* _parsx_1 = parsx_pop_value(Expr*);
						parsx_push_value(List<ExprList>, alloc(ExprList)(_parsx_1));
					}
					parsx_commit_token();
				}break;
				case 1221:{
					parsx_commit_token();
				}break;
				case 1222:{
					parsx_commit_token();
				}break;
				case 1223:{
					{
						parsx_push_value(List<ClassMember>, List<ClassMember>());
					}
					parsx_commit_token();
				}break;
				case 1224:{
					{
						parsx_push_value(List<ClassMember>, List<ClassMember>());
					}
					parsx_commit_token();
				}break;
				case 1225:{
					{
						parsx_push_value(List<ClassMember>, List<ClassMember>());
					}
					parsx_commit_token();
				}break;
				case 1226:{
					{
						parsx_push_value(List<ClassMember>, List<ClassMember>());
					}
					parsx_commit_token();
				}break;
				case 1227:{
					{
						parsx_push_value(List<ClassMember>, List<ClassMember>());
					}
					parsx_commit_token();
				}break;
				case 1228:{
					parsx_commit_token();
				}break;
				case 1229:{
					parsx_commit_token();
				}break;
				case 1230:{
					parsx_commit_token();
				}break;
				case 1231:{
					parsx_commit_token();
				}break;
				case 1232:{
					parsx_commit_token();
				}break;
				case 1233:{
					parsx_commit_token();
				}break;
				case 1234:{
					parsx_commit_token();
				}break;
				case 1235:{
					parsx_commit_token();
				}break;
				case 1236:{
					parsx_commit_token();
				}break;
				case 1237:{
					parsx_commit_token();
				}break;
				case 1238:{
					parsx_commit_token();
				}break;
				case 1239:{
					parsx_commit_token();
				}break;
				case 1240:{
					parsx_commit_token();
				}break;
				case 1241:{
					parsx_commit_token();
				}break;
				case 1242:{
					parsx_commit_token();
				}break;
				case 1243:{
					parsx_commit_token();
				}break;
				case 1244:{
					parsx_commit_token();
				}break;
				case 1245:{
					parsx_commit_token();
				}break;
				case 1246:{
					parsx_commit_token();
				}break;
				case 1247:{
					parsx_commit_token();
				}break;
				case 1248:{
					parsx_commit_token();
				}break;
				case 1249:{
					parsx_commit_token();
				}break;
				case 1250:{
					parsx_commit_token();
				}break;
				case 1251:{
					parsx_commit_token();
				}break;
				case 1252:{
					parsx_commit_token();
				}break;
				case 1253:{
					parsx_commit_token();
				}break;
				case 1254:{
					parsx_commit_token();
				}break;
				case 1255:{
					parsx_commit_token();
				}break;
				case 1256:{
					parsx_commit_token();
				}break;
				case 1257:{
					parsx_commit_token();
				}break;
				case 1258:{
					parsx_commit_token();
				}break;
				case 1259:{
					parsx_commit_token();
				}break;
				case 1260:{
					parsx_commit_token();
				}break;
				case 1261:{
					parsx_commit_token();
				}break;
				case 1262:{
					parsx_commit_token();
				}break;
				case 1263:{
					parsx_commit_token();
				}break;
				case 1264:{
					parsx_commit_token();
				}break;
				case 1265:{
					{
						parsx_push_value(List<Import>, List<Import>());
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 1266:{
					parsx_commit_token();
				}break;
				case 1267:{
					parsx_commit_token();
				}break;
				case 1268:{
					parsx_commit_token();
				}break;
				case 1269:{
					parsx_commit_token();
				}break;
				case 1270:{
					parsx_commit_token();
				}break;
				case 1271:{
					parsx_commit_token();
				}break;
				case 1272:{
					parsx_commit_token();
				}break;
				case 1273:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 1274:{
					parsx_commit_token();
				}break;
				case 1275:{
					parsx_commit_token();
				}break;
				case 1276:{
					parsx_commit_token();
				}break;
				case 1277:{
					parsx_commit_token();
				}break;
				case 1278:{
					parsx_commit_token();
				}break;
				case 1279:{
					parsx_commit_token();
				}break;
				case 1280:{
					parsx_commit_token();
				}break;
				case 1281:{
					parsx_commit_token();
				}break;
				case 1282:{
					parsx_commit_token();
				}break;
				case 1283:{
					parsx_commit_token();
				}break;
				case 1284:{
					parsx_commit_token();
				}break;
				case 1285:{
					parsx_commit_token();
				}break;
				case 1286:{
					parsx_commit_token();
				}break;
				case 1287:{
					parsx_commit_token();
				}break;
				case 1288:{
					parsx_commit_token();
				}break;
				case 1289:{
					parsx_commit_token();
				}break;
				case 1290:{
					parsx_commit_token();
				}break;
				case 1291:{
					parsx_commit_token();
				}break;
				case 1292:{
					parsx_commit_token();
				}break;
				case 1293:{
					parsx_commit_token();
				}break;
				case 1294:{
					parsx_commit_token();
				}break;
				case 1295:{
					parsx_commit_token();
				}break;
				case 1296:{
					{
						parsx_push_value(List<Import>, List<Import>());
					}
					{
						parsx_push_value(List<TopLevel>, List<TopLevel>());
					}
					parsx_commit_token();
				}break;
				case 1297:{
					{
						parsx_push_value(List<Import>, List<Import>());
					}
					{
						parsx_push_value(List<TopLevel>, List<TopLevel>());
					}
					parsx_commit_token();
				}break;
				case 1298:{
					{
						parsx_push_value(List<Import>, List<Import>());
					}
					{
						parsx_push_value(List<TopLevel>, List<TopLevel>());
					}
					parsx_commit_token();
				}break;
				case 1299:{
					{
						parsx_push_value(List<Import>, List<Import>());
					}
					{
						parsx_push_value(List<TopLevel>, List<TopLevel>());
					}
					parsx_commit_token();
				}break;
				case 1300:{
					{
						parsx_push_value(List<Import>, List<Import>());
					}
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 1301:{
					{
						parsx_push_value(List<Import>, List<Import>());
					}
					{
						parsx_push_value(List<TopLevel>, List<TopLevel>());
					}
					parsx_commit_token();
				}break;
				case 1302:{
					{
						parsx_push_value(List<Import>, List<Import>());
					}
					{
						parsx_push_value(List<TopLevel>, List<TopLevel>());
					}
					parsx_commit_token();
				}break;
				case 1303:{
					{
						parsx_push_value(List<Import>, List<Import>());
					}
					{
						parsx_push_value(List<TopLevel>, List<TopLevel>());
					}
					parsx_commit_token();
				}break;
				case 1304:{
					parsx_commit_token();
				}break;
				case 1305:{
					{
						parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
					}
					parsx_commit_token();
				}break;
				case 1306:{
					{
						parsx_push_value(List<TopLevel>, List<TopLevel>());
					}
					parsx_commit_token();
				}break;
				case 1307:{
					{
						parsx_push_value(List<TopLevel>, List<TopLevel>());
					}
					parsx_commit_token();
				}break;
				case 1308:{
					{
						parsx_push_value(List<TopLevel>, List<TopLevel>());
					}
					parsx_commit_token();
				}break;
				case 1309:{
					{
						parsx_push_value(List<TopLevel>, List<TopLevel>());
					}
					parsx_commit_token();
				}break;
				case 1310:{
					{
						parsx_push_value(List<TopLevel>, List<TopLevel>());
					}
					parsx_commit_token();
				}break;
				case 1311:{
					{
						parsx_push_value(List<TopLevel>, List<TopLevel>());
					}
					parsx_commit_token();
				}break;
				case 1312:{
					parsx_commit_token();
				}break;
				case 1313:{
					parsx_commit_token();
				}break;
				case 1314:{
					parsx_commit_token();
				}break;
				case 1315:{
					parsx_commit_token();
				}break;
				case 1316:{
					parsx_commit_token();
				}break;
				case 1317:{
					parsx_commit_token();
				}break;
				case 1318:{
					parsx_commit_token();
				}break;
				case 1319:{
					parsx_commit_token();
				}break;
				case 1320:{
					parsx_commit_token();
				}break;
				case 1321:{
					parsx_commit_token();
				}break;
				case 1322:{
					parsx_commit_token();
				}break;
				case 1323:{
					parsx_commit_token();
				}break;
				case 1324:{
					parsx_commit_token();
				}break;
				case 1325:{
					parsx_commit_token();
				}break;
				case 1326:{
					parsx_commit_token();
				}break;
				case 1327:{
					parsx_commit_token();
				}break;
				case 1328:{
					parsx_commit_token();
				}break;
				case 1329:{
					parsx_commit_token();
				}break;
				case 1330:{
					parsx_commit_token();
				}break;
				case 1331:{
					parsx_commit_token();
				}break;
				case 1332:{
					parsx_commit_token();
				}break;
				case 1333:{
					{
						parsx_push_value(List<ConstructorStringPart>, nullptr);
					}
					parsx_commit_token();
				}break;
				case 1334:{
					{
						parsx_push_value(List<ConstructorStringPart>, nullptr);
					}
					parsx_commit_token();
				}break;
				case 1335:{
					parsx_commit_token();
				}break;
				case 1336:{
					parsx_commit_token();
				}break;
				case 1337:{
					parsx_commit_token();
				}break;
				case 1338:{
					parsx_commit_token();
				}break;
				case 1339:{
					parsx_commit_token();
				}break;
				case 1340:{
					parsx_commit_token();
				}break;
				case 1341:{
					parsx_commit_token();
				}break;
				case 1342:{
					parsx_commit_token();
				}break;
			}
			if ( parsx_action > 389 ){
				return true;
			}
		}
	parsx_commit_func_end()
	parsx_undo_func_begin()
		while ( parsx_has_queued_action ){
			Action parsx_action = parsx_pop_last_queued_action;
			const short* parsx_pushed_states = parsx_rule_state_table + parsx_rule_state_table_index[parsx_action];
			const short parsx_pushed_state = *parsx_pushed_states;
			while ( *(++parsx_pushed_states) ) parsx_pop_state();
			parsx_push_state(parsx_pushed_state);
			if ( parsx_action > 389 ){
				parsx_unshift_token();
			}
		}
	parsx_undo_func_end()
	parsx_sync_cost_func_begin()
		if ( parsx_sync_token <= parsx_max_token_id ){
			short parsx_taken_action = parsx_table[parsx_sync_token][parsx_sync_state];
			if ( parsx_taken_action > 0 ) return 0;
			if ( parsx_taken_action < 0 ) return parsx_sync_cost_table[-parsx_taken_action];
		}
		return parsx_sync_cost_table[-parsx_table[parsx_max_token_id + 2][parsx_sync_state]];
	parsx_sync_cost_func_end()
	parsx_sync_func_begin()
		short parsx_taken_action = 0;
		if ( parsx_lookahead_token <= parsx_max_token_id ){
			parsx_taken_action = parsx_table[parsx_lookahead_token][parsx_current_state];
		}
		if ( parsx_taken_action == 0 ) parsx_taken_action = parsx_table[parsx_max_token_id + 2][parsx_current_state];
		if ( parsx_taken_action > 0 ) return;
		parsx_pop_state();
		switch ( -parsx_taken_action ){
			case 0:{
			}break;
			case 1:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Mult, _parsx_1, _parsx_3));
				}
			}break;
			case 2:{
				{
					parsx_push_value(Expr*, nullptr);
				}
			}break;
			case 3:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::GT, _parsx_1, _parsx_3));
				}
			}break;
			case 4:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Div, _parsx_1, _parsx_3));
				}
			}break;
			case 5:{
			}break;
			case 6:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Rem, _parsx_1, _parsx_3));
				}
			}break;
			case 7:{
				{
					Pattern* _parsx_1 = parsx_pop_value(Pattern*);
					parsx_push_value(List<Pattern>, List<Pattern>(_parsx_1));
				}
			}break;
			case 8:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, nullptr, nullptr));
				}
			}break;
			case 9:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Return, _parsx_2));
				}
			}break;
			case 10:{
			}break;
			case 11:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtBlock)(SrcSpan(_parsx_1.where, _parsx_3.where), _parsx_2));
				}
			}break;
			case 12:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchBranch<Expr>*, alloc(MatchBranch<Expr>)(_parsx_1.where, nullptr, _parsx_2));
				}
			}break;
			case 13:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List< MatchCase<Stmt> > _parsx_4 = parsx_pop_value(List< MatchCase<Stmt> >);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtMatch)(SrcSpan(_parsx_1.where, _parsx_5.where), _parsx_2, _parsx_4));
				}
			}break;
			case 14:{
				{
					parsx_push_value(MatchBranch<Expr>*, nullptr);
				}
			}break;
			case 15:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
					SrcLoc _parsx_1 = parsx_pop_value(SrcLoc);
					parsx_push_value(FunctionBody*, alloc(FunctionBodyDefined)(to_here(_parsx_1), _parsx_2));
				}
			}break;
			case 16:{
			}break;
			case 17:{
				{
					MatchBranch<Expr>* _parsx_5 = parsx_pop_value(MatchBranch<Expr>*);
					Expr* _parsx_4 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchBranch<Expr>*, alloc(MatchBranch<Expr>)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
				}
			}break;
			case 18:{
				parsx_insert_token(KCase);
				{
					parsx_push_value(List<Pattern>, List<Pattern>());
				}
				parsx_insert_token(KThen);
				{
					parsx_push_value(List<Stmt>, List<Stmt>());
				}
				{
					List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchBranch<Stmt>*, alloc(MatchBranch<Stmt>)(_parsx_1.where, nullptr, _parsx_2));
				}
				{
					MatchBranch<Stmt>* _parsx_3 = parsx_pop_value(MatchBranch<Stmt>*);
					List<Pattern> _parsx_2 = parsx_pop_value(List<Pattern>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchCase<Stmt>*, alloc(MatchCase<Stmt>)(_parsx_1.where, _parsx_2, _parsx_3));
				}
			}break;
			case 19:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchBranch<Expr>*, alloc(MatchBranch<Expr>)(_parsx_1.where, nullptr, _parsx_2));
				}
			}break;
			case 20:{
				{
					MatchBranch<Stmt>* _parsx_3 = parsx_pop_value(MatchBranch<Stmt>*);
					List<Pattern> _parsx_2 = parsx_pop_value(List<Pattern>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchCase<Stmt>*, alloc(MatchCase<Stmt>)(_parsx_1.where, _parsx_2, _parsx_3));
				}
			}break;
			case 21:{
				parsx_insert_token(KThen);
				{
					parsx_push_value(List<Stmt>, List<Stmt>());
				}
				{
					List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchBranch<Stmt>*, alloc(MatchBranch<Stmt>)(_parsx_1.where, nullptr, _parsx_2));
				}
			}break;
			case 22:{
				{
					parsx_push_value(List<Stmt>, List<Stmt>());
				}
			}break;
			case 23:{
				{
					List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchBranch<Stmt>*, alloc(MatchBranch<Stmt>)(_parsx_1.where, nullptr, _parsx_2));
				}
			}break;
			case 24:{
				{
					MatchBranch<Stmt>* _parsx_5 = parsx_pop_value(MatchBranch<Stmt>*);
					List<Stmt> _parsx_4 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchBranch<Stmt>*, alloc(MatchBranch<Stmt>)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
				}
			}break;
			case 25:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
			}break;
			case 26:{
				{
					MatchBranch<Stmt>* _parsx_5 = parsx_pop_value(MatchBranch<Stmt>*);
					List<Stmt> _parsx_4 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchBranch<Stmt>*, alloc(MatchBranch<Stmt>)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
				}
			}break;
			case 27:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, alloc(PatternPrim)(_parsx_1.where, PatternPrim::Wildcard));
				}
			}break;
			case 28:{
				{
					Expr* _parsx_5 = parsx_pop_value(Expr*);
					Expr* _parsx_4 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
				}
			}break;
			case 29:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprTrue)(_parsx_1.where));
				}
			}break;
			case 30:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List< MatchCase<Expr> > _parsx_4 = parsx_pop_value(List< MatchCase<Expr> >);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprMatch)(SrcSpan(_parsx_1.where, _parsx_5.where), _parsx_2, _parsx_4));
				}
			}break;
			case 31:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprFalse)(_parsx_1.where));
				}
			}break;
			case 32:{
			}break;
			case 33:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprNull)(_parsx_1.where));
				}
			}break;
			case 34:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, _parsx_2);
				}
			}break;
			case 35:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List<AssignPair> _parsx_4 = parsx_pop_value(List<AssignPair>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ConstructorStringPart> _parsx_2 = parsx_pop_value(List<ConstructorStringPart>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtConstruct)(_parsx_1.where, _parsx_2, _parsx_4));
				}
			}break;
			case 36:{
				{
					parsx_push_value(List<ConstructorStringPart>, nullptr);
				}
			}break;
			case 37:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprNumber)(_parsx_1.where, sym(_parsx_1)));
				}
			}break;
			case 38:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Negate, _parsx_2));
				}
			}break;
			case 39:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Rem, _parsx_1, _parsx_3));
				}
			}break;
			case 40:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprID)(_parsx_1.where, sym(_parsx_1)));
				}
			}break;
			case 41:{
				{
					parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(List<ConstructorStringPart>, alloc(ConstructorStringPart)(nullptr, _parsx_1.where, sym(_parsx_1), _parsx_3));
				}
			}break;
			case 42:{
			}break;
			case 43:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprTuple)(SrcSpan(_parsx_1.where, _parsx_3.where), _parsx_2));
				}
			}break;
			case 44:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Raise, _parsx_2));
				}
			}break;
			case 45:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
			}break;
			case 46:{
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(QualID*, alloc(QualID)(_parsx_1.where, sym(_parsx_1)));
				}
			}break;
			case 47:{
				parsx_insert_token(KWith);
			}break;
			case 48:{
				{
					Expr* _parsx_4 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					List<AssignPair> _parsx_1 = parsx_pop_value(List<AssignPair>);
					parsx_push_value(List<AssignPair>, _parsx_1.append(alloc(AssignPair)(_parsx_2, _parsx_4)));
				}
			}break;
			case 49:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(QualID*, alloc(QualID)(_parsx_1.where, sym(_parsx_1)));
				}
			}break;
			case 50:{
			}break;
			case 51:{
				{
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<AssignPair> _parsx_1 = parsx_pop_value(List<AssignPair>);
					parsx_push_value(List<AssignPair>, _parsx_1);
				}
			}break;
			case 52:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					QualID* _parsx_1 = parsx_pop_value(QualID*);
					parsx_push_value(QualID*, alloc(QualID)(jf::SrcSpan(_parsx_1->where.from(), _parsx_3.where.to()), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 53:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Unit));
				}
			}break;
			case 54:{
				{
					parsx_token_type _parsx_6 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_5 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<ConstructorStringPart> _parsx_1 = parsx_pop_value(List<ConstructorStringPart>);
					parsx_push_value(List<ConstructorStringPart>, alloc(ConstructorStringPart)(_parsx_1, _parsx_3.where, sym(_parsx_3), _parsx_5));
				}
			}break;
			case 55:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
				{
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(List<ExprList>, alloc(ExprList)(_parsx_1));
				}
			}break;
			case 56:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Mult, _parsx_1, _parsx_3));
				}
			}break;
			case 57:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(List<ConstructorStringPart>, alloc(ConstructorStringPart)(nullptr, SrcSpan(_parsx_1.where, _parsx_3.where), StringRef(), _parsx_2));
				}
			}break;
			case 58:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Div, _parsx_1, _parsx_3));
				}
			}break;
			case 59:{
				{
					FunctionBody* _parsx_3 = parsx_pop_value(FunctionBody*);
					FunctionSignature* _parsx_2 = parsx_pop_value(FunctionSignature*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprLambda)(_parsx_1.where, _parsx_2, _parsx_3));
				}
			}break;
			case 60:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Rem, _parsx_1, _parsx_3));
				}
			}break;
			case 61:{
			}break;
			case 62:{
				{
					parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
				}
				{
					parsx_push_value(List<Stmt>, List<Stmt>());
				}
				parsx_insert_token(KEnd);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
					SrcLoc _parsx_1 = parsx_pop_value(SrcLoc);
					parsx_push_value(FunctionBody*, alloc(FunctionBodyDefined)(to_here(_parsx_1), _parsx_2));
				}
			}break;
			case 63:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Unit));
				}
			}break;
			case 64:{
				{
					parsx_push_value(List<ParamGroup>, nullptr);
				}
			}break;
			case 65:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Return, _parsx_2));
				}
			}break;
			case 66:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Eval, _parsx_2));
				}
			}break;
			case 67:{
			}break;
			case 68:{
				{
					ParamGroup* _parsx_3 = parsx_pop_value(ParamGroup*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<ParamGroup> _parsx_1 = parsx_pop_value(List<ParamGroup>);
					parsx_push_value(List<ParamGroup>, _parsx_1.append(_parsx_3));
				}
			}break;
			case 69:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Unit));
				}
				{
					Type* _parsx_1 = parsx_pop_value(Type*);
					parsx_push_value(ParamGroup*, alloc(ParamGroup)(nullptr, _parsx_1));
				}
			}break;
			case 70:{
				{
					List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_1 = parsx_pop_value(List<ExprList>);
					parsx_push_value(Stmt*, alloc(StmtAssign)(SrcSpan(_parsx_1.first->expr->where, _parsx_3.last->expr->where), _parsx_1, _parsx_3));
				}
			}break;
			case 71:{
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<Name> _parsx_1 = parsx_pop_value(List<Name>);
					parsx_push_value(ParamGroup*, alloc(ParamGroup)(_parsx_1, _parsx_3));
				}
			}break;
			case 72:{
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(List<Name>, alloc(Name)(_parsx_1.where, sym(_parsx_1)));
				}
			}break;
			case 73:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					WithSrcLoc<TypeReferenceNode*> _parsx_1 = parsx_pop_value(WithSrcLoc<TypeReferenceNode*>);
					parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1, alloc(TypeReferenceInstance)(_parsx_1, _parsx_4)));
				}
			}break;
			case 74:{
				{
					List<ExprList> _parsx_4 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Pattern> _parsx_2 = parsx_pop_value(List<Pattern>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtLet)(SrcSpan(_parsx_1.where, _parsx_4.last->expr->where), _parsx_2, _parsx_4));
				}
			}break;
			case 75:{
				{
					parsx_push_value(List<TypeList>, List<TypeList>());
				}
			}break;
			case 76:{
				parsx_insert_token(OPeriod);
			}break;
			case 77:{
				parsx_insert_token(OColon);
			}break;
			case 78:{
				parsx_insert_token(OLParen);
			}break;
			case 79:{
				parsx_insert_token(ORParen);
			}break;
			case 80:{
				parsx_insert_token(ORBrace);
			}break;
			case 81:{
				parsx_insert_token(OGT);
			}break;
			case 82:{
				{
					MatchBranch<Expr>* _parsx_5 = parsx_pop_value(MatchBranch<Expr>*);
					Expr* _parsx_4 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchBranch<Expr>*, alloc(MatchBranch<Expr>)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
				}
			}break;
			case 83:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 84:{
				{
					parsx_push_value(List< MatchCase<Stmt> >, List< MatchCase<Stmt> >());
				}
			}break;
			case 85:{
				parsx_insert_token(OMult);
			}break;
			case 86:{
				parsx_insert_token(OArrow);
			}break;
			case 87:{
				parsx_insert_token(OVBar);
			}break;
			case 88:{
				parsx_insert_token(OComma);
			}break;
			case 89:{
				parsx_insert_token(OAssign);
			}break;
			case 90:{
				parsx_insert_token(OQuote);
			}break;
			case 91:{
				{
					MatchCase<Stmt>* _parsx_2 = parsx_pop_value(MatchCase<Stmt>*);
					List< MatchCase<Stmt> > _parsx_1 = parsx_pop_value(List< MatchCase<Stmt> >);
					parsx_push_value(List< MatchCase<Stmt> >, _parsx_1.append(_parsx_2));
				}
			}break;
			case 92:{
				parsx_insert_token(Identifier);
			}break;
			case 93:{
				parsx_insert_token(StringLiteral);
			}break;
			case 94:{
			}break;
			case 95:{
				{
					parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprCall)(SrcSpan(_parsx_2.where, _parsx_4.where), _parsx_1, _parsx_3));
				}
			}break;
			case 96:{
			}break;
			case 97:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 98:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Eval, _parsx_2));
				}
			}break;
			case 99:{
				parsx_insert_token(KElse);
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
				parsx_insert_token(KEnd);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, _parsx_2);
				}
			}break;
			case 100:{
				parsx_insert_token(OVBar);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(int, 1);
				}
			}break;
			case 101:{
				{
					Expr* _parsx_5 = parsx_pop_value(Expr*);
					Expr* _parsx_4 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
				}
			}break;
			case 102:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprInstance)(SrcSpan(_parsx_2.where, _parsx_5.where), _parsx_1, _parsx_4));
				}
			}break;
			case 103:{
				{
					Expr* _parsx_5 = parsx_pop_value(Expr*);
					Type* _parsx_4 = parsx_pop_value(Type*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
				}
			}break;
			case 104:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 105:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprInstance)(SrcSpan(_parsx_2.where, _parsx_5.where), _parsx_1, _parsx_4));
				}
			}break;
			case 106:{
			}break;
			case 107:{
				{
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<Name> _parsx_1 = parsx_pop_value(List<Name>);
					parsx_push_value(List<Name>, _parsx_1.append(alloc(Name)(_parsx_2.where, sym(_parsx_2))));
				}
			}break;
			case 108:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, _parsx_2);
				}
			}break;
			case 109:{
				{
					Expr* _parsx_5 = parsx_pop_value(Expr*);
					Expr* _parsx_4 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
				}
			}break;
			case 110:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1.where.from(), alloc(TypeReferenceLeaf)(sym(_parsx_1))));
				}
				{
					WithSrcLoc<TypeReferenceNode*> _parsx_1 = parsx_pop_value(WithSrcLoc<TypeReferenceNode*>);
					parsx_push_value(Type*, alloc(TypeReference)(to_here(_parsx_1), _parsx_1));
				}
				{
					Type* _parsx_1 = parsx_pop_value(Type*);
					parsx_push_value(ParamGroup*, alloc(ParamGroup)(nullptr, _parsx_1));
				}
			}break;
			case 111:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List< MatchCase<Expr> > _parsx_4 = parsx_pop_value(List< MatchCase<Expr> >);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprMatch)(SrcSpan(_parsx_1.where, _parsx_5.where), _parsx_2, _parsx_4));
				}
			}break;
			case 112:{
				{
					parsx_push_value(MatchBranch<Stmt>*, nullptr);
				}
			}break;
			case 113:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, _parsx_2);
				}
			}break;
			case 114:{
				{
					Expr* _parsx_4 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtRepeat)(_parsx_1.where, _parsx_2, _parsx_4));
				}
			}break;
			case 115:{
			}break;
			case 116:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Not, _parsx_2));
				}
			}break;
			case 117:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
			}break;
			case 118:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Concat, _parsx_1, _parsx_3));
				}
			}break;
			case 119:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Plus, _parsx_1, _parsx_3));
				}
			}break;
			case 120:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Minus, _parsx_1, _parsx_3));
				}
			}break;
			case 121:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Type* _parsx_2 = parsx_pop_value(Type*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, _parsx_2);
				}
			}break;
			case 122:{
				{
					List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchBranch<Stmt>*, alloc(MatchBranch<Stmt>)(_parsx_1.where, nullptr, _parsx_2));
				}
			}break;
			case 123:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Mult, _parsx_1, _parsx_3));
				}
			}break;
			case 124:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Div, _parsx_1, _parsx_3));
				}
			}break;
			case 125:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Rem, _parsx_1, _parsx_3));
				}
			}break;
			case 126:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, nullptr, _parsx_3));
				}
			}break;
			case 127:{
				{
					MatchCase<Expr>* _parsx_2 = parsx_pop_value(MatchCase<Expr>*);
					List< MatchCase<Expr> > _parsx_1 = parsx_pop_value(List< MatchCase<Expr> >);
					parsx_push_value(List< MatchCase<Expr> >, _parsx_1.append(_parsx_2));
				}
			}break;
			case 128:{
				{
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					int _parsx_1 = parsx_pop_value(int);
					parsx_push_value(int, _parsx_1 + 1);
				}
			}break;
			case 129:{
				{
					parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprCall)(SrcSpan(_parsx_2.where, _parsx_4.where), _parsx_1, _parsx_3));
				}
			}break;
			case 130:{
				{
					Expr* _parsx_5 = parsx_pop_value(Expr*);
					Type* _parsx_4 = parsx_pop_value(Type*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
				}
			}break;
			case 131:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 132:{
			}break;
			case 133:{
			}break;
			case 134:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprInstance)(SrcSpan(_parsx_2.where, _parsx_5.where), _parsx_1, _parsx_4));
				}
			}break;
			case 135:{
				{
					MatchBranch<Expr>* _parsx_3 = parsx_pop_value(MatchBranch<Expr>*);
					List<Pattern> _parsx_2 = parsx_pop_value(List<Pattern>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchCase<Expr>*, alloc(MatchCase<Expr>)(_parsx_1.where, _parsx_2, _parsx_3));
				}
			}break;
			case 136:{
				{
					Expr* _parsx_5 = parsx_pop_value(Expr*);
					Expr* _parsx_4 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
				}
			}break;
			case 137:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List< MatchCase<Expr> > _parsx_4 = parsx_pop_value(List< MatchCase<Expr> >);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprMatch)(SrcSpan(_parsx_1.where, _parsx_5.where), _parsx_2, _parsx_4));
				}
			}break;
			case 138:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, nullptr, nullptr));
				}
			}break;
			case 139:{
				{
					Pattern* _parsx_2 = parsx_pop_value(Pattern*);
					QualID* _parsx_1 = parsx_pop_value(QualID*);
					parsx_push_value(Pattern*, alloc(PatternCons)(_parsx_1->where, _parsx_1, _parsx_2));
				}
			}break;
			case 140:{
				{
					parsx_push_value(List<Pattern>, List<Pattern>());
				}
			}break;
			case 141:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, _parsx_2);
				}
			}break;
			case 142:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprString)(_parsx_1.where, lit(_parsx_1)));
				}
			}break;
			case 143:{
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 144:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_4 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtWhile)(_parsx_1.where, _parsx_2, _parsx_4));
				}
			}break;
			case 145:{
				parsx_insert_token(KThen);
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchBranch<Expr>*, alloc(MatchBranch<Expr>)(_parsx_1.where, nullptr, _parsx_2));
				}
			}break;
			case 146:{
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 147:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(List<Name>, alloc(Name)(_parsx_1.where, sym(_parsx_1)));
				}
			}break;
			case 148:{
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 149:{
				{
					parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprCall)(SrcSpan(_parsx_2.where, _parsx_4.where), _parsx_1, _parsx_3));
				}
			}break;
			case 150:{
				{
					ParamGroup* _parsx_1 = parsx_pop_value(ParamGroup*);
					parsx_push_value(List<ParamGroup>, List<ParamGroup>(_parsx_1));
				}
			}break;
			case 151:{
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 152:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprInstance)(SrcSpan(_parsx_2.where, _parsx_5.where), _parsx_1, _parsx_4));
				}
			}break;
			case 153:{
				{
					parsx_push_value(List<AssignPair>, List<AssignPair>());
				}
			}break;
			case 154:{
				parsx_insert_token(ORParen);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Type* _parsx_2 = parsx_pop_value(Type*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, _parsx_2);
				}
			}break;
			case 155:{
				{
					Type* _parsx_2 = parsx_pop_value(Type*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, _parsx_2);
				}
			}break;
			case 156:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtBlock)(SrcSpan(_parsx_1.where, _parsx_3.where), _parsx_2));
				}
			}break;
			case 157:{
			}break;
			case 158:{
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					WithSrcLoc<TypeReferenceNode*> _parsx_1 = parsx_pop_value(WithSrcLoc<TypeReferenceNode*>);
					parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1, alloc(TypeReferenceSubscript)(_parsx_1, sym(_parsx_3))));
				}
			}break;
			case 159:{
			}break;
			case 160:{
				{
					List<ExprList> _parsx_4 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Pattern> _parsx_2 = parsx_pop_value(List<Pattern>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtLet)(SrcSpan(_parsx_1.where, _parsx_4.last->expr->where), _parsx_2, _parsx_4));
				}
			}break;
			case 161:{
				{
					parsx_token_type _parsx_6 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_5 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<ConstructorStringPart> _parsx_1 = parsx_pop_value(List<ConstructorStringPart>);
					parsx_push_value(List<ConstructorStringPart>, alloc(ConstructorStringPart)(_parsx_1, _parsx_3.where, sym(_parsx_3), _parsx_5));
				}
			}break;
			case 162:{
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 163:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List< MatchCase<Stmt> > _parsx_4 = parsx_pop_value(List< MatchCase<Stmt> >);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtMatch)(SrcSpan(_parsx_1.where, _parsx_5.where), _parsx_2, _parsx_4));
				}
			}break;
			case 164:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
					SrcLoc _parsx_1 = parsx_pop_value(SrcLoc);
					parsx_push_value(FunctionBody*, alloc(FunctionBodyDefined)(to_here(_parsx_1), _parsx_2));
				}
			}break;
			case 165:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::NE, _parsx_1, _parsx_3));
				}
			}break;
			case 166:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Not, _parsx_2));
				}
			}break;
			case 167:{
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 168:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Minus, _parsx_1, _parsx_3));
				}
			}break;
			case 169:{
				{
					Stmt* _parsx_2 = parsx_pop_value(Stmt*);
					List<Stmt> _parsx_1 = parsx_pop_value(List<Stmt>);
					parsx_push_value(List<Stmt>, _parsx_1.append(_parsx_2));
				}
			}break;
			case 170:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::LE, _parsx_1, _parsx_3));
				}
			}break;
			case 171:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Negate, _parsx_2));
				}
			}break;
			case 172:{
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(List<Name>, alloc(Name)(_parsx_1.where, sym(_parsx_1)));
				}
				parsx_insert_token(OSemicolon);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, nullptr, nullptr));
				}
			}break;
			case 173:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::GE, _parsx_1, _parsx_3));
				}
			}break;
			case 174:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Not, _parsx_2));
				}
			}break;
			case 175:{
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(ClassMember*, alloc(ClassField)(_parsx_2, _parsx_3));
				}
			}break;
			case 176:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::GT, _parsx_1, _parsx_3));
				}
			}break;
			case 177:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(FunctionBody*, alloc(FunctionBodyExpr)(_parsx_1.where, _parsx_2));
				}
			}break;
			case 178:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Rem, _parsx_1, _parsx_3));
				}
			}break;
			case 179:{
				{
					Type* _parsx_2 = parsx_pop_value(Type*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, _parsx_2);
				}
			}break;
			case 180:{
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprCoerce)(SrcSpan(_parsx_1->where, _parsx_3->where), _parsx_1, _parsx_3));
				}
			}break;
			case 181:{
				{
					List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_1 = parsx_pop_value(List<ExprList>);
					parsx_push_value(Stmt*, alloc(StmtAssign)(SrcSpan(_parsx_1.first->expr->where, _parsx_3.last->expr->where), _parsx_1, _parsx_3));
				}
			}break;
			case 182:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Or, _parsx_1, _parsx_3));
				}
			}break;
			case 183:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Not, _parsx_2));
				}
			}break;
			case 184:{
				{
					Type* _parsx_1 = parsx_pop_value(Type*);
					parsx_push_value(ParamGroup*, alloc(ParamGroup)(nullptr, _parsx_1));
				}
			}break;
			case 185:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
				{
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(List<ExprList>, alloc(ExprList)(_parsx_1));
				}
			}break;
			case 186:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_1 = parsx_pop_value(List<ExprList>);
					parsx_push_value(List<ExprList>, _parsx_1.append(alloc(ExprList)(_parsx_3)));
				}
			}break;
			case 187:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::And, _parsx_1, _parsx_3));
				}
			}break;
			case 188:{
				{
					use_decl
				}
			}break;
			case 189:{
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 190:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List<AssignPair> _parsx_4 = parsx_pop_value(List<AssignPair>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ConstructorStringPart> _parsx_2 = parsx_pop_value(List<ConstructorStringPart>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtConstruct)(_parsx_1.where, _parsx_2, _parsx_4));
				}
			}break;
			case 191:{
				{
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(List<ExprList>, alloc(ExprList)(_parsx_1));
				}
			}break;
			case 192:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 193:{
				{
					List<ConstructorStringPart> _parsx_3 = parsx_pop_value(List<ConstructorStringPart>);
					QualID* _parsx_2 = parsx_pop_value(QualID*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprNew)(SrcSpan(_parsx_1.where), _parsx_2, _parsx_3));
				}
			}break;
			case 194:{
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprCoerce)(SrcSpan(_parsx_1->where, _parsx_3->where), _parsx_1, _parsx_3));
				}
			}break;
			case 195:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprInstance)(SrcSpan(_parsx_2.where, _parsx_5.where), _parsx_1, _parsx_4));
				}
			}break;
			case 196:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, _parsx_2);
				}
			}break;
			case 197:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Or, _parsx_1, _parsx_3));
				}
			}break;
			case 198:{
				parsx_insert_token(OLParen);
				{
					parsx_push_value(List<ParamGroup>, nullptr);
				}
				parsx_insert_token(ORParen);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ParamGroup> _parsx_2 = parsx_pop_value(List<ParamGroup>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(FunctionSignature*, alloc(FunctionSignature)(to_here(_parsx_1.where.from()), _parsx_2, nullptr));
				}
			}break;
			case 199:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Plus, _parsx_1, _parsx_3));
				}
			}break;
			case 200:{
				{
					QualID* _parsx_2 = parsx_pop_value(QualID*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(QualID*, _parsx_2);
				}
			}break;
			case 201:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Minus, _parsx_1, _parsx_3));
				}
			}break;
			case 202:{
				{
					parsx_push_value(Pattern*, nullptr);
				}
			}break;
			case 203:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::And, _parsx_1, _parsx_3));
				}
			}break;
			case 204:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List< MatchCase<Expr> > _parsx_4 = parsx_pop_value(List< MatchCase<Expr> >);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprMatch)(SrcSpan(_parsx_1.where, _parsx_5.where), _parsx_2, _parsx_4));
				}
			}break;
			case 205:{
			}break;
			case 206:{
				{
					FunctionBody* _parsx_4 = parsx_pop_value(FunctionBody*);
					FunctionSignature* _parsx_3 = parsx_pop_value(FunctionSignature*);
					QualID* _parsx_2 = parsx_pop_value(QualID*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(ClassMember*, alloc(ClassConstructor)(_parsx_1.where, StringRef(), _parsx_2, _parsx_3, _parsx_4));
				}
			}break;
			case 207:{
				parsx_insert_token(OLParen);
				{
					parsx_push_value(List<ExprList>, List<ExprList>());
				}
				parsx_insert_token(ORParen);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(List<ConstructorStringPart>, alloc(ConstructorStringPart)(nullptr, SrcSpan(_parsx_1.where, _parsx_3.where), StringRef(), _parsx_2));
				}
			}break;
			case 208:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Mult, _parsx_1, _parsx_3));
				}
			}break;
			case 209:{
				{
					parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
				}
				parsx_insert_token(KImport);
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(QualID*, alloc(QualID)(_parsx_1.where, sym(_parsx_1)));
				}
				{
					parsx_push_value(StringRef, StringRef());
				}
				{
					StringRef _parsx_4 = parsx_pop_value(StringRef);
					QualID* _parsx_3 = parsx_pop_value(QualID*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					SrcLoc _parsx_1 = parsx_pop_value(SrcLoc);
					parsx_push_value(Import*, alloc(Import)(to_here(_parsx_1), _parsx_3, _parsx_4));
				}
			}break;
			case 210:{
				{
					parsx_push_value(List<Implements>, List<Implements>());
				}
			}break;
			case 211:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Div, _parsx_1, _parsx_3));
				}
			}break;
			case 212:{
				{
					Expr* _parsx_4 = parsx_pop_value(Expr*);
					Type* _parsx_3 = parsx_pop_value(Type*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(TopLevel*, alloc(GlobalVariable)(_parsx_2.where, sym(_parsx_2), _parsx_3, _parsx_4));
				}
			}break;
			case 213:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Negate, _parsx_2));
				}
			}break;
			case 214:{
				{
					List<ConstructorStringPart> _parsx_2 = parsx_pop_value(List<ConstructorStringPart>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtConstructPass)(_parsx_1.where, _parsx_2));
				}
			}break;
			case 215:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Div, _parsx_1, _parsx_3));
				}
			}break;
			case 216:{
			}break;
			case 217:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Not, _parsx_2));
				}
			}break;
			case 218:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Plus, _parsx_1, _parsx_3));
				}
			}break;
			case 219:{
				{
					parsx_push_value(List<EnumConstructor>, List<EnumConstructor>());
				}
			}break;
			case 220:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Minus, _parsx_1, _parsx_3));
				}
			}break;
			case 221:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Minus, _parsx_1, _parsx_3));
				}
			}break;
			case 222:{
				{
					EnumConstructor* _parsx_2 = parsx_pop_value(EnumConstructor*);
					List<EnumConstructor> _parsx_1 = parsx_pop_value(List<EnumConstructor>);
					parsx_push_value(List<EnumConstructor>, _parsx_1.append(_parsx_2));
				}
			}break;
			case 223:{
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(EnumConstructor*, alloc(EnumConstructor)(_parsx_1.where, sym(_parsx_1), nullptr));
				}
			}break;
			case 224:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, alloc(PatternPrim)(_parsx_1.where, PatternPrim::True));
				}
			}break;
			case 225:{
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprCoerce)(SrcSpan(_parsx_1->where, _parsx_3->where), _parsx_1, _parsx_3));
				}
			}break;
			case 226:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(FunctionBody*, alloc(FunctionBodyExpr)(_parsx_1.where, _parsx_2));
				}
			}break;
			case 227:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(QualID*, alloc(QualID)(SrcSpan(_parsx_1.where, _parsx_3.where), alloc(QualID)(SrcSpan(_parsx_1.where), sym(_parsx_1)), sym(_parsx_3)));
				}
			}break;
			case 228:{
			}break;
			case 229:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::LT, _parsx_1, _parsx_3));
				}
			}break;
			case 230:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Unit));
				}
			}break;
			case 231:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, alloc(PatternPrim)(_parsx_1.where, PatternPrim::Null));
				}
			}break;
			case 232:{
				parsx_insert_token(OColon);
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Unit));
				}
				{
					Type* _parsx_2 = parsx_pop_value(Type*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, _parsx_2);
				}
			}break;
			case 233:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Div, _parsx_1, _parsx_3));
				}
			}break;
			case 234:{
				{
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_1 = parsx_pop_value(List<Stmt>);
					parsx_push_value(List<Stmt>, _parsx_1);
				}
			}break;
			case 235:{
				{
					List<TypeList> _parsx_1 = parsx_pop_value(List<TypeList>);
					parsx_push_value(Type*, alloc(TypeUnion)(SrcSpan(_parsx_1.first->type->where.from(), _parsx_1.last->type->where.to()), _parsx_1));
				}
			}break;
			case 236:{
				parsx_insert_token(OSemicolon);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, nullptr, nullptr));
				}
			}break;
			case 237:{
				{
					parsx_token_type _parsx_6 = parsx_pop_value(parsx_token_type);
					List<ClassMember> _parsx_5 = parsx_pop_value(List<ClassMember>);
					List<Implements> _parsx_4 = parsx_pop_value(List<Implements>);
					Extends* _parsx_3 = parsx_pop_value(Extends*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(TopLevel*, alloc(Class)(_parsx_2.where, sym(_parsx_2), _parsx_3, _parsx_4, _parsx_5));
				}
			}break;
			case 238:{
				{
					Stmt* _parsx_1 = parsx_pop_value(Stmt*);
					parsx_push_value(List<Stmt>, List<Stmt>(_parsx_1));
				}
			}break;
			case 239:{
			}break;
			case 240:{
			}break;
			case 241:{
				parsx_insert_token(OLParen);
				{
					parsx_push_value(List<ParamGroup>, nullptr);
				}
				parsx_insert_token(ORParen);
				{
					parsx_push_value(Type*, nullptr);
				}
				{
					Type* _parsx_4 = parsx_pop_value(Type*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ParamGroup> _parsx_2 = parsx_pop_value(List<ParamGroup>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(FunctionSignature*, alloc(FunctionSignature)(to_here(_parsx_1.where.from()), _parsx_2, _parsx_4));
				}
			}break;
			case 242:{
				{
					FunctionSignature* _parsx_3 = parsx_pop_value(FunctionSignature*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(ClassMember*, alloc(ClassMethod)(ClassMethod::Abstract, _parsx_2.where, sym(_parsx_2), _parsx_3, nullptr));
				}
			}break;
			case 243:{
				{
					parsx_push_value(int, 0);
				}
			}break;
			case 244:{
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<TypeList> _parsx_1 = parsx_pop_value(List<TypeList>);
					parsx_push_value(List<TypeList>, _parsx_1.append(alloc(TypeList)(_parsx_3)));
				}
			}break;
			case 245:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, alloc(PatternNumber)(_parsx_1.where, sym(_parsx_1)));
				}
			}break;
			case 246:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Raise, _parsx_2));
				}
			}break;
			case 247:{
				{
					FunctionBody* _parsx_4 = parsx_pop_value(FunctionBody*);
					FunctionSignature* _parsx_3 = parsx_pop_value(FunctionSignature*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(ClassMember*, alloc(ClassMethod)(ClassMethod::Method, _parsx_2.where, sym(_parsx_2), _parsx_3, _parsx_4));
				}
			}break;
			case 248:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					QualID* _parsx_1 = parsx_pop_value(QualID*);
					parsx_push_value(QualID*, alloc(QualID)(jf::SrcSpan(_parsx_1->where.from(), _parsx_3.where.to()), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 249:{
				{
					use_def
				}
				{
					parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
				}
				{
					parsx_push_value(List<Stmt>, List<Stmt>());
				}
				parsx_insert_token(KEnd);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
					SrcLoc _parsx_1 = parsx_pop_value(SrcLoc);
					parsx_push_value(FunctionBody*, alloc(FunctionBodyDefined)(to_here(_parsx_1), _parsx_2));
				}
				{
					use_decl
				}
			}break;
			case 250:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::LT, _parsx_1, _parsx_3));
				}
			}break;
			case 251:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
			}break;
			case 252:{
				{
					parsx_push_value(Type*, nullptr);
				}
			}break;
			case 253:{
			}break;
			case 254:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
			}break;
			case 255:{
			}break;
			case 256:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::EQ, _parsx_1, _parsx_3));
				}
			}break;
			case 257:{
			}break;
			case 258:{
			}break;
			case 259:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Concat, _parsx_1, _parsx_3));
				}
			}break;
			case 260:{
			}break;
			case 261:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
			}break;
			case 262:{
				{
					parsx_push_value(List<StructField>, List<StructField>());
				}
			}break;
			case 263:{
			}break;
			case 264:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Plus, _parsx_1, _parsx_3));
				}
			}break;
			case 265:{
				{
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Type* _parsx_1 = parsx_pop_value(Type*);
					parsx_push_value(Type*, alloc(TypeOptional)(SrcSpan(_parsx_1->where.from(), _parsx_2.where.to()), _parsx_1));
				}
			}break;
			case 266:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
			}break;
			case 267:{
			}break;
			case 268:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Unit));
				}
			}break;
			case 269:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
			}break;
			case 270:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Undef));
				}
			}break;
			case 271:{
			}break;
			case 272:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Bool));
				}
			}break;
			case 273:{
			}break;
			case 274:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Int));
				}
			}break;
			case 275:{
			}break;
			case 276:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Pattern* _parsx_2 = parsx_pop_value(Pattern*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, _parsx_2);
				}
			}break;
			case 277:{
			}break;
			case 278:{
			}break;
			case 279:{
			}break;
			case 280:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Double));
				}
			}break;
			case 281:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::String));
				}
			}break;
			case 282:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_1 = parsx_pop_value(List<ExprList>);
					parsx_push_value(List<ExprList>, _parsx_1.append(alloc(ExprList)(_parsx_3)));
				}
			}break;
			case 283:{
				{
					parsx_push_value(List<ExprList>, List<ExprList>());
				}
			}break;
			case 284:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Bytes));
				}
			}break;
			case 285:{
			}break;
			case 286:{
			}break;
			case 287:{
			}break;
			case 288:{
				{
					WithSrcLoc<TypeReferenceNode*> _parsx_1 = parsx_pop_value(WithSrcLoc<TypeReferenceNode*>);
					parsx_push_value(Type*, alloc(TypeReference)(to_here(_parsx_1), _parsx_1));
				}
			}break;
			case 289:{
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1.where.from(), alloc(TypeReferenceLeaf)(sym(_parsx_1))));
				}
			}break;
			case 290:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, alloc(PatternVar)(_parsx_1.where, sym(_parsx_1)));
				}
			}break;
			case 291:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					WithSrcLoc<TypeReferenceNode*> _parsx_1 = parsx_pop_value(WithSrcLoc<TypeReferenceNode*>);
					parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1, alloc(TypeReferenceSubscript)(_parsx_1, sym(_parsx_3))));
				}
			}break;
			case 292:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_1 = parsx_pop_value(List<ExprList>);
					parsx_push_value(List<ExprList>, _parsx_1.append(alloc(ExprList)(_parsx_3)));
				}
			}break;
			case 293:{
				parsx_insert_token(KField);
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(List<Name>, alloc(Name)(_parsx_1.where, sym(_parsx_1)));
				}
				parsx_insert_token(OColon);
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Unit));
				}
				{
					Type* _parsx_2 = parsx_pop_value(Type*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, _parsx_2);
				}
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(ClassMember*, alloc(ClassField)(_parsx_2, _parsx_3));
				}
			}break;
			case 294:{
			}break;
			case 295:{
				{
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(List<ExprList>, alloc(ExprList)(_parsx_1));
				}
			}break;
			case 296:{
			}break;
			case 297:{
			}break;
			case 298:{
				{
					parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
				}
				{
					parsx_push_value(List<Stmt>, List<Stmt>());
				}
				parsx_insert_token(KEnd);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
					SrcLoc _parsx_1 = parsx_pop_value(SrcLoc);
					parsx_push_value(FunctionBody*, alloc(FunctionBodyDefined)(to_here(_parsx_1), _parsx_2));
				}
			}break;
			case 299:{
			}break;
			case 300:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprInstance)(SrcSpan(_parsx_2.where, _parsx_5.where), _parsx_1, _parsx_4));
				}
			}break;
			case 301:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Negate, _parsx_2));
				}
			}break;
			case 302:{
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<TypeList> _parsx_1 = parsx_pop_value(List<TypeList>);
					parsx_push_value(List<TypeList>, _parsx_1.append(alloc(TypeList)(_parsx_3)));
				}
			}break;
			case 303:{
			}break;
			case 304:{
				{
					Type* _parsx_1 = parsx_pop_value(Type*);
					parsx_push_value(List<TypeList>, alloc(TypeList)(_parsx_1));
				}
			}break;
			case 305:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::EQ, _parsx_1, _parsx_3));
				}
			}break;
			case 306:{
			}break;
			case 307:{
				{
					parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprCall)(SrcSpan(_parsx_2.where, _parsx_4.where), _parsx_1, _parsx_3));
				}
			}break;
			case 308:{
			}break;
			case 309:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					WithSrcLoc<TypeReferenceNode*> _parsx_1 = parsx_pop_value(WithSrcLoc<TypeReferenceNode*>);
					parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1, alloc(TypeReferenceInstance)(_parsx_1, List<TypeList>())));
				}
			}break;
			case 310:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, _parsx_2);
				}
			}break;
			case 311:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(WithSrcLoc<TypeReferenceNode*>, WithSrcLoc<TypeReferenceNode*>(_parsx_1.where.from(), alloc(TypeReferenceLeaf)(sym(_parsx_1))));
				}
			}break;
			case 312:{
				{
					Expr* _parsx_5 = parsx_pop_value(Expr*);
					Expr* _parsx_4 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
				}
			}break;
			case 313:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<TypeList> _parsx_2 = parsx_pop_value(List<TypeList>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypeTuple)(SrcSpan(_parsx_1.where.from(), _parsx_3.where.to()), _parsx_2));
				}
			}break;
			case 314:{
				{
					parsx_push_value(List< MatchCase<Expr> >, List< MatchCase<Expr> >());
				}
			}break;
			case 315:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List< MatchCase<Expr> > _parsx_4 = parsx_pop_value(List< MatchCase<Expr> >);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_2 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprMatch)(SrcSpan(_parsx_1.where, _parsx_5.where), _parsx_2, _parsx_4));
				}
			}break;
			case 316:{
			}break;
			case 317:{
				{
					Type* _parsx_4 = parsx_pop_value(Type*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypeFunction)(SrcSpan(_parsx_1.where, _parsx_4->where), nullptr, _parsx_4));
				}
			}break;
			case 318:{
				parsx_insert_token(KCase);
				{
					parsx_push_value(List<Pattern>, List<Pattern>());
				}
				parsx_insert_token(KThen);
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchBranch<Expr>*, alloc(MatchBranch<Expr>)(_parsx_1.where, nullptr, _parsx_2));
				}
				{
					MatchBranch<Expr>* _parsx_3 = parsx_pop_value(MatchBranch<Expr>*);
					List<Pattern> _parsx_2 = parsx_pop_value(List<Pattern>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(MatchCase<Expr>*, alloc(MatchCase<Expr>)(_parsx_1.where, _parsx_2, _parsx_3));
				}
			}break;
			case 319:{
				{
					Type* _parsx_5 = parsx_pop_value(Type*);
					parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<TypeList> _parsx_2 = parsx_pop_value(List<TypeList>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypeFunction)(SrcSpan(_parsx_1.where, _parsx_5->where), _parsx_2, _parsx_5));
				}
			}break;
			case 320:{
				{
					FunctionBody* _parsx_4 = parsx_pop_value(FunctionBody*);
					FunctionSignature* _parsx_3 = parsx_pop_value(FunctionSignature*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(ClassMember*, alloc(ClassMethod)(ClassMethod::Override, _parsx_2.where, sym(_parsx_2), _parsx_3, _parsx_4));
				}
			}break;
			case 321:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Unit));
				}
				parsx_insert_token(OComma);
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Unit));
				}
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Type* _parsx_1 = parsx_pop_value(Type*);
					parsx_push_value(List<TypeList>, List<TypeList>(alloc(TypeList)(_parsx_1)).append(alloc(TypeList)(_parsx_3)));
				}
			}break;
			case 322:{
			}break;
			case 323:{
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<TypeList> _parsx_1 = parsx_pop_value(List<TypeList>);
					parsx_push_value(List<TypeList>, _parsx_1.append(alloc(TypeList)(_parsx_3)));
				}
			}break;
			case 324:{
				{
					parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprCall)(SrcSpan(_parsx_2.where, _parsx_4.where), _parsx_1, _parsx_3));
				}
			}break;
			case 325:{
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Type* _parsx_1 = parsx_pop_value(Type*);
					parsx_push_value(List<TypeList>, List<TypeList>(alloc(TypeList)(_parsx_1)).append(alloc(TypeList)(_parsx_3)));
				}
			}break;
			case 326:{
			}break;
			case 327:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, alloc(PatternPrim)(_parsx_1.where, PatternPrim::Unit));
				}
				{
					Pattern* _parsx_1 = parsx_pop_value(Pattern*);
					parsx_push_value(List<Pattern>, List<Pattern>(_parsx_1));
				}
			}break;
			case 328:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Concat, _parsx_1, _parsx_3));
				}
			}break;
			case 329:{
				{
					Pattern* _parsx_3 = parsx_pop_value(Pattern*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<Pattern> _parsx_1 = parsx_pop_value(List<Pattern>);
					parsx_push_value(List<Pattern>, _parsx_1.append(_parsx_3));
				}
			}break;
			case 330:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Unit));
				}
				parsx_insert_token(ORParen);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Type* _parsx_2 = parsx_pop_value(Type*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, _parsx_2);
				}
			}break;
			case 331:{
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Type* _parsx_1 = parsx_pop_value(Type*);
					parsx_push_value(List<TypeList>, List<TypeList>(alloc(TypeList)(_parsx_1)).append(alloc(TypeList)(_parsx_3)));
				}
			}break;
			case 332:{
			}break;
			case 333:{
			}break;
			case 334:{
			}break;
			case 335:{
				{
					FunctionBody* _parsx_5 = parsx_pop_value(FunctionBody*);
					FunctionSignature* _parsx_4 = parsx_pop_value(FunctionSignature*);
					QualID* _parsx_3 = parsx_pop_value(QualID*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(ClassMember*, alloc(ClassConstructor)(_parsx_2.where, sym(_parsx_2), _parsx_3, _parsx_4, _parsx_5));
				}
			}break;
			case 336:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Pattern* _parsx_1 = parsx_pop_value(Pattern*);
					parsx_push_value(Pattern*, alloc(PatternRemember)(_parsx_3.where, _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 337:{
				{
					parsx_token_type _parsx_7 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_6 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_4 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtFor)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_6));
				}
			}break;
			case 338:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Or, _parsx_1, _parsx_3));
				}
			}break;
			case 339:{
				{
					Type* _parsx_4 = parsx_pop_value(Type*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ParamGroup> _parsx_2 = parsx_pop_value(List<ParamGroup>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(FunctionSignature*, alloc(FunctionSignature)(to_here(_parsx_1.where.from()), _parsx_2, _parsx_4));
				}
			}break;
			case 340:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::NE, _parsx_1, _parsx_3));
				}
			}break;
			case 341:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Negate, _parsx_2));
				}
			}break;
			case 342:{
				{
					parsx_push_value(QualID*, nullptr);
				}
			}break;
			case 343:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Mult, _parsx_1, _parsx_3));
				}
			}break;
			case 344:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnOp)(SrcSpan(_parsx_1.where.from(), _parsx_2->where.to()), ExprUnOp::Not, _parsx_2));
				}
			}break;
			case 345:{
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Type* _parsx_1 = parsx_pop_value(Type*);
					parsx_push_value(Type*, alloc(TypeFunction)(SrcSpan(_parsx_1->where, _parsx_3->where), alloc(TypeList)(_parsx_1), _parsx_3));
				}
			}break;
			case 346:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Rem, _parsx_1, _parsx_3));
				}
			}break;
			case 347:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::LE, _parsx_1, _parsx_3));
				}
			}break;
			case 348:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::GE, _parsx_1, _parsx_3));
				}
			}break;
			case 349:{
			}break;
			case 350:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::GT, _parsx_1, _parsx_3));
				}
			}break;
			case 351:{
			}break;
			case 352:{
			}break;
			case 353:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::And, _parsx_1, _parsx_3));
				}
			}break;
			case 354:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Plus, _parsx_1, _parsx_3));
				}
			}break;
			case 355:{
				{
					parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprCall)(SrcSpan(_parsx_2.where, _parsx_4.where), _parsx_1, _parsx_3));
				}
			}break;
			case 356:{
				parsx_insert_token(OSemicolon);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, nullptr, nullptr));
				}
			}break;
			case 357:{
				{
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(FunctionBody*, alloc(FunctionBodyImport)(_parsx_2.where, lit(_parsx_2)));
				}
			}break;
			case 358:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 359:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List<TypeList> _parsx_4 = parsx_pop_value(List<TypeList>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprInstance)(SrcSpan(_parsx_2.where, _parsx_5.where), _parsx_1, _parsx_4));
				}
			}break;
			case 360:{
			}break;
			case 361:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, _parsx_2);
				}
			}break;
			case 362:{
				{
					Expr* _parsx_5 = parsx_pop_value(Expr*);
					Expr* _parsx_4 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
				}
			}break;
			case 363:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(EnumConstructor*, alloc(EnumConstructor)(_parsx_1.where, sym(_parsx_1), nullptr));
				}
			}break;
			case 364:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::NE, _parsx_1, _parsx_3));
				}
			}break;
			case 365:{
			}break;
			case 366:{
				{
					parsx_push_value(QualID*, nullptr);
				}
				parsx_insert_token(OLParen);
				{
					parsx_push_value(List<ParamGroup>, nullptr);
				}
				parsx_insert_token(ORParen);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ParamGroup> _parsx_2 = parsx_pop_value(List<ParamGroup>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(FunctionSignature*, alloc(FunctionSignature)(to_here(_parsx_1.where.from()), _parsx_2, nullptr));
				}
				{
					use_def
				}
				{
					parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
				}
				{
					parsx_push_value(List<Stmt>, List<Stmt>());
				}
				parsx_insert_token(KEnd);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
					SrcLoc _parsx_1 = parsx_pop_value(SrcLoc);
					parsx_push_value(FunctionBody*, alloc(FunctionBodyDefined)(to_here(_parsx_1), _parsx_2));
				}
				{
					use_decl
				}
				{
					FunctionBody* _parsx_4 = parsx_pop_value(FunctionBody*);
					FunctionSignature* _parsx_3 = parsx_pop_value(FunctionSignature*);
					QualID* _parsx_2 = parsx_pop_value(QualID*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(ClassMember*, alloc(ClassConstructor)(_parsx_1.where, StringRef(), _parsx_2, _parsx_3, _parsx_4));
				}
			}break;
			case 367:{
				parsx_insert_token(KThen);
			}break;
			case 368:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::LE, _parsx_1, _parsx_3));
				}
			}break;
			case 369:{
				{
					parsx_push_value(List<ConstructorStringPart>, nullptr);
				}
				{
					List<ConstructorStringPart> _parsx_2 = parsx_pop_value(List<ConstructorStringPart>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtConstructPass)(_parsx_1.where, _parsx_2));
				}
			}break;
			case 370:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::GE, _parsx_1, _parsx_3));
				}
			}break;
			case 371:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<ParamGroup> _parsx_2 = parsx_pop_value(List<ParamGroup>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(FunctionSignature*, alloc(FunctionSignature)(to_here(_parsx_1.where.from()), _parsx_2, nullptr));
				}
			}break;
			case 372:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::LT, _parsx_1, _parsx_3));
				}
			}break;
			case 373:{
				parsx_insert_token(KDo);
			}break;
			case 374:{
				parsx_insert_token(KIn);
			}break;
			case 375:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
			}break;
			case 376:{
			}break;
			case 377:{
				{
					List<Stmt> _parsx_5 = parsx_pop_value(List<Stmt>);
					List<Stmt> _parsx_4 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
				}
			}break;
			case 378:{
				{
					List<Stmt> _parsx_5 = parsx_pop_value(List<Stmt>);
					List<Stmt> _parsx_4 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
				}
			}break;
			case 379:{
				parsx_insert_token(KEnd);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(List<Stmt>, nullptr);
				}
			}break;
			case 380:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprSubscript)(SrcSpan(_parsx_2.where, _parsx_3.where), _parsx_1, sym(_parsx_3)));
				}
			}break;
			case 381:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(List<Stmt>, nullptr);
				}
			}break;
			case 382:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(List<Stmt>, _parsx_2);
				}
			}break;
			case 383:{
				parsx_insert_token(KUntil);
			}break;
			case 384:{
				{
					List<Stmt> _parsx_5 = parsx_pop_value(List<Stmt>);
					List<Stmt> _parsx_4 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(List<Stmt>, alloc(StmtIf)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_5));
				}
			}break;
			case 385:{
			}break;
			case 386:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_4 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtWhile)(_parsx_1.where, _parsx_2, _parsx_4));
				}
			}break;
			case 387:{
			}break;
			case 388:{
				{
					Expr* _parsx_4 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_2 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtRepeat)(_parsx_1.where, _parsx_2, _parsx_4));
				}
			}break;
			case 389:{
			}break;
			case 390:{
				{
					parsx_token_type _parsx_7 = parsx_pop_value(parsx_token_type);
					List<Stmt> _parsx_6 = parsx_pop_value(List<Stmt>);
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_4 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtFor)(_parsx_1.where, _parsx_2, _parsx_4, _parsx_6));
				}
			}break;
			case 391:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, nullptr, _parsx_3));
				}
			}break;
			case 392:{
				parsx_insert_token(OAssign);
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, _parsx_2);
				}
			}break;
			case 393:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::EQ, _parsx_1, _parsx_3));
				}
			}break;
			case 394:{
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, _parsx_2);
				}
			}break;
			case 395:{
				parsx_insert_token(KEnum);
				parsx_insert_token(Identifier);
				{
					parsx_push_value(List<EnumConstructor>, List<EnumConstructor>());
				}
				parsx_insert_token(KEnd);
				{
					parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
					List<EnumConstructor> _parsx_3 = parsx_pop_value(List<EnumConstructor>);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(TopLevel*, alloc(Enum)(_parsx_2.where, sym(_parsx_2), _parsx_3));
				}
			}break;
			case 396:{
			}break;
			case 397:{
				{
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1->where, StmtEval::Naked, _parsx_1));
				}
			}break;
			case 398:{
				{
					FunctionBody* _parsx_4 = parsx_pop_value(FunctionBody*);
					FunctionSignature* _parsx_3 = parsx_pop_value(FunctionSignature*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(TopLevel*, alloc(GlobalFunction)(_parsx_2.where, sym(_parsx_2), _parsx_3, _parsx_4));
				}
			}break;
			case 399:{
			}break;
			case 400:{
				{
					FunctionSignature* _parsx_2 = parsx_pop_value(FunctionSignature*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(EnumConstructor*, alloc(EnumConstructor)(_parsx_1.where, sym(_parsx_1), _parsx_2));
				}
			}break;
			case 401:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Unit));
				}
			}break;
			case 402:{
				{
					List<ConstructorStringPart> _parsx_2 = parsx_pop_value(List<ConstructorStringPart>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtConstructPass)(_parsx_1.where, _parsx_2));
				}
			}break;
			case 403:{
				{
					parsx_token_type _parsx_5 = parsx_pop_value(parsx_token_type);
					List<InterfaceMethod> _parsx_4 = parsx_pop_value(List<InterfaceMethod>);
					List<Implements> _parsx_3 = parsx_pop_value(List<Implements>);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(TopLevel*, alloc(Interface)(_parsx_2.where, sym(_parsx_2), _parsx_3, _parsx_4));
				}
			}break;
			case 404:{
				{
					parsx_push_value(List<Implements>, List<Implements>());
				}
			}break;
			case 405:{
				{
					parsx_push_value(SrcLoc, parsx_next_shifted.where.from());
				}
			}break;
			case 406:{
				{
					parsx_push_value(List<InterfaceMethod>, List<InterfaceMethod>());
				}
			}break;
			case 407:{
				{
					QualID* _parsx_3 = parsx_pop_value(QualID*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<Implements> _parsx_1 = parsx_pop_value(List<Implements>);
					parsx_push_value(List<Implements>, _parsx_1.append(alloc(Implements)(_parsx_3->where, _parsx_3)));
				}
			}break;
			case 408:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Concat, _parsx_1, _parsx_3));
				}
			}break;
			case 409:{
			}break;
			case 410:{
			}break;
			case 411:{
			}break;
			case 412:{
				{
					FunctionSignature* _parsx_4 = parsx_pop_value(FunctionSignature*);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<InterfaceMethod> _parsx_1 = parsx_pop_value(List<InterfaceMethod>);
					parsx_push_value(List<InterfaceMethod>, _parsx_1.append(alloc(InterfaceMethod)(_parsx_3.where, sym(_parsx_3), _parsx_4)));
				}
			}break;
			case 413:{
			}break;
			case 414:{
				{
					Expr* _parsx_3 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprBinOp)(SrcSpan(_parsx_1->where.from(), _parsx_3->where.to()), ExprBinOp::Mult, _parsx_1, _parsx_3));
				}
			}break;
			case 415:{
				{
					Pattern* _parsx_2 = parsx_pop_value(Pattern*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, alloc(PatternCons)(to_here(_parsx_1.where.from()), alloc(QualID)(_parsx_1.where, sym(_parsx_1)), _parsx_2));
				}
			}break;
			case 416:{
				{
					use_def
				}
				parsx_insert_token(OAssign);
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, alloc(ExprUnit)(_parsx_1.where));
				}
				{
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Expr*, _parsx_2);
				}
				{
					use_decl
				}
			}break;
			case 417:{
				{
					parsx_push_value(Extends*, nullptr);
				}
			}break;
			case 418:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, alloc(PatternPrim)(_parsx_1.where, PatternPrim::Unit));
				}
			}break;
			case 419:{
				{
					QualID* _parsx_2 = parsx_pop_value(QualID*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Extends*, alloc(Extends)(_parsx_2->where, _parsx_2));
				}
			}break;
			case 420:{
			}break;
			case 421:{
			}break;
			case 422:{
				{
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1->where, StmtEval::Naked, _parsx_1));
				}
			}break;
			case 423:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(int, 1);
				}
			}break;
			case 424:{
			}break;
			case 425:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, alloc(PatternPrim)(_parsx_1.where, PatternPrim::False));
				}
			}break;
			case 426:{
				{
					parsx_push_value(List<ClassMember>, List<ClassMember>());
				}
			}break;
			case 427:{
				{
					QualID* _parsx_3 = parsx_pop_value(QualID*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					List<Implements> _parsx_1 = parsx_pop_value(List<Implements>);
					parsx_push_value(List<Implements>, _parsx_1.append(alloc(Implements)(_parsx_3->where, _parsx_3)));
				}
			}break;
			case 428:{
			}break;
			case 429:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, alloc(PatternPrim)(_parsx_1.where, PatternPrim::Wildcard));
				}
			}break;
			case 430:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, alloc(PatternVar)(_parsx_1.where, sym(_parsx_1)));
				}
			}break;
			case 431:{
				{
					ClassMember* _parsx_2 = parsx_pop_value(ClassMember*);
					List<ClassMember> _parsx_1 = parsx_pop_value(List<ClassMember>);
					parsx_push_value(List<ClassMember>, _parsx_1.append(_parsx_2));
				}
			}break;
			case 432:{
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(List<Name>, alloc(Name)(_parsx_1.where, sym(_parsx_1)));
				}
				parsx_insert_token(OSemicolon);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtVar)(_parsx_1.where, _parsx_2, nullptr, nullptr));
				}
			}break;
			case 433:{
			}break;
			case 434:{
			}break;
			case 435:{
				{
					parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
					List<StructField> _parsx_3 = parsx_pop_value(List<StructField>);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(TopLevel*, alloc(Struct)(_parsx_2.where, sym(_parsx_2), _parsx_3));
				}
			}break;
			case 436:{
				{
					int _parsx_4 = parsx_pop_value(int);
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					int _parsx_2 = parsx_pop_value(int);
					SrcLoc _parsx_1 = parsx_pop_value(SrcLoc);
					parsx_push_value(EnumConstructorNumber, EnumConstructorNumber(to_here(_parsx_1), _parsx_2, _parsx_2 + _parsx_4));
				}
			}break;
			case 437:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_2 = parsx_pop_value(Expr*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, alloc(PatternQuote)(_parsx_2->where, _parsx_2));
				}
			}break;
			case 438:{
				{
					StructField* _parsx_2 = parsx_pop_value(StructField*);
					List<StructField> _parsx_1 = parsx_pop_value(List<StructField>);
					parsx_push_value(List<StructField>, _parsx_1.append(_parsx_2));
				}
			}break;
			case 439:{
				parsx_insert_token(KField);
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(List<Name>, alloc(Name)(_parsx_1.where, sym(_parsx_1)));
				}
				parsx_insert_token(OColon);
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Unit));
				}
				{
					Type* _parsx_2 = parsx_pop_value(Type*);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, _parsx_2);
				}
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(StructField*, alloc(StructField)(_parsx_2, _parsx_3));
				}
			}break;
			case 440:{
				{
					parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
					List<ExprList> _parsx_3 = parsx_pop_value(List<ExprList>);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Expr* _parsx_1 = parsx_pop_value(Expr*);
					parsx_push_value(Expr*, alloc(ExprCall)(SrcSpan(_parsx_2.where, _parsx_4.where), _parsx_1, _parsx_3));
				}
			}break;
			case 441:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<Pattern> _parsx_2 = parsx_pop_value(List<Pattern>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, alloc(PatternTuple)(SrcSpan(_parsx_1.where, _parsx_3.where), _parsx_2));
				}
			}break;
			case 442:{
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					List<Name> _parsx_2 = parsx_pop_value(List<Name>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(StructField*, alloc(StructField)(_parsx_2, _parsx_3));
				}
			}break;
			case 443:{
				{
					parsx_token_type _parsx_4 = parsx_pop_value(parsx_token_type);
					List<EnumConstructor> _parsx_3 = parsx_pop_value(List<EnumConstructor>);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(TopLevel*, alloc(Enum)(_parsx_2.where, sym(_parsx_2), _parsx_3));
				}
			}break;
			case 444:{
				parsx_insert_token(Identifier);
				parsx_insert_token(OPeriod);
				parsx_insert_token(Identifier);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(QualID*, alloc(QualID)(SrcSpan(_parsx_1.where, _parsx_3.where), alloc(QualID)(SrcSpan(_parsx_1.where), sym(_parsx_1)), sym(_parsx_3)));
				}
			}break;
			case 445:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Unit));
				}
				parsx_insert_token(OVBar);
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Unit));
				}
				{
					Type* _parsx_3 = parsx_pop_value(Type*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					Type* _parsx_1 = parsx_pop_value(Type*);
					parsx_push_value(List<TypeList>, List<TypeList>(alloc(TypeList)(_parsx_1)).append(alloc(TypeList)(_parsx_3)));
				}
			}break;
			case 446:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, alloc(PatternString)(_parsx_1.where, lit(_parsx_1)));
				}
			}break;
			case 447:{
				{
					parsx_push_value(List<Import>, List<Import>());
				}
			}break;
			case 448:{
				{
					StringRef _parsx_4 = parsx_pop_value(StringRef);
					QualID* _parsx_3 = parsx_pop_value(QualID*);
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					SrcLoc _parsx_1 = parsx_pop_value(SrcLoc);
					parsx_push_value(Import*, alloc(Import)(to_here(_parsx_1), _parsx_3, _parsx_4));
				}
			}break;
			case 449:{
				{
					parsx_push_value(StringRef, StringRef());
				}
			}break;
			case 450:{
				parsx_insert_token(KUnit);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Pattern*, alloc(PatternPrim)(_parsx_1.where, PatternPrim::Unit));
				}
			}break;
			case 451:{
				{
					parsx_token_type _parsx_2 = parsx_pop_value(parsx_token_type);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(StringRef, sym(_parsx_2));
				}
			}break;
			case 452:{
				parsx_insert_token(KEnd);
			}break;
			case 453:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Return, alloc(ExprUnit)(_parsx_1.where)));
				}
			}break;
			case 454:{
			}break;
			case 455:{
				{
					parsx_push_value(List<Import>, List<Import>());
				}
				{
					parsx_push_value(List<TopLevel>, List<TopLevel>());
				}
				parsx_insert_token(EndOfFile);
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<TopLevel> _parsx_2 = parsx_pop_value(List<TopLevel>);
					List<Import> _parsx_1 = parsx_pop_value(List<Import>);
					parsx_push_value(Module*, alloc(Module)(_parsx_1,_parsx_2));
				}
			}break;
			case 456:{
				{
					Import* _parsx_2 = parsx_pop_value(Import*);
					List<Import> _parsx_1 = parsx_pop_value(List<Import>);
					parsx_push_value(List<Import>, _parsx_1.append(_parsx_2));
				}
			}break;
			case 457:{
				{
					Pattern* _parsx_2 = parsx_pop_value(Pattern*);
					EnumConstructorNumber _parsx_1 = parsx_pop_value(EnumConstructorNumber);
					parsx_push_value(Pattern*, alloc(PatternEnum)(_parsx_1.where, _parsx_1, _parsx_2));
				}
			}break;
			case 458:{
				parsx_insert_token(OMult);
				parsx_insert_token(OVBar);
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(int, 1);
				}
				{
					int _parsx_2 = parsx_pop_value(int);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(EnumConstructorNumber, EnumConstructorNumber(to_here(_parsx_1.where.from()), 0, _parsx_2));
				}
			}break;
			case 459:{
				{
					int _parsx_2 = parsx_pop_value(int);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(EnumConstructorNumber, EnumConstructorNumber(to_here(_parsx_1.where.from()), 0, _parsx_2));
				}
			}break;
			case 460:{
				{
					parsx_token_type _parsx_3 = parsx_pop_value(parsx_token_type);
					List<TopLevel> _parsx_2 = parsx_pop_value(List<TopLevel>);
					List<Import> _parsx_1 = parsx_pop_value(List<Import>);
					parsx_push_value(Module*, alloc(Module)(_parsx_1,_parsx_2));
				}
			}break;
			case 461:{
				{
					parsx_push_value(List<TopLevel>, List<TopLevel>());
				}
			}break;
			case 462:{
			}break;
			case 463:{
				parsx_insert_token(EndOfFile);
			}break;
			case 464:{
				{
					TopLevel* _parsx_2 = parsx_pop_value(TopLevel*);
					List<TopLevel> _parsx_1 = parsx_pop_value(List<TopLevel>);
					parsx_push_value(List<TopLevel>, _parsx_1.append(_parsx_2));
				}
			}break;
			case 465:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtEval)(_parsx_1.where, StmtEval::Return, alloc(ExprUnit)(_parsx_1.where)));
				}
			}break;
			case 466:{
			}break;
			case 467:{
				{
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Type*, alloc(TypePrim)(_parsx_1.where, TypePrim::Float));
				}
			}break;
			case 468:{
				{
					parsx_push_value(List<ConstructorStringPart>, nullptr);
				}
				{
					List<ConstructorStringPart> _parsx_2 = parsx_pop_value(List<ConstructorStringPart>);
					parsx_token_type _parsx_1 = parsx_pop_value(parsx_token_type);
					parsx_push_value(Stmt*, alloc(StmtConstructPass)(_parsx_1.where, _parsx_2));
				}
			}break;
			case 469:{
			}break;
			case 470:{
			}break;
			case 471:{
			}break;
		}
	parsx_sync_func_end()
	const parsx_expect_type parsx_expect_table[] = {
		parsx_expect_token(OAssign), 
		parsx_expect_token(OGE), parsx_expect_token(KAnd), parsx_expect_token(OEQ), parsx_expect_token(OConcat), parsx_expect_token(OLT), parsx_expect_token(KOr), parsx_expect_token(ONE), parsx_expect_token(OGT), parsx_expect_token(OLE), parsx_expect_token(OColon), 
		parsx_expect_token(KOr), parsx_expect_token(KAnd), parsx_expect_token(OColon), 
		parsx_expect_token(KElseIf), parsx_expect_token(KElse), 
		parsx_expect_token(OLParen), parsx_expect_token(OPeriod), 
		parsx_expect_token(KCase), 
		parsx_expect_token(KIf), parsx_expect_token(KThen), 
		parsx_expect_name(NonTerminal.Expression), parsx_expect_token(KFor), parsx_expect_token(KWhile), parsx_expect_token(KMatch), parsx_expect_token(KDo), parsx_expect_token(KRepeat), parsx_expect_token(KIf), parsx_expect_token(KLet), parsx_expect_token(KConstruct), parsx_expect_token(KReturn), parsx_expect_token(KEval), parsx_expect_token(KVar), parsx_expect_token(KRaise), 
		parsx_expect_name(NonTerminal.Expression), 
		parsx_expect_token(OVBar), 
		parsx_expect_token(OMinus), parsx_expect_token(OMult), parsx_expect_token(OGT), parsx_expect_token(OConcat), parsx_expect_token(ODiv), parsx_expect_token(KOr), parsx_expect_token(ORem), parsx_expect_token(OLT), parsx_expect_token(OLE), parsx_expect_token(OGE), parsx_expect_token(OEQ), parsx_expect_token(OColon), parsx_expect_token(KAnd), parsx_expect_token(ONE), parsx_expect_token(OPlus), 
		parsx_expect_token(Identifier), parsx_expect_token(OPeriod), 
		parsx_expect_token(KOr), parsx_expect_token(KAnd), parsx_expect_token(OColon), 
		parsx_expect_name(NonTerminal.Expression), 
		parsx_expect_token(Identifier), 
		parsx_expect_token(KWith), 
		parsx_expect_token(ORem), parsx_expect_token(OMult), parsx_expect_token(ODiv), 
		parsx_expect_name(NonTerminal.Type), 
		parsx_expect_token(OComma), parsx_expect_name(NonTerminal.Expression), 
		parsx_expect_token(OPeriod), 
		parsx_expect_name(NonTerminal.Expression), parsx_expect_token(KFor), parsx_expect_token(OBigArrow), parsx_expect_token(KWhile), parsx_expect_token(KMatch), parsx_expect_token(KDo), parsx_expect_token(KRepeat), parsx_expect_token(KIf), parsx_expect_token(KLet), parsx_expect_token(KConstruct), parsx_expect_token(KEnd), parsx_expect_token(KReturn), parsx_expect_token(KEval), parsx_expect_token(KVar), parsx_expect_token(KRaise), 
		parsx_expect_name(NonTerminal.Type), 
		parsx_expect_name(NonTerminal.Type), parsx_expect_token(Identifier), 
		parsx_expect_token(OMinus), parsx_expect_token(KAnd), parsx_expect_token(OConcat), parsx_expect_token(OLT), parsx_expect_token(KOr), parsx_expect_token(OGT), parsx_expect_token(OLE), parsx_expect_token(OGE), parsx_expect_token(OEQ), parsx_expect_token(OColon), parsx_expect_token(ONE), parsx_expect_token(OPlus), 
		parsx_expect_token(Identifier), parsx_expect_name(NonTerminal.Type), 
		parsx_expect_token(Identifier), 
		parsx_expect_name(NonTerminal.Type), 
		parsx_expect_token(OPeriod), 
		parsx_expect_token(OColon), 
		parsx_expect_token(OLParen), 
		parsx_expect_token(ORParen), 
		parsx_expect_token(ORBrace), 
		parsx_expect_token(OGT), 
		parsx_expect_token(KCase), 
		parsx_expect_token(OMult), 
		parsx_expect_token(OArrow), 
		parsx_expect_token(OVBar), 
		parsx_expect_token(OComma), 
		parsx_expect_token(OAssign), 
		parsx_expect_token(OQuote), 
		parsx_expect_token(Identifier), 
		parsx_expect_token(StringLiteral), 
		parsx_expect_token(OMinus), parsx_expect_token(OMult), parsx_expect_token(OGT), parsx_expect_token(OConcat), parsx_expect_token(ODiv), parsx_expect_token(KOr), parsx_expect_token(ORem), parsx_expect_token(OLT), parsx_expect_token(OGE), parsx_expect_token(OLE), parsx_expect_token(OPeriod), parsx_expect_token(OEQ), parsx_expect_token(OColon), parsx_expect_token(ONE), parsx_expect_token(KAnd), parsx_expect_token(OLParen), parsx_expect_token(OPlus), 
		parsx_expect_token(OMinus), parsx_expect_token(OPeriod), parsx_expect_token(OMult), parsx_expect_token(OConcat), parsx_expect_token(ODiv), parsx_expect_token(OLParen), parsx_expect_token(ORem), parsx_expect_token(OPlus), 
		parsx_expect_token(KElseIf), parsx_expect_token(KElse), 
		parsx_expect_token(OVBar), 
		parsx_expect_token(OMinus), parsx_expect_token(OPlus), parsx_expect_token(OConcat), 
		parsx_expect_token(OArrow), parsx_expect_token(OPeriod), parsx_expect_token(OVBar), parsx_expect_token(OColon), parsx_expect_token(Identifier), parsx_expect_token(OQuestion), 
		parsx_expect_token(KElseIf), parsx_expect_token(KElse), 
		parsx_expect_token(Identifier), 
		parsx_expect_token(OComma), 
		parsx_expect_token(Identifier), parsx_expect_token(OSemicolon), 
		parsx_expect_name(NonTerminal.Pattern), 
		parsx_expect_token(Identifier), parsx_expect_token(OLT), 
		parsx_expect_token(KIf), parsx_expect_token(KThen), 
		parsx_expect_token(Identifier), parsx_expect_token(OLT), 
		parsx_expect_token(Identifier), parsx_expect_token(OLT), 
		parsx_expect_token(Identifier), parsx_expect_token(OLT), 
		parsx_expect_token(Identifier), parsx_expect_token(OSemicolon), 
		parsx_expect_token(OComma), parsx_expect_token(ORParen), 
		parsx_expect_token(OLParen), parsx_expect_token(OPeriod), 
		parsx_expect_token(Identifier), parsx_expect_token(ONE), parsx_expect_token(OLT), 
		parsx_expect_token(OMinus), parsx_expect_token(OMult), parsx_expect_token(OGT), parsx_expect_token(OConcat), parsx_expect_token(ODiv), parsx_expect_token(KOr), parsx_expect_token(ORem), parsx_expect_token(OLT), parsx_expect_token(OGE), parsx_expect_token(OLE), parsx_expect_token(OPeriod), parsx_expect_token(OEQ), parsx_expect_token(OColon), parsx_expect_token(ONE), parsx_expect_token(KAnd), parsx_expect_token(OLParen), parsx_expect_token(OPlus), 
		parsx_expect_token(Identifier), parsx_expect_token(OLT), 
		parsx_expect_token(Identifier), parsx_expect_token(OLT), 
		parsx_expect_token(Identifier), 
		parsx_expect_name(NonTerminal.Expression), 
		parsx_expect_token(Identifier), parsx_expect_token(OLT), 
		parsx_expect_token(OLParen), 
		parsx_expect_name(NonTerminal.Pattern), 
		parsx_expect_token(KEnum), parsx_expect_token(KStruct), parsx_expect_token(KInterface), parsx_expect_token(KClass), parsx_expect_token(KFunction), parsx_expect_token(KGlobal), 
		parsx_expect_token(OLParen), 
		parsx_expect_token(KImport), 
		parsx_expect_token(KImplements), 
		parsx_expect_token(KWith), 
		parsx_expect_token(Identifier), 
		parsx_expect_token(Identifier), 
		parsx_expect_token(Identifier), 
		parsx_expect_token(KOr), parsx_expect_token(OColon), 
		parsx_expect_name(NonTerminal.Type), 
		parsx_expect_token(OColon), 
		parsx_expect_token(OAssign), parsx_expect_token(OSemicolon), parsx_expect_token(OColon), 
		parsx_expect_token(OLParen), parsx_expect_token(OPeriod), 
		parsx_expect_token(OGE), parsx_expect_token(KAnd), parsx_expect_token(OEQ), parsx_expect_token(OLT), parsx_expect_token(ONE), parsx_expect_token(OGT), parsx_expect_token(OLE), 
		parsx_expect_token(OLParen), 
		parsx_expect_token(OVBar), 
		parsx_expect_name(NonTerminal.Expression), parsx_expect_token(OBigArrow), parsx_expect_token(KMatch), parsx_expect_token(KRepeat), parsx_expect_token(KIf), parsx_expect_token(KConstruct), parsx_expect_token(KImport), parsx_expect_token(KEnd), parsx_expect_token(KFor), parsx_expect_token(KWhile), parsx_expect_token(KDo), parsx_expect_token(KVar), parsx_expect_token(KLet), parsx_expect_token(KReturn), parsx_expect_token(KEval), parsx_expect_token(KRaise), 
		parsx_expect_name(NonTerminal.Expression), 
		parsx_expect_token(OColon), 
		parsx_expect_token(OLParen), parsx_expect_token(OPeriod), 
		parsx_expect_name(NonTerminal.Expression), 
		parsx_expect_token(OComma), 
		parsx_expect_token(OPeriod), 
		parsx_expect_token(OPeriod), 
		parsx_expect_token(OMinus), parsx_expect_token(KAnd), parsx_expect_token(OConcat), parsx_expect_token(OLT), parsx_expect_token(KOr), parsx_expect_token(OGT), parsx_expect_token(OLE), parsx_expect_token(OGE), parsx_expect_token(OEQ), parsx_expect_token(OColon), parsx_expect_token(ONE), parsx_expect_token(OPlus), 
		parsx_expect_name(NonTerminal.Expression), 
		parsx_expect_token(KField), 
		parsx_expect_token(OComma), 
		parsx_expect_name(NonTerminal.Expression), 
		parsx_expect_token(KCase), 
		parsx_expect_name(NonTerminal.Expression), 
		parsx_expect_token(OPeriod), 
		parsx_expect_token(OVBar), 
		parsx_expect_token(OComma), 
		parsx_expect_token(OComma), 
		parsx_expect_token(KOr), parsx_expect_token(OColon), 
		parsx_expect_token(OMinus), parsx_expect_token(OPlus), 
		parsx_expect_token(OComma), parsx_expect_name(NonTerminal.Expression), 
		parsx_expect_token(OMinus), parsx_expect_token(OMult), parsx_expect_token(OGT), parsx_expect_token(OConcat), parsx_expect_token(ODiv), parsx_expect_token(KOr), parsx_expect_token(ORem), parsx_expect_token(OLT), parsx_expect_token(OGE), parsx_expect_token(OLE), parsx_expect_token(OPeriod), parsx_expect_token(OEQ), parsx_expect_token(OColon), parsx_expect_token(ONE), parsx_expect_token(KAnd), parsx_expect_token(OLParen), parsx_expect_token(OPlus), 
		parsx_expect_token(OVBar), 
		parsx_expect_token(OLParen), parsx_expect_token(OPeriod), parsx_expect_token(OMult), parsx_expect_token(ORem), parsx_expect_token(ODiv), 
		parsx_expect_token(Identifier), 
		parsx_expect_name(NonTerminal.Pattern), parsx_expect_token(OPeriod), 
		parsx_expect_token(KConstructor), parsx_expect_token(KField), parsx_expect_token(KMethod), parsx_expect_token(KAbstract), parsx_expect_token(KOverride), 
		parsx_expect_token(OGE), parsx_expect_token(KAnd), parsx_expect_token(OEQ), parsx_expect_token(OConcat), parsx_expect_token(OLT), parsx_expect_token(KOr), parsx_expect_token(ONE), parsx_expect_token(OGT), parsx_expect_token(OLE), parsx_expect_token(OColon), 
		parsx_expect_token(KCase), 
		parsx_expect_token(OLParen), parsx_expect_token(OPeriod), 
		parsx_expect_name(NonTerminal.Expression), parsx_expect_token(KFor), parsx_expect_token(OBigArrow), parsx_expect_token(KWhile), parsx_expect_token(KMatch), parsx_expect_token(KDo), parsx_expect_token(KRepeat), parsx_expect_token(KIf), parsx_expect_token(KLet), parsx_expect_token(KConstruct), parsx_expect_token(KEnd), parsx_expect_token(KReturn), parsx_expect_token(KImport), parsx_expect_token(KEval), parsx_expect_token(KVar), parsx_expect_token(KRaise), 
		parsx_expect_token(OLParen), parsx_expect_token(OPeriod), parsx_expect_token(OMult), parsx_expect_token(ORem), parsx_expect_token(ODiv), 
		parsx_expect_token(OComma), 
		parsx_expect_token(ORem), parsx_expect_token(OMult), parsx_expect_token(ODiv), 
		parsx_expect_token(OComma), 
		parsx_expect_token(KCase), 
		parsx_expect_token(OMinus), parsx_expect_token(OMult), parsx_expect_token(OGT), parsx_expect_token(OConcat), parsx_expect_token(ODiv), parsx_expect_token(KOr), parsx_expect_token(ORem), parsx_expect_token(OLT), parsx_expect_token(OLE), parsx_expect_token(OGE), parsx_expect_token(OEQ), parsx_expect_token(OColon), parsx_expect_token(KAnd), parsx_expect_token(ONE), parsx_expect_token(OPlus), 
		parsx_expect_token(KCase), 
		parsx_expect_name(NonTerminal.Type), 
		parsx_expect_token(OConcat), 
		parsx_expect_token(OMinus), parsx_expect_token(OPeriod), parsx_expect_token(OMult), parsx_expect_token(ODiv), parsx_expect_token(OLParen), parsx_expect_token(ORem), parsx_expect_token(OPlus), 
		parsx_expect_name(NonTerminal.Pattern), 
		parsx_expect_name(NonTerminal.Type), parsx_expect_token(ORParen), 
		parsx_expect_token(OGE), parsx_expect_token(KAnd), parsx_expect_token(OEQ), parsx_expect_token(OConcat), parsx_expect_token(OLT), parsx_expect_token(KOr), parsx_expect_token(ONE), parsx_expect_token(OGT), parsx_expect_token(OLE), parsx_expect_token(OColon), 
		parsx_expect_token(OArrow), 
		parsx_expect_token(OMinus), parsx_expect_token(ORem), parsx_expect_token(OMult), parsx_expect_token(OPlus), parsx_expect_token(ODiv), 
		parsx_expect_token(KWith), 
		parsx_expect_token(KImplements), 
		parsx_expect_token(KField), parsx_expect_token(KMethod), parsx_expect_token(KAbstract), parsx_expect_token(KConstructor), parsx_expect_token(KOverride), 
		parsx_expect_token(KField), 
		parsx_expect_token(OAssign), parsx_expect_token(OSemicolon), parsx_expect_token(OColon), 
		parsx_expect_token(KImport), 
		parsx_expect_token(OLParen), 
		parsx_expect_token(OVBar), 
		parsx_expect_token(Identifier), parsx_expect_token(KWith), parsx_expect_token(OLParen), 
		parsx_expect_token(KThen), 
		parsx_expect_token(Identifier), parsx_expect_token(OPeriod), parsx_expect_token(KWith), 
		parsx_expect_token(KDo), 
		parsx_expect_token(KIn), 
		parsx_expect_name(NonTerminal.Expression), 
		parsx_expect_token(KMethod), 
		parsx_expect_token(KElseIf), parsx_expect_token(KEnd), parsx_expect_token(KElse), 
		parsx_expect_token(KUntil), 
		parsx_expect_token(OPeriod), 
		parsx_expect_token(OMinus), parsx_expect_token(OMult), parsx_expect_token(OGT), parsx_expect_token(OConcat), parsx_expect_token(ODiv), parsx_expect_token(KOr), parsx_expect_token(ORem), parsx_expect_token(OLT), parsx_expect_token(OLE), parsx_expect_token(OGE), parsx_expect_token(OEQ), parsx_expect_token(OColon), parsx_expect_token(KAnd), parsx_expect_token(ONE), parsx_expect_token(OPlus), 
		parsx_expect_token(OArrow), parsx_expect_token(OQuestion), 
		parsx_expect_token(OAssign), 
		parsx_expect_token(KEnum), parsx_expect_token(KStruct), parsx_expect_token(KInterface), parsx_expect_token(KClass), parsx_expect_token(KFunction), parsx_expect_token(KGlobal), 
		parsx_expect_token(OComma), 
		parsx_expect_token(OComma), parsx_expect_token(OAssign), 
		parsx_expect_token(OMinus), parsx_expect_token(OMult), parsx_expect_token(OConcat), parsx_expect_token(ODiv), parsx_expect_token(ORem), parsx_expect_token(OPlus), 
		parsx_expect_name(NonTerminal.Type), 
		parsx_expect_token(KWith), 
		parsx_expect_token(KExtends), 
		parsx_expect_token(KMethod), 
		parsx_expect_token(OLParen), parsx_expect_token(OPeriod), 
		parsx_expect_token(KAnd), 
		parsx_expect_token(KExtends), 
		parsx_expect_name(NonTerminal.Expression), parsx_expect_token(KFor), parsx_expect_token(KWhile), parsx_expect_token(KMatch), parsx_expect_token(KDo), parsx_expect_token(KRepeat), parsx_expect_token(OSemicolon), parsx_expect_token(KIf), parsx_expect_token(KLet), parsx_expect_token(KConstruct), parsx_expect_token(KReturn), parsx_expect_token(KEval), parsx_expect_token(KVar), parsx_expect_token(KRaise), 
		parsx_expect_token(OAssign), 
		parsx_expect_token(KExtends), 
		parsx_expect_token(KOr), parsx_expect_token(OColon), 
		parsx_expect_token(OArrow), parsx_expect_token(OVBar), parsx_expect_token(OQuestion), 
		parsx_expect_token(OComma), parsx_expect_token(OAssign), 
		parsx_expect_token(OLParen), parsx_expect_token(OPeriod), 
		parsx_expect_token(KField), parsx_expect_token(KMethod), parsx_expect_token(KAbstract), parsx_expect_token(KConstructor), parsx_expect_token(KOverride), 
		parsx_expect_token(OMinus), parsx_expect_token(OPlus), 
		parsx_expect_token(Identifier), 
		parsx_expect_token(OGE), parsx_expect_token(KAnd), parsx_expect_token(OEQ), parsx_expect_token(OColon), parsx_expect_token(OLT), parsx_expect_token(KOr), parsx_expect_token(ONE), parsx_expect_token(OGT), parsx_expect_token(OLE), 
		parsx_expect_token(OMinus), parsx_expect_token(KAnd), parsx_expect_token(OConcat), parsx_expect_token(OLT), parsx_expect_token(KOr), parsx_expect_token(OGT), parsx_expect_token(OLE), parsx_expect_token(OGE), parsx_expect_token(OEQ), parsx_expect_token(OColon), parsx_expect_token(ONE), parsx_expect_token(OPlus), 
		parsx_expect_token(KField), 
		parsx_expect_token(Identifier), 
		parsx_expect_name(NonTerminal.Type), 
		parsx_expect_token(KImport), 
		parsx_expect_token(KAs), 
		parsx_expect_name(NonTerminal.Pattern), 
		parsx_expect_token(KEnd), 
		parsx_expect_name(NonTerminal.Expression), 
		parsx_expect_token(OComma), 
		parsx_expect_token(KStruct), parsx_expect_token(KInterface), parsx_expect_token(KClass), parsx_expect_token(KEnum), parsx_expect_token(KImport), parsx_expect_token(KFunction), parsx_expect_token(EndOfFile), parsx_expect_token(KGlobal), 
		parsx_expect_token(OMult), parsx_expect_token(OVBar), 
		parsx_expect_token(KEnum), parsx_expect_token(KStruct), parsx_expect_token(KInterface), parsx_expect_token(KClass), parsx_expect_token(KFunction), parsx_expect_token(KGlobal), 
		parsx_expect_token(KOr), parsx_expect_token(KAnd), parsx_expect_token(OColon), 
		parsx_expect_token(EndOfFile), 
		parsx_expect_name(NonTerminal.Expression), 
		parsx_expect_token(KAs), 
		parsx_expect_token(Identifier), parsx_expect_token(OPeriod), parsx_expect_token(KWith), 
		parsx_expect_token(OGE), parsx_expect_token(OEQ), parsx_expect_token(OLT), parsx_expect_token(ONE), parsx_expect_token(OGT), parsx_expect_token(OLE), 
		parsx_expect_token(OQuestion), 
		parsx_expect_token(OConcat), 
	};
	const unsigned int parsx_expect_table_index[] = {
		0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 11, 3, 0, 0, 0, 0, 0, 0, 14, 2, 0, 0, 16, 2, 0, 0, 18, 1, 0, 0, 0, 0, 19, 2, 21, 13, 0, 0, 0, 0, 34, 1, 0, 0, 35, 1, 0, 0, 0, 0, 0, 0, 0, 0, 36, 15, 0, 0, 0, 0, 0, 0, 51, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 53, 3, 0, 0, 0, 0, 56, 1, 57, 1, 58, 1, 0, 0, 0, 0, 59, 3, 0, 0, 0, 0, 62, 1, 0, 0, 63, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65, 1, 66, 15, 81, 1, 82, 2, 0, 0, 0, 0, 84, 12, 0, 0, 96, 2, 0, 0, 0, 0, 98, 1, 0, 0, 0, 0, 99, 1, 100, 1, 101, 1, 102, 1, 103, 1, 104, 1, 105, 1, 0, 0, 0, 0, 106, 1, 107, 1, 108, 1, 109, 1, 110, 1, 111, 1, 112, 1, 0, 0, 113, 1, 114, 1, 115, 17, 0, 0, 132, 8, 0, 0, 0, 0, 140, 2, 142, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 143, 3, 0, 0, 0, 0, 0, 0, 146, 6, 0, 0, 152, 2, 0, 0, 0, 0, 154, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 155, 1, 156, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 158, 1, 0, 0, 0, 0, 159, 2, 0, 0, 161, 2, 163, 2, 0, 0, 165, 2, 0, 0, 0, 0, 167, 2, 0, 0, 169, 2, 171, 2, 0, 0, 0, 0, 173, 2, 175, 3, 178, 17, 0, 0, 0, 0, 195, 2, 0, 0, 0, 0, 0, 0, 0, 0, 197, 2, 0, 0, 0, 0, 0, 0, 0, 0, 199, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 1, 0, 0, 0, 0, 0, 0, 201, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 203, 1, 0, 0, 0, 0, 0, 0, 204, 1, 0, 0, 0, 0, 205, 6, 0, 0, 211, 1, 0, 0, 212, 1, 213, 1, 0, 0, 0, 0, 0, 0, 214, 1, 0, 0, 215, 1, 0, 0, 0, 0, 216, 1, 0, 0, 0, 0, 0, 0, 217, 1, 0, 0, 0, 0, 0, 0, 0, 0, 218, 2, 0, 0, 220, 1, 0, 0, 221, 1, 0, 0, 0, 0, 0, 0, 222, 3, 0, 0, 0, 0, 225, 2, 227, 7, 234, 1, 0, 0, 235, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 236, 16, 0, 0, 252, 1, 253, 1, 254, 2, 256, 1, 257, 1, 0, 0, 258, 1, 259, 1, 0, 0, 260, 12, 272, 1, 273, 1, 274, 1, 0, 0, 0, 0, 275, 1, 276, 1, 0, 0, 277, 1, 0, 0, 278, 1, 0, 0, 279, 1, 0, 0, 280, 1, 0, 0, 281, 1, 282, 2, 284, 2, 0, 0, 0, 0, 0, 0, 286, 2, 0, 0, 288, 17, 305, 1, 306, 5, 0, 0, 311, 1, 312, 2, 0, 0, 0, 0, 314, 5, 319, 10, 0, 0, 329, 1, 330, 2, 332, 16, 348, 5, 0, 0, 0, 0, 0, 0, 353, 1, 0, 0, 0, 0, 354, 3, 0, 0, 357, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 358, 1, 0, 0, 359, 15, 0, 0, 374, 1, 0, 0, 0, 0, 375, 1, 376, 1, 0, 0, 0, 0, 0, 0, 377, 7, 384, 1, 0, 0, 0, 0, 385, 2, 0, 0, 387, 10, 397, 1, 398, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 403, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 404, 1, 0, 0, 405, 5, 410, 1, 0, 0, 0, 0, 0, 0, 411, 3, 0, 0, 0, 0, 0, 0, 414, 1, 0, 0, 0, 0, 415, 1, 0, 0, 416, 1, 417, 3, 420, 1, 0, 0, 421, 3, 0, 0, 0, 0, 0, 0, 424, 1, 425, 1, 426, 1, 427, 1, 0, 0, 0, 0, 428, 3, 0, 0, 0, 0, 0, 0, 431, 1, 0, 0, 432, 1, 0, 0, 433, 15, 0, 0, 448, 2, 0, 0, 0, 0, 450, 1, 0, 0, 0, 0, 451, 6, 457, 1, 458, 2, 0, 0, 460, 6, 0, 0, 466, 1, 467, 1, 0, 0, 468, 1, 0, 0, 469, 1, 0, 0, 0, 0, 470, 2, 472, 1, 473, 1, 0, 0, 474, 14, 0, 0, 0, 0, 488, 1, 489, 1, 0, 0, 0, 0, 490, 2, 492, 3, 495, 2, 0, 0, 497, 2, 0, 0, 499, 5, 0, 0, 504, 2, 0, 0, 0, 0, 0, 0, 506, 1, 507, 9, 516, 12, 0, 0, 0, 0, 0, 0, 0, 0, 528, 1, 0, 0, 0, 0, 0, 0, 0, 0, 529, 1, 530, 1, 0, 0, 531, 1, 0, 0, 532, 1, 533, 1, 0, 0, 534, 1, 535, 1, 536, 1, 537, 8, 0, 0, 0, 0, 545, 2, 0, 0, 0, 0, 547, 6, 553, 3, 556, 1, 0, 0, 557, 1, 558, 1, 0, 0, 559, 3, 562, 6, 568, 1, 569, 1, 
	};
	parsx_expected_func_begin()
		const unsigned int* parsx_expect_index = parsx_expect_table_index + parsx_expect_state * 2;
		const parsx_expect_type *parsx_expects = parsx_expect_table + parsx_expect_index[0];
		unsigned int parsx_expect_count = parsx_expect_index[1];
		while ( parsx_expect_count-- ) parsx_expect(*(parsx_expects++));
	parsx_expected_func_end()
	parsx_sync_mask_table_begin()
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OAssign))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(10,parsx_token(KAnd),parsx_token(OConcat),parsx_token(OLT),parsx_token(KOr),parsx_token(OGT),parsx_token(OLE),parsx_token(OGE),parsx_token(OEQ),parsx_token(OColon),parsx_token(ONE))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(3,parsx_token(KOr),parsx_token(KAnd),parsx_token(OColon))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(KElseIf),parsx_token(KElse))
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(OLParen),parsx_token(OPeriod))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KCase))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(KIf),parsx_token(KThen))
		parsx_sync_mask(25,parsx_token(KNot),parsx_token(KIf),parsx_token(KConstruct),parsx_token(OLParen),parsx_token(OLBrace),parsx_token(KFor),parsx_token(KWhile),parsx_token(KDo),parsx_token(KVar),parsx_token(KLet),parsx_token(KReturn),parsx_token(KEval),parsx_token(KRaise),parsx_token(OMinus),parsx_token(KMatch),parsx_token(KRepeat),parsx_token(KLambda),parsx_token(KNew),parsx_token(KUnit),parsx_token(KNull),parsx_token(Identifier),parsx_token(StringLiteral),parsx_token(NumberLiteral),parsx_token(KTrue),parsx_token(KFalse))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(10,parsx_token(OLBrace),parsx_token(KNull),parsx_token(Identifier),parsx_token(KLambda),parsx_token(StringLiteral),parsx_token(KNew),parsx_token(NumberLiteral),parsx_token(KTrue),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OVBar))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(15,parsx_token(OMinus),parsx_token(OMult),parsx_token(OConcat),parsx_token(ODiv),parsx_token(KOr),parsx_token(ORem),parsx_token(OLT),parsx_token(OLE),parsx_token(OGE),parsx_token(OEQ),parsx_token(OColon),parsx_token(ONE),parsx_token(KAnd),parsx_token(OGT),parsx_token(OPlus))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(Identifier),parsx_token(OPeriod))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(3,parsx_token(KOr),parsx_token(KAnd),parsx_token(OColon))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(15,parsx_token(OLBrace),parsx_token(KMatch),parsx_token(OMinus),parsx_token(KNull),parsx_token(KNot),parsx_token(KIf),parsx_token(Identifier),parsx_token(KLambda),parsx_token(StringLiteral),parsx_token(KNew),parsx_token(KTrue),parsx_token(NumberLiteral),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(1,parsx_token(Identifier))
		parsx_sync_mask(1,parsx_token(KWith))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(3,parsx_token(ORem),parsx_token(OMult),parsx_token(ODiv))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(11,parsx_token(OLBrace),parsx_token(KBool),parsx_token(KInt),parsx_token(KFloat),parsx_token(KDouble),parsx_token(Identifier),parsx_token(KString),parsx_token(KBytes),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KUndef))
		parsx_sync_mask(0)
		parsx_sync_mask(16,parsx_token(OLBrace),parsx_token(KMatch),parsx_token(OMinus),parsx_token(KNull),parsx_token(NumberLiteral),parsx_token(KNot),parsx_token(KIf),parsx_token(Identifier),parsx_token(KLambda),parsx_token(StringLiteral),parsx_token(KNew),parsx_token(KTrue),parsx_token(OComma),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OPeriod))
		parsx_sync_mask(27,parsx_token(OBigArrow),parsx_token(KNot),parsx_token(KIf),parsx_token(KConstruct),parsx_token(OLParen),parsx_token(KEnd),parsx_token(OLBrace),parsx_token(KFor),parsx_token(KWhile),parsx_token(KDo),parsx_token(KVar),parsx_token(KLet),parsx_token(KReturn),parsx_token(KEval),parsx_token(KRaise),parsx_token(OMinus),parsx_token(KMatch),parsx_token(KRepeat),parsx_token(KLambda),parsx_token(KNew),parsx_token(KUnit),parsx_token(KNull),parsx_token(Identifier),parsx_token(StringLiteral),parsx_token(NumberLiteral),parsx_token(KTrue),parsx_token(KFalse))
		parsx_sync_mask(11,parsx_token(OLBrace),parsx_token(KBool),parsx_token(KInt),parsx_token(KFloat),parsx_token(KDouble),parsx_token(Identifier),parsx_token(KString),parsx_token(KBytes),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KUndef))
		parsx_sync_mask(11,parsx_token(OLBrace),parsx_token(KBool),parsx_token(KInt),parsx_token(KFloat),parsx_token(KDouble),parsx_token(Identifier),parsx_token(KString),parsx_token(KBytes),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KUndef))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(12,parsx_token(OMinus),parsx_token(KAnd),parsx_token(OConcat),parsx_token(OLT),parsx_token(KOr),parsx_token(OGT),parsx_token(OLE),parsx_token(OGE),parsx_token(OEQ),parsx_token(OColon),parsx_token(ONE),parsx_token(OPlus))
		parsx_sync_mask(0)
		parsx_sync_mask(11,parsx_token(OLBrace),parsx_token(KBool),parsx_token(KInt),parsx_token(KFloat),parsx_token(KDouble),parsx_token(Identifier),parsx_token(KString),parsx_token(KBytes),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KUndef))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(Identifier))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(11,parsx_token(OLBrace),parsx_token(KBool),parsx_token(KInt),parsx_token(KFloat),parsx_token(KDouble),parsx_token(Identifier),parsx_token(KString),parsx_token(KBytes),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KUndef))
		parsx_sync_mask(1,parsx_token(OPeriod))
		parsx_sync_mask(1,parsx_token(OColon))
		parsx_sync_mask(1,parsx_token(OLParen))
		parsx_sync_mask(1,parsx_token(ORParen))
		parsx_sync_mask(1,parsx_token(ORBrace))
		parsx_sync_mask(1,parsx_token(OGT))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KCase))
		parsx_sync_mask(1,parsx_token(OMult))
		parsx_sync_mask(1,parsx_token(OArrow))
		parsx_sync_mask(1,parsx_token(OVBar))
		parsx_sync_mask(1,parsx_token(OComma))
		parsx_sync_mask(1,parsx_token(OAssign))
		parsx_sync_mask(1,parsx_token(OQuote))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(Identifier))
		parsx_sync_mask(1,parsx_token(StringLiteral))
		parsx_sync_mask(17,parsx_token(OMinus),parsx_token(OMult),parsx_token(OGT),parsx_token(OConcat),parsx_token(ODiv),parsx_token(KOr),parsx_token(ORem),parsx_token(OLT),parsx_token(OGE),parsx_token(OLE),parsx_token(OPeriod),parsx_token(OEQ),parsx_token(OColon),parsx_token(ONE),parsx_token(KAnd),parsx_token(OLParen),parsx_token(OPlus))
		parsx_sync_mask(0)
		parsx_sync_mask(8,parsx_token(OMinus),parsx_token(OMult),parsx_token(OConcat),parsx_token(ODiv),parsx_token(ORem),parsx_token(OPeriod),parsx_token(OLParen),parsx_token(OPlus))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(KElseIf),parsx_token(KElse))
		parsx_sync_mask(1,parsx_token(OVBar))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(3,parsx_token(OMinus),parsx_token(OPlus),parsx_token(OConcat))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(6,parsx_token(OArrow),parsx_token(Identifier),parsx_token(OPeriod),parsx_token(OVBar),parsx_token(OColon),parsx_token(OQuestion))
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(KElseIf),parsx_token(KElse))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(Identifier))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OComma))
		parsx_sync_mask(2,parsx_token(Identifier),parsx_token(OSemicolon))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(12,parsx_token(OLBrace),parsx_token(KNull),parsx_token(OMult),parsx_token(Identifier),parsx_token(OQuote),parsx_token(StringLiteral),parsx_token(OVBar),parsx_token(KTrue),parsx_token(NumberLiteral),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(Identifier),parsx_token(OLT))
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(KIf),parsx_token(KThen))
		parsx_sync_mask(2,parsx_token(Identifier),parsx_token(OLT))
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(Identifier),parsx_token(OLT))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(Identifier),parsx_token(OLT))
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(Identifier),parsx_token(OSemicolon))
		parsx_sync_mask(2,parsx_token(OComma),parsx_token(ORParen))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(OLParen),parsx_token(OPeriod))
		parsx_sync_mask(3,parsx_token(Identifier),parsx_token(ONE),parsx_token(OLT))
		parsx_sync_mask(17,parsx_token(OMinus),parsx_token(OMult),parsx_token(OGT),parsx_token(OConcat),parsx_token(ODiv),parsx_token(KOr),parsx_token(ORem),parsx_token(OLT),parsx_token(OGE),parsx_token(OLE),parsx_token(OPeriod),parsx_token(OEQ),parsx_token(OColon),parsx_token(ONE),parsx_token(KAnd),parsx_token(OLParen),parsx_token(OPlus))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(Identifier),parsx_token(OLT))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(Identifier),parsx_token(OLT))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(Identifier))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(13,parsx_token(OLBrace),parsx_token(OMinus),parsx_token(KNull),parsx_token(KNot),parsx_token(Identifier),parsx_token(KLambda),parsx_token(StringLiteral),parsx_token(KNew),parsx_token(KTrue),parsx_token(NumberLiteral),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(Identifier),parsx_token(OLT))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OLParen))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(11,parsx_token(OLBrace),parsx_token(KNull),parsx_token(OMult),parsx_token(Identifier),parsx_token(OQuote),parsx_token(StringLiteral),parsx_token(KTrue),parsx_token(NumberLiteral),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(6,parsx_token(KStruct),parsx_token(KInterface),parsx_token(KClass),parsx_token(KEnum),parsx_token(KFunction),parsx_token(KGlobal))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OLParen))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KImport))
		parsx_sync_mask(1,parsx_token(KImplements))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KWith))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(Identifier))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(Identifier))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(Identifier))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(KOr),parsx_token(OColon))
		parsx_sync_mask(0)
		parsx_sync_mask(11,parsx_token(OLBrace),parsx_token(KBool),parsx_token(KInt),parsx_token(KFloat),parsx_token(KDouble),parsx_token(Identifier),parsx_token(KString),parsx_token(KBytes),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KUndef))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OColon))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(3,parsx_token(OAssign),parsx_token(OSemicolon),parsx_token(OColon))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(OLParen),parsx_token(OPeriod))
		parsx_sync_mask(7,parsx_token(KAnd),parsx_token(OLT),parsx_token(OGT),parsx_token(OLE),parsx_token(OGE),parsx_token(OEQ),parsx_token(ONE))
		parsx_sync_mask(1,parsx_token(OLParen))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OVBar))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(28,parsx_token(OBigArrow),parsx_token(KNot),parsx_token(KIf),parsx_token(KConstruct),parsx_token(OLParen),parsx_token(KEnd),parsx_token(OLBrace),parsx_token(KFor),parsx_token(KWhile),parsx_token(KDo),parsx_token(KVar),parsx_token(KLet),parsx_token(KReturn),parsx_token(KEval),parsx_token(KRaise),parsx_token(OMinus),parsx_token(KMatch),parsx_token(KRepeat),parsx_token(KLambda),parsx_token(KNew),parsx_token(KImport),parsx_token(KUnit),parsx_token(KNull),parsx_token(Identifier),parsx_token(StringLiteral),parsx_token(NumberLiteral),parsx_token(KTrue),parsx_token(KFalse))
		parsx_sync_mask(0)
		parsx_sync_mask(15,parsx_token(OLBrace),parsx_token(KMatch),parsx_token(OMinus),parsx_token(KNull),parsx_token(KNot),parsx_token(KIf),parsx_token(Identifier),parsx_token(KLambda),parsx_token(StringLiteral),parsx_token(KNew),parsx_token(KTrue),parsx_token(NumberLiteral),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(1,parsx_token(OColon))
		parsx_sync_mask(2,parsx_token(OLParen),parsx_token(OPeriod))
		parsx_sync_mask(15,parsx_token(OLBrace),parsx_token(KMatch),parsx_token(OMinus),parsx_token(KNull),parsx_token(KNot),parsx_token(KIf),parsx_token(Identifier),parsx_token(KLambda),parsx_token(StringLiteral),parsx_token(KNew),parsx_token(KTrue),parsx_token(NumberLiteral),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(1,parsx_token(OComma))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OPeriod))
		parsx_sync_mask(1,parsx_token(OPeriod))
		parsx_sync_mask(0)
		parsx_sync_mask(12,parsx_token(OMinus),parsx_token(KAnd),parsx_token(OConcat),parsx_token(OLT),parsx_token(KOr),parsx_token(OGT),parsx_token(OLE),parsx_token(OGE),parsx_token(OEQ),parsx_token(OColon),parsx_token(ONE),parsx_token(OPlus))
		parsx_sync_mask(15,parsx_token(OLBrace),parsx_token(KMatch),parsx_token(OMinus),parsx_token(KNull),parsx_token(KNot),parsx_token(KIf),parsx_token(Identifier),parsx_token(KLambda),parsx_token(StringLiteral),parsx_token(KNew),parsx_token(KTrue),parsx_token(NumberLiteral),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(1,parsx_token(KField))
		parsx_sync_mask(1,parsx_token(OComma))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(15,parsx_token(OLBrace),parsx_token(KMatch),parsx_token(OMinus),parsx_token(KNull),parsx_token(KNot),parsx_token(KIf),parsx_token(Identifier),parsx_token(KLambda),parsx_token(StringLiteral),parsx_token(KNew),parsx_token(KTrue),parsx_token(NumberLiteral),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(1,parsx_token(KCase))
		parsx_sync_mask(0)
		parsx_sync_mask(15,parsx_token(OLBrace),parsx_token(KMatch),parsx_token(OMinus),parsx_token(KNull),parsx_token(KNot),parsx_token(KIf),parsx_token(Identifier),parsx_token(KLambda),parsx_token(StringLiteral),parsx_token(KNew),parsx_token(KTrue),parsx_token(NumberLiteral),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OPeriod))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OVBar))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OComma))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OComma))
		parsx_sync_mask(2,parsx_token(KOr),parsx_token(OColon))
		parsx_sync_mask(2,parsx_token(OMinus),parsx_token(OPlus))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(16,parsx_token(OLBrace),parsx_token(KMatch),parsx_token(OMinus),parsx_token(KNull),parsx_token(NumberLiteral),parsx_token(KNot),parsx_token(KIf),parsx_token(Identifier),parsx_token(KLambda),parsx_token(StringLiteral),parsx_token(KNew),parsx_token(KTrue),parsx_token(OComma),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(0)
		parsx_sync_mask(17,parsx_token(OMinus),parsx_token(OMult),parsx_token(OGT),parsx_token(OConcat),parsx_token(ODiv),parsx_token(KOr),parsx_token(ORem),parsx_token(OLT),parsx_token(OGE),parsx_token(OLE),parsx_token(OPeriod),parsx_token(OEQ),parsx_token(OColon),parsx_token(ONE),parsx_token(KAnd),parsx_token(OLParen),parsx_token(OPlus))
		parsx_sync_mask(1,parsx_token(OVBar))
		parsx_sync_mask(5,parsx_token(OLParen),parsx_token(OPeriod),parsx_token(OMult),parsx_token(ORem),parsx_token(ODiv))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(Identifier))
		parsx_sync_mask(12,parsx_token(OLBrace),parsx_token(KNull),parsx_token(OMult),parsx_token(Identifier),parsx_token(OPeriod),parsx_token(OQuote),parsx_token(StringLiteral),parsx_token(KTrue),parsx_token(NumberLiteral),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(5,parsx_token(KField),parsx_token(KMethod),parsx_token(KAbstract),parsx_token(KConstructor),parsx_token(KOverride))
		parsx_sync_mask(10,parsx_token(KAnd),parsx_token(OConcat),parsx_token(OLT),parsx_token(KOr),parsx_token(OGT),parsx_token(OLE),parsx_token(OGE),parsx_token(OEQ),parsx_token(OColon),parsx_token(ONE))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KCase))
		parsx_sync_mask(2,parsx_token(OLParen),parsx_token(OPeriod))
		parsx_sync_mask(28,parsx_token(OBigArrow),parsx_token(KNot),parsx_token(KIf),parsx_token(KConstruct),parsx_token(OLParen),parsx_token(KEnd),parsx_token(OLBrace),parsx_token(KFor),parsx_token(KWhile),parsx_token(KDo),parsx_token(KVar),parsx_token(KLet),parsx_token(KReturn),parsx_token(KEval),parsx_token(KRaise),parsx_token(OMinus),parsx_token(KMatch),parsx_token(KRepeat),parsx_token(KLambda),parsx_token(KNew),parsx_token(KImport),parsx_token(KUnit),parsx_token(KNull),parsx_token(Identifier),parsx_token(StringLiteral),parsx_token(NumberLiteral),parsx_token(KTrue),parsx_token(KFalse))
		parsx_sync_mask(5,parsx_token(OLParen),parsx_token(OPeriod),parsx_token(OMult),parsx_token(ORem),parsx_token(ODiv))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OComma))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(3,parsx_token(ORem),parsx_token(OMult),parsx_token(ODiv))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OComma))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KCase))
		parsx_sync_mask(0)
		parsx_sync_mask(15,parsx_token(OMinus),parsx_token(OMult),parsx_token(OConcat),parsx_token(ODiv),parsx_token(KOr),parsx_token(ORem),parsx_token(OLT),parsx_token(OLE),parsx_token(OGE),parsx_token(OEQ),parsx_token(OColon),parsx_token(ONE),parsx_token(KAnd),parsx_token(OGT),parsx_token(OPlus))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KCase))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(11,parsx_token(OLBrace),parsx_token(KBool),parsx_token(KInt),parsx_token(KFloat),parsx_token(KDouble),parsx_token(Identifier),parsx_token(KString),parsx_token(KBytes),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KUndef))
		parsx_sync_mask(1,parsx_token(OConcat))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(7,parsx_token(OMinus),parsx_token(OMult),parsx_token(ODiv),parsx_token(ORem),parsx_token(OPeriod),parsx_token(OLParen),parsx_token(OPlus))
		parsx_sync_mask(12,parsx_token(OLBrace),parsx_token(KNull),parsx_token(OMult),parsx_token(Identifier),parsx_token(OQuote),parsx_token(StringLiteral),parsx_token(OVBar),parsx_token(KTrue),parsx_token(NumberLiteral),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(12,parsx_token(OLBrace),parsx_token(KBool),parsx_token(KInt),parsx_token(KFloat),parsx_token(KUndef),parsx_token(Identifier),parsx_token(KString),parsx_token(KBytes),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KDouble),parsx_token(ORParen))
		parsx_sync_mask(0)
		parsx_sync_mask(10,parsx_token(KAnd),parsx_token(OConcat),parsx_token(OLT),parsx_token(KOr),parsx_token(OGT),parsx_token(OLE),parsx_token(OGE),parsx_token(OEQ),parsx_token(OColon),parsx_token(ONE))
		parsx_sync_mask(1,parsx_token(OArrow))
		parsx_sync_mask(5,parsx_token(OMinus),parsx_token(ORem),parsx_token(OMult),parsx_token(OPlus),parsx_token(ODiv))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KWith))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KImplements))
		parsx_sync_mask(0)
		parsx_sync_mask(5,parsx_token(KField),parsx_token(KMethod),parsx_token(KAbstract),parsx_token(KConstructor),parsx_token(KOverride))
		parsx_sync_mask(1,parsx_token(KField))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(3,parsx_token(OAssign),parsx_token(OSemicolon),parsx_token(OColon))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KImport))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OLParen))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OVBar))
		parsx_sync_mask(3,parsx_token(OLParen),parsx_token(KWith),parsx_token(Identifier))
		parsx_sync_mask(1,parsx_token(KThen))
		parsx_sync_mask(0)
		parsx_sync_mask(3,parsx_token(Identifier),parsx_token(OPeriod),parsx_token(KWith))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KDo))
		parsx_sync_mask(1,parsx_token(KIn))
		parsx_sync_mask(15,parsx_token(OLBrace),parsx_token(KMatch),parsx_token(OMinus),parsx_token(KNull),parsx_token(KNot),parsx_token(KIf),parsx_token(Identifier),parsx_token(KLambda),parsx_token(StringLiteral),parsx_token(KNew),parsx_token(KTrue),parsx_token(NumberLiteral),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(1,parsx_token(KMethod))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(3,parsx_token(KElseIf),parsx_token(KEnd),parsx_token(KElse))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KUntil))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OPeriod))
		parsx_sync_mask(0)
		parsx_sync_mask(15,parsx_token(OMinus),parsx_token(OMult),parsx_token(OConcat),parsx_token(ODiv),parsx_token(KOr),parsx_token(ORem),parsx_token(OLT),parsx_token(OLE),parsx_token(OGE),parsx_token(OEQ),parsx_token(OColon),parsx_token(ONE),parsx_token(KAnd),parsx_token(OGT),parsx_token(OPlus))
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(OArrow),parsx_token(OQuestion))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OAssign))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(6,parsx_token(KStruct),parsx_token(KInterface),parsx_token(KClass),parsx_token(KEnum),parsx_token(KFunction),parsx_token(KGlobal))
		parsx_sync_mask(1,parsx_token(OComma))
		parsx_sync_mask(2,parsx_token(OComma),parsx_token(OAssign))
		parsx_sync_mask(0)
		parsx_sync_mask(6,parsx_token(OMinus),parsx_token(OMult),parsx_token(OConcat),parsx_token(ODiv),parsx_token(ORem),parsx_token(OPlus))
		parsx_sync_mask(0)
		parsx_sync_mask(10,parsx_token(OLBrace),parsx_token(KBool),parsx_token(KInt),parsx_token(KFloat),parsx_token(KDouble),parsx_token(Identifier),parsx_token(KString),parsx_token(KBytes),parsx_token(KUnit),parsx_token(KUndef))
		parsx_sync_mask(1,parsx_token(KWith))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KExtends))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KMethod))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(OLParen),parsx_token(OPeriod))
		parsx_sync_mask(1,parsx_token(KAnd))
		parsx_sync_mask(1,parsx_token(KExtends))
		parsx_sync_mask(0)
		parsx_sync_mask(24,parsx_token(KNot),parsx_token(KIf),parsx_token(KConstruct),parsx_token(OLBrace),parsx_token(KFor),parsx_token(KWhile),parsx_token(KDo),parsx_token(KVar),parsx_token(KLet),parsx_token(KReturn),parsx_token(KEval),parsx_token(KRaise),parsx_token(KMatch),parsx_token(KRepeat),parsx_token(OSemicolon),parsx_token(KLambda),parsx_token(KNew),parsx_token(KUnit),parsx_token(KNull),parsx_token(Identifier),parsx_token(StringLiteral),parsx_token(NumberLiteral),parsx_token(KTrue),parsx_token(KFalse))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(OAssign))
		parsx_sync_mask(1,parsx_token(KExtends))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(KOr),parsx_token(OColon))
		parsx_sync_mask(3,parsx_token(OArrow),parsx_token(OVBar),parsx_token(OQuestion))
		parsx_sync_mask(2,parsx_token(OComma),parsx_token(OAssign))
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(OLParen),parsx_token(OPeriod))
		parsx_sync_mask(0)
		parsx_sync_mask(5,parsx_token(KField),parsx_token(KMethod),parsx_token(KAbstract),parsx_token(KConstructor),parsx_token(KOverride))
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(OMinus),parsx_token(OPlus))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(Identifier))
		parsx_sync_mask(9,parsx_token(KAnd),parsx_token(OLT),parsx_token(KOr),parsx_token(OGT),parsx_token(OLE),parsx_token(OGE),parsx_token(OEQ),parsx_token(OColon),parsx_token(ONE))
		parsx_sync_mask(12,parsx_token(OMinus),parsx_token(KAnd),parsx_token(OConcat),parsx_token(OLT),parsx_token(KOr),parsx_token(OGT),parsx_token(OLE),parsx_token(OGE),parsx_token(OEQ),parsx_token(OColon),parsx_token(ONE),parsx_token(OPlus))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KField))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(Identifier))
		parsx_sync_mask(11,parsx_token(OLBrace),parsx_token(KBool),parsx_token(KInt),parsx_token(KFloat),parsx_token(KDouble),parsx_token(Identifier),parsx_token(KString),parsx_token(KBytes),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KUndef))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KImport))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KAs))
		parsx_sync_mask(12,parsx_token(OLBrace),parsx_token(KNull),parsx_token(OMult),parsx_token(Identifier),parsx_token(OQuote),parsx_token(StringLiteral),parsx_token(OVBar),parsx_token(KTrue),parsx_token(NumberLiteral),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(0)
		parsx_sync_mask(1,parsx_token(KEnd))
		parsx_sync_mask(15,parsx_token(OLBrace),parsx_token(KMatch),parsx_token(OMinus),parsx_token(KNull),parsx_token(KNot),parsx_token(KIf),parsx_token(Identifier),parsx_token(KLambda),parsx_token(StringLiteral),parsx_token(KNew),parsx_token(KTrue),parsx_token(NumberLiteral),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(1,parsx_token(OComma))
		parsx_sync_mask(8,parsx_token(KStruct),parsx_token(KInterface),parsx_token(KClass),parsx_token(KEnum),parsx_token(KImport),parsx_token(KFunction),parsx_token(EndOfFile),parsx_token(KGlobal))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(2,parsx_token(OMult),parsx_token(OVBar))
		parsx_sync_mask(0)
		parsx_sync_mask(0)
		parsx_sync_mask(6,parsx_token(KStruct),parsx_token(KInterface),parsx_token(KClass),parsx_token(KEnum),parsx_token(KFunction),parsx_token(KGlobal))
		parsx_sync_mask(3,parsx_token(KOr),parsx_token(KAnd),parsx_token(OColon))
		parsx_sync_mask(1,parsx_token(EndOfFile))
		parsx_sync_mask(0)
		parsx_sync_mask(15,parsx_token(OLBrace),parsx_token(KMatch),parsx_token(OMinus),parsx_token(KNull),parsx_token(KNot),parsx_token(KIf),parsx_token(Identifier),parsx_token(KLambda),parsx_token(StringLiteral),parsx_token(KNew),parsx_token(KTrue),parsx_token(NumberLiteral),parsx_token(OLParen),parsx_token(KUnit),parsx_token(KFalse))
		parsx_sync_mask(1,parsx_token(KAs))
		parsx_sync_mask(0)
		parsx_sync_mask(3,parsx_token(Identifier),parsx_token(OPeriod),parsx_token(KWith))
		parsx_sync_mask(6,parsx_token(OLT),parsx_token(OGT),parsx_token(OLE),parsx_token(OGE),parsx_token(OEQ),parsx_token(ONE))
		parsx_sync_mask(1,parsx_token(OQuestion))
		parsx_sync_mask(1,parsx_token(OConcat))
	parsx_sync_mask_table_end()
#endif

