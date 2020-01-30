#pragma once

#include "object.h"

class String : public Object {
    public:
    
    // returns the size of this string
    size_t size();
    
    // Returns a char buffer containing the characters of this string
    // Caller should not modify return, as if it is const
    char* to_char_array();
    
    // Compares this string to another string,
    // returns <0 if this is less than the other,
    //    =0 if they are equal, and >0 if this is greater.
    int compare_to(String* other);
    
    // Same as compare_to
    int cmp(const String* other);
    
    // Same as compare_to
    int compare(String* other);
    
    // Returns a new object
    String* concat(String* other);
};
