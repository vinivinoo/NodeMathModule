class ShaderNodeMathModule : public Module {
  override auto GetFetchInfo() : FetchInfo {
    return {
      constants : {"operation0"},
      input_ports : {"in0", "in1", "in2"},
      output_ports : {"out0"},
    };
  }

  override auto GenerateTokenString() : AbstractToken[] {
    string sign;

    string op_c = GetConstant("operation0");
    if (op_c == "ADD") {
      sign = "+";
    } else if (op_c == "SUB") {
      sign = "-";
    }
    [...]

        return {WildcardToken("value2"), TextToken(" = "),
                WildcardToken("value0"), TextToken(sign),
                WildcardToken("value1"), TextToken(";")};
  }
}
