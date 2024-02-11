#include <stdlib.h>
#include "LinkedList.h"
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cout << "Usage: " << argv[0] << " 3 4 42\n"
                  << "Where the 3 is Length, 4 is Width, and 42 is the Seed." << std::endl;
        return 0;
    }
    std::cout << "Enter the Matrix!" << std::endl;
    srand(atoi(argv[3])); // could use strol for error checking but yolo
    LinkedList theMatrix(atoi(argv[1]), atoi(argv[2]));
    
    theMatrix.print();
    theMatrix.traceTheCall(0);
    theMatrix.traceTheCall(1);
    theMatrix.traceTheCall(2);
    
    //Some Test Cases To Help Code It
    // srand(26); //you always get the same random numbers.
    // LinkedList list(3, 6); // ./a.out 3 6 26
    // list.print();
    // list.traceTheCall(0);
    // list.traceTheCall(1);
    // list.traceTheCall(5);
    // LinkedList list0(10, 20);
    // list0.traceTheCall(0);
    // list0.traceTheCall(1);
    // list0.print();
    // LinkedList list1(0, 0);
    // LinkedList list2(0, 1);
    // LinkedList list3(1, 0);
    // LinkedList list4(1, 1);
    // list1.print();
    // list1.traceTheCall(0);
    // list2.print();
    // list2.traceTheCall(0);
    // list3.print();
    // list3.traceTheCall(0);
    // list4.print();
    // list4.traceTheCall(0);
    
    return 0;
}
