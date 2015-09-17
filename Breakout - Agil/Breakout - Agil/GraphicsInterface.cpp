#include "GraphicsInterface.h"



GraphicsInterface::GraphicsInterface()
{
	mGraphicsEngine = new GraphicsEngine();
}


GraphicsInterface::~GraphicsInterface()
{
}

int GraphicsInterface::CreateObject(const char* pMeshGroup)
{
	if(/*Windows*/true)
	{
		return mGraphicsEngine->CreateObject(pMeshGroup);
	}
	else
	{
		return 0;//mOpenGLengine->CreateMesh();
	}
}

void GraphicsInterface::DrawObjects(int pMeshType, int pTextureGroup[], TransformComponent pTransform[], int pNumberOfInstances)
{
	if (/*Windows*/true)
	{
		vector<XMMATRIX> tMatrixVector;
		for (int i = 0; i < pNumberOfInstances; i++)
		{
			XMMATRIX trans;
			trans = XMMatrixTranslation(pTransform[i].mPosition[0], pTransform[i].mPosition[1], pTransform[i].mPosition[2]);
			XMVECTOR orientation;
			orientation = XMLoadFloat4(&XMFLOAT4(pTransform[i].mQuatRotation[0], pTransform[i].mQuatRotation[1], pTransform[i].mQuatRotation[2], pTransform[i].mQuatRotation[3]));
			
			XMMATRIX rot = XMMatrixRotationQuaternion(orientation);
			tMatrixVector.push_back(XMMatrixTranspose(rot*trans)); ////////FELFEL KANSKE 123hej trans kanske ska vara på höger sida
		}
		mGraphicsEngine->DrawObjects(pMeshType, pTextureGroup, tMatrixVector, pNumberOfInstances);
	}
	
	//mGraphicsEngine->DrawBatch(pMeshGroup, pTextureGroup, pWorldMatrix, pNumberOfMeshes);

}