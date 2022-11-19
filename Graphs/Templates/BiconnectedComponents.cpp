int n, m;
cin >> n >> m;
vector<vector<int>> g(n);
for (int i = 0; i < m; i++) {
  int u, v;
  cin >> u >> v;
  --u, --v;
  g[u].push_back(v);
  g[v].push_back(u);
}
int T = 0;
vector<int> in(n, -1), low(n, -1);
stack<pair<int, int>> stk;
vector<vector<int>> biCC;
function<void(int, int)> dfs = [&](int u, int p) {
  in[u] = low[u] = T++;
  bool hasFE = false;
  for (int v : g[u]) {
    if (in[v] == -1) {
      stk.emplace(u, v);
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (p == -1 ? hasFE : in[u] <= low[v]) {
        set<int> s;
        while (true) {
          auto [a, b] = stk.top();
          stk.pop();
          s.insert(a);
          s.insert(b);
          if (a == u && b == v) {
            break;
          }
        }
        biCC.push_back(vector<int>(s.begin(), s.end()));
      }
      hasFE = true;
    } else if (v != p) {
      if (in[v] < in[u]) {
        stk.emplace(u, v);
      }
      low[u] = min(low[u], in[v]);
    }
  }
};
for (int u = 0; u < n; u++) {
  if (in[u] == -1) {
    dfs(u, -1);
    set<int> s;
    while (!stk.empty()) {
      auto [a, b] = stk.top();
      stk.pop();
      s.insert(a);
      s.insert(b);;
    }
    if (!s.empty()) {
      biCC.push_back(vector<int>(s.begin(), s.end()));
    }
  }
}
