class ShaderNodeMapRange : public Module {
public:
  override auto GetFetchInfo() : FetchInfo {
    return {
      // Wir holen uns die relevanten Einstellungen der Node
      constants : {"data_type0", "interpolation_type0", "clamp0"},

      // Wir registrieren alle potenziellen Inputs (Float und Vector Varianten)
      input_ports :
          {"Value0", "From Min0", "From Max0", "To Min0", "To Max0", "Steps0",
           "Vector0", "From Min1", "From Max1", "To Min1", "To Max1", "Steps1"},

      // Sowie beide möglichen Outputs
      output_ports : {"Result0", "Vector1"},
    };
  }

  override auto GenerateTokenString() : AbstractToken[] {
    string data_type = GetConstant("data_type0");
    string interp_type = GetConstant("interpolation_type0");
    string clamp = GetConstant("clamp0");

    // Variablen für die Port-Namen (werden je nach Datentyp zugewiesen)
    string val_in, from_min, from_max, to_min, to_max, steps, result_out;

    // Unterscheidung der Ports anhand des Datentyps
    if (data_type == "FLOAT_VECTOR") {
      val_in = "Vector0";
      from_min = "From Min1";
      from_max = "From Max1";
      to_min = "To Min1";
      to_max = "To Max1";
      steps = "Steps1";
      result_out = "Vector1";
    } else {
      // Fallback & Standard ist FLOAT
      val_in = "Value0";
      from_min = "From Min0";
      from_max = "From Max0";
      to_min = "To Min0";
      to_max = "To Max0";
      steps = "Steps0";
      result_out = "Result0";
    }

    // Wir bauen den Namen der Ziel-Funktion dynamisch zusammen
    // z.B. "map_range_linear" oder "map_range_smoothstep_clamp"
    string func_name = "map_range_";

    if (interp_type == "LINEAR") {
      func_name += "linear";
    } else if (interp_type == "STEPPED") {
      func_name += "stepped";
    } else if (interp_type == "SMOOTHSTEP") {
      func_name += "smoothstep";
    } else if (interp_type == "SMOOTHERSTEP") {
      func_name += "smootherstep";
    }

    // Falls Clamping aktiviert ist, fügen wir den Suffix an
    if (clamp == "True") {
      func_name += "_clamp";
    }

    // STEPPED Interpolation ist ein Sonderfall, da hier der "Steps"-Input mit
    // übergeben werden muss
    if (interp_type == "STEPPED") {
      return {WildcardToken(result_out), TextToken(" = " + func_name + "("),
              WildcardToken(val_in),     TextToken(", "),
              WildcardToken(from_min),   TextToken(", "),
              WildcardToken(from_max),   TextToken(", "),
              WildcardToken(to_min),     TextToken(", "),
              WildcardToken(to_max),     TextToken(", "),
              WildcardToken(steps),      TextToken(");")};
    }

    // Für alle anderen Interpolationsarten (ohne den Steps-Parameter)
    return {WildcardToken(result_out), TextToken(" = " + func_name + "("),
            WildcardToken(val_in),     TextToken(", "),
            WildcardToken(from_min),   TextToken(", "),
            WildcardToken(from_max),   TextToken(", "),
            WildcardToken(to_min),     TextToken(", "),
            WildcardToken(to_max),     TextToken(");")};
  }
};
