#include "../include/include.h"
#include <fstream>
#include <sstream>
#include <time.h>

string getTime()
{
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d-%H-%M-%S", localtime(&timep));
    return tmp;
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
        return -1;

    string inf_path(argv[1]);
    string path;

    auto path_it = inf_path.find_last_of('\\');
    if (path_it != string::npos)
        path = inf_path.substr(0, path_it);

    string time = getTime();
    cout << time << endl;
    string ouf_path = path + "\\" + time + " - formatDlms.txt ";

    ifstream in(inf_path);
    ofstream out(ouf_path);

    if (!in)
    {
        cout << "open" << inf_path << "failed" << endl;
        return -1;
    }
    if (!in)
    {
        cout << "open" << ouf_path << "failed" << endl;
        return -1;
    }

    string txt_line;
    while (getline(in, txt_line))
    {
        auto it = txt_line.find("Send:");
        if (it != string::npos)
            txt_line = txt_line.substr(it);

        auto it2 = txt_line.find("Received:");
        if (it2 != string::npos)
            txt_line = txt_line.substr(it2);

        auto it3 = txt_line.find_first_of("0123456789ABCDE");
        if (it3 != string::npos)
            txt_line = txt_line.substr(it3);

        string new_line;
        for (auto ch : txt_line)
        {
            if (ch != ' ')
                new_line.push_back(ch);
        }

        if (it != string::npos)
            out << "Put: " << new_line << endl;
        if (it2 != string::npos)
            out << "Get: " << new_line << endl;
    }
    out.close();

    return 0;
}
