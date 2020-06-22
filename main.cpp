#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>

using namespace std;

struct tree
{
    char contains;
    tree* left, *right;
};

// check if 'c'
// is an operator
bool isOperator(char c)
{
    if (c == 'H' || c == 'V')
        return true;
    else
        return false;
}
//ignore '-'
bool isFake(char c)
{
    if (c == '-')
        return true;
    else
        return false;
}

// print tree function
void look(tree *t)
{
    if(t)
    {
        look(t->left);
        printf("%c ", t->contains);
        look(t->right);
    }
}
//print tree in reverse sort of
void lookback(tree *node)
{
    if (node == NULL)
        return;

    // first recur on left subtree
    lookback(node->left);

    // then recur on right subtree
    lookback(node->right);

    // now deal with the node
    cout << node->contains << " ";
}

//make a node
tree* newNode(int v)
{
    tree *temp = new tree;
    temp->left = temp->right = NULL;
    temp->contains = v;
    return temp;
};

tree* buildTree(const std::string& input)
{
    stack<tree *> st;
    tree *t, *t1, *t2;

    // Traverse through input
    for (int i=0; i < input.length(); i++)
    {
        {
            if (std::isspace(input[i]))
            {
                continue;
            }
        }
        // If operand as in not '-' or 'H' or 'V' push onto the stack
        if (!isOperator(input[i]) && (!isFake(input[i])))
        {
            t = newNode(input[i]);
            st.push(t);
        }
        else if (isOperator(input[i]) && (!isFake(input[i]))) // operator
        {
            t = newNode(input[i]);

            
            t1 = st.top(); 
            st.pop();      
            t2 = st.top();
            st.pop();

            //  make children
            t->right = t1;
            t->left = t2;

            // Add to stack
            st.push(t);
        }
        else
        {
            //do nothing
        }
    }

    //  root of tree
    t = st.top();
    st.pop();

    return t;
}

class block {
    int width, length;
public: block();
    block(int, int);
    void setwidth (int w)
    {
        width = w;
    }

    void setlength (int l)
    {
        length = l;
    }
    int getwidth() {return width;}
    int getlength() {return length;}
    int getarea() {return width * length;}

};

block::block()
{
    width = 0;
    length = 0;
}

block::block (int a, int b)
{
    width = a;
    length = b;
}


block floor(tree* root, std::vector<block> &blocks)
{
    int index, smallvalue1, smallindex1, smallarray1[6];
    block block1, block2, block3, block4, block5, block6;

    // empty tree
    if (!root)
        return block(0,0);

    // leaf node
    if (!root->left && !root->right) {
        index = (int(root->contains) - '0') - 1;
        cout << blocks[index].getwidth() << " " <<blocks[index].getlength() << endl;
        return blocks[index];
    }
    // Evaluate left subtree
    block l_val = floor(root->left, blocks);

    // Evaluate right subtree
    block r_val = floor(root->right, blocks);

    if (root->contains == 'H')
    {
        int lwidth1, lwidth2, llength1, llength2, rwidth1, rwidth2, rlength1, rlength2;
        lwidth1 = l_val.getwidth();
        llength1 = l_val.getlength();
        lwidth2 = l_val.getlength();
        llength2 = l_val.getwidth();
        rwidth1 = r_val.getwidth();
        rlength1 = r_val.getlength();
        rwidth2 = r_val.getlength();
        rlength2 = r_val.getwidth();

        block1.setwidth(max(lwidth1, rwidth1));
        block1.setlength(llength1 + rlength1);
        smallarray1[0] = block1.getarea();

        if (lwidth1 > rwidth1) {
            block2.setwidth(max(lwidth2, rwidth1));
            block2.setlength(llength2 + rlength1);
            smallarray1[1] = block2.getarea();
        }
        else {
            block2.setwidth(max(lwidth1, rwidth2));
            block2.setlength(llength1 + rlength2);
            smallarray1[1] = block2.getarea();
        }
        block3.setwidth(max(lwidth2,rwidth2));
        block3.setlength(llength2 + rlength2);
        smallarray1[2] = block3.getarea();
        smallvalue1 = smallarray1[0];
        smallindex1 = 0;
        for (int k = 0; k < 3; k++)
        {
            if (smallarray1[k] < smallvalue1)
            {
                smallvalue1 = smallarray1[k];
                smallindex1 = k;
            }
        }

        if (smallindex1 == 0){
            cout << "H block " << block1.getwidth() << " " << block1.getlength()  << endl;
            return block1;
        }
        else if (smallindex1 == 1){
            cout << "H block " << block2.getwidth() << " " << block2.getlength() << endl;
            return block2;
        }
        else if (smallindex1 == 2){
            cout << "H block " << block3.getwidth() << " " << block3.getlength() << endl;
            return block3;
        }
    }
    if (root->contains == 'V')
    {
        int lwidth1, lwidth2, llength1, llength2, rwidth1, rwidth2, rlength1, rlength2;
        lwidth1 = l_val.getwidth();
        llength1 = l_val.getlength();
        lwidth2 = l_val.getlength();
        llength2 = l_val.getwidth();
        rwidth1 = r_val.getwidth();
        rlength1 = r_val.getlength();
        rwidth2 = r_val.getlength();
        rlength2 = r_val.getwidth();

        block4.setlength(max(llength1, rlength1));
        block4.setwidth(lwidth1 + rwidth1);
        smallarray1[3] = block4.getarea();

        if (rwidth1 < lwidth1) {
            block5.setlength(max(llength1, rlength2));
            block5.setwidth(lwidth1 + rwidth2);
            smallarray1[4] = block5.getarea();
        }
        else {
            block5.setlength(max(llength2, rlength1));
            block5.setwidth(lwidth2 + rwidth1);
            smallarray1[4] = block5.getarea();
        }
        block6.setlength(max(llength2, rlength2));
        block6.setwidth(lwidth2 + rwidth2);
        smallarray1[5] = block6.getarea();

        smallvalue1 = smallarray1[3];
        smallindex1 = 3;
        for (int k = 3; k < 6; k++)
        {
            if (smallarray1[k] < smallvalue1)
            {
                smallvalue1 = smallarray1[k];
                smallindex1 = k;
            }
        }

        if (smallindex1 == 3){
            cout << "V block " << block4.getwidth() << " " << block4.getlength()   << endl;
            return block4;
        }
        else if (smallindex1 == 4){
            cout << "V block " << block5.getwidth() << " " << block5.getlength() << endl;
            return block5;
        }
        else if (smallindex1 == 5){
            cout << "V block " << block6.getwidth() << " " << block6.getlength() << endl;
            return block6;
        }

    }
}





int main(int argc, char *argv[]) {

    std::ifstream inputfile;
    inputfile.open(argv[1]);
    //inputfile.open("C:/Users/Luna Lovegood/ClionProjects/stockmeyer/caseV2.txt");
    int leafwidth, leaflength, outwidth, outlength, area, numBlocks = 0;
    std::string polish;
    std::vector<block> inputblocks;
    block finalblock;

    if (!inputfile)
    {
        printf("Input file failed to open. Program Terminated!\n");
        return 1;
    }

    std::getline (inputfile,polish);
    cout << polish << endl;

    tree* stock = buildTree(polish);
    look(stock);
    cout << endl;
    lookback(stock);

    while (!inputfile.eof())
    {
        inputfile >> leafwidth >> leaflength;
        inputblocks.push_back(block(leafwidth, leaflength));
        numBlocks++;
    }

    inputfile.close();

    /*for (int i = 0; i < inputblocks.size(); i++)
    {

        outwidth = inputblocks[i].getwidth();
        outlength = inputblocks[i].getlength();
        area = inputblocks[i].getarea();
        cout << outwidth <<  " " << outlength << " " << area << endl;
    }*/
    cout << endl;

    finalblock = floor(stock, inputblocks);
    cout << finalblock.getwidth() << endl;
    cout << finalblock.getlength() << endl;
    cout << finalblock.getarea() << endl;




    std::cout << "Hello, World!" << std::endl;
    return 0;
}
