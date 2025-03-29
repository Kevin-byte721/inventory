#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

class Item {
private:
    int productID;
    string name;
    int quantity;
    double price;
    string category;

public:
    Item(int id, string n, int q, double p, string cat) : productID(id), name(n), quantity(q), price(p), category(cat) {}

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

void addItem(vector<Item>& inventory, int& nextID) {
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

    Item newItem(nextID, name, quantity, price, category);
    inventory.push_back(newItem);
    nextID++;

    cout << "Item added successfully!" << endl;
}

void updateItem(vector<Item>& inventory) {
    int productID;
    cout << "Enter product ID to update: ";
    cin >> productID;

    for (auto& item : inventory) {
        if (item.getProductID() == productID) {
            cout << "Update quantity or price? (q/p): ";
            char choice;
            cin >> choice;

            if (choice == 'q') {
                int newQuantity;
                cout << "Enter new quantity: ";
                cin >> newQuantity;
                int oldQuantity = item.getQuantity();
                item.setQuantity(newQuantity);
                cout << "Quantity of Item " << item.getName() << " is updated from "
                     << oldQuantity << " to " << newQuantity << endl;
            } else if (choice == 'p') {
                double newPrice;
                cout << "Enter new price: ";
                cin >> newPrice;
                double oldPrice = item.getPrice();
                item.setPrice(newPrice);
                cout << "Price of Item " << item.getName() << " is updated from "
                     << oldPrice << " to " << newPrice << endl;
            } else {
                cout << "Invalid choice." << endl;
            }
            return;
        }
    }
    cout << "Item not found!" << endl;
}

void removeItem(vector<Item>& inventory) {
    int productID;
    cout << "Enter product ID to remove: ";
    cin >> productID;

    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->getProductID() == productID) {
            cout << "Item " << it->getName() << " has been removed from the inventory" << endl;
            inventory.erase(it);
            return;
        }
    }
    cout << "Item not found!" << endl;
}

void displayAllItems(const vector<Item>& inventory) {
    cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity"
         << setw(10) << "Price" << setw(20) << "Category" << endl;
    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

    for (const auto& item : inventory) {
        item.displayItem();
    }
}

void searchItem(const vector<Item>& inventory) {
    int productID;
    cout << "Enter product ID to search: ";
    cin >> productID;

    for (const auto& item : inventory) {
        if (item.getProductID() == productID) {
            cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity"
                 << setw(10) << "Price" << setw(20) << "Category" << endl;
            cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;
            item.displayItem();
            return;
        }
    }
    cout << "Item not found!" << endl;
}

void sortItems(vector<Item>& inventory) {
    char choice;
    cout << "Sort by quantity or price? (q/p): ";
    cin >> choice;

    char order;
    cout << "Ascending or descending? (a/d): ";
    cin >> order;

    if (choice == 'q') {
        if (order == 'a') {
            sort(inventory.begin(), inventory.end(), [](const Item& a, const Item& b) {
                return a.getQuantity() < b.getQuantity();
            });
        } else if (order == 'd') {
            sort(inventory.begin(), inventory.end(), [](const Item& a, const Item& b) {
                return a.getQuantity() > b.getQuantity();
            });
        } else {
            cout << "Invalid order choice." << endl;
            return;
        }
    } else if (choice == 'p') {
        if (order == 'a') {
            sort(inventory.begin(), inventory.end(), [](const Item& a, const Item& b) {
                return a.getPrice() < b.getPrice();
            });
        } else if (order == 'd') {
            sort(inventory.begin(), inventory.end(), [](const Item& a, const Item& b) {
                return a.getPrice() > b.getPrice();
            });
        } else {
            cout << "Invalid order choice." << endl;
            return;
        }
    } else {
        cout << "Invalid sort choice." << endl;
        return;
    }

    cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity"
         << setw(10) << "Price" << endl;
    cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
    for (const auto& item : inventory) {
        cout << setw(10) << item.getProductID() << setw(20) << item.getName()
             << setw(10) << item.getQuantity() << setw(10) << fixed << setprecision(2) << item.getPrice() << endl;
    }
}

void displayLowStockItems(const vector<Item>& inventory) {
    cout << "Low Stock Items (Quantity <= 5):" << endl;
    cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity"
         << setw(10) << "Price" << setw(20) << "Category" << endl;
    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

    for (const auto& item : inventory) {
        if (item.getQuantity() <= 5) {
            item.displayItem();
        }
    }
}

int main() {
    vector<Item> inventory;
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
                addItem(inventory, nextID);
                break;
            case 2:
                updateItem(inventory);
                break;
            case 3:
                removeItem(inventory);
                break;
            case 4:
                displayAllItems(inventory);
                break;
            case 5:
                searchItem(inventory);
                break;
            case 6:
                sortItems(inventory);
                break;
            case 7:
                displayLowStockItems(inventory);
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