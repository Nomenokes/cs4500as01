#pragma once

#include "object.h"

class Array : public Object {
    public:
    
    // Appends val to the end of the array.
    // Gives array control of val, do not use after calling.
    void append(Object* val);
    
    // Appends every element of vals to the end of the array.
    // Gives array control of vals, do not use after calling.
    // If vals is null, does nothing.
    void append_all(Array* vals);
    
    // Inserts val at index, so that array.get(index) will return val.
    // Pushes all elements after index down by 1.
    // Gives array control of val, do not use after calling.
    // If index is >= size(), is equivalent to calling append(val).
    void insert(Object* val, size_t index);
    
    // Inserts every element of vals into the array.
    // Pushes all elements after index down by the length of the array.
    // Gives array control of vals, do not use after calling.
    // If vals is null, does nothing.
    // If index is >= size(), is equivalent to calling append_all(vals).
    void insert_all(Array* vals, size_t index);
    
    // Sets the element at index to val. Returns the value previously at index.
    // Caller should give up control of val and gain control of the return value.
    // If index == size(), appends to the end of the array and returns NULL.
    // If index is > size(), does nothing and returns NULL. In this case,
    //   caller should retain control of val.
    Object* set(Object* val, size_t index);
    
    // Gets the element at index.
    // Does NOT give control of return value. Caller should not mutate return value
    //   (as if it is const).
    // If index is >= size(), does nothing and returns NULL.
    Object* get(size_t index);
    
    // Removes the element at index.
    // Pulls all elements after index up by 1.
    // Caller gains control of return value.
    // If index is >= size(), does nothing and returns NULL.
    Object* remove(size_t index);
    
    // Removes the elements from start to end and returns a 
    //    new Array containing the elements. 
    //    Start is inclusive, end is exclusive
    // Pulls all elements after start up by (end - start).
    // Caller gains control of return value.
    // If end <= start, does nothing and returns NULL.
    // Else if start >= size(), does nothing and returns NULL.
    // Else if end > size(), acts as if end == size().
    Array* remove_range(size_t start, size_t end);
    
    // Returns if this array contains obj, using obj->equals().
    // If obj is null, uses == .
    bool contains(Object* obj);
    
    // Returns the first index of obj, using obj->equals().
    // If obj is null, uses == .
    // If obj does not exist in the array, 
    //    returns a value greater than size().
    size_t index_of(Object* obj);
    
    // Clears all the elements in this array, 'delete' ing them.
    void clear();
    
    // Returns the number of elements in this array. 
    size_t size();
};
