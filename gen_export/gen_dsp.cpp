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
	t_sample m_x_24;
	t_sample m_history_34;
	t_sample m_history_35;
	t_sample m_history_36;
	t_sample m_i_23;
	t_sample m_r_21;
	t_sample m_n_6;
	t_sample m_d_5;
	t_sample m_l_7;
	t_sample m_a_8;
	t_sample m_b_9;
	t_sample m_c_4;
	t_sample m_w_2;
	t_sample m_h_3;
	t_sample samplerate;
	t_sample m_g_1;
	t_sample m_q_22;
	t_sample m_k_10;
	t_sample m_e_12;
	t_sample m_v_18;
	t_sample m_j_19;
	t_sample m_f_20;
	t_sample m_s_11;
	t_sample m_u_17;
	t_sample m_m_15;
	t_sample m_t_16;
	t_sample m_o_13;
	t_sample m_p_14;
	t_sample __m_latch_52;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_g_1 = ((int)0);
		m_w_2 = ((int)0);
		m_h_3 = ((int)0);
		m_c_4 = ((int)0);
		m_d_5 = ((int)0);
		m_n_6 = ((int)0);
		m_l_7 = ((int)0);
		m_a_8 = ((int)0);
		m_b_9 = ((int)0);
		m_k_10 = ((int)0);
		m_s_11 = ((int)0);
		m_e_12 = ((int)0);
		m_o_13 = ((int)0);
		m_p_14 = ((int)0);
		m_m_15 = ((int)0);
		m_t_16 = ((int)0);
		m_u_17 = ((int)0);
		m_v_18 = ((int)0);
		m_j_19 = ((int)0);
		m_f_20 = ((int)0);
		m_r_21 = ((int)0);
		m_q_22 = ((int)0);
		m_i_23 = ((int)0);
		m_x_24 = ((int)0);
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
		t_sample expr_835 = ((m_a_8 * ((int)10)) - ((int)5));
		t_sample expr_836 = ((m_b_9 * ((int)10)) - ((int)5));
		t_sample expr_837 = ((m_c_4 * ((int)10)) - ((int)5));
		t_sample expr_838 = ((m_d_5 * ((int)10)) - ((int)5));
		t_sample expr_840 = ((m_f_20 * ((int)10)) - ((int)5));
		t_sample expr_841 = ((m_g_1 * ((int)10)) - ((int)5));
		t_sample expr_842 = ((m_h_3 * ((int)10)) - ((int)5));
		t_sample expr_843 = ((m_i_23 * ((int)10)) - ((int)5));
		t_sample expr_844 = ((m_j_19 * ((int)10)) - ((int)5));
		t_sample expr_845 = ((m_k_10 * ((int)10)) - ((int)5));
		t_sample expr_846 = ((m_l_7 * ((int)10)) - ((int)5));
		t_sample expr_847 = ((m_m_15 * ((int)10)) - ((int)5));
		t_sample expr_848 = ((m_n_6 * ((int)10)) - ((int)5));
		t_sample expr_849 = ((m_o_13 * ((int)10)) - ((int)5));
		t_sample expr_850 = ((m_p_14 * ((int)10)) - ((int)5));
		t_sample expr_851 = safepow((m_q_22 * ((int)100)), ((int)2));
		t_sample expr_852 = safepow((m_r_21 * ((int)100)), ((int)2));
		t_sample expr_853 = safepow((m_s_11 * ((int)100)), ((int)2));
		t_sample expr_854 = safepow((m_t_16 * ((int)100)), ((int)2));
		t_sample expr_855 = safepow((m_u_17 * ((int)100)), ((int)2));
		t_sample expr_856 = safepow((m_v_18 * ((int)100)), ((int)2));
		t_sample expr_857 = safepow((m_w_2 * ((int)100)), ((int)2));
		t_sample expr_858 = safepow((m_x_24 * ((int)100)), ((int)2));
		t_sample rsub_690 = (((int)0) - expr_843);
		t_sample div_758 = safediv(expr_851, samplerate);
		t_sample mul_764 = (expr_852 * (-1));
		t_sample div_759 = safediv(mul_764, samplerate);
		t_sample rsub_687 = (((int)0) - expr_849);
		t_sample div_704 = safediv(expr_857, samplerate);
		t_sample mul_710 = (expr_858 * (-1));
		t_sample div_705 = safediv(mul_710, samplerate);
		t_sample rsub_689 = (((int)0) - expr_845);
		t_sample div_740 = safediv(expr_853, samplerate);
		t_sample mul_746 = (expr_854 * (-1));
		t_sample div_741 = safediv(mul_746, samplerate);
		t_sample rsub_688 = (((int)0) - expr_847);
		t_sample div_722 = safediv(expr_855, samplerate);
		t_sample mul_728 = (expr_856 * (-1));
		t_sample div_723 = safediv(mul_728, samplerate);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample mul_753 = (m_history_34 * expr_836);
			t_sample choice_37 = int(m_history_25);
			t_sample selector_765 = ((choice_37 >= 2) ? div_759 : ((choice_37 >= 1) ? div_758 : 0));
			t_sample plusequals_766 = __m_pluseq_38.post(selector_765, ((int)0), 0);
			t_sample dcblock_755 = __m_dcblock_39(plusequals_766);
			t_sample pass_756 = plusequals_766;
			int gte_762 = (pass_756 >= (rsub_690 + mul_753));
			int lte_763 = (pass_756 <= (m_history_31 + expr_844));
			__m_latch_40 = (((lte_763 + gte_762) != 0) ? gte_762 : __m_latch_40);
			int latch_761 = __m_latch_40;
			int add_757 = (latch_761 + ((int)1));
			int gen_769 = add_757;
			t_sample mul_754 = (add_757 * expr_835);
			t_sample gen_770 = mul_754;
			t_sample history_760_next_767 = fixdenorm(add_757);
			t_sample mul_699 = (m_history_30 * expr_842);
			t_sample choice_41 = int(m_history_26);
			t_sample selector_711 = ((choice_41 >= 2) ? div_705 : ((choice_41 >= 1) ? div_704 : 0));
			t_sample plusequals_712 = __m_pluseq_42.post(selector_711, ((int)0), 0);
			t_sample dcblock_701 = __m_dcblock_43(plusequals_712);
			t_sample pass_702 = plusequals_712;
			int gte_708 = (pass_702 >= (rsub_687 + mul_699));
			int lte_709 = (pass_702 <= (m_history_36 + expr_850));
			__m_latch_44 = (((lte_709 + gte_708) != 0) ? gte_708 : __m_latch_44);
			int latch_707 = __m_latch_44;
			int add_703 = (latch_707 + ((int)1));
			int gen_715 = add_703;
			t_sample mul_700 = (add_703 * expr_841);
			t_sample gen_716 = mul_700;
			t_sample history_706_next_713 = fixdenorm(add_703);
			t_sample mul_735 = (m_history_35 * expr_838);
			t_sample choice_45 = int(m_history_27);
			t_sample selector_747 = ((choice_45 >= 2) ? div_741 : ((choice_45 >= 1) ? div_740 : 0));
			t_sample plusequals_748 = __m_pluseq_46.post(selector_747, ((int)0), 0);
			t_sample dcblock_737 = __m_dcblock_47(plusequals_748);
			t_sample pass_738 = plusequals_748;
			int gte_744 = (pass_738 >= (rsub_689 + mul_735));
			int lte_745 = (pass_738 <= (m_history_29 + expr_846));
			__m_latch_48 = (((lte_745 + gte_744) != 0) ? gte_744 : __m_latch_48);
			int latch_743 = __m_latch_48;
			int add_739 = (latch_743 + ((int)1));
			int gen_751 = add_739;
			t_sample mul_736 = (add_739 * expr_837);
			t_sample gen_752 = mul_736;
			t_sample history_742_next_749 = fixdenorm(add_739);
			t_sample mul_686 = (dcblock_755 * dcblock_737);
			t_sample fold_685 = fold(mul_686, (-1), ((int)1));
			t_sample out1 = fold_685;
			t_sample mul_717 = (m_history_32 * expr_840);
			t_sample choice_49 = int(m_history_28);
			t_sample selector_729 = ((choice_49 >= 2) ? div_723 : ((choice_49 >= 1) ? div_722 : 0));
			t_sample plusequals_730 = __m_pluseq_50.post(selector_729, ((int)0), 0);
			t_sample dcblock_719 = __m_dcblock_51(plusequals_730);
			t_sample pass_720 = plusequals_730;
			int gte_726 = (pass_720 >= (rsub_688 + mul_717));
			int lte_727 = (pass_720 <= (m_history_33 + expr_848));
			__m_latch_52 = (((lte_727 + gte_726) != 0) ? gte_726 : __m_latch_52);
			int latch_725 = __m_latch_52;
			int add_721 = (latch_725 + ((int)1));
			int gen_733 = add_721;
			t_sample mul_718 = (add_721 * ((t_sample)22.18281828459));
			t_sample gen_734 = mul_718;
			t_sample history_724_next_731 = fixdenorm(add_721);
			t_sample mul_684 = (dcblock_719 * dcblock_701);
			t_sample fold_683 = fold(mul_684, (-1), ((int)1));
			t_sample out2 = fold_683;
			t_sample history_693_next_859 = fixdenorm(gen_770);
			t_sample history_698_next_860 = fixdenorm(gen_769);
			t_sample history_694_next_861 = fixdenorm(gen_716);
			t_sample history_695_next_862 = fixdenorm(gen_715);
			t_sample history_692_next_863 = fixdenorm(gen_752);
			t_sample history_697_next_864 = fixdenorm(gen_751);
			t_sample history_696_next_865 = fixdenorm(gen_733);
			t_sample history_691_next_866 = fixdenorm(gen_734);
			m_history_25 = history_760_next_767;
			m_history_36 = history_691_next_866;
			m_history_35 = history_696_next_865;
			m_history_34 = history_697_next_864;
			m_history_33 = history_692_next_863;
			m_history_32 = history_695_next_862;
			m_history_31 = history_694_next_861;
			m_history_30 = history_698_next_860;
			m_history_29 = history_693_next_859;
			m_history_28 = history_724_next_731;
			m_history_27 = history_742_next_749;
			m_history_26 = history_706_next_713;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_g(t_param _value) {
		m_g_1 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_w(t_param _value) {
		m_w_2 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_h(t_param _value) {
		m_h_3 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_c(t_param _value) {
		m_c_4 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_d(t_param _value) {
		m_d_5 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_n(t_param _value) {
		m_n_6 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_l(t_param _value) {
		m_l_7 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_a(t_param _value) {
		m_a_8 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_b(t_param _value) {
		m_b_9 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_k(t_param _value) {
		m_k_10 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_s(t_param _value) {
		m_s_11 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_e(t_param _value) {
		m_e_12 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_o(t_param _value) {
		m_o_13 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_p(t_param _value) {
		m_p_14 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_m(t_param _value) {
		m_m_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_t(t_param _value) {
		m_t_16 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_u(t_param _value) {
		m_u_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_v(t_param _value) {
		m_v_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_j(t_param _value) {
		m_j_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_f(t_param _value) {
		m_f_20 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_r(t_param _value) {
		m_r_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_q(t_param _value) {
		m_q_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_i(t_param _value) {
		m_i_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_x(t_param _value) {
		m_x_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
		case 0: *value = self->m_a_8; break;
		case 1: *value = self->m_b_9; break;
		case 2: *value = self->m_c_4; break;
		case 3: *value = self->m_d_5; break;
		case 4: *value = self->m_e_12; break;
		case 5: *value = self->m_f_20; break;
		case 6: *value = self->m_g_1; break;
		case 7: *value = self->m_h_3; break;
		case 8: *value = self->m_i_23; break;
		case 9: *value = self->m_j_19; break;
		case 10: *value = self->m_k_10; break;
		case 11: *value = self->m_l_7; break;
		case 12: *value = self->m_m_15; break;
		case 13: *value = self->m_n_6; break;
		case 14: *value = self->m_o_13; break;
		case 15: *value = self->m_p_14; break;
		case 16: *value = self->m_q_22; break;
		case 17: *value = self->m_r_21; break;
		case 18: *value = self->m_s_11; break;
		case 19: *value = self->m_t_16; break;
		case 20: *value = self->m_u_17; break;
		case 21: *value = self->m_v_18; break;
		case 22: *value = self->m_w_2; break;
		case 23: *value = self->m_x_24; break;
		
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
	// initialize parameter 0 ("m_a_8")
	pi = self->__commonstate.params + 0;
	pi->name = "a";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_a_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_b_9")
	pi = self->__commonstate.params + 1;
	pi->name = "b";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_b_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_c_4")
	pi = self->__commonstate.params + 2;
	pi->name = "c";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_5")
	pi = self->__commonstate.params + 3;
	pi->name = "d";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_12")
	pi = self->__commonstate.params + 4;
	pi->name = "e";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_f_20")
	pi = self->__commonstate.params + 5;
	pi->name = "f";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_f_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_g_1")
	pi = self->__commonstate.params + 6;
	pi->name = "g";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_1;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_3")
	pi = self->__commonstate.params + 7;
	pi->name = "h";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_i_23")
	pi = self->__commonstate.params + 8;
	pi->name = "i";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_i_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_j_19")
	pi = self->__commonstate.params + 9;
	pi->name = "j";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_j_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_k_10")
	pi = self->__commonstate.params + 10;
	pi->name = "k";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_k_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_l_7")
	pi = self->__commonstate.params + 11;
	pi->name = "l";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_l_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_m_15")
	pi = self->__commonstate.params + 12;
	pi->name = "m";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_15;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_n_6")
	pi = self->__commonstate.params + 13;
	pi->name = "n";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_n_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 14 ("m_o_13")
	pi = self->__commonstate.params + 14;
	pi->name = "o";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_o_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 15 ("m_p_14")
	pi = self->__commonstate.params + 15;
	pi->name = "p";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_p_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 16 ("m_q_22")
	pi = self->__commonstate.params + 16;
	pi->name = "q";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_q_22;
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
	// initialize parameter 18 ("m_s_11")
	pi = self->__commonstate.params + 18;
	pi->name = "s";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_s_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 19 ("m_t_16")
	pi = self->__commonstate.params + 19;
	pi->name = "t";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_t_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 20 ("m_u_17")
	pi = self->__commonstate.params + 20;
	pi->name = "u";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_u_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 21 ("m_v_18")
	pi = self->__commonstate.params + 21;
	pi->name = "v";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_v_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 22 ("m_w_2")
	pi = self->__commonstate.params + 22;
	pi->name = "w";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_w_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 23 ("m_x_24")
	pi = self->__commonstate.params + 23;
	pi->name = "x";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_x_24;
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
