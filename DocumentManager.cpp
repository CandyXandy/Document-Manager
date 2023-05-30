#include "DocumentManager.h"



/**
 * Adds a document to the list of documents, using an unordered_map
 * @param name : Name of the document
 * @param id : id reference to the document
 * @param license_limit : borrow limit of the document
 */
void DocumentManager::addDocument(const std::string& name, int id, int license_limit) {
    std::vector<int> docValues(2);
    docValues.at(0) = id; // the two values of our array are id and license_limit.
    docValues.at(1) = license_limit;
    auto toInsert = std::make_pair(name, docValues); // construct a pair out of our name and values
    this -> documentList.insert(toInsert); // insert the pair into our map.
}

/**
 * Adds a patron to the list of patrons, using an unordered_set
 * @param patronID : ID reference to the patron
 */
void DocumentManager::addPatron(int patronID) {
    // Check we aren't adding a patronID that already exists
    if (!checkPatronID(patronID)) {
        this -> patronList.insert(patronID);
        return;
    } else {
        perror("patronID already exists! Patron addition cancelled."); // display error message to stderr
    }
}

/**
 * Searches the collection of documents to find the associated document's docID.
 * @param name : name of the document
 * @return : 0 if document not found, otherwise returns the document's docID.
 */
int DocumentManager::search(const std::string& name) {
    // found will either be an iterator pointing to the key if found, or an iterator pointing to end() if not.
    std::unordered_map<std::string, std::vector<int>>::const_iterator found = this -> documentList.find(name);
    if (found == this-> documentList.end() ) { // if key not found
        return 0;
    } else { // otherwise return the docID associated with the document.
        return found->second.at(0); // docID is always the first index
    }
}

/**
 * Tries to borrow a document from the collection of documents.
 * Checks if the patronID is valid, and then checks if the document ID exists.
 * @param docid : docID to search for
 * @param patronID : patron to loan document to
 * @return : false if patron or document doesn't exist, or if there are no more
 *           copies of document to be lent. Returns true if there are and all values
 *           are good.
 */
bool DocumentManager::borrowDocument(int docid, int patronID) {
    // check that patronID is valid
    if (!checkPatronID(patronID)) {
        // if patronID not found return false
        return false;
    }
    // look through documentList to find the docID
    auto it = findDocID(docid);
    if (it == this -> documentList.end()) return false;
    if (it -> second[1] < 1) { // if there are no more documents left to borrow
        return false; // we can't lend out the document
    }
    // otherwise,
    it -> second.at(1)--; // decrease the number of documents left to borrow
    return true;       // document has been lent!
}

/**
 * Return a document to the document list, increasing the amount of
 * documents of that type that can be lent out.
 * @param docid
 * @param patronID
 */
void DocumentManager::returnDocument(int docid, int patronID) {
    // check that patronID is valid
    if (!checkPatronID(patronID) ) {
        perror("Patron ID does not exist! Return cancelled");
        return;
    }
    auto it = findDocID(docid);
    if (it == this -> documentList.end() ) {
        perror("Cannot find document ID! Return cancelled");
        return;
    }
    // if all values good, increment number of documents left to borrow
    it -> second[1]++;
}

/**
 * Helper function to find if a patronID is valid
 * @param patronID : patronID to search for
 * @return : True if patronID exists, false if not.
 */
bool DocumentManager::checkPatronID(int patronID) {
    // check that patronID is valid
    if (this -> patronList.find(patronID) == this -> patronList.end()) {
        // if patronID not found return false
        return false;
    } else {
        return true;
    }
}

/**
 * Searches the document list to find a matching docID using a const iterator
 * @param docID : docID to find
 * @return : iterator to end of document list if not found, iterator to key of docID if found.
 */
std::unordered_map<std::string, std::vector<int>>::iterator DocumentManager::findDocID(int docID) {
    // search through documentList with an iterator
    for (auto it = this -> documentList.begin(); it != this->documentList.end(); ++it ) {
        if ( it -> second[0] == docID) { // if the iterator is pointing to the correct key
            return it; // return it
        }
    }
    // otherwise if not found, return an iterator to the end.
    return this -> documentList.end();
}