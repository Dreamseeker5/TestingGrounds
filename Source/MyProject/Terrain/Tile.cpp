// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Tile.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float radius)
{

	//The random number of times to spawn a specific actor
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		//Spawn the actor only when a clear position (no overlaps) is found
		FVector SpawnPoint;
		bool clearPositionFound	= FindEmptyLocation(SpawnPoint, radius);
		if(clearPositionFound)
		{
			PlaceActor(ToSpawn, SpawnPoint);
		}
	}

}

bool ATile::FindEmptyLocation(FVector& OutLocation, float radius)
{
	//Created a Box instance to randomly spawn actors into it

		//Nearest and farthest box's vertices  
		FVector Min(0, -2000, 0);
		FVector Max(4000, 2000, 0);

	FBox Bounds(Min, Max);

	//Try to find a clear point to spawn in a determined amount of times
	const int MAX_ATTEMPTS = 100;
	for(size_t i = 0; i < MAX_ATTEMPTS; i++ )
	{
		//Generate a random point which potentially serves as a spawn position 
		FVector PotentialPoint = FMath::RandPointInBox(Bounds);

		//Test every randomly generated potential point until one is not overlapping with other object
		if (CanSpawnAtLocation(PotentialPoint, radius))
		{
			OutLocation = PotentialPoint;
			return true;
		}
	}

	return false;

}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint)
{
	//Spawn the actor
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	//Set the actor's location
	Spawned->SetActorRelativeLocation(SpawnPoint);
	//Attach the new actor to the tile instance
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

}

bool ATile::CanSpawnAtLocation(FVector location, float radius)
{

	FHitResult HitResult;
	
	//Cast the position from local to global transforms
	FVector globalLocation = ActorToWorld().TransformPosition(location);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		globalLocation,
		globalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(radius)
	);

	FColor ColorResult = HasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), globalLocation,0, radius, FQuat::Identity, ColorResult, true, 100);
	 
	return !HasHit;
}