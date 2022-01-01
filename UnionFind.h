//
// Created by tsahiedri on 01/01/2022.
//
#ifndef MIVNEHW2_UNIONFIND_H
#define MIVNEHW2_UNIONFIND_H
#include "hashTable.h"

template<class S>
class reversedTree;


template<class S>
class Group_info;

template<class S>
class Node{
public:
    Node* father;
    int key;
    Group_info<S> * groupInfo;
    int getID()
    {
        return key;
    }
};



template<class S>
struct Group_info{
    int key;
    S data;
    reversedTree<S> * group_elements;
};


template<class S>
class reversedTree{
public:
    reversedTree() : root(nullptr),size(0) {}
    int getSize() const
    {
        return size;
    }
private:
    Node<S> *root;
    Group_info<S> *group_node;
    int size;
};



template<class S>
class UnionFind{
private:
    HashTable<Node<S>*> elements_table;
    Group_info<S> *group_arr;
    int number_of_groups;
public:
    UnionFind(int n) : number_of_groups(n){
        Node<S> * tombstone = new Node<S>;
        tombstone->key = -2;
        elements_table(&tombstone);
        group_arr = new Group_info<S>*[n]();
        for(int i=0; i<n; i++)
        {
            (*group_arr)[i].key = i;
        }
    }


    int find(int player_id)
    {
        int index = elements_table.find(player_id);
        if(index == -1)
            return -1;
        Node<S> * iterator = elements_table[index];
        while(iterator->father != nullptr)
        {
            iterator = iterator->father;
        }
        return iterator->groupInfo->key;
    }

    int Union(int group_id1, int group_id2)
    {
        int size_group1 = *(group_arr[group_id1])->group_elements.getSize();
        int size_group2 = *(group_arr[group_id2])->group_elements.getSize();
        if (size_group1 >= size_group2)
        {

        }
        else{

        }
    }



};



#endif //MIVNEHW2_UNIONFIND_H
