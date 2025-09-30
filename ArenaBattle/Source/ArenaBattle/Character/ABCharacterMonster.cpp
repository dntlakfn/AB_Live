// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterMonster.h"
#include "Engine/AssetManager.h"
#include "AI/ABAIController.h"

AABCharacterMonster::AABCharacterMonster()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AABAIController::StaticClass();

	GetMesh()->SetHiddenInGame(true);
}

void AABCharacterMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ensure(MonsterMeshes.Num() > 0);

	int32 RandomIndex = FMath::RandRange(0, MonsterMeshes.Num() - 1);
	MonsterMeshHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(MonsterMeshes[RandomIndex], FStreamableDelegate::CreateUObject(this, &AABCharacterMonster::MonsterMeshLoadCompleted));

}

void AABCharacterMonster::AttackByAI()
{
	ComboCommand();
}

void AABCharacterMonster::SetDead()
{
	Super::SetDead();

	AABAIController* ABAIController = Cast<AABAIController>(GetController());
	if (ABAIController)
	{
		ABAIController->StopAI();
	}

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]() 
		{
			Destroy();
		}),
		DeadEventDelayTime, false);

}

void AABCharacterMonster::MonsterMeshLoadCompleted()
{
	if (MonsterMeshHandle.IsValid())
	{
		USkeletalMesh* MonsterMesh = Cast<USkeletalMesh>(MonsterMeshHandle->GetLoadedAsset());
		if (MonsterMesh)
		{
			GetMesh()->SetSkeletalMesh(MonsterMesh);
			GetMesh()->SetHiddenInGame(false);
		}
	}

	MonsterMeshHandle->ReleaseHandle();

}
