class FunctionNodeFloatToIntModule : public Module {
public:
  override auto GetFetchInfo() : FetchInfo {
    return {
      constants: {"rounding_mode0"},
      input_ports: {"Float0"},
      output_ports: {"Integer0"},
    };
  }

  override auto GenerateTokenString() : AbstractToken[] {
    string mode = GetConstant("rounding_mode0");
    string func_expr;
    string close_expr;

    if (mode == "ROUND") {
      func_expr = "int(round(";
      close_expr = "));";
    } else if (mode == "FLOOR") {
      func_expr = "int(floor(";
      close_expr = "));";
    } else if (mode == "CEILING" || mode == "CEIL") {
      func_expr = "int(ceil(";
      close_expr = "));";
    } else if (mode == "TRUNCATE" || mode == "TRUNC") {
      func_expr = "int(";
      close_expr = ");";
    } else {
      func_expr = "int(";
      close_expr = ");";
    }

    return {
      WildcardToken("Integer0"),
      TextToken(" = "),
      TextToken(func_expr),
      WildcardToken("Float0"),
      TextToken(close_expr)
    };
  }
};