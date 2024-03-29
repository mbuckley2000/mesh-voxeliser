#include "../include/Mesh.h"
#include <igl/readOBJ.h>
#include "../include/Box.h"

using namespace Eigen;

void Mesh::loadFromFile(std::string filename)
{
  Eigen::Matrix2Xf texCoords;
  Eigen::MatrixXi faceTex;  //   FTC  #F list of face indices into vertex texture coordinates

  // Read file into our arrays
  if (!igl::readOBJ(filename, this->vertices, texCoords, this->vertexNormals, this->faces, faceTex, this->faceVns))
  {
    // Failed to read object
    exit(2);
  }
}

void Mesh::setSize(float size)
{
  // Get bb
  this->calculateTriangles();
  this->calculateBoundingBox();

  // Scale
  const int largestDim    = this->boundingBox.largestDim();
  const float scaleFactor = size / this->boundingBox.getSize()(largestDim);

  this->vertices = this->vertices * scaleFactor;
}

void Mesh::moveTo(Vec3 position)
{
  this->calculateTriangles();
  this->calculateBoundingBox();
  this->translation = -this->boundingBox.minimum + position;
}

bool Mesh::intersects(Box *box)
{
  return this->kdTree->intersects(box);
}

void Mesh::deleteTriangles()
{
  for (auto const &triangle : this->triangles)
  {
    delete triangle;
  }

  this->triangles.clear();
}

void Mesh::calculateTriangles()
{
  this->deleteTriangles();

  // Turn loaded matrices into a vector of triangle objects
  for (int f = 0; f < this->faces.rows(); f++)
  {
    const Vector3i face = this->faces.row(f);
    // const Vector3i faceVns = this->faceVns.row(f);

    Matrix3f vs;
    // Matrix3f vns;

    for (int v = 0; v < 3; v++)
    {
      vs.col(v) = (this->vertices.row(face(v)).transpose() + this->translation);
      // vns.col(v) = (this->vertexNormals.row(faceVns(v)).transpose());
    }

    auto *t = new Triangle(vs);

    this->triangles.push_back(t);
  }

  this->trianglesCalculated = true;
}

Mesh::Mesh(std::string filename)
{
  loadFromFile(filename);
  trianglesCalculated   = false;
  boundingBoxCalculated = false;
  this->setSize(1);
  this->moveTo(Vec3(0, 0, 0));
  this->calculateTriangles();
  this->calculateBoundingBox();
  this->buildKDTree();
}

Mesh::~Mesh()
{
  this->deleteTriangles();
}

void Mesh::calculateBoundingBox()
{
  this->boundingBox = Box();

  for (auto const &triangle : this->triangles)
  {
    for (int v = 0; v < 3; v++)
    {
      const Vec3 vertex = triangle->getVertex(v);

      this->boundingBox.expand(vertex);
    }
  }
  this->boundingBoxCalculated = true;
}

void Mesh::buildKDTree()
{
  this->kdTree = new TriangleKDNode(this->triangles, 10);
}