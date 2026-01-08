#pragma once

#include "Flux/Core.h"

namespace Flux {

	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Invalidate() = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetColorAttachmentID() const = 0;
		virtual uint32_t GetDepthAttachmentID() const = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};

}
