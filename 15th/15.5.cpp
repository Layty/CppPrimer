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
        // if (n < min)
        // {
        //     return price * n;
        // }
        // else
        // {
        //     return price * (1 - discount) * n;
        // }
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

    Bulk_quote devBook("A2", (double)50, 0.1, 2);
    print_total(devBook, 2) << std::endl;
    print_total(devBook, 3) << std::endl;

    while (1)
        ;
    return 0;
}
