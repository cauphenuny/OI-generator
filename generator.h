//author: ycp | https://ycpedef.github.io
//type: generator
#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

namespace gen {

using namespace std;

using T = long long;

#define endline() putchar('\n')

void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    T y = 10, len = 1;
    while (y <= x) y *= 10, len++;
    while (len--) y /= 10, putchar(x / y + 48), x %= y;
}

void print(const T& x) {
    write(x), putchar(' ');
}

void print(const vector<T>& a) {
    for (auto i : a) print(i);
    endline();
}

void println(const T& x) {
    write(x), endline();
}

template<typename T>
void print(const initializer_list<T>& a, char end = '\0') {
    for (auto i : a) print(i);
    putchar(end);
}

struct range {
    T l, r;
    T size() const { return r - l + 1; }
    range(const T& x) { l = 0, r = x; }
    range(const T& _l, const T& _r) { l = _l, r = _r; }
    range(const initializer_list<T>& a) {
        l = *(a.begin());
        r = *(next(a.begin()));
    }
};

mt19937 rnd((random_device())());

T randint(const range& a) {
    uniform_int_distribution<T> distrib(a.l, a.r);
    return distrib(rnd);
}
T randint(T l, T r) {
    return randint(range(l, r));
}

// ======================================================== List =========================================================

namespace limits {
const int unique = 1 << 1;
const int decrease = 1 << 2;
const int increase = 1 << 3;
}  // namespace limits

vector<T> generate_list(const int&, const range&, int = 0);
vector<T> generate_list(const int&, function<T(const vector<T>&)>);
vector<T> generate_increase_list(const int&, const range&);
vector<T> generate_decrease_list(const int&, const range&);
vector<T> generate_unique_list(const int&, const range&);
vector<T> generate_non_decrease_list(const int&, const range&);
vector<T> generate_non_increase_list(const int&, const range&);

vector<T> generate_list(const int& size, const range& a, int extra) {
    assert(size > 0);
    if (extra & limits::decrease) {
        if (extra & limits::unique)
            return generate_decrease_list(size, a);
        else
            return generate_non_increase_list(size, a);
    }
    if (extra & limits::increase) {
        if (extra & limits::unique)
            return generate_increase_list(size, a);
        else
            return generate_non_decrease_list(size, a);
    }
    if (extra & limits::unique) {
        return generate_unique_list(size, a);
    }
    vector<T> res;
    uniform_int_distribution<T> distrib(a.l, a.r);
    for (int i = 0; i < size; i++) { res.push_back(distrib(rnd)); }
    return res;
}

vector<T> generate_list(const int& size, function<T(const vector<T>&)> generate) {
    assert(size > 0);
    vector<T> res;
    for (int i = 0; i < size; i++) { res.push_back(generate(res)); }
    return res;
}

vector<T> generate_increase_list(const int& size, const range& val) {
    assert(val.size() >= size);
    auto generate = [val, size](const vector<T>& cur) -> T {
        T prev;
        if (cur.size())
            prev = cur[cur.size() - 1];
        else
            prev = val.l - 1;
        T l = prev + 1;
        T r = max(prev + 1, val.l + (T)(((cur.size() + 2) * 1.0 / size) * (val.r - val.l)));
        r = min(r, (T)(val.r - (size - cur.size() - 1)));
        return randint(l, r);
    };
    vector<T> res = generate_list(size, generate);
    return res;
}

vector<T> generate_decrease_list(const int& size, const range& val) {
    vector<T> res = generate_increase_list(size, val);
    reverse(res.begin(), res.end());
    return res;
}

vector<T> generate_non_decrease_list(const int& size, const range& val) {
    vector<T> res = generate_list(size, val);
    sort(res.begin(), res.end());
    return res;
}

vector<T> generate_non_increase_list(const int& size, const range& val) {
    vector<T> res = generate_non_decrease_list(size, val);
    reverse(res.begin(), res.end());
    return res;
}

vector<T> generate_unique_list(const int& size, const range& val) {
    vector<T> res = generate_increase_list(size, val);
    shuffle(res.begin(), res.end(), default_random_engine((random_device())()));
    return res;
}

// ======================================================== Graph =======================================================

struct edge {
    int from, to;
    T val;
    edge(int x, int y, T v = 0) : from(x),
                                  to(y),
                                  val(v) {}
};

class non_directed_graph {
public:
    bool has_edge_val, has_node_val;
    int n, m;
    vector<edge> edges;
    vector<T> node;
};

class directed_graph {
public:
    bool has_edge_val, has_node_val;
    int n, m;
    vector<edge> edges;
    vector<T> node;
};

class tree : public non_directed_graph {
public:
    tree();
    tree(const int& size);
    tree(const int& size, const range&, int extra);
};

class dag : public directed_graph {
public:
    dag();
    dag(const int& size);
    dag(const int& size, const range&, int extra);
};

tree generate_random_tree(const int&);
tree generate_random_tree(const int&, const range&, int extra);

tree generate_random_tree(const int& size) {
    tree res;
    res.n = size;
    res.has_edge_val = 0;
    for (int i = 2; i <= size; i++) {
        int j = randint(1, i - 1);
        res.edges.push_back(edge(j, i));
    }
    return res;
}

tree generate_random_tree(const int& size, const range& val_range, int extra = 0) {
    tree res = generate_random_tree(size);
    res.has_edge_val = 1;
    auto edge_val = generate_list(size - 1, val_range, extra);
    for (int i = 0; i < size - 1; i++) {
        res.edges[i].val = edge_val[i];
    }
    return res;
}

tree::tree() {
    has_edge_val = n = 0;
}

tree::tree(const int& size) {
    auto t = generate_random_tree(size);
    has_edge_val = t.has_edge_val, n = t.n;
    edges = t.edges;
}

tree::tree(const int& size, const range& val_range, int extra = 0) {
    auto t = generate_random_tree(size, val_range, extra);
    has_edge_val = t.has_edge_val, n = t.n;
    edges = t.edges;
}

void print(tree t) {
    println(t.n);
    shuffle(t.edges.begin(), t.edges.end(), default_random_engine((random_device())()));
    for (auto e : t.edges) {
        if (randint({0, 1})) swap(e.from, e.to);
        if (t.has_edge_val)
            print(e.from), print(e.to), println(e.val);
        else
            print(e.from), println(e.to);
    }
}

} // namespace gen
