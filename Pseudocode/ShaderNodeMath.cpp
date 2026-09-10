class ShaderNodeMath : public Module {
public:
  override auto GetFetchInfo() : FetchInfo {
    return {
      constants : {"operation0", "use_clamp0"},
      input_ports : {"Value0", "Value1", "Value2"},
      output_ports : {"Value3"},
    };
  }

  override auto GenerateTokenString() : AbstractToken[] {
    string op = GetConstant("operation0");
    bool use_clamp = (GetConstant("use_clamp0") == "True");

    AbstractToken[] expr;

    // Direct Arithmetic Operations
    if (op == "ADD") {
      expr = {WildcardToken("Value0"), TextToken(" + "),
              WildcardToken("Value1")};
    } else if (op == "SUBTRACT") {
      expr = {WildcardToken("Value0"), TextToken(" - "),
              WildcardToken("Value1")};
    } else if (op == "MULTIPLY") {
      expr = {WildcardToken("Value0"), TextToken(" * "),
              WildcardToken("Value1")};
    } else if (op == "DIVIDE") {
      expr = {WildcardToken("Value0"), TextToken(" / "),
              WildcardToken("Value1")};
    } else if (op == "MULTIPLY_ADD") {
      expr = {WildcardToken("Value0"), TextToken(" * "),
              WildcardToken("Value1"), TextToken(" + "),
              WildcardToken("Value2")};
    }
    // Power & Logarithmic
    else if (op == "POWER") {
      expr = {TextToken("pow("), WildcardToken("Value0"), TextToken(", "),
              WildcardToken("Value1"), TextToken(")")};
    } else if (op == "LOGARITHM") {
      expr = {TextToken("log("), WildcardToken("Value0"), TextToken(") / log("),
              WildcardToken("Value1"), TextToken(")")};
    } else if (op == "SQRT") {
      expr = {TextToken("sqrt("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "INVERSE_SQRT") {
      expr = {TextToken("inversesqrt("), WildcardToken("Value0"),
              TextToken(")")};
    } else if (op == "EXPONENT") {
      expr = {TextToken("exp("), WildcardToken("Value0"), TextToken(")")};
    }
    // Comparison & Min/Max
    else if (op == "MINIMUM") {
      expr = {TextToken("min("), WildcardToken("Value0"), TextToken(", "),
              WildcardToken("Value1"), TextToken(")")};
    } else if (op == "MAXIMUM") {
      expr = {TextToken("max("), WildcardToken("Value0"), TextToken(", "),
              WildcardToken("Value1"), TextToken(")")};
    } else if (op == "LESS_THAN") {
      expr = {TextToken("float("), WildcardToken("Value0"), TextToken(" < "),
              WildcardToken("Value1"), TextToken(")")};
    } else if (op == "GREATER_THAN") {
      expr = {TextToken("float("), WildcardToken("Value0"), TextToken(" > "),
              WildcardToken("Value1"), TextToken(")")};
    } else if (op == "COMPARE") {
      expr = {TextToken("float(abs("), WildcardToken("Value0"),
              TextToken(" - "),        WildcardToken("Value1"),
              TextToken(") <= "),      WildcardToken("Value2"),
              TextToken(")")};
    }
    // Rounding & Modulo
    else if (op == "ABSOLUTE") {
      expr = {TextToken("abs("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "SIGN") {
      expr = {TextToken("sign("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "FLOOR") {
      expr = {TextToken("floor("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "CEIL") {
      expr = {TextToken("ceil("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "FRACT") {
      expr = {TextToken("fract("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "TRUNC") {
      expr = {TextToken("trunc("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "ROUND") {
      expr = {TextToken("floor("), WildcardToken("Value0"),
              TextToken(" + 0.5)")};
    } else if (op == "MODULO" || op == "FLOORED_MODULO") {
      expr = {TextToken("mod("), WildcardToken("Value0"), TextToken(", "),
              WildcardToken("Value1"), TextToken(")")};
    } else if (op == "SNAP") {
      expr = {TextToken("floor("), WildcardToken("Value0"),
              TextToken(" / "),    WildcardToken("Value1"),
              TextToken(") * "),   WildcardToken("Value1")};
    }
    // Trigonometry
    else if (op == "SINE") {
      expr = {TextToken("sin("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "COSINE") {
      expr = {TextToken("cos("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "TANGENT") {
      expr = {TextToken("tan("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "ARCSINE") {
      expr = {TextToken("asin("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "ARCCOSINE") {
      expr = {TextToken("acos("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "ARCTANGENT") {
      expr = {TextToken("atan("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "ARCTAN2") {
      expr = {TextToken("atan("), WildcardToken("Value0"), TextToken(", "),
              WildcardToken("Value1"), TextToken(")")};
    } else if (op == "SINH") {
      expr = {TextToken("sinh("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "COSH") {
      expr = {TextToken("cosh("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "TANH") {
      expr = {TextToken("tanh("), WildcardToken("Value0"), TextToken(")")};
    } else if (op == "RADIANS") {
      expr = {TextToken("radians("), WildcardToken("Value0"), TextToken(")")};
    } else {
      expr = {WildcardToken("Value0")};
    }

    // Assemble assignment and apply optional clamp
    AbstractToken[] result = {WildcardToken("Value3"), TextToken(" = ")};

    if (use_clamp) {
      result.append(TextToken("clamp("));
      result.append(expr);
      result.append(TextToken(", 0.0, 1.0);"));
    } else {
      result.append(expr);
      result.append(TextToken(";"));
    }

    return result;
  }
};
