#pragma once

class Object {
    public:
    
    // returns if this object equals the other object
    // other can be NULL, in which case return false
    virtual bool equals (const Object* other);
    
    // Hashes this object. Must be the same if equal.
    virtual size_t hash();
};
