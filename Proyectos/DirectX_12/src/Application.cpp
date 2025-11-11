#include "Application.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Application::ThrowIfFailed(HRESULT hr, const std::string& msg) {
	if (FAILED(hr)) {
		throw std::runtime_error(msg);
	}
}

void Application::ThrowIfFailed(HRESULT hr) {
	ThrowIfFailed(hr, ":(");
}

std::string Application::readFile(const std::string& filename)
{
	std::ifstream myFile(filename);

	if (!myFile.is_open()) {
		return "";
	}

	std::stringstream buffer;
	buffer << myFile.rdbuf();

	return buffer.str(); 
}

HWND Application::GetWindowNativeHandler() const
{
	return glfwGetWin32Window(window);
}


void Application::setupGeometry()
{
	std::vector<float> geometry{
		// X    Y    Z     W
		-1.0f,  1.0, 0.0f, 1.0f,  //vertice 1
		-1.0f, -1.0, 0.0f, 1.0f,  //vertice 2
		 1.0f, -1.0, 0.0f, 1.0f,  //vertice 3

		1.0f, 0.0f, 0.0f, 1.0f,   //rojo
		0.0f, 1.0f, 0.0f, 1.0f,   //verde
		 0.0f, 0.0f, 1.0f, 1.0f   //azul
	};

	
}

void Application::keyCallback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//teclas para mover	
}

void Application::setupShaders()
{
	//Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;
	//const std::string vertexShaderSource = readFile("Shaders/VertexShader.hlsl");
	//const std::string pixelShaderSource = readFile("Shaders/PixelShader.hlsl");
	//DirectX:D3DCompile(pixelShaderSource.c_str(), pixelShaderSource.length(), nullptr, 
	//nullptr, nullptr, "main", 
	//"ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, 
	//vertexShader, &errorBlob);
}

void Application::setupDevice()
{
	// Crear el Device (Buscando el adaptador de hardware)
	Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
	for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(adapterIndex, &adapter); ++adapterIndex) {
		DXGI_ADAPTER_DESC1 desc;
		adapter->GetDesc1(&desc);
		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;
		if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_2, IID_PPV_ARGS(&g_device)))) {
			break;
		}
	}
	//std::cout << "Failed to create d3d11 device and context." << std::endl;
}
void Application::setupCommandQueue()
{
	// Crear Command Queue
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	ThrowIfFailed(g_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&g_commandQueue)), "Error creating Command Queue");
}

void Application::setupSwapChain()
{
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.BufferCount = BUFFER_COUNT;
	swapChainDesc.Width = WINDOW_WIDTH;
	swapChainDesc.Height = WINDOW_HEIGHT;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;

	Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain;
	ThrowIfFailed(factory->CreateSwapChainForHwnd(
		g_commandQueue.Get(),
		GetWindowNativeHandler(),
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapChain
	));
	ThrowIfFailed(swapChain.As(&g_swapChain), "Error creando Swapchain");
	g_frameIndex = g_swapChain->GetCurrentBackBufferIndex();
}

void Application::setupDescriptorHeap()
{
	//Crear Descriptor Heap para RTVs
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = Application::BUFFER_COUNT;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	ThrowIfFailed(g_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&g_rtvHeap)));

	g_rtvDescriptorSize = g_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
}

void Application::setupRenderTargetView()
{
	//Crear Render Target Views(RTVs)
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = g_rtvHeap->GetCPUDescriptorHandleForHeapStart();
	for (UINT i = 0; i < BUFFER_COUNT; i++) {
		ThrowIfFailed(g_swapChain->GetBuffer(i, IID_PPV_ARGS(&g_renderTargets[i])), "Error al crear Target View");
		g_device->CreateRenderTargetView(g_renderTargets[i].Get(), nullptr, rtvHandle);
		// Correcto: Asegurar que el cálculo sea SIZE_T para punteros
		rtvHandle.ptr += (SIZE_T)g_rtvDescriptorSize;
	}
}

void Application::setupCommandAllocator()
{
	//Crear Command Allocator y Command List
	ThrowIfFailed(g_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_commandAllocator)),
		"Error creando Command Allocator");
}

void Application::setupCommandList()
{
	ThrowIfFailed(g_device->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		g_commandAllocator.Get(),
		nullptr, // No necesitamos PSO para solo limpiar
		IID_PPV_ARGS(&g_commandList)
	), "Error creando Command Queue");
	g_commandList->Close(); // La lista debe estar cerrada para el primer reset.	
}

void Application::clearColorBuffer(const float& r, const float& g, const float& b, const float& a) //Esta no se utiliza en el uevo PJ
{
	// Obtener el handle al RTV actual
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = g_rtvHeap->GetCPUDescriptorHandleForHeapStart();

	// Establecer RTV (Aunque solo limpiemos, es buena práctica)
	rtvHandle.ptr += (SIZE_T)g_frameIndex * g_rtvDescriptorSize;	
	g_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

	// 5. ¡El Clear! (ID3D12GraphicsCommandList::ClearRenderTargetView)
	const float clearColor[] = { r, g, b, a };
	g_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	
}

void Application::setup()
{

	setupGeometry();
	//Inicializa DirectX 12
	// Crear el DXGI Factory		
	ThrowIfFailed(CreateDXGIFactory2(0, IID_PPV_ARGS(&factory)), "Error creating Factory");
	setupDevice();
	setupCommandQueue();
	setupSwapChain();
	setupDescriptorHeap();
	setupRenderTargetView();

	// Configurar el Depth Buffer
	SetUpDepthBuffer();
		
	setupCommandAllocator();
	setupCommandList();
	setupShaders();
	
}

void Application::update()
{
}

void Application::swapBuffers()
{
	// Transición del Back Buffer: Render Target -> Present
	D3D12_RESOURCE_BARRIER transitionToPresent = {};
	transitionToPresent.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	transitionToPresent.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	transitionToPresent.Transition.pResource = g_renderTargets[g_frameIndex].Get();
	transitionToPresent.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	transitionToPresent.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	transitionToPresent.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

	g_commandList->ResourceBarrier(1, &transitionToPresent);
}

void Application::SetUpDepthBuffer()
{
	// Heap de descriptores para DSV
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	ThrowIfFailed(g_device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&g_dsvHeap)),
		"Error creando DSV Descriptor Heap");

	// Recurso de Depth
	D3D12_RESOURCE_DESC dsDesc = {};
	dsDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	dsDesc.Alignment = 0;
	dsDesc.Width = WINDOW_WIDTH;
	dsDesc.Height = WINDOW_HEIGHT;
	dsDesc.DepthOrArraySize = 1;
	dsDesc.MipLevels = 1;
	dsDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // común y compatible
	dsDesc.SampleDesc.Count = 1;
	dsDesc.SampleDesc.Quality = 0;
	dsDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	dsDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	// Valor de limpieza (clear) por defecto
	D3D12_CLEAR_VALUE optClear = {};
	optClear.Format = dsDesc.Format;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;

	// Propiedades del heap del recurso
	D3D12_HEAP_PROPERTIES heapProps = {};
	heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;
	heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heapProps.CreationNodeMask = 1;
	heapProps.VisibleNodeMask = 1;

	// Crear el recurso en estado de escritura de profundidad
	ThrowIfFailed(
		g_device->CreateCommittedResource(
			&heapProps,
			D3D12_HEAP_FLAG_NONE,
			&dsDesc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE, // estado inicial correcto
			&optClear,
			IID_PPV_ARGS(&g_depthStencil)
		),
		"Error creando recurso Depth/Stencil"
	);

	// Crear el DSV
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = dsDesc.Format;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;

	g_device->CreateDepthStencilView(
		g_depthStencil.Get(),
		&dsvDesc,
		g_dsvHeap->GetCPUDescriptorHandleForHeapStart()
	);
}

void Application::draw()
{	
	// Resetear el Command Allocator y la Command List
	ThrowIfFailed(g_commandAllocator->Reset(), "Error borrando el Command Allocator");
	ThrowIfFailed(g_commandList->Reset(g_commandAllocator.Get(), nullptr), "Error borrando el Command List");
	
	// Transición del Back Buffer: Present -> Render Target
	swapBuffers();
	
	//Borrar el buffer
	clearColorBuffer(0.0f, 1.0f, 0.0f, 1.0f);
	
	//render !!
	//Agrega aqui tus comandos
	
	swapBuffers();
	
	// Cerrar y Ejecutar Command List
	ThrowIfFailed(g_commandList->Close(), "Error al cerrar Command List");
	
	ID3D12CommandList* commandLists[] = { g_commandList.Get() };
	g_commandQueue->ExecuteCommandLists(1, commandLists);
	
	// 8. Presentar el frame y actualizar el índice
	ThrowIfFailed(g_swapChain->Present(1, 0), "Error al renderizar el cuadro"); // Sincronizado con VSync (1)
	g_frameIndex = g_swapChain->GetCurrentBackBufferIndex();

	 

}
