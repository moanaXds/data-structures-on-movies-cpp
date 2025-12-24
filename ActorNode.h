#include <iostream>

using namespace std;

class moviesofActor;
class ACTOR;

class ActorNode {
public:
    string name;
    moviesofActor* mHead;
    moviesofActor* mTail;
    ActorNode* left;
    ActorNode* right;

    ActorNode(const string& actorname)
    {
        name = actorname;
        mHead = NULL;
        mTail = NULL;
        left = NULL;
        right = NULL;
    }


    void addmovieToActorsList(MovieNode* movie)
    {
        moviesofActor* newnode = new moviesofActor(movie);
        if (mHead == NULL)
        {
            mHead = mTail = newnode;
            return;
        }

        mTail->next = newnode;
        mTail = newnode;
    }

    void displayMovies()
    {
        cout << endl;
        cout << "Movies Done by : " << name << " :" << endl;
        moviesofActor* temp = mHead;
        while (temp != NULL)
        {
            if (temp->movie != NULL)
            {
                cout << "      * " << temp->movie->title << " [ " << temp->movie->year << " ]\n";
            }
            temp = temp->next;
        }
    }


    void displayCoActors()
    {
        cout << endl;
        cout << "CO-ACTORS of " << name << " :" << endl;

        moviesofActor* temp = mHead;
        while (temp != NULL)
        {
            if (temp->movie != NULL)
            {
                ACTOR* coactor = temp->movie->ahead; // head of actor linklist in that movie.

                while (coactor != NULL)
                {
                    if (coactor->name != name)
                    {
                        cout << "      * " << coactor->name << " [  in " << temp->movie->title << "  ]\n";
                    }
                    coactor = coactor->next;
                }
            }

            temp = temp->next;
        }
        cout << "\n-------------------\n";
    }

};
