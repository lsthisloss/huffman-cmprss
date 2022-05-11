#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

// A Tree node
struct Node
{
	char ch;
	int freq;
	Node* left, * right; 
};

Node* getNode(char ch, int freq, Node* left, Node* right) 
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

struct comp
{
	bool operator()(Node* l, Node* r) 
	{
		return l->freq > r->freq; 
	}
};

void encode(Node* root, string str,
	unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;
	
	if (!root->left && !root->right)
	{
		huffmanCode[root->ch] = str;
	}
	encode(root->right, str + "1", huffmanCode);
	encode(root->left, str + "0", huffmanCode);
}

void decode(Node* root, int& index, string str)
{
	if (root == nullptr)
	{
		return;
	}

	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}
	index++;
	if (str[index] == '1')
		decode(root->right, index, str);
	else
		decode(root->left, index, str);
}

void buildHuffmanTree(string text)
{
	string temp = "";
	double entropy = 0;
	int numlen = text.length();

	unordered_map<char, int> freq;
	priority_queue<Node*, vector<Node*>, comp> pq;

	for (char ch : text)
	{
		freq[ch]++;
	}

	for (pair<char, int> p : freq) {
		double freq = static_cast<double>(p.second) / numlen;
		entropy -= freq * log2(freq);
	}

	cout << "------------------------------------"<< endl;
	cout << endl << "Frequencies table : ";
	for (auto pair : freq)
	{
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
		cout << endl;
		cout << pair.first << " : " << pair.second << " : " << (float)pair.second / text.size();
	}   

	while (pq.size() != 1)
	{
		Node* left = pq.top();
		pq.pop();
		Node* right = pq.top();
		pq.pop();
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	Node* root = pq.top();
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << endl << endl << "Huffman Codes are : " << endl;
	for (auto pair : huffmanCode)
	{
		cout << pair.first << " : " << pair.second << endl;
	}
	
	for (char ch : text)
	{
		temp += huffmanCode[ch];
	}

	cout << endl<< "Encoded string is : "<< temp << endl;
	int index = -1;
	cout << endl<< "Decoded string is : ";

	while (index < (int)temp.size() -1)
	{
		decode(root, index, temp);
	}
	cout << endl << endl;
	cout << "Entropy is : " << entropy << endl;
	cout << endl << "------------------------------------" << endl;
}

int main()
{

	string str;
	cout << "Please, input text : ";
	getline(cin, str);
	buildHuffmanTree(str);

	return 0;
}