#include "include.h"

#include <stack>


int main(int argc, char const *argv[])
{

    // 1*(2+10)-11

    stack<string> s;


    string  abc="1*(2+10)-1";


    string num;
    string::size_type i=0;
    for(auto ch : abc)
    {
        i++;

        if(ch>='0' && ch <='9')
        {
            num.append(string(1,ch));
            if(i==abc.size())
            {
                s.push(num);
            }
        }
        else
        {
            if(!num.empty())
            {
                s.push(num);
            }
            s.push(string(1,ch));
            num.erase();
        }
    }
    while(!s.empty())
    {
        cout<<s.top()<<endl;
        s.pop();
    }



    auto& expr = "This is (Mooophy(awesome)((((wooooooooo))))) and (ocxs) over";

    stack<char> s1;

    int ok=0;

    for(auto ch: expr)
    {
        s1.push(ch);
        if(ch=='(')  ok++;
        if(ch==')' && ok)
        {
            while(s1.top()!='(')
            {
                s1.pop();
            }
            s1.pop();
            s1.push('#');
            ok--;
        }
    }

    string output;
    for (; !s1.empty(); s1.pop()) output.insert(output.begin(), s1.top());
    cout << output << endl; // "This is # and # over"







    while(1);
    return 0;
}
