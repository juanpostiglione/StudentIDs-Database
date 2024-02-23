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
        ostringstream oss;
        root->printInOrder(root, oss);
        string output = oss.str();
        cout <<output<< endl;
    }

    /// PrintPreorder command
    else if (command == "printPreorder") {
        ostringstream oss;
        root->printPreOrder(root, oss);
        string output = oss.str();
        cout <<output<< endl;
    }
    /// PrintPostorder command
    else if (command == "printPostorder") {
        ostringstream oss;
        root->printPostOrder(root, oss);
        string output = oss.str();
        cout <<output<< endl;
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
        root = root->removeID(root, idStr);
    }

    /// RemoveInorder command
    else if (command == "removeInorder") {
        int n;
        iss >> n;
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
