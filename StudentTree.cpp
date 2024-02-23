#include "StudentTree.h"
#include<queue>
#include<stack>
#include<sstream>
#include <algorithm>


/// Student Constructor
Student::Student(string name, string id): name(name), id(id){
}

/// StudentTree Constructor
StudentTree::StudentTree(Student data): data(data), height(1), right(nullptr),left(nullptr){
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
    // Check if the name contains numeric characters
    if (!all_of(student.name.begin(), student.name.end(), ::isalpha)) {
        cout << "unsuccessful" << endl;
        return root;
    }

        // Check if the id contains only numeric characters
    else if(student.id.length() != 8 || !all_of(student.id.begin(), student.id.end(), ::isdigit)){
        cout << "unsuccessful" << endl;
        return root;
    }

    // Continue with the insertion process if the name is valid
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
void StudentTree::printInOrderHelper(StudentTree* root, bool& first, ostringstream& oss) {
    if (root != nullptr) {
        printInOrderHelper(root->left, first, oss);
        if (!first) {
            oss << ", ";
        } else {
            first = false;
        }
        oss << root->data.name;
        printInOrderHelper(root->right, first, oss);
    }
}

/// Print in order, now reset the boolean
void StudentTree::printInOrder(StudentTree* root, ostringstream& oss) {
    bool first = true;
    printInOrderHelper(root, first, oss);
}

/// Helper of print pre Pre Order
void StudentTree::printPreOrderHelper(StudentTree *root, bool& first, ostringstream& oss) {
    if (root != nullptr) {
        if (!first) {
            oss << ", ";
        } else {
            first = false;
        }
        oss << root->data.name;
        printPreOrderHelper(root->left, first, oss);
        printPreOrderHelper(root->right, first, oss);
    }
}

/// Print pre order, now reset the boolean
void StudentTree::printPreOrder(StudentTree* root, ostringstream& oss) {
    bool first = true;
    printPreOrderHelper(root, first, oss);
}

/// Helper for print in Post Order
void StudentTree::printPostOrderHelper(StudentTree *root, bool& first, ostringstream& oss) {
    if (root != nullptr) {
        printPostOrderHelper(root->left, first, oss);
        printPostOrderHelper(root->right, first, oss);
        if (!first) {
            oss << ", ";
        } else {
            first = false;
        }
        oss << root->data.name;
    }
}

/// Print post order, now reset the boolean
void StudentTree::printPostOrder(StudentTree* root, ostringstream& oss) {
    bool first = true;
    printPostOrderHelper(root, first, oss);
}

/// Print Levels
void StudentTree::printLevels(StudentTree *root) {
    if(root == nullptr){
        cout<<levelCount;
    }
    queue<StudentTree*> levels;
    levels.push(root);
    int currentLevelCount = 0; // Rename the variable to avoid shadowing
    while(!levels.empty())
    {
        int levelSize = levels.size();

        for(int i = 0; i < levelSize;i++){
            StudentTree* node = levels.front();
            levels.pop();

            if(node->left != nullptr){
                levels.push(node->left);
            }
            if(node->right != nullptr){
                levels.push(node->right);
            }
        }
        currentLevelCount++;
    }
    cout<<currentLevelCount;
}


/// Search for ID
void StudentTree::searchID(StudentTree *root, std::string searchId) {
    if(root == nullptr){
        cout<<"unsuccessful" << endl;
        return;
    }
    if(stoi(searchId) < stoi(root->data.id)){
        searchID(root->left, searchId);
    }
    else if(stoi(searchId) > stoi(root->data.id)){
        searchID(root->right, searchId);
    }
    else{
        cout<<root->data.name << endl;
        return;
    }
}



/// Search for Name
void StudentTree::searchName(StudentTree *root, string searchName) {
    if (root == nullptr) {
        cout << "unsuccessful"<<endl;
        return;
    }

    bool found = false;
    string output;
    stack<StudentTree*> names;
    names.push(root);

    while (!names.empty()) {
        StudentTree* current = names.top();
        names.pop();

        if (current->data.name == searchName) {
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
        cout << "unsuccessful"<<endl;
    } else {
        // Remove the trailing comma and space
        cout << output;
    }
}

/// Remove ID
StudentTree* StudentTree::removeID(StudentTree* root, string removeId) {
    if (root == nullptr) {
        cout << "unsuccessful" << endl;
        return nullptr;
    }

    int nodeId = stoi(root->data.id);
    int targetId = stoi(removeId);

    if (targetId < nodeId) {
        root->left = removeID(root->left, removeId);
    } else if (targetId > nodeId) {
        root->right = removeID(root->right, removeId);
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
            cout<<"successful" << endl;

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
    // Decrease n as we are still searching
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
