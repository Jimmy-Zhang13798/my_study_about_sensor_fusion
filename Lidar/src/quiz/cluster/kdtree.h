/* \author Aaron Brown */
// Quiz on implementing kd tree

#include "../../render/render.h"

enum SPLIT_AXIS{x_axis=0,y_axis=1};

// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;


	SPLIT_AXIS split_axis ;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL),split_axis{x_axis}
	{}

	~Node()
	{
		delete left;
		delete right;
	}
};


// Actually, this Kdtree is not a very good one. it just adds new point to new position of node. 
// The good solution would be that everytime you add a new point, that means you update one point to the whole pointcloud.
// so we  have the whole pointcloud now, then we compute the variance of data on each axis, we handle the axis that has the largest variance， first.

struct KdTree
{
    Node* root;


	KdTree(): root(NULL) {}

	~KdTree() { delete root; }

	void insertHelper (Node** node, uint depth, std::vector<float> point, int id)
	{
		// Tree is empty
		if(*node==NULL)
		{
			*node= new Node(point,id);
			uint cd = depth%2;
			if (cd == 0) 
			{
				(*node)->split_axis = x_axis;
				std::cout << "node"<<id<<" split in x_axis" << std::endl;
			}
			else
			{
				(*node)->split_axis = y_axis;
				std::cout << "node"<<id<<" split in y_axis" << std::endl;
			}

		}

		else
		{
			// calculate current dim
			uint cd = depth%2;

			if(point[cd] < ((*node)->point[cd]))
				insertHelper(&((*node)->left),depth+1,point,id);
			else
				insertHelper(&((*node)->right),depth+1,point,id);



		}
	}

	void insert(std::vector<float> point, int id)
	{
		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 
		insertHelper(&root,0,point,id);

	}

	void searchHelper(std::vector<float> target, Node* node, int depth, float distanceTol, std::vector<int>& ids)
	{

		if(node != NULL)
		{


			// basically, this "if' built a square(box), we check if the current node is inside the square
			// if it's inside the square,then furthernore, we calculate the actual distance
			// that helps us avoid calculating the actual distance every time.
			if  ( (node->point[0] >= (target[0]-distanceTol) && node->point[0] <= (target[0]+distanceTol)) && 
				  (node->point[1] >= (target[1]-distanceTol) && node->point[1] <= (target[1]+distanceTol)))
			{

				float distance = sqrt( (node->point[0]-target[0])*(node->point[0]-target[0]) + (node->point[1]-target[1])*(node->point[1]-target[1]) );
				if (distance <= distanceTol)
				ids.push_back(node->id);
			}

			//check accross boundary
			if( (target[depth%2]-distanceTol) < (node->point[depth%2]) )
				searchHelper(target, node->left,  depth+1, distanceTol, ids);
			if( (target[depth%2]+distanceTol) > (node->point[depth%2]) )
				searchHelper(target, node->right, depth+1, distanceTol, ids);

		}

	} 

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{

		std::vector<int> ids;
		searchHelper(target, root, 0, distanceTol,ids);

		return ids;
	}
};