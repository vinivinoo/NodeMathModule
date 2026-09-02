class ShaderNodeBooleanMathModule : public Module {
  public:
  override auto GetFetchInfo(): FetchInfo {
    return {
      constants: { "operation0" },
      input_ports: { "Boolean0", "Boolean1" },
      output_ports: { "Boolean2" },
    };
  }

  override auto GenerateTokenString(): AbstractToken[] {
    string op = GetConstant("operation0");

    // Single-input operation edge case
    if (op == "NOT") {
      return {
        WildcardToken("Boolean2"), 
        TextToken(" = !"), 
        WildcardToken("Boolean0"), 
        TextToken(";")
      };
    } 

    // Two-input operations configuration
    string prefix = " ";
    string infix  = " && ";
    string suffix = ";";

    if (op == "AND") {
      infix = " && ";
    }
    else if (op == "OR") {
      infix = " || ";
    }
    else if (op == "NAND" || op == "NOT AND") {
      prefix = " !(";
      infix  = " && ";
      suffix = ");";
    }
    else if (op == "NOR") {
      prefix = " !(";
      infix  = " || ";
      suffix = ");";
    }
    else if (op == "XOR" || op == "NOT EQUAL") {
      infix = " != ";
    }
    else if (op == "XNOR" || op == "EQUAL") {
      infix = " == ";
    }
    else if (op == "IMPLY") {
      prefix = " (!";
      infix  = " || ";
      suffix = ");";
    }
    else if (op == "NIMPLY" || op == "SUBTRACT") {
      prefix = " (";
      infix  = " && !";
      suffix = ");";
    }

    return {
      WildcardToken("Boolean2"), 
      TextToken(" =" + prefix), 
      WildcardToken("Boolean0"), 
      TextToken(infix), 
      WildcardToken("Boolean1"), 
      TextToken(suffix)
    };
  }
};