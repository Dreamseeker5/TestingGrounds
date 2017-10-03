// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	auto volumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (volumeIterator)
	{
		AddToPool(*volumeIterator);
		++volumeIterator;
	}
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* volumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("Found actor: %s"), *volumeToAdd->GetName());
}



