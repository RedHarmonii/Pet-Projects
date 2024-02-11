/*
    Name: Saurav Kumar, 8000658229, Section 1002, AS#8
    Description: Using a doubly linked list connected 4 ways, forming a
    grid, search for a target node
    Input: User inputs three option when running the program which is 
    the matrix length,width, and a number used to generate random seed
    Output: Prints the matrix and then searches for the target node and
    prints either the coordinates or number of steps the algorithm took
*/
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <unordered_set>

using std::cout;
const int LIMIT = 10'000;
/// @brief Node class: each node has a string 3 charachters long and 
/// connects to four different directions
class Node{
    public:
    //constructor to set the string
    //also sets the the four directions to nullptr
    Node(std::string name){
        this->word = name;
        this->left = nullptr;
        this->up = nullptr;
        this->right = nullptr;
        this->down = nullptr;
    }
    friend Node* RNGdirection(Node *curr);
    Node*left;
    Node*up;
    Node*right;
    Node*down;
    std::string word;
};

/// @brief Linked List class: contains a pointer that has a reference 
/// to the remainder of the grid based linked list.
class LinkedList{
    Node*head;
    public:
    LinkedList(int length, int width);
    ~LinkedList();
    static std::string RNGString();
    void print();
    int traceTheCall(int mode);
    friend void breadthFirstSearch(Node* head);
};

Node* RNGdirection(Node *curr){
    Node* newCurr = nullptr;
    //print out which one we took too so we can see it trying lol
    int direction = rand() % 4; //0,1,2,3 (up,down,left,right)
    switch(direction){
    case 0: cout << "u,"; //up
        newCurr = curr->up; break;
    case 1: cout << "d,"; //down
        newCurr = curr->down; break;
    case 2: cout << "l,"; //left
        newCurr = curr->left; break;
    case 3: cout << "r,"; //right
        newCurr = curr->right; break;
    }
    if(!newCurr) return RNGdirection(curr);
    return newCurr;
}

/// @brief This function randomly picks a lowercase character and
/// stores the character in a string 3 times.
/// @return returns a string with size 3
std::string LinkedList::RNGString(){
    std::string temp;
    // char will always be 'a' plus 0 : 26 which will modify the 'a'
    // from a to z
    temp = 'a' + rand() % 26;
    temp += 'a' + rand() % 26;
    temp += 'a' + rand() % 26;
    return temp;
}

/// @brief Constructor for grid-based doubly linked list. head points to
/// the very first node on the top left and then makes connections with
/// all other nodes within length and width
/// @param length max number of rows in linked list
/// @param width max number of nodes in each row
LinkedList::LinkedList(int length, int width){
    // If length or width is zero, no list will be created and head
    // will point to nullptr and exit the constructor
    if(length <= 0 || width <= 0){
        head = nullptr;
        return;
    }
    // ramdomly pick a location in the linked list to store "neo"
    int x,y = 0;
    x = rand() % length;
    y = rand() % width;

    Node*above = nullptr;  //keeps track of any node above current node
    Node*curr = nullptr;   //current node being set
    Node*start = nullptr;  //first node of every row
    for(int i = 0; i < length;i++){
        for(int j = 0; j < width; j++){
            // temp node that will be assigned to curr
            Node*temp = new Node(RNGString());
            if(j == 0){
                above = start;
                start = temp;
            }
            // Runs for all rows except the first
            if(i >= 1 && above != nullptr){
                
                temp->up = above;
                above->down = temp;
                above = above->right;
            }
            // Only runs very first time
            if(curr == above && i == 0 && j == 0){
                // setting head to first Node
                head = temp;
            }
            // makes all left and right connections
            if(start != temp){
                curr->right = temp;
                temp->left = curr;
            }
            // place neo
            if(i == x && j == y){
                temp->word = "neo";
            }
            // keep track of the code just built
            curr = temp;
        }
    }
}

/// @brief deconstructor, deletes all nodes beganning from top left 
/// to bottom right in a snake pattern
LinkedList::~LinkedList(){
    // temp used to copy the refernece to beginning of the list
    Node*temp = head;
    // keeps track of the first node of every row
    Node*nextRow = head;
    while(nextRow){
        nextRow = nextRow->down;
        while(temp){
            Node*dispose = temp;
            temp = temp->right;
            delete dispose;
        }
        temp = nextRow;
    }
}

/// @brief prints the linked list, deletes all nodes beganning from 
/// top left to bottom right in a snake pattern
void LinkedList::print(){
    // temp used to copy the refernece to beginning of the list
    Node*temp = head;
    // keeps track of the first node of every row
    Node*nextRow = head;
    while(nextRow){
        nextRow = nextRow->down;
        while(temp){
            cout << temp->word << ' ';
            temp = temp->right;
        }
        cout << '\n';
        temp = nextRow;
    }
}

void breadthFirstSearch(Node* head){
    std::queue<Node*>q;              //queue for nodes inside the grid
    std::unordered_set<Node*>seen;   // cache of previously nodes searched
    int compares = 0;                // numbe of compares

    q.push(head);
    seen.insert(head);

    while(!q.empty()){
        Node*temp = q.front();
        q.pop();
        Node* neighbors[4] = {temp->right,temp->down,temp->left,temp->up};
        
        compares++;
        if(temp->word == "neo"){
            cout << "\n2: Trace Successful by " << compares 
                << " Compares...\n";
            return;
        }else{
            for(auto neighbor:neighbors){
                if(neighbor != nullptr && seen.find(neighbor) == seen.end()){
                    q.push(neighbor);
                    seen.insert(neighbor);
                }
            }
        }
    }
    cout << "2: Trace Failed.\n";
    return;
}

/// @brief this function traverses the linke list in search of "neo".
/// Depending on the mode of search, If user states 0, this function
/// will conduct a linear search and search every node from top left
/// to bottom right. If user states 1, this function will conduct a
/// random search in four directions and repeat the process until
/// neo is found.
/// @param mode int to specify the search mode
/// @return 0 if search is successful, else prints an error message
int LinkedList::traceTheCall(int mode){

    // anything beside 0 or 1 is passed
    if(mode < 0 || mode > 2){
        cout << mode << ": Unknown Trace Mode.\n";
        return 0;
    }
    // if a linked list was never created due to length or width being 0
    if(head == nullptr){
        cout << mode << ": Trace Failed.\n";
        return 0;
    }
    // row and col used to display the coordinates of "neo"
    int col = 0;
    int row = 0;
    // total number of nodes looked at
    int compares = 0;
    Node*temp = head;
    Node*nextRow = head;
    if(mode == 0){
        // linear search
        while(nextRow){
            nextRow = nextRow->down;
            while(temp){
                compares++;
                if(temp->word == "neo"){
                    cout << "0: Trace Successful at Coordinates (" << row
                    <<", " << col <<") by "<< compares<<" Compares...\n";
                    return 0;
                }
                temp = temp->right;
                col++;
            }
            temp = nextRow;
            col = 0;
            row++;
        }
        cout << "0: Trace Failed.\n";
    }
    else if(mode == 1){
        // random search
        while(compares <= LIMIT){
            compares++;
            if(temp->word == "neo"){
                cout << "\n1: Trace Successful by " << compares 
                << " Compares...\n";
                return 0;
            }
            temp = RNGdirection(temp);
        }
        cout << "1: Trace Failed.\n";
    }else{
        breadthFirstSearch(head);
    }
    return 0;
}