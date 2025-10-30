#include "AppDirect12X.h"
#include <fstream>
#include <sstream>

using Microsoft::WRL::ComPtr;

void ApplicationDirect12X::ThrowIfFailedX(HRESULT hr, const std::string& msg) {
    if (FAILED(hr)) throw std::runtime_error(msg);
}
void ApplicationDirect12X::ThrowIfFailedX(HRESULT hr) {
    ThrowIfFailedX(hr, "D3D12 error");
}
std::string ApplicationDirect12X::readFileX(const std::string& filename)
{
    std::ifstream myFile(filename);
    if (!myFile.is_open()) return "";
    std::stringstream buffer;
    buffer << myFile.rdbuf();
    return buffer.str();
}

HWND ApplicationDirect12X::GetWindowNativeHandleX() const
{
    if (windowX) return glfwGetWin32Window(windowX);
    return hwndX; // Win32
}

void ApplicationDirect12X::AttachHWNDX(HWND hwnd, UINT width, UINT height)
{
    hwndX = hwnd;
    WINDOW_WIDTHX = static_cast<int>(width);
    WINDOW_HEIGHTX = static_cast<int>(height);
}

void ApplicationDirect12X::setupGeometryX()
{

}
void ApplicationDirect12X::setupShadersX()
{

}

void ApplicationDirect12X::setupDeviceX()
{
    ComPtr<IDXGIAdapter1> adapter;
    for (UINT i = 0; factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i) {
        DXGI_ADAPTER_DESC1 d{};
        adapter->GetDesc1(&d);
        if (d.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;
        if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_2, IID_PPV_ARGS(&device)))) {
            return;
        }
    }
    ComPtr<IDXGIAdapter> warp;
    ThrowIfFailedX(factory->EnumWarpAdapter(IID_PPV_ARGS(&warp)), "WARP adapter");
    ThrowIfFailedX(D3D12CreateDevice(warp.Get(), D3D_FEATURE_LEVEL_12_2, IID_PPV_ARGS(&device)), "WARP device");
}

void ApplicationDirect12X::setupCommandQueueX()
{
    D3D12_COMMAND_QUEUE_DESC q{};
    q.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    q.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    ThrowIfFailedX(device->CreateCommandQueue(&q, IID_PPV_ARGS(&commandQueue)), "Create Queue");
}

void ApplicationDirect12X::setupSwapChainX()
{
    DXGI_SWAP_CHAIN_DESC1 sc{};
    sc.BufferCount = BUFFER_COUNTX;
    sc.Width = WINDOW_WIDTHX;
    sc.Height = WINDOW_HEIGHTX;
    sc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    sc.SampleDesc.Count = 1;

    ComPtr<IDXGISwapChain1> temp;
    ThrowIfFailedX(factory->CreateSwapChainForHwnd(commandQueue.Get(), GetWindowNativeHandleX(), &sc, nullptr, nullptr, &temp), "Swapchain");
    ThrowIfFailedX(temp.As(&swapChain), "Swapchain QI");
    g_frameIndexX = swapChain->GetCurrentBackBufferIndex();
}

void ApplicationDirect12X::setupDescriptorHeapX()
{
    D3D12_DESCRIPTOR_HEAP_DESC hd{};
    hd.NumDescriptors = BUFFER_COUNTX;
    hd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    hd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    ThrowIfFailedX(device->CreateDescriptorHeap(&hd, IID_PPV_ARGS(&rtvHeap)), "RTV Heap");
    rtvIncrementSizeX = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
}

void ApplicationDirect12X::setupRenderTargetViewX()
{
    D3D12_CPU_DESCRIPTOR_HANDLE h = rtvHeap->GetCPUDescriptorHandleForHeapStart();
    for (UINT i = 0; i < BUFFER_COUNTX; ++i) {
        ThrowIfFailedX(swapChain->GetBuffer(i, IID_PPV_ARGS(&g_renderTargetsX[i])), "GetBuffer");
        device->CreateRenderTargetView(g_renderTargetsX[i].Get(), nullptr, h);
        h.ptr += static_cast<SIZE_T>(rtvIncrementSizeX);
    }
}

void ApplicationDirect12X::setupCommandAllocatorX()
{
    ThrowIfFailedX(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)), "Allocator");
}

void ApplicationDirect12X::setupCommandListX()
{
    ThrowIfFailedX(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList)), "CmdList");
    ThrowIfFailedX(commandList->Close(), "Close initial cmdlist");
}

void ApplicationDirect12X::setViewportScissorX()
{
    viewportX.TopLeftX = 0.0f;
    viewportX.TopLeftY = 0.0f;
    viewportX.Width = static_cast<float>(WINDOW_WIDTHX);
    viewportX.Height = static_cast<float>(WINDOW_HEIGHTX);
    viewportX.MinDepth = 0.0f;
    viewportX.MaxDepth = 1.0f;

    scissorX.left = 0; scissorX.top = 0;
    scissorX.right = WINDOW_WIDTHX;
    scissorX.bottom = WINDOW_HEIGHTX;
}

void ApplicationDirect12X::createRootSignatureAndPSOX()
{
    D3D12_ROOT_SIGNATURE_DESC rs{};
    rs.NumParameters = 0;
    rs.pParameters = nullptr;
    rs.NumStaticSamplers = 0;
    rs.pStaticSamplers = nullptr;
    rs.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

    ComPtr<ID3DBlob> blob, err;
    ThrowIfFailedX(D3D12SerializeRootSignature(&rs, D3D_ROOT_SIGNATURE_VERSION_1, &blob, &err), "Serialize RS");
    ThrowIfFailedX(device->CreateRootSignature(0, blob->GetBufferPointer(), blob->GetBufferSize(), IID_PPV_ARGS(&rootSignatureX)), "Create RS");

    // Compilar shaders
    ComPtr<ID3DBlob> vs, ps;
    ThrowIfFailedX(D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", 0, 0, &vs, &err), "Compile VS");
    ThrowIfFailedX(D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", 0, 0, &ps, &err), "Compile PS");

    D3D12_GRAPHICS_PIPELINE_STATE_DESC pso{};
    pso.pRootSignature = rootSignatureX.Get();
    pso.VS = { vs->GetBufferPointer(), vs->GetBufferSize() };
    pso.PS = { ps->GetBufferPointer(), ps->GetBufferSize() };

    pso.BlendState = {};
    pso.BlendState.AlphaToCoverageEnable = FALSE;
    pso.BlendState.IndependentBlendEnable = FALSE;
    {
        D3D12_RENDER_TARGET_BLEND_DESC rt{};
        rt.BlendEnable = FALSE;
        rt.LogicOpEnable = FALSE;
        rt.SrcBlend = D3D12_BLEND_ONE;
        rt.DestBlend = D3D12_BLEND_ZERO;
        rt.BlendOp = D3D12_BLEND_OP_ADD;
        rt.SrcBlendAlpha = D3D12_BLEND_ONE;
        rt.DestBlendAlpha = D3D12_BLEND_ZERO;
        rt.BlendOpAlpha = D3D12_BLEND_OP_ADD;
        rt.LogicOp = D3D12_LOGIC_OP_NOOP;
        rt.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
        for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) pso.BlendState.RenderTarget[i] = rt;
    }

    pso.RasterizerState = {};
    pso.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
    pso.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
    pso.RasterizerState.FrontCounterClockwise = FALSE;
    pso.RasterizerState.DepthClipEnable = TRUE;

    pso.DepthStencilState = {};
    pso.DepthStencilState.DepthEnable = FALSE;
    pso.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
    pso.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
    pso.DepthStencilState.StencilEnable = FALSE;

    pso.SampleMask = UINT_MAX;
    pso.InputLayout = { nullptr, 0 };
    pso.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
    pso.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    pso.NumRenderTargets = 1;
    pso.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    pso.SampleDesc.Count = 1;

    ThrowIfFailedX(device->CreateGraphicsPipelineState(&pso, IID_PPV_ARGS(&pipelineStateX)), "Create PSO");
}

void ApplicationDirect12X::transitionToRTX()
{
    D3D12_RESOURCE_BARRIER b{};
    b.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    b.Transition.pResource = g_renderTargetsX[g_frameIndexX].Get();
    b.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    b.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    b.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    commandList->ResourceBarrier(1, &b);
}
void ApplicationDirect12X::transitionToPresentX()
{
    D3D12_RESOURCE_BARRIER b{};
    b.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    b.Transition.pResource = g_renderTargetsX[g_frameIndexX].Get();
    b.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    b.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    b.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    commandList->ResourceBarrier(1, &b);
}

void ApplicationDirect12X::SetUpX()
{
    ThrowIfFailedX(CreateDXGIFactory1(IID_PPV_ARGS(&factory)), "Factory");

    setupDeviceX();
    setupCommandQueueX();
    setupSwapChainX();

    setupDescriptorHeapX();
    setupRenderTargetViewX();

    setupCommandAllocatorX();
    setupCommandListX();

    createRootSignatureAndPSOX();

    setViewportScissorX();
}

void ApplicationDirect12X::UpdateX()
{
}

void ApplicationDirect12X::DrawX()
{
    ThrowIfFailedX(commandAllocator->Reset(), "Reset allocator");
    ThrowIfFailedX(commandList->Reset(commandAllocator.Get(), pipelineStateX.Get()), "Reset cmdlist");

    transitionToRTX();

    D3D12_CPU_DESCRIPTOR_HANDLE rtv = rtvHeap->GetCPUDescriptorHandleForHeapStart();
    rtv.ptr += static_cast<SIZE_T>(g_frameIndexX) * rtvIncrementSizeX;

    commandList->RSSetViewports(1, &viewportX);
    commandList->RSSetScissorRects(1, &scissorX);

    commandList->OMSetRenderTargets(1, &rtv, FALSE, nullptr);
    const float clear[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
    commandList->ClearRenderTargetView(rtv, clear, 0, nullptr);

    commandList->SetGraphicsRootSignature(rootSignatureX.Get());
    commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    commandList->DrawInstanced(3, 1, 0, 0);

    transitionToPresentX();

    ThrowIfFailedX(commandList->Close(), "Close cmdlist");
    ID3D12CommandList* lists[] = { commandList.Get() };
    commandQueue->ExecuteCommandLists(1, lists);

    ThrowIfFailedX(swapChain->Present(1, 0), "Present");
    g_frameIndexX = swapChain->GetCurrentBackBufferIndex();
}

void ApplicationDirect12X::clearColorBufferX(const float& r, const float& g, const float& b, const float& a)
{
    D3D12_CPU_DESCRIPTOR_HANDLE rtv = rtvHeap->GetCPUDescriptorHandleForHeapStart();
    rtv.ptr += static_cast<SIZE_T>(g_frameIndexX) * rtvIncrementSizeX;
    commandList->OMSetRenderTargets(1, &rtv, FALSE, nullptr);
    const float c[4] = { r, g, b, a };
    commandList->ClearRenderTargetView(rtv, c, 0, nullptr);
}
