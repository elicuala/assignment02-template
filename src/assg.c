/*
Eli Cuala Assignment 2 Lec A2 Lab D06
ccid: cuala
Student ID: 1898248
Instructor: Henry Tang
*/

#include "assg.h"
#include <stdbool.h>
#define MAX_SIZE 100
Node nodePool[MAX_SIZE];
Node * openList [MAX_SIZE];
Node * closedList [MAX_SIZE];
int nodeCount = 0;

int main(int argc, char * argv[]) {

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

void heapify_up(MinHeap * heap, int index) {

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