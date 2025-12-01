#include "../include/Vector.hpp"
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

// 运行时是否启用详细输出（通过环境变量 TEST_VERBOSE=1 控制）
static bool isVerbose() {
    static int v = getenv("TEST_VERBOSE") ? 1 : 0;
    return v;
}

namespace {
void testConstructor() {
    if (isVerbose()) cout << "运行构造函数测试..." << endl;
    Vector<int> vec1;
    if (isVerbose()) cout << "vec1 初始: 大小=" << vec1.size() << '\n';
    assert(vec1.size() == 0);

    Vector<int> vec2(10, 5, 1);
    if (isVerbose()) {
        cout << "vec2 初始化 (容量=10, 大小=5, 值=1): ";
        for (int i = 0; i < vec2.size(); ++i) cout << vec2[i] << ' ';
        cout << '\n';
    }
    assert(vec2.size() == 5);
    for (int i = 0; i < vec2.size(); ++i) {
        assert(vec2[i] == 1);
    }

    int arr[] = {1, 2, 3, 4, 5};
    Vector<int> vec3(arr, 5);
    if (isVerbose()) {
        cout << "vec3 从数组构造: ";
        for (int i = 0; i < vec3.size(); ++i) cout << vec3[i] << ' ';
        cout << '\n';
    }
    assert(vec3.size() == 5);
    for (int i = 0; i < vec3.size(); ++i) {
        assert(vec3[i] == arr[i]);
    }

    if (isVerbose()) cout << "通过!" << endl;
}

void testInsert() {
    if (isVerbose()) cout << "运行插入操作测试..." << endl;
    Vector<int> vec;
    if (isVerbose()) cout << "插入前 vec: 大小=" << vec.size() << '\n';
    vec.insert(0, 10);
    vec.insert(1, 20);
    vec.insert(1, 15);
    assert(vec.size() == 3);
    assert(vec[0] == 10);
    assert(vec[1] == 15);
    assert(vec[2] == 20);

    vec.insert(25);
    if (isVerbose()) {
        cout << "插入后 vec 内容: ";
        for (int i = 0; i < vec.size(); ++i) cout << vec[i] << ' ';
        cout << '\n';
    }
    assert(vec.size() == 4);
    assert(vec[3] == 25);

    if (isVerbose()) cout << "通过!" << endl;
}

void testRemove() {
    if (isVerbose()) cout << "运行删除操作测试..." << endl;
    Vector<int> vec;
    if (isVerbose()) cout << "构造查找/搜索测试 vec 初始 (空)" << '\n';
    vec.insert(10);
    vec.insert(20);
    vec.insert(30);

    assert(vec.remove(1) == 20);
    assert(vec.size() == 2);
    assert(vec[0] == 10);
    assert(vec[1] == 30);

    vec.remove(0, 2);
    assert(vec.size() == 0);

    if (isVerbose()) cout << "通过!" << endl;
}

void testFindAndSearch() {
    if (isVerbose()) cout << "运行查找操作测试..." << endl;
    Vector<int> vec;
    vec.insert(10);
    vec.insert(20);
    vec.insert(30);

    assert(vec.find(20) == 1);
    assert(vec.find(40) == -1);

    vec.bubbleSort();
    if (isVerbose()) {
        cout << "冒泡排序之后: ";
        for (int i = 0; i < vec.size(); ++i) cout << vec[i] << ' ';
        cout << '\n';
    }
    assert(vec.binSearch(20, 0, vec.size()) == 1);
    assert(vec.binSearch(40, 0, vec.size()) == -1);

    if (isVerbose()) cout << "通过!" << endl;
}

void testSort() {
    if (isVerbose()) cout << "运行排序操作测试..." << endl;
    Vector<int> vec;
    if (isVerbose()) cout << "构造排序测试 vec 初始 (大小=" << vec.size() << ")" << '\n';
    vec.insert(30);
    vec.insert(10);
    vec.insert(20);

    vec.bubbleSort();
    if (isVerbose()) cout << "冒泡排序结果: " << vec[0] << ',' << vec[1] << ',' << vec[2] << '\n';
    assert(vec[0] == 10);
    assert(vec[1] == 20);
    assert(vec[2] == 30);

    vec.insert(25);
    vec.selectionSort();
    if (isVerbose()) cout << "选择排序结果: ";
    if (isVerbose()) for (int i = 0; i < vec.size(); ++i) cout << vec[i] << ' ';
    if (isVerbose()) cout << '\n';
    assert(vec[0] == 10);
    assert(vec[1] == 20);
    assert(vec[2] == 25);
    assert(vec[3] == 30);

    vec.insert(5);
    vec.insertionSort();
    if (isVerbose()) cout << "插入排序结果: ";
    if (isVerbose()) for (int i = 0; i < vec.size(); ++i) cout << vec[i] << ' ';
    if (isVerbose()) cout << '\n';
    assert(vec[0] == 5);
    assert(vec[1] == 10);
    assert(vec[2] == 20);
    assert(vec[3] == 25);
    assert(vec[4] == 30);

    vec.mergeSort();
    if (isVerbose()) cout << "归并排序结果: ";
    if (isVerbose()) for (int i = 0; i < vec.size(); ++i) cout << vec[i] << ' ';
    if (isVerbose()) cout << '\n';
    assert(vec[0] == 5);
    assert(vec[4] == 30);

    if (isVerbose()) cout << "通过!" << endl;
}

void testUnique() {
    if (isVerbose()) cout << "运行唯一化操作测试..." << endl;
    Vector<int> vec;
    if (isVerbose()) cout << "构造唯一化测试 vec 初始" << '\n';
    vec.insert(10);
    vec.insert(10);
    vec.insert(20);
    vec.insert(20);

    assert(vec.deduplicate() == 2);
    assert(vec.size() == 2);

    vec.insert(30);
    vec.insert(30);
    vec.uniquify();
    assert(vec.size() == 3);

    if (isVerbose()) cout << "通过!" << endl;
}

void testUnsortAndTraverse() {
    if (isVerbose()) cout << "运行置乱和遍历操作测试..." << endl;
    Vector<int> vec;
    if (isVerbose()) cout << "构造置乱与遍历测试 vec 初始" << '\n';
    vec.insert(10);
    vec.insert(20);
    vec.insert(30);

    vec.unsort();
    if (isVerbose()) {
        cout << "置乱后: ";
        for (int i = 0; i < vec.size(); ++i) cout << vec[i] << ' ';
        cout << '\n';
    }
    assert(vec.size() == 3);

    vec.traverse([](int& e) { e *= 2; });
    assert(vec[0] % 2 == 0);
    assert(vec[1] % 2 == 0);
    assert(vec[2] % 2 == 0);

    if (isVerbose()) cout << "通过!" << endl;
}

} // end anonymous namespace

void run_vector_test() {
    cout << "\n===== 开始 向量 测试 =====" << endl;

    testConstructor();
    testInsert();
    testRemove();
    testFindAndSearch();
    testSort();
    testUnique();
    testUnsortAndTraverse();

    cout << "===== 向量 测试通过 =====" << endl;
}
