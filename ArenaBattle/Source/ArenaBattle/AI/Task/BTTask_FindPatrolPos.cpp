// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Task/BTTask_FindPatrolPos.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
    NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    if (Result == EBTNodeResult::Failed)
        return EBTNodeResult::Failed;

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

    if(nullptr == ControllingPawn)
        return EBTNodeResult::Failed;

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
    if(nullptr == NavSystem)
        return EBTNodeResult::Failed;

    FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(HomePosKey.SelectedKeyName);
    FNavLocation NextPatrolPos;

    if (NavSystem->GetRandomPointInNavigableRadius(Origin, PatrolRadius, NextPatrolPos)) 
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(PatrolPosKey.SelectedKeyName, NextPatrolPos.Location);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
