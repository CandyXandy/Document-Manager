#ifndef PRAC_9_DOCUMENTMANAGER_H
#define PRAC_9_DOCUMENTMANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>


class DocumentManager {

private:
    std::unordered_map<std::string, std::vector<int>> documentList;
    /*
     * We need to store multiple values about each document,
     * including its id and license_limit, and we will be
     * frequently searching through our data structure to
     * find these values.
     * An unordered map will provide us a constant time
     * complexity on searching, and will also allow us
     * to find these values based on a string input.
     * We could store each document as a key-value pair, with
     * its name (string) being the key, and storing the values
     * in an array. Storing the values in a vector would allow
     * us to take advantage of order one access time as well to
     * find each individual value and modify / reference them.
     */

    std::unordered_set<int> patronList;
    /*
     * For our list of patrons, an unordered set ADT would
     * be appropriate as all the values in a set are unique.
     * Unordered sets will allow us an amortised constant
     * time complexity to search for the existence of a
     * patronID, and would also allow us to search the
     * patronID directly rather than having to iterate through
     * an array to find a matching value.
     * Unordered sets also have an average case constant time
     * complexity for inserting elements.
     */

    // helper function to find patronID
    bool checkPatronID(int patronID);

    // helper function to find docID
    std::unordered_map<std::string, std::vector<int>>::iterator findDocID(int docID);

public:
    /* Add a document to the current list of documents */
    void addDocument(const std::string& name, int id, int license_limit);

    /* Add a patron to the current list of patrons */
    void addPatron(int patronID);

    /* Returns docid if name is in the document collection or
     * 0 if the name is not in the collection.
     */
    int search(const std::string& name);

    /*
     * returns true if document is borrowed, false if it cannot
     * be borrowed (invalid patronage or the number of copies
     * current borrowed has reached the license limit)
     */
    bool borrowDocument(int docid, int patronID);

    /* Re-add a document to the list */
    void returnDocument(int docid, int patronID);
};


#endif //PRAC_9_DOCUMENTMANAGER_H
