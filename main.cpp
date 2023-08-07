#include <iostream>
#include <vector>
using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

class Node {
public:
    int value;
    Node* left;
    Node* right;

    Node(int value) : value(value), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root;
    int comparisons;

    BST() : root(nullptr), comparisons(0){}
    void reset() {
        comparisons = 0;
    }

    int getCount() {
        return comparisons;
    }

    void insert(int value) {
        root = insert(value, root);
    }

    bool find(int value) {
        return find(value, root);
    }

    void remove(int value) {
        root = remove(value, root);
    }

    void print() {
        print(root);
        cout << endl;
    }

    double averageDepth() {
        if (root == nullptr) {
            return 0;
        }
        int sum = 0;
        int count = 0;
        depthCalculate(root, 0, sum, count);
        return (double)sum / count;
    }

    int height() {
        return height(root);
    }

private:
    Node* insert(int value, Node* node) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->value) {
            node->left = insert(value, node->left);
        } else if (value > node->value) {
            node->right = insert(value, node->right);
        }
        comparisons++;
        return node;
        
    }

    bool find(int value, Node* node) {
        if (node == nullptr) {
            return false;
        }
        comparisons++;
        if (value < node->value) {
            return find(value, node->left);
        } else if (value > node->value) {
            return find(value, node->right);
        } else {
            return true;
        }
    }

    Node* remove(int value, Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->value) {
            node->left = remove(value, node->left);
        } else if (value > node->value) {
            node->right = remove(value, node->right);
        } else {
            if (node->left == nullptr) {
                Node* right = node->right;
                delete node;
                return right;
            } else if (node->right == nullptr) {
                Node* left = node->left;
                delete node;
                return left;
            } else {
                node->value = minValue(node->right);
                node->right = remove(node->value, node->right);
            }
        }
        comparisons++;
        return node;
        
    }

    int minValue(Node* node) {
        int minValue = node->value;
        while (node->left != nullptr) {
            minValue = node->left->value;
            node = node->left;
        }
        return minValue;
    }

    void print(Node* node) {
        if (node == nullptr) {
            return;
        }

        cout << node->value << " ";
        print(node->left);
        print(node->right);
    }

    void depthCalculate(Node* node, int depth, int& sum, int& count) {
        if (node == nullptr) {
            return;
        }
        sum += depth;
        count++;

        depthCalculate(node->left, depth + 1, sum, count);
        depthCalculate(node->right, depth + 1, sum, count);
    }

    int height(Node* node) {
        if (node == nullptr) {
            return -1;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return max(leftHeight, rightHeight) + 1;
    }
};

void insertValuesFromVector(BST& bst, const vector<int>& values) {
    for (int value : values) {
        bst.insert(value);
    }
}

void removeValuesFromVector(BST& bst, const vector<int>& values) {
    for (int value : values) {
        bst.remove(value);
    }
}
void shake(vector<int>& v, int S, int R) {
    srand(time(nullptr)); // seed the random number generator
    int n = v.size();
    for (int i = 0; i < S; i++) {
        int j = rand() % n; // select a random index in the vector
        int d = (rand() % R) + 1; // select a random displacement between 1 and R
        if (rand() % 2 == 0) { // decide whether to move left or right
            for (int k = j; k > max(j - d, 0); k--) {
                swap(v[k], v[k-1]); // move the element left
            }
        } else {
            for (int k = j; k < min(j + d, n-1); k++) {
                swap(v[k], v[k+1]); // move the element right
            }
        }
    }
}
void shuffle(vector<int>& v, int S) {
    srand(time(nullptr)); // seed the random number generator
    int n = v.size();
    for (int i = 0; i < S; i++) {
        int j = rand() % n; // select a random index in the vector
        int k = rand() % n; // select another random index in the vector
        swap(v[j], v[k]); // swap the two elements
    }

}



int main() {
    
    vector<int> sortedInsertValues = {1, 2, 3, 4, 5, 6, 7};
    BST sortedInsertBst;
    insertValuesFromVector(sortedInsertBst, sortedInsertValues);
    cout << "Inserting values from sorted vector: ";
    sortedInsertBst.print();
    cout << "Height of the BST: " << sortedInsertBst.height() << endl;

    vector<int> reversedSortedInsertValues = {7, 6, 5, 4, 3, 2, 1};
    BST reversedSortedInsertBst;
    insertValuesFromVector(reversedSortedInsertBst, reversedSortedInsertValues);
    cout << "Inserting values from reversed sorted vector: ";
    reversedSortedInsertBst.print();
    cout << "Height of the BST: " << reversedSortedInsertBst.height() << endl;

    vector<int> shuffledInsertValues = {3, 7, 1, 6, 4, 2, 5};
    BST shuffledInsertBst;
    insertValuesFromVector(shuffledInsertBst, shuffledInsertValues);
    cout << "Inserting values from shuffled vector: ";
    shuffledInsertBst.print();
    cout << "Height of the BST: " << shuffledInsertBst.height() << endl;

    vector<int> singleRemoveValue = {5};
    removeValuesFromVector(shuffledInsertBst, singleRemoveValue);
    cout << "Removing single value from vector: ";
    shuffledInsertBst.print();

    vector<int> multipleRemoveValues = {1, 3, 7};
    removeValuesFromVector(shuffledInsertBst, multipleRemoveValues);
    cout << "Removing multiple values from vector: ";
    shuffledInsertBst.print();

    vector<int> shakeLargerDisplacementVec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Original vector: ";
    for (int x : shakeLargerDisplacementVec) {
        cout << x << " ";
    }
    cout << endl;

    shake(shakeLargerDisplacementVec, 5, 4);
    cout << "Shaken vector with larger displacement: ";
    for (int x : shakeLargerDisplacementVec) {
        cout << x << " ";
    }
    cout << endl;

    BST shakeLargerDisplacementBst;
    insertValuesFromVector(shakeLargerDisplacementBst, shakeLargerDisplacementVec);
    cout << "BST after inserting values from shaken vector with larger displacement: ";
    shakeLargerDisplacementBst.print();
    cout << "Height of the BST: " << shakeLargerDisplacementBst.height() << endl;
    cout << "Comparisons made during insertion: " <<       shakeLargerDisplacementBst.getCount() << endl;

    shakeLargerDisplacementBst.reset(); 
    vector<int> removeValues = {2, 5, 8};
    removeValuesFromVector(shakeLargerDisplacementBst, removeValues);
    cout << "BST after removing values from shaken vector with larger displacement: ";
    shakeLargerDisplacementBst.print();
    cout << "Comparisons made during removal: " << shakeLargerDisplacementBst.getCount() << endl;

    vector<int> shuffleMoreSwapsVec = {1, 2, 3, 4, 5,6, 7, 8, 9, 10};
    cout << "Original vector: ";
    for (int x : shuffleMoreSwapsVec) {
    cout << x << " ";
    }
    cout << endl;
    shuffle(shuffleMoreSwapsVec, 20);
    cout << "Shuffled vector with more swaps: ";
    for (int x : shuffleMoreSwapsVec) {
        cout << x << " ";
    }
    cout << endl;

    BST shuffleMoreSwapsBst;
    insertValuesFromVector(shuffleMoreSwapsBst, shuffleMoreSwapsVec);
    cout << "BST after inserting values from shuffled vector with more swaps: ";
    shuffleMoreSwapsBst.print();
    cout << "Height of the BST: " << shuffleMoreSwapsBst.height() << endl;
    cout << "Comparisons made during insertion: " << shuffleMoreSwapsBst.getCount() << endl;
    
    shuffleMoreSwapsBst.reset(); // Reset comparison count
    vector<int> removeMoreSwapsValues = {3, 6, 9};
    removeValuesFromVector(shuffleMoreSwapsBst, removeMoreSwapsValues);
    cout << "BST after removing values from shuffled vector with more swaps: ";
    shuffleMoreSwapsBst.print();
    cout << "Comparisons made during removal: " << shuffleMoreSwapsBst.getCount() << endl;
    
    return 0;
}