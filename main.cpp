//
//  main.cpp
//  Created by Nivetha Mahalakshmi Balasamy on 3/28/16.
//  Copyright © 2016 Nivetha Mahalakshmi Balasamy. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <stdio.h>


int red_node_count=0;


class Tree{
    
    struct BinTree
    {
        int data;
        struct BinTree *left;
        struct BinTree *right;
        bool colour;
        int N;
        
    };
    
public:
    
    Tree(){
        
        rootptr=NULL;
        
    }
    
    void rb_insert(int data){
        rootptr = insert(rootptr, data);
        rootptr->colour = BLACK;
    }
    
    int size(){
        return sizeR(rootptr);
    }
    
    void printinorder(){
        return inorder(rootptr);
    }
    
    
private:
    BinTree* rootptr;
    const static bool RED = true;
    const static bool BLACK = false;
    
    BinTree* createBNode(int data){
        struct BinTree* newnode = new (struct BinTree);
        newnode->data = data;
        newnode->left = newnode->right = NULL;
        newnode->colour=RED;
        newnode->N=1;
        return newnode;
    }
    
    BinTree* insert(BinTree* BinTree, int data){
        if(BinTree == NULL){
            return createBNode(data);
            
        }
        
         if(data <= BinTree->data){
            BinTree->left = insert(BinTree->left, data);
        }
        else {
            BinTree->right = insert(BinTree->right, data);
        }
    
        if(isRed(BinTree->right) && !isRed(BinTree->left)) BinTree =rotateleft(BinTree);
        if(isRed(BinTree->left) && isRed(BinTree->left->left)) BinTree=rotateright(BinTree);
        if(isRed(BinTree->left) && isRed(BinTree->right)) flipcolours(BinTree);
        
        return BinTree;
    }
    
    
    bool isRed(struct BinTree* BinTree){
        if(BinTree == NULL) return false;
        return BinTree->colour == RED;
    }
    
    BinTree* rotateleft(BinTree* BinTree){
        struct BinTree* x = BinTree->right;
        BinTree->right = x->left;
        x->left = BinTree;
        x->colour = BinTree->colour;
        BinTree->colour = RED;
        x->N = BinTree->N;
        return x;
    }
    
    BinTree* rotateright(BinTree* BinTree){
        struct BinTree* x = BinTree->left;
        BinTree->left = x->right;
        x->right = BinTree;
        x->colour = BinTree->colour;
        BinTree->colour = RED;
        x->N = BinTree->N;
        return x;
    }
    
    void flipcolours(struct BinTree* BinTree){
        BinTree->colour = RED;
        BinTree->left->colour = BLACK;
        BinTree->right->colour = BLACK;
    }
    
    // Internal Path Length - RBTree
    //int internalpathlength(BinTree* rootptr, int curr_level){
    //    if(rootptr == NULL){
    //        return 0;
    //    }
    //    else
    //        return (curr_level+internalpathlength(rootptr->left,curr_level+1)+internalpathlength(rootptr->right,curr_level+1));
    //
    //}
    
    void inorder(BinTree* BinTree){
        if(BinTree == NULL) return;
        inorder(BinTree->left);
        
        if(BinTree->colour == RED)
            //std::cout<<BinTree->data<<endl;
            red_node_count++;
        inorder(BinTree->right);
        
    }
    
    
    int sizeR(struct BinTree* BinTree){
        if(BinTree == NULL){
            return 0;
        }
        else{
            return sizeR(BinTree->left)+1+sizeR(BinTree->right);
        }
        
    }
    
};


int main(int argc,const char* argv[]){
    
    //BinTree* rootptr=NULL;
    Tree *t;
    t = NULL;
    
    std::ofstream outfile;
    outfile.open("out.txt");
    
    int size=10000;
    int data[size];
    int trial=100;
    
    for(int j=0;j<trial;j++){
        
        t = new Tree();
        
        //std::srand(unsigned(std::time(0)));
        //std::srand ( unsigned ( std::time(0)*100));
        srand( static_cast<unsigned int>(time(0)));
        
        for (int i=0; i<size; i++)
            
        {
            data[i]= (rand() % 10000);
            t->rb_insert(data[i]);
        }
        
        t->printinorder();
        std::cout<<" Size "<<t->size();
        
        int y = red_node_count;
        float x= t->size();
        float percent = y/x;
        std::cout<<" Percentage "<<percent<<std::endl;
        outfile<<percent<<std::endl;
        
        delete t;
        red_node_count=0;
        //sleep(1);
    }
    
    return 0;
}






