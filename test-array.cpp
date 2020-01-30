
#include "string.h"
#include "array.h"
#include "object.h"

void check(const char* name, bool thing){
    if(thing) printf("\033[0;32m[succeeded: %s]\033[0m\n", name);
    else printf("\033[0;31m[failed: %s]\033[0m\n", name);
}

//tests append, append_all, insert, insert_all 
//indirectly tests get, size
void testAdd (void) {
    String* hi = new String("hi");
    String* bar = new String("bar");
    String* baz = new String("baz");
    String* bat = new String("bat");
    String* end = new String("end");
    String* sad = new String("sad");
    
    Array* arr = new Array();
    arr->append(new String("hi"));
    check("append 0", arr->get(0)->equals(hi));
    arr->append(NULL);
    check("append unchanged", arr->get(0)->equals(hi));
    check("append 1", arr->get(1) == NULL);
    
    
    Array* arr2 = new Array();
    arr2->append(new String("bar"));
    arr2->append(new String("sad"));
    check("append size", arr2->size() == 2);
    arr2->append_all(arr);
    check("appendall 0", arr2->get(0)->equals(bar));
    check("appendall 1", arr2->get(1)->equals(sad));
    check("appendall 2", arr2->get(2)->equals(hi));
    check("appendall 3", arr2->get(3) == NULL);
    check("appendall size", arr2->size() == 4);
    arr2->append_all(new Array());
    check("appendall blank 0", arr2->get(0)->equals(bar));
    check("appendall blank 1", arr2->get(1)->equals(sad));
    check("appendall blank 2", arr2->get(2)->equals(hi));
    check("appendall blank 3", arr2->get(3) == NULL);
    check("appendall blank size", arr2->size() == 4);
    
    
    Array* dup = new Array();
    dup->append(new String("bar"));
    dup->append(new String("sad"));
    dup->append(new String("hi"));
    dup->append(NULL);
    
    arr2->insert_all(dup, 2);
    check("insertall 0", arr2->get(0)->equals(bar));
    check("insertall 1", arr2->get(1)->equals(sad));
    check("insertall 2", arr2->get(2)->equals(bar));
    check("insertall 3", arr2->get(3)->equals(sad));
    check("insertall 4", arr2->get(4)->equals(hi));
    check("insertall 5", arr2->get(5) == NULL);
    check("insertall 6", arr2->get(6)->equals(hi));
    check("insertall 7", arr2->get(7) == NULL);
    check("insertall size", arr2->size() == 8);
    arr2->insert_all(new Array(), 5);
    check("insertall blank 0", arr2->get(0)->equals(bar));
    check("insertall blank 1", arr2->get(1)->equals(sad));
    check("insertall blank 2", arr2->get(2)->equals(bar));
    check("insertall blank 3", arr2->get(3)->equals(sad));
    check("insertall blank 4", arr2->get(4)->equals(hi));
    check("insertall blank 5", arr2->get(5) == NULL);
    check("insertall blank 6", arr2->get(6)->equals(hi));
    check("insertall blank 7", arr2->get(7) == NULL);
    check("insertall blank size", arr2->size() == 8);
    
    Array* arr3 = new Array();
    arr3->append(new String("hi"));
    arr3->append(NULL);
    
    arr3->insert(new String("bar"), 0);
    arr3->insert(new String("baz"), 3);
    arr3->insert(new String("bat"), 0);
    arr3->insert(new String("end"), 10000);
    check("insert 0", arr3->get(0)->equals(bat));
    check("insert 1", arr3->get(1)->equals(bar));
    check("insert 2", arr3->get(2)->equals(hi));
    check("insert 3", arr3->get(3) == NULL);
    check("insert 4", arr3->get(4)->equals(baz));
    check("insert 5", arr3->get(5)->equals(end));
    check("insert size", arr3->size() == 6);
    
    //arr3 freed by adding to arr2
    //dup freed by adding to arr2
    delete arr2; 
    delete arr3;
    delete hi;
    delete bar;
    delete baz;
    delete bat;
    delete end;
    delete sad;
}

//tests set, remove, removeRange, clear
// indirectly tests append, get, size
void testRemove(void) {
    
    String* hi = new String("hi");
    String* foo = new String("foo");
    String* bar = new String("bar");
    
    Object* free1;
    Object* free2;
    Object* free3;
    Object* free4;
    
    Array* arr = new Array();
    arr->append(new String("hi"));
    check("set replace return", (free1 = arr->set(new String("foo"), 0))->equals(hi));
    check("set replace 0", arr->get(0)->equals(foo));
    arr->append(NULL);
    check("set at size return", arr->set(new String("hi"), 1) == NULL);
    check("set at size 0", arr->get(0)->equals(foo));
    check("set at size 1", arr->get(1)->equals(hi));
    
    check("remove return", (free2 = arr->remove(0))->equals(foo));
    check("remove shrink", (free3 = arr->remove(0))->equals(hi));
    check("remove from empty", arr->remove(0) == NULL);
    check("size after remove", arr->size() == 0);
    arr->append(NULL);
    arr->append(new String("hi"));
    check("remove index 1", (free4 = arr->remove(1))->equals(hi));
    check("size after remove 1", arr->size() == 1);
    check("remove null", arr->remove(0) == NULL);
    
    arr->append(new String("hi"));
    arr->append(new String("hi"));
    arr->append(new String("hi"));
    check("size before clear", arr->size() == 3);
    arr->clear();
    check("size after clear", arr->size() == 0);
    arr->append(new String("hi"));
    arr->append(new String("foo"));
    arr->append(new String("bar"));
    arr->append(new String("hi"));
    check("size before removerange", arr->size() == 4);
    arr->remove_range(1, 3);
    check("removerange start", arr->get(0)->equals(hi));
    check("removerange shrink", arr->get(1)->equals(hi));
    check("size after removerange", arr->size() == 2);
    
    delete arr;
    delete hi;
    delete foo;
    delete bar;
    delete free1;
    delete free2;
    delete free3;
    delete free4;
}

//tests get, contains, indexOf, size, equals
//indirectly tests remove, append
void testQueries(void) {
    
    String* hi = new String("hi");
    String* foo = new String("foo");
    
    Array* arr = new Array();
    Array* arr2 = new Array();
    check("empty arrays equal", arr->equals(arr2));
    arr->append(new String("hi"));
    arr->clear();
    check("cleared arrays equal", arr->equals(arr2));
    arr->append(new String("hi"));
    arr2->append(new String("hi"));
    check("non-empty arrays equal", arr2->equals(arr));
    check("symmetric equality", arr->equals(arr2));
    
    arr->append(NULL);
    check("size after append", arr->size() == 2);
    check("get null", arr->get(1) == NULL);
    check("get non-null", arr->get(0)->equals(hi));
    arr->append(new String("foo"));
    check("get after append", arr->get(1) == NULL);
    check("get after append 2", arr->get(2)->equals(foo));
    
    check("contains non-null", arr->contains(foo));
    check("indexof non-null", arr->index_of(foo) == 2);
    check("contains null", arr->contains(NULL));
    check("indexof null", arr->index_of(NULL) == 1);
    arr->remove(1);
    check("!contains null", !arr->contains(NULL));
    check("!indexof null", arr->index_of(NULL) > 2);
    arr->remove(1);
    check("!contains non-null", !arr->contains(foo));
    check("!indexof non-null", arr->index_of(foo) > 1);
    check("size (for indexof validation)", arr->size() == 1);
    
    delete arr;
    delete arr2;
    delete hi;
    delete foo;
}

// should free all memory (if you want to check if you are freeing properly)
int main(int argc, char** argv) {
    testQueries();
    testAdd();
    testRemove();
    return 0;
}