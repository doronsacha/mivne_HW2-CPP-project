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
    NodeU<Box> *head;
    int scale;

    explicit Box(int scale) : score_array(new AVL<int> *[scale]) , players_in_group(),
    num_of_players_with_lvl_0(0), size(0) , head(nullptr),scale(scale)
    {
        for(int i=0; i<scale;i++)
        {
            score_array[i] = new AVL<int>;
        }
    }
    ~Box()
    {
        for(int i=0; i<scale; i++)
        {
            if(score_array[i] != nullptr)
                delete score_array[i];
        }
        delete[] score_array;
    }
    void merge_boxes(Box * other, int scale) //Not Done
    {
        if(other->size == 0)
        {
            delete other;
            return;
        }
        merge_trees_inside_box_ref(other->players_in_group);
        for(int i=0; i<scale; i++)
        {
            merge_trees_inside_box_pointer(i,other->score_array[i]);
            delete other->score_array[i];
        }
        size+=other->size;
        num_of_players_with_lvl_0+=other->num_of_players_with_lvl_0;
        delete other;
    }

    static void merge(const int * a,const int *b, int *c, int sizeA,int sizeB)
    {
        int ia,ib,ic;
        ia=ib=ic=0;
        while(ia<sizeA && ib <sizeB)
        {
            if(a[ia] < b[ib])
            {
                c[ic] = a[ia];
                ia++; ic++;
            }
            else
            {
                c[ic] = b[ib];
                ib++; ic++;
            }
        }
        while (ia<sizeA)
        {
            c[ic]= a[ia];
            ia++; ic++;
        }
        while (ib<sizeB)
        {
            c[ic]= b[ib];
            ib++; ic++;
        }
    }

    void merge_trees_inside_box_ref(AVL<int> &other)
    {
        int x=0;
        int other_tree_size = other.getSize();
        int * other_tree_lvls = new int[other_tree_size];
        other.transform_to_array(other_tree_lvls,&x);

        x=0;
        int our_tree_size = players_in_group.getSize();
        int * our_tree_lvls = new int[our_tree_size];
        players_in_group.transform_to_array(our_tree_lvls,&x);
        int * total_lvls = new int[other_tree_size+our_tree_size];
        merge(other_tree_lvls,our_tree_lvls,total_lvls,other_tree_size,our_tree_size);
        delete[] other_tree_lvls;
        delete[] our_tree_lvls;
        other.treeClear();
        players_in_group.treeClear();
        create_empty_tree(players_in_group,our_tree_size+other_tree_size);
        x=0;
        players_in_group.fillTree(total_lvls,&x);
        players_in_group.update_tree_extra_data_post_order();
    }

    static void create_empty_tree(AVL<int> & tree, int desired_size)
    {
        for(int i=0; i<desired_size; i++)
        {
            tree.insert(0);
        }
    }

    void merge_trees_inside_box_pointer(int idx,AVL<int> *other)
    {
        int x=0;
        int other_tree_size = other->getSize();
        int * other_tree_lvls = new int[other_tree_size];
        other->transform_to_array(other_tree_lvls,&x);

        x=0;
        int our_tree_size = score_array[idx]->getSize();
        int * our_tree_lvls = new int[our_tree_size];
        score_array[idx]->transform_to_array(our_tree_lvls,&x);
        int * total_lvls = new int[other_tree_size+our_tree_size];
        merge(other_tree_lvls,our_tree_lvls,total_lvls,other_tree_size,our_tree_size);
        delete[] other_tree_lvls;
        delete[] our_tree_lvls;
        other->treeClear();
        delete other;
        score_array[idx]->treeClear();
        create_empty_tree(*score_array[idx],our_tree_size+other_tree_size);
        x=0;
        score_array[idx]->fillTree(total_lvls,&x);
        score_array[idx]->update_tree_extra_data_post_order();
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
