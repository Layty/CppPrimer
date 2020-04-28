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
    Query q = Query("fiery") & Query("bird") | Query("wind");
    std::cout << " Follow  <<q" << std::endl;
    std::cout << q;
    while (1)
        ;
    return 0;
}
