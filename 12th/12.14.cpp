/*
12.14+12.15
智能指针与异常结合的使用
当异常发生后,我们在异常发生之后的语句无法执行,比如一些资源清理操作,这个时候可以把清理动作作为一个共享指针的delte参数
shared_ptr<connection> end_link(&linkme, try_end_link);  try_end_link 在程序结束或者异常后能够执行
*/

#include <vector>
#include <memory>
#include <iostream>

using namespace std;

struct connection
{
    int fd;
};

struct disconnection
{
    int fd;
    int port;
};

connection
connect(struct disconnection *t)
{
    struct connection ret;
    ret.fd = t->port + 1;
    cout << "link to port:" << t->port << endl;
    return ret;
}

disconnection
disconnect(struct connection *t)
{
    struct disconnection ret;
    if (t->fd > 0)
    {
        ret.fd = -1;
        ret.port = t->fd - 1;
        cout << "break LINK to port:" << ret.port << endl;
        t->fd = -1;
    }

    return ret;
}

void try_end_link(struct connection *t)
{
    cout << "By shared_ptr" << endl;
    disconnect(t);
}

int main(int argc, char const *argv[])
{
    {
        struct disconnection unlinkme = {-1, 20};
        connection linkme = connect(&unlinkme);
        // disconnect(&linkme);
        //shared_ptr<connection> end_link(&linkme, try_end_link);
        shared_ptr<connection> end_link(&linkme, [](struct connection *t) {cout << "By shared_ptr" << endl;disconnect(t); });
    }
    while (1)
        ;
    return 0;
}
