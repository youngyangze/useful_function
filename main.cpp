#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vll = vector<ll>;
using vint = vector<int>;
using matrix = vector<vint>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using sint = stack<int>;
using tii = tuple<int, int, int>;
using base = complex<double>;

#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define endl '\n'
#define _CRT_SECURE_NO_WARNINGS
#define all(vec) vec.begin(), vec.end()

const int INF = 0x3f3f3f3f;
const long double PI = acos(-1);

class segmentTree {
private:
  vll a, tree;
  int n;

  int init(int node, int start, int end) {
      if (start == end) { // 리프 노드라면
          tree[node] = a[start];
      }
      const int mid = (start + end) / 2;
      init(node * 2,  start, mid);
      init(node * 2 + 1, mid + 1, end);

      return tree[node] = tree[node * 2]  + tree[node * 2 + 1];
  }

  ll update(int node, int start, int end, int index, ll val) {
      if (index < start || index > end) {
          return -1;
      }

      const int mid = (start + end) / 2;
      if (start <= index && index <= mid) update(node * 2,  start, mid, index, val);
      else update(node * 2 + 1, mid + 1, end, index, val);
      return tree[node] = tree[node * 2] + tree[node * 2 + 1];
  }

  ll query(int node, int start, int end, int left, int right) {
      if (left > end || right < start) {
          return 0;
      }
      if (left <= start && end <= right) {
          return tree[node];
      }

      const int mid = (start + end) / 2;
      return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
  }

public:
  segmentTree(vll &arr) {
      a = arr;
      n = arr.size();
      tree.resize(4 * n);
      init(1, 0, n - 1);
  }

  void update(int index, ll val) {
      update(1, 0, n - 1, index, val);
  }

  ll query(int left, int right) {
      return query(1, 0, n - 1, left, right);
  }
};

class unions {
	private:
		vint parent;
		int _find(int x) {
			if (parent[x] == x) return x;
        	return parent[x] = _find(parent[x]);
		}
		void _unionParent(int a, int b) {
        	a = _find(a);
        	b = _find(b);
        	if (a < b) parent[b] = a;
        	else parent[a] = b;
    	}
    public:
    	int find(int x) {
    		_find(x);
		}
    	void unionParent(int a, int b) {
			_unionParent(a, b);
		}
		vint getParent() {
			return parent;
		}
};

struct dinic {
    int n;
    matrix capacity, flow;
    vint level, ptr;

    dinic(int n) : n(n), capacity(n, vint(n)), flow(n, vint(n)), level(n), ptr(n) {}

    void add_edge(int from, int to, int cap) {
        capacity[from][to] += cap;
    }

    bool bfs(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        queue<int> que;
        que.push(source);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int v = 0; v < n; v++) {
                if (level[v] < 0 && capacity[u][v] - flow[u][v] > 0) {
                    level[v] = level[u] + 1;
                    que.push(v);
                }
            }
        }
        return level[sink] >= 0;
    }

    int dfs(int u, int sink, int pushed) {
        if (u == sink || pushed == 0) return pushed;
        for (int &v = ptr[u]; v < n; v++) {
            if (level[v] == level[u] + 1 && capacity[u][v] - flow[u][v] > 0) {
                int f = dfs(v, sink, min(pushed, capacity[u][v] - flow[u][v]));
                if (f > 0) {
                    flow[u][v] += f;
                    flow[v][u] -= f;
                    return f;
                }
            }
        }
        return 0;
    }

    ll max_flow(int source, int sink) {
        ll ret = 0;
        while (bfs(source, sink)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(source, sink, numeric_limits<int>::max())) ret += pushed;
        }
        return ret;
    }
};

int main() {
    fastio;

    return 0;
}
