// Node Definition für den GESAMTEN Boolean Math Node
class ShaderNodeBooleanMathModule : public Module {
  public:
  override auto GetFetchInfo(): FetchInfo {
    return {
      constants: { "operation0" }, // Enum aus Blender
      input_ports: { "boolean0", "boolean1" },
      output_ports: { "boolean2" },
    };
  }

  override auto GenerateTokenString(): AbstractToken[] {
    string op_c = GetConstant("operation0");

    // (NOT) 1 Input - Sonderfall
    if (op_c == "NOT") {
      return {
        WildcardToken("boolean2"), 
        TextToken(" = !"), 
        WildcardToken("boolean0"), 
        TextToken(";")
      };
    } 
    // Alle 2-Input Operationen
    else {
      string prefix = " ";
      string infix = " ";
      string suffix = ";";

      if (op_c == "AND") { 
        infix = " && "; 
      }
      else if (op_c == "OR") { 
        infix = " || "; 
      }
      else if (op_c == "NOT AND") { // NAND: !(A && B)
        prefix = " !(";
        infix  = " && ";
        suffix = ");";
      }
      else if (op_c == "NOR") { // NOR: !(A || B)
        prefix = " !(";
        infix  = " || ";
        suffix = ");";
      }
      else if (op_c == "EQUAL") { // EQUAL (XNOR): A == B
        infix = " == ";
      }
      else if (op_c == "NOT EQUAL") { // NOT EQUAL (XOR): A != B
        infix = " != ";
      }
      else if (op_c == "IMPLY") { // IMPLY: !A || B
        prefix = " (!";
        infix  = " || ";
        suffix = ");";
      }
      else if (op_c == "SUBTRACT") { // SUBTRACT: A && !B
        prefix = " (";
        infix  = " && !";
        suffix = ");";
      }

      return {
        WildcardToken("boolean2"), 
        TextToken(" =" + prefix), 
        WildcardToken("boolean0"), 
        TextToken(infix), 
        WildcardToken("boolean1"), 
        TextToken(suffix)
      };
    }
  }
};