#include <lava/createinfos/Buffers.hh>
#include <lava/createinfos/Images.hh>
#include <lava/createinfos/PipelineLayoutCreateInfo.hh>
#include <lava/features/GlfwOutput.hh>
#include <lava/features/GlfwWindow.hh>
#include <lava/features/Validation.hh>
#include <lava/gpuselection/NthOfTypeStrategy.hh>
#include <lava/objects/Buffer.hh>
#include <lava/objects/Device.hh>
#include <lava/objects/GraphicsPipeline.hh>
#include <lava/objects/Image.hh>
#include <lava/objects/ImageView.hh>
#include <lava/objects/Instance.hh>
#include <lava/objects/PipelineLayout.hh>
#include <lava/objects/RenderPass.hh>
#include <lava/objects/ShaderModule.hh>
#include <lava/raii/ActiveRenderPass.hh>
#include <lava-extras/pack/pack.hh>

#include <lava/createinfos/GraphicsPipelineCreateInfo.hh>
#include <lava/createinfos/RenderPassCreateInfo.hh>

#include <lava-extras/camera/GenericCamera.hh>

#include <iostream>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include <thread>

/**
 * The struct holding the information about each vertex send to the GPU.
 * Extend this, if you need more information in your shaders.
 * */
struct Vertex {
	glm::vec3 position;
	glm::u8vec4 color;
};

/**
 * The struct holding the information needed in shaders to transform vertex data.
 * */
struct CameraData {
	glm::mat4 view;
	glm::mat4 proj;
};

/**
 * The path where all our shaders are located.
 * */
const std::string shaderFolder = "../HelloCube/shaders/";

const std::vector<Vertex> cubeVertices = {
	{{-1.f, -1.f, -1.f}, {0, 0, 0, 255}},
	{{-1.f, -1.f, 1.f}, {0, 0, 255, 255}},
	{{-1.f, 1.f, -1.f}, {0, 255, 0, 255}},
	{{-1.f, 1.f, 1.f}, {0, 255, 255, 255}},
	{{1.f, -1.f, -1.f}, {255, 0, 0, 255}},
	{{1.f, -1.f, 1.f}, {255, 0, 255, 255}},
	{{1.f, 1.f, -1.f}, {255, 255, 0, 255}},
	{{1.f, 1.f, 1.f}, {255, 255, 255, 255}},
};

const std::vector<uint32_t> cubeIndices{ 0, 2, 3, //
										0, 3, 1, //
										0, 1, 5, //
										0, 5, 4, //
										2, 7, 3, //
										2, 6, 7, //
										1, 7, 5, //
										1, 3, 7, //
										0, 4, 6, //
										0, 6, 2, //
										4, 5, 7, //
										4, 7, 6 };

int main() {
	// Create a Vulkan instance, tell it we need glfw and the validation as
	// extension features
	auto glfw = lava::features::GlfwOutput::create();
	auto instance =
		lava::Instance::create({ lava::features::Validation::create(), glfw });

	// Create a logical device with a single graphics queue named "graphics" on
	// a discrete (non-integrated) GPU. For more complex apps you can request
	// additional queues (e.g. a separate transfer queue)
	auto device = instance->createDevice(
		{ lava::QueueRequest::graphics("graphics") },
		lava::NthOfTypeStrategy(vk::PhysicalDeviceType::eDiscreteGpu));

	// Create a pipeline layout that transfers the CameraData as push constants
	// and has no descriptors (textures or uniform buffers)
	auto plLayout = device->createPipelineLayout<CameraData>();

	// Create a forward pass that writes a color and a depth target and clears
	// both at the beginning of the pass
	auto pass = device->createRenderPass(
		lava::RenderPassCreateInfo::simpleForward(glfw->format()));

	auto pipeline = [&]() {
		auto ci = lava::GraphicsPipelineCreateInfo::defaults();
		ci.setLayout(plLayout);

		ci.depthStencilState.depthTestEnable = true;
		ci.depthStencilState.depthWriteEnable = true;

		// Due to the flipped y axis in NDC, the triangle winding order is
		// inverted, too
		ci.rasterizationState.frontFace = vk::FrontFace::eClockwise;

		ci.addStage(
			lava::pack::shader(device, "cube_vert.spv"));
		ci.addStage(
			lava::pack::shader(device, "cube_frag.spv"));
		ci.vertexInputState.binding(0, &Vertex::position, &Vertex::color);

		return pass->createPipeline(0, ci);
	}();

	lava::camera::GenericCamera camera;
	camera.setPosition({ 0.f, 0.f, 1.f });
	camera.setTarget({ 0.f, 0.f, 0.f });

	// Unlike OpenGL, in Vulkan there is no FBO 0. We need to create a
	// framebuffer for each image on the swapchain of the image ourselves.
	// We pass a lambda here, so when the swapchain becomes outdated, the FBOs
	// are recreated automatically.
	std::vector<lava::SharedFramebuffer> fbos;
	auto window = glfw->openWindow();
	window->buildSwapchainWith(
		[&](std::vector<lava::SharedImageView> const& views) {
			auto depth_image =
				lava::attachment2D(window->width(), window->height(),
					lava::Format::DEPTH_COMPONENT32F)
				.create(device);
			depth_image->realizeAttachment();
			auto depth_view = depth_image->createView();

			fbos.clear();
			for (auto& view : views)
				fbos.push_back(pass->createFramebuffer({ depth_view, view }));

			camera.setAspectRatio(float(window->width()) /
				float(window->height()));
		});

	// Upload of the cube mesh
	auto vab = device->createBuffer(lava::arrayBuffer());
	vab->setDataVRAM(cubeVertices);
	auto eab = device->createBuffer(lava::indexBuffer());
	eab->setDataVRAM(cubeIndices);

	camera.setPosition({ 2.f, 2.f, 2.f });
	camera.setTarget({ 0.f, 0.f, 0.f });

	while (true) {
		// Prevent the CPU from getting too far ahead. Here we wait until only
		// one unfinished CommandBuffer is left, so we can overlap GPU and CPU
		// work, without introducing too much delay.
		device->graphicsQueue().catchUp(1);

		camera.rotateAroundTarget_GlobalAxes(0.f, 0.001f, 0.f);

		// Acquires an image from the swap chain to begin rendering.
		// When frame goes out of scope, the image is presented on the window.
		auto frame = window->startFrame();

		auto cmd = device->graphicsQueue().beginCommandBuffer();

		// Vulkan doesn't take care of synchronization for us.
		// We need to tell it to wait with rendering until the image is ready
		// and to wait with presenting the image until the rendering is done.
		// The frame struct provides the necessary semaphores.
		cmd.wait(frame.imageReady());
		cmd.signal(frame.renderingComplete());

		auto forward = cmd.beginRenderpass(fbos[frame.imageIndex()]);

		{
			auto sub = forward.startInlineSubpass();
			sub.bindPipeline(pipeline);
			sub.setViewports(
				{ {0, 0, float(window->width()), float(window->height())} });

			sub.bindVertexBuffers({ vab });
			sub.bindIndexBuffer({ eab });
			sub.pushConstantBlock(CameraData{ camera.getViewMatrix(),
											 camera.getProjectionMatrix() });
			sub.drawIndexed(uint32_t(cubeIndices.size()));
		}

		// std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}