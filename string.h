#pragma once

#include "object.h"

class String : public Object {
    public:
    size_t size();
    char* to_char_array();
    int compare_to(String* other);
};
