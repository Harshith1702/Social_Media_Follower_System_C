#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define NAME_LEN 50

char users[MAX_USERS][NAME_LEN];
int userCount = 0;
int graph[MAX_USERS][MAX_USERS]; // follower -> followee

// Function declarations
void loadUsers();
void loadFollows();
void saveFollows();
int findUserIndex(char name[]);
void addUser(char name[]);
void followUser(char follower[], char followee[]);
void unfollowUser(char follower[], char followee[]);
void showFollowers(char name[]);
void showFollowing(char name[]);
void suggestAccounts(char name[]);
void searchUser(char name[]);

// MAIN FUNCTION
int main() {
    loadUsers();
    loadFollows();

    int choice;
    char name1[NAME_LEN], name2[NAME_LEN];

    while (1) {
        printf("\n--- Mini Instagram ---\n");
        printf("1. Add User\n");
        printf("2. Follow User\n");
        printf("3. Unfollow User\n");
        printf("4. Show Followers\n");
        printf("5. Show Following\n");
        printf("6. Suggest Accounts\n");
        printf("7. Search User\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1:
                printf("Enter new user name: ");
                fgets(name1, sizeof(name1), stdin);
                name1[strcspn(name1, "\n")] = '\0';
                addUser(name1);
                break;
            case 2:
                printf("Your name: ");
                fgets(name1, sizeof(name1), stdin);
                name1[strcspn(name1, "\n")] = '\0';
                printf("User to follow: ");
                fgets(name2, sizeof(name2), stdin);
                name2[strcspn(name2, "\n")] = '\0';
                followUser(name1, name2);
                break;
            case 3:
                printf("Your name: ");
                fgets(name1, sizeof(name1), stdin);
                name1[strcspn(name1, "\n")] = '\0';
                printf("User to unfollow: ");
                fgets(name2, sizeof(name2), stdin);
                name2[strcspn(name2, "\n")] = '\0';
                unfollowUser(name1, name2);
                break;
            case 4:
                printf("Enter user name: ");
                fgets(name1, sizeof(name1), stdin);
                name1[strcspn(name1, "\n")] = '\0';
                showFollowers(name1);
                break;
            case 5:
                printf("Enter user name: ");
                fgets(name1, sizeof(name1), stdin);
                name1[strcspn(name1, "\n")] = '\0';
                showFollowing(name1);
                break;
            case 6:
                printf("Enter your user name: ");
                fgets(name1, sizeof(name1), stdin);
                name1[strcspn(name1, "\n")] = '\0';
                suggestAccounts(name1);
                break;
            case 7:
                printf("Enter user to search: ");
                fgets(name1, sizeof(name1), stdin);
                name1[strcspn(name1, "\n")] = '\0';
                searchUser(name1);
                break;
            case 8:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}

// FUNCTION DEFINITIONS

void loadUsers() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) return;

    while (fgets(users[userCount], NAME_LEN, file)) {
        users[userCount][strcspn(users[userCount], "\n")] = '\0';
        userCount++;
    }
    fclose(file);
}

void loadFollows() {
    FILE *file = fopen("follows.txt", "r");
    if (file == NULL) return;

    char follower[NAME_LEN], followee[NAME_LEN];
    while (fscanf(file, "%s %s", follower, followee) == 2) {
        int i = findUserIndex(follower);
        int j = findUserIndex(followee);
        if (i != -1 && j != -1) {
            graph[i][j] = 1;
        }
    }
    fclose(file);
}

void saveFollows() {
    FILE *file = fopen("follows.txt", "w");
    int i=0,j=0;
    for (i = 0; i < userCount; i++) {
        for (j = 0; j < userCount; j++) {
            if (graph[i][j]) {
                fprintf(file, "%s %s\n", users[i], users[j]);
            }
        }
    }
    fclose(file);
}

int findUserIndex(char name[]) {
	int i=0;
    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i], name) == 0)
            return i;
    }
    return -1;
}

void addUser(char name[]) {
    if (userCount >= MAX_USERS) {
        printf("User limit reached.\n");
        return;
    }
    if (findUserIndex(name) != -1) {
        printf("User already exists.\n");
        return;
    }
    strcpy(users[userCount++], name);

    FILE *file = fopen("users.txt", "a");
    fprintf(file, "%s\n", name);
    fclose(file);

    printf("User '%s' added.\n", name);
}

void followUser(char follower[], char followee[]) {
    int i = findUserIndex(follower);
    int j = findUserIndex(followee);
    if (i == -1 || j == -1) {
        printf("User not found.\n");
        return;
    }
    if (i == j) {
        printf("You cannot follow yourself.\n");
        return;
    }
    if (graph[i][j]) {
        printf("You already follow '%s'.\n", followee);
        return;
    }
    graph[i][j] = 1;
    saveFollows();
    printf("%s now follows %s.\n", follower, followee);
}

void unfollowUser(char follower[], char followee[]) {
    int i = findUserIndex(follower);
    int j = findUserIndex(followee);
    if (i == -1 || j == -1) {
        printf("User not found.\n");
        return;
    }
    if (!graph[i][j]) {
        printf("You are not following '%s'.\n", followee);
        return;
    }
    graph[i][j] = 0;
    saveFollows();
    printf("%s has unfollowed %s.\n", follower, followee);
}

void showFollowers(char name[]) {
    int index = findUserIndex(name);
    if (index == -1) {
        printf("User not found.\n");
        return;
    }
    printf("Followers of %s:\n", name);
    int found = 0,i=0;
    for (i = 0; i < userCount; i++) {
        if (graph[i][index]) {
            printf("- %s\n", users[i]);
            found = 1;
        }
    }
    if (!found) printf("No followers.\n");
}

void showFollowing(char name[]) {
    int index = findUserIndex(name);
    if (index == -1) {
        printf("User not found.\n");
        return;
    }
    printf("%s is following:\n", name);
    int found = 0,j=0;
    for (j = 0; j < userCount; j++) {
        if (graph[index][j]) {
            printf("- %s\n", users[j]);
            found = 1;
        }
    }
    if (!found) printf("Not following anyone.\n");
}

void suggestAccounts(char name[]) {
    int index = findUserIndex(name);
    if (index == -1) {
        printf("User not found.\n");
        return;
    }

    int suggested[MAX_USERS] = {0},j=0,i=0;
    for (i = 0; i < userCount; i++) {
        if (graph[index][i]) {
            for (j = 0; j < userCount; j++) {
                if (graph[i][j] && j != index && !graph[index][j]) {
                    suggested[j] = i + 1;
                }
            }
        }
    }

    printf("Suggested accounts for %s:\n", name);
    int found = 0;
    for (i = 0; i < userCount; i++) {
        if (suggested[i]) {
            printf("- %s (Followed by %s)\n", users[i], users[suggested[i] - 1]);
            found = 1;
        }
    }
    if (!found) printf("No suggestions.\n");
}

void searchUser(char name[]) {
    int index = findUserIndex(name);
    if (index == -1)
        printf("User '%s' not found.\n", name);
    else
        printf("User '%s' exists in the system.\n", name);
}
