#include <iostream>
#include <time.h>
using namespace std;
int height;
struct Node {
    int data;
    Node* leftChild;
    Node* rightChild;
    Node* parent;
    Node* root;
    int level;
};
Node* createTree(int data) {
    Node* node = new Node();
    node->data = data;
    node->leftChild = nullptr;
    node->rightChild = nullptr;
    node->parent = nullptr;
    node->root = node;
    node->level++;
    height = 1;
    return node;
}
Node* createChild(int data, Node* node1) {
    Node* node = new Node();
    node->data = data;
    node->leftChild = nullptr;
    node->rightChild = nullptr;
    node->parent = node1;
    node->root = node1->root;
    node->level = node->parent->level+1;
    if(height < node->level) {
        height = node->level;
    }
    return node;
}
Node* insert(Node* node, int data) {
    if (node == nullptr) {
        return createTree(data);
    }if(node->data == data) {
        return node;
    }if (data < node->data) {
        if (node->leftChild != nullptr) {
            node->leftChild = insert(node->leftChild, data);
        }if(node->leftChild == nullptr) {
            node->leftChild = createChild(data, node);
        }
        return node;
    }if (data > node->data) {
        }if (node->rightChild != nullptr) {
            node->rightChild = insert(node->rightChild, data);
        }if(node->rightChild == nullptr) {
            node->rightChild = createChild(data, node);
        }
    return node;
    }
void findNode(Node* node, int data) {
    if (node == nullptr) {
        cout << "nullptr" << endl;
        return;
    }if (node->data == data) {
        cout <<"Your node: "<<node->data << endl;
        return;
    }if (node->data > data) {
        if (node->leftChild != nullptr) {
            findNode(node->leftChild, data);
        }else {
            cout << "Node doesn't exist" << endl;
        }
    }if (node->data < data) {
        if (node->rightChild != nullptr) {
            findNode(node->rightChild, data);
        }else {
            cout << "Node doesn't exist" << endl;
        }
    }
}
Node* betterInsert(Node* leftChild, Node* rightChild) {
    if(rightChild->leftChild != nullptr) {
        return betterInsert(leftChild, rightChild->leftChild);
    }
    rightChild->leftChild = leftChild->rightChild;
    leftChild->rightChild->parent = rightChild;
    leftChild->rightChild = nullptr;
    return leftChild;
}
Node* parentInsert(Node* leftChild, Node* rightChild) {
    if(leftChild->rightChild != nullptr) {
        return parentInsert(leftChild->rightChild, rightChild);
    }
    leftChild->rightChild = rightChild;
    rightChild->parent = leftChild;
    return rightChild;
}
void setRoot(Node* node, bool isLeft) {
    if (node != nullptr) {
        if(node->parent == nullptr) {
            node->root = node;
        }if(node->parent != nullptr) {
            node->root = node -> parent->root;
        }
        setRoot(node->leftChild, true);
        setRoot(node->rightChild, false);
    }
}
Node* deleteNode(Node* node, int data) {
    if (node == nullptr) {
        cout << "nullptr" << endl;
    }if (node->data > data) {
        if (node->leftChild != nullptr) {
            deleteNode(node->leftChild, data);
        }else {
            cout << "Node doesn't exist" << endl;
        }
    }
    if (node->data < data) {
        if (node->rightChild != nullptr) {
            deleteNode(node->rightChild, data);
        }else {
            cout << "Node doesn't exist" << endl;
        }
    }if (node->data == data) {
        if(node->parent == nullptr) {//delete for root
            if(node->leftChild == nullptr && node->rightChild == nullptr) {
                delete node;
                cout << "Root deleted"<<endl;
                return 0;
            }if (node->rightChild == nullptr && node->leftChild != nullptr) {
                node->leftChild->parent = nullptr;
                Node* newRoot = node->leftChild;
                delete node;
                return newRoot;
            }if (node->leftChild == nullptr && node->rightChild != nullptr) {
                node->rightChild->parent = nullptr;
                Node* newRoot = node->rightChild;
                delete node;
                return newRoot;
            }if (node->rightChild != nullptr && node->leftChild != nullptr) {
                //finding new path for left->right child
                betterInsert(node->leftChild, node->rightChild);
                node->rightChild->parent = node->leftChild;
                node->leftChild->rightChild = node->rightChild;
                node->leftChild->parent = nullptr;
                node->leftChild->root = node->leftChild;
                Node* newRoot = node->leftChild;
                node->leftChild = nullptr;
                node->rightChild = nullptr;
                delete node;
                setRoot(newRoot, false);
                return newRoot;
            }
    }if(node->parent != nullptr) {
        //delete for normal node
        if(node->leftChild == nullptr && node->rightChild == nullptr) {
            //delete node without children
            if(node->parent->leftChild == nullptr && node->parent->rightChild != nullptr) {
                node->parent->rightChild = nullptr;
                Node* newChild = node->parent;
                delete node;
                return newChild;
            }if (node->parent->rightChild == nullptr && node->parent->leftChild != nullptr) {
                node->parent->leftChild = nullptr;
                Node* newChild = node ->parent;
                delete node;
                return newChild;
            }
        }
    }if(node->leftChild != nullptr && node->rightChild == nullptr) {
        //delete node with one child
        if(node == node->parent->leftChild) {
            node->parent->leftChild = node->leftChild;
            node->leftChild->parent = node->parent;
            Node* newParent = node->parent;
            delete node;
            return newParent;
        }if(node == node->parent->rightChild) {
            node->parent->rightChild = node->leftChild;
            node->leftChild->parent = node->parent;
            Node* newParent = node->parent;
            delete node;
            return newParent;
        }
    }if(node->rightChild != nullptr && node->leftChild != nullptr) {
        //delete node with children's
        if(node == node->parent->leftChild) {
            if(node->leftChild->rightChild != nullptr) {//check if node have grand child
                node->parent->leftChild = node->leftChild;
                node->leftChild->parent = node->parent;
                parentInsert(node->leftChild, node->rightChild);
                Node* newParent = node->parent;
                delete node;
                return newParent;
            }if(node->leftChild->rightChild == nullptr) {
                node->parent->leftChild = node->leftChild;
                node->leftChild->parent = node->parent;
                node->rightChild->parent = node->leftChild;
                node->leftChild->rightChild = node->rightChild;
                Node* newParent = node->parent;
                delete node;
                return newParent;
            }
        }
        if(node == node->parent->rightChild) {
            if(node->leftChild->rightChild != nullptr) {
                node->parent->rightChild = node->leftChild;
                node->leftChild->parent = node->parent;
                parentInsert(node->leftChild, node->rightChild);
                Node* newParent = node->parent;
                delete node;
                return newParent;
            }if(node->leftChild->rightChild == nullptr) {
                node->parent->rightChild = node->leftChild;
                node->leftChild->parent = node->parent;
                node->rightChild->parent = node->leftChild;
                node->leftChild->rightChild = node->rightChild;
                Node* newParent = node->parent;
                delete node;
                return newParent;
            }
        }
    }
    }
    return node;
}
void clearAll(Node* root) {
    if(root != nullptr) {
       if(root->leftChild != nullptr && root->rightChild != nullptr) {
            clearAll(root->leftChild);
            clearAll(root->rightChild);
        }if(root->leftChild == nullptr && root->rightChild != nullptr) {
            clearAll(root->rightChild);
        }if(root->leftChild != nullptr && root->rightChild == nullptr) {
            clearAll(root->leftChild);
        }if(root->leftChild == nullptr && root->rightChild == nullptr) {
            if(root->parent == nullptr) {
                delete root;
                return;
            }
            if(root->parent->leftChild == root) {
                root->parent->leftChild = nullptr;
            }if(root->parent->rightChild == root) {
                root->parent->rightChild = nullptr;
            }
            root->parent = nullptr;
            delete root;
        }
    }
}
void printBT(const std::string& prefix, const Node* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->data << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->leftChild, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->rightChild, false);
    }
}
void printBT(const Node* node)
{
    printBT("", node, false);
}
void test() {
    srand((unsigned)time(0));
    Node* root = createTree(50);
    insert(root, 67);
    insert(root, 76);
    insert(root, 13);
    insert(root, 22);
    insert(root, 24);
    insert(root, 11);
    insert(root, 18);
    insert(root, 34);
    insert(root, 8);
    insert(root, 5);
    insert(root, 29);
    insert(root, 54);
    insert(root, 68);
    insert(root, 71);
    insert(root, 45);
    insert(root, 30);
    printBT(root);
    root = deleteNode(root, 50);
    root = deleteNode(root, 30);
    root = deleteNode(root, 76);
    root = deleteNode(root, 11);
    insert(root, 55);
    root = deleteNode(root, 67);
    root = deleteNode(root, 22);
    printBT(root);
    clearAll(root);
}
void test2(int x) {
    srand((unsigned)time(0));
    Node* root = createTree(50);
    for(int i = 0; i < x; i++) {
        insert(root, rand() % 100);
    }
    insert(root, 12);
    printBT(root);
    clock_t t1 = clock();//start
    findNode(root, 12);
    clock_t t2 = clock();
    double time_spent = (double)((t2 - t1)*100)/CLOCKS_PER_SEC;
    cout<<"Time spent for " << x <<" node: "<<time_spent<<endl;
}
int main() {

    // test();
    test2(20);
    test2(100);
    return 0;
}
