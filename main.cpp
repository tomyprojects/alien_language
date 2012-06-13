#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "topological_sort.h"

using namespace std;

#define throw_if(c) if (c) { throw std::runtime_error(#c); }

typedef topological_sort dictionary_t;
typedef vector<int> solution_t;
typedef vector<string> testcase_list;

void find_matches(dictionary_t & d, int & matches, string str, int index=0)
{
    size_t a = str.find('(');

    if (a == string::npos)
    {
        if (d.find(str))
        {
            matches++;
        }
        return;
    }

    size_t b = str.find(')');

    throw_if(b == string::npos);

    string a_str;

    if (a > 0)
    {
        a_str += str.substr(0,a);

        if (d.find(a_str) == false)
            return;
    }

    for (int i=a+1; i<b; i++)
    {
        string new_str = a_str;

        new_str += str.substr(i,1);

        if (b+1 < str.size())
            new_str += str.substr(b+1);

        find_matches(d, matches, new_str, a);
    }
}

void read_from_file(string name, dictionary_t & d, testcase_list & t)
{
    fstream f(name.c_str(), ios::in);

    throw_if(!f.is_open());

    int L, D, N;
    f >> L >> D >> N;

    f.get();

    string s;

    while (D--)
    {
        getline(f, s);
        d.push_back(s);
    }

    while (N--)
    {
        getline(f, s);
        t.push_back(s);
    }

    f.close();
}

void print(string s) { cout << s << endl; }

void write_to_file(string name, solution_t s)
{
    fstream f(name.c_str(), ios::out);

    throw_if (!f.is_open());

    for (int i=0; i<s.size(); i++)
    {
        f << "Case #" << i+1 << ": " << s[i] << endl;
    }

    f.close();
}

int main()
{
    try
    {
        string path = "/Users/Jim/Desktop/Google Drive/google code jam/alien_language/";

        dictionary_t d;
        testcase_list t;
        solution_t solution;

        read_from_file(path + "A-small-practice.in", d, t);

        for (int i=0; i<t.size(); i++)
        {
            int matches = 0;

            cout << "case #" << i+1 << ": " << t[i] << endl;

            find_matches(d, matches, t[i]);
            solution.push_back(matches);
        }

        write_to_file(path + "A-small-practice.txt", solution);
    }
    catch (std::exception & e)
    {
        cout << "exception caught: " << e.what() << endl;
    }

    return 0;
}

