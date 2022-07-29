#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#define MAX 20
#define N 9


//--------------------------STRUCTS----------------------------
typedef struct stack
{
    int top;
    int *array;
    unsigned capacity;
}STACK;


//---------------------GLOBAL VARS-----------------------------
int graph[MAX][MAX];
STACK pathStack;
int found = 0;       // if we want to use findPath() function again , we must assign 0 to this variable


//----------------------PROTOTYPES----------------------------
void initGraph();
void printGraph();
void readFile();
void addEdge(int u, int v, int w);
void initStack();
void push();
void pop();
int isEmpty();
int isInStack(int vertex);
void printStack();
void findPath(int u, int target);
int findMaxEdge(int* vertex1, int* vertex2);
void updateMST(int u, int v, int w);


//----------------------MAIN-----------------------------------
int main(void) {
    int choice=0;
    int u, v, w;

    initGraph();
    initStack();
    readFile();
    printf("Initial MST: \n");
    printGraph();
    
    do
    {
        printf("\n--------------------MENU-------------------\n");
        printf("1. Print Graph  2.Print Path(Stack)\n");
        printf("3. Add Edge\n0. Exit\n");
        scanf("%d", &choice);
        
        switch (choice)
        {
        case 1:
            printGraph();
            break;
        case 2:
            printStack();
            break;
        case 3:
            printf("Please enter U, V and W respectively: \n");
            scanf("%d %d %d", &u, &v, &w);
            initStack();
            found = 0;
            updateMST(u, v, w);
            printGraph();
            break;
        default:
            break;
        }

    } while (choice != 0);
    

    printf("\n\nEND");
    
    return 0;
}



//---------------------------------FUNCTIONS---------------------------
void initGraph() {
    int i, j;

    for ( i = 0; i < MAX; i++)
        for ( j = 0; j < MAX; j++)
            graph[i][j] = 0;
    
}


void initStack() {

    pathStack.capacity = 100;
    pathStack.array = (int*)calloc(pathStack.capacity, sizeof(int));
    pathStack.top = -1;
}


void push(int val) {
    pathStack.top++;
    pathStack.array[pathStack.top] = val;
}


void pop() {
    if (!isEmpty())
    {
        pathStack.array[pathStack.top] = 0;
        pathStack.top--;    
    }
    else printf("Cannot pop()! Stack is Empty.\n");
    
}


int isEmpty() {
    if (pathStack.top == -1)
    {
        return 1;
    }
    return 0;
}


void printStack() {
    int i=0;

    if (!isEmpty())
    {
        for ( i = 0; i <= pathStack.top; i++)
        {
            printf("%d ->", pathStack.array[i]);
        }
        printf("\n");
    }
    else printf("Stack is Empty.\n");
    
}


int isInStack(int vertex) {
    int i=0;

    while (i <= pathStack.top)
    {
        if (pathStack.array[i] == vertex)
        {
            return 1;
        }
        i++;
    }

    return 0;
}


void printGraph() {
    int i, j;
    
    printf("\n    ");
    for ( i = 0; i < N; i++)
    {
        printf("%d ", i);
    }
    printf("\n    ");
    for ( i = 0; i < N; i++)
    {
        printf("| ");
    }
    printf("\n");

    for ( i = 0; i < N; i++)
    {   
        printf("%d-- ", i);
        for ( j = 0; j < N; j++)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}


void readFile() {
    FILE *fptr;
    char W[MAX], N1[MAX], N2[MAX];
    int w, u, v;


    fptr = fopen("Sample_MST.txt", "r");
    if (!fptr)
    {
        printf("File not Found\n");
    }
    
    while (!feof(fptr))
    {
        fscanf(fptr, "%s", W);
        w = atoi(W);
        fscanf(fptr, "%s", N1);
        u = atoi(N1);
        fscanf(fptr, "%s", N2);
        v = atoi(N2);

        graph[u][v] = w;
        graph[v][u] = w;
    }

    fclose(fptr);
}


void addEdge(int u, int v, int w) {

    if (graph[u][v] != 0 || graph[v][u] != 0)
    {
        printf("There is already an edge from <%d>to<%d>.\n", u, v);
        return;
    }

    graph[u][v] = w;
    graph[v][u] = w;
    printf("Edge added sucessfully.\n");
}


void updateMST(int u, int v, int w) {
    int vertex1, vertex2, maxWeight;

    if (graph[u][v] != 0)
    {
        if (graph[u][v] > w)
        {
            printf("Current Weight: %d\n", graph[u][v]);
            printf("Input Weight: %d\n", w);
            graph[u][v] = w;
            graph[v][u] = w;
            printf("New Weight: %d\n", graph[u][v]);
        }

        else if (graph[u][v] <= w)
        {
            printf("Current Weight: %d\n", graph[u][v]);
            printf("Input Weight: %d\n", w);
            printf("Weight does not change!\n");
        }
        
    }
    else if (u>=N || v>=N)
    {
        printf("U or V vertices are not in MST.");
    }
    else if (graph[u][v] == 0)
    {
        findPath(u, v);
        maxWeight = findMaxEdge(&vertex1, &vertex2);
        printf("Input Weight: %d\n", w);
        printf("Maximum Weight in the Cycle: %d\n", maxWeight);

        if (w < maxWeight)
        {
            graph[vertex1][vertex2] = 0;
            graph[vertex2][vertex1] = 0;
            addEdge(u, v, w);
        }
        else printf("Edge is not Added.\n");
        
        //printf("here\n");
    }

}


void findPath(int u, int target) {
    int j;
    
    //printf("\n-----------\n");
    push(u);
    //printStack();

    j = 1;
    while ( j < N && !found)
    {
        //printf("u=%d, j=%d\n", u, j);
        if (u == target)
        {
            //printf("Target found.\n");
            found = 1;
            return;
        }
        else if ( (graph[u][j] != 0) && (!isInStack(j)) )
        {
            //printf("u=%d, j=%d\n", u, j);
            findPath(j, target);
        }

        j++;
    }
    
    if (!found)
    {
        pop();
        //printStack();    
    }

    
}


int findMaxEdge(int* vertex1, int* vertex2) {
    int i=1, maxWeight=0, u, v;

    while (i <= pathStack.top)
    {
        u = pathStack.array[i-1];
        v = pathStack.array[i];

        if (graph[u][v] > maxWeight)
        {
            maxWeight = graph[u][v];
            *vertex1 = u;
            *vertex2 = v;
        }
        
        i++;
    }

    return maxWeight;
}



