#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

/**
 * AVL tree node.
 */
struct TreeNode
{
    int nData;
    TreeNode* pstLeft;
    TreeNode* pstRight;
    int nHeight;
};

/**
 * AVL tree node.
 */
class AVLTree
{
public:

    AVLTree();
    ~AVLTree();
    void InsertNode( const int nData_i );
    void DeleteNode( const int nData_i );
    void PrintTree();

private:

    int Height( TreeNode*& pstRoot_io );
    void RotateLeft( TreeNode*& pstRoot_io );
    void RotateRight( TreeNode*& pstRoot_io );
    void RotateLeftRight( TreeNode*& pstRoot_io );
    void RotateRightLeft( TreeNode*& pstRoot_io );
    void Print( TreeNode*& pstRoot_i, const int nSpace_i );
    int Insert( TreeNode*& pstRoot_io, const int nData_i );
    int Delete( TreeNode*& pstRoot_io, const int nData_i );

private:

    TreeNode* m_pstRoot;
};

#endif // _AVL_TREE_H_