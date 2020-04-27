// 15.30编写你自己的 Basket 类，用它计算上一个练习中交易记录的总价格。

//15.29 再运行一次你的程序，这次传入 Quote 对象的 shared_ptr 。如果这次计算出的总额与之前的不一致，解释为什么;如果一直，也请说明原因。
//15.28 定义一个存放 Quote 对象的 vector，将 Bulk_quote 对象传入其中。计算 vector 中所有元素总的 net_price。

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <set>
using namespace std;

// 15.16 改写你在15.2.2节练习中编写的数量受限的折扣策略，令其继承 Disc_quote。
// 15.15 定义你自己的 Disc_quote 和 Bulk_quote。

// 15.11 为你的 Quote 类体系添加一个名为 debug 的虚函数，令其分别显示每个类的数据成员
// 15.7 定义一个类使其实现一种数量受限的折扣策略，具体策略是：当购买书籍的数量不超过一个给定的限量时享受折扣，如果购买量一旦超过了限量，则超出的部分将以原价销售。
// 15.5 定义你自己的 Bulk_quote 类。
// 15.3 定义你自己的 Quote 类和 print_total 函数。

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
    virtual Quote *clone() const & { return new Quote(*this); }
    virtual Quote *clone() && { return new Quote(std::move(*this)); }
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
    virtual Bulk_quote *clone() const & { return new Bulk_quote(*this); }
    virtual Bulk_quote *clone() && { return new Bulk_quote(std::move(*this)); }
};

double print_total(const Quote &book, int n, std::ostream &o = std::cout)
{
    o << "Isbn= " << book.isbn() << "\tTotal price =" << book.net_price(n);
    return book.net_price(n);
}
class Basket
{
private:
    static bool compare(const shared_ptr<Quote> a, const shared_ptr<Quote> b)
    {
        return a->isbn() < b->isbn();
    }
    multiset<shared_ptr<Quote>, decltype(compare) *> items{compare};

public:
    //void add_item(const shared_ptr<Quote> s) { items.insert(s); }

    void add_item(const Quote &s) { items.insert(std::shared_ptr<Quote>(s.clone())); }
    void add_item(Quote &&s) { items.insert(std::shared_ptr<Quote>(std::move(s).clone())); }
    double total_show(std::ostream &o = std::cout)
    {
        double sum = 0;
        for (auto it = items.begin(); it != items.end(); it = items.upper_bound(*it))
        {
            sum += print_total(**it, items.count(*it), o);
        }
        o << " Total sale:" << sum << endl;
    }
};

int main(int argc, char const *argv[])
{
    Quote baseBook("A1", (double)50);
    Bulk_quote devBook("A2", (double)50, 0, 0.1);

    vector<Quote> total;
    total.push_back(devBook);
    total.push_back(devBook);

    double sum = 0;
    for (auto ch : total)
    {
        // 这里的实际是base的没有折扣的价格,push_back传的是子类转换到基类的 拷贝构造
        sum += ch.net_price(1);
    }
    std::cout << sum << std::endl;

    vector<shared_ptr<Quote>> total_ptr;
    std::shared_ptr<Bulk_quote> pdv1 = std::make_shared<Bulk_quote>(devBook); //total =50*0.9+50*0.9=90 子类的正确调用
    total_ptr.push_back(pdv1);
    total_ptr.push_back(pdv1);

    // 但是下面的调用 ,使用时 devBook来构造Quote类,所以调用的是基类的哦
    //total_ptr.push_back(make_shared<Quote>(devBook)); //=50+50=100

    sum = 0;
    for (auto ch : total_ptr)
    {
        // 调用的实际的net_price
        sum += ch->net_price(1);
    }
    std::cout << sum << std::endl;

    {
        vector<shared_ptr<Quote>> total_ptr;
        std::shared_ptr<Quote> pdv1 = std::make_shared<Quote>(devBook); //total =50*0.9+50*0.9=90 子类的正确调用
        total_ptr.push_back(pdv1);
        total_ptr.push_back(pdv1);

        sum = 0;
        for (auto ch : total_ptr)
        {
            // 调用的实际的net_price
            sum += ch->net_price(1);
        }
        std::cout << sum << std::endl;
    }

    //*****************************
    Basket vb;
    vb.add_item(devBook);
    vb.add_item(devBook);
    vb.total_show();

    while (1)
        ;
    return 0;
}
