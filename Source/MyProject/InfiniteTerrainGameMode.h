// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyProjectGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AInfiniteTerrainGameMode : public AMyProjectGameMode
{
	GENERATED_BODY()
	
public:
	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
		void PopulateBoundsVolumePool();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
		class UActorPoolComponent* NavMeshBoundsVolumePool;

private:
	void AddToPool(class ANavMeshBoundsVolume* volumeToAdd);
	
};
