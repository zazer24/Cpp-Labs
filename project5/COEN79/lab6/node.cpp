// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

	void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr) { 
		// copies a piece of the list given by start_ptr and (not including) end_ptr and gives them to a new head and tail pointer
		list_clear(head_ptr);
		node* cursor;
		if (start_ptr == NULL && end_ptr == NULL) {
			head_ptr = NULL;
			tail_ptr = NULL;
			return;
		}
		if (start_ptr == end_ptr) {
			return;
		}
		list_head_insert(head_ptr,start_ptr->data());
		tail_ptr = head_ptr;
		
		cursor = start_ptr->link();
		for (cursor; cursor != end_ptr && cursor != NULL; cursor = cursor->link()) {
			list_insert(tail_ptr,cursor->data());
			tail_ptr = tail_ptr->link();
		}
	}
	
    size_t list_occurrences(node* head_ptr, const node::value_type& target) { 
		// counts the number of occurrences of the target variable
    	const node *cursor;
		size_t count = 0;
		// loops to count the number of times target is found
    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( )){
    	    if (target == cursor->data( )){
        		count++;
			}
		}
    	return count;
	}
	
    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) { 
		// inserts a node with the given value before the given position on the linked list provided by head
		node* hold;
    	assert (position > 0 && position <= list_length(head_ptr)+1);
		if (position == 1) {
			list_head_insert(head_ptr, entry);
			return;
		}
		hold = list_locate(head_ptr, position - 1);
		list_insert(hold,entry);
	}
	
    node::value_type list_remove_at(node*& head_ptr, size_t position) { 
		// removes the node at the given position on the linked list provided by head
		node* hold;
		node::value_type dTemp;
		assert (0 < position && position <= list_length(head_ptr));
		if (position == 1) {
			hold = list_locate(head_ptr, position);
			dTemp = hold->data();
			list_head_remove(head_ptr);
			return dTemp;
		}
		hold = list_locate(head_ptr, position - 1);
		dTemp = hold->data();
		list_remove(hold);
		return dTemp;
	}
	
    node* list_copy_segment(node* head_ptr, size_t start, size_t finish) { 
		// uses list_piece but through usage of positions rather than start and finish nodes
		assert((1 <= start) && (start <= finish) && (finish <= list_length(head_ptr)));
	 	node* begin = list_locate(head_ptr,start);
		node* end = list_locate(head_ptr,finish+1);
		node* newBeg = new node();
		node* newEnd = new node();
		list_piece(begin, end, newBeg, newEnd);
		return newBeg;
	}
	
    void list_print (const node* head_ptr) { 
		// prints the data on the nodes in the list with proper formatting
		const node* cursor = head_ptr;
		for (cursor; cursor != NULL; cursor = cursor->link()) {
			cout << cursor->data();
			if (cursor->link() != NULL) {
				cout << ", ";
			}
		}
		cout << endl;
	}
	
    void list_remove_dups(node* head_ptr) { 
		// removes all duplicates in the list. 
		// Starts at the head and then compares the rest of the list 
		// to the head, then iterates to the next node in the list
		node* cursor = head_ptr;
		node* temp;
		for (head_ptr; head_ptr != NULL && head_ptr->link() != NULL; head_ptr = head_ptr->link()) {
			for (cursor = head_ptr->link(); cursor != NULL; cursor = cursor->link()) {
				if (head_ptr->data() == cursor->data()) {
					temp = cursor->link();
					delete cursor;
					head_ptr->set_link(temp);
				}
			}
		}
	}
	
    node* list_detect_loop (node* head_ptr) { 
		// f is fast runner, s is slow runner
		node* f = head_ptr;
		node* s = head_ptr;

		// both fast and slow runner go through the loop until they meet or fast is NULL
		// fast moves by 2 nodes and moves by 1
		while (f != NULL && f->link() != NULL) {
			s = s->link();
			f = f->link()->link();
			if (f == s) {
				break;
			}
		}
		// return if they don't meet
		if (f != s) {
			return NULL;
		}
		// loops for the loops beginning
		for (s = head_ptr, f; f != NULL; f = f->link(), s = s->link()) {
			if (s == f) {
				break;
			}
		}
		return f;
	}
	

    
    
}
