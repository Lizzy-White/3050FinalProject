/* 
 * File:   main.c
 * Author: MonBorg
 *
 * Created on November 15, 2015, 4:03 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2
#define PARENT(i) (i-1)/2


//GCost = Distance from starting point
//HCost = Distance from ending point
//FCost = Sum of GCost and HCost
typedef struct GraphNode
{
    int GCost;
    int HCost;
    int FCost;
    struct GraphNode* Parent;
    bool open;
    bool closed;
    bool wall;
    int iPos;
    int jPos;
} Node;

typedef struct NodeHeap {
    Node* A;
    int size;
} node_t;


/*
 * 
 */
void AddNode(Node** list, Node node, int* size);
void init_heap(node_t* heap);
void swap(Node* x, Node* y);
void min_heapify(node_t* heap, int i, int n);
void build_min_heap(node_t* heap, int n);
void insert(node_t* heap, Node x);
Node extract_min(node_t* heap);
void decrease_key(node_t* heap, int i, Node key);
void print_array(node_t heap);

void SetFCost(Node* curr, Node start, Node end);
Node** GetNeighbours(Node curr, Node** nodeArray, int nodeArraySize, int* neighbourSize);
void MallocNode(Node*** node, int* size);
bool CompareNode(Node one, Node two);
void AddToList(Node** nodeList, Node addedNode, int *size);
void PrintList(int size, Node* nodeList);
int CalcCost(Node curr, Node target);

void GetStartingAndEndingNode(Node* start, Node* end, int size);
void Malloc2dArray(Node*** node, int size);
void GenerateMap(Node** node, int size);
void PrintMaze(Node** node, int size, Node start, Node end);

int main(int argc, char** argv) {
    int size = 6;
    Node** nodeArray;
    Node startingNode;
    startingNode.FCost = 0;
    Node endingNode;
    
    GetStartingAndEndingNode(&startingNode, &endingNode, size);
    Malloc2dArray(&nodeArray, size);
    GenerateMap(nodeArray, size);
    PrintMaze(nodeArray, size, startingNode, endingNode);
    
    int openSize = 0, closedSize = 0;
    node_t openList;
    Node* closedList = (Node*) malloc(sizeof(Node));
    //memset(closedList, 0, sizeof(Node));
    Node curr = startingNode;
    
    init_heap(&openList);
    insert(&openList, curr);

    //print_array(openList);
    
    int neighbourSize=0;
    //Node* list = GetNeighbours(curr, nodeArray, size, &neighbourSize);
    //PrintList(neighbourSize, GetNeighbours(curr, nodeArray, size, &neighbourSize));

    int Buffer = 1, buff;
    for(buff = 0; buff<Buffer; buff++)//Should continue until every node is closed or until found
    {
        curr = extract_min(&openList);
        AddNode(&closedList, curr, &closedSize);
        //printf("%d %d %d \n", curr.jPos, curr.iPos, curr.closed);
        //curr.closed = true;
        //printf("%d %d %d \n\n", nodeArray[curr.jPos][curr.iPos].jPos, nodeArray[curr.jPos][curr.iPos].iPos, nodeArray[curr.jPos][curr.iPos].closed);
        if(CompareNode(curr, endingNode))
        {
            buff = Buffer+1;
        }
        
        Node** neighbours = GetNeighbours(curr, nodeArray, size, &neighbourSize);
        int i;
        for(i = 0; i<neighbourSize; i++)
        {
            //if(!neighbours[i].closed && (!neighbours[i].open || neighbours[i].FCost < curr.FCost))  //TODO: Revisit.  Fcost is iffy
            {
                //SetFCost(&(neighbours[i]), startingNode, endingNode);
                //printf("Cost: %d %d %d\n", neighbours[i].GCost, neighbours[i].HCost, neighbours[i].FCost);
                //(neighbours[i]).Parent = &curr;
                //if(!neighbours[i].open)
                {
                    //addNode(openList, neighbours[i]);
                }
            }
        }
        
    }
    
    
    
    
    
    return (EXIT_SUCCESS);
}

void AddNode(Node** list, Node node, int* size)
{
    if(*size > 0)
        *list = realloc(*list, sizeof(Node)*(*size+1));
    *list[*size++] = node;
}

void init_heap(node_t* heap) {
    memset(heap, 0, sizeof(node_t));
}

void swap(Node* x, Node* y) {
    Node temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void min_heapify(node_t* heap, int i, int n) {
    int l, r, min;
    l = LEFT(i);
    r = RIGHT(i);
    if (l < n && heap->A[l].FCost < heap->A[i].FCost)
            min = l;
    else
            min = i;
    if (r < n && heap->A[r].FCost < heap->A[min].FCost)
            min = r;
    if (min != i) {
            swap(&heap->A[i], &heap->A[min]);
            min_heapify(heap, min, n);
    }
}

void build_min_heap(node_t* heap, int n) {
    int i;
    for (i = n/2; i >= 0; i--)
            min_heapify(heap, i, n);
}

void insert(node_t* heap, Node x) {
    heap->A = (Node*) realloc(heap->A, sizeof(Node)*(heap->size + 1));
    heap->A[heap->size] = x;
    decrease_key(heap, heap->size++, x);
}

Node extract_min(node_t* heap) {
    if (heap->size < 1) {
        printf("\nError.  Heap underflow.\n");
        exit(15);
    }
    Node min = heap->A[0];
    heap->A[0] = heap->A[heap->size - 1];
    heap->size--;
    min_heapify(heap, 0, heap->size);
    return min;
}

void decrease_key(node_t* heap, int i, Node key) {
    if (key.FCost > heap->A[i].FCost) {
        printf("\nError.  New key is larger than current key.\n");
        return;
    }

    heap->A[i] = key;
    while (i > 0 && heap->A[PARENT(i)].FCost > heap->A[i].FCost) {
        swap(&heap->A[i], &heap->A[PARENT(i)]);
        i = PARENT(i);
    }	
}

void print_array(node_t heap) {
    int i;
    printf("\n\n");
    for (i = 0; i < heap.size; i++)
    {
        if(heap.A[i].FCost < 0)
        {
            printf("noFCost ");
        } else
        {
            printf("%d ", heap.A[i].FCost);
        }
    }
}

void SetFCost(Node* curr, Node start, Node end)
{
    (*curr).GCost = CalcCost((*curr), start);
    (*curr).HCost = CalcCost((*curr), end);
    (*curr).FCost = (*curr).GCost + (*curr).HCost;
}

//Goes clockwise. Starting from the node above
Node** GetNeighbours(Node curr, Node** nodeArray, int nodeArraySize, int* neighbourSize)
{
    Node** temp;
    (*neighbourSize) = 0;
    if(curr.jPos-1 >= 0)
    {
        if(!nodeArray[curr.jPos-1][curr.iPos].wall)
        {
            nodeArray[curr.jPos-1][curr.iPos].Parent = &curr;
            MallocNode(&temp, neighbourSize);
            temp[(*neighbourSize)-1] = &nodeArray[curr.jPos-1][curr.iPos];
            (*neighbourSize)++;
        }
    }
    if(curr.iPos+1 < nodeArraySize)
    {
        if(!nodeArray[curr.jPos][curr.iPos+1].wall)
        {
            nodeArray[curr.jPos][curr.iPos+1].Parent = &curr;
            MallocNode(&temp, neighbourSize);
            temp[(*neighbourSize)-1] = &nodeArray[curr.jPos][curr.iPos+1];
            (*neighbourSize)++;
        }
    }
    if(curr.jPos+1 < nodeArraySize)
    {
        if(!nodeArray[curr.jPos+1][curr.iPos].wall)
        {
            nodeArray[curr.jPos+1][curr.iPos].Parent = &curr;
            MallocNode(&temp, neighbourSize);
            temp[(*neighbourSize)-1] = &nodeArray[curr.jPos+1][curr.iPos];
            (*neighbourSize)++;
        }
    }
    if(curr.iPos-1 >= 0)
    {
        if(!nodeArray[curr.jPos][curr.iPos-1].wall)
        {
            nodeArray[curr.jPos][curr.iPos-1].Parent = &curr;
            MallocNode(&temp, neighbourSize);
            temp[(*neighbourSize)-1] = &nodeArray[curr.jPos][curr.iPos-1];
            (*neighbourSize)++;
        }
    }
    
    return temp;
}

void MallocNode(Node*** node, int* size)
{
    if((*size) >= 0)
    {
        if((*size) == 0)
        {
            (*node) = (Node**) malloc(sizeof(Node*));
            (**node) = (Node*) malloc(sizeof(Node));
        } else if ((*size) > 0)
        {
            (*node) = (Node**) realloc((*node), sizeof(Node*) * ((*size)+1));
            (**node) = (Node*) malloc(sizeof(Node));
        }
        (*size)++;
    } else
    {
        printf("ERROR: Size is negative");
    }
}

bool CompareNode(Node one, Node two)
{
    if(one.iPos == two.iPos && one.jPos == two.jPos)
    {
        return true;
    }
    
    return false;
}

void AddToList(Node** nodeList, Node addedNode, int *size)
{
//    if((*size) >= 0)
//    {
//        if((*size) == 0)
//        {
//            (*nodeList) = (Node*) malloc(sizeof(Node));
//        } else if ((*size) > 0)
//        {
//            (*nodeList) = (Node*) realloc((*nodeList), sizeof(Node) * ((*size)+1));
//        }
//        (*size)++;
//        (*nodeList)[(*size)-1] = addedNode;
//    } else
//    {
//        printf("ERROR: Size is negative");
//    }
}

void RemoveFromList(Node** nodeList, Node removeNode, int *size)
{
    
}

void PrintList(int size, Node* nodeList)
{
    int i;
    for(i = 0; i<size; i++)
    {
        printf("Pos: %d %d\n", nodeList[i].iPos, nodeList[i].jPos);
    }
}

int CalcCost(Node curr, Node target)
{
    return abs(curr.iPos - target.iPos) + abs(curr.jPos - target.jPos);
}

void GetStartingAndEndingNode(Node* start, Node* end, int size)
{
    (*start).iPos = 2;
    (*start).jPos = size-2;
    (*end).iPos = size-1;
    (*end).jPos = 0;
}

void Malloc2dArray(Node*** node, int size)
{
    (*node) = (Node**)malloc(sizeof(Node*) * size);
    int j;
    int i;
    for(j = 0; j<size; j++)
    {
        (*node)[j] = (Node*) malloc(sizeof(Node) * size);
        for(i = 0; i<size; i++)
        {
            (*node)[j][i].iPos = i;
            (*node)[j][i].jPos = j;
            (*node)[j][i].open = false;
            (*node)[j][i].closed = false;
        }
    }
}

void GenerateMap(Node** node, int size)
{    
    int j;
    int i;
    for(j = 0; j<size; j++)
    {
        for(i = 0; i<size; i++)
        {
            if(i> size*((float)1/4) && i<size* ((float)3/4)-1 && j> size*((float)1/4) && j<size* ((float)3/4)-1)
            {
                node[j][i].wall = true;
            }
        }
    }
}

void PrintMaze(Node** node, int size, Node start, Node end)
{
    int i;
    int j;
    printf(" ");
    for(i = 0; i<size; i++)
    {
        printf("-");
    }
    printf("\n");
    for(j = 0; j<size; j++)
    {
        printf("|");
        for(i = 0; i<size; i++)
        {
            if(start.iPos == i && start.jPos == j)
            {
                printf("S");
            } else if(end.iPos == i && end.jPos == j)
            {
                printf("E");
            } else
            {
                if(node[j][i].wall)
                {
                    printf("X");
                } else
                {
                    printf(" ");
                }
            }
        }
        printf("|\n");
    }
    
    printf(" ");
    for(i = 0; i<size; i++)
    {
        printf("-");
    }
    printf("\n");
}

