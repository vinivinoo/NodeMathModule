class ShaderNodeClampModule : public Module {
public:
  override auto GetFetchInfo() : FetchInfo {
    return {
      constants : {"clamp_type"},
      input_ports : {"value", "min", "max"},
      output_ports : {"result"},
    };
  }

  override auto GenerateTokenString() : AbstractToken[] {
    string clamp_type = GetConstant("clamp_type");

    // RANGE
    if (clamp_type == "RANGE") {
      return {WildcardToken("result"), TextToken(" = clamp("),
              WildcardToken("value"),  TextToken(", min("),
              WildcardToken("min"),    TextToken(", "),
              WildcardToken("max"),    TextToken("), max("),
              WildcardToken("min"),    TextToken(", "),
              WildcardToken("max"),    TextToken("));")};
    }

    // MINMAX
    return {WildcardToken("result"), TextToken(" = clamp("),
            WildcardToken("value"),  TextToken(", "),
            WildcardToken("min"),    TextToken(", "),
            WildcardToken("max"),    TextToken(");")};
  }
};
