// FILE: company.cpp
// Authors: James Dameris and Zach Azer
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
/* Function: constructor
 * Description: initializes a company object with an empty name
*/ 
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
/* Function: constructor
 * Description: initializes a company object with an inputted name
*/ 
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);
        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
/* Function: copy constructor
 * Description: creates the copy constructor for the company class
*/ 
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
        *this = src;
    }
/* Function: assignment operator
 * Description: creates the assignment operator for the company class
*/ 
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);
        if (this == &src) {
            return *this;
        }
        list_clear(head_ptr);
        this->company_name = src.company_name;
        list_copy(src.head_ptr, head_ptr, tail_ptr);
        return *this;
    }
/* Function: destructor
 * Description: clears the list and its memory
*/ 
    company::~company() {
        list_clear(head_ptr);
    }
/* Function: get name
 * Description: returns the name of the company
*/ 
    std::string company::get_name() const {
        return company_name;
    }
/* Function: get head
 * Description: returns the constant version of the head of the linked list
*/ 
    const node *company::get_head() const {
        return head_ptr;
    }
/* Function: get tail
 * Description: returns the constant version of the tail of the linked list
*/ 
    const node *company::get_tail() const {
        return tail_ptr;
    }
/* Function: get head
 * Description: returns the non constant version of the head of the linked list
*/ 
    node* company::get_head() {
        return head_ptr;
    }
/* Function: get tail
 * Description: returns the non constant version of the tail of the linked list
*/ 
    node* company::get_tail() {
        return tail_ptr;
    }
/* Function: print items
 * Description: prints the list
*/ 
    void company::print_items() {
        list_print(head_ptr);
    }
/* Function: insert
 * Description: creates and inserts a new node to the back of the list
 * Runtime: O(1)
*/ 
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) {
            node* insert_ptr = new node(product_name, price, NULL);
    	    head_ptr = tail_ptr = insert_ptr;
        }
        else {
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }
/* Function: erase
 * Description: erases a product matching the given name
 * Runtime: O(n)
*/ 
    
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);
        node* target = list_search(head_ptr, product_name);
        node* cursor = head_ptr;
        if (target != NULL) {
            while (cursor != target) {
                if (cursor->getLink() == target) {
                    break;
                }
                cursor = cursor->getLink();
            }
            cursor->setLink(target->getLink());
            delete target;
            return true;
        }
        else {
            return false;
        }
    }
    
    
}
