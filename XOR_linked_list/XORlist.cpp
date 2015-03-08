#include <iostream>
#include <stdlib.h>
#include <stdint.h>
using namespace std;

struct node{
  int key;
  node *np;
};

/* we need 2 nodes to keep track of the beginning and the
end of the list to reverse the list in O(1) and for the delete
function */
struct node* head;
struct node* tail;

/* XOR-ing 2 pointers which had to be casted via intptr_t for
the XOR to work. The result becomes struct node pointer. */
struct node* XOR(struct node* a, struct node* b){

return (struct node*)((intptr_t)(a) ^ (intptr_t)(b));

}

void initialize(){
   head = NULL;
   tail = NULL;
}

/* insertion at the back of the list */
void insert(int key){

   struct node* new_node = new node;
   new_node->key = key;
   new_node->np = XOR(tail,NULL);

   if(tail){
     // update connection between tail and new_node
     struct node *next = XOR(NULL, tail->np);
     tail->np = XOR(next,new_node);
   }

   if(!head){
     // if head is null
     head = new_node;
   }

   tail = new_node;

}

void printXORlist(){

    struct node* curr = head;
    struct node* prev = NULL;
    struct node* next;

    while(curr){

       cout<<curr->key<<" ";
       next = XOR(prev,curr->np);
       prev = curr;
       curr = next;
    }
   cout<<"\n";
}

struct node* search(int key){

    struct node* curr = head;
    struct node* prev = NULL;
    struct node* next;

    while(curr){

     if(curr->key == key) return curr;
     // the following 3 instructions handle the walking through
     // the list
     next = XOR(prev,curr->np);
     prev = curr;
     curr = next;

    }
    // key not found
    return NULL;

}

void deleteNode(int key){

   struct node* curr = head;
   struct node* prev = NULL;
   struct node* next;

   while(curr){

      if(curr->key == key){

         next = XOR(curr->np,prev);

         // we distinguish 4 cases which need to be updated if they happen
         if(prev){
           // prev is an inside node in which case we bypass the connection
           // with current node and connect prev with next directly
           struct node* aux = XOR(curr,prev->np);
           prev->np = XOR(aux,next);

         } else {
           // prev is null and we just move the head to next and we get rid of
           // the first element
           head = next;
         }

         if(next){
           // next is an inside node in which case we bypass the connection
           // with current node and connect next with prev
           struct node* aux = XOR(curr,next->np);
           next->np = XOR(aux,prev);

         } else {
           // next is null so we move the tail pointer on prev, to get rid
           // of the last element
           tail = prev;
         }

         return; // no need to go further

      } else {
        // in the case that key is not found just go further into the list
        next = XOR(prev,curr->np);
        prev = curr;
        curr = next;
      }

   }
}

/* to reverse the list is enough to swap the beginning and the end
 since for an inside node the np field is commutatice in the sense that
 XOR(A,B) = XOR(B,A) so it doesn't matter if we walk through the list
 from head to tail or from the tail to the head, such that the inside
 nodes need no further change. */
void reverse(){
   struct node* aux;
   aux = head;
   head = tail;
   tail = aux;
}

int main()
{
    initialize();
    insert(2);
    insert(4);
    insert(3);
    insert(5);

    printXORlist();

    if(search(3)) cout<<"Found 3\n";
    else cout<<"Not found\n";

    reverse();

    printXORlist();

    deleteNode(5);
    deleteNode(4);

    printXORlist();

    return 0;
}
