//
//  LinkedList.cpp
//  Lab 02
//
//  Created by Zac Clark on 3/7/16.
//  Copyright © 2016 Zac Clark. All rights reserved.
//

#include <stdio.h>
#include "LinkedListInterface.h"
#include <stdexcept>
#include <iostream>

using namespace std;

template<typename T>

class LinkedList : public LinkedListInterface<T>
{
public:
    LinkedList<T>()
    {
        Head = NULL;
    }
    ~LinkedList<T>()
    {
        clear();
    }

    void insertHead(T value)
    {
        cout << "Ran insertHead()" << endl;
        cout << "Value: " << value << endl;
        //check against duplicate values
        if (duplicate(value))
            return;
        
        if (Head != NULL)
        {
            Temp = Head;
            Head = new Node(value);
            Head->next = Temp;
            Temp = NULL;
        }
        else
            Head = new Node(value);
        count ++;
    }

    void insertTail(T value)
    {
        cout << "Ran insertTail()" << endl;
        cout << "Value: " << value << endl;
        //check against duplicate values
        if (duplicate(value))
            return;
        
        if (Head == NULL)
            Head = new Node(value);
        else
        {
            Temp = Head;
            while (Temp->next!= NULL)
                Temp = Temp->next;
            Node* newNode = new Node(value);
            Temp->next = newNode;
            newNode->next = NULL;
        }
        count ++;
    }

    void insertAfter(T value, T insertionNode)
    {
        cout << "Ran insertAfter()" << endl;
        cout << "Value: " << value << " After value: " << insertionNode << endl;
        //check against duplicate values
        if (duplicate(value))
            return;
        //check to make sure value exists
        bool exists = false;
        Temp = Head;
        while (Temp != NULL)
        {
            if (Temp->value == insertionNode)
                exists = true;
            Temp = Temp->next;
        }
        //if doesn't exist, return out of function
        if (exists == false)
            return;
        
        Temp = Head;
        while (Temp != NULL)
        {
            if (Temp->value == insertionNode)
            {
                Node* newNode = new Node(value);
                newNode->next = Temp->next;
                Temp->next = newNode;
                count ++;
                return;
            }
            else
                Temp = Temp->next;
        }
    }

    void remove(T value)
    {
        cout << "Ran remove()" << endl;
        //if head
        if (Head->value == value)
        {
            cout << "Removed Head with value: " << value << endl;
            Node* Current = Head;
            Head = Head->next;
            delete Current;
            count --;
            return;
        }
        Temp = Head;
        //if in body
        while (Temp->next != NULL)
        {
            if (Temp->next->value == value)
            {
                cout << "Value Removed: " << Temp->next->value << endl;
                Node* Current = Temp->next;
                Temp->next = Temp->next->next;
                delete Current;
                Temp = NULL;
                count--;
                return;
            }
            else
                Temp = Temp->next;
        }
    }

    void clear()
    {
        cout << "Ran clear()" << endl;
        if (count == 0)
            return;
        
        Temp = Head;
        Node* Current = Head;
        while (Temp->next != NULL)
        {
            Current = Temp->next;
            remove(Temp->value);
            Temp = Current;
        }
        //run it one more time just for kicks;)
        Current = Temp->next;
        remove(Temp->value);
        Temp = Current;
        
        Temp = NULL;
        Current = NULL;
        count = 0;
    }

    T at(int index)
    {
        cout << "Ran at()" << endl;
        
        if (index < 0 || index > (count-1))
            throw "out of range";
        
        Temp = Head;
        for (int i = 0; i < index; i++)
        {
            Temp = Temp->next;
        }
        return Temp->value;
    }

    int size()
    {
        cout << "Ran size()" << endl;
        return count;
    }
    
    bool duplicate(T value)
    {
        if (Head == NULL)
            return false;
        Temp = Head;
        while (Temp->next != NULL)
        {
            if (Temp->value == value)
                return true;
            else
                Temp = Temp->next;
        }
        //test to see if at tail
        if (Temp->value == value)
            return true;
        
        return false;
    }
private:

    struct Node
    {
        T value;
        Node* next;
        
        Node (const T& data_item, Node* next_ptr = NULL) : value(data_item), next(next_ptr){}
    };
    Node* Head;
    Node* Temp;
    int count = 0;
    
};