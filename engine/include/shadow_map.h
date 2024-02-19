#pragma once

namespace Odyssey{
class ShadowMap{

public:
  ShadowMap(unsigned width, unsigned height);
  ~ShadowMap();
  ShadowMap* read(unsigned texture_unit);
  ShadowMap* write();

private:
  unsigned m_fbo;
  unsigned m_shadow_map;
};
}
