// #include <iostream>
#include <vector>
using namespace std;

struct X
{
    X() { std::cout << "X()" << std::endl; }
    X(const X &) { std::cout << "X(const X&)" << std::endl; }

    // 拷贝赋值
    X &operator=(const X &s) { cout << "X& operator=(const X& s)" << endl; }
    // 析构函数
    ~X() { cout << "~X()" << endl; }
};

void test(const X &ref_x, const X real_x)
{
    X x1, x2; //构造函数
    cout << "I think it will call X(const X &)" << endl;
    X x3(x2); //拷贝构造
    cout << "I think it will call X& operator=(const X& s)" << endl;
    x1 = x2; // 拷贝赋值

    cout << "use by ref" << endl;
    x3 = ref_x;  //拷贝赋值
    x3 = real_x; //拷贝赋值

    X *px2 = new X; //只有一个构造,因为是匿名对象
    cout << "use vector" << endl;
    vector<X> vx;
    vx.push_back(x1);   //拷贝构造
    vx.push_back(*px2); //拷贝构造

    cout << "quit" << endl;
    delete px2;
}

void test2()
{
    X a;
    X b(a);
}

void test3()
{
    X m;
    X *px = new X; //只有一个构造,因为是匿名对象
    cout << "test" << endl;
    test(m, m); // 这里在传递参数的时候先进行了拷贝构造,实参转形参
    delete px;  // 这个不会自动释放的
}

void test4()
{

    X *px2 = new X; //只有一个构造,因为是匿名对象
    X x1;

    cout << "use vector" << endl;
    vector<X> vx;
    vx.push_back(x1);   //拷贝构造,一次拷贝构造
    vx.push_back(*px2); //拷贝构造,为什么这里有两次拷贝构造?   一次是传递参数的 形参=*px2,还一次是什么
    //https://stackoverflow.com/questions/30358475/why-the-copy-constructor-is-called-twice-when-doing-a-vector-push-back
    // 没有人规定内部怎么实现的
    //
    cout << "quit" << endl;
    delete px2;
}

int main(int argc, char const *argv[])
{
    test4();
    //test2();
    while (1)
        ;
    return 0;
}
