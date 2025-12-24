#include <iostream>

using namespace std;


class ACTOR {
public:
    string name;
    ACTOR* next;

    ACTOR(const string& name)
    {
        this->name = name;
        next = NULL;
    }
};

class GENRE {
public:
    string name;
    GENRE* next;

    GENRE(const string& name)
    {
        this->name = name;
        next = NULL;
    }
};

