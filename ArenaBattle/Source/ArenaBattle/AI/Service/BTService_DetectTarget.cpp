// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_DetectTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/OverlapResult.h"
#include "DrawDebugHelpers.h"

UBTService_DetectTarget::UBTService_DetectTarget()
{
	NodeName = TEXT("DetectTarget");
	Interval = 1.0f;
}

void UBTService_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return;
	}
	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == World) return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQuertParams;
	CollisionQuertParams.AddIgnoredActor(ControllingPawn);

	bool bReuslt = World->OverlapMultiByChannel(
		OverlapResults,
		ControllingPawn->GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_EngineTraceChannel2,
		FCollisionShape::MakeSphere(DetectRange),
		CollisionQuertParams
	);

	if (bReuslt)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			APawn* TargetPawn = Cast<APawn>(OverlapResult.GetActor());
			if (TargetPawn && TargetPawn->IsPlayerControlled()) 
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetPawnkey.SelectedKeyName, TargetPawn);

				DrawDebugSphere(World, ControllingPawn->GetActorLocation(), DetectRange, 16, FColor::Green, false, 0.2f);
				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetPawnkey.SelectedKeyName, nullptr);

	DrawDebugSphere(World, ControllingPawn->GetActorLocation(), DetectRange, 16, FColor::Red, false, 0.2f);
}
