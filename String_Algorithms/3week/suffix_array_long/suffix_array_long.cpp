#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.

int letterToIndex(char letter)
{
  // cout << "letter to be checked: " << letter << endl;
  switch (letter)
  {
  case '$':
    return 0;
  case 'A':
    return 1;
    break;
  case 'C':
    return 2;
    break;
  case 'G':
    return 3;
    break;
  case 'T':
    return 4;
    break;
  default:
    assert(false);
    return -1;
  }
}

vector<int> SortCharacters(string &t)
{
  int n = t.size();
  // cout << "Size of text : " << n << endl;
  vector<int> ord(n);
  vector<int> count(5);
  for(int i = 0; i < n; i++)
  {
    count[letterToIndex(t[i])] = count[letterToIndex(t[i])] + 1;
  }

  for(int j = 0; j < 5; j++)
  {
    count[j] = count[j] + count[j - 1];
  }

  int c;
  for(int i = n - 1; i >= 0; i--)
  {
    c = letterToIndex(t[i]);
    count[c] = count[c] - 1;
    ord[count[c]] = i;
  }

  // for(int i = 0; i < n; i++)
  // {
  //   cout << ord[i] << "  ";
  // }
  // cout << endl;
  // cout << "order generated..." << endl;
  return ord;
}

vector<int> ComputeCharClasses(string &t, vector<int> &ord)
{
  // cout << "Computing char classes.:::" << endl;
  int n = t.size();
  vector<int> cl(n);
  cl[ord[0]] = 0;

  for (int i = 1; i < n; i++)
  {
    if (t[ord[i]] != t[ord[i - 1]])
    {
      cl[ord[i]] = cl[ord[i - 1]] + 1;
    }
    else
    {
      cl[ord[i]] = cl[ord[i - 1]];
    }
  }
  // for(int i = 0; i < n; i++)
  // {
  //   cout << cl[i] << "  ";
  // }
  // cout << endl;
  // cout << "Char classs computed." << endl;
  return cl;
}

vector<int> SortDoubled(string &t, int l, vector<int> &ord, vector<int> &cl)
{
  // cout << "In sort doubled... " << endl;
  int n = t.size();
  vector<int> n_ord(n);
  int count[n];
  for (int i = 0; i < n; i++)
  {
    count[i] = 0;
  }

  for (int i = 0; i < n; i++)
  {
    count[cl[i]] = count[cl[i]] + 1;
  }

  for (int j = 1; j < n; j++)
  {
    count[j] = count[j] + count[j - 1];
  }

  int cs, start;

  for (int i = n - 1; i >= 0; i--)
  {
    start = (ord[i] - l + n) % n;
    cs = cl[start];
    count[cs] = count[cs] - 1;
    n_ord[count[cs]] = start;
  }
  // for(int i = 0; i < n; i++)
  // {
  //   cout << n_ord[i] << "  ";
  // }
  // cout << endl;
  // cout << "New order generated." << endl;

  return n_ord;
}

vector<int> UpdatedClasses(vector<int> &ord, vector<int> &cl, int &l)
{
  // cout << "Updating classe..." << endl;
  int n = ord.size();
  vector<int> n_cl(ord.size());
  n_cl[ord[0]] = 0;

  int cur, prev, mid, mid_prev;

  for (int i = 1; i < n; i++)
  {
    cur = ord[i];
    prev = ord[i -1];
    mid = (cur + l) % n;
    mid_prev = (prev + l) % n;
    if (cl[cur] != cl[prev] || cl[mid] != cl[mid_prev])
    {
      n_cl[cur] = n_cl[prev] + 1;
    }
    else
    {
      n_cl[cur] = n_cl[prev];
    }
  }
  
  // for(int i = 0; i < n; i++)
  // {
  //   cout << n_cl[i] << "  ";
  // }
  // cout << endl;
  // cout << "New class essential generated." << endl;

  return n_cl;
}

vector<int> BuildSuffixArray(const string &text_act)
{
  vector<int> result;
  vector<int> order(text_act.size());
  vector<int> classE(text_act.size());
  string text = text_act;

  order = SortCharacters(text);
  classE = ComputeCharClasses(text, order);

  int l = 1;

  while (l < text.size())
  {
    // cout << "For length = " << l << endl;
    order = SortDoubled(text, l, order, classE);
    classE = UpdatedClasses(order, classE, l);
    l = 2 * l;
  }
  result = order;

  return result;
}

int main()
{
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i)
  {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
