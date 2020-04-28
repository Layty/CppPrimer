#ifndef __QUERY_BASE_H__
#define __QUERY_BASE_H__

#include <string>
#include <iostream>
#include <memory>
#include "textquery.h"
#include "queryresult.h"
//#include "query.h"

class Query_base
{
    friend class Query;

protected:
    //using line_no = TextQuery::line_no; //  used in the eval function
    virtual ~Query_base() = default;

private:
    //virtual QueryResult eval(const TextQuery &) const = 0;
    virtual std::string rep() const = 0;
};

#endif // !__QUERY_BASE_H__
