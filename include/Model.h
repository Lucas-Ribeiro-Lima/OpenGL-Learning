#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Material.h"
#include "Mesh.h"
#include "Program.h"

namespace oriongl::graphics {
class Model {
  protected:
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::vector<std::shared_ptr<Material>> materials;
    std::shared_ptr<Program> program = nullptr;

  public:
    Model(std::shared_ptr<Program> program);

    virtual ~Model() = default;

    virtual void draw();
  
    void loadData(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material = nullptr);

    void deleteData(size_t index);

    void setProgram(std::shared_ptr<Program> prg);

    std::shared_ptr<Program> getModelProgram() const;
};
} // namespace oriongl::graphics
