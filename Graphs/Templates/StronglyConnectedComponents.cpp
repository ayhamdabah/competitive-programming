int n, m;
cin >> n >> m;
vector<vector<int>> g(n);
for (int i = 0; i < m; i++) {
  int u, v;
  cin >> u >> v;
  --u, --v;
  g[u].push_back(v);
}
vector<vector<int>> SCC;
int T = 0;
vector<int> in(n, -1), low(n, -1);
stack<int> stk;
const int INF = 1e9;
function<void(int)> dfs = [&](int u) {
  in[u] = low[u] = T++;
  stk.push(u);
  for (int v : g[u]) {
    if (in[v] == -1) {
      dfs(v);
      low[u] = min(low[u], low[v]);
    } else {
      low[u] = min(low[u], in[v]);
    }
  }
  if (in[u] == low[u]) {
    SCC.push_back({});
    while (true) {
      int v = stk.top();
      stk.pop();
      SCC.back().push_back(v);
      in[v] = INF;
      if (v == u) {
        break;
      }
    }
  }
};
for (int u = 0; u < n; u++) {
  if (in[u] == -1) {
    dfs(u);
  }
}
