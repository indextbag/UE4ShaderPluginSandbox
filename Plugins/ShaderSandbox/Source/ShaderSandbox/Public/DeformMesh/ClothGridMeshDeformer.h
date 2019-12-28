#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/EngineTypes.h"
#include "RHICommandList.h"

struct FSphereCollisionParameters
{
	FVector RelativeCenter;
	float Radius;

	FSphereCollisionParameters(const FVector& RelativeCenterVec, float RadiusVal) : RelativeCenter(RelativeCenterVec), Radius(RadiusVal) {}
};

struct FGridClothParameters
{
	uint32 NumRow;
	uint32 NumColumn;
	uint32 NumVertex;
	float GridWidth;
	float GridHeight;
	float DeltaTime;
	float Stiffness;
	float Damping;
	FVector PreviousInertia;
	float VertexRadius;
	uint32 NumIteration;

	class FRHIUnorderedAccessView* PositionVertexBufferUAV;
	class FRHIUnorderedAccessView* TangentVertexBufferUAV;
	class FRHIUnorderedAccessView* PrevPositionVertexBufferUAV;
	class FRHIShaderResourceView* AccelerationVertexBufferSRV;
	TArray<FSphereCollisionParameters> SphereCollisionParams;
};

struct FClothGridMeshDeformer
{
	static const uint32 MAX_SPHERE_COLLISION = 16;
	static const uint32 MAX_CLOTH_MESH = 16;

	void EnqueueDeformTask(const FGridClothParameters& Param);
	void FlushDeformTaskQueue(FRHICommandListImmediate& RHICmdList);

	TArray<FGridClothParameters> DeformTaskQueue;
};

