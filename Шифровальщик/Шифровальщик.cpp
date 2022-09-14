#include <iostream>
#include <string>
#include <fstream>
#include <map>


struct Node {
    bool leaf;
    char symb;
    Node* left, * right;

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

void Get_codes(std::map <char, std::string> &m, Node* tree, std::string cur) {
    if (tree->left == nullptr) {
        m[tree->symb] = cur;
        return;
    }
    Get_codes(m, tree->left, cur + '0');
    Get_codes(m, tree->right, cur + '1');
}



int main()
{
    std::ifstream f_tree("tree.txt");
    std::ifstream f_text("decrypted.txt");
    std::ofstream out("incrypted.txt");


    Node* root = Build_tree(f_tree);

    std::map <char, std::string> codes;
    Get_codes(codes, root, "");
    
    std::string text;
    while (std::getline(f_text, text)) {
        if (text == "") text = '\n';
        for (auto elem : text) {
            out << codes[elem];
        }
        out << codes['\n'];

    }
   
    std::cout << "OK";
    out.close(); f_tree.close(); f_text.close();
}

