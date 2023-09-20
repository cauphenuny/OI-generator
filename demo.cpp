// author: ycp | https://ycpedef.github.io
#include "generator.h"
int main() {
    using namespace gen;
    // 生成一个长度为 10，值域为 [-20, 20] 的数组
    auto a = generate_list(10, {-20, 20});//此时 a 的类型是vector<long long>
    // 生成一个长度为 10，值域为 [-20, 20] 的数组，互不重复
    auto b = generate_list(10, {-20, 20}, limits::unique);
    // 生成一个长度为 10，值域为 [-20, 20] 的数组，单调不升
    auto c = generate_list(10, {-20, 20}, limits::decrease);
    // 生成一个长度为 10，值域为 [-20, 20] 的数组，单调递增
    auto d = generate_list(10, {-20, 20}, limits::increase | limits::unique);
    // 在一行输出一个数组
    print(a);
    // 输出多个数组
    print(b, c, d);

    print('\n');

    // 一行输出多个数
    int x = 10, y = -1, z = 5;
    print(x, y, z, '\n');

    print('\n');

    // 生成一颗节点大小为 10 的树，两种方法等价
    tree t1(10);
    auto t2 = generate_tree(10);
    // 加上边权，随机范围[0, 10]
    t2.add_edge_weight({0, 10});
    // 输出
    print(t1, t2);

    print('\n');

    // 生成一个节点数量为 5 的有向无环图
    dag d1(5);
    // 加上点权，随机范围[0, 10]
    d1.add_node_weight({0, 10});
    print(d1); // 默认不输出点权，若要输出，加上一行print(d1.node);

    print('\n');

    using ll = long long;
    // 随机数，值域 [-20, 20]
    ll v1 = randint(-20, 20);
    // 随机数，值域 [0, 10)
    ll v2 = randint(10);
    // 随机数，值域 [-1e12, 1e12]
    ll v3 = randint(-1e12, 1e12);
    print(v1, v2, v3, '\n');
}
