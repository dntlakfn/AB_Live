// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackHitCheck.h"
#include "Interface/ABAttackInterface.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	// 충돌 판정
	if (MeshComp)
	{
		IABAttackInterface* AttackPlayer = Cast<IABAttackInterface>(MeshComp->GetOwner());
		if (AttackPlayer)
		{
			AttackPlayer->AttackHitCheck();
		}
	}
}
