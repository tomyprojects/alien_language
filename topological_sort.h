#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

#define throw_if(c) if (c) { throw std::runtime_error(#c); }

struct tsnode
{
    tsnode* n[26];
    tsnode() : n() {}
};

class topological_sort
{
    tsnode* root;
    void delete_node(tsnode * node)
    {
        for (int i=0; i<26; i++)
            if (node->n[i])
                delete_node(node->n[i]);
        delete node;
    }
public:
    topological_sort() { root = new tsnode; }
    ~topological_sort() { delete_node(root); }

    void push_back(string s)
    {
        tsnode * nodeptr = root;
        for (int i=0; i<s.size(); i++)
        {
            if (nodeptr->n[s[i] % 26] == 0)
                nodeptr->n[s[i] % 26] = new tsnode;
            nodeptr = nodeptr->n[s[i] % 26];
        }
    }

    bool find(string const& s)
    {
        tsnode * nodeptr = root;

        for (int i=0; i<s.size(); i++)
        {
            if (nodeptr->n[s[i] % 26] == 0)
                return false;
            nodeptr = nodeptr->n[s[i] % 26];
        }

        return true;
    }
};

#endif // TOPOLOGICAL_SORT_H
