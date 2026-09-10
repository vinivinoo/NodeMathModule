class ShaderNodeClamp : public Module {
public:
  override auto GetFetchInfo() : FetchInfo {
    return {
      constants : {"clamp_type0"},
      input_ports : {"Value0", "Min0", "Max0"},
      output_ports : {"Result0"},
    };
  }

  override auto GenerateTokenString() : AbstractToken[] {
    string clamp_type = GetConstant("clamp_type0");

    if (clamp_type == "RANGE") {
      return {WildcardToken("Result0"), TextToken(" = clamp("),
              WildcardToken("Value0"),  TextToken(", min("),
              WildcardToken("Min0"),    TextToken(", "),
              WildcardToken("Max0"),    TextToken("), max("),
              WildcardToken("Min0"),    TextToken(", "),
              WildcardToken("Max0"),    TextToken("));")};
    }

    return {WildcardToken("Result0"), TextToken(" = clamp("),
            WildcardToken("Value0"),  TextToken(", "),
            WildcardToken("Min0"),    TextToken(", "),
            WildcardToken("Max0"),    TextToken(");")};
  }
};
