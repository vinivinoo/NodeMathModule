// Predefined
struct FetchInfo {
  const string[] constants;
  const string[] input_ports;
  const string[] output_ports;
}

class Module {
public
  auto GetFetchInfo() : FetchInfo = delete;

public
  auto GenerateTokenString() : AbstractToken[] = delete;
}

// Node Definition
class ShaderNodeMathModule : public Module {
  override auto GetFetchInfo() : FetchInfo {
    return {
      constants : {"operation0"},
      input_ports : {"in0", "in1"},
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

        return {WildcardToken("out0"), TextToken(" = "),
                WildcardToken("in0"),  TextToken(sign),
                WildcardToken("in1"),  TextToken(";")};
  }
}
