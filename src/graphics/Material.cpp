//
// Created by lucas.lima on 12/09/2025.
//

#include <Material.h>
#include <cassert>
#include <glad.h>

namespace oriongl::graphics {

constexpr const size_t MAX_TEXTURES_SUPPORT = 8;

Material::Material() {};

void Material::loadTexture(std::shared_ptr<oriongl::graphics::Texture> texture) {
    assert(textures.size() < MAX_TEXTURES_SUPPORT && "Exceeded maximum number of textures per material");
    textures.push_back(std::move(texture));
}

void Material::bindMaterial(std::shared_ptr<Program> prg) {
    size_t number = 0;
    for (auto &texture : textures) {
        glActiveTexture(GL_TEXTURE0 + number++);
        glBindTexture(GL_TEXTURE_2D, texture->getTex());
    }

    prg->setUniform3fv("material_color", glm::vec3(_color[0], _color[1], _color[2]));
}

void Material::setColor(MaterialColor color) { _color = color; }
} // namespace oriongl::graphics
