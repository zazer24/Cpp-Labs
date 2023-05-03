// FILE: database.cpp
// Authors: James Dameris and Zach Azer
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
/* Function: constructor
 * Description: Creates a database object with no used entries and sets the initial size of the dynamic array
*/ 
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
/* Function: copy constructor
 * Description: creates the copy constructor for the database class
*/ 
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);
        used_slots = src.used_slots;
        aloc_slots = used_slots + 1;
        company_array = new company[aloc_slots];
        *this = src;
    }
    
/* Function: assignment operator
 * Description: sets the assignment operator for the database class
*/ 
    database& database::operator= (const database &rhs) {
        std::cout << "copying elements of database...";
        used_slots = rhs.used_slots;
        reserve(used_slots + 1);
        std::copy(rhs.company_array,rhs.company_array + rhs.used_slots, company_array);
        return *this;
    }
    
/* Function: destructor
 * Description: clears the dynamic array
*/ 
    database::~database() {
        delete [] company_array;
    }
/* Function: reserve
 * Description: sets the capacity to the new capacity
 * Runtime: O(1)
*/     
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        
        company* tmp = new company[new_capacity];
        std::copy(company_array,company_array + used_slots, tmp);
        delete [] company_array;
        company_array = tmp;
        aloc_slots = new_capacity;
    }
/* Function: Insert company
 * Description: Inserts a new company to the list
 * Runtime: O(n)
*/    
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }
        if (used_slots == aloc_slots) {
            reserve(aloc_slots * 2);
        }
        company* init = new company(entry);
        company_array[used_slots] = *init;
        ++used_slots;
        return true;
    }
/* Function: insert item
 * Description: adds a new product to the list pertaining to a specific company
 * Runtime: O(n)
*/ 
    
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);
        size_type pos = search_company(company);
        if (pos == COMPANY_NOT_FOUND) {
            return false;
        }
        company_array[pos].insert(product_name, price);
        return true;
    }
/* Function: erase company
 * Description: removes a company and its products from the database
 * Runtime: O(n)
*/ 
    
    bool database::erase_company(const std::string &company) {
        
        size_type company_index = search_company(company);
        if (company_index == COMPANY_NOT_FOUND) {
            return false;
        }
        for (int i = company_index; i < used_slots - 1; ++i) {
            company_array[i] = company_array[i + 1];
        }
        --used_slots;
        return true;
    }
/* Function: erase item
 * Description: erases a product from the database
 * Runtime: O(n)
*/ 
    
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);
        size_type company_index = search_company(cName);
        return company_array[company_index].erase(pName);
    }
/* Function: search company
 * Description: searches for a company in the database
 * Runtime: O(n)
*/ 
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);

        for (int i = 0; i < used_slots; ++i) {
            if (company_array[i].get_name() == company) {
                return i;
            }
        }
        return COMPANY_NOT_FOUND;
    }
/* Function: print items by company
 * Description: prints out all of the items corresponding to a specified company
 * Runtime: O(n)
*/     
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
/* Function: print companies
 * Description: prints a list of companies in the database
 * Runtime: O(n)
*/ 
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
