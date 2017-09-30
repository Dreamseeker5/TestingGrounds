// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Tile.h"


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

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn)
{
	//Created a Box instance to randomly spawn actors into it

		//Nearest and farthest box's vertices  
		FVector Min(0, -2000, 0);
		FVector Max(4000, 2000, 0);

	FBox Bounds(Min, Max);

	//The random number to spawn a specific actor
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		//Spawn a point inside the box instance
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		
		//Spawn the actor
		AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
		//Set the actor's location
		Spawned->SetActorRelativeLocation(SpawnPoint);
		//Attach the new actor to the tile instance
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		
		/*UE_LOG(LogTemp, Warning, TEXT("Spawn point: %s"), *SpawnPoint.ToString());*/

	}

}
