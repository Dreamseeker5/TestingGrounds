// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector location;
	float rotation; 
	float scale;

};


class UActorPoolComponent;

UCLASS()
class MYPROJECT_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float radius = 500, float MinScale = 1, float MaxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPoolComponent* InPool);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinExtent;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxExtent;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundsOffset;

private:

	void PositionNavMeshBoundsVolume();

	bool FindEmptyLocation(FVector& OutLocation, float radius);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition spawnPosition);

	bool CanSpawnAtLocation(FVector location, float radius);

	TArray<FSpawnPosition> RandomSpawnPositions(int32 MinSpawn, int32 MaxSpawn, float radius, float MinScale, float MaxScale);

	UActorPoolComponent* Pool;

	AActor* NavMeshBoundsVolume;

	
	
};
