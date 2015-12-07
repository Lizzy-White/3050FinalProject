#include "heap.h"

//GCost = Distance from starting point
//HCost = Distance from ending point
//FCost = Sum of GCost and HCost
Node** GetNeighbours(Node* curr, Node** nodeArray, int nodeArraySize, int* neighbourSize);
void MallocNode(Node*** node, int size);
void PrintList(int size, Node* nodeList);

int main(int argc, char** argv) {

    //print_array(openList);
    
    //Node* list = GetNeighbours(curr, nodeArray, size, &neighbourSize);
    //PrintList(neighbourSize, GetNeighbours(curr, nodeArray, size, &neighbourSize));
Node** neighbours;
    int Buffer = 3, buff;
    for(buff = 0; buff<Buffer; buff++)//Should continue until every node is closed or until found
    {
        curr = extract_min(&openList);
        AddNode(&closedList, curr, &closedSize);
        if(CompareNode(*curr, endingNode))
        {
            buff = Buffer+1;
        }
        
        
//        printf("%d %d %d \n", curr->jPos, curr->iPos, curr->closed);
//        curr->closed = true;
//        printf("%d %d %d \n\n", nodeArray[curr->jPos][curr->iPos].jPos, nodeArray[curr->jPos][curr->iPos].iPos, nodeArray[curr->jPos][curr->iPos].closed);
        if(true){
            
        int neighbourSize=0;
        neighbours = GetNeighbours(curr, nodeArray, size, &neighbourSize);
        int i;
            printf("Size: %d\n", neighbourSize);
        for(i = 0; i<neighbourSize; i++)
        {
            printf("%d %d \n", neighbours[i]->jPos, neighbours[i]->iPos);
            insert(&openList, neighbours[i]);
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

        printf("--------\n");
        }

    }
    
    return (EXIT_SUCCESS);
}

void print_array(node_t heap) {
    int i;
    printf("\n\n");
    for (i = 0; i < heap.size; i++)
    {
        if((*(heap.A[i])).FCost < 0)
        {
            printf("noFCost ");
        } else
        {
            printf("%d ", (*(heap.A[i])).FCost);
        }
    }
}
//Goes clockwise. Starting from the node above
Node** GetNeighbours(Node* curr, Node** nodeArray, int nodeArraySize, int* neighbourSize)
{
    Node** temp;
    if(curr->jPos-1 >= 0)
    {
        if(!nodeArray[curr->jPos-1][curr->iPos].wall)
        {
            nodeArray[curr->jPos-1][curr->iPos].Parent = (struct GraphNode*)malloc(sizeof(struct GraphNode));
            nodeArray[curr->jPos-1][curr->iPos].Parent = curr;
            MallocNode(&temp, *neighbourSize);
            (*neighbourSize)++;
            temp[(*neighbourSize)-1] = &nodeArray[curr->jPos-1][curr->iPos];
        }
    }
    if(curr->iPos+1 < nodeArraySize)
    {
        if(!nodeArray[curr->jPos][curr->iPos+1].wall)
        {
            nodeArray[curr->jPos][curr->iPos+1].Parent = (struct GraphNode*)malloc(sizeof(struct GraphNode));
            nodeArray[curr->jPos][curr->iPos+1].Parent = curr;
            MallocNode(&temp, *neighbourSize);
            (*neighbourSize)++;
            temp[(*neighbourSize)-1] = &nodeArray[curr->jPos][curr->iPos+1];
        }
    }
    if(curr->jPos+1 < nodeArraySize)
    {
        if(!nodeArray[curr->jPos+1][curr->iPos].wall)
        {
            nodeArray[curr->jPos+1][curr->iPos].Parent = (struct GraphNode*)malloc(sizeof(struct GraphNode));
            nodeArray[curr->jPos+1][curr->iPos].Parent = curr;
            MallocNode(&temp, *neighbourSize);
            (*neighbourSize)++;
            temp[(*neighbourSize)-1] = &nodeArray[curr->jPos+1][curr->iPos];
        }
    }
    if(curr->iPos-1 >= 0)
    {
        if(!nodeArray[curr->jPos][curr->iPos-1].wall)
        {
            nodeArray[curr->jPos][curr->iPos-1].Parent = (struct GraphNode*)malloc(sizeof(struct GraphNode));
            nodeArray[curr->jPos][curr->iPos-1].Parent = curr;
            
        printf("KK:%d\n",*neighbourSize);
            MallocNode(&temp, *neighbourSize);
        printf("kk:  %d\n",*neighbourSize);
            (*neighbourSize)++;
        printf("k: %d\n",*neighbourSize);
            temp[(*neighbourSize)-1] = &nodeArray[curr->jPos][curr->iPos-1];
        }
    }
    
    return temp;
}

void MallocNode(Node*** node, int size)
{   //printf("starting: %d  ", *size);
    if((size) >= 0)
    {
        if((size) == 0)
        {
            *node = (Node**) malloc(sizeof(Node*));
            *(node)[0] = (Node*) malloc(sizeof(Node));
        } else
        {
            *node = (Node**) realloc((*node), sizeof(Node*) * ((size)+1));
            //printf("starting: %d  ", *size);
            *(node)[(size)] = (Node*) malloc(sizeof(Node));
            //printf("starting: %d  ", *size);
        }
        //printf("si: %d\n", *size);
        //(*size)++;
    } else
    {
        printf("ERROR: Size is negative");
    }
}

void PrintList(int size, Node* nodeList)
{
    int i;
    for(i = 0; i<size; i++)
    {
        printf("Pos: %d %d\n", nodeList[i].iPos, nodeList[i].jPos);
    }
}

