/* Name: Prithvi Arunshankar
 * CruzID: parunsha
 * Assignment: pa8
*/
//-----------------------------------------------------------------------------
// Dictionary.cpp
// Implementation file for Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

// Color Constants ------------------------------------------------------------
#define BLACK 0
#define RED 1

// Class Constructors & Destructors -------------------------------------------

// Private Node Constructor
Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = BLACK;
}

// Dictionary()
// Creates new Dictionary in the empty state
Dictionary::Dictionary() {
    nil = new Node("NULL", -1);
    root = current = nil;
    root->left = root->right = root->parent = nil;
    num_pairs = 0;   
}

// Copy constructor
Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("NULL", -1);;
    root = current = nil;
    num_pairs = 0;   
    preOrderCopy(D.root, D.nil);
    begin();
}

// Destructor
Dictionary::~Dictionary() {
    clear();
    delete(nil);
}


// Helper functions --------------------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Dictionary::Node* R) const {
    if(R != nil) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Dictionary::Node* R) const {
    if(R != nil) {
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Dictionary::Node* R, Dictionary::Node* N) {
    if(R != nil) {
        if(R != N) {
            setValue(R->key, R->val);
            preOrderCopy(R->left, N); 
            preOrderCopy(R->right, N); 
        }
    } 
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Dictionary::Node* R) {
    if(R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete(R);
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Dictionary::Node* R, keyType k) const {
    if(R == nil || k == R->key) {
        return(R);
    } else if(k < R->key) {
        return(search(R->left, k));
    } else {
        return(search(R->right, k));
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Dictionary::Node* R) {
    while(R->left != nil) {
        R = R->left;
    }

    return(R); 
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Dictionary::Node* R) {
    while(R->right != nil) {
        R = R->right;
    }

    return(R);
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk. If N points to the rightmost
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findNext(Dictionary::Node* N) {
    if(N == nil || N == findMax(root)) {
        return(nil);
    }

    if(N->right != nil) {
        return(findMin(N->right));
    }

    Node* P = N->parent;

    while(P != nil && N == P->right) {
        N = P;
        P = P->parent;
    }

    return(P);
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk. If N points to the leftmost
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Dictionary::Node* N) {
    if(N == nil || N == findMin(root)) {
        return(nil);
    }

    if(N->left != nil) {
        return(findMax(N->left));    
    }

    Node* P = N->parent;

    while(P != nil && N == P->left) {
        N = P;
        P = P->parent;
    }

    return(P);
}

// transplant()
// Helper function which is used for node deletion
// Helps restructure tree
void Dictionary::transplant(Dictionary::Node* U, Dictionary::Node* V) {
    if(U->parent == nil) {
        root = V;
    } else if(U == U->parent->left) {
        U->parent->left = V;
    } else {
        U->parent->right = V;
    }

    if(V != nil) {
        V->parent = U->parent;
    }
}


// RBT Helper Functions (Optional) -----------------------------------------

// LeftRotate()
// Helper function which performs a rotation in the left direction
void Dictionary::LeftRotate(Dictionary::Node* N) {
    // Set Y
    Node *Y = N->right; 

    // Turn Y's left subtree into N's right subtree
    N->right = Y->left;

    if(Y->left != nil) {
        Y->left->parent = N;
    }

    // Link Y's parent to N
    Y->parent = N->parent;

    if(N->parent == nil) {
        root = Y;
    } else if(N == N->parent->left) {
        N->parent->left = Y;
    } else {
        N->parent->right = Y;
    }

    // Put N on Y's Left
    Y->left = N;
    N->parent = Y;
}

// RightRotate()
// Helper function which performs a rotation in the right direction
void Dictionary::RightRotate(Dictionary::Node* N) {
    // Set Y
    Node* Y = N->left; 

    // Turn Y's right subtree into N's left subtree
    N->left = Y->right;

    if(Y->right != nil) {
        Y->right->parent = N;
    }

    Y->parent = N->parent;

    if(N->parent == nil) {
        root = Y;
    } else if(N == N->parent->right) {
        N->parent->right = Y;
    } else {
        N->parent->left = Y;
    }

    Y->right = N;
    N->parent = Y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Dictionary::Node* N) {
    Node* Y;

    while(N->parent->color == RED) {
        if(N->parent == N->parent->parent->left) {
            Y = N->parent->parent->right;

            if(Y->color == RED) {
                N->parent->color = BLACK;
                Y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            } else {
                if(N == N->parent->right) {
                    N = N->parent;
                    LeftRotate(N);
                }

                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }        

        } else {
            Y = N->parent->parent->left;

            if(Y->color == RED) {
                N->parent->color = BLACK;
                Y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            } else {
                if(N == N->parent->left) {
                    N = N->parent;
                    RightRotate(N);
                }

                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }

    root->color = BLACK;
}

// RB_Transplant()
// Helper function which is used to transplant a tree
void Dictionary::RB_Transplant(Dictionary::Node* u, Dictionary::Node* v) {
    if(u->parent == nil) {
        root = v;
    } else if(u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    v->parent = u->parent;
}

// RB_DeleteFixUp()
// Helper function which is used to fix tree after a deletion is performed
void Dictionary::RB_DeleteFixUp(Dictionary::Node* N) {
    Node* W;

    while(N != root && N->color == BLACK) {
        if(N == N->parent->left) {
            W = N->parent->right;

            if(W->color == RED) {
                W->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                W = N->parent->right;
            }

            if(W->left->color == BLACK && W->right->color == BLACK) {
                W->color = RED;
                N = N->parent;
            }

            else {
                if(W->right->color == BLACK) {
                    W->left->color = BLACK;
                    W->color = RED;
                    RightRotate(W);
                    W = N->parent->right;
                }

                W->color = N->parent->color;
                N->parent->color = BLACK;
                W->right->color = BLACK;
                LeftRotate(N->parent);
                N = root;
            }        
        } else {
            W = N->parent->left;

            if(W->color == RED) {
                W->color = BLACK;
                N->parent->color = RED;
                RightRotate(N->parent);
                W = N->parent->left;
            }

            if(W->right->color == BLACK && W->left->color == BLACK) {
                W->color = RED;
                N = N->parent;
            }

            else {
                if(W->left->color == BLACK) {
                    W->right->color = BLACK;
                    W->color = RED;
                    LeftRotate(W);
                    W = N->parent->left;
                }

                W->color = N->parent->color;
                N->parent->color = BLACK;
                W->left->color = BLACK;
                RightRotate(N->parent);
                N = root;
            }
        }
    }

    N->color = BLACK;
}

// RB_Delete()
// Helper function which is used to delete a particular node from RBT
void Dictionary::RB_Delete(Dictionary::Node* N) {
    Node* Y = N;
    Node* X;
    int original_color = Y->color; 

    if(N->left == nil) {
        X = N->right;
        RB_Transplant(N, N->right); 
    } else if(N->right == nil) {
        X = N->left;
        RB_Transplant(N, N->left);
    } else {
        Y = findMin(N->right);
        original_color = Y->color;
        X = Y->right;

        if(Y->parent == N) {
            X->parent = Y;
        } else {
            RB_Transplant(Y, Y->right);
            Y->right = N->right;
            Y->right->parent = Y;
        }

        RB_Transplant(N, Y);
        Y->left = N->left;
        Y->left->parent = Y;
        Y->color = N->color;
    }

    if(original_color == BLACK) {
        RB_DeleteFixUp(X);
    }
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary
int Dictionary::size() const {
    return(num_pairs); 
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
    if(search(root, k) == nil) {
        return(false);
    } 

    return(true);
}

// getValue()
// Returns a reference to the value corresponding to key k
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
    if(!contains(k)) {
        throw(std::domain_error("Dictionary: getValue(): key doesn't exist in dictionary"));
    }

    Node* N = search(root, k);
    return(N->val);
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false
// otherwise
bool Dictionary::hasCurrent() const {
    if(current != nil) {
        return(true);
    }

    return(false);
}

// currentKey()
// Returns the current key
// Pre: hasCurrent()
keyType Dictionary::currentKey() const {
    if(!hasCurrent()) {
        throw(std::invalid_argument("Dictionary: currentKey(): dictionary cursor is undefined"));
    }

    return(current->key);
}

// currentVal()
// Returns a reference to the current value
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
    if(!hasCurrent()) {
        throw(std::invalid_argument("Dictionary: currentVal(): dictionary cursor is undefined"));
    }

    return(current->val);
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    postOrderDelete(root);
    root = current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v,
// otherwise inserts the new pair (k, v)
void Dictionary::setValue(keyType k, valType v) {
    Node* X = root;
    Node* Y = nil;
    Node* Z = new Node(k, v);

    while(X != nil) {
        Y = X;

        if(k.compare(X->key) == 0) {
            Y->val = v;
            return;
        } else if(k.compare(X->key) < 0) {
            X = X->left;
        } else {
            X = X->right;
        }
    }

    Z->parent = Y;

    if(Y == nil) {
        root = Z;
    } else if(k.compare(Y->key) < 0) {
        Y->left = Z;
    } else {
        Y->right = Z;
    }

    Z->left = nil;
    Z->right = nil;
    Z->color = RED;
    RB_InsertFixUp(Z);
    num_pairs++;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k)
void Dictionary::remove(keyType k) {
    if(!contains(k)) {
        throw(std::domain_error("Dictionary: remove(): key doesn't exist in dictionary"));
    }

    // Otherwise, find that node and delete it
    Node *S = search(root, k);
    RB_Delete(S);

    if(current == S) {
      current = nil;
    }

    num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin() {
    if(size() > 0) {
        current = findMin(root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end() {
    if(size() > 0) {
        current = findMax(root);
    }
}

// next()
// If the current iterator is not at the last pair, advances current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if(!hasCurrent()) {
        throw(std::invalid_argument("Dictionary: next(): dictionary cursor is undefined"));
    }

    current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    if(!hasCurrent()) {
        throw(std::invalid_argument("Dictionary: prev(): dictionary cursor is undefined"));
    }

    current = findPrev(current);
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value
// are separated by the sequence space-colon-space " : ". The pairs are arranged
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    std::string s = "";
    inOrderString(s, root);
    return(s);
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
    std::string s = "";
    preOrderString(s, root);
    return(s);
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string()
std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    return(stream << D.Dictionary::to_string());
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary
Dictionary& Dictionary::operator=( const Dictionary& D ) {
    if(this != &D) {
        Dictionary temp = D;

        // Swap all the fields
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        //std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }

    return(*this);
}
