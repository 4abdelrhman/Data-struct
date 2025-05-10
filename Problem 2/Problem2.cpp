#include<iostream>
#include<cstring>
#include<iomanip>
#include<fstream>
using namespace std;

struct Contact{
    char name[100];
    char email[100];
    char phone[100];

    Contact(){
        name[0] = phone[0] = email[0] = '\0';
    }

    Contact(const char* n,const char* p,const char* e ){
        strcpy(name, n);
        strcpy(phone, p);
        strcpy(email, e);
    }

    void display(int id) const{
        cout << "ID: "<< id << "\nName: " << name<<
        "\nPhone: " << phone << "\nEmail: " << email << "\n";
    }
};

struct Node{
    int data;
    Node* left;
    Node* right;
    Contact contact;
    int height;

    Node(int id, const Contact& c){
        data = id;
        contact = c;
        height = 1;
        left = right = nullptr; 
    }
};

class AVLtree{
private:
    Node* root;

    int height(Node* n){
        return n ? n->height : 0;
    }

    int balanceFac(Node* n){
        return n ? height(n->left) - height(n->right) : 0;
    }

    void updateHeight(Node* n){
        n->height = 1 + max(height(n->left), height(n->right));
    }

    Node* rotateRight(Node* y){
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);
        return x; 
    }

    Node* rotateLeft(Node* x){
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* balance(Node* n){
        updateHeight(n);
        int bf = balanceFac(n);
        if(bf > 1){
            if(balanceFac(n->left) < 0){
                n->left = rotateLeft(n->left);
            }
            return rotateRight(n);
        }else if(bf < -1){
            if(balanceFac(n->right) > 0){
                n->right = rotateRight(n->right);
            }
            return rotateLeft(n);
        }
        return n;
    }

    Node* add(Node* n, int id, const Contact& c,bool& success){
        if(!n){
            success = true;
            return new Node(id,c);
        }
        if(id < n->data){
            n->left = add(n->left , id, c , success);
        }else if(id > n->data){
            n->right = add(n->right, id , c , success);
        }else{
            success = false;
            return n;
        }
        return balance(n);
    }
    
    Node* minValueNode(Node* n) {
        Node* current = n;
        while (current->left)
            current = current->left;
        return current;
    }


    Node* deleteNode(Node* n, int id, bool& deleted){
        if(!n) return nullptr;
        if(id < n->data){
            n->left = deleteNode(n->left, id, deleted);
        }else if( id > n-> data) {
            n->right = deleteNode(n->right,id,deleted);
        }else{
            deleted = true;
            if(!n->left || !n->right){
                Node* temp = n->left ? n->left : n->right;
                delete n;
                return temp;
            }else{
                Node* temp = minValueNode(n->right);
                n->data = temp->data;
                n->contact = temp->contact;
                n->right = deleteNode(n->right, temp->data,deleted);
            }
        }
        return balance(n);
        
    }

    Node* search(Node* n, int id) const{
        if(!n) return nullptr;
        if(id == n->data) return n;
        if(id < n->data) return search(n->left, id);

        return search(n->right, id);
    }

    void inOrder(Node* n) const{
        if(!n) return;
        inOrder(n->left);
        n->contact.display(n->data);
        cout << "--------------------------\n";
        inOrder(n->right);
    }



    void displayTree(Node* n, int space = 0,int indent = 5) const {
        if(!n) return;
        
        displayTree(n->right, space + indent);
        
        cout << setw(space) << n->data << "\n";
        
        displayTree(n->left, space + indent);
    }
    void freeMemory(Node* n){
        if(!n) return;
        freeMemory(n->left);
        freeMemory(n->right);
        delete n;
    }

public:
    AVLtree() : root(nullptr){}
    ~AVLtree(){
        freeMemory(root);
    }

    void addContact(int id, const Contact& c){
        bool success = false;
        root = add(root, id, c, success);
        if(success) cout << "Contact added successfully.\n";
        else cout << "Error: Contact With ID: " << id << " already exist.\n";
    }

    void deleteContact(int id){
        bool deleted = false;
        root = deleteNode(root, id, deleted);
        if(deleted) cout << "Contact deleted successfully";
        else cout <<"Contact not found.\n";
    }

    void searchContact(int id) const {
        Node* result = search(root,id);
        if(result){
            cout << "Contact found:\n";
            result->contact.display(id);
        }else{
            cout << "Contact not found.\n";
        }
    }

    void listContacts() const{
        if(!root){
            cout <<"Address Book is empty.\n";
        }else{
            cout<<"Contact in Address Book(STORED BY ID):\n";
            inOrder(root);
        }
    }

    void showTree() const {
        if(!root){
            cout << "Address Book is empty.\n";
        }else{
            cout << "Current AVL Tree:\n";
            displayTree(root);
        }
    }
};

class app{
private:
    AVLtree tree;
public:
    void run(){
        int choice;
        while (true) {
            cout << "\n\nAddress Book Application\n------------------------\n";
            cout << "1. Add New Contact\n";
            cout << "2. Search for Contact\n";
            cout << "3. Delete Contact (Optional)\n";
            cout << "4. List All Contacts (Sorted by ID)\n";
            cout << "5. Display Current Tree Structure\n";
            cout << "6. Exit\n";
            cout << "------------------------\n";
            cout << "Enter operation (1-6): ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) handleAdd();
            else if (choice == 2) handleSearch();
            else if (choice == 3) handleDelete();
            else if (choice == 4) tree.listContacts();
            else if (choice == 5) tree.showTree();
            else if (choice == 6) {
                cout << "Thank You for using the APP.\n" << "Exiting...";
                break;
            }
            else cout << "Invalid option.\n";
        }
    }

    void handleAdd() {
        ifstream file("contact.txt");
        if(!file){
            cout << "Error: Couldn't open the file.";
            return;
        }


        int id;
        char name[100], phone[20], email[100];
        while(file >> id){
        file.ignore();
        file.getline(name, 100);
        file.getline(phone, 20);
        file.getline(email, 100);
        Contact c(name, phone, email);
        tree.addContact(id, c);
        }
    }

    void handleSearch() {
        int id;
        cout << "Enter ID to search: ";
        cin >> id;
        tree.searchContact(id);
    }

    void handleDelete() {
        int id;
        cout << "Enter ID to delete: ";
        cin >> id;
        tree.deleteContact(id);
    }
};

int main(){
    app app;
    app.run();
    return 0;
}