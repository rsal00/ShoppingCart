/*
    Ruben Salazar
    CMPR 131
    March 19, 2025

    Homework 2

    Collaboration:
    None
*/

#include "ShoppingCart.h"
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

// Constructor
ShoppingCart::ShoppingCart() : capacity(5),numOfItems(0)
{
    cart = new string[capacity];
}

// Destructor
ShoppingCart::~ShoppingCart()
{
    destroyCart();
}

// Overloaded constructor
ShoppingCart::ShoppingCart(int newCapacity) : capacity(newCapacity), numOfItems(0)
{
    cart = new string[capacity];
}

// Copy constructor
ShoppingCart::ShoppingCart(const ShoppingCart &otherCart)
{
    capacity = otherCart.capacity;
    numOfItems = otherCart.numOfItems;
    cart = new string[capacity];
    for (int i = 0; i < numOfItems; i++)
    {
        cart[i] = otherCart.cart[i];
    }
}

// Adds item to the array
void ShoppingCart::addItem(string item)
{
    // Error checking if the allocation fails
    if (!cart)
    {
        cerr << "Allocation failed!" << endl;
        return;
    }

    // If the cart items reaches have the capacity, double the size
    if (numOfItems == capacity / 2)
    {
        resize();
        cart[numOfItems] = item;
        numOfItems++;
    }
    // Otherwise, add to the end of the list
    else
    {
        cart[numOfItems] = item;
        numOfItems++;
    }
}

// Removes an item by its name
void ShoppingCart::removeItem(string item)
{
    if (numOfItems == 0)
    {
        cerr << "Cart is empty!\n";
    }
    else
    {
        string* temp = new string[capacity];
        int count = 0;
        for (int i = 0; i < numOfItems; i++)
        {
            // The first condition checks if the item we want to remove is in the cart.
            // The second condition is for when we want to remove an item that in the cart
            // multiple times.
            // count and i will be the same when no item is removed, but when one item is removed,
            // they will differ, which is why we add the second condition so that we only remove the
            // first occurence of the item.
            if (!checkItems(cart[i], item) && cart[i] != item || count != i)
            {
                temp[count] = cart[i];
                count++;
            }
        }
        delete[] cart;
        cart = temp;
        if (count == numOfItems - 1)
        {
            numOfItems--;
            cout << "Successfully removed!\n";
        }
        else
        {
            cout << "Item is not in the list\n";
        }
    }
}

// Function that checks for case-sensitivity of the item in the cart and
// the item inputted by the user to remove
bool ShoppingCart::checkItems(string inCart, string removeItem)
{
    // Put the item we want to remove into a C-String
    char* r_str = new char[removeItem.size()];

    // Put the item in the cart to compare into a C-String
    char *c_str = new char[inCart.size()];

    // Check if allocation is successful
    if (!r_str || !c_str)
    {
        cerr << "\nFailed allocation!\n";
        return -1;
    }

    // Copy characters of the removeItem into the corresponding C-String
    for (int i = 0; i < removeItem.size(); i++)
    {
        r_str[i] = removeItem[i];
    }

    // Copy characters of the item in the cart into the corresponding C-String
    for (int i = 0; i < inCart.size(); i++)
    {
        c_str[i] = inCart[i];
    }

    // Condition to check if user inputted a lowercase letter in as the first character for a string
    if (islower(*(r_str)))
    {
        *(r_str) = toupper(*(r_str)); // Make the lowercase letter uppercase
        for (int i = 0; i < inCart.size(); i++)
        {
            if (r_str[i] == c_str[i]) // Check if the strings are the same
            {
                return true;
            }
        }
    }
    // Conditional to check if the item in the cart's first letter is lowercase
    // and item to remove's first letter is uppercase
    else if (islower(*(c_str)) && isupper(*(r_str)))
    {
        *(c_str) = toupper(*(c_str)); // Make item in the cart's first letter uppercase
        for (int i = 0; i < inCart.size(); i++)
        {
            if (r_str[i] == c_str[i]) // Check if the strings are the same
            {
                return true;
            }
        }
    }
    // If the items in the cart's first letter and the item to remove's first letter are both uppercase
    else
    {
        for (int i = 0; i < inCart.size(); i++)
        {
            if (removeItem[i] == inCart[i])
            {
                return true;
            }
        }
    }

    // Deallocate the memory for the C-Strings
    delete[] r_str;
    delete[] c_str;
    r_str = nullptr;
    c_str = nullptr;

    return false;
}

// Prints the items onto the screen
void ShoppingCart::listItems() const
{
    // Checks if the cart is empty
    if (numOfItems == 0)
    {
        cout << "Cart is empty." << endl;
    }
    else
    {
        for (int i = 0; i < numOfItems; i++)
        {
            cout << "Item " << i+1 << ": " << cart[i] << endl;
        }
    }
}

// Function to resize the array when we want to add an item after reaching half the capacity.
void ShoppingCart::resize()
{
    int newCapacity = capacity * 2; // Double the array capacity
    capacity = newCapacity;
    string* temp = new string[capacity]; // Allocate a new array with new capacity
    for (int i = 0; i < capacity; i++)
    {
        temp[i] = cart[i]; // Copy the old elements into the temp array
    }
    delete[] cart; // Deallocate old array
    cart = temp; // Point cart to the new array
}

// Returns number of items
int ShoppingCart::getNumOfItems() const
{
    return numOfItems;
}

// Returns capacity
int ShoppingCart::getCapacity() const
{
    return capacity;
}

// Clears cart and resets capacity and numOfItems
void ShoppingCart::clearCart()
{
    if (numOfItems == 0)
    {
        cerr << "\nCart is empty.\n";
    }
    else
    {
        capacity = 5;
        numOfItems = 0;
        delete[] cart;
        cart = new string[capacity];
        cout << "Successfully cleared!\n";
    }
}

// Destroys the cart for the destructor to call
void ShoppingCart::destroyCart()
{
    delete[] cart;
    cart = nullptr;
}

// Function that saves items in cart to a file
void ShoppingCart::saveCart()
{
    // Create an output stream
    ofstream file;
    file.open("Shopping Cart.txt"); // Name the text file

    // If the file is open, write to it
    if (file.is_open())
    {
        file << *this; // using the overloaded insertion operator and dereferencing the current object
        file.close();
        cout << "Successfully saved!" << endl;
    }
    else // Error checking if the file never opened
    {
        cerr << "Failed to write!" << endl;
    }
}

// Insertion operator overload
ostream& operator<<(ostream& out, const ShoppingCart& myCart)
{
    // Check if the list has items to display
    if (myCart.numOfItems != 0)
    {
        for (int i = 0; i < myCart.numOfItems; i++)
        {
            out << "Item " << i+1 << ": " << myCart.cart[i] << endl;
        }
    }
    else
    {
        cout << "Cart is empty." << endl;
    }
    return out;
}

// Assignment operator overload
ShoppingCart& ShoppingCart::operator=(const ShoppingCart& right)
{
    if (this != &right)
    {
        delete[] cart;

        capacity = right.capacity;
        numOfItems = right.numOfItems;
        cart = new string[capacity];

        for (int i = 0; i < numOfItems; i++)
        {
            cart[i] = right.cart[i];
        }
    }
    return *this;
}
