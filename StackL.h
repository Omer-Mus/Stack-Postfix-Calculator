/***************************************************/
/* Programmer: Omer Mustel                          */     
/* Date:                                            */    
/* Purpose:  Stack class  - Linked implementation   */
/****************************************************/

#ifndef STACK_H
#define STACK_H

template <class T>
struct node
{
    T data;
    node *next;
};

template <class T>
class Stack
{
   private:
      node<T> *top;
      int length;  
        
   public:
      //Constructor 
      Stack();
      // Destructor: releases memory allocated 
      ~Stack();
       // Destroy stack
      void destroy();
      //Copy constructor
      Stack ( const Stack<T> & other);
      //Overload the assignment operator 
      const Stack<T> & operator= (const Stack<T> & other);
      // function to copy a stack
      void copy (const Stack<T> & other);
      //Returns current length of stack
      int getLength();
      // Returns true if stack is full, false otherwise
      bool isFull();
      //Returns true if stack is empty, false otherwise
      bool isEmpty();
      //If stack is not full, inserts parameter item 
      // If stack is full, prints error message
      void push (T item);
      //If stack is not empty removes top item
      T pop ();
      // Saves copy of top item in parameter item
      T getTop ();
};
#endif




     
