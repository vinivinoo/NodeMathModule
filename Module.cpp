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
