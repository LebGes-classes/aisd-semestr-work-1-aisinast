#include <iostream>
#include "aaTree.h"

using namespace std;

int main() 
{
    aaTree<int> tree;

    int data = 10;
    if (!tree.contains(data)) 
    {
        cout << "1. the \"contains\" method works!" << endl;
    }
    else 
    {
        cout << "1. error in the operatio of the \"contains\" method" << endl;
    }

    cout << endl;

    int arr[] = {70, 3, 30, 75, 20, 5, 13};

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        tree.insert(arr[i]);
    }

    if (!tree.contains(data)) 
    {
        cout << "2. the \"insert\" method works!" << endl;
    }
    else 
    {
        cout << "2. error in the operatio of the \"contains\" or the \"insert\" method" << endl;
    }

    cout << "\n\"inOrder\" check:" << endl;

    cout << "should be output:\n3 5 13 20 30 70 75\noutput:" << endl;
    tree.inOrder();

    cout << endl;

    if (!tree.contains(data)) 
    {
        cout << "3. the \"contains\" method works! (don't contain " << data << ")" << endl;
    }
    else 
    {
        cout << "3. error in the operatio of the \"contains\" method" << endl;
    }

    cout << endl;

    data = 20;

    if (tree.contains(data)) 
    {
        cout << "4. the \"contains\" method works! (contains " << data << ")" << endl;
    }
    else 
    {
        cout << "4. error in the operatio of the \"contains\" method" << endl;
    }
    
    cout << "\n\"delete\" check:" << endl;

    tree.remove(data);

    cout << "should be output:\n3 5 13 30 70 75\noutput:" << endl;
    tree.inOrder();

    cout << "\n\"clear\" check:" << endl;

    tree.clear();

    cout << "nothing should be output\noutput:" << endl;
    tree.inOrder();

}