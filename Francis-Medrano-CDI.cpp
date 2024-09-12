#include <iostream>
#include <string>
using namespace std;

class Product {
public:
    string id;
    string name;
    int price;

    Product(string id = "", string name = "", int price = 0) : id(id), name(name), price(price) {}
};

class ShoppingCart {
public:
    struct CartItem {
        Product product;
        int quantity;

        
        CartItem(Product product = Product("", "", 0), int quantity = 1) : product(product), quantity(quantity) {}
    };

private:
    CartItem cartItems[10];  
    int cartSize = 0;

public:
    
    ShoppingCart() {}

    void addProduct(Product product, int quantity = 1) {
        for (int i = 0; i < cartSize; ++i) {
            if (cartItems[i].product.id == product.id) {
                cartItems[i].quantity += quantity;
                return;
            }
        }

        if (cartSize < 10) {
            cartItems[cartSize] = CartItem(product, quantity);
            cartSize++;
            cout << "Product added successfully!\n";
        } else {
            cout << "Cart is full!\n";
        }
    }

    void viewCart() {
        if (cartSize == 0) {
            cout << "Your shopping cart is empty.\n";
            return;
        }

        cout << "Product ID\tName\tPrice\tQuantity\n";
        for (int i = 0; i < cartSize; ++i) {
            cout << cartItems[i].product.id << "\t\t"
                 << cartItems[i].product.name << "\t"
                 << cartItems[i].product.price << "\t"
                 << cartItems[i].quantity << "\n";
        }
    }

    int checkout() {
        int totalAmount = 0;

        if (cartSize == 0) {
            cout << "Cart is empty! Nothing to checkout.\n";
            return totalAmount;
        }

        cout << "Checkout Products:\n";
        cout << "Product ID\tName\tPrice\tQuantity\n";
        for (int i = 0; i < cartSize; ++i) {
            cout << cartItems[i].product.id << "\t\t"
                 << cartItems[i].product.name << "\t"
                 << cartItems[i].product.price << "\t"
                 << cartItems[i].quantity << "\n";
            totalAmount += cartItems[i].product.price * cartItems[i].quantity;
        }

        cout << "Total Amount: " << totalAmount << "\n";
        return totalAmount;
    }

    void clearCart() {
        cartSize = 0;  
    }

    
    CartItem* getCartItems() {
        return cartItems;
    }

    int getCartSize() const {
        return cartSize;
    }
};

class Order {
private:
    struct OrderDetail {
        int orderId;
        ShoppingCart::CartItem cartItems[10];
        int numItems;
        int totalAmount;
    };

    OrderDetail orders[10]; 
    int orderCount = 0;

public:
    Order() {}

    void createOrder(ShoppingCart::CartItem cartItems[], int cartSize, int totalAmount) {
        if (orderCount < 10) {
            OrderDetail& order = orders[orderCount];
            order.orderId = orderCount + 1;
            order.totalAmount = totalAmount;
            order.numItems = cartSize;
            for (int i = 0; i < cartSize; ++i) {
                order.cartItems[i] = cartItems[i];
            }
            orderCount++;
            cout << "You have successfully checked out the products!\n";
        } else {
            cout << "Order limit reached!\n";
        }
    }

    void viewOrders() {
        if (orderCount == 0) {
            cout << "No orders available.\n";
            return;
        }

        for (int i = 0; i < orderCount; ++i) {
            OrderDetail& order = orders[i];
            cout << "Order ID: " << order.orderId << "\n";
            cout << "Total Amount: " << order.totalAmount << "\n";
            cout << "Order Details:\n";
            cout << "Product ID\tName\tPrice\tQuantity\n";
            for (int j = 0; j < order.numItems; ++j) {
                cout << order.cartItems[j].product.id << "\t\t"
                     << order.cartItems[j].product.name << "\t"
                     << order.cartItems[j].product.price << "\t"
                     << order.cartItems[j].quantity << "\n";
            }
            cout << "\n";
        }
    }
};

void displayProducts(Product products[], int numProducts) {
    cout << "Available Products:\n";
    cout << "Product ID\tName\tPrice\n";
    for (int i = 0; i < numProducts; ++i) {
        cout << products[i].id << "\t\t"
             << products[i].name << "\t"
             << products[i].price << "\n";
    }
}

int main() {
    Product products[] = {
        Product("ABC", "Paper", 60),
        Product("CDE", "Pencil", 10),
        Product("QWE", "Ballpen", 10),
        Product("TRE", "Eraser", 20),
        Product("ZXC", "Ruller", 50)
    };
    const int numProducts = 5;

    ShoppingCart cart;
    Order orderManager;

    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. View Products\n";
        cout << "2. View Shopping Cart\n";
        cout << "3. View Orders\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            displayProducts(products, numProducts);

            char addMore;
            do {
                string productId;
                cout << "Enter the ID of the product you want to add to the shopping cart: ";
                cin >> productId;

                bool found = false;
                for (int i = 0; i < numProducts; ++i) {
                    if (products[i].id == productId) {
                        cart.addProduct(products[i]);
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Product not found!\n";
                }

                cout << "Do you want to add another product? (y/n): ";
                cin >> addMore;

            } while (addMore == 'y' || addMore == 'Y');

        } else if (choice == 2) {
            cart.viewCart();
            char checkout;
            cout << "Do you want to check out all the products? (Y/N): ";
            cin >> checkout;

            if (checkout == 'Y' || checkout == 'y') {
                int totalAmount = cart.checkout();
                orderManager.createOrder(cart.getCartItems(), cart.getCartSize(), totalAmount);
                cart.clearCart();
            }

        } else if (choice == 3) {
            orderManager.viewOrders();
        }

    } while (choice != 0);

    return 0;
}
