
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

void testPrimitives(void) {
    BoolArray* ba = new BoolArray();
    IntArray* ia = new IntArray();
    FloatArray* fa = new FloatArray();
    
    
    check("empty BA size 0", ba->size() == 0);
    check("empty IA size 0", ia->size() == 0);
    check("empty FA size 0", fa->size() == 0);
    ba->append(false);
    ba->append(false);
    ba->append(true);
    check("append BA changes size", ba->size() == 3);
    check("BA get 0", ba->get(0) == false);
    check("BA get 2", ba->get(2) == true);
    ba->get(3);//check OB
    ia->append(0);
    ia->append(2);
    ia->append(3);
    check("append IA changes size", ia->size() == 3);
    check("IA get 0", ia->get(0) == 0);
    check("IA get 2", ia->get(2) == 3);
    ia->get(3);//check OB
    fa->append(0.0f);
    fa->append(2.2f);
    fa->append(3.3f);
    check("append FA changes size", fa->size() == 3);
    check("FA get 0", fa->get(0) == 0.0f);
    check("FA get 2", fa->get(2) == 3.3f);
    fa->get(3);//check OB
    
    ba->insert(false, 1000);
    ba->insert(true, 1);
    check("BA insert 0", ba->get(0) == false);
    check("BA insert 1", ba->get(1) == true);
    check("BA insert 2", ba->get(2) == false);
    check("BA insert 3", ba->get(3) == true);
    check("BA insert 4", ba->get(4) == false);
    ia->insert(4, 1000);
    ia->insert(1, 1);
    check("IA insert 0", ia->get(0) == 0);
    check("IA insert 1", ia->get(1) == 1);
    check("IA insert 2", ia->get(2) == 2);
    check("IA insert 3", ia->get(3) == 3);
    check("IA insert 4", ia->get(4) == 4);
    fa->insert(4.4, 1000);
    fa->insert(1.1, 1);
    check("FA insert 0", fa->get(0) == 0.0f);
    check("FA insert 1", fa->get(1) == 1.1f);
    check("FA insert 2", fa->get(2) == 2.2f);
    check("FA insert 3", fa->get(3) == 3.3f);
    check("FA insert 4", fa->get(4) == 4.4f);
    
    check("BA size after insert/append", ba->size() == 5);
    check("IA size after insert/append", ia->size() == 5);
    check("FA size after insert/append", fa->size() == 5);
    
    check("BA set RV", ba->set(false, 1) == true);
    ba->set(true, 1000);
    check("BA set 0", ba->get(0) == false);
    check("BA set 1", ba->get(1) == false);
    check("BA set 2", ba->get(2) == false);
    check("BA set 3", ba->get(3) == true);
    check("BA set 4", ba->get(4) == false);
    check("IA set RV", ia->set(5, 1) == 1);
    ia->set(6, 1000);
    check("IA set 0", ia->get(0) == 0);
    check("IA set 1", ia->get(1) == 5);
    check("IA set 2", ia->get(2) == 2);
    check("IA set 3", ia->get(3) == 3);
    check("IA set 4", ia->get(4) == 4);
    check("FA set RV", ia->set(5.5, 1) == 1);
    fa->set(6, 1000);
    check("FA set 0", fa->get(0) == 0.0f);
    check("FA set 1", fa->get(1) == 5.5f);
    check("FA set 2", fa->get(2) == 2.2f);
    check("FA set 3", fa->get(3) == 3.3f);
    check("FA set 4", fa->get(4) == 4.4f);
    
    check("BA size after set", ba->size() == 5);
    check("IA size after set", ia->size() == 5);
    check("FA size after set", fa->size() == 5);
    
    check("BA contains", ba->contains(true));
    check("BA indexof", ba->index_of(true) == 3);
    check("BA remove RV", ba->remove(3) == true);
    ba->remove(500);//out of range
    check("BA !contains", !ba->contains(true));
    check("BA !indexof", ba->index_of(true) > 4);
    check("IA contains", ia->contains(5));
    check("IA indexof", ia->index_of(5) == 1);
    check("IA remove RV", ia->remove(1) == 5);
    ba->remove(500);//out of range
    check("IA !contains", !ia->contains(5));
    check("IA !indexof", ia->index_of(5) > 4);
    check("FA contains", fa->contains(5.5f));
    check("FA indexof", fa->index_of(5.5f) == 1);
    check("FA remove RV", fa->remove(1) == 5.5f);
    ba->remove(500);//out of range
    check("FA !contains", !fa->contains(5.5f));
    check("FA !indexof", fa->index_of(5.5f) > 4);
    
    check("BA size after remove", ba->size() == 4);
    check("IA size after remove", ia->size() == 4);
    check("FA size after remove", fa->size() == 4);
    
    ba->clear();
    ia->clear();
    fa->clear();
    check("BA size after clear", ba->size() == 0);
    check("IA size after clear", ia->size() == 0);
    check("FA size after clear", fa->size() == 0);
    
    
    delete ba;
    delete ia;
    delete fa;
}

// should free all memory (if you want to check if you are freeing properly)
int main(int argc, char** argv) {
    testQueries();
    testAdd();
    testRemove();
    testPrimitives();
    return 0;
}