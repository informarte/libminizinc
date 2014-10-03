/*
 *  Main authors:
 *     Kevin Leo <kevin.leo@monash.edu>
 *     Andrea Rendl <andrea.rendl@nicta.com.au>
 *     Guido Tack <guido.tack@monash.edu>
 */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <minizinc/solver_instance_base.hh>
#include "gecode_solverinstance.hh"
#include "gecode_constraints.hh"

using namespace Gecode;

namespace MiniZinc {
 
     GecodeSolverInstance::GecodeSolverInstance(Env& env, const Options& options) 
     : SolverInstanceImpl<GecodeSolver>(env,options), model(NULL) {
       registerConstraints(); // TODO: move this into the super-class since it's always the same for each solver?
       processFlatZinc();
     }
  
    GecodeSolverInstance::~GecodeSolverInstance(void) {
      //delete model;
    }
    
    void GecodeSolverInstance::registerConstraints(void) {
      _constraintRegistry.add(ASTString("all_different_int"), GecodeConstraints::p_distinct);
      _constraintRegistry.add(ASTString("all_different_offset"), GecodeConstraints::p_distinctOffset);
      _constraintRegistry.add(ASTString("all_equal_int"), GecodeConstraints::p_all_equal);
      _constraintRegistry.add(ASTString("int_eq"), GecodeConstraints::p_int_eq);
      _constraintRegistry.add(ASTString("int_ne"), GecodeConstraints::p_int_ne);
      _constraintRegistry.add(ASTString("int_ge"), GecodeConstraints::p_int_ge);
      _constraintRegistry.add(ASTString("int_gt"), GecodeConstraints::p_int_gt);
      _constraintRegistry.add(ASTString("int_le"), GecodeConstraints::p_int_le);
      _constraintRegistry.add(ASTString("int_lt"), GecodeConstraints::p_int_lt);
      _constraintRegistry.add(ASTString("int_eq_reif"), GecodeConstraints::p_int_eq_reif);
      _constraintRegistry.add(ASTString("int_ne_reif"), GecodeConstraints::p_int_ne_reif);
      _constraintRegistry.add(ASTString("int_ge_reif"), GecodeConstraints::p_int_ge_reif);
      _constraintRegistry.add(ASTString("int_gt_reif"), GecodeConstraints::p_int_gt_reif);
      _constraintRegistry.add(ASTString("int_le_reif"), GecodeConstraints::p_int_le_reif);
      _constraintRegistry.add(ASTString("int_lt_reif"), GecodeConstraints::p_int_lt_reif);
      _constraintRegistry.add(ASTString("int_eq_imp"), GecodeConstraints::p_int_eq_imp);
      _constraintRegistry.add(ASTString("int_ne_imp"), GecodeConstraints::p_int_ne_imp);
      _constraintRegistry.add(ASTString("int_ge_imp"), GecodeConstraints::p_int_ge_imp);
      _constraintRegistry.add(ASTString("int_gt_imp"), GecodeConstraints::p_int_gt_imp);
      _constraintRegistry.add(ASTString("int_le_imp"), GecodeConstraints::p_int_le_imp);
      _constraintRegistry.add(ASTString("int_lt_imp"), GecodeConstraints::p_int_lt_imp);
      _constraintRegistry.add(ASTString("int_lin_eq"), GecodeConstraints::p_int_lin_eq);
      _constraintRegistry.add(ASTString("int_lin_eq_reif"), GecodeConstraints::p_int_lin_eq_reif);
      _constraintRegistry.add(ASTString("int_lin_eq_imp"), GecodeConstraints::p_int_lin_eq_imp);
      _constraintRegistry.add(ASTString("int_lin_ne"), GecodeConstraints::p_int_lin_ne);
      _constraintRegistry.add(ASTString("int_lin_ne_reif"), GecodeConstraints::p_int_lin_ne_reif);
      _constraintRegistry.add(ASTString("int_lin_ne_imp"), GecodeConstraints::p_int_lin_ne_imp);
      _constraintRegistry.add(ASTString("int_lin_le"), GecodeConstraints::p_int_lin_le);
      _constraintRegistry.add(ASTString("int_lin_le_reif"), GecodeConstraints::p_int_lin_le_reif);
      _constraintRegistry.add(ASTString("int_lin_le_imp"), GecodeConstraints::p_int_lin_le_imp);
      _constraintRegistry.add(ASTString("int_lin_lt"), GecodeConstraints::p_int_lin_lt);
      _constraintRegistry.add(ASTString("int_lin_lt_reif"), GecodeConstraints::p_int_lin_lt_reif);
      _constraintRegistry.add(ASTString("int_lin_lt_imp"), GecodeConstraints::p_int_lin_lt_imp);
      _constraintRegistry.add(ASTString("int_lin_ge"), GecodeConstraints::p_int_lin_ge);
      _constraintRegistry.add(ASTString("int_lin_ge_reif"), GecodeConstraints::p_int_lin_ge_reif);
      _constraintRegistry.add(ASTString("int_lin_ge_imp"), GecodeConstraints::p_int_lin_ge_imp);
      _constraintRegistry.add(ASTString("int_lin_gt"), GecodeConstraints::p_int_lin_gt);
      _constraintRegistry.add(ASTString("int_lin_gt_reif"), GecodeConstraints::p_int_lin_gt_reif);
      _constraintRegistry.add(ASTString("int_lin_gt_imp"), GecodeConstraints::p_int_lin_gt_imp);
      _constraintRegistry.add(ASTString("int_plus"), GecodeConstraints::p_int_plus);
      _constraintRegistry.add(ASTString("int_minus"), GecodeConstraints::p_int_minus);
      _constraintRegistry.add(ASTString("int_times"), GecodeConstraints::p_int_times);
      _constraintRegistry.add(ASTString("int_div"), GecodeConstraints::p_int_div);
      _constraintRegistry.add(ASTString("int_mod"), GecodeConstraints::p_int_mod);
      _constraintRegistry.add(ASTString("int_min"), GecodeConstraints::p_int_min);
      _constraintRegistry.add(ASTString("int_max"), GecodeConstraints::p_int_max);
      _constraintRegistry.add(ASTString("int_abs"), GecodeConstraints::p_abs);
      _constraintRegistry.add(ASTString("int_negate"), GecodeConstraints::p_int_negate);
      _constraintRegistry.add(ASTString("bool_eq"), GecodeConstraints::p_bool_eq);
      _constraintRegistry.add(ASTString("bool_eq_reif"), GecodeConstraints::p_bool_eq_reif);
      _constraintRegistry.add(ASTString("bool_eq_imp"), GecodeConstraints::p_bool_eq_imp);
      _constraintRegistry.add(ASTString("bool_ne"), GecodeConstraints::p_bool_ne);
      _constraintRegistry.add(ASTString("bool_ne_reif"), GecodeConstraints::p_bool_ne_reif);
      _constraintRegistry.add(ASTString("bool_ne_imp"), GecodeConstraints::p_bool_ne_imp);
      _constraintRegistry.add(ASTString("bool_ge"), GecodeConstraints::p_bool_ge);
      _constraintRegistry.add(ASTString("bool_ge_reif"), GecodeConstraints::p_bool_ge_reif);
      _constraintRegistry.add(ASTString("bool_ge_imp"), GecodeConstraints::p_bool_ge_imp);
      _constraintRegistry.add(ASTString("bool_le"), GecodeConstraints::p_bool_le);
      _constraintRegistry.add(ASTString("bool_le_reif"), GecodeConstraints::p_bool_le_reif);
      _constraintRegistry.add(ASTString("bool_le_imp"), GecodeConstraints::p_bool_le_imp);
      _constraintRegistry.add(ASTString("bool_gt"), GecodeConstraints::p_bool_gt);
      _constraintRegistry.add(ASTString("bool_gt_reif"), GecodeConstraints::p_bool_gt_reif);
      _constraintRegistry.add(ASTString("bool_gt_imp"), GecodeConstraints::p_bool_gt_imp);
      _constraintRegistry.add(ASTString("bool_lt"), GecodeConstraints::p_bool_lt);
      _constraintRegistry.add(ASTString("bool_lt_reif"), GecodeConstraints::p_bool_lt_reif);
      _constraintRegistry.add(ASTString("bool_lt_imp"), GecodeConstraints::p_bool_lt_imp);
      _constraintRegistry.add(ASTString("bool_or"), GecodeConstraints::p_bool_or);
      _constraintRegistry.add(ASTString("bool_or_imp"), GecodeConstraints::p_bool_or_imp);
      _constraintRegistry.add(ASTString("bool_and"), GecodeConstraints::p_bool_and);
      _constraintRegistry.add(ASTString("bool_and_imp"), GecodeConstraints::p_bool_and_imp);
      _constraintRegistry.add(ASTString("bool_xor"), GecodeConstraints::p_bool_xor);
      _constraintRegistry.add(ASTString("bool_xor_imp"), GecodeConstraints::p_bool_xor_imp);
      _constraintRegistry.add(ASTString("array_bool_and"), GecodeConstraints::p_array_bool_and);
      _constraintRegistry.add(ASTString("array_bool_and_imp"), GecodeConstraints::p_array_bool_and_imp);
      _constraintRegistry.add(ASTString("array_bool_or"), GecodeConstraints::p_array_bool_or);
      _constraintRegistry.add(ASTString("array_bool_or_imp"), GecodeConstraints::p_array_bool_or_imp);
      _constraintRegistry.add(ASTString("array_bool_xor"), GecodeConstraints::p_array_bool_xor);
      _constraintRegistry.add(ASTString("array_bool_xor_imp"), GecodeConstraints::p_array_bool_xor_imp);
      _constraintRegistry.add(ASTString("bool_clause"), GecodeConstraints::p_array_bool_clause);
      _constraintRegistry.add(ASTString("bool_clause_reif"), GecodeConstraints::p_array_bool_clause_reif);
      _constraintRegistry.add(ASTString("bool_clause_imp"), GecodeConstraints::p_array_bool_clause_imp);
      _constraintRegistry.add(ASTString("bool_left_imp"), GecodeConstraints::p_bool_l_imp);
      _constraintRegistry.add(ASTString("bool_right_imp"), GecodeConstraints::p_bool_r_imp);
      _constraintRegistry.add(ASTString("bool_not"), GecodeConstraints::p_bool_not);
      _constraintRegistry.add(ASTString("array_int_element"), GecodeConstraints::p_array_int_element);
      _constraintRegistry.add(ASTString("array_var_int_element"), GecodeConstraints::p_array_int_element);
      _constraintRegistry.add(ASTString("array_bool_element"), GecodeConstraints::p_array_bool_element);
      _constraintRegistry.add(ASTString("array_var_bool_element"), GecodeConstraints::p_array_bool_element);
      _constraintRegistry.add(ASTString("bool2int"), GecodeConstraints::p_bool2int);
      _constraintRegistry.add(ASTString("int_in"), GecodeConstraints::p_int_in);
      _constraintRegistry.add(ASTString("int_in_reif"), GecodeConstraints::p_int_in_reif);
      _constraintRegistry.add(ASTString("int_in_imp"), GecodeConstraints::p_int_in_imp);
      //#ifndef GECODE_HAS_SET_VARS
      _constraintRegistry.add(ASTString("set_in"), GecodeConstraints::p_int_in);
      _constraintRegistry.add(ASTString("set_in_reif"), GecodeConstraints::p_int_in_reif);
      _constraintRegistry.add(ASTString("set_in_imp"), GecodeConstraints::p_int_in_imp);
      //#endif
      _constraintRegistry.add(ASTString("array_int_lt"), GecodeConstraints::p_array_int_lt);
      _constraintRegistry.add(ASTString("array_int_lq"), GecodeConstraints::p_array_int_lq);
      _constraintRegistry.add(ASTString("array_bool_lt"), GecodeConstraints::p_array_bool_lt);
      _constraintRegistry.add(ASTString("array_bool_lq"), GecodeConstraints::p_array_bool_lq);
      _constraintRegistry.add(ASTString("count"), GecodeConstraints::p_count);
      _constraintRegistry.add(ASTString("count_reif"), GecodeConstraints::p_count_reif);
      _constraintRegistry.add(ASTString("count_imp"), GecodeConstraints::p_count_imp);
      _constraintRegistry.add(ASTString("at_least_int"), GecodeConstraints::p_at_least);
      _constraintRegistry.add(ASTString("at_most_int"), GecodeConstraints::p_at_most);
      _constraintRegistry.add(ASTString("gecode_bin_packing_load"), GecodeConstraints::p_bin_packing_load);
      _constraintRegistry.add(ASTString("global_cardinality"), GecodeConstraints::p_global_cardinality);
      _constraintRegistry.add(ASTString("global_cardinality_closed"), GecodeConstraints::p_global_cardinality_closed);
      _constraintRegistry.add(ASTString("global_cardinality_low_up"), GecodeConstraints::p_global_cardinality_low_up);
      _constraintRegistry.add(ASTString("global_cardinality_low_up_closed"), GecodeConstraints::p_global_cardinality_low_up_closed);
      _constraintRegistry.add(ASTString("minimum_int"), GecodeConstraints::p_minimum);
      _constraintRegistry.add(ASTString("maximum_int"), GecodeConstraints::p_maximum);
      //addConstraintMappinASTString(g("regular"), GecodeConstraints::p_regular);
      _constraintRegistry.add(ASTString("sort"), GecodeConstraints::p_sort);
      _constraintRegistry.add(ASTString("inverse_offsets"), GecodeConstraints::p_inverse_offsets);
      _constraintRegistry.add(ASTString("increasing_int"), GecodeConstraints::p_increasing_int);
      _constraintRegistry.add(ASTString("increasing_bool"), GecodeConstraints::p_increasing_bool);
      _constraintRegistry.add(ASTString("decreasing_int"), GecodeConstraints::p_decreasing_int);
      _constraintRegistry.add(ASTString("decreasing_bool"), GecodeConstraints::p_decreasing_bool);
      _constraintRegistry.add(ASTString("table_int"), GecodeConstraints::p_table_int);
      _constraintRegistry.add(ASTString("table_bool"), GecodeConstraints::p_table_bool);
      _constraintRegistry.add(ASTString("cumulatives"), GecodeConstraints::p_cumulatives);
      _constraintRegistry.add(ASTString("gecode_among_seq_int"), GecodeConstraints::p_among_seq_int);
      _constraintRegistry.add(ASTString("gecode_among_seq_bool"), GecodeConstraints::p_among_seq_bool);

      _constraintRegistry.add(ASTString("bool_lin_eq"), GecodeConstraints::p_bool_lin_eq);
      _constraintRegistry.add(ASTString("bool_lin_ne"), GecodeConstraints::p_bool_lin_ne);
      _constraintRegistry.add(ASTString("bool_lin_le"), GecodeConstraints::p_bool_lin_le);
      _constraintRegistry.add(ASTString("bool_lin_lt"), GecodeConstraints::p_bool_lin_lt);
      _constraintRegistry.add(ASTString("bool_lin_ge"), GecodeConstraints::p_bool_lin_ge);
      _constraintRegistry.add(ASTString("bool_lin_gt"), GecodeConstraints::p_bool_lin_gt);

      _constraintRegistry.add(ASTString("bool_lin_eq_reif"), GecodeConstraints::p_bool_lin_eq_reif);
      _constraintRegistry.add(ASTString("bool_lin_eq_imp"), GecodeConstraints::p_bool_lin_eq_imp);
      _constraintRegistry.add(ASTString("bool_lin_ne_reif"), GecodeConstraints::p_bool_lin_ne_reif);
      _constraintRegistry.add(ASTString("bool_lin_ne_imp"), GecodeConstraints::p_bool_lin_ne_imp);
      _constraintRegistry.add(ASTString("bool_lin_le_reif"), GecodeConstraints::p_bool_lin_le_reif);
      _constraintRegistry.add(ASTString("bool_lin_le_imp"), GecodeConstraints::p_bool_lin_le_imp);
      _constraintRegistry.add(ASTString("bool_lin_lt_reif"), GecodeConstraints::p_bool_lin_lt_reif);
      _constraintRegistry.add(ASTString("bool_lin_lt_imp"), GecodeConstraints::p_bool_lin_lt_imp);
      _constraintRegistry.add(ASTString("bool_lin_ge_reif"), GecodeConstraints::p_bool_lin_ge_reif);
      _constraintRegistry.add(ASTString("bool_lin_ge_imp"), GecodeConstraints::p_bool_lin_ge_imp);
      _constraintRegistry.add(ASTString("bool_lin_gt_reif"), GecodeConstraints::p_bool_lin_gt_reif);
      _constraintRegistry.add(ASTString("bool_lin_gt_imp"), GecodeConstraints::p_bool_lin_gt_imp);

      _constraintRegistry.add(ASTString("gecode_schedule_unary"), GecodeConstraints::p_schedule_unary);
      _constraintRegistry.add(ASTString("gecode_schedule_unary_optional"), GecodeConstraints::p_schedule_unary_optional);

      _constraintRegistry.add(ASTString("gecode_circuit"), GecodeConstraints::p_circuit);
      _constraintRegistry.add(ASTString("gecode_circuit_cost_array"), GecodeConstraints::p_circuit_cost_array);
      _constraintRegistry.add(ASTString("gecode_circuit_cost"), GecodeConstraints::p_circuit_cost);
      _constraintRegistry.add(ASTString("gecode_nooverlap"), GecodeConstraints::p_nooverlap);
      _constraintRegistry.add(ASTString("gecode_precede"), GecodeConstraints::p_precede);
      _constraintRegistry.add(ASTString("nvalue"), GecodeConstraints::p_nvalue);
      _constraintRegistry.add(ASTString("among"), GecodeConstraints::p_among);
      _constraintRegistry.add(ASTString("member_int"), GecodeConstraints::p_member_int);
      _constraintRegistry.add(ASTString("gecode_member_int_reif"), GecodeConstraints::p_member_int_reif);
      _constraintRegistry.add(ASTString("member_bool"), GecodeConstraints::p_member_bool);
      _constraintRegistry.add(ASTString("gecode_member_bool_reif"), GecodeConstraints::p_member_bool_reif);

#ifdef GECODE_HAS_FLOAT_VARS
      _constraintRegistry.add(ASTString("int2float"),GecodeConstraints::p_int2float);
      _constraintRegistry.add(ASTString("float_abs"),GecodeConstraints::p_float_abs);
      _constraintRegistry.add(ASTString("float_sqrt"),GecodeConstraints::p_float_sqrt);
      _constraintRegistry.add(ASTString("float_eq"),GecodeConstraints::p_float_eq);
      _constraintRegistry.add(ASTString("float_eq_reif"),GecodeConstraints::p_float_eq_reif);
      _constraintRegistry.add(ASTString("float_le"),GecodeConstraints::p_float_le);
      _constraintRegistry.add(ASTString("float_le_reif"),GecodeConstraints::p_float_le_reif);
      _constraintRegistry.add(ASTString("float_lt"),GecodeConstraints::p_float_lt);
      _constraintRegistry.add(ASTString("float_lt_reif"),GecodeConstraints::p_float_lt_reif);
      _constraintRegistry.add(ASTString("float_ne"),GecodeConstraints::p_float_ne);
      _constraintRegistry.add(ASTString("float_times"),GecodeConstraints::p_float_times);
      _constraintRegistry.add(ASTString("float_div"),GecodeConstraints::p_float_div);
      _constraintRegistry.add(ASTString("float_plus"),GecodeConstraints::p_float_plus);
      _constraintRegistry.add(ASTString("float_max"),GecodeConstraints::p_float_max);
      _constraintRegistry.add(ASTString("float_min"),GecodeConstraints::p_float_min);
      _constraintRegistry.add(ASTString("float_lin_eq"),GecodeConstraints::p_float_lin_eq);
      _constraintRegistry.add(ASTString("float_lin_eq_reif"),GecodeConstraints::p_float_lin_eq_reif);
      _constraintRegistry.add(ASTString("float_lin_le"),GecodeConstraints::p_float_lin_le);
      _constraintRegistry.add(ASTString("float_lin_le_reif"),GecodeConstraints::p_float_lin_le_reif);
#endif
#ifdef GECODE_HAS_MPFR
      _constraintRegistry.add(ASTString("float_acos"),GecodeConstraints::p_float_acos);
      _constraintRegistry.add(ASTString("float_asin"),GecodeConstraints::p_float_asin);
      _constraintRegistry.add(ASTString("float_atan"),GecodeConstraints::p_float_atan);
      _constraintRegistry.add(ASTString("float_cos"),GecodeConstraints::p_float_cos);       
      _constraintRegistry.add(ASTString("float_exp"),GecodeConstraints::p_float_exp);
      _constraintRegistry.add(ASTString("float_ln"),GecodeConstraints::p_float_ln);
      _constraintRegistry.add(ASTString("float_log10"),GecodeConstraints::p_float_log10);
      _constraintRegistry.add(ASTString("float_log2"),GecodeConstraints::p_float_log2);
      _constraintRegistry.add(ASTString("float_sin"),GecodeConstraints::p_float_sin);       
      _constraintRegistry.add(ASTString("float_tan"),GecodeConstraints::p_float_tan);       
#endif		      
    }
    
    
  /*  IntVarArgs GecodeSolverInstance::arg2intvarargs(Expression* arg, int offset) {
        ArrayLit* a = getArrayLit(arg);
        if (a->v().size() == 0) {
            IntVarArgs emptyIa(0);
            return emptyIa;
        }
        IntVarArgs ia(a->v().size()+offset);
        for (int i=offset; i--;)
            ia[i] = IntVar(*this->model, 0, 0);
        for (int i=a->v().size(); i--;) {
            Expression* e = a->v()[i];
            int idx;
            if (e->type().isvar()) {
                ia[i+offset] = model->iv[*(int*)resolveVar(getVarDecl(e))];
            } else {
                int value = e->cast<IntLit>()->v().toInt();
                IntVar iv(*this->model, value, value);
                ia[i+offset] = iv;
            }
        }
        return ia;
    }
    */
}