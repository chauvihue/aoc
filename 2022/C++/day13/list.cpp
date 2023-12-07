#include <bits/stdc++.h>
using namespace std;
#define sz1 (elements.size())
#define sz2 (obj.elements.size())



class List
{
    vector<int> elements;
    public:
        List(string s)
        {

        }
        void push(int n)
        {
            elements.push_back(n);
        }
        int operator < (List const &obj)
        {
            if (sz1 != sz2) return sz1 < sz2;
            for (int i = 0; i < sz1; i++)
                if (elements[i] != obj.elements[i]) return elements[i] < obj.elements[i];
            return -1;
        }
};

class Element
{
    int value;
    List* parent;
    
};

class Packet
{
    vector<Packet> elements;
    public:
        Packet(string s)
        {
            
        }
        void push(Packet p)
        {
            elements.push_back(p);
        }
        bool operator < (Packet const &obj)
        {
            if (sz1 != sz2) return sz1 < sz2;
            for (int i = 0; i < sz1; i++)
                if (elements[i] < obj.elements[i] != -1) return elements[i] < obj.elements[i];
            return -1; 
        }
};
