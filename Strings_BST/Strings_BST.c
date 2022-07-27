#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#define MAX 20
#define LINE_SIZE 255

// Structs-----------------------------------------------------------------------
typedef struct node {
    char word[MAX];
    char fileNames[MAX][MAX];        // "\0" will be assigned to the deleted rows (when deleting a word)
    struct node *left, *right;
    int lastRow;                     // keeps the index of the last row of the fileName in fileNames[][]
}NODE;


// Prototypes--------------------------------------------------------------------------
NODE* insert(NODE *root, char newWord[MAX], char newFileName[MAX]);
NODE* createNode(char newWord[MAX], char newFileName[MAX]);
NODE* search(NODE *root, char key[MAX]);
void inOrder(NODE *root);
void readFile(NODE** ptrRoot);
int isDuplicateFileName(NODE* currentNode, char fileName[MAX]);
void displayFileNames();
void deleteFile(NODE** ptrRoot, char fileToBeDeleted[MAX]);
void deleteWord(NODE* currentNode, char* word, char fileToBeDeleted[MAX], NODE** ptrRoot);
NODE* deleteNode(NODE *root, char key[MAX]);
NODE* findMin(NODE *root);
NODE* deepCopyStruct(NODE* root, NODE* tmpRoot);


// Main --------------------------------------------------------------------------------
int main(void) {
    NODE* root=NULL;
    NODE* tmpNode;
    char key[MAX];
    int choice=0;
    int i;
    
    readFile(&root);

   do
   {
        printf("\n--------------MENU-------------\n");
        printf("1. Display tree inOrder\n2. Search Word\t3. Delete File\n0. Exit\n");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
            case 1:
                inOrder(root);
                break;

            case 2:
                printf("Please enter the Word: ");
                scanf("%s", &key);
                printf("\n");

                tmpNode = search(root, key);
                if (tmpNode == NULL)
                {
                    printf("<%s> is not in Tree!\n", key);
                }
                else
                {
                    printf("<%s>\n", tmpNode->word);
                    for ( i = 0; i <= tmpNode->lastRow; i++)
                    {
                        if (strcmp(tmpNode->fileNames[i], "-1") != 0)
                        {
                            puts(tmpNode->fileNames[i]);           // print file names which this word occurs
                        }
                    }
                    printf("\n");
                }
                break;

            case 3:
                printf("Please Enter File to be Deleted: \n");
                displayFileNames();
                printf("\n");
                scanf("%s", &key);
                deleteFile(&root, key);
                break;

            default: 
                break;
        }
   } while (choice);
   
    printf("\n------------EXIT-----------\n");

    return 0;
}


// Functions-------------------------------------------------------

NODE* insert(NODE *root, char newWord[MAX], char newFileName[MAX]) {

    if (root == NULL)
    {
        root = createNode(newWord, newFileName);
        return root;
    }
    
    if (strcmp(newWord, root->word) == -1)
    {
        root->left = insert(root->left, newWord, newFileName);
    }

    if (strcmp(newWord, root->word) == 1)
    {
        root->right = insert(root->right, newWord, newFileName);
    }

    return root;
}


NODE* createNode(char newWord[MAX], char newFileName[MAX]) {

    NODE *newNode = (NODE*)malloc(1*sizeof(NODE));
    strcpy(newNode->word, newWord);
    newNode->lastRow = 0;
    strcpy(newNode->fileNames[newNode->lastRow], newFileName);
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


NODE* search(NODE *root, char key[MAX]) {

    if (root == NULL)
    {
        //printf("Word not Found!\n");
        return root;
    }

    if (strcmp(root->word, key) == 0)
    {
        //printf("Word Found!\n");
        return root;
    }
    else if (strcmp(key, root->word) == -1)
    {
        root = search(root->left, key);
        return root;
    }
    else if (strcmp(key, root->word) == 1)
    {
        root = search(root->right, key);
        return root;
    }
}


void inOrder(NODE *root) {
    int i;

    if (root != NULL)
    {
        inOrder(root->left);                        //left
        puts(root->word);                           //  print word
        
        for ( i = 0; i <= root->lastRow; i++)
        {
            if (strcmp(root->fileNames[i], "\0") != 0)
            {
                puts(root->fileNames[i]);           // print file names which this word occurs
            }
        }
        printf("\n");           
        
        inOrder(root->right);                       // right
    }

}


void readFile(NODE** ptrRoot) {

    FILE* fptr;
    char line[LINE_SIZE];
    char* word;
    char fileName[MAX];
    char delimiter[MAX] = " ";
    NODE* currentNode;
    
    fptr = fopen("test.txt", "r");
    if (fptr == NULL)
    {
        printf("ERROR while opening FILE.\n");
    }
    
    while (fgets(line, LINE_SIZE, fptr))      // fgets() reads file line by line and assigns each line to line[LINE_SIZE]
    {
        word = strtok(line, delimiter);    // first token is the file name.
        strcpy(fileName, word);             // assign x.txt to fileName[]

        word = strtok(NULL, delimiter);     // this is the first word of the sentence (first word of the line after x.txt)

        while (word != NULL)
        {

            currentNode = search(*ptrRoot, word);          // search(root, key)

            if (currentNode == NULL)            // if the word is not in the tree yet (if the word is not duplicate) insert it
            {
                *ptrRoot = insert(*ptrRoot, word, fileName);
            }
            else    // if the word is duplicate (if currentNode is not NULL) , check it's file name
            {
                if (!isDuplicateFileName(currentNode, fileName))       // if the file name is not duplicate , add the fileName to the last row of FileNames[][]
                {
                    (currentNode->lastRow)++;
                    strcpy(currentNode->fileNames[currentNode->lastRow], fileName);
                }
                //else printf("The Word and it's File Name is Duplicate!");
            }

            word = strtok(NULL, delimiter);    // next word is in the token
            
            // if next word is the last word of the line , it is in the form of {'a', '\n', '\0'}
            // so we assign '\0' to the word[strlen(word)-1]
            if (word != NULL && (word[strlen(word)-1] == '\n'))
            {
                word[strlen(word)-1] = '\0';
            }
            
        }
    
    }

    fclose(fptr);
} 


int isDuplicateFileName(NODE* currentNode, char fileName[MAX]) {
    int i;

    for ( i = 0; i <= currentNode->lastRow; i++)
    {
        if (strcmp(currentNode->fileNames[i], fileName) == 0)   // if the fileName is already in fileNames[i] (if it is Duplicate)
        {
            return 1;
        }
    }

    return 0;
}


void displayFileNames() {
    FILE* fptr;
    char line[LINE_SIZE];
    char* word;
    char delimiter[MAX] = " ";

    fptr = fopen("test.txt", "r");
    
    while (fgets(line, LINE_SIZE, fptr))
    {
        word = strtok(line, delimiter);     // file name is assigned to the word , which is the first word of each line
        puts(word);
    }
    
} 


void deleteFile(NODE** ptrRoot, char fileToBeDeleted[MAX]) {
    FILE* fptr;
    NODE* currentNode;
    char line[LINE_SIZE];
    char* word = " ";
    char delimiter[MAX] = " ";
    int flag=1;

    fptr = fopen("test.txt", "r");
    if (fptr == NULL)
    {
        printf("ERROR while opening FILE.\n");
    }

    while (!feof(fptr) && flag == 1)
    {
        fgets(line, LINE_SIZE, fptr);               // get a new line
        word = strtok(line, delimiter);             // assign first word of the new line to word (which is a file name)
        if (strcmp(word, fileToBeDeleted) == 0)
        {
            flag = 0;
        }
    }
    
    if (flag == 0)                              // if the file name(word) is found on x.txt
    {
        word = strtok(NULL, delimiter);         // word keeps second word of the current line
        while (word != NULL)              // iterate each word of the current line (starting from second word) until the end of the line
        {
            currentNode = search(*ptrRoot, word);
            /*
            if one word occurs in the line for 2 times , after deleting the first word , if we 
            search for that word again currentNode will be equal to NULL because that word
            has already been deleted! so we use an if to check if currentNode is NULL or not.
            if it is NULL , it means that the word is not in the tree anymore  
            */
            if (currentNode != NULL)    // if the word is in the tree
            {
                deleteWord(currentNode, word, fileToBeDeleted, ptrRoot);
            }
            
            word = strtok(NULL, delimiter);     // iterate to next word
            if (word != NULL && (word[strlen(word)-1] == '\n'))     // for the last word of the line
            {
                word[strlen(word)-1] = '\0';
            }
        }
        printf("%s has been Deleted Successfully!\n", fileToBeDeleted);
    }
    else printf("File NOT Found!\n");

}


void deleteWord(NODE* currentNode, char* word, char fileToBeDeleted[MAX], NODE** ptrRoot) {
    int i, numOfNulls=0, j;

    for ( i = 0; i <= currentNode->lastRow; i++)
    {
        if (currentNode->fileNames[i] == '\0')          // counts number of null rows
        {
            numOfNulls++;
        }
        if (strcmp(currentNode->fileNames[i], fileToBeDeleted) == 0)    // finds the row of fileToBeDeleted in filenames[i]
        {
            j = i;                                                      // j equals to index of desired row
        }
    }
    
    if (numOfNulls == currentNode->lastRow)      // delete the entire node if there is only one file fot that word
    {
        *ptrRoot = deleteNode(*ptrRoot, word);
    }
    else        // only delete the file name from fileNames[i]
    {
        strcpy(currentNode->fileNames[j], "\0");
    }

}


NODE* deleteNode(NODE *root, char key[MAX]) {       // ususal function to delete a node from binary search tree
    NODE *tmpRoot;


    if (root == NULL)
    {
        //printf("Node not found!\n");
        return;
    }
    else if (strcmp(key, root->word) > 0)
    {
        root->right = deleteNode(root->right, key);
    }
    else if (strcmp(key, root->word) < 0)
    {
        root->left = deleteNode(root->left, key);
    }
    else        // if the Node to be deleted is the current Node
    {
        if (root->left == NULL)     // if the node to be deleted has 1 or 0 child
        {
            tmpRoot = root->right;
            free(root);
            return tmpRoot;
        }
        else if (root->right == NULL)   // if the node to be deleted has 1 or 0 child
        {
            tmpRoot = root->left;
            free(root);
            return tmpRoot;
        }
        
        tmpRoot = findMin(root->right);
        //strcpy(root->word, tmpRoot->word);
        root = deepCopyStruct(root, tmpRoot);
        /*
            tmpRoot = successor  and  we have copied the successor data to root data (swap data by deep copy)
            now we want to delete the succesor and then return NULL to the succesor's parent's left 
            (because successor is a leaf node and has 0 childs)
                 50
               /     \
              30      70
             /  \    /  \
           20   40  60   80
        */
        root->right = deleteNode(root->right, tmpRoot->word);
    }
    
    return root;
}


NODE* findMin(NODE *root) {         // finds minimum node of a binary search tree 
    NODE *tmpRoot = root;

    if (root == NULL)
    {
        printf("Tree is Empty!");
        return root;
    }

    while (tmpRoot->left != NULL)
    {
        tmpRoot = tmpRoot->left;
    }
    
    return tmpRoot;
}


NODE* deepCopyStruct(NODE* root, NODE* tmpRoot) {
    int i;

    strcpy(root->word, tmpRoot->word);
    for ( i = 0; i <= tmpRoot->lastRow; i++)
    {
        strcpy(root->fileNames[i], tmpRoot->fileNames[i]);
    }
    root->right = tmpRoot->right;
    root->left = tmpRoot->left;
    root->lastRow = tmpRoot->lastRow;

    return root;
}