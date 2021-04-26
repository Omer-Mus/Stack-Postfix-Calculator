// Programmer: Omer Mustel
// Date: 
// Purpose : Stack class implementation file
#include <iostream>
using namespace std;
#include "StackL.h"

template <class T>
Stack<T> :: Stack()
{
   top = NULL;
   length = 0;
}

template <class T>
Stack<T> :: ~Stack()
{
   destroy();
}

template <class T>
void Stack<T> :: destroy()
{
   node<T> *temp;

   while (top != NULL)
   {
      temp = top;
      top = top->next;
      delete temp;
   }

   length = 0;
}

template <class T>
Stack<T> :: Stack ( const Stack<T> & other)
{
   copy(other);
}

template <class T>
const Stack<T> & Stack<T> :: operator= (const Stack<T> & other)
{
    if ( this != &other )
    {
       destroy();
       copy(other);
    }
    return *this;
}

template <class T>
void Stack<T> :: copy(const Stack<T> & other)
{
    if ( other.top == NULL )
       top = NULL;
    else   
    {   
        node<T> *p;
        node<T> *r;

        top = new node<T>;
        top->data = other.top->data;

        p = other.top->next;
        r = top;

        while ( p != NULL )
        {
           r->next = new node<T>;
           r = r->next;

           r->data = p->data;
           p = p->next;

        }
      
        r->next = NULL;
    }
}
         
template <class T>
int Stack<T> :: getLength()
{
   return length;
}

template <class T>
bool Stack<T> :: isFull()
{
   return false;
}

template <class T>
bool Stack<T> :: isEmpty()
{
   return top == NULL;
}

template <class T>
void Stack<T> :: push(T item)
{
   node<T> *temp;

   temp = new node<T>;
   temp->data = item;
   temp->next = top;

   top = temp;

   length++;
}

template <class T>
T Stack<T> :: pop()
{
   if (isEmpty ())
      cout<<"STACK IS EMPTY";
   else 
   {
      node<T> *p;

      p = top;
      top = top->next;

      delete p;

      length--;
   }
   return top->data;  
}

template <class T>
T Stack<T> :: getTop ()
{
  return top->data;   
}
