// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ABComboAttackData.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABComboAttackData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	

public:
	UABComboAttackData();
public:
	UPROPERTY(EditAnywhere, Category = Combo)
	FString MontageSectionNamePrefix;

	UPROPERTY(EditAnywhere, Category = Combo)
	uint8 MaxComboCount;

	UPROPERTY(EditAnywhere, Category = Combo)
	float FrameRate;

	UPROPERTY(EditAnywhere, Category = Combo)
	TArray<float> EffectiveFrameCount;

};
