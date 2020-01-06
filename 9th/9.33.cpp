#include "include.h"


int main(int argc, const char** argv) {
 
    vector<int> ivec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto iter = ivec.begin();
    while (iter != ivec.end()) {
        ++ iter;
        /* iter = */ivec.insert(iter, 42);
        // 调试可以发现 刚开始 iter=2
        // 执行玩insert后=0 失效了
        ++ iter;
    }

    print(ivec);

    while(1);
    return 0;
}