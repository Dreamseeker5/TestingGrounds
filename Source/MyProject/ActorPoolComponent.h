// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ActorPoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UActorPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorPoolComponent();

	AActor* CheckOut();

	void Return(AActor* actorToReturn);
		
	void AddActorToPool(AActor* actorToAdd);

private:
	TArray<AActor*> Pool;

};
