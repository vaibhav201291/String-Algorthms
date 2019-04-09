#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::vector;

typedef map<char, int> edges;
typedef vector<edges> trie;

// trie build_trie(string &text)
// {

//   return t;
// }

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string &text)
{
  vector<string> result;

  trie t;
  map<char, int>::iterator itrt;
  map<char, int> snode;

  size_t cnode = 0;
  t.reserve(1);
  t.push_back(t[cnode]);
  size_t node_count = 0;
  for (size_t i = 0; i < text.size(); i++)
  {
    cnode = 0;
    for (size_t j = i; j < text.size(); j++)
    {
      itrt = t[cnode].find(text[j]);
      if (itrt != t[cnode].end())
      {
        cnode = itrt->second;
      }
      else
      {
        node_count++;
        if(j == text.size() - 1)// (text[j] == '$')
        {
          cout << "$ encountered... and index is : " << i <<  endl;
          cout << "Current node is " << cnode << endl;
          t[cnode].insert(pair<char, int>(text[j], i));
        }
        else
        {
          t[cnode].insert(pair<char, int>(text[j], node_count));
          t.resize(node_count + 1);
          t.push_back(t[node_count]);
          cnode = node_count;
        }
      }
    }
  }
  t.pop_back();
  cout << "size of trie: " << t.size() << endl;
  for (int i = 0; i < t.size(); i++)
  {
    cout << "Size of map at: " << i << " is  " << t[i].size() << endl;
    for (std::map<char,int>::iterator it=t[i].begin(); it!=t[i].end(); ++it)
    std::cout << it->first << " => " << it->second << "  ";
    cout << endl;
  }

  vector<int> index;
  for (int i = 0; i < t.size(); i++)
  {
    itrt = t[i].find('$');
    if (itrt != t[cnode].end())
    {
      cout << "$ found in node: " << i << " and is " << itrt->second << endl;
      index.push_back(itrt->second);
    }
  }
  cout << "Number of strings: " << index.size() << endl;

  string cstr;
  for (int i = 0; i < index.size(); i++)
  {
    int start = index[i];
    cstr.clear();
    for (int j = start; j < text.size(); j++)
    {
      cstr += text[j];
    }
    result.push_back(cstr);
  }
  cout << "Size of result: " << result.size() << endl;
  return result;
}

int main()
{
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i)
  {
    cout << edges[i] << endl;
  }
  return 0;
}
