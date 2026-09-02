class ShaderNodeMixModule : public Module {
 public:
  override auto GetFetchInfo(): FetchInfo {
    return {
      constants: {
        "data_type0",
        "factor_mode0",
        "blend_type0",
        "clamp_factor0",
        "clamp_result0"
      },
      input_ports: {
        "Factor0", "Factor1",
        "A0", "B0",
        "A1", "B1",
        "A2", "B2",
        "A3", "B3"
      },
      output_ports: { "Result0" },
    };
  }

  override auto GenerateTokenString(): AbstractToken[] {
    string dataType    = GetConstant("data_type0");
    string factorMode  = GetConstant("factor_mode0");
    string blendType   = GetConstant("blend_type0");
    string clampFactor = GetConstant("clamp_factor0");
    string clampResult = GetConstant("clamp_result0");

    // Zuordnung der Eingangs-Ports je nach Datentyp
    string portA = "A0";
    string portB = "B0";
    if (dataType == "VECTOR") {
      portA = "A1";
      portB = "B1";
    } else if (dataType == "RGBA") {
      portA = "A2";
      portB = "B2";
    } else if (dataType == "ROTATION") {
      portA = "A3";
      portB = "B3";
    }

    // Auswahl des Factor-Ports (Factor1 wird bei vektoriellen/non-uniform Faktoren verwendet)
    string portFactor = (factorMode == "NON_UNIFORM") ? "Factor1" : "Factor0";

    // Factor-Tokens inklusive optionalem Clamping auf [0.0, 1.0]
    vector<AbstractToken> factorTokens;
    if (clampFactor == "True") {
      factorTokens = {
        TextToken("clamp("),
        WildcardToken(portFactor),
        TextToken(", 0.0, 1.0)")
      };
    } else {
      factorTokens = { WildcardToken(portFactor) };
    }

    vector<AbstractToken> tokens;
    tokens.push_back(WildcardToken("Result0"));
    tokens.push_back(TextToken(" = "));

    if (clampResult == "True") {
      tokens.push_back(TextToken("clamp("));
    }

    // Standard Interpolation (MIX) vs. Farbmischmodi
    if (blendType == "MIX") {
      tokens.push_back(TextToken("mix("));
      tokens.push_back(WildcardToken(portA));
      tokens.push_back(TextToken(", "));
      tokens.push_back(WildcardToken(portB));
      tokens.push_back(TextToken(", "));
      tokens.insert(tokens.end(), factorTokens.begin(), factorTokens.end());
      tokens.push_back(TextToken(")"));
    } else {
      // GLSL-Ausdrücke für erweiterte Blend-Modi: mix(A, Blended(A, B), Factor)
      string prefix = "";
      string infix  = "";
      string suffix = "";

      if (blendType == "DARKEN") {
        prefix = "min("; infix = ", "; suffix = ")";
      } else if (blendType == "LIGHTEN") {
        prefix = "max("; infix = ", "; suffix = ")";
      } else if (blendType == "MULTIPLY") {
        infix = " * ";
      } else if (blendType == "SCREEN") {
        prefix = "(vec4(1.0) - (vec4(1.0) - ";
        infix  = ") * (vec4(1.0) - ";
        suffix = "))";
      } else if (blendType == "DODGE") {
        infix  = " / (vec4(1.0) - ";
        suffix = ")";
      } else if (blendType == "BURN") {
        prefix = "(vec4(1.0) - (vec4(1.0) - ";
        infix  = ") / ";
        suffix = ")";
      }

      tokens.push_back(TextToken("mix("));
      tokens.push_back(WildcardToken(portA));
      tokens.push_back(TextToken(", "));
      
      if (!prefix.empty()) tokens.push_back(TextToken(prefix));
      tokens.push_back(WildcardToken(portA));
      tokens.push_back(TextToken(infix));
      tokens.push_back(WildcardToken(portB));
      if (!suffix.empty()) tokens.push_back(TextToken(suffix));

      tokens.push_back(TextToken(", "));
      tokens.insert(tokens.end(), factorTokens.begin(), factorTokens.end());
      tokens.push_back(TextToken(")"));
    }

    if (clampResult == "True") {
      tokens.push_back(TextToken(", 0.0, 1.0)"));
    }

    tokens.push_back(TextToken(";"));
    return tokens;
  }
};