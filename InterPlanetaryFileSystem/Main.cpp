#include "Header.h"

int main()

{

    btree p(3); // A B-Tree with minimum degree 3

    p.insert(1);

    p.insert(13);

    p.insert(7);

    p.insert(10);

    p.insert(11);

    p.insert(6);

    p.insert(14);

    p.insert(15);

    cout << "Traversal of tree constructed is\n";

    p.traverse();

    cout << endl;

    p.remove(6);

    cout << "Traversal of tree after deleting 6\n";

    p.traverse();

    cout << endl;

    p.remove(13);

    cout << "Traversal of tree after deleting 13\n";

    p.traverse();

    cout << endl;

    return 0;

}