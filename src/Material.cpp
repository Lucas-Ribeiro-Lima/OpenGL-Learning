//
// Created by lucas.lima on 12/09/2025.
//

#include <Material.h>
#include <glad.h>
#include "Constants.h"
#include "ResourceManager.h"

Material::Material() : diffuse(getTextureData(Constants::TEXTURE_BLACK_FALLBACK)),
                       specular(getTextureData(Constants::TEXTURE_BLACK_FALLBACK)),
                       emissive(getTextureData(Constants::TEXTURE_BLACK_FALLBACK)) {}

Material::Material(MaterialData &mat) :
    diffuse(getTextureData(mat.diffusePath)),
    specular(getTextureData(mat.specularPath)),
    emissive(getTextureData(mat.emissivePath)) {}

void Material::bindMaterial() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuse->getTex());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specular->getTex());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, emissive->getTex());
}
