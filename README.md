
Array maintains an ordering of Objects. Objects passed to element-adding methods
(append, insert, set, etc.) should not be re-used by the caller.
"_all" functions will similarly hand control of the given arrays and their objects.

'remove' and 'set' return a pointer to the Object that was removed. 'remove_range' 
returns a new Array with pointers to the removed objects. When destroyed, the Array 
deletes all objects it is holding.
If you no longer need the object or objects being removed, the syntax is the same in 
both cases:

    delete array.remove(i);
    delete array.remove_range(start, end);
    

'contains' and 'index_of' use Object's 'equals' method to determine if two Objects are
equal. If the Object is not in the Array, 'index_of' returns a value > size().

Null values for arguments are supported.

All pointer values must be able to have 'delete' called on them. All pointer return values
that give control to the caller are able to be 'deleted'.
