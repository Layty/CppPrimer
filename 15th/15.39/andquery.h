#ifndef ANDQUERY_H
#define ANDQUERY_H

#include "binaryquery.h"
#include <algorithm>

class AndQuery : public BinaryQuery
{
    friend Query operator&(const Query &, const Query &);
    AndQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&")
    {
        std::cout << "AndQuery::AndQuery()\n";
    }

    //! @note: inherits rep and define eval

    QueryResult eval(const TextQuery &text) const override
    {
        //! virtual calls through the Query operands to get result sets for the operands
        QueryResult left = lhs.eval(text), right = rhs.eval(text);

        //! set to hold the intersection of the left and right
        std::shared_ptr<std::set<line_no>>
            ret_lines = std::make_shared<std::set<line_no>>();

        //! writes the intersection of two ranges to a destination iterator
        std::set_intersection(left.begin(), left.end(),
                              right.begin(), right.end(),
                              std::inserter(*ret_lines, ret_lines->begin()));

        return QueryResult(rep(), ret_lines, left.get_file());
    }
    std::string rep() const override
    {
        std::cout << "AndQuery::rep()\n";
        return BinaryQuery::rep();
    }
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

#endif // ANDQUERY_H
