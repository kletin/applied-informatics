
#include <stdio.h>

#define NODES 15
#define EDGES 14

#define MAX_STR_LENGTH 30

// #define PRINT
// #define PRINT1

// use an adjacency matrix to store undirected graph

int GRAPH[NODES][NODES];

// set of all Nodes
int nodes[NODES] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

// size of maximal independent set
int SizeOfMaxIndSet = 0;

// number of maximal independent sets

int NumMaxIndSets = 0;


char names[NODES][MAX_STR_LENGTH] = {
	"Νίκος",
	"Λυδία",
	"Μαρίλια",
	"Πέτρος",
	"Ελένη",
	"Μάνος",
	"Γιάννης",
	"Άκης",
	"Μαρία",
	"Δημήτρης",
	"Άννα",
	"Αλέξανδρος",
	"Άρτεμις",
	"Ζωή",
	"Αλέκος",
};

/*
	add one edge at GRAPH array pos is x,y
	x: 1..NODES
	y: 1..NODES
*/

void addEdge(int x, int y)
{
	GRAPH[x - 1][y - 1] = 1;
	GRAPH[y - 1][x - 1] = 1;
}

void printGraph()
{
	int i, j;
	int c = 0;
	printf("Incidence matrix of Graph:\n");
	for (i = 0; i < NODES; i++) {
		for (j = 0; j < NODES; j++) {
			printf("%2d", GRAPH[i][j]);
			if (GRAPH[i][j] == 1)
				c++;
		}
		printf("\n");
	}
	printf("number of edges=%d\n", c);
}


/*
	SubSet[] : array of combination
	      r  : size of combination

    returns  1:  when any edge exists at GRAPH between a pair of nodes at combination
*/

int CheckAllPairsForDislikes(int SubSet[], int n, int ADJ_MATRIX[][NODES])
{

	// Nested loop for all possible pairs of nodes at combination array SubSet[]
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (i != j) {
				if (ADJ_MATRIX[SubSet[i] - 1][SubSet[j] - 1]) {
#ifdef PRINT
					printf("(%d,%d): Dislike Rejecting Subset\n", SubSet[i], SubSet[j]);
#endif
					return 1;
				}
			}
		}
	}
	return 0;
}


/*
             arr[] : Input Array of all nodes
               n   : Size of nodes
               r   : Size of the combination
             index : Current index in data[]
combinationArray[] : Combination array to store current combination
                 i : index of current element in arr[]


      Uses Pascal's identity

	  nCr = (n-1)Cr + (n-1)C(r-1)

*/

void combination1(int arr[], int n, int r, int index,
                  int combinationArray[], int i)
{
	if (index == r) {
#ifdef PRINT1
		printf("A Candidate Set:\n");
		for (int j = 0; j < r; j++)
			printf("%d ", combinationArray[j]);
		printf("\n");
#endif

		int dislikes = CheckAllPairsForDislikes(combinationArray, r, GRAPH);

		if (dislikes == 0) {
			if (SizeOfMaxIndSet==0) {
				SizeOfMaxIndSet = r;
				printf("Μέγιστος αριθμός καλεσμένων-φίλων στο Πάρτυ : %d\n\n", SizeOfMaxIndSet);
			}

			NumMaxIndSets++;
			printf("Εναλλακτικό Σύνολο καλεσμένων-φίλων #%d :\n",NumMaxIndSets);
			for (int j = 0; j < r; j++) {
				//printf("%d ", combinationArray[j]);
				printf("%s ",names[combinationArray[j]-1]);
			}
			printf("\n\n");
		}
		return;
	}



	// Return when no more elements are there to put in combinationArray[]
	if (i >= n)
		return;

	// current is included, put next at next location
	combinationArray[index] = arr[i];
	combination1(arr, n, r, index + 1, combinationArray, i + 1);
	
	// current is excluded, replace it with next
	combination1(arr, n, r, index, combinationArray, i + 1);
	// (Note that i+1 is passed, but index is not changed)

}

void CalcCombinations(int arr[], int n, int r)
{
	// A temporary array to store all combinations
	int combinationArray[r];

	// Print all combination using array combinationArray[]
	combination1(arr, n, r, 0, combinationArray, 0);
}

int FindMaximalIndependentSets()
{
	int r;
	for (r = NODES; r > 0; r--) {
		CalcCombinations(nodes, NODES, r);
		if (SizeOfMaxIndSet != 0) {
			// solution found so break brute force
			return SizeOfMaxIndSet;
		}
	}
	return SizeOfMaxIndSet;
}

int main()
{
	int MaxNumber;

	// add 14 vertices from Social Graph 2
	addEdge(1, 2);
	addEdge(1, 8);
	addEdge(3, 6);
	addEdge(4, 5);
	addEdge(5, 6);
	addEdge(5, 9);
	addEdge(5, 10);
	addEdge(6, 8);
	addEdge(7, 8);
	addEdge(9, 12);
	addEdge(10, 15);
	addEdge(11, 12);
	addEdge(11, 15);
	addEdge(13, 14);

#ifdef PRINT
	printGraph();
#endif

	MaxNumber = FindMaximalIndependentSets();

	return MaxNumber;
}