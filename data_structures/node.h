
// Node object
// string name, integer value, and pointer to the next node (from the same type)
typedef struct Node {
	char *name;
	unsigned int value;
	struct Node *next;
} Node;

void print_node(Node node); // Prints Node attributes - Gets Node node
