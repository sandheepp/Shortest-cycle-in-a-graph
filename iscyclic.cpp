// A C++ Program to detect cycle in a graph 
#include <iostream> 
#include <list> 
#include <limits.h> 

using namespace std; 
int count =0;
class Graph 
{ 
	int V; // No. of vertices 
	list<int> *adj; // Pointer to an array containing adjacency lists 
	bool isCyclicUtil(int v, bool visited[], bool *rs); // used by isCyclic() 

public: 
	Graph(int V); // Constructor of this class
	void addEdge(int v, int w); // fucntion defenition to add an edge to graph 
	bool isCyclic(); // fucntion declaration, returns true if there is a cycle in this graph 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new list<int>[V]; 
} 


// To add an edge to the graph
void Graph::addEdge(int v, int w) 
{ 
	adj[v].push_back(w); // Add w to v’s list. 
} 

// This function is a variation of DFSUtil() in https://www.geeksforgeeks.org/archives/18212
// visited[] and *recStack are the same variable declaration type 
bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack) 
{ 
	// printf("%d",v);
	if(visited[v] == false) 
	{ 
		// Mark the current node as visited and part of recursion stack
		// printf("%d",v) ; // To print the path in which the control travels
		visited[v] = true; 
		recStack[v] = true; 

		// Recur for all the vertices adjacent to this vertex 
		list<int>::iterator i; 
		for(i = adj[v].begin(); i != adj[v].end(); ++i) 
		{ 
			if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )  // not (visited is false) && ..
				{ 
				return true; 
				}
			else if (recStack[*i]) // Place where you find a cycle
				{
				printf("Found a cycle at node %d\n", v+1);
				count =1;
				flag=0;
				// return true;
				continue; 
				}
		} 
	} 
	recStack[v] = false; // remove the vertex from recursion stack 
	return false; 
} 

// Returns true if the graph contains a cycle, else false. 
bool Graph::isCyclic() 
{ 
	// Mark all the vertices as not visited and not part of recursion 
	// stack 
	bool *visited = new bool[V]; 
	bool *recStack = new bool[V]; 
	for(int i = 0; i < V; i++) 
	{ 
		visited[i] = false; 
		recStack[i] = false; 
	} 

	// Call the recursive helper function to detect cycle in different 
	// DFS trees 
	for(int i = 0; i < V; i++) 
		if (isCyclicUtil(i, visited, recStack)) 
			{	return true;
			} 
	if (count ==0){
		cout << "Graph doesn't contain cycle\n";
	}
	return false; 
} 

int main() 
{ 
//User input data
   int n,m;
   scanf("%d %d", &n, &m);

   int u[m] , v[m] ;
   long int h[m], t[m] ;

    int i;
    for( i = 0; i < m; i +=1 ){
        // printf("line%d : ",i);
        scanf("%d%d%ld%ld",&u[i],&v[i], &t[i], &h[i]);
    }
	

    // printf("%d \n", i);
    // printf("%ld \n", t[0]-h[0]);

    Graph g(n);
    // making above uhown graph 
	for (int j=0; j<m;j++){
        // printf("%ld", t[j]-h[j]);
	    g.addEdge(u[j]-1, v[j]-1); 
    }
	g.isCyclic();

	// if(g.isCyclic())
	// 	cout << "Graph contains cycle\n"; 
	// else
	// 	cout << "Graph doesn't contain cycle\n"; 
	// return 0; 
    
}
