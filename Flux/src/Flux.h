#pragma once

// -----------------------
// --- Core --------------
// -----------------------

#include "Flux/Core.h"
#include "Flux/Core/Log.h"
#include "Flux/Core/Timestep.h"
#include "Flux/Core/Platform.h"

// -----------------------
// --- Key/Mouse Input ---
// -----------------------

#include "Flux/Core/Input.h"
#include "Flux/Core/KeyCodes.h"
#include "Flux/Core/MouseCodes.h"

// -----------------------
// --- Application -------
// -----------------------

#include "Flux/Core/Application.h"
#include "Flux/Core/Layer.h"

// -----------------------
// --- Events ------------
// -----------------------

#include "Flux/Events/Event.h"
#include "Flux/Events/WindowEvents.h"
#include "Flux/Events/KeyEvents.h"
#include "Flux/Events/MouseEvents.h"

// -----------------------
// --- Renderer ----------
// -----------------------

#include "Flux/Renderer/Renderer.h"
#include "Flux/Renderer/Renderer2D.h"
#include "Flux/Renderer/Renderer3D.h"

#include "Flux/Renderer/VertexArray.h"
#include "Flux/Renderer/Buffers.h"
#include "Flux/Renderer/Shader.h"
#include "Flux/Renderer/Texture.h"
#include "Flux/Renderer/Framebuffer.h"
#include "Flux/Renderer/Mesh.h"

#include "Flux/Renderer/OrthographicCamera.h"
#include "Flux/Renderer/PerspectiveCamera.h"
#include "Flux/Renderer/PerspectiveCameraController.h"

// -----------------------
// --- Scene -------------
// -----------------------

#include "Flux/Scene/Entity.h"
#include "Flux/Scene/Scene.h"
#include "Flux/Scene/Components.h"

// -----------------------
// --- Assets ------------
// -----------------------

#include "Flux/Assets/AssetHandle.h"
#include "Flux/Assets/AssetManager.h"

// -----------------------
// --- GLM ---------------
// -----------------------

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
