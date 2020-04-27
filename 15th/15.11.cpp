//15.11 为你的 Quote 类体系添加一个名为 debug 的虚函数，令其分别显示每个类的数据成员

// 15.7 定义一个类使其实现一种数量受限的折扣策略，具体策略是：当购买书籍的数量不超过一个给定的限量时享受折扣，如果购买量一旦超过了限量，则超出的部分将以原价销售。
// 15.5 定义你自己的 Bulk_quote 类。
// 15.3 定义你自己的 Quote 类和 print_total 函数。

#include <string>
#include <iostream>

class Quote
{
private:
    std::string bookNo;

protected:
    double price = 0;

public:
    Quote() = default;
    Quote(const std::string &name, double price) : bookNo(name), price(price) {}
    virtual ~Quote() = default;
    std::string isbn() const { return bookNo; }
    virtual double net_price(int n) const { return price * n; }
    virtual void debug(std::ostream &o = std::cout)
    {
        o << "BookBo= " << isbn() << " price=" << price << std::endl;
    }
};

class Bulk_quote : public Quote
{
private:
    int min = 0;
    double discount = 0;

public:
    Bulk_quote() = default;
    Bulk_quote(std::string name, double price, double discount, int min) : Quote(name, price), discount(discount), min(min) {}
    double net_price(int n) const override
    {
        return (n < min ? price * n : price * (1 - discount) * n);
    }
    void debug(std::ostream &o = std::cout) override
    {
        o << "BookBo= " << isbn() << " price=" << price << " min=" << min << "discount= " << discount << std::endl;
    }
};
class Bulk_quote2 : public Quote
{
private:
    int min = 0;
    int max = 0;
    double discount = 0;

public:
    Bulk_quote2() = default;
    Bulk_quote2(std::string name, double price, double discount, int min, int max) : Quote(name, price), discount(discount), min(min), max(max) {}
    double net_price(int n) const override
    {
        if (n < min)
            return price * n;
        else if (n <= max)
            return price * (1 - discount) * n;
        else
            return price * (1 - discount) * max + (n - max) * price;
    }
    void debug(std::ostream &o = std::cout) override
    {
        o << "BookBo= " << isbn() << " price=" << price << " min=" << min << " max= " << max << " discount= " << discount << std::endl;
    }
};

std::ostream &print_total(const Quote &book, int n, std::ostream &o = std::cout)
{
    return o << "Isbn= " << book.isbn() << "\tTotal price =" << book.net_price(n);
}

int main(int argc, char const *argv[])
{
    Quote baseBook("A1", (double)50);
    print_total(baseBook, 10) << std::endl;
    baseBook.debug();

    Bulk_quote devBook("A2", (double)50, 0.1, 2);
    print_total(devBook, 2) << std::endl;
    print_total(devBook, 3) << std::endl;
    devBook.debug();

    Bulk_quote2 devBook2("A3", (double)50, 0.1, 2, 5);
    print_total(devBook2, 1) << std::endl;
    print_total(devBook2, 3) << std::endl;
    print_total(devBook2, 10) << std::endl;
    devBook2.debug();

    while (1)
        ;
    return 0;
}
