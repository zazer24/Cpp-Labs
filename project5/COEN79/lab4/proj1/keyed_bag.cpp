// AUTHOR: James Dameris
// FILE: keyed_bag.cpp
// CLASS IMPLEMENTED: keyed_bag (see keyed_bag.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include <string>
#include "keyed_bag.h"

using namespace std;

namespace coen79_lab4
{
    keyed_bag::keyed_bag() {
        size_type i;
        for (i = 0; i < CAPACITY; i++) {
            key[i] = '\0';
            data[i] = 0;
        }
        used = 0;
    }
    void keyed_bag::erase() {
        size_type i;
        for (i = 0; i < CAPACITY; i++) {
            key[i] = '\0';
            data[i] = 0;
        }
        used = 0;
    }
    bool keyed_bag::erase(const key_type& key) {
        size_type i;
        for (i = 0; i < used; i++) {
            if (key == this->key[i]) {
                this->key[i] = this->key[used-1];
                this->data[i] = this->data[used-1];
                used--;
                return true;
            }
        }
        return false;

    }
    void keyed_bag::insert(const value_type& entry, const key_type& key) {
        assert(has_key(key) == false && used < CAPACITY);
        data[used] = entry;
        this->key[used] = key;
        used++;
    }
    void keyed_bag::operator +=(const keyed_bag& addend) {
        assert(hasDuplicateKey(addend) == false && used + addend.used <= CAPACITY);
        size_type i, j, total;
        i = used;
        for (i, j = 0; j < addend.used; i++, j++) {
            data[i] = addend.data[j];
            key[i] = addend.key[j];
        }
        used = used + addend.used;

    }
    bool keyed_bag::has_key(const key_type& key) const {
        size_type i;
        for (i = 0; i < used; i++) {
            if (key == this->key[i]) {
                return true;
            }
        }
        return false;
    }
    keyed_bag::value_type keyed_bag::get(const key_type& key) const {
        assert(has_key(key) == true);
        size_type i;
        for (i = 0; i < used; i++) {
            if (key == this->key[i]) {
                return data[i];
            }
        }
    }
    keyed_bag::size_type keyed_bag::size( ) const {
        return used;
    }
    keyed_bag::size_type keyed_bag::count(const value_type& target) const {
        size_type i, occ;
        occ = 0;
        for (i = 0; i < used; i++) {
            if (target == data[i]) {
                occ++;
            }
        }
        return occ;
    }
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
        size_type i;
        for (i = 0; i < otherBag.used; i++) {
            if (has_key(otherBag.key[i])) {
                return true;
            }
        }
        return false;
    }

    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2) {
        keyed_bag b;
        b += b1;
        b += b2;
        return b;
    }
}