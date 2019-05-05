#include "../include/TriangleKDNode.h"

/*
KD tree for storing HBV for meshes
*/

// Construct with an empty vector of triangles for a leaf
TriangleKDNode::TriangleKDNode() : TriangleKDNode(std::vector<Triangle *>(), 10) {}

TriangleKDNode::TriangleKDNode(std::vector<Triangle *> triangles, int maxTrianglesPerLeaf)
{
  this->left                = nullptr;
  this->right               = nullptr;
  this->boundingBox         = Box();
  this->triangles           = triangles;
  this->maxTrianglesPerLeaf = maxTrianglesPerLeaf;
  this->balance();
}

// Comparator for sorting triangles based on their midpoint in the given dimension
struct CompareDimensions
{
  explicit CompareDimensions(int dimension) { this->dimension = dimension; }

  bool operator()(Triangle *i, Triangle *j) { return (i->getMidpoint()(dimension) < j->getMidpoint()(dimension)); }

  int dimension;
};

// Returns a slice of a vector
std::vector<Triangle *> sliceVec(int startPos, int endPos, std::vector<Triangle *> vector)
{
  std::vector<Triangle *> out;

  for (int i = startPos; i <= endPos; i++)
  {
    out.push_back(vector[i]);
  }

  return out;
}

void TriangleKDNode::buildChildren()
{
  // Sort the array until middle (median) element and all preceding elements are in the correct place.
  // Values of all elements preceding median are less than it, and all following median are greater than it.
  // Much faster than sort() with same eventual outcome (almost 2x speed)
  const int medianArrayPos = this->triangles.size() / 2;
  const int largestDim     = this->boundingBox.largestDim();  // Longest dimensions of this node's bounding box
  std::nth_element(triangles.begin(), triangles.begin() + medianArrayPos, triangles.end(), CompareDimensions(largestDim));

  // Left child will contain all triangles below the median
  this->left = new TriangleKDNode(sliceVec(0, medianArrayPos, triangles), maxTrianglesPerLeaf);

  if (medianArrayPos + 1 < triangles.size())
  {
    // Left child will contain all triangles above the median
    this->right = new TriangleKDNode(sliceVec(medianArrayPos + 1, triangles.size() - 1, triangles), maxTrianglesPerLeaf);
  }
}

void TriangleKDNode::balance()
{
  if (this->triangles.empty())
  {
    // This is a leaf node
    return;
  }

  // Expand to contain all triangles and child nodes
  this->expandBoundingBox();

  if (this->triangles.size() <= this->maxTrianglesPerLeaf)
  {
    // Finish the tree with empty nodes as leaves
    this->left  = new TriangleKDNode();
    this->right = new TriangleKDNode();
    return;
  }

  this->buildChildren();
}

void TriangleKDNode::expandBoundingBox()
{
  if (!this->triangles.empty())
  {
    this->boundingBox = triangles[0]->getBoundingBox();

    for (int i = 1; i < triangles.size(); i++)
    {
      this->boundingBox.expand(triangles[i]->getBoundingBox());
    }
  }
}

bool TriangleKDNode::intersectTriangles(Box *box)
{
  for (Triangle *triangle : this->triangles)
  {
    // Check for hit
    if (triangle->intersects(box))
    {
      return true;
    }
  }

  return false;
}

bool TriangleKDNode::intersectChildren(Box *box)
{
  bool hitLeft  = false;
  bool hitRight = false;

  if (!this->left->triangles.empty())
  {
    hitLeft = this->left->intersects(box);
  }
  if (!this->right->triangles.empty())
  {
    hitRight = this->right->intersects(box);
  }

  return hitLeft || hitRight;
}

bool TriangleKDNode::intersects(Box *box)
{
  // Check to see if the ray intersects the bounding box of the given node

  if (this->boundingBox.intersects(box))
  {
    if (this->left || this->right)
    {
      if (this->left->triangles.empty() && this->right->triangles.empty())
      {
        // We're at a leaf
        // Check the triangles for intersections
        return this->intersectTriangles(box);
      }

      // Intersect with the boxes children recursively until we hit a leaf node
      return this->intersectChildren(box);
    }
  }
  return false;
}
