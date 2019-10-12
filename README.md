# Sequence
Description of Doubly-Linked List Implementation

The Nodes in my doubly linked list have an int value, a pointer prev, and a pointer next. My list has a head that points to the first Node in the sequence and a tail that points to the last Node in the sequence. The first prev pointer of the first Node is a nullptr and the next pointer of my last Node is a nullptr (ie. the list is not circular and I do not have a dummy node). An empty sequence, has head as a nullptr and tail as a nullptr. A sequence with one Node has both head and tail pointing to the same Node, and the prev and next pointer of the Node are both nullptrs.



PsuedoCode

Sequence(const Sequence& other) //copy constructor
if other is not empty
	calls addToEmpty with the value that the other Sequence head points to
	sets counter to 1
	repeatedly...
		get value of other Sequence at counter value
			call addToRear with value
			increase counter
	set size equal to other sequence size
else (other is empty)
	set head to nullptr
	set tail to nulptr
	set size to 0

Sequence& operator=(const Sequence& other) //assignment operator
if the sequences are not the same (alias check)
	call copy constructor for temp sequence with other sequence
	call swap with temp Sequence
return reference to Sequence

~Sequence() //destructor
create p pointer that points to first Node
repeatedly...
	target pointer n to the next Node in list
	delete Node that  p points to
	set p to n (p points to next Node)
	break when reach end of Sequence

Sequence::insert(int pos, const ItemType& value)
if position is smaller than 0 or larger than size
	return -1
else if list is empty and position is 0
	call addToEmpty with value
	return 0
else if list is not empty and position is 0
	call addToFront with value
	return 0
else if the position value  is the same as the size
	call addToRear with value
	return position
create p pointer that points to first Node
repeatedly... (loop through list)
	if position value matches the counter value
			create new Node
			set its value to arg value
			target next pointer to p
            	target prev pointer of n to prev pointer of p
			target next pointer of prev Node to n
            	target prev of p to n
			increase size
           		return counter (break)
	else target p to next Node
			target p to next Node
			increase counter
return -1 (nothing could be inserted)

Sequence::insert(const ItemType& value)
if list is empty
	call addToEmpty with value
	return 0
else if the value is less than the first Node value
	call addToFront with value
	return 0
repeatedly... (loop through list)
	if position value is less than the value of the Node pointed to by p
			create new Node
			set its value to arg value
			target next pointer to the Node pointed to by p
            	target prev pointer of n to prev pointer of the Node pointed to by p
			target next pointer of prev Node to n
            	target prev of the Node pointed to by p to n
			increase size
           		return counter (break)
	else target p to next Node
			target p to next Node
			increase counter
call addToRear with value
return counter

Sequence::erase(int pos)
if the list is empty or the position is equal to or greater than size
	return false
else if the position is equal to 0 and the size is greater than 1
	create d pointer that points to first Node
	target d to point to next element
	target head to point to  next pointer of the Node pointed to by d
	targeting prev of next element to nullptr b/c soon first element
	delete Node pointed to by d
	decrease size
	return true
else if position value equals the size minus 1
	create d pointer that points to first Node
	target d to point to last element
	targeting tail at node before last element
	setting the next pointer of the previous element to nullptr
	delete Node pointed to by d
	decrease size
	return true
to test if position is in the middle of the Sequence
create p pointer that points to first Node
loop through list until reach position
    	p points to element we want to erase
   	targets next of element before p to element after p
    	targets prev of element after to p to element before p
    	delete p
    	decrease size
   	return true

Sequence::remove(const ItemType& value)
create p pointer that points to first Node
set counter to 0
set numremoved to 0
repeatedly... (loop through list)
	if the value given equals the value of the Node at the current position
			set p to the next pointer of the Node pointed to by p
			call erase with counter
			increase numremoved
	else
			set p to the next pointer of the Node pointed to by p
			increase counter
return numremoved

Sequence::get(int pos, ItemType& value) const
if the list is empty or the position is equal to or greater than size
	return false
set counter to 0
create p pointer that points to first Node
loop through list until reach position
	set p to the next pointer of the Node pointed to by p
	increase counter
set value equal to the value of the Node at that position
return true

Sequence::set(int pos, const ItemType& value)
if the list is empty or the position is equal to or greater than size
	return false
create p pointer that points to first Node
loop through list until reach position
	set p to the next pointer of the Node pointed to by p
set the value of the Node at that position to the given value 
return true


Sequence::find(const ItemType& value) const
set counter to 0
create p pointer that points to first Node
loop through list
	if the value equals the value of the Node pointed to by p
			return counter (position)
	else
			set p to the next pointer of the Node pointed to by p
			increase counter
return -1 (no value found)


Sequence::swap(Sequence& other)
swap sizes with temp
swap the head poitners with temp
swap the tail pointers with temp

addToEmpty(const ItemType& value)
create new node
set its value to arg value
set next pointer to nullptr
set previous pointer to nullptr
set head to point to new Node
target tail to head which points to newly created Node
increase size

addToFront(const ItemType& value)
create new node
set its value to arg value
set next pointer to head, which points to original first Node
set previous pointer to nullptr
set original head prev to n
target head to new Node
increase size

addToRear(const ItemType& value)
create new node
set its value to arg value
set its next pointer to the nullptr
set its prev pointer to tail (which points to the last Node)
set next of prev pointer to new Node
set tail to put to n, now that it's the last element
increase size

subsequence(const Sequence& seq1, const Sequence& seq2)
set testSize equal to 0
set counter to 0
if seq2 or seq2 is empty, or if seq2 is larger than seq1
        return -1
get first value in seq2
loop through seq1
	get value of seq1 at each position
	if that value equals the initial value of seq2
			loop through seq 2
				get value of seq2 at next value
				get value of seq1 at next value
				if the values are the same
					increase counter
					increase testSize
				else
					break (b/c seq2 is not a subsequence at that position)
	if the testSize is equal to the size of seq2
			return i (position in seq1, where the intial value of seq2 is)
	reset counter, because we want  find next value that matches initial in seq1
	reset testSize
return -1 if subsequence not found

interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);
create empty sequence temp_r
if seq1 is empty
	fill temp_r with seq2 elements
if seq2 is empty
	fill temp_r with seq1 elements
if neither is empty
	repeatedly...
		get seq1 value and insert into temp_r
		increase counter for temp_r
		get seq2 value and insert into temp_r
		increase counter for temp_r
		break when get to end of smaller sequence
	if one sequence is longer than the other
		insert the rest of values from that sequence into temp_r
swap result with temp_r

    


Test Cases:
//tested with unsigned longs
#include <iostream>
#include <cassert>
#include "Sequence.h"

using namespace std;

void test_interleave()
{
    ItemType x;
    Sequence s;
    Sequence t;
    Sequence v;
    
    interleave(s,t,v);                  //test with all empty functions
    assert(v.empty());
    
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    s.insert(7);
    s.insert(8);
    
    interleave(s,s,v);                  //test with alias (seq1 and seq2)
    assert(v.size() == 16);
    assert(v.get(0,x) && x == 1);
    assert(v.get(1,x) && x == 1);
    assert(v.get(14,x) && x == 8);
    assert(v.get(15,x) && x == 8);
    
    interleave(s,t,v);                  //test with seq1 empty
    interleave(t,s,v);                  //test with seq2 empty
    
    t.insert(21);
    t.insert(22);
    t.insert(23);
    t.insert(24);
    t.insert(25);
    
    interleave(s,t,v);                  //normal interleave test
    assert(v.size() == 13);
    assert(v.get(0,x) && x == 1);       //check that the first element is from seq1
    assert(v.get(1,x) && x == 21);      //check that the second element is from seq2
    assert(v.get(11,x) && x == 7);      //check that the rest of seq1 fills in the sequence
    assert(v.get(12,x) && x == 8);
    
    interleave(s,t,t);                  //test with non-empty result and alias (seq2 and result)
    assert(v.size() == 13);
    assert(v.get(0,x) && x == 1);       //check that the first element is from seq1
    assert(v.get(1,x) && x == 21);      //check that the second element is from seq2
    assert(v.get(11,x) && x == 7);      //check that the rest of seq1 fills in the sequence
    assert(v.get(12,x) && x == 8);
               
               
}

void test_subseq1()
{
    Sequence s;
    Sequence t;
    Sequence v;
    
    s.insert(0,30);
    s.insert(1,21);
    s.insert(2,63);
    s.insert(3,42);
    s.insert(4,17);
    s.insert(5,63);
    s.insert(6,17);
    s.insert(7,29);
    s.insert(8,8);
    s.insert(9,32);
    
    t.insert(0,63);
    t.insert(1,17);
    t.insert(2,29);
    
    v.insert(0,17);
    v.insert(1,63);
    v.insert(2,29);

    assert(subsequence(s,t) == 5);
    assert(subsequence(v,t) == -1);
    
}

void test_subseq2()
{
    Sequence s;
    Sequence t;
    Sequence v;
    
    assert(subsequence(s,t) == -1);     //subsequences are empty
    
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    s.insert(7);
    s.insert(8);
    s.insert(9);
    
    assert(subsequence(s,t) == -1);     //sequence 2 is empty
    assert(subsequence(v,s) == -1);     //sequence 1 is empty
    
    t.insert(1);
    t.insert(2);
    t.insert(3);
    
    assert(subsequence(s,t) == 0);
    
}

void test()
{
    // default constructor
    Sequence s;
    unsigned long x;
    // For an empty sequence:
    assert(s.size() == 0);              // test size
    assert(s.empty());                  // test empty
    assert(!s.erase(0));                //nothing to erase
    assert(s.remove(2) == 0);           // nothing to remove
    assert(s.insert(10) == 0);          //test insert element to empty list
    assert(s.remove(10) == 1);          //removes 1st element
    assert(s.size() == 0);              //test size
    assert(s.empty());                  //test empty
    assert(s.insert(0,10) == 0);        //insert with position into empty list
    
    assert(s.insert(11) == 1);          //test insert 2nd and last element
    
    assert(s.insert(2) == 0);           //test insert new first element
    assert(s.insert(8) == 1);           //test insert element between two elements
    assert(s.insert(12) == 4);          //test insert last element, now at position 4
    assert(!s.empty());                 //test empty

    assert(s.insert(0,3) == 0);         //tests insert w/ position for first element
    assert(s.get(0,x) && x == 3);
    assert(s.insert(1,5) == 1);         //tests insert w/ position for middle element
    assert(s.get(1,x) && x == 5);
    assert(s.get(0,x) && x == 3);
    assert(s.get(2,x) && x == 2);
    assert(s.insert(10,3) == -1);       //tests that it won't add if position is larger than the size
    assert(s.insert(-1,3) == -1);       //won't accept negative values
    assert(s.size() == 7);              //test insert increases size
    
    assert(!s.erase(7));                //test erase (doesn't erase if pos out of range)
    assert(s.erase(6));                 //test erase for last element
    assert(!s.get(6,x) && x == 2);      //test get: if postion inputed to get >= size, x remains unchanged and get returns false
    assert(s.get(5,x) && x == 11);
    assert(s.find(11) == 5);            //test find
    assert(s.find(12) == -1);           //test find (value 12 should not exist)
    assert(s.erase(0));                 //test erase for first element
    assert(s.find(3) == -1);
    assert(s.get(0,x) && x == 5);
    assert(s.erase(2));                 //test erase for middle element
    assert(s.find(8) == -1);
    assert(s.get(2,x) && x == 10);
    assert(s.size() == 4);              //test that erase decreases size
    assert(!s.erase(-1));               //won't accept negative values
    s.insert(4,13);                     //test insert last element
    assert(s.get(4,x) && x == 13);
    s.insert(5,10);
    assert(s.remove(10) == 2);          //test remove (more than one item)
    assert(s.find(10) == -1);
    assert(s.get(2,x)&& x == 11);
    assert(s.size() == 4);
    assert(s.remove(13) == 1);          //test remove (one item)
    assert(s.remove(60) == 0);          //test remove (when no value exists)
    assert(s.size() == 3);
    assert(s.set(0,1));                 //test set
    assert(s.get(0,x) && x == 1);
    
    Sequence t;
    t.insert(4);
    t.insert(5);
    t.insert(6);
    t.insert(7);
    
    s.swap(t);                          //test swap
    assert(t.size() == 3);
    assert(t.get(0,x) && x == 1);
    assert(s.size() == 4);
    assert(s.get(0,x) && x == 4);
    
    Sequence q = s;                     //test copy constructor
    assert(q.size() == 4);
    assert(q.get(0,x) && x == 4);
    assert(q.get(1,x) && x == 5);
    assert(q.get(2,x) && x == 6);
    assert(q.get(3,x) && x == 7);
    
    t = q;                              //test assignment operator
    assert(t.size() == 4);
    assert(t.get(0,x) && x == 4);
    assert(t.get(1,x) && x == 5);
    assert(t.get(2,x) && x == 6);
    assert(t.get(3,x) && x == 7);
}

int main()
{
    test_interleave();
    cout << "Passed all tests" << endl;
}



