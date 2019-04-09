#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters = 4;
int const NA = -1;

struct Node
{
	int next[Letters];

	Node()
	{
		fill(next, next + Letters, NA);
	}

	bool isLeaf() const
	{
		return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

int letterToIndex(char letter)
{
	// cout << "letter to be checked: " << letter << endl;
	switch (letter)
	{
	case 'A':
		return 0;
		break;
	case 'C':
		return 1;
		break;
	case 'G':
		return 2;
		break;
	case 'T':
		return 3;
		break;
	default:
		assert(false);
		return -1;
	}
}

vector<int> solve(const string &text, int n, const vector<string> &patterns)
{
	vector<int> result;
	vector<Node> nodes;

	//To creat trie
	int cnode = 0;
	nodes.reserve(1);
	// for (int id = 0; id < Letters; id++)
	// {
	// 	cout << nodes[cnode].next[id] << endl;
	// }
	nodes.push_back(nodes[cnode]);
	for (int id = 0; id < Letters; id++)
	{
		nodes[cnode].next[id] = NA;
	}
	// for (int id = 0; id < Letters; id++)
	// {
	// 	cout << nodes[cnode].next[id] << endl;
	// }
	int node_count = 0;
	int itrt;
	for (int i = 0; i < patterns.size(); i++)
	{
		cnode = 0;
		for (int j = 0; j < patterns[i].size(); j++)
		{
			// cout << "size of Pattern: " << patterns[i].size() << endl;
			itrt = nodes[cnode].next[letterToIndex(patterns[i][j])];
			// cout << "itrt at " << j + 1 << " is " << itrt << endl;
			if (itrt != NA)
			{
				// cout << "Found a node" << endl;
				cnode = itrt;
			}
			else
			{
				// cout << "No node" << endl;
				node_count++;
				nodes[cnode].next[letterToIndex(patterns[i][j])] = node_count;
				nodes.resize(node_count + 1);
				nodes.push_back(nodes[node_count]);
				for (int id = 0; id < Letters; id++)
				{
					nodes[node_count].next[id] = NA;
				}
				cnode = node_count;
			}
		}
	}
	//Trie generated
	// cout << "Trie Generated.... " << endl;
	// cout << "Number of nodes: " << nodes.size() << endl;

	// for (int i = 0; i < nodes.size(); i++)
	// {
	// 	for (int j = 0; j < Letters; j++)
	// 	{
	// 		cout << nodes[i].next[j] << "   ";
	// 	}
	// 	cout << endl;
	// }

	for (int i = 0; i < text.size(); i++)
	{
		// cout << "text is at " << i + 1 << endl;
		int ind = 0;
		int leaf = 0;
		int j = i;
		while (!leaf && j < text.size())
		{
			if (!nodes[ind].isLeaf())
			{
				// cout << "NOT a leaf. " << endl;
				// cout << "#node: " << nodes[ind].next[letterToIndex(text[j])] << endl;
				if (nodes[ind].next[letterToIndex(text[j])] == -1)
				{
					// cout << "no match found" << endl;
					goto exit;
				}
				else
				{
					ind = nodes[ind].next[letterToIndex(text[j])];
					// cout << "Match found and index is: " << ind << endl;
				}
			}
			else
			{
				// cout << "Leaf encontered." << endl;
				result.push_back(i);
				leaf = 1;
				goto exit;
			}
			j++;
			if((j == text.size()) && (nodes[ind].isLeaf()))
			{
				// cout << "Leaf encontered." << endl;
				result.push_back(i);
				leaf = 1;
			}
		}
	exit:;
	}
	// cout << "Number of matches: " << result.size() << endl;
	for (int i = 0; i < result.size(); i++)
	// {
	// 	cout << result[i] << "   ";
	// }

	// cout << endl;

	return result;
}

int main(void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector<string> patterns(n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector<int> ans;
	ans = solve(t, n, patterns);

	for (int i = 0; i < (int)ans.size(); i++)
	{
		cout << ans[i];
		if (i + 1 < (int)ans.size())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
