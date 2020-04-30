#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>

#include "query_base.h"
#include "query.h"
#include "andquery.h"
#include "orquery.h"

int main()
{
    std::ifstream file("test.txt");

    TextQuery tQuery(file);

    Query q = Query("fieryzzz") | Query("wind");

    std::cout << "Follow" << std::endl;

    std::cout << q.eval(tQuery);
    while (1)
        ;
    return 0;
}
