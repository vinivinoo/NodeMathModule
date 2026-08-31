// Node Definition für Integer Math
class ShaderNodeIntegerMathModule : public Module {
public:
  override auto GetFetchInfo() : FetchInfo {
    return {
      constants : {"operation0"},
      input_ports : {"in0", "in1", "in2"},
      output_ports : {"out0"},
    };
  }

  override auto GenerateTokenString() : AbstractToken[] {
    string op_c = GetConstant("operation0");

    // Unary Operations (1 Inputs)
    if (op_c == "ABSOLUTE" || op_c == "SIGN" || op_c == "NEGATE") {
      if (op_c == "NEGATE") {
        return {WildcardToken("out0"), TextToken(" = -"), WildcardToken("in0"),
                TextToken(";")};
      } else {
        string glsl_func = (op_c == "ABSOLUTE") ? "abs(" : "sign(";
        return {WildcardToken("out0"), TextToken(" = " + glsl_func),
                WildcardToken("in0"), TextToken(");")};
      }
    }

    // Ternary Operations (3 Inputs)
    else if (op_c == "MULTIPLY_ADD") {
      return {WildcardToken("out0"), TextToken(" = ("),    WildcardToken("in0"),
              TextToken(" * "),      WildcardToken("in1"), TextToken(") + "),
              WildcardToken("in2"),  TextToken(";")};
    }

    // Binary Functions
    else if (op_c == "MINIMUM" || op_c == "MAXIMUM" || op_c == "POWER" ||
             op_c == "DIVIDE_ROUND" || op_c == "DIVIDE_FLOOR" ||
             op_c == "DIVIDE_CEILING" || op_c == "FLOORED_MODULO" ||
             op_c == "GREATEST_COMMON_DIVISOR" ||
             op_c == "LEAST_COMMON_MULTIPLE") {

      string func_name;

      // Native GLSL Funktionen
      if (op_c == "MINIMUM") {
        func_name = "min";
      } else if (op_c == "MAXIMUM") {
        func_name = "max";
      }

      // TODO: Hilfsfunktionen schreiben
      else if (op_c == "POWER") {
        func_name = "glsl_int_pow";
      } else if (op_c == "DIVIDE_ROUND") {
        func_name = "glsl_idiv_round";
      } else if (op_c == "DIVIDE_FLOOR") {
        func_name = "glsl_idiv_floor";
      } else if (op_c == "DIVIDE_CEILING") {
        func_name = "glsl_idiv_ceil";
      } else if (op_c == "FLOORED_MODULO") {
        func_name = "glsl_floored_modulo";
      } else if (op_c == "GREATEST_COMMON_DIVISOR") {
        func_name = "glsl_gcd";
      } else if (op_c == "LEAST_COMMON_MULTIPLE") {
        func_name = "glsl_lcm";
      }

      return {WildcardToken("out0"), TextToken(" = " + func_name + "("),
              WildcardToken("in0"),  TextToken(", "),
              WildcardToken("in1"),  TextToken(");")};
    }

    // Binary Operations (2 Inputs)
    else {
      string sign;

      if (op_c == "ADD") {
        sign = "+";
      } else if (op_c == "SUBTRACT") {
        sign = "-";
      } else if (op_c == "MULTIPLY") {
        sign = "*";
      } else if (op_c == "DIVIDE") {
        sign = "/";
      } else if (op_c == "MODULO") {
        sign = "%";
      } else {
        sign = "+";
      } // Fallback

      return {WildcardToken("out0"), TextToken(" = "),
              WildcardToken("in0"),  TextToken(" " + sign + " "),
              WildcardToken("in1"),  TextToken(";")};
    }
  }
};
