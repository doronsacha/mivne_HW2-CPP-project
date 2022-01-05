//
// Created by tsahiedri on 05/01/2022.
//

#ifndef MIVNEHW2_BOX_H
#define MIVNEHW2_BOX_H
#include "avltree.h"
#include "UnionFind.h"

class Box{
private:
    AVL<int> ** score_array;
    AVL<int> players_in_group;
    int num_of_players_with_lvl_0;
    int size;// total players, need to leave it "size" due to Unionfind implementation
    Node<Box> *head;
public:
    Box(int scale) : score_array(new AVL<int> *[scale]) , players_in_group(),
    num_of_players_with_lvl_0(0), size(0) , head(nullptr){}

};
#endif //MIVNEHW2_BOX_H
