#include "BTree.h"

btree::btree(int _t)
{
    root = NULL;
    t = _t;
}

void btree:: traverse()
{
    if (root != NULL)

        root->traverse();
}

void btree::insert(int k, File f)

{
    if (root == NULL)
    {
        root = new btreenode(t, true);
        root->key[0] = k;
        root->filepath[0] = f;
        //root->filepath[0].path = f.path;

        root->n = 1;
    }

    else
    {
        if (root->n == 2 * t - 1)

        {

            btreenode* s = new btreenode(t, false);
            s->c[0] = root;
            s->splitchild(0, root);
            int i = 0;
            if (s->key[0] < k)
                i++;
            s->c[i]->insertnonfull(k, f);
            root = s;
        }
        else
            root->insertnonfull(k, f);

    }

}

void btree::remove(int k)

{

    if (!root)

    {

        std::cout << "The tree is empty\n";

        return;

    }

    root->remove(k);

    if (root->n == 0)
    {
        btreenode* tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->c[0];

        delete tmp;
    }

    return;

}

btreenode* btree::search(int k)
{
    return (root == NULL) ? NULL : root->search(k);
}