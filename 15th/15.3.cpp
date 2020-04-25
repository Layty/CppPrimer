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

std::ostream &print_total(const Quote &book, int n, std::ostream &o = std::cout)
{
    return o << "Isbn= " << book.isbn() << "\tTotal price =" << book.net_price(n);
}

int main(int argc, char const *argv[])
{
    Quote baseBook("A1", (double)50);
    print_total(baseBook, 10) << std::endl;
    while (1)
        ;
    return 0;
}
