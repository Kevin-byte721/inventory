#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

const int MAX_ITEMS = 100; // Define a maximum number of items

class Item {
private:
    int productID;
    string name;
    int quantity;
    double price;
    string category;

public:
    Item(int id, string n, int q, double p, string cat) {
        productID = id;
        name = n;
        quantity = q;
        price = p;
        category = cat;
    }

    Item() {
        productID = 0;
        name = "";
        quantity = 0;
        price = 0.0;
        category = "";
    } 

    int getProductID() const { return productID; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    string getCategory() const { return category; }

    void setQuantity(int q) { quantity = q; }
    void setPrice(double p) { price = p; }

    void displayItem() const {
        cout << setw(10) << productID << setw(20) << name << setw(10) << quantity
             << setw(10) << fixed << setprecision(2) << price << setw(20) << category << endl;
    }
};

void addItem(Item inventory[], int& itemCount, int& nextID) {
    if (itemCount >= MAX_ITEMS) {
        cout << "Inventory is full!" << endl;
        return;
    }

    string name, category;
    int quantity;
    double price;

    cout << "Enter item name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter item category: ";
    getline(cin, category);

    cout << "Enter quantity: ";
    cin >> quantity;

    cout << "Enter price: ";
    cin >> price;

    inventory[itemCount] = Item(nextID, name, quantity, price, category);
    itemCount++;
    nextID++;

    cout << "Item added successfully!" << endl;
}

void updateItem(Item inventory[], int itemCount) {
    int productID;
    cout << "Enter product ID to update: ";
    cin >> productID;

    for (int i = 0; i < itemCount; ++i) {
        if (inventory[i].getProductID() == productID) {
            cout << "Update quantity or price? (q/p): ";
            char choice;
            cin >> choice;

            if (choice == 'q') {
                int newQuantity;
                cout << "Enter new quantity: ";
                cin >> newQuantity;
                int oldQuantity = inventory[i].getQuantity();
                inventory[i].setQuantity(newQuantity);
                cout << "Quantity of Item " << inventory[i].getName() << " is updated from "
                     << oldQuantity << " to " << newQuantity << endl;
            } else if (choice == 'p') {
                double newPrice;
                cout << "Enter new price: ";
                cin >> newPrice;
                double oldPrice = inventory[i].getPrice();
                inventory[i].setPrice(newPrice);
                cout << "Price of Item " << inventory[i].getName() << " is updated from "
                     << oldPrice << " to " << newPrice << endl;
            } else {
                cout << "Invalid choice." << endl;
            }
            return;
        }
    }
    cout << "Item not found!" << endl;
}

void removeItem(Item inventory[], int& itemCount) {
    int productID;
    cout << "Enter product ID to remove: ";
    cin >> productID;

    for (int i = 0; i < itemCount; ++i) {
        if (inventory[i].getProductID() == productID) {
            cout << "Item " << inventory[i].getName() << " has been removed from the inventory" << endl;

            for (int j = i; j < itemCount - 1; ++j) {
                inventory[j] = inventory[j + 1];
            }
            itemCount--;
            return;
        }
    }
    cout << "Item not found!" << endl;
}

void displayAllItems(const Item inventory[], int itemCount) {
    cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity"
         << setw(10) << "Price" << setw(20) << "Category" << endl;
    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

    for (int i = 0; i < itemCount; ++i) {
        inventory[i].displayItem();
    }
}

void searchItem(const Item inventory[], int itemCount) {
    int productID;
    cout << "Enter product ID to search: ";
    cin >> productID;

    for (int i = 0; i < itemCount; ++i) {
        if (inventory[i].getProductID() == productID) {
            cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity"
                 << setw(10) << "Price" << setw(20) << "Category" << endl;
            cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;
            inventory[i].displayItem();
            return;
        }
    }
    cout << "Item not found!" << endl;
}

void sortItems(Item inventory[], int itemCount) {
    char choice;
    cout << "Sort by quantity or price? (q/p): ";
    cin >> choice;

    char order;
    cout << "Ascending or descending? (a/d): ";
    cin >> order;

    if (choice == 'q') {
        if (order == 'a') {
            sort(inventory, inventory + itemCount, [](const Item& a, const Item& b) {
                return a.getQuantity() < b.getQuantity();
            });
        } else if (order == 'd') {
            sort(inventory, inventory + itemCount, [](const Item& a, const Item& b) {
                return a.getQuantity() > b.getQuantity();
            });
        }
    } else if (choice == 'p') {
        if (order == 'a') {
            sort(inventory, inventory + itemCount, [](const Item& a, const Item& b) {
                return a.getPrice() < b.getPrice();
            });
        } else if (order == 'd') {
            sort(inventory, inventory + itemCount, [](const Item& a, const Item& b) {
                return a.getPrice() > b.getPrice();
            });
        }
    }

    cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity"
         << setw(10) << "Price" << endl;
    cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
    for (int i = 0; i < itemCount; ++i) {
        cout << setw(10) << inventory[i].getProductID() << setw(20) << inventory[i].getName()
             << setw(10) << inventory[i].getQuantity() << setw(10) << fixed << setprecision(2) << inventory[i].getPrice() << endl;
    }
}

void displayLowStockItems(const Item inventory[], int itemCount) {
    cout << "Low Stock Items (Quantity <= 5):" << endl;
    cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity"
         << setw(10) << "Price" << setw(20) << "Category" << endl;
    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

    for (int i = 0; i < itemCount; ++i) {
        if (inventory[i].getQuantity() <= 5) {
            inventory[i].displayItem();
        }
    }
}

int main() {
    Item inventory[MAX_ITEMS];
    int itemCount = 0;
    int nextID = 1;

    int choice;
    do {
        cout << "\nMenu" << endl;
        cout << "1- Add Item" << endl;
        cout << "2- Update Item" << endl;
        cout << "3- Remove Item" << endl;
        cout << "4- Display All Items" << endl;
        cout << "5- Search Item" << endl;
        cout << "6- Sort Items" << endl;
        cout << "7- Display Low Stock Items" << endl;
        cout << "8- Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addItem(inventory, itemCount, nextID);
                break;
            case 2:
                updateItem(inventory, itemCount);
                break;
            case 3:
                removeItem(inventory, itemCount);
                break;
            case 4:
                displayAllItems(inventory, itemCount);
                break;
            case 5:
                searchItem(inventory, itemCount);
                break;
            case 6:
                sortItems(inventory, itemCount);
                break;
            case 7:
                displayLowStockItems(inventory, itemCount);
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}