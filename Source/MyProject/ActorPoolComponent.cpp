// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "ActorPoolComponent.h"


// Sets default values for this component's properties
UActorPoolComponent::UActorPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor* UActorPoolComponent::CheckOut()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Checkout!"), *GetName());
	return nullptr;
}

void UActorPoolComponent::Return(AActor* actorToReturn)
{
	if (actorToReturn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Returned null actor"), *GetName());
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("[%s] Actor returned: [%s]"), *GetName(),*(actorToReturn->GetName()));
}

void UActorPoolComponent::AddActorToPool(AActor* actorToAdd)
{
	if (actorToAdd == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Added null actor"), *GetName());
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("[%s] Actor added: [%s]"), *GetName(), *(actorToAdd->GetName()));

}

