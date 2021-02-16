#include "Graphic/Renderer.h"
#include "Graphic/SDL/RendererWrapper.h"

namespace MV {
	std::unique_ptr<Renderer> Renderer::s_RendererImpl = std::make_unique<RendererWrapper>();
}
