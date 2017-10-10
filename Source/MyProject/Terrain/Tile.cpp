// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "ActorPoolComponent.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NavigationBoundsOffset = FVector(2000, 0, 0);

	//Initialize the values for the nearest and farthest points in the spawning box
	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();	
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Pool != nullptr && NavMeshBoundsVolume != nullptr)
	{
		Pool->Return(NavMeshBoundsVolume);
	}

}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float radius, float MinScale, float MaxScale)
{
	RandomlyPlaceActors(ToSpawn, MinSpawn, MaxSpawn, radius, MinScale, MaxScale);
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float radius)
{
	RandomlyPlaceActors(ToSpawn, MinSpawn, MaxSpawn, radius, 1, 1);
}

template<class T>
void ATile::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float radius, float MinScale, float MaxScale)
{
	//The random number of times to spawn a specific actor
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FSpawnPosition spawnPosition;

		//Generate random number to increase the objects' size
		spawnPosition.scale = FMath::RandRange(MinScale, MaxScale);

		bool clearPositionFound = FindEmptyLocation(spawnPosition.location, radius * spawnPosition.scale);
		if (clearPositionFound)
		{
			//Generate a random number to set the rotation of the spawned object
			spawnPosition.rotation = FMath::RandRange(-180.f, 180.f);

			PlaceActor(ToSpawn, spawnPosition);
		}
	}
}

bool ATile::FindEmptyLocation(FVector& OutLocation, float radius)
{
	//Created a Box instance to randomly spawn actors into it
	FBox Bounds(MinExtent, MaxExtent);

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

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition spawnPosition)
{
	//Spawn the actor
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	if (Spawned)
	{
		//Set the actor's location
		Spawned->SetActorRelativeLocation(spawnPosition.location);
		//Attach the new actor to the tile instance
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		//Set the random rotation to the spawned object
		Spawned->SetActorRotation(FRotator(0, spawnPosition.rotation, 0));
		//Set the random scale to the spawned object
		Spawned->SetActorScale3D(FVector(spawnPosition.scale));
	}
}

void ATile::PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition spawnPosition)
{
	//Spawn the actor
	FRotator rotation = FRotator(0, spawnPosition.rotation, 0);
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn, spawnPosition.location, rotation);

	if (Spawned)
	{
		//Attach the new actor to the tile instance
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		Spawned->SpawnDefaultController();
		Spawned->Tags.Add(FName("Enemy"));
	}
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

	/*FColor ColorResult = HasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), globalLocation,0, radius, FQuat::Identity, ColorResult, true, 100);*/
	 
	return !HasHit;
}

void ATile::SetPool(UActorPoolComponent* InPool)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] setting pool: %s"), *(this->GetName()), *(InPool->GetName()));
	Pool = InPool;

	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->CheckOut();
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] No actors in pool!"), *GetName());
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("[%s] Checked Out: [%s]"), *GetName(), *(NavMeshBoundsVolume->GetName()));

	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	GetWorld()->GetNavigationSystem()->Build();
}
