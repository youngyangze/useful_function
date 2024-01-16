#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma")
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using ll = long long;
using vll = vector<ll>;
using vint = vector<int>;
using matrix = vector<vint>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using dbl = deque<bool>;
using dbltrix = deque<dbl>;
using sint = stack<int>;
using tii = tuple<int, int, int>;
using ordered_set = __gnu_pbds::tree<int, __gnu_pbds::null_type, less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define endl '\n'
#define _CRT_SECURE_NO_WARNINGS
#define all(vec) vec.begin(), vec.end()

const int INF = 0x3f3f3f3f;

class segmentTree {
private:
    vll a, tree;
    int n;

    void init(int node, int start, int end) {
        if (start == end) {
            tree[node] = a[start];
        } else {
            init(node * 2,  start, (start + end) / 2);
            init(node * 2 + 1, (start + end) / 2 + 1, end);
            tree[node] = tree[node * 2]  + tree[node * 2 + 1];
        }
    }

    void update(int node, int start, int end, int index, ll val) {
        if (index < start || index > end) {
            return;
        }
        if (start == end) {
            a[index] = val;
            tree[node] = val;
            return;
        }
        update(node * 2,  start, (start + end) / 2, index, val);
        update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
        tree[node] = tree[node * 2]  + tree[node * 2 + 1];
    }

    ll query(int node, int start, int end, int left, int right) {
        if (left > end || right < start) {
            return 0;
        }
        if (left <= start && end <= right) {
            return tree[node];
        }

        return query(node * 2,  start, (start + end) / 2, left, right) + query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
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

class HLD {
private:
    matrix inp, g;
    vint size, par, depth, top, in, out;
    int pv;

public:
    HLD() {
        pv = 0;
    }

    void addEdge(int s, int e) {
        inp[s].push_back(e); inp[e].push_back(s);
    }

    void dfs(int v, int b = -1) {
        for(auto i : inp[v]) if(i != b) g[v].push_back(i), dfs(i);
    }

    void dfs1(int v) {
        size[v] = 1;
        for(auto &i : g[v]) {
            depth[i] = depth[v] + 1; par[i] = v;
            dfs1(i); size[v] += size[i];
            if(size[i] > size[g[v][0]]) swap(i, g[v][0]);
        }
    }

    void dfs2(int v) {
        in[v] = ++pv;
        for(auto i : g[v]) top[i] = (i == g[v][0]) ? top[v] : i, dfs2(i);
        out[v] = pv;
    }

    void hld(int root) {
        dfs(root); dfs1(root); dfs2(root);
    }

    void updatePath(int u, int v, ll x) {
        for(; top[u]!=top[v]; u=par[top[u]]) {
            if(depth[top[u]] < depth[top[v]]) swap(u, v);
            update(in[top[u]], in[u], x);
        }
        if(depth[u] > depth[v]) swap(u, v);
        update(in[u], in[v], x);
        // if edge query, then update(in[u]+1, in[v], x)
    }

    ll queryPath(int u, int v) {
        ll ret = 0;
        for(; top[u]!=top[v]; u=par[top[u]]) {
            if(depth[top[u]] < depth[top[v]]) swap(u, v);
            ret += query(in[top[u]], in[u]);
        }
        if(depth[u] > depth[v]) swap(u, v);
        ret += query(in[u], in[v]);
        // if edge query, then query(in[u]+1, in[v])
        return ret;
    }
};
