#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// struct for nodes of the binary search tree
typedef struct BinarySearchTree{
	char keyword[100];
	long int frequency;
	struct BinarySearchTree *left;
    struct BinarySearchTree *right;
}BST;
// struct for to form binary tree from binary search tree
typedef struct values{
	int frequency;
	char keyword[100];
}variables;

// Function to create new nodes for binary tree
BST* createNode(char key[100],long int freq)
{
    BST* newNode = (BST*)malloc(sizeof(BST));
    strcpy(newNode->keyword,key);
    newNode->frequency = freq;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
// Inserting nodes to binary search tree
BST* Insert(BST* node, char key[100],long int freq)
{
    if (node==NULL)
    {
        node = createNode(key,freq);
    }
    else
    {
        if (stricmp(key,node->keyword) < 0)
        {
            node->left = Insert(node->left,key,freq);
        }
        else
        {
            node->right = Insert(node->right,key,freq);
        }
    }
    return node;
}
// Function to create new nodes for binary search tree
BST* newNode(variables structarray) { 
    BST* node = (BST*)malloc(sizeof(BST)); 
    node->frequency = structarray.frequency;
	strcpy(node->keyword,structarray.keyword);
    node->left = node->right = NULL; 
    return (node); 
}
// Inserting nodes in a binary tree in descending order according to frequency. Higher frequency of nodes closer to root.
BST* InsertDescendingOrder(variables arrayofstructs[],BST* node,int i,int v){  
    if (i < v){ 
        BST* temp = newNode(arrayofstructs[i]); 
        node = temp; 
        node->left = InsertDescendingOrder(arrayofstructs,node->left,2 * i + 1, v); 
        node->right = InsertDescendingOrder(arrayofstructs,node->right, 2 * i + 2, v); 
    } 
    return node; 
} 
// Printing nodes in a LNR order into console.
void LNR(BST* root){
	if(root == NULL){
		return;
	}
	LNR(root->left);
	printf("%s ",root->keyword);
	LNR(root->right);
}
// Calculating acces time.
int TotalAccessTime(BST* root,int val){
	if(root == NULL){
		return 0;
	}
	return (val*root->frequency + TotalAccessTime(root->right,val+1) + TotalAccessTime(root->left,val+1));
}
int main(){
	int i = 0;
	BST* root = NULL;
	FILE* file = fopen("input.txt", "r");
	char line[100];
	char *token;
	// Reading datas from input.txt
	while (fgets(line, sizeof(line), file)) {
		if(isspace(line[0]) != 0){
			break;
		}
		token = strtok(line,",");
		token = strtok(NULL,",");
		char key[100];
		strcpy(key,token);
		token = strtok(NULL,"");
		char tempfreq[10];
		strcpy(tempfreq,token);
   		char *cp;
   		long int freq;
   		freq = strtol(tempfreq, &cp, 10);
   		/*printf("%ld",freq);
   		printf("%s",key);
   		printf("\n");*/
   		i++;
   		// Forming BST
   		root = Insert(root,key,freq);
	}
	printf("%s","LNR of BST: ");
	//Printing bst into console
	LNR(root);
	//Calculating total access time for bst
	int total_access_time = TotalAccessTime(root,1);
	printf("\n");
	printf("%s","Total Access Time:");
	printf("%d",total_access_time);
	printf("\n");
	printf("\n");
	variables structarray[i];
	int j = 0;
	FILE* file2 = fopen("input.txt", "r");
	// Reading datas again.
	while (fgets(line, sizeof(line), file2)) {
		token = strtok(line,",");
		token = strtok(NULL,",");
		char key[100];
		strcpy(key,token);
		token = strtok(NULL,"");
		char tempfreq[10];
		strcpy(tempfreq,token);
   		char *cp;
   		long int freq;
   		freq = strtol(tempfreq, &cp, 10);
   		structarray[j].frequency = freq;
   		strcpy(structarray[j].keyword,key);
   		j++;
	}
	int m;
	int n;
	int a;
	char b[100];
	// Arranging array in a descending order.
	for (m = 0; m < i; m++){
        for (n = m + 1; n < i;n++){
            if (structarray[m].frequency < structarray[n].frequency){
                a = structarray[m].frequency;
                structarray[m].frequency = structarray[n].frequency;
                structarray[n].frequency = a;
                strcpy(b,structarray[m].keyword);
            	strcpy(structarray[m].keyword,structarray[n].keyword);
            	strcpy(structarray[n].keyword,b);
            }
        }
	}
    BST* root2 = NULL;
    int v = i;
    // Forming BT
    root2 = InsertDescendingOrder(structarray,root2,0,v);
    printf("LNR of BT: ");
    // Printing BT into console
	LNR(root2);
	// Calculating minimized access time.
	int minimizedtotal = TotalAccessTime(root2,1);
	printf("\nMinimized Total Access Time:");
	printf("%d",minimizedtotal);
	return 0;
}
