#include "compress.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
    
    cout << " ___  ___  ________  ___  ________   \n"
         << "|\\  \\|\\  \\|\\_____  \\|\\  \\|\\   __  \\  \n"
         << "\\ \\  \\\\\\  \\\\|___/  /\\ \\  \\ \\  \\|\\  \\ \n"
         << " \\ \\   __  \\   /  / /\\ \\  \\ \\   ____\\\n"
         << "  \\ \\  \\ \\  \\ /  /_/__\\ \\  \\ \\  \\___|\n"
         << "   \\ \\__\\ \\__\\\\________\\ \\__\\ \\__\\   \n"
         << "    \\|__|\\|__|\\|_______|\\|__|\\|__|   \n"
         << "By NaviHX\n"
         << "Star me on Github : https://github.com/NaviHX/hzip\n";
    if (argc == 1)
        cout << "Path Needed\nPath will be\"test.in\" if not given\nType -h for help\n";
    else
    {
        int flag = 0;
        string path = "test.in";
        string opath = "";
        for (int i = 1; i < argc; i++)
        {
            string arg(argv[i]);
            if (arg == "-h" || arg == "--help")
            {
                std::cout << "Usage          : hzip [options] file_path" << std::endl
                          << "-h, --help     : help information" << std::endl
                          << "-c, --compress : compress a file" << std::endl
                          << "-e, --extract  : extract a file" << std::endl;
            }
            else if (arg == "-c" || arg == "--compress")
                flag = 0;
            else if (arg == "-e" || arg == "--extract")
                flag = 1;
            else if (arg[0] != '-')
                path = arg;
        }
        if (flag == 0)
        {
            opath = path + ".hzp";
            compress(const_cast<char*>(path.c_str()), const_cast<char*>(opath.c_str()));
        }
        else if (flag == 1)
        {
            opath = path + ".ext";
            extract(const_cast<char*>(path.c_str()), const_cast<char*>(opath.c_str()));
        }
        cout << "Done" << endl;
    }

#ifdef DEBUG

   compress("test.in","test.hzp");
   extract("test.hzp","test.out");
   return 0;

#endif

}
