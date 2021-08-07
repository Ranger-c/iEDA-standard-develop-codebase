/*
一、二叉树的遍历概念

    1.  二叉树的遍历是指从根结点触发，按照某种次序依次访问二叉树中所有结点，使得每个结点被访问一次且仅被访问一次。

(1). 前(先)序遍历

前序遍历：若二叉树为空，则空操作返回，否则先访问根结点，然后前序遍历左子树，再前序遍历右子书。

特点：①. 根----->左------->右

           ②. 根据前序遍历的结果可知第一个访问的必定是root结点。


(2). 中序遍历

中序遍历：若二叉树为空，则空操作返回，否则从根结点开始（注意并不是先访问根结点），中序遍历根结点的左子树，然后访问根结点，最后中序遍历右子树。

特点：①. 左----->根------->右

           ②. 根据中序遍历的结果，再结合前序遍历的root结点去划分root结点的左右子树。


(3). 后序遍历

后序遍历：若二叉树为空，则空操作返回，否则从左到右先叶子结点后结点的方式遍历访问左右子树，最后访问根结点。

特点：①. 左------>右------>根

           ②. 根据后序遍历的结果可知最后访问的必定是root结点。

*/
#include <iostream>
using namespace std;

struct node
{
    int key;
    struct node *left, *right;
};

struct node *newNode(int item)
{
    struct node *temp = new node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

//Inorder traversal
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

//Preorder traversal
void preorder(struct node *root)
{
    if (root == NULL)
        return;
    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

//Postorder traversal
void postorder(struct node *root)
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->key << " ";
}

//Insert key
struct node* insert(struct node* node, int key)
{
    if (node == NULL)
        return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
}

// Driver Code
int main()
{
    /* Let us create following BST
     *       50
     *     /    \
     *    30     70
     *   /  \   /  \
     * 20   40 60   80 */
    struct node *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    cout << "Inorder traversal: ";
    inorder(root);

    cout << "\nPreorder traversal: ";
    preorder(root);

    cout << "\nPostorder traversal: ";
    postorder(root);
    cout << endl;
    return 0;
}
