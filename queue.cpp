#include <iostream> // cout, cin
#include <cstdlib> // std utility functions

using namespace std; // namespace for cout, cin, queue methods

/*
* This class defines a queue by holding nodes as fields which point to one another in a singly-linked order.
* There is a bottom and a top, where the top points to nothing and the bottom is pointed to by nothing.
* To add to the queue, a new bottom is created and is made to point to whatever the current bottom is
* To remove from the queue, the top is removed, representing the oldest value that was added
*/
class queue {
    struct node { // field denoting a member of the queue
        int value; // members of the queue will hold a value
        node* next; // a pointer will be associated with each member of the queue for operations' sake
    };
    node* top; // one member will be the top (first added)
    node* bottom; // one member will be the bottom (last added)

    public: // methods that are accessible and mutable in non-static functions
        queue(); // constructor
        ~queue(); // destructor
        void enqueue(int); // method for adding a member to the bottom of the queue--it will accept an integer as an argument
        void dequeue(); // method for removing the top member of the queue
        void printQueue(); // method for printing out the members of the queue
};

/*
* The constructor initializes the queue with no top or bottom, and displays a message for consistency's sake
*/
queue::queue() {
    cout << "Queue initialized!" << endl; // confirm that the queue has been instantiated without errors
    top = NULL; // no initial top
    bottom = NULL; // no initial bottom
};

/*
* The destructor dereferences queue members after the program has run its course, preventing variables from taking up memory they're no longer using
*/
queue::~queue() {
    node* temp = bottom; // let a temporary variable point to the bottom of the queue

    while(temp != NULL) { // while members exist in the queue
        bottom = bottom->next; // the new bottom will be the next member up from the current bottom; the old bottom is dereferenced
        delete temp; // the old bottom is deleted after being dereferenced
        temp = bottom; // the temporary pointer is now the new bottom, allowing the new bottom to be dereferenced and deleted on the next pass
    }
    cout << "Queue successfully destroyed!" << endl; // confirm that all members were dereferenced
};

/*
* This method adds a new member to the bottom of the queue by creating a temporary member that holds a given value, then making the bottom of the queue equal to that member
* The temporary member will be automatically removed from scope after being dereferenced (line 62), and does not need to be deleted
* If the bottom points to nothing (meaning it is the only member of the queue,) that member will be the top
*   Expected input: a single integer
*   Expected output: queue member at the bottom of the queue, its value being the integer input
*/
void queue::enqueue(int num) {
    node* temp = new node; // allocate a temporary space in memory
    temp->value = num; // that memory holds a value that is the integer passed to this method
    temp->next = bottom; // that memory points to the bottom of the queue
    bottom = temp; // the bottom of the queue now points to this space, as well as itself; this memory is now the bottom of the queue
    if (bottom->next == NULL) { // if the bottom is the only member in the queue
        top = bottom; // the bottom is the top, and will later be treated as such
    }
};

/*
* This method removes a member from the top of the queue by iterating to find the member that points to it, and making that the new top
* When the member pointing to the top is found, it will have its next pointer set to null and the previous top will be dereferenced and deleted
* If the member pointing to the top points to NULL (implying there is no top, and therefore no bottom) then the queue cannot be dequeued any further
* Note: the valgrind screenshot does not include the statement in line 91. This was added in after completion for the sake of screenshot legibility
*   Expected input: queue of size >= 1
*   Expected output: the same queue without its top, where the member which was pointing to the top is now the top
*/
void queue::dequeue() {
    node* temp = bottom; // let a temporary member be equivalent to the bottom; for each pass, the next member being pointed to will be evaluated
    bool sentry = true; // sentry for the following while loop
    while (sentry) { // while sentry is true
        if (temp->next != top) { // if the current member has a member after it
            temp = temp->next; // let the temporary member be equivalent to the member after the current for the next pass of the loop
            if (temp == NULL) { // if the bottom points to nothing 
                cout << "Queue empty: dequeue operation failed!" << endl; // confirm that nothing more can be removed from the queue
                sentry = false; // end the loop
            }
        }
        else { // if the current member has a member after it that points to nothing
            temp->next = NULL; // the current member now points to nothing
            delete top; // the current top is deleted
            top = temp; // the new top is the current member, which points to nothing but previously pointed to the top
            cout << "Dequeue Successful!" << endl; // confirm successful dequeue operation
            sentry = false; // end the loop
        }
    }
};

/*
* This method prints all members of the queue from the bottom up by iterating through them with a while loop
* If the bottom points to nothing, then the print cannot be completed
* If the bottom points to something, the while loop will print the value held by a member then set the member equal to the next member and repeat
*   Expected input: a queue of size >= 1
*   Expected output: A set of queue members on a single command line
*/
void queue::printQueue() {
    node* temp = bottom; // let a temporary member be equivalent to the bottom; for each pass, the next member being pointed to will be evaluated
    if (temp->next == NULL) { // if there is nothing being pointed to, meaning no top and therefore no bottom
        cout << "Queue empty: print operation failed!" << endl; // confirm that the queue cannot be iterated through
    }
    else { // if there are existing members with values
        cout << "From newest to oldest: " << endl; // confirm the order in which the prints will be made
        while (temp != NULL) { // while a bottom exists
            cout << temp->value << "  "; // print the value of the current member, delineated by a double space
            temp = temp->next; // the next member being pointed to is now the member to be evaluated in the next pass
        }
        cout << endl; // print out an empty line for spacing
    }
};

int main() {
    queue Q; // instantiate a queue 
    Q.enqueue(1); // this line and the follwing 4 add 5 integers to the queue
    Q.enqueue(1);
    Q.enqueue(2);
    Q.enqueue(3);
    Q.enqueue(5);
    Q.printQueue(); // print 5 queue members
    for (int i = 0; i < 3; i++) { // remove 3 members from the queue
            Q.dequeue();
    }
    Q.printQueue(); // print the remaining 2 members of the queue
    for (int i = 0; i < 3; i++) { // remove (or attempt to remove) 3 more members from the queue
            Q.dequeue();
    }
    Q.printQueue(); // print the presumably empty queue
    return 0;
}