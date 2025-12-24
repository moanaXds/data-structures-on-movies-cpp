#include <iostream>

using namespace std;

class Edge;
class MovieNode;
class ACTOR;

class Graph {
public:
    Edge** adj;
    MovieNode** movie;        // 1D array of pointer to movie
    int moviecount;

    Graph(int max_movies)
    {
        movie = new MovieNode * [max_movies];

        moviecount = 0;

        adj = new Edge * [max_movies];

        for (int i = 0; i < max_movies; i++)
        {
            adj[i] = NULL;
        }
    }

    void ADD_MOVIE(MovieNode* m)
    {
        movie[moviecount++] = m;
    }

    void ADD_EDGE(int i, int j)         //      insert at head
    {
        Edge* newedge = new Edge(j);    //      adj[i]=head
        newedge->next = adj[i];
        adj[i] = newedge;
    }

    void CONNECTION()
    {
        for (int i = 0; i < moviecount; i++)
        {
            for (int j = i + 1; j < moviecount; j++)
            {
                bool connect = false;

                //                 movie[i]->ahead  ( head of linkedlist of actors in that movie)

                for (ACTOR* a1 = movie[i]->ahead; a1 != NULL && !connect; a1 = a1->next)
                {
                    for (ACTOR* a2 = movie[j]->ahead; a2 != NULL && !connect; a2 = a2->next)
                    {
                        if (a1->name == a2->name)
                        {
                            connect = true;
                            break;
                        }
                    }
                }

                if (connect)
                {
                    ADD_EDGE(i, j);
                    ADD_EDGE(j, i);
                }
            }
        }
    }

    void print_RECOMMENDED_movies(int movieIndex)                     //  connected
    {
        cout << "Movies similar to \"" << movie[movieIndex]->title << "\":\n";

        Edge* temp = adj[movieIndex];
        while (temp != NULL)
        {
            int connectedIndex = temp->to;
            cout << "  - " << movie[connectedIndex]->title << endl;
            temp = temp->next;
        }
    }


    void Shortest_path(int start, int end)
    {
        int visited[6000] = { 00 };
        int queue[6000];
        int parent[6000];

        for (int i = 0; i < 6000; i++)
        {
            parent[i] = -1;
        }


        int front = 0;
        int rear = 0;

        queue[rear++] = start;
        visited[start] = 1;

        while (front < rear)
        {
            int current = queue[front++];

            if (current == end) break;

            Edge* temp = adj[current];
            while (temp != NULL)
            {
                int nxt = temp->to;
                if (!visited[nxt])
                {
                    visited[nxt] = 1;
                    parent[nxt] = current;
                    queue[rear++] = nxt;
                }
                temp = temp->next;
            }
        }


        if (!visited[end])
        {
            cout << "No paths exist between " << movie[start]->title
                << " and " << movie[end]->title << endl;
            return;
        }

        int path[6000];
        int count = 0;

        for (int v = end; v != -1; v = parent[v])
        {
            path[count++] = v;
        }

        cout << "SHORTED PATH: ";

        for (int i = count - 1; i >= 0; i--)
        {
            cout << movie[path[i]]->title;
            if (i != 0) cout << " -> ";
        }
        cout << endl;
    }

};
#pragma once
