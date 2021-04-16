#ifndef __NODE_MAP__
#define __NODE_MAP__

#include <stdint.h>

typedef struct Node
{
    uint16_t x,y;
    Node* up;
    Node* down;
    Node* left;
    Node* right;

} Node;


void node_link(Node** map, uint8_t id1, uint8_t id2);

Node* map1_nodes[69];

Node* node_new(uint16_t x, uint16_t y)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->x = x;
    n->y = y;
    n->up = NULL;
    n->down = NULL;
    n->left = NULL;
    n->right = NULL;

    return n;
}

void map1_init()
{
    map1_nodes[ 0] = node_new(  4,  4);
    map1_nodes[ 1] = node_new( 44,  4);
    map1_nodes[ 2] = node_new( 68,  4);
    map1_nodes[ 3] = node_new(140,  4);
    map1_nodes[ 4] = node_new(164,  4);
    map1_nodes[ 5] = node_new(204,  4);
    map1_nodes[ 6] = node_new(  4, 28);
    map1_nodes[ 7] = node_new( 20, 28);
    map1_nodes[ 8] = node_new( 44, 28);
    map1_nodes[ 9] = node_new( 68, 28);
    map1_nodes[10] = node_new( 92, 28); 
    map1_nodes[11] = node_new(116, 28);
    map1_nodes[12] = node_new(140, 28);
    map1_nodes[13] = node_new(164, 28);
    map1_nodes[14] = node_new(188, 28);
    map1_nodes[15] = node_new(204, 28);
    // incomplete for now

    node_link(map1_nodes, 0, 1);
    node_link(map1_nodes, 0, 6);
    node_link(map1_nodes, 6, 7);
    node_link(map1_nodes, 7, 8);
    node_link(map1_nodes, 1, 8);
    node_link(map1_nodes, 8, 9);
    // incomplete for now


    // DEBUG
    //Serial.print("N0: ");
    //Serial.print((uint32_t)map1_nodes[0], HEX);
    //Serial.print(" N1: ");
    //Serial.print((uint32_t)map1_nodes[ 1], HEX);
    //Serial.println("");
    //Serial.print(" N0.right: ");
    //Serial.print((uint32_t)(map1_nodes[ 0]->right), HEX);


}

void node_link(Node** map, uint8_t id1, uint8_t id2)
{
    Node* n1 = map[id1];
    Node* n2 = map[id2];

    if (n1->x == n2->x)
    {
        if (n1->y < n2->y)
        {
            n1->down = n2;
            n2->up = n1;
        }
        else
        {
            n2->down = n1;
            n1->up = n2;
        }
    }

    if (n1->y == n2->y)
    {
        if (n1->x < n2->x)
        {
            n1->right = n2;
            n2->left = n1;
        }
        else
        {
            n2->left = n1;
            n1->right = n2;
        }
    }
}

#endif // __NODE_MAP__