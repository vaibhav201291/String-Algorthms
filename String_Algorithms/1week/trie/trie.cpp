#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::vector;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> &patterns)
{
  trie t;
  map<char, int>::iterator itrt;
  map<char, int> snode;
  // snode.insert(pair<char, int>(' ', 0));
  // snode.clear();
  size_t cnode = 0;
  t.reserve(1);
  t.push_back(t[cnode]);
  // cout << "size to start with: " << t.size() << endl;
  size_t node_count = 0;
  for (size_t i = 0; i < patterns.size(); i++)
  {
    cnode = 0;
    for (size_t j = 0; j < patterns[i].size(); j++)
    {
      // cout << j << " " << patterns[i][j] << endl;
      itrt = t[cnode].find(patterns[i][j]);
      if (itrt != t[cnode].end())
      {
        // cout << "hit the end" << endl;
        cnode = itrt->second;
      }
      else
      {
        node_count++;
        // cout << "Adding a node" << endl;
        // cout << "Size at : " << cnode << "  " << t.size() << endl;
        // cout << "Node count is: " << node_count << endl;
        t[cnode].insert(pair<char, int>(patterns[i][j], node_count));
        // cout << "Insert check" << endl;
        t.resize(node_count + 1);
        t.push_back(t[node_count]);
        cnode = node_count;
        // cout << "second element: " << t[cnode].end()->second << endl;
      }
    }
  }
  t.pop_back();
  //cout << "Size of trie: " << t.size() << endl;

  return t;
}

int main()
{
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++)
  {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  // cout << t.size() << endl;
  for (size_t i = 0; i < t.size(); ++i)
  {
    for (const auto &j : t[i])
    {
      // cout << t[i].size() << endl;
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}