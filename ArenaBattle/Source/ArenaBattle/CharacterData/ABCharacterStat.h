// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ABCharacterStat.generated.h"

/**
 * 
 */
USTRUCT()
struct ARENABATTLE_API FABCharacterStat : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	


public:
	FABCharacterStat() : MaxHp(0.0f), Attack(0.0f), AttackRange(0.0f), AttackRadius(0.0f), AttackSpeed(0.0f), MovementSpeed(0.0f){}


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MovementSpeed;
	

	FABCharacterStat operator+(const FABCharacterStat Other) const 
	{
		const float* const ThisPtr = reinterpret_cast<const float*>(this);
		const float* const OtherPtr = reinterpret_cast<const float*>(&Other);

		FABCharacterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);

		int32 StatCount = sizeof(FABCharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatCount; ++i)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];

		}
		return Result;
	}
};
