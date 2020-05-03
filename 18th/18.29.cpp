class Class
{
};
class Base : public Class
{
};
class D1 : virtual public Base
{
};
class D2 : virtual public Base
{
};
class MI : public D1, public D2
{
};
class Final : public MI, public Class //warning: direct base 'Class' inaccessible in 'Final' due to ambiguity
                                      // 因为这里有两个class
{
};

int main(int argc, const char **argv)
{
    Base *pb;
    Class *pc;
    MI *pmi;
    D2 *pd2;

    pc = new Final;

    return 0;
}