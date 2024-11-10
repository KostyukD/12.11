#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class TreeNode 
{
public:
    string word;
    string translation;
    int accessCount;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string word, string translation) : word(word), translation(translation), accessCount(0), left(nullptr), right(nullptr) {}
};

class Dictionary 
{
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, string word, string translation) 
    {
        if (node == nullptr) 
        {
            return new TreeNode(word, translation);
        }
        if (word < node->word) 
        {
            node->left = insert(node->left, word, translation);
        }
        else if (word > node->word) 
        {
            node->right = insert(node->right, word, translation);
        }
        else 
        {
            node->translation = translation; 
        }
        return node;
    }

    TreeNode* find(TreeNode* node, string word) 
    {
        if (node == nullptr || node->word == word)
        {
            return node;
        }
        if (word < node->word) 
        {
            return find(node->left, word);
        }
        else 
        {
            return find(node->right, word);
        }
    }

    TreeNode* remove(TreeNode* node, string word) 
    {
        if (node == nullptr)
        {
            return node;
        }
        if (word < node->word)
        {
            node->left = remove(node->left, word);
        }
        else if (word > node->word) 
        {
            node->right = remove(node->right, word);
        }
        else {
            if (node->left == nullptr) 
            {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) 
            {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* temp = findMin(node->right);
            node->word = temp->word;
            node->translation = temp->translation;
            node->accessCount = temp->accessCount;
            node->right = remove(node->right, temp->word);
        }
        return node;
    }

    TreeNode* findMin(TreeNode* node) 
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    void inOrderTraversal(TreeNode* node, int& maxCount, string& popularWord, int& minCount, string& unpopularWord) 
    {
        if (node == nullptr) 
        {
            return;
        }
        inOrderTraversal(node->left, maxCount, popularWord, minCount, unpopularWord);

        if (node->accessCount > maxCount) 
        {
            maxCount = node->accessCount;
            popularWord = node->word;
        }

        if (node->accessCount < minCount) 
        {
            minCount = node->accessCount;
            unpopularWord = node->word;
        }

        inOrderTraversal(node->right, maxCount, popularWord, minCount, unpopularWord);
    }

public:
    Dictionary() : root(nullptr) {}

    void insert(string word, string translation) 
    {
        root = insert(root, word, translation);
    }

    void findAndDisplay(string word) 
    {
        TreeNode* node = find(root, word);
        if (node != nullptr) 
        {
            node->accessCount++;
            cout << "Translation of " << word << ": " << node->translation << endl;
        }
        else 
        {
            cout << "Word not found" << endl;
        }
    }

    void update(string word, string newTranslation) 
    {
        TreeNode* node = find(root, word);
        if (node != nullptr) 
        {
            node->translation = newTranslation;
        }
        else 
        {
            cout << "Word not found" << endl;
        }
    }

    void remove(string word) 
    {
        root = remove(root, word);
    }

    void displayMostPopularWord() 
    {
        int maxCount = -1;
        string popularWord = "";
        int minCount = INT_MAX;
        string unpopularWord = "";
        inOrderTraversal(root, maxCount, popularWord, minCount, unpopularWord);

        cout << "Most popular word: " << popularWord << " with " << maxCount << " accesses" << endl;
    }

    void displayLeastPopularWord() 
    {
        int maxCount = -1;
        string popularWord = "";
        int minCount = INT_MAX;
        string unpopularWord = "";
        inOrderTraversal(root, maxCount, popularWord, minCount, unpopularWord);

        cout << "Least popular word: " << unpopularWord << " with " << minCount << " accesses" << endl;
    }
};

int main() 
{
    Dictionary dictionary;
    dictionary.insert("hello", "привет");
    dictionary.insert("world", "мир");
    dictionary.insert("tree", "дерево");
    dictionary.findAndDisplay("hello");
    dictionary.findAndDisplay("world");
    dictionary.update("tree", "деревцо");
    dictionary.remove("world");
    dictionary.displayMostPopularWord();
    dictionary.displayLeastPopularWord();
}
