#include <iostream>
#include "tree.h"

//tree node has keft pointer, right pointer, data, and a next
tree::tree(char setData){
  data = setData;
  right = NULL;
  left = NULL;
  next = NULL; 
}

void tree::setRight(tree* inRight){
  right = inRight;
}

tree* tree::getRight(){
  return right;
}

void tree::setLeft(tree* inLeft){
  left = inLeft;
}

tree* tree::getLeft(){
  return left;
}

void tree::setNext(tree* inNext){
  next = inNext;
}

tree* tree::getNext(){
  return next;
}

void tree::setData(char inData){
  data = inData;
}

char tree::getData(){
  return data; 
}
