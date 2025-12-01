#include "../include/BinNode.hpp"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

static bool isVerbose() { static int v = getenv("TEST_VERBOSE") ? 1 : 0; return v; }

void run_binnode_test() {
    cout << "===== 开始 BinNode 测试 =====" << endl;
    if (isVerbose()) cout << "构建根节点 10 并插入左右子节点 5,15" << endl;

    // 简单插入与 size
    BinNode<int> root(10);
    auto left = root.insertAsLC(5);
    auto right = root.insertAsRC(15);
    assert(root.size() == 3);

    // 测试 succ (中序后继)
    if (isVerbose()) cout << "left->succ() == " << left->succ()->data << " root.succ() == " << root.succ()->data << "\n";
    assert(left->succ()->data == 10);
    assert(root.succ()->data == 15);
    assert(right->succ() == nullptr);

    // 测试遍历输出
    vector<int> v;
    if (isVerbose()) cout << "中序遍历收集结果..." << endl;
    root.travIn([&v](int x){ v.push_back(x); });
    assert((v == vector<int>{5, 10, 15}));

    v.clear();
    if (isVerbose()) cout << "先序遍历收集结果..." << endl;
    root.travPre([&v](int x){ v.push_back(x); });
    assert((v == vector<int>{10,5,15}));

    v.clear();
    if (isVerbose()) cout << "后序遍历收集结果..." << endl;
    root.travPost([&v](int x){ v.push_back(x); });
    assert((v == vector<int>{5,15,10}));

    cout << "===== BinNode 测试通过 =====" << endl << endl;
}
