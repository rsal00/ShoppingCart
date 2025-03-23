/*
    Ruben Salazar
    CMPR 131
    March 19, 2025

    Homework 2

    Collaboration:
    None
*/

#pragma once
#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <string>

class ShoppingCart
{
public:
    ShoppingCart();
    ShoppingCart(int newCapacity);
    ShoppingCart(const ShoppingCart &otherCart);
    ~ShoppingCart();

    void addItem(std::string item);
    void removeItem(std::string item);
    void listItems() const;

    bool checkItems(std::string inCart, std::string removeItem);

    int getNumOfItems() const;
    int getCapacity() const;

    void clearCart();
    void destroyCart();

    void saveCart();

    friend std::ostream& operator<<(std::ostream& out, const ShoppingCart& myCart);

    ShoppingCart& operator=(const ShoppingCart& right);

private:
    std::string* cart;
    int capacity;
    int numOfItems;

    // It is private so that it is only called when needed by the member functions
    void resize();
};

#endif
