#pragma once
#include <vector>

using uint = unsigned int;

class Mesh {
private:
  unsigned int vertexesSize = 0;
  unsigned int indexesSize = 0;
  uint VBO = 0;
  uint EBO = 0;

public:
  Mesh(std::vector<float> &vertices, std::vector<uint> &indices);

  uint getVBO() const;

  uint getEBO() const;

  unsigned int getVertexSize() const;

  unsigned int getIndexSize() const;

  void genVertexBufferObject(std::vector<float> &vertices);

  void genElementBufferObject(std::vector<uint> &indices);
};
