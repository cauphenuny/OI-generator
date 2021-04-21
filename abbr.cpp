// author: ycp | https://ycpedef.github.io
#include "generator.h"
int main() {

    using namespace gen_abbr;

    auto a = gl(10, {-20, 20});
    auto b = gl(10, {-20, 20}, lmt::unq);
    auto c = gl(10, {-20, 20}, lmt::dec);
    auto d = gl(10, {-20, 20}, lmt::inc | lmt::unq);

    pr(a), pr(b, c, d);

    int x = 10, y = -1, z = 5;
    pr(x, y, '\n');

    tree t1(10);
    auto t2 = grt(10);
    tree t3(10, {-20, 20});
    auto t4 = grt(10, {-20, 20});
    tree t5(10, {-20, 20}, lmt::unq);
    auto t6 = grt(10, {-20, 20}, lmt::unq);
    pr(t1, t2, t3, t4, t5, t6);

    using ll = long long;
    ll v1 = ri(-20, 20);
    ll v2 = ri(10);
    ll v3 = ri(-1e12, 1e12);
    print(v1, v2, v3, '\n');

    return 0;
}

