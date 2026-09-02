class FunctionNodeBitMath : public Module {
public:
  override auto GetFetchInfo() : FetchInfo {
    return {
      constants : {"operation0"},
      input_ports : {"A0", "B0", "Shift0"},
      output_ports : {"Value0"},
    };
  }

  override auto GenerateTokenString() : AbstractToken[] {
    string op_c = GetConstant("operation0");

    switch (op_c) {
    case "NOT":
      return {WildcardToken("Value0"), TextToken(" = ~"), WildcardToken("A0"),
              TextToken(";")};

    case "AND":
    case "OR":
    case "XOR": {
      string sign;
      if (op_c == "AND") {
        sign = "&";
      } else if (op_c == "OR") {
        sign = "|";
      } else {
        sign = "^";
      }

      return {WildcardToken("Value0"), TextToken(" = "),
              WildcardToken("A0"),     TextToken(" " + sign + " "),
              WildcardToken("B0"),     TextToken(";")};
    }

    // TODO: implement Helper Functions
    case "SHIFT":
      return {WildcardToken("Value0"), TextToken(" = glsl_shift("),
              WildcardToken("A0"),     TextToken(", "),
              WildcardToken("Shift0"), TextToken(");")};

    case "ROTATE":
      return {WildcardToken("Value0"), TextToken(" = glsl_rotate("),
              WildcardToken("A0"),     TextToken(", "),
              WildcardToken("Shift0"), TextToken(");")};

    default:
      return {TextToken("/* ERROR: Unknown Bitwise Operation */")};
    }
  }
};
