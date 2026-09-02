class ShaderNodeFloatCurve : public Module {
public:
  override auto GetFetchInfo() : FetchInfo {
    return {
      constants : {},
      input_ports : {"Factor0", "Value0"},
      output_ports : {"Value1"},
    };
  }

  override auto GenerateTokenString() : AbstractToken[] {
    return {WildcardToken("Value1"),  TextToken(" = glsl_float_curve("),
            WildcardToken("Factor0"), TextToken(", "),
            WildcardToken("Value0"),  TextToken(");")};
  }
};
