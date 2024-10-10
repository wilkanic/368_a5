#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

struct tnode {
int x;
int y;
int height; 
struct tnode* left;
struct tnode* right;
};

int height(struct tnode* node)
{
if(node == NULL) return -1;
return node->height;
}

struct tnode* balance(struct tnode* node);
int collision_detect(int xPoint, int yPoint, int xTest, int yTest, int area);


struct BinaryTree{
    struct tnode* head;
};

struct tnode* add(struct tnode* node, int xVal, int yVal) {
    if(node == NULL) {
        node = (struct tnode*)malloc(sizeof(struct tnode));
        if (!node) {
          return NULL;
        }   
        node->x = xVal;
        node->y = yVal;
        node->left = NULL;
        node->right = NULL;
    }
    else if(node->x > xVal){
        node->left = add(node->left, xVal, yVal);
    }
    else if(node->x < xVal){
        node->right = add(node->right, xVal, yVal);
    }
    else if((node->x == xVal) && (node->y > yVal)){
        node->left = add(node->left, xVal, yVal);
    }
    else if((node->x == xVal) && (node->y < yVal)){
        node->right = add(node->right, xVal, yVal);
    }
    else{
        return node; //no duplicates
    }

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));;
    node = balance(node);
    return node;
}

void delete(struct tnode* node) {
if (node == NULL) {
        return;
    }

    // Free left and right subtrees
    delete(node->left);
    delete(node->right);

    // Free current node
    free(node);
}

void Preorder(struct tnode* node, int* total, int xPoint, int yPoint, int area)
    {
        if (node == NULL){
            return;
        } else {
            // Visit node
            if (collision_detect(xPoint, yPoint, node->x, node->y, area)==1){
                *total += 1;
            }
            if(node->left != NULL){
                Preorder(node->left, total, xPoint, yPoint, area);
            }
            if(node->right != NULL){
                Preorder(node->right, total, xPoint, yPoint, area);
            }
        }
    }

struct tnode* rotate_r(struct tnode* current)
{
struct tnode* new = current->left;
current->left = new->right;
new->right = current;
current->height = 1 + (height(current->left) > height(current->right) ? height(current->left) : height(current->right));
new->height = 1 + (height(new->left) > height(new->right) ? height(new->left) : height(new->right));
return new;
}

struct tnode* rotate_l(struct tnode* current)
{
struct tnode* new = current->right;
current->right = new->left;
new->left = current;
current->height = 1 + (height(current->left) > height(current->right) ? height(current->left) : height(current->right));
new->height = 1 + (height(new->left) > height(new->right) ? height(new->left) : height(new->right));
return new;
}

struct tnode* rotate_r_l(struct tnode* current) {
current->right = rotate_r(current->right);
return rotate_l(current);
}

struct tnode* rotate_l_r(struct tnode* current) {
current->left = rotate_l(current->left);
return rotate_r(current);
}

struct tnode* balance(struct tnode* node) {
    if (node == NULL) return node;
    if (height(node->left) - height(node->right) > 1) {
        if (height(node->left->left) >= height(node->left->right))
            node = rotate_r(node);
        else
            node = rotate_l_r(node);
    } else if (height(node->left) - height(node->right) < -1) {
        if (height(node->right->right) >= height(node->right->left))
            node = rotate_l(node);
        else
            node = rotate_r_l(node);
    }
    return node;
}

void readFile (struct BinaryTree* tree, char* pointFile){
    FILE *fptr;

    int xcoord;
    int ycoord;

    fptr = fopen(pointFile, "r");
    if (fptr == NULL){
        printf("error\n");
        return;
    }

    while(fscanf(fptr, "%d %d", &xcoord, &ycoord) == 2){
        tree->head = add(tree->head, xcoord, ycoord);
    }

    fclose(fptr);
}

int main (){
    int total = 0;
    int inx;
    int iny;
    int area;

    struct BinaryTree tree;
    tree.head = NULL;
    readFile(&tree,"points.txt");

     while(scanf("%d %d %d",&inx, &iny, &area)==3){
            Preorder(tree.head, &total, inx, iny, area);
            printf("%d\n",total);
            total = 0;
      }
    delete(tree.head);
    return 0;
}

int collision_detect(int xPoint,int yPoint,int xTest,int yTest,int area){
    int distance;
    int x = xTest - xPoint;
    int y = yTest - yPoint;
    x = x*x;
    y = y*y;
    distance = x+y;
    if (distance <= (area * area)){
        return 1;
    } else {
        return 0;
    }
}