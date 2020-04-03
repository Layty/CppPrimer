/*
    13.49 实现自己的move操作,注意,我这里增加了 string ID,在move操作的时候一定要加上对他的操作
    13.34 设计自己的message 类和 Folder 类

    message 可以被多个Folder 所包含 ,一个Folder 包含多个 message
    Message 拷贝构造的时候,需要复制folder,同时往folder添加
    Message 拷贝赋值的时候,需要执行删除自身之前节点的操作 同时添加到新的Folder中


*/

#include <string>
#include <vector>
#include <iostream>
#include <set>
using namespace std;

class Folder;

class Message
{
    friend class Folder;
    friend void swap(Message &a, Message &b);

private:
    string Id; // fow swap debug,这个id是为了显示交换结果,因为交换message的书本做法是全部交换,而不是单单string name
    string msg_raw;
    set<Folder *> folder_list;

    void move_Folder(Message *m);

public:
    Message(const string &msg = "") : msg_raw(msg), Id(msg) {}
    Message(const Message &s);
    Message &operator=(const Message &s);
    Message &operator=(Message &&s) noexcept;
    Message(Message &&s) noexcept;

    ~Message();

    // 添加消息到Folder
    void add_to_folder(Folder &f);
    void del_from_folder(Folder &f);
    ostream &print(ostream &c)
    {
        c << msg_raw << "--ID=" << Id;
        return c;
    }
};

class Folder
{
private:
    string name;
    set<Message *> msg_list;

public:
    Folder(const string &name = "") : name(name) {}
    ~Folder();

    void add_msg(Message &msg);
    void del_msg(Message &msg);
    print(ostream &c)
    {
        c << "Dir:" << name << endl;
        for (auto it : msg_list)
            it->print(c) << endl;
    }
};
//-------------------------------------Message-------------------------------------------
//
//
//
//
void Message::add_to_folder(Folder &f)
{
    folder_list.insert(&f);
    f.add_msg(*this);
}
void Message::del_from_folder(Folder &f)
{
    folder_list.erase(&f);
    f.del_msg(*this);
}
// 在自己的set中的Folder中的,执行删除消息
Message::~Message()
{
    for (auto f : folder_list)
        f->del_msg(*this);
    // 自身元素没有指针类型,无需释放
}
// 拷贝构造函数, 1是复制Message本身,2是添加到Folder中
Message::Message(const Message &s) : msg_raw(s.msg_raw), folder_list(s.folder_list)
{
    for (auto i : s.folder_list)
        i->add_msg(*this);
}
// 拷贝赋值,需要注意自身赋值, 0.删除自身的Folder 指向 1. 复制原来的消息体,添加到Folder  2. 如果是自身的话
Message &Message::operator=(const Message &s)
{
    if (this == &s)
        return *this;
    for (auto f : folder_list)
        f->del_msg(*this);
    msg_raw = s.msg_raw;
    folder_list = s.folder_list;
    for (auto f : folder_list)
        f->add_msg(*this);
    return *this;
}

//从m 中移动信息,并释放m自身的消息
void Message::move_Folder(Message *m)
{
    folder_list = std::move(m->folder_list);
    for (auto f : folder_list)
    {
        f->del_msg(*m);
        f->add_msg(*this);
    }
    m->folder_list.clear(); //m原本的析构
}

Message::Message(Message &&s) noexcept : msg_raw(std::move(s.msg_raw)), Id(std::move(s.Id))
{
    std::cout << " **move construct**" << std::endl;
    move_Folder(&s);
}
Message &Message::operator=(Message &&s) noexcept
{
    std::cout << " **move operator=**" << std::endl;
    if (this == &s)
        return *this;
    msg_raw = std::move(s.msg_raw);
    Id = std::move(s.Id);
    move_Folder(&s);
    return *this;
}

//-----------------------------------Folder----------------------------------------------
//
//
//
//
void Folder::add_msg(Message &msg)
{
    msg_list.insert(&msg);
}
void Folder::del_msg(Message &msg)
{
    msg_list.erase(&msg);
}
// 在自己的set中的message中的,执行删除
Folder::~Folder()
{
    for (auto i : msg_list)
        i->del_from_folder(*this);
    // 自身元素没有指针类型,无需释放
}

//------------------------------------------------------------------------------------------
void swap(Message &a, Message &b)
{
    //cout << "*****************use swap************" << endl;
    for (auto f : a.folder_list)
        f->del_msg(a);
    for (auto f : b.folder_list)
        f->del_msg(b);
    swap(a.msg_raw, b.msg_raw); //我觉得交换消息应该只需要交换字符串?
    swap(a.folder_list, b.folder_list);
    for (auto f : a.folder_list)
        f->add_msg(a);
    for (auto f : b.folder_list)
        f->add_msg(b);
}
//-------------------------------------------------------------------------------------------
//
//
//
//
int main(int argc, char const *argv[])
{
    // Folder root("root");
    // /* code */
    // {
    //     Message A("msg_A");
    //     Message B("msg_B");
    //     Message C("msg_C");
    //     Message D("msg_D");
    //     A.add_to_folder(root);
    //     B.add_to_folder(root);
    //     C.add_to_folder(root);
    //     D.add_to_folder(root);
    //     root.print(cout);
    //     B.del_from_folder(root);
    //     root.print(cout);
    // }
    // // 执行msg的析构,删除消息
    // root.print(cout);

    // Folder root("root");
    // Folder root2("root2");
    // Message Q("msg_Q");
    // Q.add_to_folder(root2);
    // root2.print(cout);
    // {
    //     Message A("msg_A");
    //     Message B("msg_B");
    //     Message C(A);
    //     Message D("msg_D");
    //     A.add_to_folder(root);
    //     B.add_to_folder(root);
    //     C.add_to_folder(root);
    //     D.add_to_folder(root);
    //     root.print(cout);
    //     D = B;
    //     root.print(cout);
    //     A = A;
    //     root.print(cout);

    //     cout << "-----swap----" << endl;
    //     swap(A, Q);
    //     root.print(cout);
    //     root2.print(cout);
    // }
    // root.print(cout);
    {

        Folder root("root");
        Message A("msg_A");
        Message B((Message("__move_construct__")));
        Message C("msg_C");
        Message D = std::move(C);

        A.add_to_folder(root);
        B.add_to_folder(root);
        D.add_to_folder(root);

        root.print(cout);
    }
    while (1)
        ;
    return 0;
}
