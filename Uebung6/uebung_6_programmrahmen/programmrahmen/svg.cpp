#include <deque>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include <queue>

struct TreeNode
{
    int id = -1;
    std::unique_ptr<TreeNode> leftChild; // use unique_ptr to automatically destroy the object at end
    std::unique_ptr<TreeNode> rightChild;
    TreeNode* parent = nullptr; // only reference to another unique_ptr, so we don't need a smart pointer here
    // (std::weak_ptr doesn't work with std::unique_ptr)
};

void insertValueToTree(TreeNode* node, int id)
{
    TreeNode* parentNode = nullptr;
    while (node != nullptr)
    {
        parentNode = node;
        if (id <= node->id)
        {
            node = node->leftChild.get();
        }
        else
        {
            node = node->rightChild.get();
        }
    }

    auto newNode = std::make_unique<TreeNode>();
    newNode->id = id;
    newNode->parent = parentNode;
    if (parentNode != nullptr)
    {
        if (id <= parentNode->id)
        {
            parentNode->leftChild = std::move(newNode);
        }
        else
        {
            parentNode->rightChild = std::move(newNode);
        }
    }
}

std::unique_ptr<TreeNode> newTree(const std::vector<int>& ids)
{
    auto rootNode = std::make_unique<TreeNode>();
    rootNode->id = ids[0];
    for (size_t i = 1; i < ids.size(); ++i)
    {
        insertValueToTree(rootNode.get(), ids[i]);
    }

    return rootNode;
}

void depthFirstTraversal(const TreeNode* root)
{
    // TODO 6.3a: Traverse the tree depth-first

    //itertiv ist immer idealer aber hier nicht gefordert daher rekursiv


    if (root->leftChild==nullptr) {
        std::cout << " " << root->id << " \t";
    } else
    {
        depthFirstTraversal(&(*root->leftChild));
        std::cout << " " << root->id << " \t";
    }

    if (root->rightChild!=nullptr) {
        depthFirstTraversal(&(*root->rightChild));
    }
}

void breadthFirstTraversal(const TreeNode* root)
{
    // TODO 6.3b: Traverse the tree breadth-first
    std::queue<TreeNode*> currNodes;
    currNodes.push(const_cast<TreeNode*>(root));

    std::queue<TreeNode*> nextNodes;
    bool isOnlyLeaves = false;

    while (!isOnlyLeaves)
    {
        isOnlyLeaves = true;
        while (!currNodes.empty())
        {
            TreeNode* curr = currNodes.front();

            if (curr->leftChild!= nullptr){
                nextNodes.push(&(*(curr->leftChild)));
                isOnlyLeaves = false;
            }

            if (curr->rightChild!= nullptr){
                nextNodes.push(&(*(curr->rightChild)));
                isOnlyLeaves = false;
            }

            std::cout << " " << curr->id << " \t";

            currNodes.pop();
        }

        std::swap(currNodes,nextNodes);
    }
}

struct Point
{
    int x;
    int y;
};

void writeSVGNode(std::ofstream& stream, int id, const Point& p)
{
    // TODO 6.3c: Draw a circle at (p.x, p.y) and write the ID of the node inside of it

	//set radius of nodes 
	int nodeRad = 10;

    stream << "<circle cx=\"" << p.x << "\" cy=\"" << p.y << "\" fill=\"white\" r=\"" << nodeRad << "\"> </circle>" << std::endl;
    stream << "<text x=\"" << p.x << "\" y=\"" << p.y + nodeRad/2 << "\" text-anchor=\"middle\">" << id <<  "</text>" << std::endl;
}

void writeSVGEdge(std::ofstream& stream, const Point& p1, const Point& p2)
{
    // TODO 6.3c: Draw a line from (p1.x, p1.x) to (p2.x, p2.y)
    stream << "<line x1=\"" << p1.x << "\" y1=\"" << p1.y << "\" x2=\"" << p2.x << "\" y2=\"" << p2.y << "\" stroke-width=\"1\" stroke=\"black\"/>" << std::endl;
}

//recursive depthsearchfunction in order to draw tree
void depthTraversalNot(const TreeNode* root, Point pos, std::ofstream& ofstream, int nodeWidth, int nodeHeight)
{
    
    

    if (root->leftChild!=nullptr) {
        //write edge to next node
        writeSVGEdge(ofstream, Point{pos.x, pos.y,}, Point{pos.x-nodeWidth, pos.y+nodeHeight,});
        //recursion
        depthTraversalNot(&(*root->leftChild), Point{pos.x-nodeWidth, pos.y+nodeHeight,}, ofstream, nodeWidth/2, nodeHeight);
    }

    if (root->rightChild!=nullptr) {
        //write edge to next node
        writeSVGEdge(ofstream, Point{pos.x, pos.y,}, Point{pos.x+nodeWidth, pos.y+nodeHeight,});
        //recursion
        depthTraversalNot(&(*root->rightChild), Point{pos.x+nodeWidth, pos.y+nodeHeight,}, ofstream, nodeWidth/2, nodeHeight);
    }
	//draw point
	writeSVGNode(ofstream, root->id, pos);
}

void writeSVG(const TreeNode* root, const std::string& filename)
{
    // TODO 6.3a: Write a valid svg file with the given filename which shows the given tree

    std::ofstream output = std::ofstream(filename);

    //calculate height of tree with breadthFirstTraversal
    int heightCounter = -1;

    std::queue<TreeNode*> currNodes;
    currNodes.push(const_cast<TreeNode*>(root));

    std::queue<TreeNode*> nextNodes;
    bool isOnlyLeaves = false;

    while (!isOnlyLeaves)
    {
        isOnlyLeaves = true;
        while (!currNodes.empty())
        {
            TreeNode* curr = currNodes.front();

            if (curr->leftChild!= nullptr){
                nextNodes.push(&(*(curr->leftChild)));
                isOnlyLeaves = false;
            }

            if (curr->rightChild!= nullptr){
                nextNodes.push(&(*(curr->rightChild)));
                isOnlyLeaves = false;
            }
            currNodes.pop();
        }
        std::swap(currNodes,nextNodes);
        heightCounter++;
    }

    //calculate the biggest possible size of the deepest layer of the tree => 2^(n-1)
    int crownSize = 1;
    for (heightCounter; heightCounter>0; heightCounter--)
        crownSize*=2;

    //set basic parameters fr building the svg
    int nodeWidth = crownSize*10;
    int nodeHeight = 50;

    int treeWidth =  (crownSize) * nodeWidth;
    int treeHeight = (crownSize) * nodeHeight;


    //write basic stuff into svg
    output << "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 " << treeWidth << " " << treeHeight << "\" version=\"1.1\">" << std::endl;

    //do depthsearch in order to position the nodes correctly


    Point position = Point{
            treeWidth/2, nodeHeight,
    };


    depthTraversalNot(root, position, output, nodeWidth, nodeHeight);

    output << "</svg>" << std::endl;

    output.flush();
    output.close();
}


int main()
{
    const auto root1 = newTree({ 6, 2, 1, 4, 3, 5, 7, 9, 8 });
    const auto root2 = newTree({ 5, 9, 7, 6, 2, 1, 4, 3, 8 });

    std::cout << "TreeNode 1:" << std::endl;
    std::cout << "Breadth-first: ";
    breadthFirstTraversal(root1.get());
    std::cout << std::endl;

    std::cout << "Depth-first:   ";
    depthFirstTraversal(root1.get());
    std::cout << std::endl << std::endl;

    std::cout << "TreeNode 2:" << std::endl;
    std::cout << "Breadth-first: ";
    breadthFirstTraversal(root2.get());
    std::cout << std::endl;

    std::cout << "Depth-first:   ";
    depthFirstTraversal(root2.get());
    std::cout << std::endl;

    writeSVG(root1.get(), "tree1.svg");
    writeSVG(root2.get(), "tree2.svg");

    return 0;
}
