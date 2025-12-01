#include <ctime>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include "../include/List.hpp"  
#include "../include/ListNode.hpp" 
#include "../include/Vector.hpp"
#include "../include/Stack_and_Quene.hpp"
#include "../include/BinNode.hpp"
#include "../include/BinTree.hpp"

using namespace std;

int main() {
    // 运行所有测试：可通过环境变量 TEST_VERBOSE=1 打开详细中间输出
    run_list_test();
    run_vector_test();
    run_stackqueue_test();
    run_binnode_test();
    run_bintree_test();
    return 0;
}
