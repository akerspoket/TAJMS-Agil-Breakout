#pragma once
#ifdef _WIN32
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <windows.h>
#include <windowsx.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <vector>
#include "DDSTextureLoader.h"
#include <iostream>
#include "GraphicsVirtual.h"
#include "Math.h"
#include "ObjLoader.h"
#include <string>
#include "DirXParticle.h"
#include "HeightmapLoader.h"
#ifdef DEBUG
	#include <iostream>
#endif // DEBUG

#define MAX_INSTANCES 100

using namespace DirectX;
using namespace std;



struct MatrixBufferType
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;
};

struct ObjectBufferType
{
	ID3D11Buffer* vertexDescription;
	unsigned int numberOfIndices;
	ObjectBufferType(ID3D11Buffer* _vertex, unsigned int _numberOfIndices)
	{
		vertexDescription = _vertex;
		numberOfIndices = _numberOfIndices;
		
	}
};

struct InstanceBufferType
{
	 XMFLOAT4X4 translationMatrices;
};

class GraphicsEngine
{
private:
	struct VertexShaderComponents
	{
		ID3D11VertexShader* ShaderHandle;
		ID3D11InputLayout * InputLayout;
	};
	struct SentenceType
	{
		string text;
		ID3D11Buffer* vertexDescription;
		unsigned int numberOfIndices;
		unsigned int maxLength;
		vec2 position;
		float size;
	};
public:
	GraphicsEngine();
	~GraphicsEngine();
	// global declarations

	IDXGISwapChain *swapchain;           
	ID3D11Device *dev;                   
	ID3D11DeviceContext *devcon;         
	ID3D11RenderTargetView *backbuffer;  
	ID3D11Texture2D *mDepthBuffer;
	ID3D11DepthStencilView *mDepthView;

	XMMATRIX mTranslationMatrices[5];
	
	float time;

	void InitD3D();     // sets 
	void InitPipeline();
	void CleanD3D(void);         // close
	void InitGraphics(float pFoVAngleY, float pHeight, float pWidth, float pNear, float pFar, float pZPos);
	int CreateObject(string pMeshName);

	void DrawObjects(int pMeshType, vector<InstanceBufferType> pInstanceBufferData, int pTextureBuffer);
	int CreateTexture(const wchar_t *pFileName);
	void EndDraw();
	int CreateNewText(int pMaxCharacters);
	void DrawThisText(string pText, vec2 pPosition, float pSize, int pSentenceID);
	int CreateParticleEmitter(vec3 pPosition, vec3 pColor, float pEmitterLifetime, float pDensity,vec3 pVelocity, float pParticleLifetime, float pSpeedMulti, float pSpread, float pStartSize, float pTextureID);
	int ChangeEmitterPos(int pEmitterID, vec3 pPosition, vec3 pVelocity);
	void DrawParticles();

	void DrawBackground();
private:

	struct ConstantBufferType
	{
		int bufferID;
		int reg;
	};
	enum ShaderType { VertexShader, PixelShader };
	bool CreateShader(ShaderType pType, void* oShaderHandle, LPCWSTR pShaderFileName, LPCSTR pEntryPoint, ID3D11InputLayout** oInputLayout, D3D11_INPUT_ELEMENT_DESC pInputDescription[], int pArraySize);
	bool SetActiveShader(ShaderType pType, void* oShaderHandle);
	int CreateBuffer(D3D11_BUFFER_DESC pBufferDescription);
	bool PushToDevice(int pBufferID, void* pDataStart, unsigned int pSize);
	bool PushToDevice(int pBufferID, void* pDataStart, unsigned int pSize, unsigned int pRegister, ShaderType pType);
	bool PushToDevice(ID3D11Buffer* pBuffer, void* pDataStart, unsigned int pSize);
	int CreateObjectBuffer(D3D11_BUFFER_DESC pVertexBufferDescription, unsigned int pNumberOfVertices);
	void CreateText(SentenceType* pText, vec2 pPosition, float pSize);
	
	//Variables
	ID3D11PixelShader* mPixelShader;
	ID3D11PixelShader* mTextPixelShader;
	VertexShaderComponents* mVertexShader = new VertexShaderComponents;
	VertexShaderComponents* mTextVertexShader = new VertexShaderComponents;
	vector< ObjectBufferType> mObjectBuffers;
	vector< ID3D11Buffer*> mBuffers;
	
	ID3D11DepthStencilState* mDepthStateOn;
	ID3D11DepthStencilState* mDepthStateOff;
	ID3D11DepthStencilState* mDepthStateNoWrite;
	ID3D11BlendState* mBlendState;
	MatrixBufferType tBufferInfo;
	int mVertexBufferID;
	int mIndexBufferID;
	int mInstanceBufferID;
	int mParticleTexID;

	ConstantBufferType mWVPBufferID;
	vector <InstanceBufferType> mInstanceBuffer;

	vector<ID3D11ShaderResourceView*> mTextureBuffers;
	ID3D11ShaderResourceView* mCubesTexture;
	ID3D11SamplerState* mCubesTexSamplerState;

	ObjLoader* mObjLoader;

	vector<SentenceType> mSentences;

	DirXParticle* mParticleSystem;
	HeightmapLoader* mHeightmapLoader;
	int mBackgroundBufferID;
	int mBacgroundTextureID;
	int mWaterPlaneBufferID;
	int mWaterPlaneTextureID;
};

#endif