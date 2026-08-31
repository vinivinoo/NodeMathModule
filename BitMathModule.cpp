class ShaderNodeBitwiseModule : public Module {
public:
  override auto GetFetchInfo() : FetchInfo {
    return {
      constants :
          {"operation0"}, // Enum: "AND", "OR", "XOR", "NOT", "SHIFT", "ROTATE"
      input_ports : {"in0", "in1"},
      output_ports : {"out0"},
    };
  }

  override auto GenerateTokenString() : AbstractToken[] {
    string op_c = GetConstant("operation0");

    if (op_c == "NOT") {
      return {WildcardToken("out0"), TextToken(" = ~"), WildcardToken("in0"),
              TextToken(";")};
    }

    if (op_c == "AND" || op_c == "OR" || op_c == "XOR" ||
        op_c == "EXCLUSIVE_OR") {
      string sign;
      if (op_c == "AND")
        sign = "&";
      else if (op_c == "OR")
        sign = "|";
      else
        sign = "^";

      return {WildcardToken("out0"), TextToken(" = "),
              WildcardToken("in0"),  TextToken(" " + sign + " "),
              WildcardToken("in1"),  TextToken(";")};
    }

    // TODO: Komplexe Operationen implementieren/anschauen, wie man es macht
    if (op_c == "SHIFT") {
      return {WildcardToken("out0"), TextToken(" = glsl_shift("),
              WildcardToken("in0"),  TextToken(", "),
              WildcardToken("in1"),  TextToken(");")};
    }

    if (op_c == "ROTATE") {
      return {WildcardToken("out0"), TextToken(" = glsl_rotate("),
              WildcardToken("in0"),  TextToken(", "),
              WildcardToken("in1"),  TextToken(");")};
    }

    // Fallback bei unbekannter Operation
    return {TextToken("/* ERROR: Unknown Bitwise Operation */")};
  }
};
