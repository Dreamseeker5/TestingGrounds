// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "ChooseNextWaypoint.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("You're a little piece of shit Morty!"));
	return EBTNodeResult::Succeeded;
}


