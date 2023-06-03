#include<iostream>
#include<queue>
#include<map>
#include<vector>
using namespace std;

class huffmanTree {
public:
	int value;
	char letter;
	huffmanTree*left;
	huffmanTree* right;

	//constructor
	huffmanTree(int val, char c)
	{
		this->value = val;
		this->letter = c;
		this->left = NULL;
		this->right = NULL;
	}

};
    //MinHeap class Node
class MinHeapNode
{
public:
	char data;
	int freq;
	MinHeapNode* left, * right;

	MinHeapNode(char data, int freq)
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

vector <pair<char, int>> CountingChars(string s)
{
	map<char, int> mp;
	for (int i = 0; i < s.size(); i++)
	{
		mp[s[i]]++;
	}
	vector <pair<char, int>> v;
	for (int i = 0; i < s.size(); i++)
	{
		if (mp[s[i]] != 0)
	    {
			v.push_back(make_pair(s[i], mp[s[i]]));
			mp[s[i]] = 0;
	    }
	}

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i].first << " " << v[i].second << endl;
	}
	return v;

}
class compare
{
public:
	bool operator()(MinHeapNode* l, MinHeapNode* r)
	{
		return (l->freq > r->freq);
	}
};
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

map<char, int> freq;
void calcFreq(string str, int n)
{
	for (int i = 0; i < str.size(); i++)
		freq[str[i]]++;
}

map<char, string> codes;
void storeCodes(struct MinHeapNode* root, string str)
{
	if (root == NULL)
		return;
	if (root->data != '$')
		codes[root->data] = str;
	storeCodes(root->left, str + "0");
	storeCodes(root->right, str + "1");
}


void HuffmanCodes(int size)
{
	struct MinHeapNode* left, * right, * top;
	for (map<char, int>::iterator v = freq.begin(); v != freq.end(); v++)
		minHeap.push(new MinHeapNode(v->first, v->second));
	while (minHeap.size() != 1)
	{
		left = minHeap.top();
		minHeap.pop();
		right = minHeap.top();
		minHeap.pop();
		top = new MinHeapNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		minHeap.push(top);
	}
	storeCodes(minHeap.top(), "");
}

void printCodes(struct MinHeapNode* root, string str)
{
	if (!root)
		return;
	if (root->data != '$')
		cout << root->data << ": " << str << "\n";
	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

string decode_file(struct MinHeapNode* root, string s)
{
	string ans = "";
	struct MinHeapNode* curr = root;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '0')
			curr = curr->left;
		else
			curr = curr->right;

		// reached leaf node 
		if (curr->left == NULL && curr->right == NULL)
		{
			ans += curr->data;
			curr = root;
		}
	}
	// cout<<ans<<endl; 
	return ans + '\0';
}

int main()
{
	cout << "----------------------------------------------------------------------------------" << endl;
	string str;
	cout << "Enter the String" << endl;
	cin >> str;
	cout << "\n----------------------------------------------------------------------------------" << endl;
	cout << "The number of Counts Of each Charater is:" << endl;
	vector<pair<char, int>> cnt= CountingChars(str);
	cout << "\n----------------------------------------------------------------------------------" << endl;
	string encodedString;
	string decodedString;

	//calculating frequencies
	calcFreq(str, str.length());

	HuffmanCodes(str.length());

	cout << "Character With their Frequencies:\n";
	for (auto v = codes.begin(); v != codes.end(); v++)
		cout << v->first << ' ' << v->second << endl;

	for (auto i : str)
		encodedString += codes[i];
	cout << "\n----------------------------------------------------------------------------------" << endl;

	cout << "\nEncoding The Given String:\n" << encodedString << endl;

	cout << "\n----------------------------------------------------------------------------------" << endl;

	decodedString = decode_file(minHeap.top(), encodedString);
	cout << "\nDecoding The Given String:\n" << decodedString << endl;

	cout << "\n----------------------------------------------------------------------------------" << endl;
	
	return 0;
}
