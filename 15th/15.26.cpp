// 15.26 定义 Quote 和 Bulk_quote 的拷贝控制成员，令其与合成的版本行为一致。
//为这些成员以及其他构造函数添加打印状态的语句，使得我们能够知道正在运行哪个程序。
//使用这些类编写程序，预测程序将创建和销毁哪些对象。
//重复实验，不断比较你的预测和实际输出结果是否相同，直到预测完全准确再结束。

#include <iostream>
#include <string>
using namespace std;

class Quote
{
private:
    string bookNo;

protected:
    double price = 0;

public:
    // 默认构造函数
    Quote() { std::cout << "Quote()" << std::endl; };
    // 正常使用的构造函数
    Quote(string name, double p) : bookNo(name), price(p)
    {
        std::cout << "Quote(string name, double p)" << std::endl;
    };
    // 拷贝构造
    Quote(const Quote &s) : bookNo(s.bookNo), price(s.price)
    {
        std::cout << "Quote(const Quote &s)" << std::endl;
    };
    // 移动构造
    Quote(Quote &&s) noexcept : bookNo(std::move(s.bookNo)), price((std::move(s.price)))
    {
        std::cout << "Quote(Quote &&s)" << std::endl;
    };
    // 拷贝赋值
    Quote &operator=(const Quote &s)
    {
        std::cout << "Quote &operator=(const Quote &s)" << std::endl;
        price = s.price;
        bookNo = s.bookNo;
        return *this;
    }
    // 移动赋值
    Quote &operator=(Quote &&s) noexcept
    {
        std::cout << "Quote &operator=(Quote &&s)" << std::endl;
        price = std::move(s.price);
        bookNo = std::move(s.bookNo);
        return *this;
    }
    virtual ~Quote()
    {
        cout << "Quote Destructor" << endl;
    }
    string isbn() const { return bookNo; }
};

class Bulk_quote : public Quote
{
protected:
    size_t min_qty = 0;
    double discount = 0.0;

public:
    Bulk_quote()
    {
        cout << "Bulk_quote()" << endl;
    }

    Bulk_quote(const string &b, double p, size_t q, double d) : Quote(b, p), min_qty(q), discount(d)
    {
        cout << " Bulk_quote(const string &b, double p, size_t q, double d)" << endl;
    }

    Bulk_quote(const Bulk_quote &rhs) : Quote(rhs), min_qty(rhs.min_qty), discount(rhs.discount)
    {
        cout << "Bulk_quote(const Bulk_quote &rhs)" << endl;
    }

    Bulk_quote &operator=(const Bulk_quote &rhs)
    {
        cout << "Bulk_quote &operator=(const Bulk_quote &rhs)" << endl;
        Quote::operator=(rhs);
        min_qty = rhs.min_qty;
        discount = rhs.discount;
        return *this;
    }

    Bulk_quote(Bulk_quote &&rhs) noexcept : Quote(rhs), min_qty(std::move(rhs.min_qty)),
                                            discount(std::move(rhs.discount))
    {
        cout << "Bulk_quote(Bulk_quote &&rhs)" << endl;
    }

    Bulk_quote &operator=(Bulk_quote &&rhs) noexcept
    {
        cout << "Bulk_quote &operator=(Bulk_quote &&rhs)" << endl;
        Quote::operator=(rhs);
        min_qty = std::move(rhs.min_qty);
        discount = std::move(rhs.discount);
        return *this;
    }

    virtual ~Bulk_quote()
    {
        cout << "~Bulk_quote()" << endl;
    }
};

int main(int argc, char const *argv[])
{
    {
        Bulk_quote d1;
        std::cout << "-----------------Quote b1(d1)--------------" << std::endl;
        Quote b1(d1);
        std::cout << "----------------return---------------" << std::endl;
    }

    while (1)
        ;
    return 0;
}
