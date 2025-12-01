#include "../include/BinTree.hpp"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

static bool isVerbose() { static int v = getenv("TEST_VERBOSE") ? 1 : 0; return v; }

void run_bintree_test() {
    cout << "===== 开始 BinTree 测试 =====" << endl;
    if (isVerbose()) cout << "构建树并插入节点: 10, 5, 15, 3,7,13,17" << endl;

    BinTree<int> T;
    auto r = T.insertAsRoot(10);
    assert(T.size() == 1);

    auto a = T.insertAsLC(r, 5);
    auto b = T.insertAsRC(r, 15);
    T.insertAsLC(a, 3);
    T.insertAsRC(a, 7);
    T.insertAsLC(b, 13);
    T.insertAsRC(b, 17);

    assert(T.size() == 7);
    if (isVerbose()) cout << "当前树大小 T.size()=" << T.size() << "\n";

    vector<int> v;
    if (isVerbose()) cout << "进行中序遍历..." << endl;
    T.travIn([&](int x){ v.push_back(x); });
    assert((v == vector<int>{3,5,7,10,13,15,17}));

    v.clear();
    if (isVerbose()) cout << "进行先序遍历..." << endl;
    T.travPre([&](int x){ v.push_back(x); });
    assert((v == vector<int>{10,5,3,7,15,13,17}));

    // 测试 remove (删除子树)
    if (isVerbose()) cout << "删除子树 (a) ..." << endl;
    int removed = T.remove(a); // remove subtree rooted at a (3 nodes)
    if (isVerbose()) cout << "删除节点数量: " << removed << " 剩余 T.size()=" << T.size() << "\n";
    assert(removed == 3);
    assert(T.size() == 4);

    // 测试 secede (分离子树)
    if (isVerbose()) cout << "分离子树 b ..." << endl;
    auto sub = T.secede(b); // detach subtree rooted at b (3 nodes)
    assert(sub != nullptr);
    if (isVerbose()) cout << "分离后子树大小 sub->size()=" << sub->size() << " 总树大小 T.size()=" << T.size() << "\n";
    assert(sub->size() == 3);
    assert(T.size() == 1);

    delete sub;

    cout << "===== BinTree 测试通过 =====" << endl << endl;
}
