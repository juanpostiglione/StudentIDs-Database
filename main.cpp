#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "StudentTree.h"
#include <algorithm>
using namespace std;

/// Handle commands
void processCommand(StudentTree*& root, const string& commandLine) {
    istringstream iss(commandLine);
    string command;
    iss >> command;

    /// Insert command
    if (command == "insert") {
        string name, idStr;
        iss >> quoted(name) >> idStr;
        root = root->insert(root, Student(name, idStr));
    }
    /// PrintInorder command
    else if (command == "printInorder") {
        root->printInOrder(root);
        cout << endl;
    }

    /// PrintPreorder command
    else if (command == "printPreorder") {
        root->printPreOrder(root);
        cout << endl;
    }
    /// PrintPostorder command
    else if (command == "printPostorder") {
        root->printPostOrder(root);
        cout << endl;
    }

    /// PrintLevelCount command
    else if (command == "printLevelCount") {
        root->printLevels(root);
        cout << endl;
    }

    /// Remove command
    else if (command == "remove") {
        string idStr;
        iss >> idStr;
        cout<<"successful" << endl;
        root = root->removeID(root, idStr);
    }

    /// RemoveInorder command
    else if (command == "removeInorder") {
        int n;
        iss >> n;
        cout<<"successful" << endl;
        root->removeNthInorder(root, n);
    }

    /// Search command
    else if (command == "search") {
        string query;
        // Handle quotation strings
        if (!(iss >> std::quoted(query))) {
            cout << "unsuccessful" << endl;
            return;
        }

        // Check if is numeric iterating through all the string
        bool isNumeric = !query.empty() && all_of(query.begin(), query.end(), ::isdigit);

        // If numeric, calls searchID
        if (isNumeric) {
            root->searchID(root, query);
        }

        // Else, calls searchName
        else {
            root->searchName(root, query);
        }
        cout << endl;
    } else {
        cout << "unsuccessful" << endl;
    }
}

int main() {

    // Empty tree
    StudentTree* root = nullptr;

    // Number of commands
    int numberOfCommands;
    cin >> numberOfCommands;
    cin.ignore();

    // Loop according to the number of commands, and execute them with processCommand
    string line;
    for (int i = 0; i < numberOfCommands; i++) {
        getline(cin, line);
        processCommand(root, line);
    }

    return 0;
}