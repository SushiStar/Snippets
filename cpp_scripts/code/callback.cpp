/*
 * This is the testing script for callback functions.
 *
 * Date: Apr/23/2019
 * Author: Wei Du
 */
#include <iostream>

using namespace std;
void greetings_hello() { std::cout << "Hello world!\n"; }
void greetings_hay() { std::cout << "How are you?\n"; }

void sendGreetings(void (*p)()) { p(); }

int main() {
    sendGreetings(greetings_hello);
    sendGreetings(greetings_hay);
    return 0;
}
