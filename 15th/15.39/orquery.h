#ifndef ORQUERY_H
#define ORQUERY_H

#include "binaryquery.h"

class OrQuery : public BinaryQuery
{
    friend Query operator|(const Query &, const Query &);
    OrQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "|")
    {
        std::cout << "OrQuery::OrQuery\n";
    }

    QueryResult eval(const TextQuery &text) const override
    {
        QueryResult right = rhs.eval(text), left = lhs.eval(text);

        //! copy the left-hand operand into the result set
        std::shared_ptr<std::set<line_no>> ret_lines =
            std::make_shared<std::set<line_no>>(left.begin(), left.end());

        //! inert lines from the right-hand operand
        ret_lines->insert(right.begin(), right.end());

        return QueryResult(rep(), ret_lines, left.get_file());
    }
    std::string rep() const override
    {
        std::cout << "OrQuery::rep()\n";
        return BinaryQuery::rep();
    }
};

inline Query operator|(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

#endif // ORQUERY_H
