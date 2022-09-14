#include <iostream>
#include <fstream>
#include <string>

struct Node {
    bool leaf;
    char symb;
    Node *left, *right;

    Node(char symb0) {
        symb = symb0;
        left = right = nullptr;
        leaf = true;
    }

    Node() { leaf = false; }
};

Node* Build_tree(std::ifstream& in) {
    std::string s;
    std::getline(in, s);

    char type = s[0];

    if (type == '0' && s.size() == 2) {
        char symb = '\n';
        std::getline(in, s);
        Node* node = new Node(symb);
        return node;
    } else if (type == '0') {
        char symb = s[2];
        Node* node = new Node(symb);
        return node;
    } 

    Node* node = new Node;
    node->left = Build_tree(in);
    node->right = Build_tree(in);
    return node;
}

char Find_symb_code(std::ifstream& in, Node* tree, int &ind) {
    if (in.eof()) return -1;

    if (tree->left == nullptr) {
        ind++;
        return tree->symb;
    } else {
        char next;
        in >> next;
        ind += 1;
        if (next == '0') Find_symb_code(in, tree->left, ind);
        else { Find_symb_code(in, tree->right, ind); }
    }
}


int main()
{
    std::ifstream f_tree("tree.txt");
    std::ifstream f_code("incrypted.txt");
    std::ofstream out("decrypted.txt");

    Node* root = Build_tree(f_tree);

    int ind = 0;
    for (;;) {
        char res = Find_symb_code(f_code, root, ind);
        if (res != -1) {
            out << res;
        } else {
            break;
        }
    }

    std::cout << "OK";
    out.close();
}
