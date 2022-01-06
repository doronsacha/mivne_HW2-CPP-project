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
    int size;// we would name it "total_players",but need to leave it "size" due to Unionfind implementation
    Node<Box> *head;

    Box(int scale) : score_array(new AVL<int> *[scale]) , players_in_group(),
    num_of_players_with_lvl_0(0), size(0) , head(nullptr){}
    ~Box()
    {
        delete[] score_array;
    }
    void merge_boxes(Box * smaller_box, int scale) //Not Done
    {
        // note to myself: maybe merging the trees will be a method in box and not in avl, need to think about it.
        players_in_group.merge_lvl_trees_reference(smaller_box->players_in_group); // no delete needed
        for(int i=0; i<scale; i++)
        {
            score_array[i]->merge_lvl_trees_pointer(smaller_box->score_array[i]); // also deletes smaller tree
        }
        size+=smaller_box->size;
        num_of_players_with_lvl_0+=smaller_box->num_of_players_with_lvl_0;
        delete smaller_box;
    }
    void insert_player_to_box()
    {
        size++;
        num_of_players_with_lvl_0++;
    }
    void remove_player_from_box(int score, int level)
    {
        if(level == 0)
        {
            num_of_players_with_lvl_0--;
            size--;
        }
        else
        {
            score_array[score]->remove(level);
            players_in_group.remove(level);
            size--;
        }
    }
    void update_lvl_for_player_lvl_0(int new_level,int score)
    {
        num_of_players_with_lvl_0--;
        // update in the tree that inside a score
        score_array[score]->insert(new_level);
        // update in the tree that includes all the player in the box
        players_in_group.insert(new_level);
    }

    void update_lvl_for_player_above_lvl_0(int prev_lvl, int additional_lvl, int score)
    {
        int new_lvl = prev_lvl + additional_lvl;
        // update in the tree that inside a score
        score_array[score]->remove(prev_lvl);
        score_array[score]->insert(new_lvl);
        // update in the tree that includes all the player in the box
        players_in_group.remove(prev_lvl);
        players_in_group.insert(new_lvl);
    }

    void change_score_in_box(int prev_score,int new_score,int lvl)
    {
        score_array[prev_score]->remove(lvl);
        score_array[new_score]->insert(lvl);
    }

};
#endif //MIVNEHW2_BOX_H
