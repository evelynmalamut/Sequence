//
//  Sequence.cpp
//  Project_2
//
//  Created by Evelyn Malamut on 4/18/19.
//  Copyright © 2019 Evelyn Malamut. All rights reserved.
//

#include "Sequence.h"

Sequence::Sequence() {
    head = nullptr; //sets head to nullptr (creating empty list)
    tail = nullptr; //sets tail to nullptr
    m_size = 0;
}

Sequence::Sequence(const Sequence& other) { //copy constructor
    if (!other.empty()) {
        addToEmpty(other.head->m_value); //add first node with value from first node of other Sequence
        int counter = 1;
        ItemType x;
        while (counter < other.m_size) { //loop through nodes
                other.get(counter,x); //get value of other Node at position counter
                addToRear(x); //use value to create a new node at the end of the list with value of other
                counter ++;
        }
        m_size = other.m_size;
    }
    else {
        head = nullptr; //sets head to nullptr (creating empty list)
        tail = nullptr; //sets tail to nullptr
        m_size = 0;
    }
}

Sequence& Sequence::operator=(const Sequence &other) { //assignment operator
    if (this != &other) {
        Sequence temp(other);
        swap(temp);
    }
    return *this;
}

Sequence::~Sequence() { //deletes Nodes one at a time in order from first to last
    Node *p;
    p = head;
    while (p != nullptr) { //loop through nodes
        Node *n = p->next; //target n to Node after p
        delete p; //deleting node where p points
        //note: delete gets rid of Node not pointer
        p = n; //target p to n, which points to next Node
    }
}

bool Sequence::empty() const {
    if (head == nullptr && m_size == 0) { //checking that head is the nullptr (ie points to nothing --> list is empty)
        return true;
    }
    return false;
}

int Sequence::size() const {
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value) {
    if (0 > pos && pos > m_size) {
        return -1;
    }
    else if (pos == 0 && head == nullptr) { //if list is empty
        addToEmpty(value); //call private member function to add Node to empty Sequence
        return 0; //return pos, which is 0
    }
    else if (pos == 0 && head != nullptr) { //if pos is 0, but head doesn't point to nullptr (ie list is not empty)
        addToFront(value); //call private member function to add Node to front
        return 0; //return pos, which is 0
    }
    else if (pos == m_size) {
        addToRear(value); //call private member function to add Node to end
        return pos; //return pos, which should be m_size - 1
    }
    Node *p;
    p = head;
    int counter = 0;
    while (p != nullptr) { //loop through nodes
        if (pos == counter) { //if at the right position in the linked list
            Node *n = new Node; //create new node
            n->m_value = value; //set it's value to arg value
            n->next = p; //target next pointer to p
            n->prev = p->prev; //target prev pointer of n to prev pointer of p
            p->prev->next = n; //target next pointer of prev Node to n
            p->prev = n; //target prev of p to n
            m_size ++; //increase size
            return counter;
        }
        p = p->next; //target p to next Node
        counter ++; //increase counter
    }
    return -1;
}

int Sequence::insert(const ItemType& value) {
    if (empty()) { //if list is empty
        addToEmpty(value); //call private member function to add Node to empty Sequence
        return 0; //return pos, which is 0
    }
    else if (value <= head->m_value) { //if the value is less than the first Node
        addToFront(value); //call private member function to add Node to front
        return 0; //return pos, which is 0
    }
    Node *p;
    p = head;
    int counter = 0;
    while (p != nullptr) { //loop through nodes
        if (value <= p->m_value) { //if value arg is less than the value of a node
            Node *n = new Node; //create new node
            n->m_value = value; //set it's value to arg value
            n->next = p; //target next pointer to p
            n->prev = p->prev; //target prev pointer of n to prev pointer of p
            p->prev->next = n; //target next pointer of prev Node to n
            p->prev = n; //target prev of p to n
            m_size ++; //increase size
            return counter; //return pos
        }
        p = p->next; //target p to next Node
        counter ++;
    }
    addToRear(value); //call private member function to add Node to end
    return counter; //return pos (which should be m_size - 1)
}

bool Sequence::erase(int pos) {
    if (pos < 0 || pos >= m_size || empty()) //if list is empty or pos is equal to or greater than size
        return false;
    else if (pos == 0 && m_size > 1) { //deleting first Node
        Node *d;
        d = head; //targeting d to point to first element
        head = d->next; //targeting head to point to next element
        d->next->prev = nullptr; //targeting prev of next element to nullptr b/c soon first element
        delete d; //deleting the Node that d points to
        m_size --;
        return true;
    }
    else if (pos == 0 && m_size == 1) { //deleting only element in list
        delete head; //deleting the Node that head points to
        head = nullptr; //setting head to nullptr b/c empty
        tail = nullptr; //setting tail to nullptr b/c empty
        m_size --;
        return true;
    }
    else if (pos == m_size - 1) { //if Node is last element
        Node *d;
        d = tail; //targeting d to point to last element
        tail = d->prev; //targeting tail at node before last element
        d->prev->next = nullptr; //setting the next of the element before it to the nullptr
        delete d;
        m_size --;
        return true;
    }
    //to test if position is in the middle of the Sequence
    int counter = 0;
    Node *p;
    p = head;
    while (p->next != nullptr && counter < pos) { //loop should terminate with p pointing to the element at pos or the last element
        p = p->next; //target p to next Node
        counter ++;
    }
    //p points to element we want to erase
    p->prev->next = p->next; //targets next of element before p to element after p
    p->next->prev = p->prev; //targets prev of element after to p to element before p
    delete p;
    m_size --;
    return true;
}

int Sequence::remove(const ItemType& value)
{
    int num_removed = 0;
    Node *p;
    p = head;
    int counter = 0;
    while (p != nullptr) { //loop through nodes
        if (value == p->m_value) { //if value arg = the value of a node in Sequence
            p = p->next; //before erase, so that p doesn't point to nothing
            erase(counter);
            num_removed ++;
        }
        else {
            p = p->next; //target p to next Node
            counter ++;
        }
    }
    return num_removed;
}

bool Sequence::get(int pos, ItemType& value) const {
    if (pos < 0 || pos >= m_size || empty()) //if list is empty or pos is equal to or greater than size
        return false;
    int counter = 0;
    Node *p;
    p = head;
    while (p->next != nullptr && counter < pos) { //loop should terminate with p pointing to the element at pos or the last element
        p = p->next; //target p to next Node
        counter++;
    }
    value = p->m_value;
    return true;
}

bool Sequence::set(int pos, const ItemType& value) {
    if (pos < 0 || pos >= m_size || empty()) //if list is empty or pos is equal to or greater than size
        return false;
    int counter = 0;
    Node *p;
    p = head;
    while (p->next != nullptr && counter < pos) { //loop should terminate with p pointing to the element at pos or the last element
        p = p->next; //target p to next Node
        counter++;
    }
    p->m_value = value;
    return true;
}

int Sequence::find(const ItemType& value) const {
    int counter = 0;
    Node *p;
    p = head;
    while (p != nullptr) { //loop through nodes
        if (value == p->m_value) { //if value arg is equal to the value of a node
            return counter; //return pos
        }
        p = p->next; //target p to next Node
        counter ++;
    }
    return -1; //no value found
}

void Sequence::swap(Sequence& other) {
    int temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
    
    Node *temp_head = head;
    head = other.head;
    other.head = temp_head;
    
    Node *temp_tail = tail;
    tail = other.tail;
    other.tail = temp_tail;
}
    
void  Sequence::addToEmpty(const ItemType& value) {
    Node *n = new Node; //create new node
    n->m_value = value; //set its value to arg value
    n->next = nullptr; //set next pointer to nullptr
    n->prev = nullptr; //set previous pointer to nullptr
    head = n; //set head to point to new Node
    tail = n; //target tail to head which points to newly created Node
    m_size ++; //increase size
}

void Sequence::addToFront(const ItemType& value) {
    Node *n = new Node; //create new node
    n->m_value = value; //set its value to arg value
    n->next = head; //set next pointer to head, which points to original first Node
    n->prev = nullptr; //set previous pointer to nullptr
    head->prev = n; //set original head prev to n
    head = n; //target head to new Node
    m_size ++; //increase size
}

void  Sequence::addToRear(const ItemType& value) {
    Node *n = new Node; //create new node
    n->m_value = value; //set its value to arg value
    n->next = nullptr; //set its next pointer to the nullptr
    n->prev = tail; //set its prev pointer to tail (which points to the last Node)
    tail->next = n; //set next of prev pointer to new Node
    tail = n; //set tail to put to n, now that it's the last element
    m_size ++; //increase size
}

int subsequence(const Sequence& seq1, const Sequence& seq2) {
    ItemType x;
    ItemType y;
    int counter = 0;
    int testSize = 0;
    
    if (seq1.empty() || seq2.empty() || seq1.size() < seq2.size()) //check if seq2 or seq2 is empty, or if seq2 is larger than seq1
        return -1;

    seq2.get(0,x); //get first value in smaller sequence
    ItemType initial = x; //set initial to that value
    
    for (int i = 0; i < seq1.size(); i++) { //loop through seq1
        seq1.get(i,y); //get value in seq1 at the counter value
        if (y == initial) { //if that value equals the initial value
            while (counter < seq2.size()) { //loop through seq2
                seq2.get(counter,x); //get value of seq2 at next value value
                seq1.get(i + counter, y); //get value of seq1 at the next value
                if  (y == x) { //if equal (next value in seq1 should match the next value in the subsequence)
                    testSize++; //increase testsize
                    counter++; //increase counter
                }
                else {
                    break; //break out of loop if values are not equal (ie. full subsequence is not present)
                }
            }
        }
        if (testSize == seq2.size()) { //if the test size is the same as the size as seq2, then the whole subsequence exists in seq1, so we return the position in seq1 where the subsequence started
            return i;
        }
        counter = 0; //reset counter (want to start over looping through subsequence, when we find next value that matches initial)
        testSize = 0; //reset testSize
    }
    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
    ItemType x;
    ItemType y;
    ItemType e;
    Sequence small;
    Sequence large;
    Sequence temp_r;
    int counter = 0;

    if(seq1.empty() && !seq2.empty()) { //if seq 1 is empty, replace result values with seq2 values
        for(int i = 0; i < seq2.size(); i++) {
            seq2.get(i,x);
            temp_r.insert(i, x);
        }
    }
    else if(seq2.empty() && !seq1.empty()) { //if seq 2 is empty, replace result values with seq1 values
        for(int i = 0; i < seq1.size(); i++) {
            seq1.get(i,x);
            temp_r.insert(i, x);
        }
    }
    else if (!seq1.empty() && !seq2.empty() ) {
        if (seq1.size() > seq2.size()) { //set smaller sequence to small and larger sequence to large
            small = seq2;
            large = seq1;
        }
        else {
            small = seq1;
            large = seq2;
        }
        
        for(int i = 0; i < small.size(); i++) { //loop through smaller sequence
            seq1.get(i,y); //get value of y from seq1 at postion i
            seq2.get(i,x); //get value of x from seq2 at postion i
            temp_r.insert(counter, y); //insert y from seq1
            counter ++; //increase counter (so that seq2 value is inserted in the next position
            temp_r.insert(counter, x); //insert x from seq2
            counter ++; //increase counter
        }
        
        if (small.size() != large.size()) { //if sequences are not the same size, add to the end of result
            for(int i = small.size(); i < large.size(); i++) { //starting from where small seq ended, loop through larger seq
                large.get(i,e); //get value of at i from larger sequence
                temp_r.insert(counter, e);//insert e from larger sequence
                counter ++; //increase counter
            }
        }
    }
    result.swap(temp_r); //swap result with temp_r
} //small, large, and temp are destructed
    
