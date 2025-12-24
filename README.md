**C++ implementation of core data structures for managing a movies dataset.**

---

## Overview

This project demonstrates a complete data structure system to store, search, and analyze movies, actors, and genres. It includes:

* **Binary Search Trees (BST):** For storing and updating movies and actors efficiently.
* **Graphs:** To recommend similar movies based on shared actors and to find the shortest path between movies using BFS.
* **Hash Tables:** For fast lookup of actors and genres, supporting multiple movies per actor or genre.
* **Linked Lists:** To maintain actors per movie and movies per actor, as well as connected movies in graphs.
* **CSV Parsing & Cleaning:** Load and process raw movie dataset with proper handling of quoted fields, genres, and actor names.

  ---
  
<img width="852" height="592" alt="image" src="https://github.com/user-attachments/assets/d0611eca-bfd9-468f-8660-8d774f605772" />
<img width="793" height="570" alt="image" src="https://github.com/user-attachments/assets/d8e4d4df-60c4-424b-a46a-31def33ad531" />
<img width="828" height="581" alt="image" src="https://github.com/user-attachments/assets/ff2f15d6-c660-43da-a6cb-bb805c2f82c8" />
<img width="614" height="159" alt="image" src="https://github.com/user-attachments/assets/8ac2b802-9c75-443d-8692-4d5e3f6da14a" />
<img width="897" height="585" alt="image" src="https://github.com/user-attachments/assets/4ba8638e-c26d-49b8-8479-411029d0389c" />

## Features

* Load movie dataset from CSV.
* Display all movies in-order (BST traversal).
* Search and update movie details.
* Recommend similar movies based on shared actors (Graph connections).
* Find shortest path between two movies (BFS on Graph).
* Search actors and genres efficiently using hash tables.
* Display all movies of an actor.
* Display co-actors of a given actor.
* Maintain multiple data structures working together (BST, Graph, Hash Table, Linked List).

---

## Files Structure

```
MovieProject/
│
├─ main.cpp
├─ MovieNode.h
├─ Actor_Genre.h
├─ MoviesOfActor.h
├─ Edge.h
├─ ActorBST.h
├─ MovieBST.h
├─ Graph.h
└─ movie_metadata.csv
```

## Dataset

* `movie_metadata.csv` contains movie details including title, year, rating, director, actors, and genres.

## Author

Moana Hamid



