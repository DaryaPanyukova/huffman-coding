#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

struct Node {
    int num;
    char symb;

    Node* left, * right;

    Node(int num0, char symb0) {
        num = num0;
        symb = symb0;
        left = right = nullptr;
    }

    Node(int num0, Node* left0, Node* right0) {
        num = num0;
        left = left0;
        right = right0;
    }
};

void Frequency_analysis(std::map <char, int>& letters_num,
                        std::string& text) {
    for (auto symb : text) {
        letters_num[symb]++;
    }
}

void Build_tree(std::map <char, int> &letters_num, Node* &root) {
    auto cmp = [](Node* a, Node* b) { return a->num < b->num; };
    std::multiset <Node*, decltype(cmp)> sorted_nodes(cmp);
    for (auto elem : letters_num) {
        Node* node = new Node(elem.second, elem.first);
        sorted_nodes.insert(node);
    }


    while (sorted_nodes.size() > 1) {
        Node* left = *sorted_nodes.begin();
        sorted_nodes.erase(sorted_nodes.begin());

        Node* right = *sorted_nodes.begin();
        sorted_nodes.erase(sorted_nodes.begin());

        Node* node = new Node(left->num + right->num, left, right);
        sorted_nodes.insert(node);
    }
    root = *sorted_nodes.begin();
}

void Print_tree(std::ofstream& out, Node* tree) {
    if (tree->left == nullptr) {
        out << 0 << ' ' << tree->symb << '\n';
        return;
    }

    out << 1 << '\n';
    Print_tree(out, tree->left);
    Print_tree(out, tree->right);
}


int main()
{
    std::ifstream input("decrypted.txt");
    std::ofstream tree("tree.txt");

    std::string text;
    std::map <char, int> letters_num;
    while (std::getline(input, text)) {
        if (text == "") text = '\n';
        Frequency_analysis(letters_num, text);
    }

    Node* root;
    Build_tree(letters_num, root);    

    Print_tree(tree, root);
    std::cout << "OK";

    input.close(); tree.close();
}

