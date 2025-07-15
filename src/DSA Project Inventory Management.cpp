#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

class Product {
    int id, quantity;
    string name;
    float price;
    Product* next;

public:
    Product(int ID, const string& n, float p, int q) {
        id = ID;
        name = n;
        price = p;
        quantity = q;
        next = nullptr;
    }

    void setNext(Product* product) {
        next = product;
    }

    Product* getNext() const {
        return next;
    }

    int getID() const {
        return id;
    }

    void setID(int newID) {
        id = newID;
    }

    string getName() const {
        return name;
    }

    void setName(const string& newName) {
        name = newName;
    }

    float getPrice() const {
        return price;
    }

    void setPrice(float newPrice) {
        price = newPrice;
    }

    int getQuantity() const {
        return quantity;
    }

    void setQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    float getValue() const {
        return price * quantity;
    }
};
class User {
    string username;
    string password;
    string role;

public:
    User() {}

    User(const string& u_name, const string& pass, const string& r) {
        username = u_name;
        password = pass;
        role = r;
    }

    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }

    string getRole() const {
        return role;
    }
};

class UserNode {
    User user;
    UserNode* next;

public:
    UserNode(const User& u) {
        user = u;
        next = nullptr;
    }

    void setNext(UserNode* node) {
        next = node;
    }

    UserNode* getNext() const {
        return next;
    }

    User getUser() const {
        return user;
    }
};

class UserList {
    UserNode* head;

public:
    UserList() {
        head = nullptr;
    }

    void addUser(const User& user) {
        UserNode* newNode = new UserNode(user);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            UserNode* current = head;
            while (current->getNext() != nullptr) {
                current = current->getNext();
            }
            current->setNext(newNode);
        }
    }

    UserNode* getHead() const {
        return head;
    }
};

Product* products = nullptr;
int productCount = 0;
UserList users;

void saveDataToFile() {
    ofstream file("products.txt");
    if (file.is_open()) {
        Product* current = products;
        while (current != nullptr) {
            file << current->getID() << " "
                << current->getName() << " "
                << current->getPrice() << " "
                << current->getQuantity() << endl;
            current = current->getNext();
        }
        file.close();
        cout << "Data saved to file." << endl;
    }
    else {
        cout << "Unable to open file." << endl;
    }
}

void loadDataFromFile() {
    ifstream file("products.txt");
    if (file.is_open()) {
        productCount = 0;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int id, quantity;
            string name;
            float price;
            if (ss >> id >> name >> price >> quantity) {
                Product* product = new Product(id, name, price, quantity);
                if (products == nullptr) {
                    products = product;
                }
                else {
                    Product* current = products;
                    while (current->getNext() != nullptr) {
                        current = current->getNext();
                    }
                    current->setNext(product);
                }
                productCount++;
            }
        }
        file.close();
        cout << "Data loaded from file." << endl;
    }
    else {
        cout << "Unable to open file." << endl;
    }
}

void addProduct(const User& user) {
    system("cls");
    cout << "How many products do you want to enter? ";
    int count;
    cin >> count;
    for (int i = 0; i < count; i++) {
        int id, quantity;
        float price;
        string name;

        cout << "\nEnter Product " << i + 1 << ":-";
        cout << "\nEnter ID: ";
        cin >> id;

        bool duplicateID = false;
        Product* current = products;
        while (current != nullptr) {
            if (current->getID() == id) {
                duplicateID = true;
                cout << "Product with the same ID already exists. Please enter a different ID." << endl;
                break;
            }
            current = current->getNext();
        }

        if (!duplicateID) {
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Price: ";
            cin >> price;
            cout << "Enter Quantity: ";
            cin >> quantity;

            Product* product = new Product(id, name, price, quantity);
            if (products == nullptr) {
                products = product;
            }
            else {
                Product* current = products;
                while (current->getNext() != nullptr) {
                    current = current->getNext();
                }
                current->setNext(product);
            }

            productCount++;
        }
    }

    saveDataToFile();
    cout << "Product(s) added successfully." << endl;
    system("pause");
}

void editProduct(const User& user) {
    system("cls");
    int id;
    cout << "Enter the ID of the product to edit: ";
    cin >> id;

    Product* current = products;
    while (current != nullptr) {
        if (current->getID() == id) {
            float price;
            int quantity;

            cout << "Enter new price: ";
            cin >> price;
            current->setPrice(price);

            cout << "Enter new quantity: ";
            cin >> quantity;
            current->setQuantity(quantity);

            cout << "Product edited successfully." << endl;
            saveDataToFile();
            system("pause");
            return;
        }
        current = current->getNext();
    }

    cout << "Product with ID " << id << " not found." << endl;
    system("pause");
}

void deleteProduct(int id) {
    Product* current = products;
    Product* previous = nullptr;

    while (current != nullptr) {
        if (current->getID() == id) {
            if (previous == nullptr) {
                products = current->getNext();
            }
            else {
                previous->setNext(current->getNext());
            }

            delete current;
            productCount--;
            cout << "Product with ID " << id << " deleted successfully." << endl;
            saveDataToFile();
            system("pause");
            return;
        }

        previous = current;
        current = current->getNext();
    }

    cout << "Product with ID " << id << " not found." << endl;
    system("pause");
}
void sortByID() {
    bool swapped;
    Product* current;
    Product* last = nullptr;

    do {
        swapped = false;
        current = products;

        while (current->getNext() != last) {
            if (current->getID() > current->getNext()->getID()) {
                int tempID = current->getID();
                string tempName = current->getName();
                float tempPrice = current->getPrice();
                int tempQuantity = current->getQuantity();

                current->setID(current->getNext()->getID());
                current->setName(current->getNext()->getName());
                current->setPrice(current->getNext()->getPrice());
                current->setQuantity(current->getNext()->getQuantity());

                current->getNext()->setID(tempID);
                current->getNext()->setName(tempName);
                current->getNext()->setPrice(tempPrice);
                current->getNext()->setQuantity(tempQuantity);

                swapped = true;
            }
            current = current->getNext();
        }
        last = current;
    } while (swapped);
}
void displaySortedProducts() {
    sortByID();

    system("cls");
    if (productCount == 0) {
        cout << "No products found." << endl;
    }
    else {
        cout << "Product List (Sorted by ID):" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------" << endl;
        cout << "ID\tName\t\tPrice\tQuantity\tValue" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------" << endl;
        Product* currentProduct = products;
        while (currentProduct != nullptr) {
            cout << currentProduct->getID() << "\t" << currentProduct->getName() << "\t\t" << currentProduct->getPrice() << "\t" << currentProduct->getQuantity() << "\t\t" << currentProduct->getValue() << endl;
            currentProduct = currentProduct->getNext();
        }
        cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    }
    system("pause");
}
void sortByPrice() {
    bool swapped;
    Product* current;
    Product* last = nullptr;

    do {
        swapped = false;
        current = products;

        while (current->getNext() != last) {
            if (current->getPrice() > current->getNext()->getPrice()) {
                int tempID = current->getID();
                string tempName = current->getName();
                float tempPrice = current->getPrice();
                int tempQuantity = current->getQuantity();

                current->setID(current->getNext()->getID());
                current->setName(current->getNext()->getName());
                current->setPrice(current->getNext()->getPrice());
                current->setQuantity(current->getNext()->getQuantity());

                current->getNext()->setID(tempID);
                current->getNext()->setName(tempName);
                current->getNext()->setPrice(tempPrice);
                current->getNext()->setQuantity(tempQuantity);

                swapped = true;
            }
            current = current->getNext();
        }
        last = current;
    } while (swapped);
}
void displaySortedByPriceProducts() {
    sortByPrice();

    system("cls");
    if (productCount == 0) {
        cout << "No products found." << endl;
    }
    else {
        cout << "Product List (Sorted by Price - Low to High):" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------" << endl;
        cout << "ID\tName\t\tPrice\tQuantity\tValue" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------" << endl;
        Product* currentProduct = products;
        while (currentProduct != nullptr) {
            cout << currentProduct->getID() << "\t" << currentProduct->getName() << "\t\t" << currentProduct->getPrice() << "\t" << currentProduct->getQuantity() << "\t\t" << currentProduct->getValue() << endl;
            currentProduct = currentProduct->getNext();
        }
        cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    }
    system("pause");
}
void sortByPriceHighToLow() {
    bool swapped;
    Product* current;
    Product* last = nullptr;

    do {
        swapped = false;
        current = products;

        while (current->getNext() != last) {
            if (current->getPrice() < current->getNext()->getPrice()) {
                int tempID = current->getID();
                string tempName = current->getName();
                float tempPrice = current->getPrice();
                int tempQuantity = current->getQuantity();

                current->setID(current->getNext()->getID());
                current->setName(current->getNext()->getName());
                current->setPrice(current->getNext()->getPrice());
                current->setQuantity(current->getNext()->getQuantity());

                current->getNext()->setID(tempID);
                current->getNext()->setName(tempName);
                current->getNext()->setPrice(tempPrice);
                current->getNext()->setQuantity(tempQuantity);

                swapped = true;
            }
            current = current->getNext();
        }
        last = current;
    } while (swapped);
}
void displaySortedByPriceHighToLowProducts() {
    sortByPriceHighToLow();

    system("cls");
    if (productCount == 0) {
        cout << "No products found." << endl;
    }
    else {
        cout << "Product List (Sorted by Price - High to Low):" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------" << endl;
        cout << "ID\tName\t\tPrice\tQuantity\tValue" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------" << endl;
        Product* currentProduct = products;
        while (currentProduct != nullptr) {
            cout << currentProduct->getID() << "\t" << currentProduct->getName() << "\t\t" << currentProduct->getPrice() << "\t" << currentProduct->getQuantity() << "\t\t" << currentProduct->getValue() << endl;
            currentProduct = currentProduct->getNext();
        }
        cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    }
    system("pause");
}
void searchProduct() {
    system("cls");
    if (productCount == 0) {
        cout << "No products found." << endl;
    }
    else {
        string searchTerm;
        cout << "Enter the product name or ID to search: ";
        cin.ignore();
        getline(cin, searchTerm);

        bool found = false;
        Product* currentProduct = products;
        while (currentProduct != nullptr) {
            if (currentProduct->getName().find(searchTerm) != string::npos || to_string(currentProduct->getID()) == searchTerm) {
                if (!found) {
                    cout << "Search Results:" << endl;
                    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
                    cout << "ID\tName\t\tPrice\tQuantity\tValue" << endl;
                    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
                    found = true;
                }
                cout << currentProduct->getID() << "\t" << currentProduct->getName() << "\t\t" << currentProduct->getPrice() << "\t" << currentProduct->getQuantity() << "\t\t" << currentProduct->getValue() << endl;
            }
            currentProduct = currentProduct->getNext();
        }

        if (!found) {
            cout << "No matching products found." << endl;
        }
        cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    }
    system("pause");
}

void displayProducts() {
    system("cls");
    if (productCount == 0) {
        cout << "No products found." << endl;
    }
    else {
        bool swapped;
        Product* current;
        Product* last = nullptr;

        do {
            swapped = false;
            current = products;

            while (current->getNext() != last) {
                if (current->getName() > current->getNext()->getName()) {
                    int tempID = current->getID();
                    string tempName = current->getName();
                    float tempPrice = current->getPrice();
                    int tempQuantity = current->getQuantity();

                    current->setID(current->getNext()->getID());
                    current->setName(current->getNext()->getName());
                    current->setPrice(current->getNext()->getPrice());
                    current->setQuantity(current->getNext()->getQuantity());

                    current->getNext()->setID(tempID);
                    current->getNext()->setName(tempName);
                    current->getNext()->setPrice(tempPrice);
                    current->getNext()->setQuantity(tempQuantity);

                    swapped = true;
                }
                current = current->getNext();
            }
            last = current;
        } while (swapped);

        cout << "Product List:" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------" << endl;
        cout << "ID\tName\t\tPrice\tQuantity\tValue" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------" << endl;
        Product* currentProduct = products;
        while (currentProduct != nullptr) {
            cout << currentProduct->getID() << "\t" << currentProduct->getName() << "\t\t" << currentProduct->getPrice() << "\t" << currentProduct->getQuantity() << "\t\t" << currentProduct->getValue() << endl;
            currentProduct = currentProduct->getNext();
        }
        cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    }
    int ch;
    cout << "Do you want to sort Products\n1)by ID \n2)by Price Low to High\n3)by Price High to Low\n4)if you don't want to sort\n Enter :  ";
    cin >> ch;
    if (ch == 1) {
        displaySortedProducts();
    }
    else if (ch == 2 ) {
        displaySortedByPriceProducts();
    }
    else if (ch == 3) {
        displaySortedByPriceHighToLowProducts();
    }
    else {
    	 system("pause");
	}
}
int main() {
    loadDataFromFile();
    users.addUser(User("admin", "admin123", "admin"));
    users.addUser(User("user", "user123", "user"));
    

    string username, password;
    cout << "Login" << endl;
    cout << "-------------------" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    bool loggedIn = false;
    User currentUser("", "", "");

    UserNode* userNode = users.getHead();
    while (userNode != nullptr) {
        User user = userNode->getUser();
        if (user.getUsername() == username && user.getPassword() == password) {
            loggedIn = true;
            currentUser = user;
            break;
        }
        userNode = userNode->getNext();
    }

    if (loggedIn) {
        cout << "Login successful!" << endl;
        cout << "Welcome, " << currentUser.getUsername() << "!" << endl;

		Sleep(3000);  // Delay for 5000 milliseconds = 5 seconds
		
        if (currentUser.getRole() == "admin") {
            int choice;
            do {
                system("cls");
                cout << "Admin Menu" << endl;
                cout << "-------------------" << endl;
                cout << "1. Add Product" << endl;
                cout << "2. Display Products" << endl;
                cout << "3. Edit Product" << endl;
                cout << "4. Delete Product" << endl;
                cout << "5. Search Product"<<endl;
                cout << "6. Exit" << endl;
                cout << "-------------------" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        addProduct(currentUser);
                        break;
                    case 2:
                        displayProducts();
                        break;
                    case 3:
                        editProduct(currentUser);
                        break;
                    case 4:
                        int deleteID;
                        cout << "Enter the ID of the product to delete: ";
                        cin >> deleteID;
                        deleteProduct(deleteID);
                        break;
                    case 5:
                    	searchProduct();
                    case 6:
                        cout << "Exiting..." << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
            } while (choice != 6);
        }
        else {
            displayProducts();
        }
    }
    else {
        cout << "Invalid username or password. Login failed." << endl;
    }

    return 0;
}

