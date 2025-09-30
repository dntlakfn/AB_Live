// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTDecorator_AttackRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTDecorator_AttackRange::UBTDecorator_AttackRange()
{
	NodeName = TEXT("AttackInRange");
}

bool UBTDecorator_AttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return false;

	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetPawnKey.SelectedKeyName));
	if (nullptr == TargetPawn) return false;

	return (ControllingPawn->GetDistanceTo(TargetPawn) <= AttackRange);
}
