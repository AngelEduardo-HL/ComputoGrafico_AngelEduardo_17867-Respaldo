#pragma once
#include <windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <wrl/client.h> // Microsoft::WRL::ComPtr

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
    // Helpers
    void ThrowIfFailedX(HRESULT hr, const std::string& msg);
    void ThrowIfFailedX(HRESULT hr);

    // Etapas (migradas desde el main que dibuja triángulo)
    void setupGeometryX();          // (no se requiere VB: usamos SV_VertexID)
    void setupShadersX();           // placeholder si luego lo usas
    void setupDeviceX();
    void setupCommandQueueX();
    void setupSwapChainX();
    void setupDescriptorHeapX();
    void setupRenderTargetViewX();
    void setupCommandAllocatorX();
    void setupCommandListX();
    void setViewportScissorX();
    void createRootSignatureAndPSOX();  // RootSig + PSO (compila shader.hlsl)
    void transitionToRTX();              // PRESENT -> RENDER_TARGET
    void transitionToPresentX();         // RENDER_TARGET -> PRESENT

    std::string readFileX(const std::string& filename);

    // --- Configuración y Constantes ---
    static const UINT BUFFER_COUNTX = 2; // Double buffering
    int WINDOW_WIDTHX = 1024;
    int WINDOW_HEIGHTX = 768;

    // --- Variables Globales de DX12 ---
    Microsoft::WRL::ComPtr<IDXGIFactory4>         factory;
    Microsoft::WRL::ComPtr<ID3D12Device>          device;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue>    commandQueue;
    Microsoft::WRL::ComPtr<IDXGISwapChain4>       swapChain;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>  rtvHeap;
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;

    Microsoft::WRL::ComPtr<ID3D12Resource>        g_renderTargetsX[BUFFER_COUNTX];
    UINT                                          g_frameIndexX = 0;
    UINT                                          rtvIncrementSizeX = 0;

    Microsoft::WRL::ComPtr<ID3D12RootSignature>   rootSignatureX;
    Microsoft::WRL::ComPtr<ID3D12PipelineState>   pipelineStateX;

    D3D12_VIEWPORT viewportX{};
    D3D12_RECT     scissorX{};

    // Ventana
    GLFWwindow* windowX = nullptr;   // si usas GLFW
    HWND hwndX = nullptr;            // si usas Win32 puro (de MainApp.cpp)

public:
    const int Width{ 1280 };
    const int Height{ 1024 };

    // Obtención de HWND desde GLFW (si usas GLFW)
    HWND GetWindowNativeHandleX() const;

    // Para Win32: adjuntar el HWND creado en MainApp.cpp
    void AttachHWNDX(HWND hwnd, UINT width, UINT height);

    // Ciclo de vida de la App
    void SetUpX();
    void UpdateX();
    void DrawX();

    // Utilidad: limpiar color manual (opcional)
    void clearColorBufferX(const float& r, const float& g, const float& b, const float& a);
};
