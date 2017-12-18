//
// Created by Fitz on 2017/12/14.
//
/*
 * 在构建平衡二叉树的过程中，每当插入一个结点时，先检查是否因插入而破坏了树的平衡性，若是，则找出最小不平衡子树(通过递归的方式)，在保持二叉排序树特性的前提下，调整关系。
这句话意味着：只要破坏了平衡性，就马上修改使得二叉树重新平衡，意思就是只要修改了最小不平衡树就可以使得整个二叉树重新平衡.
 */
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;
#define nullptr NULL


class AVL {
#define LH 1   //表示左面的树高
#define EH 0   //表示两面的树一样高
#define RH -1  //表示右面的树高
public:
    class node {
#define infinite 0x0fffffff
    public:
        int balancedFactor;  //AVL的平衡因子
        int data;    //节点的数据
        int sameNum;  //表示与该节点有相同关键字的个数
        node *lchild, *rchild;

        node()   //将节点的数据初始化
        {
            lchild = nullptr;
            rchild = nullptr;
            data = infinite;
            sameNum = 1;
            balancedFactor = 0;
        }
    };

    node *root;
    int size;

    AVL()   //初始化树的节点
    {
        root = new node;
        size = 0;
    }

    //test if the AVL tree is empty if so , return true
    bool empty() {
        return !size;
    }

    //通过中序遍历建立的搜索树来得到排序后的结果
    void MidRecursive(node *root) {
        if (root != nullptr) {
            MidRecursive(root->lchild);
            for (int i = 0; i < root->sameNum; i++)
                cout << root->data << " ";
            MidRecursive(root->rchild);
        }
    }

    //search the specific data
    node *search(int searchNum) {
        if (searchNum == root->data)
            return root;
        else if (searchNum < root->data) {
            if (root->lchild)
                return searchRecursive(searchNum, root->lchild);
            else
                return nullptr;
        } else {
            if (root->rchild)
                return searchRecursive(searchNum, root->rchild);
            else
                return nullptr;
        }
    }


    void insert(int insertNum) {
        size++;
        bool addFloor = false;
        if (root->data == infinite)    //在第一次插入节点时，需要特殊处理, 如果是根节点没有数据,则他的值是宏 infinite
        {
            root->data = insertNum;
            return;
        }
        if (root->data == insertNum)   //如果有相同的关键字，就在该节点的记录重复的数据上加1
        {
            root->sameNum++;
            return;
        } else if (insertNum < root->data) {    //插入的节点在该节点的左子树上
            root->lchild = insertRecursive(root->lchild, insertNum, &addFloor);
            if (addFloor) {
                switch (root->balancedFactor)        //addFloor  是表示插入新节点导致层数增加，根据原来的状态来判断现在的平衡因子
                {
                    case LH:    //原本左子树比右子树高，需要作左平衡处理
                        root = leftBalanced(root);    //进行左平衡
                        addFloor = false;
                        break;
                    case EH:   //原本左、右子树等高，现因左子树增高而使树增高
                        root->balancedFactor = LH;
                        addFloor = true;
                        break;
                    case RH:   //原本右子树比左子树高，现左、右子树等高
                        root->balancedFactor = EH;
                        addFloor = false;
                        break;
                }
            }
        } else {
            root->rchild = insertRecursive(root->rchild, insertNum, &addFloor);
            if (addFloor) {
                switch (root->balancedFactor) {
                    case LH:    //原本左子树比右子树高，现左、右子树等高
                        root->balancedFactor = EH;
                        addFloor = false;
                        break;
                    case EH:    //原本左、右子树等高，现因右子树增高而使树增高
                        root->balancedFactor = RH;
                        addFloor = true;
                        break;
                    case RH:   //原本右子树比左子树高，需要作右平衡处理
                        root = rightBalanced(root);   //进行右平衡
                        addFloor = false;
                        break;
                }
            }
        }
    }

    //负责删除节点的函数
    void Delete(node *tree, int deleteNum) {
        if (!tree)
            return;
        node *pr, *p;
        if (empty())
            return;
        if (tree->data == deleteNum) {
            size--;
            if (tree->sameNum > 1) {   //如果遇到该关键词有多个相同的,需要将count减1
                tree->sameNum--;
            } else {
                if (!tree->lchild && !tree->rchild) {    //如果该节点是叶节点的情况,直接删除节点
                    if (tree == root)
                        tree->data = infinite;
                    else
                        delete (tree);
                } else if (!tree->lchild) {   //如果是只有左子树,没有右子树
                    tree->data = tree->rchild->data;
                    tree->sameNum = tree->rchild->sameNum;
                    pr = tree->rchild->lchild;
                    p = tree->rchild->rchild;
                    delete (tree->rchild);
                    tree->lchild = pr;
                    tree->rchild = p;
                } else if (!tree->rchild) {   //只有右子树,没有左子树
                    tree->data = tree->lchild->data;
                    tree->sameNum = tree->lchild->sameNum;
                    pr = tree->lchild->lchild;
                    p = tree->lchild->rchild;
                    delete (tree->lchild);
                    tree->lchild = pr;
                    tree->rchild = p;
                } else {    //既有左子树,又有右子树,需要找到右子树中最左的节点,将其删除
                    pr = p = tree->rchild;
                    while (p->lchild) {
                        pr = p;
                        p = p->lchild;
                    }
                    tree->data = p->data;
                    tree->sameNum = p->sameNum;
                    if (pr != p) {
                        pr->lchild = p->rchild;
                    } else {
                        tree->rchild = p->rchild;
                    }
                    delete (p);
                }
            }
        } else if (deleteNum < tree->data) {   //递归左子树,寻找匹配的节点
            Delete(tree->lchild, deleteNum);
        } else {
            Delete(tree->rchild, deleteNum);  //递归右子树,寻找匹配的节点
        }
    }

private:
    //this is for recursive search use and the other users can't use and see it and parameter is complex ,the search() is more easy for use
    node *searchRecursive(int searchNum, node *newTree) {
        if (searchNum == newTree->data)
            return newTree;
        else if (searchNum < newTree->data) {
            if (newTree->lchild)
                return searchRecursive(searchNum, newTree->lchild);
        } else {
            if (newTree->rchild)
                return searchRecursive(searchNum, newTree->rchild);
            else
                return nullptr;
        }
    }

    //这个函数用于递归调用，与上面public属性的区别在于上面的函数传入的参数更少，更符合restful api 的设计
    node *insertRecursive(node *tree, int insertNum, bool *addFloor) {
        if (!tree)   //如果是空，表示搜索树中没有该节点
        {
            tree = new node;
            tree->data = insertNum;
            *addFloor = true;
            return tree;
        }
        if (tree->data == insertNum) {
            tree->sameNum++;
            *addFloor = false;
        } else if (insertNum < tree->data) {
            tree->lchild = insertRecursive(tree->lchild, insertNum, addFloor);
            if (*addFloor) {
                switch (tree->balancedFactor) {
                    case LH:
                        tree = leftBalanced(tree);
                        *addFloor = false;
                        break;
                    case EH:
                        tree->balancedFactor = LH;
                        *addFloor = true;
                        break;
                    case RH:
                        tree->balancedFactor = EH;
                        *addFloor = false;
                        break;
                }
            }
        } else {
            tree->rchild = insertRecursive(tree->rchild, insertNum, addFloor);
            if (*addFloor) {
                switch (tree->balancedFactor) {
                    case LH:
                        tree->balancedFactor = EH;
                        *addFloor = false;
                        break;
                    case EH:
                        tree->balancedFactor = RH;
                        *addFloor = true;
                        break;
                    case RH:
                        tree = rightBalanced(tree);
                        *addFloor = false;
                        break;
                }
            }
        }
        return tree;
    }

    //单次向左旋转
    void leftRotate(node **tree) {
        node *newNode;
        newNode = (**tree).rchild;
        (**tree).rchild = newNode->lchild;
        newNode->lchild = *tree;
        *tree = newNode;
    }

    //单次向右旋转
    void rightRotate(node **tree) {
        node *newNode;
        newNode = (**tree).lchild;
        (**tree).lchild = newNode->rchild;
        newNode->rchild = *tree;
        *tree = newNode;
    }

    node *leftBalanced(node *tree) {
        node *l = tree->lchild, *lr = l->rchild;    //l表示tree的左子树 lr表示左子树的右子树
        switch (l->balancedFactor)             //根据l的平衡因子来判断  是LL旋转还是LR旋转的方式来调节树的平衡
        {
            case LH:
                rightRotate(&tree);       //是左子树的左子树导致不平衡，是LL的旋转方式
                tree->balancedFactor = l->balancedFactor = EH;
                break;
            case RH:
                switch (lr->balancedFactor)   //调节tree和l的平衡因子
                {
                    case LH:
                        l->balancedFactor = EH;
                        tree->balancedFactor = RH;
                        break;
                    case EH:
                        l->balancedFactor = tree->balancedFactor = EH;
                        break;
                    case RH:
                        l->balancedFactor = LH;
                        tree->balancedFactor = EH;
                        break;
                }
                lr->balancedFactor = EH;
                leftRotate(&l);    //是LR的情况
                tree->lchild = l;
                rightRotate(&tree);

        }
        return tree;
    }

    node *rightBalanced(node *tree) {
        node *r = tree->rchild, *rl = r->lchild;
        switch (r->balancedFactor) {
            case RH:
                leftRotate(&tree);
                tree->balancedFactor = r->balancedFactor = EH;     //是RR的情况
                break;
            case LH:
                switch (rl->balancedFactor) {
                    case LH:
                        tree->balancedFactor = EH;
                        r->balancedFactor = RH;
                        break;
                    case EH:
                        tree->balancedFactor = r->balancedFactor = EH;
                        break;
                    case RH:
                        tree->balancedFactor = LH;
                        r->balancedFactor = EH;
                        break;
                }
                rl->balancedFactor = EH;
                rightRotate(&r);
                tree->rchild = r;   //是RL的旋转调节平衡方式
                leftRotate(&tree);
        }
        return tree;
    }
};

int main() {
    AVL atree;
    int n, a;
    cout << "input the number of the num" << endl;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a;
        atree.insert(a);
    }
    for (int i = 1; i < 15; i++) {
        atree.Delete(atree.root, i);
    }
    cout << atree.size << endl;
    cout << "mid sequence results are:" << endl;
    atree.MidRecursive(atree.root);
    cout << endl;
    return 0;
}
//13 12 10 6 4 11 2 8 7 5 3 1 9 13
//1,5,3,7,6,2,4,8,9,0
//27 12 10 6 4 11 2 8 7 5 3 1 9 13 102 3 14 45 23 455 65 12 4 56 56 546 1 45 6