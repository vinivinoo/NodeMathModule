class FunctionNodeCompare : public Module {
public:
  override auto GetFetchInfo() : FetchInfo {
    return {
      constants : {"operation0", "data_type0", "mode0"},
      input_ports : {"A0", "B0", // Float
                     "A1", "B1", // Int
                     "A2", "B2", // Vector
                     "A3", "B3", // Color
                     "A4", "B4", // String
                     "C0", "Angle0", "Epsilon0"},
      output_ports : {"Result0"},
    };
  }

  override auto GenerateTokenString() : AbstractToken[] {
    string op = GetConstant("operation0");
    string dt = GetConstant("data_type0");

    // Route correct ports based on data type
    string port_a = "A0";
    string port_b = "B0";

    if (dt == "INT") {
      port_a = "A1";
      port_b = "B1";
    } else if (dt == "VECTOR") {
      port_a = "A2";
      port_b = "B2";
    } else if (dt == "COLOR") {
      port_a = "A3";
      port_b = "B3";
    } else if (dt == "STRING") {
      port_a = "A4";
      port_b = "B4";
    }

    // Edge case: Blender's Float comparisons for EQUAL / NOT_EQUAL use Epsilon
    if (dt == "FLOAT" && (op == "EQUAL" || op == "NOT_EQUAL")) {
      string comp_operator = (op == "EQUAL") ? " <= " : " > ";
      return {WildcardToken("Result0"),
              TextToken(" = abs("),
              WildcardToken(port_a),
              TextToken(" - "),
              WildcardToken(port_b),
              TextToken(")"),
              TextToken(comp_operator),
              WildcardToken("Epsilon0"),
              TextToken(";")};
    }

    // Standard operator configuration
    string infix = " == ";

    if (op == "LESS_THAN") {
      infix = " < ";
    } else if (op == "LESS_EQUAL") {
      infix = " <= ";
    } else if (op == "GREATER_THAN") {
      infix = " > ";
    } else if (op == "GREATER_EQUAL") {
      infix = " >= ";
    } else if (op == "NOT_EQUAL") {
      infix = " != ";
    }

    return {WildcardToken("Result0"), TextToken(" = "),
            WildcardToken(port_a),    TextToken(infix),
            WildcardToken(port_b),    TextToken(";")};
  }
};
