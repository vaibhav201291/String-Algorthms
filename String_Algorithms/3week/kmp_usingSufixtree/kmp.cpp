#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::vector;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(string &text)
{
  trie t;
  map<char, int>::iterator itrt;
  map<char, int> snode;
  snode.insert(pair<char, int>(' ', 0));
  snode.clear();
  size_t cnode = 0;
  t.reserve(1);
  t.push_back(t[cnode]);
  cout << "size to start with: " << t.size() << endl;
  size_t node_count = 0;
  for (size_t i = 0; i < text.size(); i++)
  {
    cnode = 0;
    for (size_t j = i; j < text.size(); j++)
    {
      cout << j << " " << text[j] << endl;
      itrt = t[cnode].find(text[j]);
      if (itrt != t[cnode].end())
      {
        cout << "Match found" << endl;
        cnode = itrt->second;
      }
      else
      {
        if (text[j] == '$')
        {
          t[cnode].insert(pair<char, int>(text[j], i));
        }
        else
        {
          node_count++;
          cout << "Adding a node" << endl;
          cout << "Size at : " << cnode << "  " << t.size() << endl;
          cout << "Node count is: " << node_count << endl;
          t[cnode].insert(pair<char, int>(text[j], node_count));
          cout << "Insert check" << endl;
          cout << "Size of Map: " << t[cnode].size() << endl;
          t.resize(node_count + 1);
          t.push_back(t[node_count]);
          cnode = node_count;
        }
      }
    }
  }
  t.pop_back();
  cout << "Size of trie: " << t.size() << endl;
  return t;
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where
// the pattern starts in the text.
vector<int> find_pattern(const string &pattern, const string &in_text)
{
  vector<int> result;
  string text = in_text;
  trie txt = build_trie(text);
  map<char, int>::iterator itrt;

  int match = 0;
  int ix = 0;

  for (int i = 0; i < pattern.size(); i++)
  {
    itrt = txt[ix].find(pattern[i]);
    if (itrt != txt[ix].end())
    {
      if (i == pattern.size() - 1)
      {
        match = txt[ix].size();
      }
      else
      {
        ix = itrt->second;
      }
    }
  }

  // for (int i = 0; i < match; i++)
  // {
  //   while (txt[ix]
  // }

  return result;
}

int main()
{
  string pattern, text;
  cin >> pattern;
  cin >> text;
  text += '$';
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i)
  {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
