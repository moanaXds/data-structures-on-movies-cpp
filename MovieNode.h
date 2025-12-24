#include <iostream>

using namespace std;

#include <iostream>

using namespace std;


class MovieNode {
public:
    string title;
    string director;
    int year;
    float rating;

    ACTOR* ahead;
    ACTOR* atail;

    GENRE* ghead;
    GENRE* gtail;

    MovieNode* left;
    MovieNode* right;

    MovieNode()
    {
        title = "";
        director = "";
        year = 0;
        rating = 0.0f;
        ahead = NULL;
        atail = NULL;
        ghead = NULL;
        gtail = NULL;
        left = NULL;
        right = NULL;
    }

    void LINKED_LIST_OF_ACTOR(const string& name)
    {
        ACTOR* newnode = new ACTOR(name);

        if (ahead == NULL)
        {
            ahead = atail = newnode;
            return;
        }
        atail->next = newnode;
        atail = newnode;
    }

    void LINKED_LIST_OF_GENRE(const string& name)
    {
        GENRE* newnode = new GENRE(name);

        if (ghead == NULL)
        {
            ghead = gtail = newnode;
            return;
        }
        gtail->next = newnode;
        gtail = newnode;
    }

    void display()
    {
        cout << "Title      : " << title << endl;
        cout << "Director   : " << director << endl;
        cout << "Actors     : ";
        ACTOR* temp = ahead;
        while (temp != NULL)
        {
            cout << temp->name;
            if (temp->next)
            {
                cout << "|";
            }
            temp = temp->next;
        }

        cout << endl;

        cout << "Genre      : ";
        GENRE* temp1 = ghead;
        while (temp1 != NULL)
        {
            cout << temp1->name;
            if (temp1->next)
            {
                cout << "|";
            }
            temp1 = temp1->next;
        }

        cout << endl;

        cout << "Rating     : " << rating << endl;
        cout << "Year       : " << year << endl;

        cout << "\n-------------------\n";
    }
};

#pragma once
