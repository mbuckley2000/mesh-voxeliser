#include "../include/TriangleKDNode.h"

/*
KD tree for storing HBV for meshes
Code based on https://blog.frogslayer.com/kd-trees-for-faster-ray-tracing-with-triangles/
*/

// Construct with an empty vector of triangles for a leaf
TriangleKDNode::TriangleKDNode() : TriangleKDNode(std::vector<Triangle *>()) {}

TriangleKDNode::TriangleKDNode(std::vector<Triangle *> triangles)
{
    this->left        = nullptr;
    this->right       = nullptr;
    this->boundingBox = Box();
    this->triangles   = triangles;
    this->balance();
}

// Comparator for sorting triangles based on their midpoint in the given dimension
struct CompareDimensions
{
    explicit CompareDimensions(int dimension) { this->dimension = dimension; }

    bool operator()(Triangle *i, Triangle *j)
    {
        return (i->getMidpoint()(dimension) < j->getMidpoint()(dimension));
    }

    int dimension;
};

// Returns a slice of a vector
// template <typename T>
std::vector<Triangle *> sliceVec(int startPos, int endPos, std::vector<Triangle *> vector)
{
    std::vector<Triangle *> out;

    for (int i = startPos; i <= endPos; i++)
    {
        out.push_back(vector[i]);
    }

    return out;
}

void TriangleKDNode::balance()
{
    const int maxTrianglesPerLeaf = 10;  // Must be 1 or more
    static_assert(maxTrianglesPerLeaf >= 1, "Failed at KD tree balancing");

    if (triangles.empty())
    {
        return;
    }

    this->expandBoundingBox();

    if (triangles.size() <= maxTrianglesPerLeaf)
    {
        // Finish the tree with empty nodes as leaves
        this->left  = new TriangleKDNode();
        this->right = new TriangleKDNode();
        return;
    }

    // Sort the array just until middle (median) posision is correct.
    // All elements preceding median are less than it, and all following median are greater than it.
    // Much faster than sort() with same eventual outcome (almost 2x speed)
    const int medianArrayPos = this->triangles.size() / 2;
    const int largestDim     = this->boundingBox.largestDim();
    std::nth_element(triangles.begin(), triangles.begin() + medianArrayPos, triangles.end(),
                     CompareDimensions(largestDim));

    // Left tree becomes all photons less than median
    this->left = new TriangleKDNode(sliceVec(0, medianArrayPos, triangles));

    if (medianArrayPos + 1 < triangles.size())
    {
        // Right tree becomes all photons greater than median
        this->right =
            new TriangleKDNode(sliceVec(medianArrayPos + 1, triangles.size() - 1, triangles));
    }

    return;
}

void TriangleKDNode::expandBoundingBox()
{
    if (this->triangles.size() > 0)
    {
        this->boundingBox = triangles[0]->getBoundingBox();

        for (int i = 1; i < triangles.size(); i++)
        {
            this->boundingBox.expand(triangles[i]->getBoundingBox());
        }
    }
}

bool TriangleKDNode::intersects(Box *box)
{
    // Check to see if the ray intersects the bounding box of the given node

    if (this->boundingBox.intersects(box))
    {
        bool triangleHit = false;

        if (this->left || this->right)
        {
            // Intersect with the boxes children until we hit a leaf node
            if (this->left->triangles.size() > 0 || this->right->triangles.size() > 0)
            {
                bool hitLeft  = false;
                bool hitRight = false;

                if (this->left->triangles.size() > 0)
                {
                    hitLeft = this->left->intersects(box);
                }
                if (this->right->triangles.size() > 0)
                {
                    hitRight = this->right->intersects(box);
                }

                return hitLeft || hitRight;
            }
            else
            {
                // We're at a leaf
                // Check the triangles for intersections
                for (int i = 0; i < this->triangles.size(); i++)
                {

                    // Check for hit
                    if (this->triangles[i]->intersects(box))
                    {
                        triangleHit = true;
                    }
                }

                return triangleHit;
            }
        }
    }
    return false;
}
