// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the patrol points
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	//Warn if no patrol route component is attached
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	//Warn about a guard without patrol points
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0) 
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard have not patrol route"));
		return EBTNodeResult::Failed;
	}

	//Set next waypoint
	auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	auto index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);
	//UE_LOG(LogTemp, Warning, TEXT("Index: %i"), index);
	BlackboardComponent->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[index]);

	//Cycle index
	auto NextIndex = (index + 1) % PatrolPoints.Num();
	BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}


