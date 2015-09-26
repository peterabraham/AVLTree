#include <iostream>
#include <algorithm>
#include <iomanip>
#include <ctype.h>
#include "AVLTree.h"

using namespace std;


/**
 * Constructor.
 */
AVLTree::AVLTree() : m_pstRoot( NULL )
{
}


/**
 * Destructor.
 */
AVLTree::~AVLTree()
{
}


/**
 * Function to call abtracted insert function to insert a tree node.
 */
void AVLTree::InsertNode( const int nData_i )
{
    if( !Insert( m_pstRoot, nData_i ))
    {
        cout << "Failed to insert data" << endl;
    }
}


/**
 * Function to call abtracted delete function to delete a tree node.
 */
void AVLTree::DeleteNode( const int nData_i )
{
    if( !Delete( m_pstRoot, nData_i ))
    {
        cout << "Failed to delete";
    }
}


/**
 * Function to call abtracted print function to print the tree.
 */
void AVLTree::PrintTree()
{
    Print( m_pstRoot, 0 );
}


/**
 * Function to return the height of input Node.
 */
int AVLTree::Height( TreeNode*& pstRoot_io )
{
    if( NULL == pstRoot_io )
    {
        return -1;
    }
    else
    {
        return pstRoot_io->nHeight;
    }
}


/**
 * Function to rotate the input Node anticlockwise(moving right to current & current to left).
 */
void AVLTree::RotateLeft( TreeNode*& pstRoot_io )
{
    TreeNode* pstTempNode = pstRoot_io;
    TreeNode* pstChgNode = pstRoot_io->pstRight;
    pstTempNode->pstRight = pstChgNode->pstLeft;
    pstChgNode->pstLeft = pstTempNode;

    pstRoot_io = pstChgNode;

    pstTempNode->nHeight = max( Height( pstTempNode->pstLeft ), Height( pstTempNode->pstRight )) + 1;
    pstRoot_io->nHeight = max( pstTempNode->nHeight, Height( pstRoot_io->pstRight )) + 1;
}


/**
 * Function to rotate the input Node clockwise(moving left to current & current to right).
 */
void AVLTree::RotateRight( TreeNode*& pstRoot_io )
{
    TreeNode* pstTempNode = pstRoot_io;
    TreeNode* pstChgNode = pstRoot_io->pstLeft;
    pstTempNode->pstLeft = pstChgNode->pstRight;
    pstChgNode->pstRight = pstTempNode;

    pstRoot_io = pstChgNode;

    pstTempNode->nHeight = max( Height( pstTempNode->pstLeft ), Height( pstTempNode->pstRight )) + 1;
    pstRoot_io->nHeight = max( Height( pstRoot_io->pstLeft ), pstTempNode->nHeight ) + 1;
}


/**
 * Function to  double rotate the input Node.
 * First left rotate current-->left.
 * Then right rotate current.
 */
void AVLTree::RotateLeftRight( TreeNode*& pstRoot_io )
{
    RotateLeft( pstRoot_io->pstLeft );
    RotateRight( pstRoot_io );
}


/**
 * Function to  double rotate the input Node.
 * First right rotate current-->right.
 * Then leftt rotate current.
 */
void AVLTree::RotateRightLeft( TreeNode*& pstRoot_io )
{
    RotateRight( pstRoot_io->pstRight );
    RotateLeft( pstRoot_io );
}


/**
 * Function to print the entire tree keeping root node at left.
 * Rotate the printed tree clockwise to see actual tree representation.
 */
void AVLTree::Print( TreeNode*& pstRoot_i, const int nSpace_i )
{
    if( NULL != pstRoot_i )
    {
        Print( pstRoot_i->pstRight, nSpace_i + 4 );
        cout << setw( nSpace_i ) << pstRoot_i->nData << endl;
        Print( pstRoot_i->pstLeft, nSpace_i + 4 );
    }
}


/**
 * Function to insert a new element to tree.
 * If the new element already exist(key value), no need to add.
 * Also balnces the tree if the |bal factor| > 1 after insertion.
 */
int AVLTree::Insert( TreeNode*& pstRoot_io, const int nData_i )
{
    try
    {
        if( NULL == pstRoot_io )
        {
            pstRoot_io = new TreeNode;
            pstRoot_io->nData = nData_i;
            pstRoot_io->nHeight = 0;
            pstRoot_io->pstLeft = pstRoot_io->pstRight = NULL;
        }

        else if( nData_i < pstRoot_io->nData )
        {
            if( Insert( pstRoot_io->pstLeft, nData_i ))
            {
                if( Height( pstRoot_io->pstLeft ) - Height( pstRoot_io->pstRight ) == 2 )
                {
                    if( nData_i < pstRoot_io->pstLeft->nData )
                    {
                        RotateRight( pstRoot_io );
                    }
                    else
                    {
                        RotateLeftRight( pstRoot_io );
                        //RotateRightLeft( pstRoot_io );
                    }
                } // End: Tree balance check.
            } // End: Insert function.
        } // End: Left insertion.

        else if( nData_i > pstRoot_io->nData )
        {
            if( Insert( pstRoot_io->pstRight, nData_i ))
            {
                if( Height( pstRoot_io->pstRight ) - Height( pstRoot_io->pstLeft ) == 2 )
                {
                    if( nData_i > pstRoot_io->pstRight->nData )
                    {
                        RotateLeft( pstRoot_io );
                    }
                    else
                    {
                        RotateRightLeft( pstRoot_io );
                        // RotateLeftRight( pstRoot_io );
                    }
                } // End: Tree balance check.
            } // End: Insert function.
        } // End: Right insertion.

        else
        {
            // Do nothing.
        }

        pstRoot_io->nHeight = max( Height( pstRoot_io->pstLeft ), Height( pstRoot_io->pstRight )) + 1;

        return 1;
    }
    catch( ... )
    {
        return 0;
    }
}


/**
 * Function to delete an element from tree.
 * If the element not present, do nothing.
 * Also balnces the tree if the |bal factor| > 1 after deletion.
 */
int AVLTree::Delete( TreeNode*& pstRoot_io, const int nData_i )
{
    try
    {
        if( NULL == pstRoot_io )
        {
            cout << "Node not found!!!..." << endl;
        }

        // To delete the selected node.
        else if( nData_i == pstRoot_io->nData )
        {
            TreeNode*& pstP = pstRoot_io;
            TreeNode* pstP0 = pstP;
            TreeNode** pstQQ = NULL;
            TreeNode* pstQ = NULL;

            if( NULL == pstP->pstLeft )
            {
                pstP = pstP->pstRight;
                delete pstP0;
            }
            else if( NULL == pstP->pstRight )
            {
                pstP = pstP->pstLeft;
                delete pstP0;
            }
            else
            {
                pstQQ = &pstP->pstLeft;
                while( NULL != ( *pstQQ )->pstRight )
                {
                    pstQQ = &( *pstQQ )->pstRight;
                }
                pstQ = *pstQQ;
                pstP->nData = ( *pstQQ )->nData;
                *pstQQ = pstQ->pstLeft;
                delete pstQ;
            }
        }

        else if( nData_i < pstRoot_io->nData )
        {
            if( Delete( pstRoot_io->pstLeft, nData_i ))
            {
                if( Height( pstRoot_io->pstLeft ) - Height( pstRoot_io->pstRight ) == 2 )
                {
                    if( nData_i < pstRoot_io->pstLeft->nData )
                    {
                        RotateRight( pstRoot_io );
                    }
                    else
                    {
                        RotateLeftRight( pstRoot_io );
                    }
                } // End: Tree balance check.
            } // End: Insert function.
        } // End: Left insertion.

        else if( nData_i > pstRoot_io->nData )
        {
            if( Delete( pstRoot_io->pstRight, nData_i ))
            {
                if( Height( pstRoot_io->pstRight ) - Height( pstRoot_io->pstLeft ) == 2 )
                {
                    if( nData_i > pstRoot_io->pstRight->nData )
                    {
                        RotateLeft( pstRoot_io );
                    }
                    else
                    {
                        RotateRightLeft( pstRoot_io );
                    }
                } // End: Tree balance check.
            } // End: Insert function.
        } // End: Right insertion.

        else
        {
            // Do nothing.
        }

        return 1;
    }
    catch( ... )
    {
        return 0;
    }
}


/**
 * Main function to demonstrate Linked List
 **/
int main()
{
    int nNumber;
    char chOprn;
    AVLTree tree;
    cout << "\nAVL  Tree displayed has it's root on left side...\n\n\n";

    while( 1 )
    {
        cout << "Enter an integer, followed by I for insertion\n"
                "or D for deletion, or enter Q to quit:";
        cin >> nNumber >> chOprn;
        if( cin.fail())
        {
            break;
        }
        chOprn = toupper( chOprn );
        if( chOprn == 'I')
        {
            tree.InsertNode( nNumber );
        }
        else if( chOprn == 'D' )
        {
            tree.DeleteNode( nNumber );
        }
        else
        {
            // Do nothing.
        }
        tree.PrintTree();
    }
    return 0;
}