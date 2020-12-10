//Shunting Yard by Joshua Lukose 11/20

#include <iostream>
#include <cstring>
#include "tree.h"

using namespace std;

// Declaring Stack
struct Stack{
    char StackData;
    
    Stack *StackLink;
};

struct StackT{
    tree* StackDataT;
    StackT* StackLinkT;
};

tree* peekT();
tree* popT();
void StackPushT(tree* t);
bool isStackEmptyT();
StackT *topT = NULL;
StackT *bottomT = NULL;

bool aa=true;
bool isStackEmpty();
void StackPush(char value);
char pop();
char peek();
void clearStack();
//stack pointers
Stack *top = NULL;
Stack *bottom=NULL;
//declaring queue
struct Queue{
    char QueueData;
    
    Queue *QueueLink;
};

bool isQueueEmpty();
void enqueue(int value);
void dequeue();
char showFirst();
void printQueue();
//queue pointers
Queue *front = NULL;
Queue *rear = NULL;

int findPrecedence(char op);

void preFix(tree* n);
void postFix(tree* n);
void inFix(tree* n);
tree* createData();
tree* buildTree();

int main(){
    int i = 0;
    char input[50], input2[50], prefix[100];
    cout << "Please input an equation constructed of characters. ex:(a+b)" << endl;
    cin.get(input, 50);
    cin.clear();
    cin.ignore(100000, '\n');
    
    while(input[i] != '\0'){
        if (input[i] == '('){
            //add to stack
            cout<<"\nstack push "<<input[i];
            StackPush(input[i]);
        }
        //if it is an operand
        else if (isalpha(input[i])){
            cout<<"\nqueue "<<input[i];
            enqueue(input[i]);
        }
        //if it is an operator
        //check precedence with top of stack
        //if greater then push into stack
        //if not then pop all the stack into the queue
        else if (input[i] == '+' || input[i] == '-' ||  input[i] == '*' || input[i] == '/' || input[i] == '^'){
            if (isStackEmpty()){
                cout<<"\nstack push "<<input[i];
                StackPush(input[i]);
            }
            else if (findPrecedence(input[i]) >= findPrecedence(peek()))
                StackPush(input[i]);
            else{
                while(!isStackEmpty()){
                    enqueue(pop());
                }
                StackPush(input[i]);
            }
            
        }
        //if it closing paranthesis
        else if (input[i] == ')'){
            while (peek() != '('){
                enqueue(pop());
            }
            pop();
        }
        i++;
    }
    
    //put everything in the queue
    while(!isStackEmpty())
        enqueue(pop());
    
    printQueue();
    
    tree* mytree = buildTree();
    
    while (aa==true){
        cout << "\nWould you like the output in infix, postfix, or prefix? (If you would like to quit please type quit)" <<  endl;
        cin.get(input2, 50);
        cin.clear();
        cin.ignore(100000, '\n');
        
        if(strcmp(input2, "infix") == 0){
            inFix(mytree);
        }
        
        if(strcmp(input2, "postfix") == 0){
            postFix(mytree);
        }
        
        if(strcmp(input2, "prefix") == 0){
            preFix(mytree);
        }
        if(strcmp(input2, "quit") == 0){
            aa = false;
        }
        else{
            cout << "\nInvalid Input." << endl;
        }
    }
}

//check if stack is empty
bool isStackEmpty(){
    if (top == NULL)
        return true;
    else{
        return false;
    }
}

//add to top of stack
void StackPush(char value){
    Stack *ptr = new Stack();
    ptr -> StackData = value;
    ptr -> StackLink = top;
    top = ptr;
}

//take element off top of stack
char pop(){
    char data;
    if(isStackEmpty() == true){
        cout << "The stack is empty" << endl;
        return ' ';
    }
    else{
        Stack *ptr = top;
        top = ptr -> StackLink;
        data = ptr -> StackData;
        delete ptr;
        return data;
    }
    
}

//show element at top of stack
char peek(){
    char op = ' ';
    if (isStackEmpty() == true){
        cout << "The stack is empty" << endl;
        return op;
    }
    else{
        cout << "The element at the top is: " << top -> StackData;
        op = top -> StackData;
        return op;
    }
    
}

//check if queue is empty
bool isQueueEmpty(){
    if (front == NULL && rear == NULL){
        return true;
    }
    else{
        return false;
    }
}

//add to queue
void enqueue(int value){
    Queue *ptr = new Queue();
    ptr -> QueueData = value;
    ptr -> QueueLink = NULL;
    
    if (front == NULL){
        front = ptr;
        rear = ptr;
    }
    else{
        rear -> QueueLink = ptr;
        rear = ptr;
    }
}

//delete from queue
void dequeue(){
    if (isQueueEmpty() == true){
        cout << "The queue is empty." << endl;
    }
    else{
        if (front == rear){
            free(front);
            front = rear = NULL;
        }
        else{
            Queue *ptr = front;
            front = front -> QueueLink;
            free(ptr);
        }
    }
}

//show front of queue
char showFirst(){
    if (isQueueEmpty() == true){
        cout << "The queue is empty." << endl;
        return 0;
    }
    else{
        cout << front -> QueueData;
        return front ->  QueueData;
    }
}

//print queue
void printQueue(){
    if (isQueueEmpty() == true){
        cout << "The queue is empty." << endl;
    }
    else{
        Queue *ptr = front;
        cout<<"\n";
        while(ptr != NULL){
            cout << ptr -> QueueData;
            ptr = ptr -> QueueLink;
        }
        cout<<"\n";
    }
}

//clear stack
void clearStack(){
    while (isStackEmpty() == false){
        pop();
    }
}

//assigns opaerator precedence
int findPrecedence(char op){
    switch (op){
        case '+':
        case '-':
            return 1;
        case '/':
        case '*':
            return 2;
        case '^':
            return 3;
    }
    return 0;
}

//print tree in prefix
void preFix(tree* n){
    if (n == NULL){
        return;
    }
    else{
        cout << n -> getData();
        preFix(n -> getLeft());
        preFix(n -> getRight());
    }
}

//print tree in postfix
void postFix(tree* n){
    if (n == NULL){
        return;
    }
    else{
        postFix(n -> getLeft());
        postFix(n -> getRight());
        cout << n -> getData();
    }
}

//print tree in fix
void inFix(tree* n){
    if (n == NULL){
        return;
    }
    else{
        inFix(n -> getLeft());
        cout << n -> getData();
        inFix(n -> getRight());
    }
}

//determines if tree stack is empty
bool isStackEmptyT(){
    if (topT == NULL)
        return true;
    else{
        return false;
    }
}

//pop tree stack
tree* popT(){
    tree* subtree = NULL;
    if(isStackEmptyT() == true){
        cout << "The stack is empty" << endl;
        return subtree;
    }
    else{
        StackT *ptr = topT;
        topT = ptr -> StackLinkT;
        subtree = ptr -> StackDataT;
        //  delete ptr;
        return subtree;
    }
}

//push in tree stack
void StackPushT(tree* t){
    StackT *ptr = new StackT();
    ptr -> StackDataT = t;
    ptr -> StackLinkT = topT;
    topT = ptr;
}

//peek function for tree stack
tree* peekT(){
    tree* op = NULL;
    if (isStackEmptyT() == true){
        cout << "The stack is empty" << endl;
        return op;
    }
    else{
        cout << "The element at the top is: " << topT -> StackDataT -> getData();
        op = topT -> StackDataT;
        return op;
    }
    
}

//build binary expression tree from postfix queue
tree* buildTree(){
    //build tree
    Queue* position;
    position = front;
    
    //traverse queue left to right
    while (position != rear->QueueLink){
        char treeData = position -> QueueData;
        //if operand, push in stack
        if (isalpha(treeData)){
            tree* operand = new tree(treeData);
            StackPushT(operand);
        }
        //if operator, assign the left and right to be the two top stack nodes
        else if (treeData == '+' || treeData == '-' || treeData == '/' || treeData == '*' || treeData == '^'){
            tree* t = new tree(treeData);
            tree* right = peekT();
            popT();
            tree* left = peekT();
            popT();
            t -> setRight(right);
            t -> setLeft(left);
            StackPushT(t);
        }
        position = position -> QueueLink;
    }
    return topT -> StackDataT;
}
