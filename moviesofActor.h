#include <iostream>

using namespace std;


class MovieNode;   

class moviesofActor {
public:
    MovieNode* movie;
    moviesofActor* next;

    moviesofActor(MovieNode* m)
    {
        movie = m;
        next = NULL;
    }
};
