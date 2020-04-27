// 15.16 改写你在15.2.2节练习中编写的数量受限的折扣策略，令其继承 Disc_quote。
// 15.15 定义你自己的 Disc_quote 和 Bulk_quote。

// 15.11 为你的 Quote 类体系添加一个名为 debug 的虚函数，令其分别显示每个类的数据成员
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
    virtual std::ostream &debug(std::ostream &o = std::cout) const
    {
        return o << "BookBo= " << isbn() << " price=" << price;
    }
};

class Disc_quote : public Quote
{
protected:
    double discount = 0;
    int quantity = 0;

public:
    Disc_quote() = default;
    Disc_quote(const std::string &name, double price, int num, double discount) : Quote(name, price), quantity(num), discount(discount) {}
    virtual double net_price(int n) const = 0;
    std::ostream &debug(std::ostream &o = std::cout) const override
    {
        return Quote::debug(o) << " discount= " << discount << " quantity=" << quantity;
    }
};

class Bulk_quote : public Disc_quote
{

public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &name, double price, int num, double discount) : Disc_quote(name, price, num, discount) {}
    double net_price(int n) const override
    {
        if (n <= quantity)
            return price * n;
        else
            return price * quantity + (n - quantity) * price * (1 - discount);
    }
};

class Bulk_quote2 : public Disc_quote
{
protected:
    int quantity_lv2 = 0; //享受折扣的最大数量

public:
    Bulk_quote2() = default;
    Bulk_quote2(const std::string &name, double price, int num, double discount, int lv2) : Disc_quote(name, price, num, discount), quantity_lv2(lv2) {}
    double net_price(int n) const override
    {
        int tmp = quantity_lv2 + quantity;
        if (n <= quantity)
            return price * n;
        else if (n < tmp)
            return price * quantity + (tmp - n) * price * (1 - discount);
        else
            return price * quantity + quantity_lv2 * price * (1 - discount) + (n - quantity_lv2 - quantity) * price;
    }
    std::ostream &debug(std::ostream &o = std::cout) const override
    {
        return Disc_quote::debug(o) << " quantity_lv2= " << quantity_lv2;
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
    baseBook.debug() << std::endl;

    Bulk_quote devBook("A2", (double)50, 5, 0.1);
    print_total(devBook, 2) << std::endl;
    print_total(devBook, 6) << std::endl;
    devBook.debug() << std::endl;

    Bulk_quote2 devBook2("A2", (double)50, 5, 0.1, 3);
    print_total(devBook2, 2) << std::endl;
    print_total(devBook2, 10) << std::endl;
    devBook2.debug() << std::endl;

    Disc_quote B();

    while (1)
        ;
    return 0;
}
