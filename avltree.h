#ifndef AVL_TREE_H
#define AVL_TREE_H
//Created By Tsahi and Doron
#include <memory>
#include <iostream>

using namespace std;

template <class T>
class AVL{
private:
    class Node{
    public:
        Node* right;
        Node* left;
        T key;
        int num_of_elements_in_sub_tree; // for getting rank
        int sum_of_smaller; // for Sum problem - need to sum the keys
        // which will be the levels in the tree (averageHighestPlayerByGroup)
    };
    Node *root;
    int size;
public:
    /**Basic Avl-Tree Constructor, initialize an empty root node. */
    AVL() : root(nullptr),size(0) {}

    /** Destructor. */
    ~AVL(){
        treeClear();
    }

    /** Pre-order traversal. */
    void preorder(){
        preorderAid(root);
    }

    /** Post-order traversal. */
    void postorder(){
        postorderAid(root);
    }

    /** In-order traversal. */
    void inorder()
    {
        inorderAid(root);
    }


    /** Inserting a new node with the given key. may required some rotating. */
    void insert(T key)
    {
        root = insertUtil(root,key);
        size++;
    }

    /** A function used to remove a specific node with the given key. */
    void remove(T key)
    {
        root = removeAid(root, key);
        size--;
    }

    /** A function that completely removes all the nodes in the tree, and set it's root to null.*/
    void treeClear(){
        treeClearAid(root);
        root = nullptr;
        size=0;
    }

    int lowRank(T key)
    {
        return lowRankAid(key, root);
    }

    int lowRankAid(T key, Node* v)
    {
        if (v == nullptr)
        {
            return 1;
        }
        if (key<v->key)
        {
            return lowRankAid(key, v->left);
        }

        else if (key>v->key)
        {
            if(v->left!= nullptr)
            {
                return 1 + v->left->num_of_elements_in_sub_tree + lowRankAid(key, v->right);
            }
            return 1 + lowRankAid(key,v->right);
        }
        else
        {
            if(v->left == nullptr)
            {
                int sub=0;
                {
                    if(v->right != nullptr)
                    {
                        sub=v->right->num_of_elements_in_sub_tree;
                    }
                }
                return (v->num_of_elements_in_sub_tree)-sub;
            }
            else
            {
                return lowRankAid(key, v->left);
            }
        }
    }

    int highRank(T key)
    {
        return highRankAid(key, root);
    }

    int highRankAid(T key, Node* v)
    {
        if (v == nullptr)
        {
            return 0;
        }
        if (key < v->key)
        {
            return highRankAid(key, v->left);
        }

        else if (key>v->key)
        {
            if(v->left!= nullptr)
            {
                return 1 + v->left->num_of_elements_in_sub_tree + highRankAid(key, v->right);
            }
            return 1 + highRankAid(key,v->right);
        }
        else
        if(v->left == nullptr)
        {
            int sub=0;
            {
                if(v->right != nullptr)
                {
                    if(v->right->key== key)
                    {
                         return 1+ highRankAid(key,v->right);
                    }
                    sub=v->right->num_of_elements_in_sub_tree;
                }
            }
            return (v->num_of_elements_in_sub_tree)-sub;
        }
        else
        {
            return highRankAid(key, v->right)+1+v->left->num_of_elements_in_sub_tree;
        }
    }

    void update_num_of_elements_in_subtree(Node * v)
    {
        int updating = 1;
        if(v->left != nullptr)
            updating += v->left->num_of_elements_in_sub_tree;
        if(v->right != nullptr)
            updating += v->right->num_of_elements_in_sub_tree;
        v->num_of_elements_in_sub_tree = updating;
    }

    void update_sum_of_smaller(Node *v)
    {
        int sum = v->key;
        if(v->left != nullptr)
            sum += v->left->sum_of_smaller;
        if(v->right != nullptr)
            sum += v->right->sum_of_smaller;
        v->sum_of_smaller = sum;
    }

    Node* findNode(T key)
    {
        return findNodeAid(root,key);
    }
    Node * find_max_root()
    {
        return findMax(root);
    }
    Node * getRoot() const
    {
        return root;
    }
    int getSize() const
    {
        return size;
    }



//**********************************************************************************************************************
//----------------------------------------------Balancing---------------------------------------------------------------
//**********************************************************************************************************************

    /** balance the tree using the AVL rules for balance factor that doesn't belong to [-1,1].*/
    Node* balance(Node *t) {
        int bal_factor = getBalanceFactor(t);
        if (bal_factor > 1) {
            if (getBalanceFactor(t->left) > 0)
                t = ll_rotate(t);
            else
                t = lr_rotate(t);
        } else if (bal_factor < -1) {
            if (getBalanceFactor(t->right) > 0)
                t = rl_rotate(t);
            else
                t = rr_rotate(t);
        }
        return t;
    }

    /** A function used in order to get the node's height. */
    int height(Node* v) const
    {
        int h =0;
        if (v != nullptr)
        {
            int l_height = height(v->left);
            int r_height = height(v->right);
            int max_height = (l_height > r_height) ? l_height : r_height;
            h = max_height + 1;
        }
        return h;
    }

    /** calculating node's balance factor.*/
    int getBalanceFactor(Node *t)
    {
        int l_height = height(t->left);
        int r_height = height(t->right);
        int b_factor = l_height - r_height;
        return b_factor;
    }


//**********************************************************************************************************************
//----------------------------------------------Rotating----------------------------------------------------------------
//**********************************************************************************************************************

    Node * rr_rotate(Node *parent){
        Node *t;
        t = parent->right;
        parent->right = t->left;
        t->left = parent;
        update_num_of_elements_in_subtree(parent);
        update_num_of_elements_in_subtree(t);
        update_sum_of_smaller(parent);
        update_sum_of_smaller(t);
        return t;
    }


    Node * ll_rotate(Node *parent){
        Node *t;
        t = parent->left;
        parent->left = t->right;
        t->right = parent;
        update_num_of_elements_in_subtree(parent);
        update_num_of_elements_in_subtree(t);
        update_sum_of_smaller(parent);
        update_sum_of_smaller(t);
        return t;
    }

    Node * lr_rotate(Node *parent){
        Node *t;
        t = parent->left;
        parent->left = rr_rotate(t);
        return ll_rotate(parent);
    }

    Node * rl_rotate(Node *parent){
        Node *t;
        t = parent->right;
        parent->right = ll_rotate(t);
        return rr_rotate(parent);
    }

//**********************************************************************************************************************
//----------------------------------------------Searching---------------------------------------------------------------
//**********************************************************************************************************************



    /** A function used in order to find the minimum of the tree. */
    Node* findMin(Node * v) const
    {
        if(v == nullptr)
            return nullptr;
        else if(v->left == nullptr)
            return v;
        else
            return findMin(v->left);
    }

    /** A function used in order to find the maximum of the tree. */
    Node* findMax(Node * v) const
    {
        if(v == nullptr)
            return nullptr;
        else if(v->right == nullptr)
            return v;
        else
            return findMax(v->right);
    }

    /** A function used in order to search a specific node on the tree,given its key. */
    Node* findNodeAid(Node *v,T &key) const
    {
        if (v == nullptr)
        {
            return nullptr;
        }
        if(v->key == key)
        {
            return v;
        }
        else if (v->key < key)
        {
            return findNodeAid(v->right, key);
        }
        else{
            return findNodeAid(v->left,key);
        }
    }

    int getSum(int rank)
    {
        return getSumAid(rank,root,0);
    }

    int getSumAid(int rank, Node* v,int curr_rank)
    {
        if(v== nullptr)
        {
            return 0;
        }
        if(v->left!= nullptr)
        {
            curr_rank+=v->left->num_of_elements_in_sub_tree + 1;
        }
        if(v->left== nullptr)
        {
            curr_rank +=1;
        }
        if(curr_rank<rank)
        {
            if(v->left!= nullptr)
            {
                return v->left->sum_of_smaller +v->key + getSumAid(rank,v->right,curr_rank);
            }
            else
            {
                return v->key + getSumAid(rank,v->right,curr_rank);
            }
        }
        else if(curr_rank>rank)
        {
            if(v->left!= nullptr)
            {
                return getSumAid(rank, v->left, curr_rank - v->left->num_of_elements_in_sub_tree-1);
            }
            return getSumAid(rank,v->left,curr_rank-1);
        }
        else
        {
            if(v->left!= nullptr)
            {
                return v->left->sum_of_smaller +v->key;
            }
            else
            {
                return v->key;
            }
        }
    }
//**********************************************************************************************************************
//----------------------------------------------Aid functions---------------------------------------------------------------
//**********************************************************************************************************************

    void preorderAid(Node* r){
        if (r == nullptr)
            return;
        //cout << r->key << "  ";
        preorderAid(r->left);
        preorderAid(r->right);
    }

    void postorderAid(Node* r){
        if (r == nullptr)
            return;
        postorderAid(r->left);
        postorderAid(r->right);
        //cout << r->key << "  ";
    }

    void inorderAid(Node* r){
        if (r == nullptr)
            return;
        inorderAid(r->left);
        //cout << r->key << "  ";
        inorderAid(r->right);
    }

    Node* insertUtil(Node * r, T key)
    {
        if (r == nullptr) {
            r = new Node;
            r->key = key;
            r->num_of_elements_in_sub_tree = 1;
            r->sum_of_smaller = key;
            r->left = nullptr;
            r->right = nullptr;
            return r;
        }
        else if (key < r->key)
        {
            r->left = insertUtil(r->left, key);
            r = balance(r);
        }
        else if (r->key <= key) {
            r->right = insertUtil(r->right, key);
            r = balance(r);
        }
        update_num_of_elements_in_subtree(r);
        update_sum_of_smaller(r);
        return r;
    }

    Node* removeAid(Node* t, T key) {
        Node* temp;
        // element not found
        if (t == nullptr) return nullptr;
            // searching element
        else if (key < t->key) t->left = removeAid(t->left, key);
        else if (t->key < key) t->right = removeAid(t->right, key);
            // element found
            // element has 2 children
        else if (t->left && t->right) {
            temp = findMin(t->right);
            t->key = temp->key;
            t->right = removeAid(t->right, t->key);
        }
            // if element has 1 or 0 child
        else {
            temp = t;
            if (t->left == nullptr) t = t->right;
            else if (t->right == nullptr) t = t->left;
            delete temp;
        }
        if (t == nullptr) return t;
        update_num_of_elements_in_subtree(t);
        update_sum_of_smaller(t);
        // check balanced
        t = balance(t);
        return t;
    }

    void treeClearAid(Node* v){
        if(v != nullptr){
            treeClearAid(v->left);
            treeClearAid(v->right);
            delete v;
        }
    }


    void update_tree_extra_data_post_order()
    {
        update_tree_extra_data_post_order_aid(root);
    }

    void update_tree_extra_data_post_order_aid(Node *r)
    {
        if (r == nullptr)
            return;
        postorderAid(r->left);
        postorderAid(r->right);
        update_sum_of_smaller(r);
        update_num_of_elements_in_subtree(r);
    }

    void fill_tree_helper(Node* firstNode,T * arr,int* i)
    {
        if(firstNode== nullptr)
        {
            return;
        }
        fill_tree_helper(firstNode->left,arr,i);
        firstNode->key = arr[*i];
        (*i)++;
        fill_tree_helper(firstNode->right,arr,i);
    }

    void fillTree(T * arr,int* i)
    {
        fill_tree_helper(root,arr,i);
    }


    // for keys.
    void transform_to_array(T *lvl_arr ,int* i)
    {
        transform_to_array_helper(root,lvl_arr,i);
    }

    void transform_to_array_helper(Node* firstNode,T *lvl_arr, int* i)
    {
        if(firstNode== nullptr)
        {
            return;
        }
        transform_to_array_helper(firstNode->left,lvl_arr,i);
        lvl_arr[*i]=firstNode->key;
        (*i)++;
        transform_to_array_helper(firstNode->right,lvl_arr,i);
    }

    void set_size(int num)
    {
        size=num;
    }

    void insertZeros(T key)
    {
        root = insertUtil(root,key);
        size++;
    }
    Node* insertUtilForZero(Node * r, T key)
    {
        if (r == nullptr) {
            r = new Node;
            r->key = key;
            r->sum_of_smaller=key;
            r->num_of_elements_in_sub_tree=1;
            r->left = nullptr;
            r->right = nullptr;
            return r;
        }
        else if (key < r->key)
        {
            r->left = insertUtil(r->left, key);
            r = balance(r);
        } else if (r->key <= key) {
            r->right = insertUtil(r->right, key);
            r = balance(r);
        } return r;
    }
};

#endif //AVL_TREE_H



