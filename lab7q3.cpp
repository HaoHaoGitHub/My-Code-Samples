#include <iostream>
#include<fstream>
#include <string>
#include<map>
#include<vector>
#include<queue>

using namespace std;
float totalCost;

/*
 *  HuffNode.h
 *  Huffman
 *
 *  Created by David Rappaport on 22/02/07. 
 *  Copied from MArk Nelson's Priority queues and the STL article at URL
 * http://www.dogma.net/markn/articles/pq_stl/priority.htm
 *
 */

//
// The HuffNode class is used to represent both leaf
// and internal nodes. leaf nodes have 0s in the
// child pointers, and their symbol member corresponds
// to the character they encode.  internal nodes
// don't have anything meaningful in their symbol
// member, but their child pointers point to
// other nodes.
//

class HuffNode {
public:
  char symbol;
  int weight;
  HuffNode *left, *right;
  HuffNode() {
    left = right = 0;
  }
  HuffNode(char s, int f, 
	   HuffNode *lt = 0, HuffNode *rt = 0) {
    symbol = s; 
    weight = f; 
    left = lt; right = rt;
  }
    
  HuffNode(  HuffNode* c0,  HuffNode *c1 ) {
    symbol = 0;
    weight = c0->weight + c1->weight;
    left = c0;
    right = c1;
  }
    
  //
  //bool operator > (const HuffNode & other);
  //
  // The comparison operator used to order the
  // priority queue.
  //
  bool operator > ( const HuffNode & other ) const {
    return weight > other.weight;
  }
  void traverse( string code);
  float traverseGetCost();
};

//
// The traverse member function is used to
// print out the code for a given node.  It
// is designed to print the entire tree if
// called for the root node.
//

void HuffNode::traverse( string code ) {
    
    
  if ( left ) {
    left->traverse( code + "0" );
    right->traverse( code + "1" );
  } else {
    cout << " " << symbol << "      ";
    cout << weight;
    cout << "     " << code << endl;
    totalCost += weight * code.size();
  }
}

float HuffNode::traverseGetCost(){
  traverse("");
  return totalCost;
}


int main (int argc, char * const argv[]) {
  // Get frequency of symbols in the file
  char filename[30];
  ifstream inStream;
    
  map<const char, int > freqMap;
  map<const char, int > ::iterator it;
  priority_queue< HuffNode, vector<HuffNode>, greater<HuffNode> > q;
  HuffNode *hNode;
    
  char ch;
    
  //  cout << " Filename please.  \n";
  //cin >> filename;
  //inStream.open(filename);
    
    
  //if (inStream.fail()){
  //cout << "Error in opening file \n";
  //  exit(1);
  //}
  //Now read all characters in the file and count the frequencies.
    
  int count,ii,y;
  count = 27;
  ii =0;
  while ( ii < count)
    { 
      cin >> ch >> y;
      freqMap[ch]=y;
      ii++;
    }
  //while( !inStream.eof()) {
  //  it = freqMap.find(ch);
  //  if (it == freqMap.end())
  //    freqMap[ch] = 1;
  //  else
  //    freqMap[ch]++;
  //  inStream.get(ch);
  //}
    
    
  int numSym = 0; // To count the number of symbols

  // Initialize forest of Huffman trees. 
  // Step 1. Copy map items into a priority queue
  it = freqMap.begin();
  while(it != freqMap.end()){
    hNode = new HuffNode(it->first, it->second);
    q.push(*hNode);
    numSym += it->second;
    it++;
  }

  //I'm done with the map now I should be able to free up the memory

  freqMap.clear();

  //
  // This loop removes the two smallest nodes from the
  // queue.  It creates a new internal node that has
  // those two nodes as children. The new internal node
  // is then inserted into the priority queue.  When there
  // is only one node in the priority queue, the tree
  // is complete.
  //

  while ( q.size() > 1 ) {
    HuffNode *left = new HuffNode( q.top() );
    q.pop();
    HuffNode *right = new HuffNode( q.top() );
    q.pop();
    q.push( HuffNode( left, right ) );
  }
  //
  // Now I dump the results
  //
  cout << "Char  Symbol   Code" << endl;
  *hNode = q.top();
  totalCost = hNode->traverseGetCost();
  // Average number of bits per character
  cout << "Total Cost " << totalCost << ".  Average bits per symbol " << totalCost/ numSym*1.0 << endl;

  return 0;
}