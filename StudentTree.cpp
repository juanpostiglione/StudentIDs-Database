#include "StudentTree.h"
#include<queue>
#include<stack>


/// Student Constructor
Student::Student(string name, string id): name(name), id(id){
}

/// StudentTree Constructor
StudentTree::StudentTree(Student data): data(data), right(nullptr), left(nullptr), height(1){
}

/// Function to get the height
int StudentTree::getHeight(StudentTree* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

/// Function to get the balance
int StudentTree::getBalance(StudentTree* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

/// Left Rotation (Right Right)
StudentTree* StudentTree::leftRotation(StudentTree *root) {
    StudentTree* grandchild;
    StudentTree* newParent;

    grandchild = root->right->left;
    newParent = root->right;
    newParent->left = root;
    root->right = grandchild;

    // Update heights
    root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
    newParent->height = std::max(getHeight(newParent->left), getHeight(newParent->right)) + 1;

    return newParent;
}

/// Right Rotation (Left Left)
StudentTree* StudentTree::rightRotation(StudentTree *root){
    StudentTree* grandChild;
    StudentTree* newParent;

    grandChild = root->left->right;
    newParent = root->left;
    newParent->right = root;
    root->left = grandChild;

    // Update heights
    root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
    newParent->height = std::max(getHeight(newParent->left), getHeight(newParent->right)) + 1;

    return newParent;
}

/// Insert Function
StudentTree* StudentTree::insert(StudentTree* root, Student student) {
    if (root == nullptr) {
        cout << "successful" << endl;
        return new StudentTree(student);
    }

    int studentID = stoi(student.id);
    int rootID = stoi(root->data.id);

    if (studentID < rootID) {
        root->left = insert(root->left, student);
    } else if (studentID > rootID) {
        root->right = insert(root->right, student);
    } else {
        cout << "unsuccessful" << endl;
        return root;
    }

    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && studentID < stoi(root->left->data.id)) {
        return rightRotation(root);
    }

    if (balance < -1 && studentID > stoi(root->right->data.id)) {
        return leftRotation(root);
    }

    if (balance > 1 && studentID > stoi(root->left->data.id)) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    if (balance < -1 && studentID < stoi(root->right->data.id)) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;
}

/// Helper for print in order
void StudentTree::printInOrderHelper(StudentTree* root, bool& first) {
    if (root != nullptr) {
        printInOrderHelper(root->left, first);
        if (!first) {
            cout << ", ";
        } else {
            first = false;
        }
        cout << root->data.name;
        printInOrderHelper(root->right, first);
    }
}

/// Print in order, now reset the boolean
void StudentTree::printInOrder(StudentTree* root) {
    bool first = true;
    printInOrderHelper(root, first);
}

/// Print in Pre Order
void StudentTree::printPreOrder(StudentTree *root) {
    static bool first = true;
    if (root != nullptr) {
        if (!first) {
            cout << ", ";
        } else {
            first = false;
        }
        cout << root->data.name;
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

/// Print in Post Order
void StudentTree::printPostOrder(StudentTree *root) {
    static bool first = true;
    if (root != nullptr) {
        printPostOrder(root->left);
        printPostOrder(root->right);
        if (!first) {
            cout << ", ";
        } else {
            first = false;
        }
        cout << root->data.name;
    }
}

/// Print Levels
void StudentTree::printLevels(StudentTree *root) {
    if(root == nullptr){
        cout<<levelCount;
    }
    queue<StudentTree*> levels;
    levels.push(root);
    int levelCount = 0;
    while(!levels.empty())
    {
        int levelSize = levels.size();

        for(int i = 0; i < levelSize;i++){
            StudentTree* Node = levels.front();
            levels.pop();

            if(Node->left != nullptr){
                levels.push(Node->left);
            }
            if(Node->right != nullptr){
                levels.push(Node->right);
            }
        }
        levelCount++;
    }
    cout<<levelCount;
}

/// Search for ID
void StudentTree::searchID(StudentTree *root, std::string id) {
    if(root == nullptr){
        cout<<"unsuccessful";
        return;
    }
    if(stoi(id) < stoi(root->data.id)){
        searchID(root->left,id);
    }
    else if(stoi(id) > stoi(root->data.id)){
        searchID(root->right,id);
    }
    else{
        cout<<root->data.name;
        return;
    }
}

/// Search for Name
void StudentTree::searchName(StudentTree *root, string name) {
    if (root == nullptr) {
        cout << "unsuccessful";
        return;
    }

    bool found = false;
    string output;
    stack<StudentTree*> names;
    names.push(root);

    while (!names.empty()) {
        StudentTree* current = names.top();
        names.pop();

        if (current->data.name == name) {
            output += current->data.id + "\n";
            found = true;
        }

        if (current->right != nullptr) {
            names.push(current->right);
        }

        if (current->left != nullptr) {
            names.push(current->left);
        }
    }
    if (!found) {
        cout << "unsuccessful";
    } else {
        // Remove the trailing comma and space
        cout << output;
    }
}
/// Remove ID
StudentTree* StudentTree::removeID(StudentTree* root, string id) {
    if (root == nullptr) {
        cout << "unsuccessful" << endl;
        return nullptr;
    }

    int nodeId = stoi(root->data.id);
    int targetId = stoi(id);



    if (targetId < nodeId) {
        root->left = removeID(root->left, id);
    } else if (targetId > nodeId) {
        root->right = removeID(root->right, id);
    } else {
        // Node with only one child or no child
        if (root->left == nullptr || root->right == nullptr) {
            StudentTree* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                // No child case
                temp = root;
                root = nullptr;
            } else {
                // One child case
                *root = *temp; // Copy the contents of the non-empty child
            }
            delete temp;
        } else {
            // Node with two children: get the inorder successor
            StudentTree* temp = root->right;
            while (temp && temp->left != nullptr) {
                temp = temp->left;
            }

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = removeID(root->right, temp->data.id);
        }

    }

    // If the tree had only one node, then return
    if (root == nullptr) {
        return root;
    }

    root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotation(root);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotation(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;
}

/// Helper function to find the Nth node in inorder traversal.
StudentTree* findNthInorder(StudentTree*& root, int& n) {
    if (root == nullptr) {
        return nullptr;
    }

    StudentTree* left = findNthInorder(root->left, n);
    if (left != nullptr) {
        return left;
    }
    if (n == 0) {
        return root;
    }
    // Decrease n as we're still searching.
    n--;

    return findNthInorder(root->right, n);
}

/// Remove NthInorder
void StudentTree::removeNthInorder(StudentTree*& root, int n) {
    StudentTree* nodeToRemove = findNthInorder(root, n);
    if (nodeToRemove != nullptr) {
        root = removeID(root, nodeToRemove->data.id);

    } else {
        cout << "unsuccessful" << endl;
    }
}
