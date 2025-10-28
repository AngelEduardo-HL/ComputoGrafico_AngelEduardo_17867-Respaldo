#pragma once
#include <windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <wrl/client.h> // Para Microsoft::WRL::ComPtr

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>

class ApplicationDirect12X
{
private:
	void ThrowIfFailedX(HRESULT hr, const std::string& msg);
	void ThrowIfFailedX(HRESULT hr);
	void setupGeometryX();
	void setupShadersX();
	void setupDeviceX();
	void setupCommandQueueX();
	void setupSwapChainX();
	void setupDescriptorHeapX();
	void setupRenderTargetViewX();
	void setupCommandAllocatorX();
	void setupCommandListX();
	void swapBuffersX();

	std::string readFileX(const std::string& filename);

	// --- Configuración y Constantes ---
	static const UINT BUFFER_COUNTX = 2; // Double buffering
	const int WINDOW_WIDTHX = 1024;
	const int WINDOW_HEIGHTX = 768;

	// --- Variables Globales de DX12 ---
	Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;

	Microsoft::WRL::ComPtr<ID3D12Resource> g_renderTargetsX[BUFFER_COUNTX];
	UINT g_frameIndexX;
public:
	const int Width{ 1280 };
	const int Height{ 1024 };
	GLFWwindow* windowX;
	HWND GetWindowNativeHandleX() const;
	void SetUpX();
	void UpdateX();
	void DrawX();
	void SetUpSignatureX();
	void clearColorBufferX(const float& r, const float& g, const float& b, const float& a);
};