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
vector<pair<int, int>> bridges;
vector<int> artps;
function<void(int, int)> dfs = [&](int u, int p) {
  in[u] = low[u] = T++;
  bool hasFE = false;
  for (int v : g[u]) {
    if (v == p) {
      continue;
    }
    if (in[v] == -1) {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (in[u] < low[v]) {
        bridges.emplace_back(min(u, v), max(u, v));
      }
      if (p == -1 ? hasFE : in[u] <= low[v]) {
        artps.push_back(u);
      }
      hasFE = true;
    } else {
      low[u] = min(low[u], in[v]);
    }
  }
};
for (int u = 0; u < n; u++) {
  if (in[u] == -1) {
    dfs(u, -1);
  }
}
