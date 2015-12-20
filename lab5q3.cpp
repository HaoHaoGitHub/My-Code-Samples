#include <iostream>
#include <fstream>
#include <limits.h>
#include <map>
#include <vector>
#include <string>
#include <stack>
#include <list>
#include <queue>
#include <cstdlib>

using namespace std;

int INFINITY = INT_MAX;

class Vertex {
public:
    string           name;   // Vertex name
    vector<Vertex *> adj;    // Adjacent vertices
    vector<int> weight;
    int              dist;   // Cost
    Vertex          *path;   // Previous vertex on shortest path

    Vertex( const string & nm ) : name( nm )
      { reset( ); }

    void reset( )
      { dist = INFINITY; path = NULL; }
};


typedef map<string,Vertex *> vmap;
typedef pair<string,Vertex *> vpair;


class Graph {
  public:
    Graph( ) { }
    ~Graph( );
    void addEdge( const string & sourceName, const string & destName, const int weight );
    void printPath( const string & destName ) const;
    void unweighted( const string & startName );
    void SHP_weighted( const string & startName );
      
  private:
    Vertex* getVertex( const string & vertexName );
    void printPath( const Vertex & dest ) const;
    void clearAll( );

    vmap vertexMap;
    vector<Vertex *> allVertices;
};

void Graph::addEdge( const string & sourceName, const string & destName ,const int weight) {
    Vertex * v = getVertex( sourceName );
    Vertex * w = getVertex( destName );
    v->adj.push_back( w );
    v->weight.push_back(weight);
}

void Graph::printPath( const string & destName ) const {
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
    {
        printPath( w );
    }
    cout << endl;
}

void Graph::printPath( const Vertex & dest ) const {
    if( dest.path != NULL ) {
        printPath( *dest.path );
        cout << " to ";
    }
    cout << dest.name;
 }

// If vertexName is not present, add it to vertexMap
// In either case, return the Vertex
Vertex * Graph::getVertex( const string & vertexName ) {
    vmap::iterator itr = vertexMap.find( vertexName );

    if( itr == vertexMap.end( ) ) {
        Vertex *newv = new Vertex( vertexName );
        allVertices.push_back( newv );
        vertexMap.insert( vpair( vertexName, newv ) );
        return newv;
    }
    return (*itr).second;
}

void Graph::clearAll( ) {
    for( int i = 0; i < allVertices.size( ); i++ )
        allVertices[ i ]->reset( );
}

Graph::~Graph( ) {
    for( int i = 0; i < allVertices.size( ); i++ )
        delete allVertices[ i ];
}


//------------------------------------------------------
// To decide sorting order of priority queue
class PrioritizeVertices {
public :
    bool operator()(Vertex *x, Vertex *y )
    {
        if (x->dist < y->dist) return true;
        else return false;
    }
};
//------------------------------------------------------

void Graph::SHP_weighted( const string & startName ) {
    clearAll( );

    vmap::iterator itr = vertexMap.find( startName );

    if( itr == vertexMap.end( ) ) {
        cout << startName << " is not a vertex in this graph" << endl;
        return;
    }

    Vertex *start = (*itr).second;
	
	priority_queue<Vertex *, vector<Vertex *>, PrioritizeVertices> prior_q;

	for( int i = 0; i < allVertices.size( ); i++ ) {
        prior_q.push(allVertices[i]);
	}

    Vertex* v = (*itr).second;
	v->dist = 0;
	while (!prior_q.empty()) {
		Vertex *v = prior_q.top();
		prior_q.pop();
		cout << "Node : " << v->name << endl;
		
        for( int i = 0; i < v->adj.size( ); i++ ) {
            Vertex *w = v->adj[ i ];
            int xx = v->weight[i];
            if( w->dist > v->dist+ xx ) {
                w->dist = v->dist + xx;
                w->path = v;
            }
        }
		
    }
}

/**
 * Process a request; return false if end of file.
 */
bool processRequest( istream & in, Graph & g ) {
    string startName;
    string destName;

    cout << "Enter start node: ";
    if( !( in >> startName ) ) return false;
    cout << "Enter destination node: ";
    if( !( in >> destName ) ) return false;

    g.SHP_weighted( startName );
    g.printPath( destName );

    return true;
}


/**
 * A simple main that reads the file given by argv[1]
 * and then calls processRequest to compute shortest paths.
 * Skimpy error checking in order to concentrate on the basics.
 */
int main( int argc, char *argv[ ] ) {
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
    int w;
    // Read the vertices; add them to vertexMap
    while( inFile >> source >> dest >> w )
    {
        g.addEdge( source, dest, w );
    }

    cout << "File read" << endl;
    while( processRequest( cin, g ) )
        ;

    return 0;
}
