// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterData/ABCharacterStat.h"
#include "ABStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENABATTLE_API UABStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UABStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	FORCEINLINE float GetCurrentLevel() { return CurrentLevel; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	FORCEINLINE const FABCharacterStat& GetBaseStat() const { return BaseStat; }
	FORCEINLINE const FABCharacterStat& GetModifierStat() const { return ModifierStat; }
	FORCEINLINE const FABCharacterStat GetTotalStat() { return GetBaseStat() + GetModifierStat(); }

public:
	void SetLevel(int32 NewLevel);
	void SetHp(int32 NewHp);

	FORCEINLINE void SetBaseStat(const FABCharacterStat& InBaseStat)
	{
		BaseStat = InBaseStat;
	}
	FORCEINLINE void SetModifierStat(const FABCharacterStat& InModifierStat)
	{
		ModifierStat = InModifierStat;
	}

public:
	FORCEINLINE void AddHp(float InHealAmount)
	{
		CurrentHp = FMath::Clamp(CurrentHp + InHealAmount, 0, GetTotalStat().MaxHp);
	}
	FORCEINLINE void AddBaseStat(const FABCharacterStat InAddBaseStat)
	{
		BaseStat = BaseStat + InAddBaseStat;
	}
	FORCEINLINE void AddModifierStat(const FABCharacterStat InAddModifierStat)
	{
		ModifierStat = ModifierStat + InAddModifierStat;
	}

public:
	float ApplyDamage(float InDamage);
protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentLevel;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	FABCharacterStat BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	FABCharacterStat ModifierStat;
		
};
