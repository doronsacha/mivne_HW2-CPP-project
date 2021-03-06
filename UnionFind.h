#ifndef WET2_UNIONFIND_H
#define WET2_UNIONFIND_H

template<class T>
class NodeU{
public:
    int key;
    NodeU * father; // head the team will have nullptr here
    T * box;// nullptr for every NodeU except the head of the team
    NodeU(int n): key(n), father(nullptr),box(nullptr){}
};

template<class T>
class UnionFind
        {
private:
    int universe_size;
    NodeU<T>** elements;
    T ** groups;
public:
    UnionFind(int n, int scale) : universe_size(n+1)
    {
        elements = new NodeU<T>*[n+1];//array of pointers to NodeUs
        groups = new T*[n+1]; // array of T's pointers
        for(int i=1; i<n+1; i++)
        {
            make_set(i, scale);
        }
    }
    ~UnionFind()
    {
        clear_elements();
        delete[] elements;
        delete[] groups;
    }


    void clear_elements()
    {
        for(int i=1; i<universe_size; i++)
        {
            if(elements[i]->father == nullptr && elements[i]->box != nullptr)
            {
                delete elements[i]->box;
            }
            delete elements[i];
        }
    }
    void make_set(int id,int scale)
    {
        elements[id] = new NodeU<T>(id);
        groups[id] = new T(scale);
        groups[id]->head = elements[id];
        elements[id]->box = groups[id];
        elements[id]->box->size=1;
    }

    int find(int id)
    {
        NodeU<T> * team_leader = find_team_leader(id);
        shrink_group(team_leader,id);
        return team_leader->box->getID();
    }


    T * get_box(int id)
    {
        NodeU<T> * leader = find_team_leader(id);
        return leader->box;
    }

    void union_groups(int first_group, int second_group, int scale){
        T * box1 = get_box(first_group);
        T * box2 = get_box(second_group);
        if(box1 == box2 || first_group == second_group)
        {
            return;
        }
        if (box1->size > box2->size)
        {
            box2->head->father = box1->head;
            box1->merge_boxes(box2,scale);
            groups[second_group] = box1;
        }
        else if(box1-> size < box2->size)
        {
            box1->head->father = box2->head;
            box2->merge_boxes(box1,scale);
            groups[first_group] = box2;
        }
        else
        {
            if(box1->head->key > box2->head->key)
            {
                box2->head->father = box1->head;
                box1->merge_boxes(box2,scale);
                groups[second_group] = box1;
            }
            else
            {
                box1->head->father = box2->head;
                box2->merge_boxes(box1,scale);
                groups[first_group] = box2;
            }
        }
    }


    void shrink_group(NodeU<T> *team_leader, int current_id)
    {
        NodeU<T>* iterator = elements[current_id];
        NodeU<T> * temp = iterator;
        while(iterator->father != nullptr)
        {
            iterator = iterator->father;
            temp->father = team_leader;
            temp = iterator;
        }
    }

    NodeU<T> * find_team_leader(int id)
    {
        NodeU<T>* iterator = elements[id];
        while(iterator->father != nullptr)
        {
            iterator = iterator->father;
        }
        return iterator;
    }

    int getUniverseSize() const
    {
        return universe_size;
    }
};


#endif //WET2_UNIONFIND_H