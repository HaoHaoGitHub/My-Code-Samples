#include <iostream>
#include <fstream>
#include <limits.h>
#include <map>
#include <vector>
#include <string>
#include <stack>
#include <list>
#include<queue>

using namespace std;

int INFINITY = INT_MAX;

class Vertex {
public:
    string           name;   // Vertex name
    vector<pair<Vertex*, int> > adj;    // Adjacent vertices
    int              dist;   // Cost
    Vertex          *path;   // Previous vertex on shortest path

    Vertex( const string & nm ) : name( nm )
      { reset( ); }

    void reset( )
      { dist = INFINITY; path = NULL; }
};


typedef map<string,Vertex *> vmap;
typedef pair<string,Vertex *> vpair;
typedef pair<Vertex*, int> wpair;

class Graph
{
  public:
    Graph( ) { }
    ~Graph( );
    void addEdge( const string & sourceName, const string & destName, const int& cost );
    void printPath( const string & destName ) const;
    void unweighted( const string & startName );
    void min_sp_tree(const string & startName);  // shortest path alg
      
  private:
    Vertex * getVertex( const string & vertexName );
    void printPath( const Vertex & dest ) const;
    void clearAll( );

    vmap vertexMap;
    vector<Vertex *> allVertices;
};

// ======given by lab file===============================
class PrioritizeVertices {
public :
    bool operator()(Vertex *x, Vertex *y )
    {
  if (x->dist > y->dist) return true;   // not sure here, changed by me
    else return false;
    }
};
// ======================================================

void Graph::addEdge( const string & sourceName, const string & destName, const int& length )
{
    Vertex * v = getVertex( sourceName );
    Vertex * w = getVertex( destName );
    v->adj.push_back( wpair(w, length) );
}

void Graph::printPath( const string & destName ) const
{
    vmap::const_iterator itr = vertexMap.find( destName );

    if( itr == vertexMap.end( ) )
    {
        cout << "Destination vertex not found" << endl;
        return;
    }

    const Vertex & w = *(*itr).second;
    if( w.dist == INFINITY )
        cout << destName << " is unreachable";
    else
        printPath( w );
    cout << endl;
}

// If vertexName is not present, add it to vertexMap
// In either case, return the Vertex
Vertex * Graph::getVertex( const string & vertexName )
{
    vmap::iterator itr = vertexMap.find( vertexName );

    if( itr == vertexMap.end( ) )
    {
        Vertex *newv = new Vertex( vertexName );
        allVertices.push_back( newv );
        vertexMap.insert( vpair( vertexName, newv ) );
        return newv;
    }
    return (*itr).second;
}

void Graph::printPath( const Vertex & dest ) const
{
    if( dest.path != NULL )
    {
        printPath( *dest.path );
        cout << " to ";
    }
    cout << dest.name;
}

void Graph::clearAll( )
{
    for( int i = 0; i < allVertices.size( ); i++ )
        allVertices[ i ]->reset( );
}

Graph::~Graph( )
{
    for( int i = 0; i < allVertices.size( ); i++ )
        delete allVertices[ i ];
}

// ================================================
void Graph::min_sp_tree(const string & startName) {
    clearAll();
    // set dist(s)=0, dist(u)=infinity
    Vertex* s = getVertex(startName);
    s->dist = 0;
    for (int i = 0; i < allVertices.size(); ++i) {
        if (allVertices[i] != s)
            allVertices[i]->dist = INT_MAX;
    }
    // insert all vertices in priority queue
    priority_queue < Vertex *, vector <Vertex *>, PrioritizeVertices> prior_q;
    for( int i = 0; i < allVertices.size( ); i++ ) {
        prior_q.push(allVertices[i]);
    }
    // while pq not empty
    while( !prior_q.empty()) {
        //get top (which is min by def here) and delete min
        Vertex* v = prior_q.top();
        prior_q.pop();
        // for all edges u of v, compare dist(u) and w(u, v), diff from shortest path here
        for (int i = 0; i < v->adj.size(); ++i) {
            if(v->adj[i].first->dist > v->adj[i].second) 
                v->adj[i].first->dist = v->adj[i].second;
            // decrease key u
            priority_queue < Vertex *, vector <Vertex *>, PrioritizeVertices> tmp_pq;
            while (!prior_q.empty()) {
                tmp_pq.push(prior_q.top());
                prior_q.pop();
            }
            prior_q.swap(tmp_pq);
        }
        if (!prior_q.empty()) {
            cout << "Tree edge: " << v->name << " " << prior_q.top()->name << endl;
        }
    }
}
// ================================================
/**
 * Process a request; return false if end of file.
 */
bool processRequest( istream & in, Graph & g )
{
    string startName;
    string destName;

    cout << "Enter start node: ";
    if( !( in >> startName ) ) return false;
        // changed from here
    g.min_sp_tree(startName);
    return true;
}


/**
 * A simple main that reads the file given by argv[1]
 * and then calls processRequest to compute shortest paths.
 * Skimpy error checking in order to concentrate on the basics.
 */
int main( int argc, char *argv[ ] )
{
    Graph g;

    if( argc != 2 )
    {
        cerr << "Usage: " << argv[ 0 ] << " graphfile" << endl;
        return 1;
    }

    ifstream inFile( argv[ 1 ] );
    if( !inFile )
    {
        cerr << "Cannot open " << argv[ 1 ] << endl;
        return 1;
    }

    string source, dest;
    int length;

    // Read the vertices; add them to vertexMap
    while( inFile >> source >> dest >> length)
    {
        g.addEdge(source, dest, length );
         g.addEdge(dest, source, length);   // undirected here  
    }

    cout << "File read" << endl;
    processRequest( cin, g );
    

    return 0;
}

