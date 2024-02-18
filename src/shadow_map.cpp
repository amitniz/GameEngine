#include "include/shadow_map.h"
#include "include/renderer.h"


ShadowMap::ShadowMap(unsigned width, unsigned height){
  Renderer::createShadowMap(width,height,&m_fbo,&m_shadow_map);
}

ShadowMap::~ShadowMap(){
  Renderer::deleteShadowMap(m_fbo,m_shadow_map);
}

ShadowMap* ShadowMap::read(unsigned texture_unit){
  Renderer::readShadowMap(texture_unit, m_shadow_map);
  return this;
}
ShadowMap* ShadowMap::write(){
  Renderer::writeShadowMap(m_fbo);
  return this;
}
