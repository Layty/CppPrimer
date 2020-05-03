class List
{
    int a;
};

class DbiList : public List, public List
{
    int b;
};

int main(int argc, char const *argv[])
{
    DbiList C;
    return 0;
}
