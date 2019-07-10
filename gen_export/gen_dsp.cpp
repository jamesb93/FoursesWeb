#include "gen_dsp.h"

namespace gen_dsp {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	DCBlock __m_dcblock_51;
	DCBlock __m_dcblock_47;
	DCBlock __m_dcblock_39;
	DCBlock __m_dcblock_43;
	PlusEquals __m_pluseq_50;
	PlusEquals __m_pluseq_46;
	PlusEquals __m_pluseq_38;
	PlusEquals __m_pluseq_42;
	int __exception;
	int vectorsize;
	t_sample m_history_28;
	t_sample __m_latch_40;
	t_sample m_history_29;
	t_sample m_history_30;
	t_sample m_history_27;
	t_sample m_history_25;
	t_sample m_history_26;
	t_sample __m_latch_44;
	t_sample m_history_31;
	t_sample m_history_33;
	t_sample __m_latch_48;
	t_sample m_history_32;
	t_sample m_l_24;
	t_sample m_history_34;
	t_sample m_history_35;
	t_sample m_history_36;
	t_sample m_u_23;
	t_sample m_r_21;
	t_sample m_j_6;
	t_sample m_q_5;
	t_sample m_m_7;
	t_sample m_b_8;
	t_sample m_k_9;
	t_sample m_n_4;
	t_sample m_o_2;
	t_sample m_c_3;
	t_sample samplerate;
	t_sample m_w_1;
	t_sample m_g_22;
	t_sample m_s_10;
	t_sample m_i_12;
	t_sample m_e_18;
	t_sample m_d_19;
	t_sample m_v_20;
	t_sample m_h_11;
	t_sample m_x_17;
	t_sample m_f_15;
	t_sample m_a_16;
	t_sample m_p_13;
	t_sample m_t_14;
	t_sample __m_latch_52;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_w_1 = ((int)0);
		m_o_2 = ((int)0);
		m_c_3 = ((int)0);
		m_n_4 = ((int)0);
		m_q_5 = ((int)0);
		m_j_6 = ((int)0);
		m_m_7 = ((int)0);
		m_b_8 = ((int)0);
		m_k_9 = ((int)0);
		m_s_10 = ((int)0);
		m_h_11 = ((int)0);
		m_i_12 = ((int)0);
		m_p_13 = ((int)0);
		m_t_14 = ((int)0);
		m_f_15 = ((int)0);
		m_a_16 = ((int)0);
		m_x_17 = ((int)0);
		m_e_18 = ((int)0);
		m_d_19 = ((int)0);
		m_v_20 = ((int)0);
		m_r_21 = ((int)0);
		m_g_22 = ((int)0);
		m_u_23 = ((int)0);
		m_l_24 = ((int)0);
		m_history_25 = ((int)0);
		m_history_26 = ((int)0);
		m_history_27 = ((int)0);
		m_history_28 = ((int)0);
		m_history_29 = ((int)0);
		m_history_30 = ((int)0);
		m_history_31 = ((int)0);
		m_history_32 = ((int)0);
		m_history_33 = ((int)0);
		m_history_34 = ((int)0);
		m_history_35 = ((int)0);
		m_history_36 = ((int)0);
		__m_pluseq_38.reset(0);
		__m_dcblock_39.reset();
		__m_latch_40 = 0;
		__m_pluseq_42.reset(0);
		__m_dcblock_43.reset();
		__m_latch_44 = 0;
		__m_pluseq_46.reset(0);
		__m_dcblock_47.reset();
		__m_latch_48 = 0;
		__m_pluseq_50.reset(0);
		__m_dcblock_51.reset();
		__m_latch_52 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample expr_1267 = ((m_a_16 * ((int)10)) - ((int)5));
		t_sample expr_1268 = ((m_b_8 * ((int)10)) - ((int)5));
		t_sample expr_1269 = ((m_c_3 * ((int)10)) - ((int)5));
		t_sample expr_1270 = ((m_d_19 * ((int)10)) - ((int)5));
		t_sample expr_1272 = ((m_f_15 * ((int)10)) - ((int)5));
		t_sample expr_1273 = ((m_g_22 * ((int)10)) - ((int)5));
		t_sample expr_1274 = ((m_h_11 * ((int)10)) - ((int)5));
		t_sample expr_1275 = ((m_i_12 * ((int)10)) - ((int)5));
		t_sample expr_1276 = ((m_j_6 * ((int)10)) - ((int)5));
		t_sample expr_1277 = ((m_k_9 * ((int)10)) - ((int)5));
		t_sample expr_1278 = ((m_l_24 * ((int)10)) - ((int)5));
		t_sample expr_1279 = ((m_m_7 * ((int)10)) - ((int)5));
		t_sample expr_1280 = ((m_n_4 * ((int)10)) - ((int)5));
		t_sample expr_1281 = ((m_o_2 * ((int)10)) - ((int)5));
		t_sample expr_1282 = ((m_p_13 * ((int)10)) - ((int)5));
		t_sample expr_1283 = safepow((m_q_5 * ((int)100)), ((int)2));
		t_sample expr_1284 = safepow((m_r_21 * ((int)100)), ((int)2));
		t_sample expr_1285 = safepow((m_s_10 * ((int)100)), ((int)2));
		t_sample expr_1286 = safepow((m_t_14 * ((int)100)), ((int)2));
		t_sample expr_1287 = safepow((m_u_23 * ((int)100)), ((int)2));
		t_sample expr_1288 = safepow((m_v_20 * ((int)100)), ((int)2));
		t_sample expr_1289 = safepow((m_w_1 * ((int)100)), ((int)2));
		t_sample expr_1290 = safepow((m_x_17 * ((int)100)), ((int)2));
		t_sample rsub_1184 = (((int)0) - expr_1279);
		t_sample div_1218 = safediv(expr_1287, samplerate);
		t_sample mul_1224 = (expr_1288 * (-1));
		t_sample div_1219 = safediv(mul_1224, samplerate);
		t_sample rsub_1186 = (((int)0) - expr_1275);
		t_sample div_1254 = safediv(expr_1283, samplerate);
		t_sample mul_1260 = (expr_1284 * (-1));
		t_sample div_1255 = safediv(mul_1260, samplerate);
		t_sample rsub_1185 = (((int)0) - expr_1277);
		t_sample div_1236 = safediv(expr_1285, samplerate);
		t_sample mul_1242 = (expr_1286 * (-1));
		t_sample div_1237 = safediv(mul_1242, samplerate);
		t_sample rsub_1183 = (((int)0) - expr_1281);
		t_sample div_1200 = safediv(expr_1289, samplerate);
		t_sample mul_1206 = (expr_1290 * (-1));
		t_sample div_1201 = safediv(mul_1206, samplerate);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample mul_1213 = (m_history_35 * expr_1272);
			t_sample choice_37 = int(m_history_25);
			t_sample selector_1225 = ((choice_37 >= 2) ? div_1219 : ((choice_37 >= 1) ? div_1218 : 0));
			t_sample plusequals_1226 = __m_pluseq_38.post(selector_1225, ((int)0), 0);
			t_sample dcblock_1215 = __m_dcblock_39(plusequals_1226);
			t_sample pass_1216 = plusequals_1226;
			int gte_1222 = (pass_1216 >= (mul_1213 + rsub_1184));
			int lte_1223 = (pass_1216 <= (expr_1280 + m_history_34));
			__m_latch_40 = (((gte_1222 + lte_1223) != 0) ? gte_1222 : __m_latch_40);
			int latch_1221 = __m_latch_40;
			int add_1217 = (latch_1221 + ((int)1));
			int gen_1229 = add_1217;
			t_sample mul_1214 = (add_1217 * ((t_sample)22.18281828459));
			t_sample gen_1230 = mul_1214;
			t_sample history_1220_next_1227 = fixdenorm(add_1217);
			t_sample mul_1249 = (m_history_33 * expr_1268);
			t_sample choice_41 = int(m_history_26);
			t_sample selector_1261 = ((choice_41 >= 2) ? div_1255 : ((choice_41 >= 1) ? div_1254 : 0));
			t_sample plusequals_1262 = __m_pluseq_42.post(selector_1261, ((int)0), 0);
			t_sample dcblock_1251 = __m_dcblock_43(plusequals_1262);
			t_sample pass_1252 = plusequals_1262;
			int gte_1258 = (pass_1252 >= (mul_1249 + rsub_1186));
			int lte_1259 = (pass_1252 <= (expr_1276 + m_history_36));
			__m_latch_44 = (((gte_1258 + lte_1259) != 0) ? gte_1258 : __m_latch_44);
			int latch_1257 = __m_latch_44;
			int add_1253 = (latch_1257 + ((int)1));
			int gen_1265 = add_1253;
			t_sample mul_1250 = (add_1253 * expr_1267);
			t_sample gen_1266 = mul_1250;
			t_sample history_1256_next_1263 = fixdenorm(add_1253);
			t_sample mul_1231 = (m_history_29 * expr_1270);
			t_sample choice_45 = int(m_history_27);
			t_sample selector_1243 = ((choice_45 >= 2) ? div_1237 : ((choice_45 >= 1) ? div_1236 : 0));
			t_sample plusequals_1244 = __m_pluseq_46.post(selector_1243, ((int)0), 0);
			t_sample dcblock_1233 = __m_dcblock_47(plusequals_1244);
			t_sample pass_1234 = plusequals_1244;
			int gte_1240 = (pass_1234 >= (mul_1231 + rsub_1185));
			int lte_1241 = (pass_1234 <= (expr_1278 + m_history_31));
			__m_latch_48 = (((gte_1240 + lte_1241) != 0) ? gte_1240 : __m_latch_48);
			int latch_1239 = __m_latch_48;
			int add_1235 = (latch_1239 + ((int)1));
			int gen_1247 = add_1235;
			t_sample mul_1232 = (add_1235 * expr_1269);
			t_sample gen_1248 = mul_1232;
			t_sample history_1238_next_1245 = fixdenorm(add_1235);
			t_sample mul_1182 = (dcblock_1251 * dcblock_1233);
			t_sample fold_1181 = fold(mul_1182, (-1), ((int)1));
			t_sample out1 = fold_1181;
			t_sample mul_1195 = (m_history_32 * expr_1274);
			t_sample choice_49 = int(m_history_28);
			t_sample selector_1207 = ((choice_49 >= 2) ? div_1201 : ((choice_49 >= 1) ? div_1200 : 0));
			t_sample plusequals_1208 = __m_pluseq_50.post(selector_1207, ((int)0), 0);
			t_sample dcblock_1197 = __m_dcblock_51(plusequals_1208);
			t_sample pass_1198 = plusequals_1208;
			int gte_1204 = (pass_1198 >= (mul_1195 + rsub_1183));
			int lte_1205 = (pass_1198 <= (expr_1282 + m_history_30));
			__m_latch_52 = (((gte_1204 + lte_1205) != 0) ? gte_1204 : __m_latch_52);
			int latch_1203 = __m_latch_52;
			int add_1199 = (latch_1203 + ((int)1));
			int gen_1211 = add_1199;
			t_sample mul_1196 = (add_1199 * expr_1273);
			t_sample gen_1212 = mul_1196;
			t_sample history_1202_next_1209 = fixdenorm(add_1199);
			t_sample mul_1180 = (dcblock_1215 * dcblock_1197);
			t_sample fold_1179 = fold(mul_1180, (-1), ((int)1));
			t_sample out2 = fold_1179;
			t_sample history_1192_next_1291 = fixdenorm(gen_1229);
			t_sample history_1187_next_1292 = fixdenorm(gen_1230);
			t_sample history_1189_next_1293 = fixdenorm(gen_1266);
			t_sample history_1194_next_1294 = fixdenorm(gen_1265);
			t_sample history_1193_next_1295 = fixdenorm(gen_1247);
			t_sample history_1188_next_1296 = fixdenorm(gen_1248);
			t_sample history_1191_next_1297 = fixdenorm(gen_1211);
			t_sample history_1190_next_1298 = fixdenorm(gen_1212);
			m_history_25 = history_1220_next_1227;
			m_history_36 = history_1190_next_1298;
			m_history_35 = history_1191_next_1297;
			m_history_34 = history_1188_next_1296;
			m_history_33 = history_1193_next_1295;
			m_history_32 = history_1194_next_1294;
			m_history_31 = history_1189_next_1293;
			m_history_30 = history_1187_next_1292;
			m_history_29 = history_1192_next_1291;
			m_history_28 = history_1202_next_1209;
			m_history_27 = history_1238_next_1245;
			m_history_26 = history_1256_next_1263;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_w(t_param _value) {
		m_w_1 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_o(t_param _value) {
		m_o_2 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_c(t_param _value) {
		m_c_3 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_n(t_param _value) {
		m_n_4 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_q(t_param _value) {
		m_q_5 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_j(t_param _value) {
		m_j_6 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_m(t_param _value) {
		m_m_7 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_b(t_param _value) {
		m_b_8 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_k(t_param _value) {
		m_k_9 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_s(t_param _value) {
		m_s_10 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_h(t_param _value) {
		m_h_11 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_i(t_param _value) {
		m_i_12 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_p(t_param _value) {
		m_p_13 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_t(t_param _value) {
		m_t_14 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_f(t_param _value) {
		m_f_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_a(t_param _value) {
		m_a_16 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_x(t_param _value) {
		m_x_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_e(t_param _value) {
		m_e_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_d(t_param _value) {
		m_d_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_v(t_param _value) {
		m_v_20 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_r(t_param _value) {
		m_r_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_g(t_param _value) {
		m_g_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_u(t_param _value) {
		m_u_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_l(t_param _value) {
		m_l_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 24; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_a(value); break;
		case 1: self->set_b(value); break;
		case 2: self->set_c(value); break;
		case 3: self->set_d(value); break;
		case 4: self->set_e(value); break;
		case 5: self->set_f(value); break;
		case 6: self->set_g(value); break;
		case 7: self->set_h(value); break;
		case 8: self->set_i(value); break;
		case 9: self->set_j(value); break;
		case 10: self->set_k(value); break;
		case 11: self->set_l(value); break;
		case 12: self->set_m(value); break;
		case 13: self->set_n(value); break;
		case 14: self->set_o(value); break;
		case 15: self->set_p(value); break;
		case 16: self->set_q(value); break;
		case 17: self->set_r(value); break;
		case 18: self->set_s(value); break;
		case 19: self->set_t(value); break;
		case 20: self->set_u(value); break;
		case 21: self->set_v(value); break;
		case 22: self->set_w(value); break;
		case 23: self->set_x(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_a_16; break;
		case 1: *value = self->m_b_8; break;
		case 2: *value = self->m_c_3; break;
		case 3: *value = self->m_d_19; break;
		case 4: *value = self->m_e_18; break;
		case 5: *value = self->m_f_15; break;
		case 6: *value = self->m_g_22; break;
		case 7: *value = self->m_h_11; break;
		case 8: *value = self->m_i_12; break;
		case 9: *value = self->m_j_6; break;
		case 10: *value = self->m_k_9; break;
		case 11: *value = self->m_l_24; break;
		case 12: *value = self->m_m_7; break;
		case 13: *value = self->m_n_4; break;
		case 14: *value = self->m_o_2; break;
		case 15: *value = self->m_p_13; break;
		case 16: *value = self->m_q_5; break;
		case 17: *value = self->m_r_21; break;
		case 18: *value = self->m_s_10; break;
		case 19: *value = self->m_t_14; break;
		case 20: *value = self->m_u_23; break;
		case 21: *value = self->m_v_20; break;
		case 22: *value = self->m_w_1; break;
		case 23: *value = self->m_x_17; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(24 * sizeof(ParamInfo));
	self->__commonstate.numparams = 24;
	// initialize parameter 0 ("m_a_16")
	pi = self->__commonstate.params + 0;
	pi->name = "a";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_a_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_b_8")
	pi = self->__commonstate.params + 1;
	pi->name = "b";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_b_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_c_3")
	pi = self->__commonstate.params + 2;
	pi->name = "c";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_19")
	pi = self->__commonstate.params + 3;
	pi->name = "d";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_18")
	pi = self->__commonstate.params + 4;
	pi->name = "e";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_f_15")
	pi = self->__commonstate.params + 5;
	pi->name = "f";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_f_15;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_g_22")
	pi = self->__commonstate.params + 6;
	pi->name = "g";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_11")
	pi = self->__commonstate.params + 7;
	pi->name = "h";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_i_12")
	pi = self->__commonstate.params + 8;
	pi->name = "i";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_i_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_j_6")
	pi = self->__commonstate.params + 9;
	pi->name = "j";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_j_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_k_9")
	pi = self->__commonstate.params + 10;
	pi->name = "k";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_k_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_l_24")
	pi = self->__commonstate.params + 11;
	pi->name = "l";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_l_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_m_7")
	pi = self->__commonstate.params + 12;
	pi->name = "m";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_n_4")
	pi = self->__commonstate.params + 13;
	pi->name = "n";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_n_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 14 ("m_o_2")
	pi = self->__commonstate.params + 14;
	pi->name = "o";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_o_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 15 ("m_p_13")
	pi = self->__commonstate.params + 15;
	pi->name = "p";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_p_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 16 ("m_q_5")
	pi = self->__commonstate.params + 16;
	pi->name = "q";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_q_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 17 ("m_r_21")
	pi = self->__commonstate.params + 17;
	pi->name = "r";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_r_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 18 ("m_s_10")
	pi = self->__commonstate.params + 18;
	pi->name = "s";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_s_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 19 ("m_t_14")
	pi = self->__commonstate.params + 19;
	pi->name = "t";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_t_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 20 ("m_u_23")
	pi = self->__commonstate.params + 20;
	pi->name = "u";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_u_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 21 ("m_v_20")
	pi = self->__commonstate.params + 21;
	pi->name = "v";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_v_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 22 ("m_w_1")
	pi = self->__commonstate.params + 22;
	pi->name = "w";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_w_1;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 23 ("m_x_17")
	pi = self->__commonstate.params + 23;
	pi->name = "x";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_x_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // gen_dsp::
