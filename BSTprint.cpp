#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <iomanip>

class BST {
    public:
        BST();
        ~BST();
        void insertKey(int newKey);
        bool hasKey(int searchKey);
        std::vector<int> inOrder();
        int getHeight();
        void prettyPrint();
    private:
        class Node {
        public:
            Node(int insertKey);
            ~Node();
            int key;
            Node* left;
            Node* right;
        };
        Node* root;
        void insertHelper(Node*& root, int insertKey);
        bool hasKeyHelper(Node*& root, int searchKey);
        void inOrderHelper(Node*& root, std::vector<int> &orderedTree);
        int getHeightHelper(Node*& root);
        void prettyPrintHelper(Node*& root, std::vector< std::vector<int> > &treeMatrix, int &heightIndex, int widthIndex);
};

BST::BST() {
    root = nullptr;
}

BST::~BST() {
    if (root != nullptr) {
        delete root;
    }
}

BST::Node::Node(int insertKey) {
    left = right = nullptr;
    key = insertKey;
}

BST::Node::~Node() {
    if (left != nullptr) {
        delete left;
    }
    if (right != nullptr) {
        delete right;
    }
}


void BST::insertKey(int newKey) {
    insertHelper(root, newKey);
}

void BST::insertHelper(Node*& root, int insertKey) {
    if (root == nullptr) {
        root = new Node(insertKey);
    }
    else if (insertKey > root->key) {
        insertHelper(root->right, insertKey);
    }
    else {
        insertHelper(root->left, insertKey);
    }
}


bool BST::hasKey(int searchKey) {
    return hasKeyHelper(root, searchKey);
}

bool BST::hasKeyHelper(Node*& root, int searchKey) {
    if (root == nullptr) {
        return false;
    }
    else if (root->key == searchKey) {
        return true;
    }
    else if (root->key < searchKey) {
        return hasKeyHelper(root->right, searchKey);
    }
    else {
        return hasKeyHelper(root->left, searchKey);
    }
}


std::vector<int> BST::inOrder() { 
    std::vector<int> orderedTree;
    inOrderHelper(root, orderedTree);
    return orderedTree;
}

void BST::inOrderHelper(Node*& root, std::vector<int> &orderedTree){
    if (root == nullptr) {
        return;
    }
    
    inOrderHelper(root->left, orderedTree);

    orderedTree.push_back(root->key);

    inOrderHelper(root->right, orderedTree);
}


int BST::getHeight() {
    return getHeightHelper(root);
}

int BST::getHeightHelper(Node*& root) {
    if (root == nullptr) {
        return 0;
    }
    else {
        int lHeight = getHeightHelper(root->left);
        int rHeight = getHeightHelper(root->right);

        if (lHeight > rHeight) {
            return lHeight + 1;
        }
        else {
            return rHeight + 1;
        }
    }
}


void BST::prettyPrint() {
    if (inOrder().size() != 0) {
        std::vector< std::vector<int> > treeMatrix(getHeight(), std::vector<int> (inOrder().size(), INT_MAX));
        int heightIndex, widthIndex;
        heightIndex = widthIndex = 0;
        
        prettyPrintHelper(root, treeMatrix, heightIndex, widthIndex);

        std::cout << std::setfill('-') << std::setw((treeMatrix.at(0).size()) * 5 + 1) << "";
        std::cout << std::endl;

        for (int i = 0; i < treeMatrix.size(); i++) {
            for (int j = 0; j < treeMatrix.at(0).size(); j++) {
                if (treeMatrix.at(i).at(j) == INT_MAX) {
                    std::cout << "|    ";
                }
                else {
                    std::cout << "|" << std::setfill(' ') << std::setw(4) << treeMatrix.at(i).at(j);
                }
            }
            std::cout << "|";
            std::cout << std::endl;
            std::cout << std::setfill('-') << std::setw(treeMatrix.at(0).size() * 5 + 1) << "";
            std::cout << std::endl;   
        }
    }
}

void BST::prettyPrintHelper(Node*& root, std::vector< std::vector<int> > &treeMatrix, int &heightIndex, int widthIndex) {
    if (root == nullptr) {
        return;
    }

    widthIndex = 0;
    while (root->key != inOrder().at(widthIndex)) {
        widthIndex++;
    }

    if (root->left != nullptr) {
        heightIndex++;
        prettyPrintHelper(root->left, treeMatrix, heightIndex, widthIndex);
    }

    treeMatrix.at(heightIndex).at(widthIndex) = root->key;

    if (root->right != nullptr) {
        heightIndex++;
        prettyPrintHelper(root->right, treeMatrix, heightIndex, widthIndex);
        heightIndex--;
        return;
    }
    heightIndex--;
    return;
}


int main() {
    int searchKey;
    char lastChar;
    BST* tree = new BST;
    std::vector<int> inOrder;

    std::cout << "Enter the numbers to be stored: ";

    while (std::cin.good()){
        int number;
        std::cin >> number;
        if (std::cin.good()){
            tree->insertKey(number);
        }
    }

    std::cin.clear();
    std::cin >> lastChar;
    std::cout << std::endl;

    inOrder = tree->inOrder();

    std::cout << "The numbers in sorted order: ";
    
    for (int i = 0; i < inOrder.size(); i++) {
        std::cout << inOrder.at(i) << " ";
    }
    
    std::cout << std::endl;

    tree->prettyPrint();
    
    delete tree;

    return 0;
}
