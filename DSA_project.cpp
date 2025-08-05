#include <iostream>
#include <cstring>
#include <string>
#include <climits>
using namespace std;

const int TABLE_SIZE= 50;

struct TreeNode{
    string name;
    string info;
    TreeNode *left;
    TreeNode *right;

    TreeNode(string n, string i){
        name = n;
        info = i;
        left = right = NULL;
    }
};

TreeNode *insert(TreeNode *root, const string &name, const string &info, const string &parentName){
    if (!root)
        return nullptr;

    if (root->name == parentName){
        if (!root->left){
            root->left = new TreeNode(name, info);
        }
        else{
            TreeNode *temp = root->left;
            while (temp->right)
                temp = temp->right;
            temp->right = new TreeNode(name, info);
        }
        return root;
    }

    root->left = insert(root->left, name, info, parentName);
    root->right = insert(root->right, name, info, parentName);
    return root;
}

void displayTree(TreeNode *root, int level = 0){
    if (!root)
        return;

    for (int i = 0; i < level; ++i)
        cout << "   ";
    cout << root->name << " - " << root->info << endl;
    displayTree(root->left, level + 1);
    displayTree(root->right, level);
}

TreeNode *search(TreeNode *root, string buildingName){
    if (root == NULL){
        return NULL;
    }
    if (root->name == buildingName){
        return root;
    }
    TreeNode *result = search(root->left, buildingName);
    if (result != NULL){
        return result;
    }
    return search(root->right, buildingName);
}

string toLower(string str){
    for (char &c : str){
        c = tolower(c);
    }
    return str;
}

void recommendBuildings(TreeNode *root, string keyword){
    if (root == NULL){
        return;
    }

    string lowerKeyword = toLower(keyword);
    string lowerInfo = toLower(root->info);

    if (lowerInfo.find(lowerKeyword) != string::npos){
        cout << "- " << root->name << ": " << root->info << endl;
    }

    recommendBuildings(root->left, keyword);
    recommendBuildings(root->right, keyword);
}

struct Queue{
    struct Node{
        char *data;
        bool urgent;
        Node *next;
    } *front, *rear;

    Queue(){
        front = rear = NULL;
    }

    void enqueue(const char *str, bool urgent = false){
        Node *newNode = new Node;
        newNode->data = new char[strlen(str) + 1];
        strcpy(newNode->data, str);
        newNode->urgent = urgent;
        newNode->next = nullptr;

        if (!rear){
            front = rear = newNode;
        }
        else{
            if (urgent){
                newNode->next = front;
                front = newNode;
            }
            else{
                rear->next = newNode;
                rear = newNode;
            }
        }
    }

    char *dequeue(){
        if (front){
            Node *temp = front;
            front = front->next;
            char *data = temp->data;
            if (!front)
                rear = nullptr;
            delete temp;
            return data;
        }
        return nullptr;
    }

    bool isEmpty(){
        return front == nullptr;
    }
};

struct Stack{
    struct Node{
        char *data;
        Node *next;
    } *top;

    Stack(){
        top = NULL;
    }

    void push(const char *str){
        Node *newNode = new Node;
        newNode->data = new char[strlen(str) + 1];
        strcpy(newNode->data, str);
        newNode->next = top;
        top = newNode;
    }

    char *pop(){
        if (top){
            Node *temp = top;
            top = top->next;
            char *data = temp->data;
            delete temp;
            return data;
        }
        return nullptr;
    }

    bool isEmpty(){
        return top == nullptr;
    }
};

struct node{
    string locations;
    int time;
    node *next;

    node(string l, int t){
        locations = l;
        time = t;
        next = NULL;
    }
};

class Campus{
    int no_of_locations;
    node **adj_list;
    string *location_names;

public:
    Campus(int n){
        no_of_locations = n;
        adj_list = new node *[no_of_locations];
        location_names = new string[no_of_locations];

        for (int i = 0; i < no_of_locations; i++)
        {
            adj_list[i] = nullptr;
        }
    }

    int hash_strings(string str){  
        int hash_string_val = 0;

        for(int i=0; i<str.length(); i++){
            hash_string_val += str[i];
        }
        return hash_string_val % TABLE_SIZE; 
    } 

    void setLocation(int index, string loc){
        index = hash_strings(loc);
        int og_index = index;
        while (!location_names[index].empty()){
            if (location_names[index] == loc){
                cout << "Location " << loc << " already exists" << endl;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == og_index){
                cout << "HashTable is full! Cannot add location: " << loc << endl;
                return;
            }
        }
        location_names[index] = loc;
    }

    void addPath(string a, string b, int time){
        int indexA = findLocationIndex(a);
        int indexB = findLocationIndex(b);

        if (indexA == -1 || indexB == -1){
            cout << "Error! One or both locations not found: " << a << ", " << b << endl;
            return;
        }

        node *loc1 = new node(b, time);
        loc1->next = adj_list[indexA];
        adj_list[indexA] = loc1;

        node *loc2 = new node(a, time);
        loc2->next = adj_list[indexB];
        adj_list[indexB] = loc2;
    }

    void addNewLocation(){
        string new_location, og_location, response;
        int time;

        cout << "\nEnter new location: ";
        cin.ignore();
        getline(cin, new_location);

        int index = hash_strings(new_location);
        int og_index = index;

        while (!location_names[index].empty()){
            index = (index + 1) % TABLE_SIZE;
            if (index == og_index){
                cout << "HashTable is full! Cannot add location: " << new_location << endl;
                return;
            }
        }
        location_names[index] = new_location;

        while(true){
            cout << "Enter the location to connect to " << new_location << ": ";
            getline(cin, og_location);

            if (findLocationIndex(og_location) == -1){
                cout << "\n\033[31mError! The location "<< og_location << " doesnt exist.\033[0m" << endl;
                continue;
            }

            cout << "Enter the time taken to get to " << new_location << " from " << og_location << ": ";
            cin >> time;
            cin.ignore();

            addPath(new_location, og_location, time);

            cout << "Keep adding more locations? (y/n): ";
            cin >> response;

            if(response == "y" || response == "Y"){
                addNewLocation();
                break;
            }
            else if(response == "N" || response == "n"){
                break;
            }
            else{
                cout << "Invalid response. Please enter a correct response. ";
                continue;
            }
        }
    }

    int findLocationIndex(string loc){  // Find location index in hash table
        int index = hash_strings(loc);
        int original_index = index;

        while (!location_names[index].empty() && location_names[index] != loc){  //as long as you dont find the location or dont hit an empty spot
            index = (index + 1) % TABLE_SIZE;  // Linear probing to resolve collisions
            if (index == original_index){
                return -1;
            }
        }

        if (location_names[index] == loc){
            return index;
        }
        else{
            return -1;
        }
    }

    void findShortestPath(string start_location){
        int start_index = findLocationIndex(start_location);
        if (start_index == -1){
            cout << "\033[31mError! The location " << start_location << " doesn't exist.\033[0m" << endl;
            return;
        }

        int distance[no_of_locations];
        bool visited[no_of_locations] = {false};

        for (int i = 0; i < no_of_locations; i++){
            distance[i] = INT_MAX;
        }

        distance[start_index] = 0;

        for (int count = 0; count < no_of_locations; count++){
            int min_distance = INT_MAX, current_index = -1;
            for (int i = 0; i < no_of_locations; i++){
                if (!visited[i] && distance[i] < min_distance){
                    min_distance = distance[i];
                    current_index = i;
                }
            }
            if (current_index == -1){
                break;
            }

            visited[current_index] = true;

            node *neighbour = adj_list[current_index];
            while (neighbour){
                int neighbour_index = findLocationIndex(neighbour->locations);
                if (!visited[neighbour_index] && distance[current_index] + neighbour->time < distance[neighbour_index]){
                    distance[neighbour_index] = distance[current_index] + neighbour->time;
                }
                neighbour = neighbour->next;
            }
        }

        cout << "\n\033[32mShortest distances from " << start_location << ":\033[0m" << endl;
        for (int i = 0; i < no_of_locations; i++){
            if (!location_names[i].empty()){
                cout << "To\033[33m " << location_names[i] << "\033[0m: ";
                if (distance[i] == INT_MAX){
                    cout << "No direct route" << endl;
                }
                else{
                    cout << distance[i] << " mins" << endl;
                }
            }
        }
    }

    void showConnections(){
        for (int i = 0; i < no_of_locations; i++){
            if (!location_names[i].empty()) {
                cout << "\033[33m" << location_names[i] << "\033[0m is connected with ";
                node *temp = adj_list[i];
                while (temp){
                    cout << "\033[36m" << temp->locations << "\033[0m  (Time: " << temp->time << " mins)";
                    temp = temp->next;
                    if (temp){
                        cout << ", ";
                    }
                }
                cout << endl;
            }
        }
    }
};

int main(){
    cout << endl;
    TreeNode *root = new TreeNode("GIKI", "Main Campus of GIKI Institute");
    root = insert(root, "Admin Block", "Administrative Building for official work", "GIKI");
    root = insert(root, "Sports Ground", "Large ground for sports events", "GIKI");
    root = insert(root, "Sports Complex", "Complex for Sports", "GIKI");
    root = insert(root, "LOGIK", "Famous Clock Tower and symbol of GIKI", "GIKI");
    root = insert(root, "Guest House", "Accommodation for Visitors", "GIKI");
    root = insert(root, "FES", "Faculty of Engineering Sciences", "GIKI");
    root = insert(root, "FCSE", "Faculty of Computer Science & Engineering", "GIKI");
    root = insert(root, "FME", "Faculty of Mechanical Engineering", "GIKI");
    root = insert(root, "ACB", "New Academic Block", "GIKI");
    root = insert(root, "FCE", "Faculty of Chemical Engineering", "GIKI");
    root = insert(root, "Auditorium", "Event Venue", "GIKI");
    root = insert(root, "Medical Center", "Provides healthcare facilities", "GIKI");
    root = insert(root, "Library", "Central library with a vast collection of books", "GIKI");
    root = insert(root, "Brabers Building", "Quiz/Exams Building", "GIKI");
    root = insert(root, "Incubation Center", "Research center", "GIKI");
    root = insert(root, "Faculty Club", "Faculty Lounge", "GIKI");
    root = insert(root, "TUC", "Cafe Area", "GIKI");
    root = insert(root, "HBL Bank", "Habib Bank Limited", "GIKI");
    root = insert(root, "Girls Hostel", "Accommodation for female students", "GIKI");
    root = insert(root, "Boys Hostel", "Accommodation for male students", "GIKI");
    root = insert(root, "Hostel 7", "Old girls hostel", "Girls Hostel");
    root = insert(root, "Hostel 13", "New girls hostel", "Girls Hostel");
    root = insert(root, "Hostel 8", "Old boys hsotel", "Boys Hostel");
    root = insert(root, "Hostel 12", "New boys hostel", "Boys Hostel");
    root = insert(root, "Gym", "Gym inside sports complex for male/female students", "Sports Complex");
    root = insert(root, "Swimming Pool", "Swimming pool for students", "Sports Complex");
    root = insert(root, "Basketball Court", "Indoor basketball court for students", "Sports Complex");
    root = insert(root, "Squash court", "Squash court for students", "Sports Complex");
    root = insert(root, "Mess", "New mess for female students", "Hostel 13");
    root = insert(root, "Common Room", "New common room for female students", "Hostel 13");
    root = insert(root, "Mess", "Old mess for female students", "Hostel 7");
    root = insert(root, "Common Room", "Old common room for female students", "Hostel 7");
    root = insert(root, "Mess", "New mess for male students", "Hostel 12");
    root = insert(root, "Common Room", "New common room for male students", "Hostel 12");
    root = insert(root, "Mess", "Old mess for male students", "Hostel 8");
    root = insert(root, "Common Room", "Old common room for male students", "Hostel 8");
    root = insert(root, "Raju", "Cafe for fast food", "TUC");
    root = insert(root, "Ayaan", "Cafe for desi food", "TUC");
    

    Campus g(50);
    g.setLocation(0, "Main Gate");
    g.setLocation(1, "Academic Block");
    g.setLocation(2, "Library");
    g.setLocation(3, "FES");
    g.setLocation(4, "Central Mess");
    g.setLocation(5, "Sports Ground");
    g.setLocation(6, "Boys Hostels");
    g.setLocation(7, "Incubation Center");
    g.setLocation(8, "Hostel 13");
    g.setLocation(9, "Hiking Track");
    g.setLocation(10, "Auditorium");
    g.setLocation(11, "TUC Area");
    g.setLocation(12, "Habib Bank");
    g.setLocation(13, "Brabers Building");
    g.setLocation(14, "FCSE");
    g.setLocation(15, "Cafe");
    g.setLocation(16, "Guest House");
    g.setLocation(17, "LOGIK");

    g.addPath("Main Gate", "Academic Block", 1);
    g.addPath("Academic Block", "Sports Ground", 1);
    g.addPath("Boys Hostels", "Central Mess", 3);
    g.addPath("FCSE", "FES", 1);
    g.addPath("Brabers Building", "Hostel 13", 2);
    g.addPath("Incubation Center", "Brabers Building", 1);
    g.addPath("Hiking Track", "Library", 6);
    g.addPath("Auditorium", "Main Gate", 1);
    g.addPath("TUC Area", "Habib Bank", 3);
    g.addPath("Brabers Building", "Cafe", 7);
    g.addPath("Brabers Building", "Auditorium", 4);
    g.addPath("Brabers Building", "Hiking Track", 10);
    g.addPath("Guest House", "LOGIK", 10);

    Queue navigationRequests;
    Stack navigationHistory;

    int choice;
    do{
        cout << "\n\033[32mCampus Navigation System\n\033[0m";
        cout << "1. View Campus Hierarchy\n";
        cout << "2. Show Connections among buildings\n";
        cout << "3. Find Shortest Path among buildings\n";
        cout << "4. Add new location\n";
        cout << "5. Add Navigation Request\n";
        cout << "6. Process Navigation Request\n";
        cout << "7. Backtrack Navigation\n";
        cout << "8. Recommend Buildings\n";
        cout << "9. Search\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        


        switch (choice){
        case 1:
            displayTree(root);
            break;
        case 2:
            g.showConnections();
            break;
        case 3:
        {
            string start_location;
            cout << "Enter starting location: ";
            cin.ignore();
            getline(cin, start_location);
            g.findShortestPath(start_location);
            break;
        }
        case 4:
        {
            g.addNewLocation();
            cout << "\n\033[32mYour modified campus structure looks like:\033[0m" << endl;
            g.showConnections();
            break;
        }
        case 5:
        {
            char destination[50];
            bool urgent;
            cout << "Enter destination: ";
            cin.ignore();
            cin.getline(destination, 50);
            cout << "Is this request urgent (1 for yes, 0 for no): ";
            cin >> urgent;
            navigationRequests.enqueue(destination, urgent);
            cout << "Navigation request added." << endl;
            break;
        }
        case 6:
        {
            if (!navigationRequests.isEmpty()){
                char *destination = navigationRequests.dequeue();
                cout << "Processing request to: " << destination << endl;
                navigationHistory.push(destination);
                delete[] destination; // Free the memory allocated by dequeue
            }
            else{
                cout << "No navigation requests to process." << endl;
            }
            break;
        }
        case 7:
        {
            if (!navigationHistory.isEmpty()){
                char *lastLocation = navigationHistory.pop();
                cout << "Backtracking to: " << lastLocation << endl;
                delete[] lastLocation; // Free the memory allocated by pop
            }
            else{
                cout << "No navigation history to backtrack." << endl;
            }
            break;
        }
        case 8:
        {
            string keyword;
            cout << "Enter keyword for building search(sports, health, hostel, cafe): ";
            cin.ignore();
            getline(cin, keyword);
            cout << "\nBuilding matching the keyword: " << keyword << endl;
            recommendBuildings(root, keyword);
            break;
        }
        case 9:
        {
            string searchbuilding;
            cout << "Enter buidling name: ";
            cin.ignore();
            getline(cin, searchbuilding);
            TreeNode *result = search(root, searchbuilding);
            if (result != NULL){
                cout << "Building found" << endl;
                cout << "Name: " << result->name << endl;
                cout << "Info: " << result->info << endl;
            }
            else{
                cout << "Building not found" << endl;
            }
            break;
        }
        case 0:
            cout << "\033[32mExiting Campus Navigation System. Goodbye!\033[0m" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
    }while (choice != 0);
}
