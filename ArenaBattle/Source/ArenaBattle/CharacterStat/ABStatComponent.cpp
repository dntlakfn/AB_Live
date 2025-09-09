// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/ABStatComponent.h"
#include "Singleton/ABGameSingleton.h"
#include "Character/ABCharacterBase.h"

// Sets default values for this component's properties
UABStatComponent::UABStatComponent()
{
	bWantsInitializeComponent = true;

	CurrentLevel = 1;
}


// Called when the game starts
void UABStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetLevel(CurrentLevel);
	SetHp(BaseStat.MaxHp);
}

void UABStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	
}



void UABStatComponent::SetLevel(int32 NewLevel)
{
	CurrentLevel = FMath::Clamp(NewLevel, 1, UABGameSingleton::Get().GetCharacterMaxLevel());
	SetBaseStat(UABGameSingleton::Get().GetCharacterStat(CurrentLevel));
}

void UABStatComponent::SetHp(int32 NewHp)
{
	CurrentHp = FMath::Clamp(NewHp, 0.0f, GetTotalStat().MaxHp);
	OnHpChanged.Broadcast(CurrentHp);
}

float UABStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp(InDamage, 0.0f, InDamage);

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		// Dead
		OnHpZero.Broadcast();
	}
	return ActualDamage;
}



