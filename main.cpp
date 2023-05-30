#include <iostream>
#include "DocumentManager.h"

using namespace std;

int main() {
    DocumentManager dm;

    cout << "Adding patrons" << endl;
    dm.addPatron(15);
    dm.addPatron(22);
    cout << "Finished adding patrons" << endl;

    cout << "Adding documents" << endl;
    dm.addDocument("C++", 1, 1);
    dm.addDocument("Python", 42, 2);
    cout << "Finished adding documents" << endl;

    cout << "Testing search" << endl;
    int srchResult = dm.search("C++");
    cout << "Result is (Want 1): " << " " << srchResult << endl;
    int srchReslt2 = dm.search("Python");
    cout << "Result is (Want 42): " << srchReslt2 << endl;
    cout << "Finished testing search" << endl;

    cout << "Testing document borrow" << endl;
    bool result1 = dm.borrowDocument(1, 15);
    cout << "Result is (Want True): " << " " << to_string(result1) << endl;
    bool result2 = dm.borrowDocument(2, 15);
    cout << "Result is (Want True): " << " " << to_string(result2) << endl;
    cout << "Finished testing document borrow" << endl;

    cout << "Testing too many borrows" << endl;
    bool result = dm.borrowDocument(1, 22);
    cout << "Result is (Want false): " << " " << to_string(result) << endl;
    cout << "Finished testing too many borrows" << endl;

    cout << "Testing return" << endl;
    dm.returnDocument(1, 15);
    cout << "Finished testing return" << endl;

    cout << "Tests Complete" << endl;

    return 0;
}
