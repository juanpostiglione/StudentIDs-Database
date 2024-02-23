#include <iostream>
using namespace std;

/// Struct for Student
struct Student
{
    string name;
    string id;
    Student(string name, string id);

};

/// Struct for StudentTree
struct StudentTree
{
    Student data;
    int height;
    int levelCount = 0;
    string name;
    string id;
    StudentTree* right;
    StudentTree* left;

    ///StudentTree Constructor
    StudentTree(Student data);

    /// Insert function
    StudentTree* insert(StudentTree* root, Student student);

    /// Print Levels of the Tree function
    void printLevels(StudentTree *root);

    /// Helper for print in order function
    void printInOrderHelper(StudentTree* root, bool& first, ostringstream& oss);

    /// Helper for print pre order function
    void printPreOrderHelper(StudentTree* root, bool& first, ostringstream& oss);

    /// Helper for print post order function
    void printPostOrderHelper(StudentTree* root, bool& first, ostringstream& oss);


    /// Print in order function
    void printInOrder(StudentTree* root, ostringstream& oss);

    /// Print pre order function
    void printPreOrder(StudentTree* root, ostringstream& oss);

    /// Print post order function
    void printPostOrder(StudentTree* root, ostringstream& oss);

    /// Function for search ID
    void searchID(StudentTree *root, std::string id);

    /// Function for search names
    void searchName(StudentTree* root, string name);

    /// Function to remove ID
    StudentTree* removeID(StudentTree* root, string id);

    /// Function for right rotation
    static StudentTree* rightRotation(StudentTree* root);

    /// Function for left rotation
    static StudentTree* leftRotation(StudentTree* root);

    /// Function to get the height of the tree
    static int getHeight(StudentTree* node);

    /// Function to get the balance of the tree
    static int getBalance(StudentTree* node);

    /// Function to remove Nth Inorder
    void removeNthInorder(StudentTree*& root, int n);
};


