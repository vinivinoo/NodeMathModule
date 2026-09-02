class FunctionNodeIntegerMath : public Module {
public:
  override auto GetFetchInfo() : FetchInfo {
    return {
      constants : {"operation0"},
      input_ports : {"Value0", "Value1", "Value2"},
      output_ports : {"Value3"},
    };
  }

  override auto GenerateTokenString() : AbstractToken[] {
    string op_c = GetConstant("operation0");

    switch (op_c) {
    case "ABSOLUTE":
    case "SIGN": {
      string glsl_func = (op_c == "ABSOLUTE") ? "abs(" : "sign(";
      return {WildcardToken("Value3"), TextToken(" = " + glsl_func),
              WildcardToken("Value0"), TextToken(");")};
    }

    case "NEGATE":
      return {WildcardToken("Value3"), TextToken(" = -"),
              WildcardToken("Value0"), TextToken(";")};

    case "MULTIPLY_ADD":
      return {WildcardToken("Value3"), TextToken(" = ("),
              WildcardToken("Value0"), TextToken(" * "),
              WildcardToken("Value1"), TextToken(") + "),
              WildcardToken("Value2"), TextToken(";")};

    case "MINIMUM":
    case "MAXIMUM":
    case "POWER":
    case "DIVIDE_ROUND":
    case "DIVIDE_FLOOR":
    case "DIVIDE_CEIL":
    case "FLOORED_MODULO":
    case "MODULO":
    case "GCD":
    case "LCM": {
      string func_name;
      if (op_c == "MINIMUM") {
        func_name = "min";
      } else if (op_c == "MAXIMUM") {
        func_name = "max";
      } else if (op_c == "POWER") {
        func_name = "glsl_int_pow";
      } else if (op_c == "DIVIDE_ROUND") {
        func_name = "glsl_idiv_round";
      } else if (op_c == "DIVIDE_FLOOR") {
        func_name = "glsl_idiv_floor";
      } else if (op_c == "DIVIDE_CEIL") {
        func_name = "glsl_idiv_ceil";
      } else if (op_c == "FLOORED_MODULO") {
        func_name = "glsl_floored_modulo";
      } else if (op_c == "MODULO") {
        func_name = "glsl_modulo";
      } else if (op_c == "GCD") {
        func_name = "glsl_gcd";
      } else {
        func_name = "glsl_lcm";
      }

      return {WildcardToken("Value3"), TextToken(" = " + func_name + "("),
              WildcardToken("Value0"), TextToken(", "),
              WildcardToken("Value1"), TextToken(");")};
    }

    case "ADD":
    case "SUBTRACT":
    case "MULTIPLY":
    case "DIVIDE": {
      string sign;
      if (op_c == "ADD") {
        sign = "+";
      } else if (op_c == "SUBTRACT") {
        sign = "-";
      } else if (op_c == "MULTIPLY") {
        sign = "*";
      } else {
        sign = "/";
      }

      return {WildcardToken("Value3"), TextToken(" = "),
              WildcardToken("Value0"), TextToken(" " + sign + " "),
              WildcardToken("Value1"), TextToken(";")};
    }

    default:
      return {TextToken("/* ERROR: Unknown Integer Math Operation */")};
    }
  }
};
