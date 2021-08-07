/*鉴于老师已经有了代码实现 我在这里给大家简要介绍下b树的操作
 一，B-树就是B树
英文名字叫做B-tree，中间的短线是英文连接符，只是翻译的时候将短线翻译成了减号。
全称Balance-tree(平衡多路查找树)，平衡的意思是左边和右边分布均匀。多路的意思是相对于二叉树而言的，二叉树就是二路查找树，查找时只有两条路，而B-tree有多条路，即父节点有多个子节点。

二，B-树用途
使用B-tree结构可以显著减少定位记录时所经历的中间过程，从而加快存取速度。这个数据结构一般用于数据库的索引，综合效率较高。

三，阶的概念
对于一棵m阶B-tree，每个结点至多可以拥有m个子结点。

即遍观整棵树，子节点最多的个数是m，那么这棵树就是m阶树。

四，树的度
树的度就是树的高度，即树的层数。(这里网上的说法可能有不同版本的分歧,不过对使用影响不大)

五，B-树的定义
（1）树中每个结点至多有m 棵子树（注：m指的是树的阶）；

（2）若根结点不是叶子结点，则至少有两棵子树（注：根节点至少有两个儿子）；

（3）除根结点之外的所有非叶子结点至少有p个子节点;

（4）所有的非叶子结点中包含以下数据：（n，A0，K1，A1，K2，…，Kn，An）

     其中：

     Ki（i=1,2,…,n）为关键码，且Ki<Ki+1（注：ki是真实数据，存放在线性表当中，且从左至右升序排列）

     Ai 为指向儿子的指针(i=0,1,…,n)，且指针Ai-1 所指子树中所有结点的关键码均小于Ki (i=1,2,…,n)，An 所指子树中所有结点的关键码均大于Kn。

      n 为关键码的个数。

（5）所有的叶子结点都出现在同一层次上，即所有叶节点具有相同的深度，等于树高度。并且不带信息（可以看作是外部结点或查找失败的结点，实际上这些结点不存在，指向这些结点的指针为空）。 


六，B-树的查找
B-树的查找类似二叉排序树的查找，不同的是B-树每个结点上是多关键码的有序表，在到达某个结点时，先在有序表中查找，若找到，则查找成功；否则，到按照对应的指针信息指向的子树中去查找，当到达叶子结点时，则说明树中没有对应的关键码。

*/
// C++ implemntation of search() and traverse() methods
#include <iostream>
using namespace std;
// A BTree node
class BTreeNode
{
    int *keys;  // An array of keys
    int t;      // Minimum degree (defines the range for number of keys)
    BTreeNode **C; // An array of child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
public:
    BTreeNode(int _t, bool _leaf);   // Constructor

// A function to traverse all nodes in a subtree rooted with this node
    void traverse();

// A function to search a key in subtree rooted with this node.
    BTreeNode *search(int k);   // returns NULL if k is not present.

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
    void insertNonFull(int k);

// A utility function to split the child y of this node
// Note that y must be full when this function is called
    void splitChild(int i, BTreeNode *y);

// Make BTree friend of this so that we can access private members of this
// class in BTree functions
    friend class BTree;
};

// A BTree
class BTree
{
    BTreeNode *root; // Pointer to root node
    int t;  // Minimum degree
public:
// Constructor (Initializes tree as empty)
    BTree(int _t)
    {
        root = NULL;  t = _t;
    }

// function to traverse the tree
    void traverse()
    {
        if (root != NULL)
            root->traverse();
    }

// function to search a key in this tree
    BTreeNode* search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }

    void insert(int);
};

// Constructor for BTreeNode class
BTreeNode::BTreeNode(int _t, bool _leaf)
{
    // Copy the given minimum degree and leaf property
    t = _t;
    leaf = _leaf;

    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new int[2 * t - 1];
    C = new BTreeNode *[2 * t];

    // Initialize the number of keys as 0
    n = 0;
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse()
{
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }

    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->traverse();
}

// Function to search key k in subtree rooted with this node
BTreeNode *BTreeNode::search(int k)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    // If the found key is equal to k, return this node
    if (keys[i] == k)
        return this;

    // If key is not found here and this is a leaf node
    if (leaf == true)
        return NULL;

    // Go to the appropriate child
    return C[i]->search(k);

}



void BTree::insert(int k)
{
    // If tree is empty
    if (root == NULL)
    {
        // Allocate memory for root
        root = new BTreeNode(t, true);
        root->keys[0] = k;  // Insert key
        root->n = 1;  // Update number of keys in root
    }
    else // If tree is not empty
    {
        // If root is full, then tree grows in height
        if (root->n == 2 * t - 1)
        {
            // Allocate memory for new root
            BTreeNode *s = new BTreeNode(t, false);

            // Make old root as child of new root
            s->C[0] = root;

            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);

            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            // Change root
            root = s;
        }
        else  // If root is not full, call insertNonFull for root
            root->insertNonFull(k);
    }
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull(int k)
{
    // Initialize index as index of rightmost element
    int i = n - 1;

    // If this is a leaf node
    if (leaf == true)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        // Insert the new key at found location
        keys[i + 1] = k;
        n = n + 1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > k)
            i--;

        // See if the found child is full
        if (C[i + 1]->n == 2 * t - 1)
        {
            // If the child is full, then split it
            splitChild(i + 1, C[i + 1]);

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode *y)
{
    // Create a new node which is going to store (t-1) keys
    // of y
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    // Copy the last t children of y to z
    if (y->leaf == false)
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];

    // Reduce the number of keys in y
    y->n = t - 1;

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    // Link the new child to this node
    C[i + 1] = z;

    // A key of y will move to this node. Find location of
    // new key and move all greater keys one space ahead
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    // Copy the middle key of y to this node
    keys[i] = y->keys[t - 1];

    // Increment count of keys in this node
    n = n + 1;
}

// Driver program to test above functions
int main()
{
    BTree t(3); // A B-Tree with minimum degree 3
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);

    cout << "Traversal of the constucted tree is ";
    t.traverse();

    int k = 6;
    (t.search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";

    k = 15;
    (t.search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";

    return 0;
}
