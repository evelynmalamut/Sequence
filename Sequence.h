//
//  Sequence.hpp
//  Project_2
//
//  Created by Evelyn Malamut on 4/18/19.
//  Copyright © 2019 Evelyn Malamut. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h

#include <string>
using ItemType = std::string;

class Sequence
{
public:
    Sequence(); //constructor
    Sequence& operator=(const Sequence& other); //assignment operator
    Sequence(const Sequence& other); //copy constructor
    ~Sequence(); //destructor
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    
private:
    struct Node {
        ItemType m_value;
        Node *next;
        Node *prev;
    };
    Node *head;
    Node *tail;
    void  addToEmpty(const ItemType& value);
    void  addToFront(const ItemType& value);
    void  addToRear(const ItemType& value);
    int m_size;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);


#endif
