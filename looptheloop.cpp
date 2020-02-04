#include<iostream>
#include<math.h>
#include<vector>

using namespace std;

struct AdjacentListNode{
  int dest;
  struct AdjacentListNode* next;
};

struct AdjacentList{
  struct AdjacentListNode *head;  // pointer to head node of list
};

struct Graph{
  int V;
  struct AdjacentList* adjListArray;
};

struct AdjacentListNode* newAdjacentListNode(int dest){
  struct AdjacentListNode * newNode = new AdjacentListNode;
  newNode->dest = dest;
  newNode->next = NULL;
  return newNode;
}

struct Graph* createGraph(int vertices){
  struct Graph* graph = new Graph;
  
  graph->V = vertices;

  graph->adjListArray = new AdjacentList[vertices];

  for (int i = 0; i < vertices; i++){
    graph->adjListArray[i].head = NULL;
  }
  return graph;
}

void addEdge(struct Graph* graph, int src, int dest){
  struct AdjacentListNode* newNode = newAdjacentListNode(dest);
  newNode->next = graph->adjListArray[src].head;
  graph->adjListArray[src].head = newNode;

  // Add an edge from dest to src (undirected graph)
  newNode = newAdjacentListNode(src);
  newNode->next = graph->adjListArray[dest].head;
  graph->adjListArray[dest].head = newNode;
}

void populateGraph(struct Graph* graph, int num_of_edge_pair){
	int edges[num_of_edge_pair][2];
	int src, dest;
	while (num_of_edge_pair--){
    cin>>src>>dest;
		addEdge(graph, src, dest);
	}
}

bool validateSquareVertices(struct Graph* graph){
  for (int v = 0; v < graph->V; v++){
    int degree = 0;
    struct AdjacentListNode* tempNode = graph->adjListArray[v].head;
    
    while (tempNode)        {
      degree++;
      tempNode = tempNode->next;
    }

    if (degree == 1){
        cout<<"\nLoose end"<<endl;
        return false;
    }else if (degree > 2){
        cout<<"\nIntersection"<<endl;
        return false;
    }else if (degree == 0 || degree == 2){
      return true;
    }
    cout<<endl;
  }
  return true;
}

bool detectLoop(struct Graph* graph, int v, bool visited[]){
  visited[v] = true;
  
  struct AdjacentListNode* travel = graph->adjListArray[v].head;
  while (travel){
    if (travel -> dest == v){
      return true;
    }
    
    if (visited[travel -> dest]){
      travel = travel -> next;
    }else{
      visited[travel -> dest] = true;
      travel = graph->adjListArray[travel -> dest].head;
    }
  }
  return false;
}

// loop count should be 1
bool validateLoopCount(struct Graph* graph){
  int loopcount = 0;
  int vertex = graph->V;
  bool visited[vertex];

  for(int i = 0; i < vertex; i++){
    visited[i] = false;
  }

  for(int i = 0; i < vertex; i++){
    if(visited[i] == false){
      if (detectLoop(graph, i, visited)){
        loopcount++;
      }
    }
  }
  if (loopcount == 1){
    return true;
  }else{
    return false;
  }
}

int countSqareEdges(struct Graph* graph, int *square_vertices){
	int count = 0, num_unique_edges;
	for (int i = 0; i < 4; i++)	{
		int node_index = square_vertices[i];
		struct AdjacentListNode* travel = graph->adjListArray[node_index].head;	    
	    
    while (travel){
        for (int j = 0; j < 4; j++){
          if (travel -> dest == square_vertices[j] && j!=i){
            count++;
          }
        }
        travel = travel->next;
    }
	}
	num_unique_edges = count / 2;
    return num_unique_edges;
}

bool validateEdgeCount(vector<vector<int>> mat, int size, struct Graph* graph){
	int jump = size + 1, filled_sq_count = 0;
	int *square_vertices, valid_sq_count = 0;
  square_vertices = new int[4];

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			int edge_count = 0;
			if (mat[i][j] > -1){
				filled_sq_count++;
				square_vertices[0] = jump * i + j;
				square_vertices[1] = square_vertices[0] + 1;
				square_vertices[2] = square_vertices[1] + size;
				square_vertices[3] = square_vertices[2] + 1;

				edge_count = countSqareEdges(graph, square_vertices);

				if (edge_count == mat[i][j])
					valid_sq_count++;
			}
		}
	}
	if (valid_sq_count == filled_sq_count){
		return true;
  }else{
		return false;
  }
}

vector<vector<int>> inputProblem(int size){
  vector<vector<int>> mat;
  int item;
  for(int row = 0; row < size; row++){
    vector<int> newCol;
    for(int col = 0; col < size; col++){
      cin>>item;
      newCol.push_back(item);
    }
    mat.push_back(newCol);
  }
  return mat;
}

void printGraph(struct Graph* graph){
  for (int v = 0; v < graph->V; v++){
    struct AdjacentListNode* travel = graph->adjListArray[v].head;
    cout<<"\nAdjacency list of vertex: "<<v<<" head";
    while (travel){
      cout<<"-> "<<travel->dest;
      travel = travel->next;
    }
    cout<<endl;
  }
}

int main(){
	cout<<"--. Enter -1 value for empty cells."<<endl;
  cout<<"--. The edge number should be equal to total number of edges needed to form a single loop."<<endl;
	cout<<"--. Enter space-separated edge-pairs."<<endl;

  int size;
  cout<<"\nInsert size of matrix:"<<endl;
  cin>>size;
  cout<<endl;
  cout<<"\nInput problem matrix"<<endl;  
  cout<<endl;
  auto problem_matrix = inputProblem(size);

  int vertices = pow((size + 1), 2);  // no of vertices in the graph
  int num_of_edge_pair;
  cout<<"\nInsert total number of edges that is needed to solve the problem:\n"<<endl;
  cin>>num_of_edge_pair;
  cout<<endl;
  struct Graph* graph = createGraph(vertices);
  populateGraph(graph, num_of_edge_pair);

  printGraph(graph);
 	
 	bool vertex = validateSquareVertices(graph);

  bool loop = validateLoopCount(graph);

  bool edge = validateEdgeCount(problem_matrix, size, graph);


 	if (!vertex){
     cout<<"\nInvalid vertex degrees."<<endl;
  }else if(!loop){
    cout<<"\nInvalid loop count."<<endl;
  }else if(!edge){
    cout<<"\nInvalid edge count."<<endl;
  }

	if (vertex && loop && edge){
    cout<<"\nYour solution is correct"<<endl;
  }else{
    cout<<"\nYour solution is incorrect"<<endl;
  }

    return 0;
}