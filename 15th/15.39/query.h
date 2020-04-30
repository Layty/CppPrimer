#ifndef __QUERY_H__
#define __QUERY_H__

#include <memory>
#include <iostream>
#include <string>
#include "wordquery.h"
class Query
{

    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);

private:
    // 实际指向的一般是派生类的对象
    std::shared_ptr<Query_base> q;
    Query(std::shared_ptr<Query_base> query) : q(query)
    {
        std::cout << "Query::Query(std::shared_ptr<Query_base> query)\n";
    }

public:
    Query(const std::string &s) : q(new WordQuery(s))
    {
        std::cout << "Query::Query(const std::string& s) where s=" + s + "\n";
    }
    QueryResult eval(const TextQuery &t) const
    {
        return q->eval(t);
    }
    std::string rep() const
    {
        std::cout << "Query::rep() \n";
        return q->rep();
    }
};
inline std::ostream &
operator<<(std::ostream &os, const Query &query)
{
    //Query::rep 通过他的Query_base指针,对rep进行虚调用
    return os << query.rep();
}

#endif // !__QUERY_H__
