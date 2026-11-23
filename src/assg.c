/*
Eli Cuala Assignment 2 Lec A2 Lab D06
ccid: cuala
Student ID: 1898248
Instructor: Henry Tang
*/

#include "assg.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100
Node nodePool[MAX_SIZE];
Node * openList [MAX_SIZE];
Node * closedList [MAX_SIZE];
int nodeCount = 0;

int main(int argc, char * argv[]) {

    int x, y, g, h;
    MinHeap heap;
    ClosedList closedlist;
    char input[256];

    heap_init(&heap);
    closed_list_init(&closedlist);

    while (fgets(input, 256, stdin) != NULL) {
        if (strncmp(input, "[O] In", 6) == 0) {
            while (fgets(input, 256, stdin) != NULL) {
                if (strncmp(input, "done", 4) == 0) {
                    break;
                }
                if (sscanf(input, "%d, %d, %d, %d", &x, &y, &g, &h) == 4) {
                    Node * node = create_node(x, y, g, h, NULL);
                    heap_insert(&heap, node);
                } else {
                    fprintf(stderr, "Node could not be created\n");
                    exit(EXIT_FAILURE);
                }
            }
        } else if (strncmp(input, "[O] Is", 6) == 0) {
            bool empty = heap_is_empty(&heap);
            if (empty) {
                fprintf(stdout, "True\n");
            } else {
                fprintf(stdout, "False\n");
            }
        } else if (strncmp(input, "[O] Ex", 6) == 0) {
            Node * removed = heap_extract_min(&heap);
            if (removed != NULL) {
                closed_list_add(&closedlist, removed);
                fprintf(stdout, "Extracted Node (%d, %d), f = %d, g = %d, h = %d\n", (*removed).x, (*removed).y, (*removed).f, (*removed).g, (*removed).h);
            }
        } else if (strncmp(input, "[O] De", 6) == 0) {
            int xcoord, ycoord, new_g, index;
            sscanf(input, "[O] DecreaseKey (%d, %d), new_g = %d", &xcoord, &ycoord, &new_g);
            index = heap_find(&heap, xcoord, ycoord);
            if (index != -1) {
                Node * target = (heap).data[index];
                heap_decrease_key(&heap, index, new_g, (*heap.data[index]).h);
                fprintf(stdout, "Decreased key for Node (%d, %d): f = %d, g = %d, h = %d\n", xcoord, ycoord, (*target).f, new_g, (*target).h);
            }
        } else if (strncmp(input, "[O] Fi", 6) == 0) {
            int xcoord, ycoord;
            sscanf(input, "[O] Find (%d, %d)", &xcoord, &ycoord);
            if (heap_find(&heap, xcoord, ycoord) == -1) {
                fprintf(stdout, "Node (%d, %d) has not been found\n", xcoord, ycoord);
            } else {
                fprintf(stdout, "Node (%d, %d) has been found\n", xcoord, ycoord);
            }
        } else if (strncmp(input, "[C] Fi", 6) == 0) {
            int xcoord, ycoord;
            sscanf(input, "[C] Find (%d, %d)", &xcoord, &ycoord);
            if (closed_list_contains(&closedlist, xcoord, ycoord)) {
                fprintf(stdout, "Node (%d, %d) has been found\n", xcoord, ycoord);
            } else {
                fprintf(stdout, "Node (%d, %d) has not been found\n", xcoord, ycoord);
            }
        } else if (strncmp(input, "[C] Is", 6) == 0) {
            if (closedlist.size == 0) {
                fprintf(stdout, "True\n");
            } else {
                fprintf(stdout, "False\n");
            }
        }
    }

    return 0;

}

Node * create_node(int x, int y, int g, int h, Node *parent) {

    Node * newNode = &nodePool[nodeCount++];
    
    (*newNode).x = x;
    (*newNode).y = y;
    (*newNode).g = g;
    (*newNode).h = h;
    (*newNode).parent = parent;
    (*newNode).f = g + h;

    return newNode;

}

void heap_init(MinHeap * heap) {

    (*heap).capacity = MAX_SIZE;
    (*heap).size = 0;
    (*heap).data = openList;

}

bool heap_is_empty(const MinHeap *heap) {

    return (*heap).size == 0;

}

bool node_compare (Node * node1, Node * node2) {  //checks if node1 is higher in heap than node2 using tie breaker rules

    if ((*node1).f < (*node2).f) {
        return true;
    } else if ((*node1).f > (*node2).f) {
        return false;
    } else {
        if ((*node1).h < (*node2).h) {
            return true;
        } else if ((*node1).h > (*node2).h) {
            return false;
        } else {
            if ((*node1).x < (*node2).x) {
                return true;
            } else if ((*node1).x > (*node2).x) {
                return false;
            } else {
                if ((*node1).y < (*node2).y) {
                    return true;
                } else if ((*node1).y > (*node2).y) {
                    return false;
                }
            }
        }
    }

    return false;

}

void heap_insert(MinHeap * heap, Node * node) {

    if ((*heap).size < (*heap).capacity) {
        (*heap).data[(*heap).size++] = node;
        heapify_up(heap, (*heap).size - 1);
    }

}

void heapify_up (MinHeap * heap, int index) {

    while (index > 0) {
        int parent_index = (index - 1) / 2;
        Node * node = (*heap).data[index];
        Node * parent = (*heap).data[parent_index];
        if (node_compare(node, parent)) {
            Node * temp = (*heap).data[index];
            (*heap).data[index] = (*heap).data[parent_index];
            (*heap).data[parent_index] = temp;
            index = parent_index;
        } else {
            break;
        }
    }

}

void heapify_down (MinHeap * heap, int index) {

    while (index < (*heap).size) {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int best = index;
        if (leftChildIndex < (*heap).size && node_compare((*heap).data[leftChildIndex], (*heap).data[best])) {  //checks for existense then sees if child is prioritized in minHeap
            best = leftChildIndex;
        }
        if (rightChildIndex < (*heap).size && node_compare((*heap).data[rightChildIndex], (*heap).data[best])) {
            best = rightChildIndex;
        } 
        if (best == index) {
            break;  //indexes didnt swap so min heap properties held after comparison
        } else {  //min heap properties didnt hold, so we must switch node with best
            Node * temp = (*heap).data[index];
            (*heap).data[index] = (*heap).data[best];
            (*heap).data[best] = temp;
            index = best;
        }
    }

}

Node * heap_extract_min(MinHeap * heap) {

    if ((*heap).size == 0) {
        return NULL;
    } else {
        Node * min = (*heap).data[0];
        (*heap).data[0] = (*heap).data[(*heap).size-- - 1];
        if ((*heap).size == 0) {
            return min;
        } else {
            heapify_down(heap, 0);
            return min;
        }
    }

}

void closed_list_init(ClosedList *list) {

    (*list).data = closedList;
    (*list).size = 0;
    (*list).capacity = MAX_SIZE;

}

void closed_list_add(ClosedList * list, Node * node) {

    if (!((*list).size == (*list).capacity)) {
        (*list).data[(*list).size++] = node;
    }

}

bool closed_list_contains(const ClosedList * list, int x, int y) {

    for (int i = 0; i < (*list).size; i++) {
        if ((*(*list).data[i]).x == x && (*(*list).data[i]).y == y) {
            return true;
        }
    }

    return false;

}

int heap_find(const MinHeap * heap, int x, int y) {

    for (int i = 0; i < (*heap).size; i++) {
        if ((*(*heap).data[i]).x == x && (*(*heap).data[i]).y == y) {
            return i;
        }
    }

    return -1;

}

void heap_free(MinHeap *heap) {



}

void closed_list_free(ClosedList *list) {

    

}

void heap_decrease_key(MinHeap *heap, int index, int new_g, int new_h) {

    (*(*heap).data[index]).g = new_g;
    (*(*heap).data[index]).h = new_h;
    (*(*heap).data[index]).f = new_g + new_h;
    heapify_up(heap, index);

}