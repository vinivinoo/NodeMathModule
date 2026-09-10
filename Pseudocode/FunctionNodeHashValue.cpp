class FunctionNodeHashValue : public Module {
public:
  override auto GetFetchInfo() : FetchInfo {
    return {
      constants : {"data_type0"},
      input_ports : {"Value0", "Seed0"},
      output_ports : {"Hash0"},
    };
  }

  override auto GenerateTokenString() : AbstractToken[] {
    string data_type = GetConstant("data_type0");

    switch (data_type) {
    case "STRING":
      return {WildcardToken("Hash0"), TextToken(" = 0.0;")};

    case "INT":
      return {WildcardToken("Hash0"),  TextToken(" = glsl_hash_int("),
              WildcardToken("Value0"), TextToken(", "),
              WildcardToken("Seed0"),  TextToken(");")};

    case "VECTOR":
      return {WildcardToken("Hash0"),  TextToken(" = glsl_hash_vector("),
              WildcardToken("Value0"), TextToken(", "),
              WildcardToken("Seed0"),  TextToken(");")};

    case "RGBA":
      return {WildcardToken("Hash0"),  TextToken(" = glsl_hash_rgba("),
              WildcardToken("Value0"), TextToken(", "),
              WildcardToken("Seed0"),  TextToken(");")};

    case "ROTATION":
      return {WildcardToken("Hash0"),  TextToken(" = glsl_hash_rotation("),
              WildcardToken("Value0"), TextToken(", "),
              WildcardToken("Seed0"),  TextToken(");")};

    case "MATRIX":
      return {WildcardToken("Hash0"),  TextToken(" = glsl_hash_matrix("),
              WildcardToken("Value0"), TextToken(", "),
              WildcardToken("Seed0"),  TextToken(");")};

    case "FLOAT":
    default:
      return {WildcardToken("Hash0"),  TextToken(" = glsl_hash_float("),
              WildcardToken("Value0"), TextToken(", "),
              WildcardToken("Seed0"),  TextToken(");")};
    }
  }
};
