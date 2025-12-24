#include <iostream>

using namespace std;

class ActorNode;
class MovieNode;

class ActorBST {

private:
    ActorNode* addmoviestoTree(ActorNode* actor, const string& name, MovieNode* movie)
    {
        if (actor == NULL)
        {
            ActorNode* newNode = new ActorNode(name);
            newNode->addmovieToActorsList(movie);
            return newNode;
        }

        if (name == actor->name)
        {
            actor->addmovieToActorsList(movie);
            return actor;
        }

        if (name < actor->name)
        {
            actor->left = addmoviestoTree(actor->left, name, movie);
        }

        else
        {
            actor->right = addmoviestoTree(actor->right, name, movie);
        }

        return actor;
    }

    ActorNode* searchRec(ActorNode* node, const string& name)
    {
        if (node == NULL)return node;

        if (node->name == name)
        {
            return node;
        }

        if (name < node->name)
        {
            return searchRec(node->left, name);
        }

        else
        {
            return searchRec(node->right, name);
        }

    }

public:
    ActorNode* root;

    ActorBST() { root = NULL; }

    void addMovieToActor(const string& actorName, MovieNode* movie)
    {
        root = addmoviestoTree(root, actorName, movie);
    }

    ActorNode* search(const string& name)
    {
        return searchRec(root, name);
    }
};

#pragma once
