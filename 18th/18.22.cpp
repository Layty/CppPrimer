// 已知存在如下所示的类的继承体系，其中每个类都定义了一个默认构造函数：
// class A { ... };
// class B : public A { ... };
// class C : public B { ... };
// class X { ... };
// class Y { ... };
// class Z : public X, public Y { ... };
// class MI : public C, public Z { ... };
// 对于下面的定义来说，构造函数的执行顺序是怎样的？
// MI mi;

//A, B, C X, Y, Z, MI
