#ifndef NOTQUERY_H
#define NOTQUERY_H

#include "query.h"
#include <memory>

class NotQuery : public Query_base
{
    friend Query operator~(const Query &operand);

public:
    NotQuery(const Query &q) : query(q)
    {
        std::cout << "NotQuery::NotQuery()\n";
    }

    //! virtuals:
    std::string rep() const override
    {
        std::cout << "NotQuery::rep()\n";
        return "~(" + query.rep() + ")";
    }

    QueryResult eval(const TextQuery &text) const override
    {
        //! virtual call to eval through the Query operand
        QueryResult result = query.eval(text);

        //! start out with an empty result set
        std::shared_ptr<std::set<line_no>>
            ret_lines = std::make_shared<std::set<line_no>>();

        std::set<TextQuery::line_no>::iterator
            begin = result.begin(),
            end = result.end();

        StrBlob::size_type sz = result.get_file().size();

        for (std::size_t n = 0; n != sz; ++n)
        {
            if (begin == end || *begin != n)
                ret_lines->insert(n);
            else if (begin != end)
                ++begin;
        }

        return QueryResult(rep(), ret_lines, result.get_file());
    }

    Query query;
};

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
    //!    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //! note : There is an imlplicit conversion here.
    //!        The Query constructor that takes shared_ptr is not
    //!        "explicit", thus the compiler allows this conversion.
}

#endif // NOTQUERY_H
