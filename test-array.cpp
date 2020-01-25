
#include "string.h"
#include "array.h"
#include "object.h"

void check(int num, bool thing){
    if(thing) printf("\033[0;32m[test %d succeeded]\033[0m\n", num);
    else printf("\033[0;31m[test %d failed]\033[0m\n", num);
}

//tests append, append_all, insert, insert_all 
//indirectly tests get, size
void testAdd (void) {
    Array* arr = new Array();
    arr->append(new String("hi"));
    check(5011, arr->get(0)->equals(new String("hi")));
    arr->append(NULL);
    check(5021, arr->get(0)->equals(new String("hi")));
    check(5022, arr->get(1) == NULL);
    
    
    Array* arr2 = new Array();
    arr2->append(new String("bar"));
    arr2->append(new String("sad"));
    check(5053, arr2->size() == 2);
    arr2->append_all(arr);
    check(5031, arr2->get(0)->equals(new String("bar")));
    check(5032, arr2->get(1)->equals(new String("sad")));
    check(5033, arr2->get(2)->equals(new String("hi")));
    check(5034, arr2->get(3) == NULL);
    check(5051, arr2->size() == 4);
    arr2->append_all(new Array());
    check(5041, arr2->get(0)->equals(new String("bar")));
    check(5042, arr2->get(1)->equals(new String("sad")));
    check(5043, arr2->get(2)->equals(new String("hi")));
    check(5044, arr2->get(3) == NULL);
    check(5052, arr2->size() == 4);
    
    
    Array* dup = new Array();
    dup->append(new String("bar"));
    dup->append(new String("sad"));
    dup->append(new String("hi"));
    dup->append(NULL);
    
    arr2->insert_all(dup, 2);
    check(5061, arr2->get(0)->equals(new String("bar")));
    check(5062, arr2->get(1)->equals(new String("sad")));
    check(5063, arr2->get(2)->equals(new String("bar")));
    check(5064, arr2->get(3)->equals(new String("sad")));
    check(5065, arr2->get(4)->equals(new String("hi")));
    check(5066, arr2->get(5) == NULL);
    check(5067, arr2->get(6)->equals(new String("hi")));
    check(5068, arr2->get(7) == NULL);
    check(5054, arr2->size() == 8);
    arr2->insert_all(new Array(), 5);
    check(5081, arr2->get(0)->equals(new String("bar")));
    check(5082, arr2->get(1)->equals(new String("sad")));
    check(5083, arr2->get(2)->equals(new String("bar")));
    check(5084, arr2->get(3)->equals(new String("sad")));
    check(5085, arr2->get(4)->equals(new String("hi")));
    check(5086, arr2->get(5) == NULL);
    check(5087, arr2->get(6)->equals(new String("hi")));
    check(5088, arr2->get(7) == NULL);
    check(5056, arr2->size() == 8);
    
    
    arr = new Array();
    arr->append(new String("hi"));
    arr->append(NULL);
    
    arr->insert(new String("bar"), 0);
    arr->insert(new String("baz"), 3);
    arr->insert(new String("bat"), 0);
    arr->insert(new String("end"), 10000);
    check(5071, arr->get(0)->equals(new String("hi")));
    check(5072, arr->get(1) == NULL);
    check(5073, arr->get(2)->equals(new String("bar")));
    check(5074, arr->get(3)->equals(new String("baz")));
    check(5075, arr->get(4)->equals(new String("bat")));
    check(5076, arr->get(5)->equals(new String("end")));
    check(5055, arr->size() == 6);
}

//tests set, remove, removeRange, clear
// indirectly tests append, get, size
void testRemove(void) {
    
    Array* arr = new Array();
    arr->append(new String("hi"));
    check(4011, arr->set(new String("foo"))->equals(new String("hi")), 0);
    check(4012, arr->get(0)->equals(new String("foo")));
    arr->append(NULL);
    check(4013, arr->set(new String("hi")) == NULL, 1);
    check(4014, arr->get(0)->equals(new String("foo")));
    check(4015, arr->get(1)->equals(new String("hi")));
    
    check(4021, arr->remove(0)->equals(new String("foo")));
    check(4022, arr->remove(0)->equals(new String("hi")));
    check(4023, arr->remove(0) == NULL);
    check(4024, arr->size() == 0);
    
    arr->append(new String("hi"));
    arr->append(new String("hi"));
    arr->append(new String("hi"));
    check(4031, arr->size() == 3);
    arr->clear();
    check(4032, arr->size() == 0);
    arr->append(new String("hi"));
    arr->append(new String("foo"));
    arr->append(new String("bar"));
    check(4033, arr->size() == 3);
    arr->removeRange(0, 2);
    check(4034, arr->get(0)->equals(new String("bar")));
    check(4035, arr->size() == 1);
}

//tests get, contains, indexOf, size, equals
//indirectly tests remove, append
void testQueries(void) {
    
    Array* arr = new Array();
    Array* arr2 = new Array();
    check(3011, arr->equals(arr2));
    arr->append(new String("hi"));
    arr->clear();
    check(3012, arr->equals(arr2);
    arr->append(new String("hi"));
    arr2->append(new String("hi"));
    check(3013, arr2->equals(arr);
    check(3014, arr->equals(arr2);
    
    arr->append(NULL);
    check(3040, arr->size() == 2);
    check(3021, arr->get(1) == NULL);
    check(3022, arr->get(0)->equals(new String("hi")));
    arr->append(new String("foo"));
    check(3021, arr->get(1) == NULL);
    check(3023, arr->get(2)->equals(new String("foo")));
    
    check(3031, arr->contains(new String("foo")));
    check(3032, arr->index_of(new String("foo")) == 1);
    check(3033, arr->contains(NULL));
    check(3034, arr->index_of(NULL) == 1);
    arr->remove(1);
    check(3035, !arr->contains(NULL));
    check(3036, arr->index_of(NULL) > 2);
    arr->remove(1);
    check(3037, !arr->contains(new String("foo")));
    check(3038, arr->index_of(new String("foo")) > 1);
    check(3039, arr->size() == 1);
}

//memory leaks galore, do not call multiple times within a process
int main(int argc, char** argv) {
    testAdd();
    testQueries();
    testRemove();
    return 0;
}