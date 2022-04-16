#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define COUNT 8
#define MAX_SIZE 250    

struct Node {
    struct Node *left;
    struct Node *right;
    int data;
};

struct Node *createNode(int data);
struct Node *insert(struct Node *root, int data);
void printInOrder(struct Node *root);
struct Node *delete(struct Node *root, int data);
int findParent(struct Node *root, int data);
int *stringToInt(char *line, int *numInts);

int main(int argc, char *argv[]) {
    struct Node *root = NULL;

    while(1){
        int array[20];
        char input[MAX_SIZE];
        char command[MAX_SIZE];
        char arg[MAX_SIZE];

        fgets(input, sizeof input, stdin);
        if(strchr(input, ' ') != NULL){
            char *token = strtok(input, " ");
            int i = 0;
            while (token != NULL) {
                if(i==0){
                    strcpy(command, token);
                }else if(i==1){
                    strcpy(arg,token);
                }
                i++;
                token = strtok(NULL, " ");
            }
        }else{
            strcpy(command, input);
            for(int i = 0; i < MAX_SIZE; i++){
                if (command[i] == '\n'){
                    command[i] = '\0';
                    break;
                }
            }
        }
        
        if(strcmp(command, "CONSTRUCT")==0){
            if(root==NULL){  
                char *result = arg+1; // removes first character
                result[strlen(result)-2] = '\0';
                int numIntsExtracted = 0;
                int *array = stringToInt(result, &numIntsExtracted);

                for (int j = 0; j < numIntsExtracted; ++j) {
                    root = insert(root, array[j]);
                }
            }else{
                printf("Tree already constructed");
            }
        }else if(strcmp(command, "INSERT")==0){
            int numIntsExtracted = 0;
            int *array = stringToInt(arg, &numIntsExtracted);
            root = insert(root, array[0]);
            
        }else if(strcmp(command, "LIST")==0){
            printInOrder(root);
            printf("\n");
        }else if(strcmp(command, "PARENT")==0){
            int numIntsExtracted = 0;
            int *array = stringToInt(arg, &numIntsExtracted);
            int parent = findParent(root, array[0]);
            if(parent==-1){
                printf("IS ROOT\n");
            }else{
                printf("%d\n", parent);
            }
        }else if(strcmp(command, "DELETE")==0){
            int numIntsExtracted = 0;
            int *array = stringToInt(arg, &numIntsExtracted);
            root = delete(root, array[0]);
        }else{
            printf("Invalid command\n");
        }
    }
    
    return 0;
}

int *stringToInt(char *line, int *numInts) {
    char sNumArray[MAX_SIZE];
    strcpy(sNumArray, line);
    int *numbers = (int *) malloc(sizeof(int) * MAX_SIZE);
    char *tokens = strtok(sNumArray, ",");
    for (int i = 0; ; i++) {
        numbers[i] = atoi(tokens);
        tokens = strtok(NULL, ",");
        if (tokens == NULL) {
            *numInts = i+1;
            break;
        }       
    }
    return numbers;
}

struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = data;
    return newNode;
}

struct Node *insert(struct Node *root, int data) {
    if (root == NULL) {
        root = createNode(data);
    } else if (data <= root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

void printInOrder(struct Node *root) {
    if (root == NULL) {
        return;
    }
    printInOrder(root->left);
    printf("%d ", root->data);
    printInOrder(root->right);
}

int findParent(struct Node *root, int data) {
    if (root == NULL) {
        return -1;
    }
    if (root->left != NULL && root->left->data == data) {
        return root->data;
    }
    if (root->right != NULL && root->right->data == data) {
        return root->data;
    }
    if (data < root->data) {
        return findParent(root->left, data);
    } else {
        return findParent(root->right, data);
    }
}

struct Node *delete(struct Node *root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
    } else {
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
        struct Node *temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}


