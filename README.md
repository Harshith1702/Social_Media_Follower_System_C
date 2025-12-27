## Social_Media_Follower_System_C

## Overview
A **C-based mini project** that simulates a basic social media follower system using core data structures and file handling.

This project focuses on **user relationships (follow / unfollow)** and demonstrates how social connections can be modeled using graphs in C.

---

## What This Project Does
- Manages users
- Maintains follower–following relationships
- Stores data persistently using files
- Provides suggestions based on mutual connections

All interactions are done through a **menu-driven console interface**.

---

## Key Features
- Add new users  
- Follow and unfollow users  
- View followers of a user  
- View users someone is following  
- Suggest accounts based on mutual follows  
- Search for users  
- Persistent storage using text files  

---

## How It Works
- Users are stored in `users.txt`
- Follow relationships are stored in `follows.txt`
- An **adjacency matrix (graph)** represents follower relationships  
- Data is loaded when the program starts and saved after updates  

---

## Data Representation
- **Users** → Array of strings  
- **Followers graph** → 2D adjacency matrix  
- **Suggestions** → Derived from mutual follow logic  

---

## File Structure
```text
Social_Media_Follower_System_C/
├── README.md
├── Social_Media_Follower_System.c
├── users.txt
└── follows.txt
```

---

## Menu Options
1. Add User  
2. Follow User  
3. Unfollow User  
4. Show Followers  
5. Show Following  
6. Suggest Accounts  
7. Search User  
8. Exit  

---

## Technologies Used
- C Programming Language  
- File Handling  
- Arrays and Strings  
- Graph Representation (Adjacency Matrix)  

---

## Limitations
- Fixed maximum number of users  
- Console-based (no GUI)  
- No authentication system  
- Designed for learning purposes  

---

## Purpose
This project is intended to **strengthen understanding of C programming**,  
especially **graphs, file handling, and system design** using real-world inspired logic.

---

## Status
Completed – Educational Prototype
