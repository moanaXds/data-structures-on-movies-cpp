#include "Actor_Genre.h"
#include "MovieNode.h"
#include "Edge.h"
#include "moviesofActor.h"
#include "ActorNode.h"
#include "Graph.h"
#include "ActorBST.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


//...................................       7.1      ........................................


class ACTOR;
class GENRE;
class MovieNode;
class MovieBST;

class MovieBST{

private:
    MovieNode* insert_data_in_tree(MovieNode* root, MovieNode* newnode)
    {
        if (root == NULL)
        {
            return newnode;
        }

        if (newnode->title < root->title)
        {
            root->left = insert_data_in_tree(root->left, newnode);

        }

        else
        {
            root->right = insert_data_in_tree(root->right, newnode);
        }

        return root;
    }

    // USE TO UPDATE

    MovieNode* SEARCH_IN_BST(MovieNode* root, const string& title)
    {
        if (root == NULL)return NULL;

        if (title == root->title)
        {
            return root;
        }

        if (title < root->title)
        {
            return SEARCH_IN_BST(root->left, title);
        }
        else
        {
            return SEARCH_IN_BST(root->right, title);
        }

    }

    void displayInorderData(MovieNode* root)
    {
        if (root == NULL)return;

        displayInorderData(root->left);

        root->display();

        displayInorderData(root->right);
    }

public:
    MovieNode* root;

    MovieBST()
    {
        root = NULL;
    }

    void insert(MovieNode* newnode)
    {
        root = insert_data_in_tree(root, newnode);
    }

    MovieNode* search(const string& title)
    {
        return SEARCH_IN_BST(root, title);
    }

    void displayInOrder()
    {
        displayInorderData(root);
    }


    void updateMovie(MovieNode* movie)
    {
        if (movie == NULL)
        {
            cout << "Movie not found!";
            return;
        }

        string ntitle;
        cout << "New Title :";
        getline(cin, ntitle);
        movie->title = ntitle;


        string ndirector;
        cout << "New director : ";
        getline(cin, ndirector);
        movie->director = ndirector;

        cout << "New rating : ";
        float nrating;
        cin >> nrating;
        movie->rating = nrating;


        cout << "New year: ";
        int nyear;
        cin >> nyear;
        if (nyear > 0) movie->year = nyear;

        cin.ignore();
    }
};





//...................................       7.2      ........................................




class moviesofActor;


// ActorNode -> one actor + a linked list of their movies

class ActorNode;


// ActorBST  manage ActorNode ( one actor + a linked list of their movies )

class ActorBST;




//...................................       7.3       ........................................




//  Edge class make a linkedlist of each movie.. with connected ones

class Edge;

class Graph;


void fillArray(MovieNode* root, Graph& G)
{
    if (root == NULL) return;

    fillArray(root->left, G);

    G.ADD_MOVIE(root);

    fillArray(root->right, G);
}




//...........................................         7.4      .......................................


struct ActorHash
{
    string name;
    MovieNode* movie[6000];
    int count = 0;
    ActorHash* next = NULL;
};


struct GenreHash
{
    string name;
    MovieNode* movie[6000];
    int count = 0;
    GenreHash* next = NULL;
};


const int SIZE = 6000;

ActorHash* actorTable[SIZE] = { NULL };
GenreHash* genreTable[SIZE] = { NULL };


int HASH_FUNCTION(const string& str)
{
    int index = 0;

    for (int i = 0; i < str.length(); i++)
    {
        index = index + str[i];
    }
    return index % SIZE;
}

void INSERT_ACTOR(const string& name, MovieNode* movie)
{
    int index = HASH_FUNCTION(name);

    //     if actor exists inc count and insert

    ActorHash* temp = actorTable[index];

    while (temp != NULL)
    {
        if (temp->name == name)
        {
            temp->movie[temp->count++] = movie;
            return;
        }
        temp = temp->next;
    }

    //   if not, create new

    ActorHash* newnode = new ActorHash();

    newnode->name = name;
    newnode->movie[newnode->count++] = movie;

    newnode->next = actorTable[index];        //   at head
    actorTable[index] = newnode;
}


void INSERT_GENRE(const string& name, MovieNode* movie)
{
    int index = HASH_FUNCTION(name);


    GenreHash* temp = genreTable[index];

    while (temp != NULL)
    {
        if (temp->name == name)
        {
            temp->movie[temp->count++] = movie;
            return;
        }
        temp = temp->next;
    }


    GenreHash* newnode = new GenreHash();

    newnode->name = name;
    newnode->movie[newnode->count++] = movie;

    newnode->next = genreTable[index];
    genreTable[index] = newnode;
}



ActorHash* SEARCH_ACTOR(const string& name)
{
    int index = HASH_FUNCTION(name);
    ActorHash* cur = actorTable[index];

    while (cur != NULL)
    {
        if (cur->name == name)
        {
            return cur;
        }

        cur = cur->next;
    }

    return NULL;
}



GenreHash* SEARCH_GENRE(const string& name)
{
    int index = HASH_FUNCTION(name);
    GenreHash* cur = genreTable[index];

    while (cur != NULL)
    {
        if (cur->name == name)
        {
            return cur;
        }

        cur = cur->next;
    }

    return NULL;
}




//......................................................................................








string readCSVField(string& line)
{
    string field;
    bool inQuotes = false;
    int i = 0;

    while (i < line.size())
    {
        char c = line[i];

        if (c == '"')
        {
            inQuotes = !inQuotes;
        }

        else if (c == ',' && !inQuotes)
        {
            i++;
            break;
        }

        else
        {
            field += c;
        }

        i++;
    }

    line = line.substr(i);



    if (!field.empty() && field.front() == '"' && field.back() == '"')
    {
        field = field.substr(1, field.size() - 2);
    }

    while (!field.empty() && (unsigned char)field.back() <= 32)
    {
        field.pop_back(); // Delete the last character
    }
    return field;
}


//     Load CSV into BST


string cleanstring(string old) {
    string newstr = "";
    for (int i = 0; i < old.size(); i++) {
        if ((old[i] > 47 && old[i] < 58) || (old[i] > 64 && old[i] < 91) || (old[i] > 96 && old[i] < 123) || old[i] == '-' || old[i] == ' ' || old[i] == '.' || old[i] == ',') {
            newstr += old[i];
        }
    }
    return newstr;
}

void loadMovies(const string& filename, MovieBST& tree, ActorBST& actorTree)
{
    ifstream in(filename);

    if (!in.is_open())
    {
        cout << "Cannot open in at: " << filename << endl;
        return;
    }

    string line;
    getline(in, line);
    int count = 0;

    while (getline(in, line))
    {
        MovieNode* movie = new MovieNode();
        int col = 0;

        string tempLine = line;

        while (!tempLine.empty())
        {
            string field = readCSVField(tempLine);

            switch (col)
            {
            case 1:
                if (!field.empty())
                {
                    movie->director = field;
                }
                break;

            case 6:                                                   // Actor 2
                if (!field.empty())
                {
                    field = cleanstring(field);
                    movie->LINKED_LIST_OF_ACTOR(field);
                    actorTree.addMovieToActor(field, movie);
                }
                break;

            case 10:                                                   // Actor 1
                if (!field.empty())
                {
                    field = cleanstring(field);
                    movie->LINKED_LIST_OF_ACTOR(field);
                    actorTree.addMovieToActor(field, movie);
                }
                break;

            case 14:                                                   // Actor 3
                if (!field.empty())
                {
                    field = cleanstring(field);
                    movie->LINKED_LIST_OF_ACTOR(field);
                    actorTree.addMovieToActor(field, movie);
                }
                break;

            case 9:
            {
                stringstream ss(field);
                string g;
                while (getline(ss, g, '|'))
                {
                    field = cleanstring(field);
                    movie->LINKED_LIST_OF_GENRE(g);
                }
                break;
            }
            case 11:
                field = cleanstring(field);
                movie->title = field;
                break;

            case 23: movie->year = field.empty() ? 0 : stoi(field);
                break;

            case 25: movie->rating = field.empty() ? 0.0f : stof(field);
                break;
            }

            col++;
        }

        tree.insert(movie);
        count++;
        if (count % 500 == 0) cout << "Loaded " << count << " movies...\n";
    }

    cout << "Total movies loaded: " << count << endl;
    in.close();
}



int main()
{
    MovieBST m1;
    ActorBST actorTree;
    Graph g1(6000);


    cout << "Loading data, wait please...\n";
    loadMovies("movie_metadata.csv", m1, actorTree);

    fillArray(m1.root, g1);
    cout << "Building Graph connections...\n";
    g1.CONNECTION();

    cout << "Populating Hash Tables...\n";
    for (int i = 0; i < g1.moviecount; i++)
    {
        MovieNode* movie = g1.movie[i];

        ACTOR* tempActor = movie->ahead;
        while (tempActor != NULL)
        {
            INSERT_ACTOR(tempActor->name, movie);
            tempActor = tempActor->next;
        }

        GENRE* tempGenre = movie->ghead;
        while (tempGenre != NULL)
        {
            INSERT_GENRE(tempGenre->name, movie);
            tempGenre = tempGenre->next;
        }
    }

    int choice;

    do {
        cout << "\n\n............................................\n\n";
        cout << "              MOVIE SYSTEM MENU             \n\n";
        cout << "............................................\n\n";

        cout << "1. Display all movies (In-order Traversal)\n";

        cout << "2. Search & Update Movie (BST)\n";

        cout << "3. Show recommended movies (Graph)\n";

        cout << "4. Find shortest path between two movies (BFS)\n";

        cout << "5. Search Actor (Hash Table)\n";

        cout << "6. Search Genre (Hash Table)\n";

        cout << "7. Search Co_Actor (Hash Table)\n";

        cout << "0. Exit\n";

        cout << "--------------------------------------------\n";

        cout << "Enter choice: ";

        cin >> choice;

        cin.ignore();

        if (choice == 1)
        {
            m1.displayInOrder();
        }

        else if (choice == 2)
        {
            string title;

            cout << "\nEnter movie title to update: ";

            getline(cin, title);

            MovieNode* movie = m1.search(title);

            if (movie)
            {
                cout << "\nCurrent Details of Movies:\n";
                movie->display();

                cout << "Updating...\n";
                m1.updateMovie(movie);

                cout << "\nUPDATED INFO:\n";
                movie->display();
            }

            else
            {
                cout << "MOVIE NOT FOUND.\n";
            }
        }

        else if (choice == 3)
        {
            string movieName;

            cout << "\nEnter title of MOVIE to see recommendations: ";

            getline(cin, movieName);

            int movieIndex = -1;

            for (int i = 0; i < g1.moviecount; i++)
            {
                if (g1.movie[i]->title == movieName)
                {
                    movieIndex = i;
                    break;
                }
            }

            if (movieIndex != -1)
            {
                g1.print_RECOMMENDED_movies(movieIndex);
            }

            else
            {
                cout << "Movie not found in graph.\n";
            }
        }

        else if (choice == 4)
        {
            string startName, endName;

            cout << "\nEnter start movie: ";
            getline(cin, startName);

            cout << "Enter end movie: ";
            getline(cin, endName);

            int startIndex = -1;
            int endIndex = -1;


            for (int i = 0; i < g1.moviecount; i++)
            {
                if (g1.movie[i]->title == startName)
                {
                    startIndex = i;
                }

                if (g1.movie[i]->title == endName)
                {
                    endIndex = i;
                }

            }

            if (startIndex != -1 && endIndex != -1)
            {
                g1.Shortest_path(startIndex, endIndex);
            }

            else
            {
                cout << "One or both movies not found.\n";
            }

        }

        else if (choice == 5)
        {
            string actorName;

            cout << "\nEnter Actor Name: ";
            getline(cin, actorName);

            ActorHash* result = SEARCH_ACTOR(actorName);

            if (result != NULL)
            {
                cout << "\nMovies featuring " << result->name << ":" << endl;

                for (int i = 0; i < result->count; i++)
                {
                    cout << "  * " << result->movie[i]->title << " (" << result->movie[i]->year << ")\n";
                }
            }

            else
            {
                cout << "Actor not found in database." << endl;
            }
        }

        else if (choice == 6)
        {
            string genreName;
            cout << "\nEnter Genre Name: ";
            getline(cin, genreName);

            GenreHash* result = SEARCH_GENRE(genreName);

            if (result != NULL)
            {
                cout << "\nMovies in genre " << result->name << ":" << endl;

                for (int i = 0; i < result->count; i++)
                {
                    cout << "  * " << result->movie[i]->title << endl;
                }
            }
            else
            {
                cout << "Genre not found.\n";
            }
        }

        else if (choice == 7)
        {
            string actorName;
            cout << "\nEnter Actor Name: ";
            getline(cin, actorName);

            ActorNode* actorNode = actorTree.search(actorName);

            if (actorNode != NULL)
            {
                cout << "\nCo-actors of " << actorName << ":\n";
                actorNode->displayCoActors();   
            }
            else
            {
                cout << "Actor not found.\n";
            }
        }

    } while (choice != 0);

    cout << "Exiting program..... Goodbye!\n";

    return 0;
}