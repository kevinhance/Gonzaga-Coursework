#include <iostream>
#include <cassert>
#include <string>

#include "Dictionary.h"
#include "SimpleDictionary.h"

using namespace std;

int main() {
    // Once you've implemented SortedDictionary, you should change
    // the line below to create a SortedDictionary instead of a 
    // SimpleDictionary.
    Dictionary<string, int> *dict = new SimpleDictionary<string, int>(20);
    cout << "   Correct:" << endl;
    dict->display();
    assert(dict->size() == 0);
    
    dict->add("e", 1);
    cout << endl << "   Correct: e->1" << endl;
    dict->display();
    assert(dict->keyExists("e"));
    assert(dict->getValue("e") == 1);

    dict->add("b", 34);
    cout << endl << "   Correct: b->34, e->1" << endl;
    dict->display();
    assert(dict->keyExists("e"));
    assert(dict->keyExists("b"));
    assert(!dict->keyExists("c"));
    assert(dict->getValue("e") == 1);
    assert(dict->getValue("b") == 34);

    dict->add("g", 2);
    cout << endl << "   Correct: b->34, e->1, g->2" << endl;
    dict->display();
    assert(dict->keyExists("e"));
    assert(dict->keyExists("b"));
    assert(dict->keyExists("g"));
    assert(dict->getValue("e") == 1);
    assert(dict->getValue("b") == 34);
    assert(dict->getValue("g") == 2);

    dict->add("f", 3);
    cout << endl << "   Correct: b->34, e->1, f->3, g->2" << endl;
    dict->display();
    assert(dict->keyExists("e"));
    assert(dict->keyExists("b"));
    assert(dict->keyExists("g"));
    assert(dict->keyExists("f"));
    assert(dict->getValue("e") == 1);
    assert(dict->getValue("b") == 34);
    assert(dict->getValue("g") == 2);
    assert(dict->getValue("f") == 3);

    dict->add("b", 2);
    cout << endl << "   Correct: b->2, e->1, f->3, g->2" << endl;
    dict->display();
    assert(dict->size() == 4);
    assert(dict->keyExists("e"));
    assert(dict->keyExists("b"));
    assert(dict->keyExists("g"));
    assert(dict->keyExists("f"));
    assert(dict->getValue("e") == 1);
    assert(dict->getValue("b") == 2);
    assert(dict->getValue("g") == 2);
    assert(dict->getValue("f") == 3);

    dict->add("c", 1);
    cout << endl << "   Correct: b->2, c->1, e->1, f->3, g->2" << endl;
    dict->display();
    assert(dict->keyExists("e"));
    assert(dict->keyExists("b"));
    assert(dict->keyExists("g"));
    assert(dict->keyExists("f"));
    assert(dict->keyExists("c"));
    assert(dict->getValue("e") == 1);
    assert(dict->getValue("b") == 2);
    assert(dict->getValue("g") == 2);
    assert(dict->getValue("f") == 3);
    assert(dict->getValue("c") == 1);

    dict->add("a", 0);
    cout << endl << "   Correct: a->0, b->2, c->1, e->1, f->3, g->2" << endl;
    dict->display();
    assert(dict->keyExists("e"));
    assert(dict->keyExists("b"));
    assert(dict->keyExists("g"));
    assert(dict->keyExists("f"));
    assert(dict->keyExists("c"));
    assert(dict->keyExists("a"));
    assert(dict->getValue("e") == 1);
    assert(dict->getValue("b") == 2);
    assert(dict->getValue("g") == 2);
    assert(dict->getValue("f") == 3);
    assert(dict->getValue("c") == 1);
    assert(dict->getValue("a") == 0);

    dict->add("a", 1);
    cout << endl << "   Correct: a->1, b->2, c->1, e->1, f->3, g->2" << endl;
    dict->display();
    assert(dict->keyExists("e"));
    assert(dict->keyExists("b"));
    assert(dict->keyExists("g"));
    assert(dict->keyExists("f"));
    assert(dict->keyExists("c"));
    assert(dict->keyExists("a"));
    assert(dict->getValue("e") == 1);
    assert(dict->getValue("b") == 2);
    assert(dict->getValue("g") == 2);
    assert(dict->getValue("f") == 3);
    assert(dict->getValue("c") == 1);
    assert(dict->getValue("a") == 1);

    dict->remove("c");
    cout << endl << "   Correct: a->1, b->2, e->1, f->3, g->2" << endl;
    dict->display();
    assert(dict->keyExists("e"));
    assert(dict->keyExists("b"));
    assert(dict->keyExists("g"));
    assert(dict->keyExists("f"));
    assert(!dict->keyExists("c"));
    assert(dict->keyExists("a"));
    assert(dict->getValue("e") == 1);
    assert(dict->getValue("b") == 2);
    assert(dict->getValue("g") == 2);
    assert(dict->getValue("f") == 3);
    assert(dict->getValue("a") == 1);

    dict->remove("g");
    cout << endl << "   Correct: a->1, b->2, e->1, f->3" << endl;
    dict->display();
    assert(dict->keyExists("e"));
    assert(dict->keyExists("b"));
    assert(!dict->keyExists("g"));
    assert(dict->keyExists("f"));
    assert(!dict->keyExists("c"));
    assert(dict->keyExists("a"));
    assert(dict->getValue("e") == 1);
    assert(dict->getValue("b") == 2);
    assert(dict->getValue("f") == 3);
    assert(dict->getValue("a") == 1);

    dict->remove("a");
    cout << endl << "   Correct: b->2, e->1, f->3" << endl;
    dict->display();
    assert(dict->keyExists("e"));
    assert(dict->keyExists("b"));
    assert(!dict->keyExists("g"));
    assert(dict->keyExists("f"));
    assert(!dict->keyExists("c"));
    assert(!dict->keyExists("a"));
    assert(dict->getValue("e") == 1);
    assert(dict->getValue("b") == 2);
    assert(dict->getValue("f") == 3);
    return 0;
}