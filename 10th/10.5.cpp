/*
在本节对名册（roster）调用equal的例子中，如果两个名册中保存的都是c风格字符串而不是string，会发生什么？

答案: 比较的是迭代器指的地址在使用char* 的类型

equal使用==运算符比较两个序列中的元素。string类重载了==，可比较两个字符串是否长度相等且其中元素对位相等。
而C风格字符串本质是char *类型，用==比较两个char *对象，只是检查两个指针值是否相等，即地址是否相等，而不会比较其中字符是否相同。
所以，只有当两个序列中的指针都指向相同的地址时，equal才会返回true，否则，即使字符串内容完全相同，也会返回false。

原文链接：https://blog.csdn.net/sunhero2010/article/details/49803965


For such case, std::equal is going to compare the address value rather than the string value.
 So the result is not the same as std::string. Try to avoid coding this way.
*/

#include "include.h"

void printAddr(const char *addr)
{
    unsigned int a;

    for (int i = 0; i < 6; i++)
    {
        a = (*(addr + i)) & 0xff;
        cout << a << "  ";
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    // const char *s1 = "123456789";
    // const char *s2 = "123456789111111";
    // auto ret = equal(begin(s1), end(s1), begin(s2));
    // cout << ret << endl;

    std::vector<const char *> roster1{"Mooophy", "pezy", "Queequeg"};
    std::list<const char *> roster2{"Mooophy", "pezy", "Queequeg", "shbling", "evan617"};
    std::cout << boolalpha << std::equal(roster1.cbegin(), roster1.cend(), roster2.cbegin()) << endl;

    const char a[3][2] = {"A", "B", "C"};
    const char b[3][2] = {"A", "B", "C"};

    std::vector<const char *> v1(std::begin(a), std::end(a));
    std::list<const char *> v2(std::begin(b), std::end(b));

    cout << "a=" << begin(a) << "----" << end(a) << endl;
    printAddr((const char *)&(*begin(a)));
    cout << "b=" << begin(b) << "----" << end(b) << endl;
    printAddr((const char *)&(*begin(b)));

    std::cout << std::boolalpha
              << std::equal(v1.cbegin(), v1.cend(), v2.cbegin()) << std::endl;

    cout << "v1_address=" << &*v1.begin() << "----" << &*v1.end() << endl;
    cout << "v2_address=" << &*v2.begin() << "----" << &*v2.end() << endl;
    printAddr((const char *)&(*v1.begin()));
    printAddr((const char *)&(*v2.begin()));

    vector<string> v3{"A", "B", "C"};
    vector<string> v4{"A", "B", "C"};

    cout << "v3_address=" << &*v3.begin() << "----" << &*v3.end() << endl;
    cout << "v4_address=" << &*v4.begin() << "----" << &*v4.end() << endl;
    printAddr((const char *)&(*v3.begin()));
    printAddr((const char *)&(*v4.begin()));
    std::cout << std::boolalpha
              << std::equal(v3.cbegin(), v3.cend(), v4.cbegin()) << std::endl;

    while (1)
        ;
    return 0;
}
