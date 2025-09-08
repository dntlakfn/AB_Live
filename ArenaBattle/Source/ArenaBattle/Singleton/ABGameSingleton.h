// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterData/ABCharacterStat.h"
#include "ABGameSingleton.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABGameSingleton : public UObject
{
	GENERATED_BODY()
	
public:
	UABGameSingleton();
	static UABGameSingleton& Get();

public:
	FORCEINLINE FABCharacterStat GetCharacterStat(int32 InLevel) const
	{
		return CharacterStatTable.IsValidIndex(InLevel - 1) ? CharacterStatTable[InLevel - 1] : FABCharacterStat();
	}

	FORCEINLINE int32 GetCharacterMaxLevel()
	{
		return CharacterMaxLevel;
	}

private:
	TArray<FABCharacterStat> CharacterStatTable;
	int32 CharacterMaxLevel;

};
