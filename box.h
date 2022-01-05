//
// Created by tsahiedri on 05/01/2022.
//

#ifndef MIVNEHW2_BOX_H
#define MIVNEHW2_BOX_H
#include "avltree.h"
#include "UnionFind.h"

class Box{
public:
    AVL<int> ** score_array;
    AVL<int> players_in_group;
    int num_of_players_with_lvl_0;
    int size;// total players, need to leave it "size" due to Unionfind implementation
    Node<Box> *head;

    Box(int scale) : score_array(new AVL<int> *[scale]) , players_in_group(),
    num_of_players_with_lvl_0(0), size(0) , head(nullptr){}
    ~Box()
    {
        delete[] score_array;
    }
    void merge_boxes() //important function, need to do with carefully!
    {

    }
    void insert_player_to_box()
    {
        size++;
        num_of_players_with_lvl_0++;
    }
    void remove_player_from_box(int score, int level)
    {
        score_array[score]->remove(level);
        players_in_group.remove(level);
        if(level == 0)
        {
            num_of_players_with_lvl_0--;
            size--;
        }
        else
        {
            size--;
        }
    }

};
#endif //MIVNEHW2_BOX_H
