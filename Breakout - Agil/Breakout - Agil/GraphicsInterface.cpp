#include "GraphicsInterface.h"

GraphicsInterface* GraphicsInterface::mSingleton = 0;

GraphicsInterface::GraphicsInterface()
{
#ifdef __linux1__
	mGraphicsEngine = new OGLGraphicsEngine();
#elif _WIN32
	mGraphicsEngine = new GraphicsEngine();
#endif
	
}


GraphicsInterface::~GraphicsInterface()
{
}

GraphicsInterface* GraphicsInterface::GetSingleton()
{
	if (!mSingleton)
	{
		mSingleton = new GraphicsInterface();
	}

	return mSingleton;
}

void GraphicsInterface::Initialize(float pFoVAngleY, float pHeight, float pWidth, float pNear, float pFar, float pZPos, SDL_Window* pWin)
{
#ifdef __linux1__
	mGraphicsEngine->InitGlew(pWin);
	mGraphicsEngine->InitGraphics(pFoVAngleY, pHeight, pWidth, pNear, pFar, pZPos);
#elif _WIN32
	mGraphicsEngine->InitD3D();
	mGraphicsEngine->InitPipeline();
	mGraphicsEngine->InitGraphics(pFoVAngleY, pHeight, pWidth, pNear, pFar, pZPos);
#endif

}

int GraphicsInterface::CreateObject(string pMeshGroup)
{

	int retValue;
	if (mLoadedObjects.find(pMeshGroup) != mLoadedObjects.end())
	{
		return mLoadedObjects[pMeshGroup];
	}

	retValue = mGraphicsEngine->CreateObject(pMeshGroup);

	mLoadedObjects[pMeshGroup] = retValue;
	return retValue;
}

int GraphicsInterface::CreateTexture(string pTextureName) //Think this needs to be string so we can converte it ourselfs to wchar or char
{
	int retValue;
	if (mLoadedTextures.find(pTextureName)!=mLoadedTextures.end())
	{
		return mLoadedTextures[pTextureName];
	}
	string tTempName;
	
#ifdef __linux1__
	tTempName = pTextureName + ".png";
	const char* cstr = tTempName.c_str(); //Not tested
	retValue = mGraphicsEngine->CreateTexture(cstr);
#elif _WIN32
	tTempName = pTextureName + ".dds";
	std::wstring widestr = std::wstring(tTempName.begin(), tTempName.end());
	const wchar_t* widecstr = widestr.c_str();
	retValue = mGraphicsEngine->CreateTexture(widecstr);
#endif
	mLoadedTextures[pTextureName] = retValue;
	return retValue;
}
void GraphicsInterface::DrawInstancedObjects(unsigned int pMeshType, unsigned int pMaterialID, TransformComponent pTransformMatrices[], int pNumberOfInstances)
{
#ifdef __linux1__
	vector<InstanceBufferType> tMatrixVector;
	for (int i = 0; i < pNumberOfInstances; i++)
	{
		InstanceBufferType tFinished;
		glm::mat4 trans = glm::translate(glm::vec3( -pTransformMatrices[i].mPosition.x, pTransformMatrices[i].mPosition.y, pTransformMatrices[i].mPosition.z));
		glm::quat tQuater;
		tQuater = glm::quat(pTransformMatrices[i].mQuatRotation.x, pTransformMatrices[i].mQuatRotation.y, pTransformMatrices[i].mQuatRotation.z, pTransformMatrices[i].mQuatRotation.w);
		glm::mat4 rot = glm::mat4_cast(tQuater);

		tFinished.TranslationMatrices = rot*trans ;

		tMatrixVector.push_back(tFinished); ////////FELFEL KANSKE 123hej trans kanske ska vara p� h�ger sida
	}
	mGraphicsEngine->DrawObjects(pMeshType, tMatrixVector, pMaterialID);
#elif _WIN32
	vector<InstanceBufferType> tMatrixVector;
	for (int i = 0; i < pNumberOfInstances; i++)
	{
		InstanceBufferType tFinished;
		XMMATRIX trans;
		trans = XMMatrixTranslation(pTransformMatrices[i].mPosition.x, pTransformMatrices[i].mPosition.y, pTransformMatrices[i].mPosition.z);
		//XMVECTOR orientation;
		//orientation = XMLoadFloat4(&XMFLOAT4(pTransformMatrices[i].mQuatRotation.x, pTransformMatrices[i].mQuatRotation.y, pTransformMatrices[i].mQuatRotation.z, pTransformMatrices[i].mQuatRotation.w));

		////orientation = XMLoadFloat4(&XMFLOAT4(1,0,0,1));

		//XMMATRIX rot = XMMatrixRotationQuaternion(orientation);
		XMMATRIX rot2 = XMMatrixRotationZ(pTransformMatrices[i].mQuatRotation.x);

		XMStoreFloat4x4(&tFinished.translationMatrices, XMMatrixTranspose(rot2*trans));

		tMatrixVector.push_back(tFinished); ////////FELFEL KANSKE 123hej trans kanske ska vara p� h�ger sida
	}
	mGraphicsEngine->DrawObjects(pMeshType, tMatrixVector, pMaterialID);
	

#endif


}

void GraphicsInterface::EndDraw()
{
	mGraphicsEngine->EndDraw();
}

int GraphicsInterface::GetTextureID(TextureNames pName)
{
	int tTextureID;
	switch (pName)
	{
	case GraphicsInterface::BRICK:
		tTextureID = 0;
		break;
	case GraphicsInterface::ELEPHANT:
		break;
	default:
		break;
	}
	return 1;
}
void GraphicsInterface::DrawParticles()
{
#ifdef _WIN32
	return mGraphicsEngine->DrawParticles();
#endif
}
int GraphicsInterface::CreateText(int pMaxCharacters)
{
	int retValue = mGraphicsEngine->CreateNewText(pMaxCharacters);
	return retValue;
}
void GraphicsInterface::DrawThisText(string pText, vec2 pPosition, float pSize, int pSentenceID)
{
	mGraphicsEngine->DrawThisText(pText, pPosition, pSize, pSentenceID);
}

int GraphicsInterface::CreateParticleEmitter(vec3 pPosition, vec3 pColor, float pEmitterLifetime, float pDensity, vec3 pVelocity, float pParticleLifetime, float pSpeedMulti, float pSpread, float pStartSize, float pTextureID)
{
#ifdef _WIN32
	return mGraphicsEngine->CreateParticleEmitter(pPosition, pColor, pEmitterLifetime, pDensity,pVelocity, pParticleLifetime, pSpeedMulti, pSpread, pStartSize, pTextureID);
#endif
}

int GraphicsInterface::UpdateEmitterPos(int pEmitterID, vec3 pPosition, vec3 pVelocity)
{
#ifdef _WIN32
	return mGraphicsEngine->ChangeEmitterPos(pEmitterID, pPosition, pVelocity);
#endif
}

void GraphicsInterface::UpdateEmitterTime(int pEmitterID, float pPosition)
{
#ifdef _WIN32
	return mGraphicsEngine->UpdateEmitterTime(pEmitterID, pPosition);
#endif
}