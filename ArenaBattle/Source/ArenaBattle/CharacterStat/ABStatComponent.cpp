// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/ABStatComponent.h"
#include "Singleton/ABGameSingleton.h"

// Sets default values for this component's properties
UABStatComponent::UABStatComponent()
{
	CurrentLevel = 1;
}


// Called when the game starts
void UABStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UABStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	SetLevel(CurrentLevel);
	SetHp(BaseStat.MaxHp);
}

void UABStatComponent::SetLevel(int32 NewLevel) 
{
	CurrentLevel = FMath::Clamp(NewLevel, 1, UABGameSingleton::Get().GetCharacterMaxLevel());
	SetBaseStat(UABGameSingleton::Get().GetCharacterStat(CurrentLevel));
}

void UABStatComponent::SetHp(int32 NewHp)
{
	CurrentHp = FMath::Clamp(NewHp, 0.0f, GetTotalStat().MaxHp);

}

float UABStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp(InDamage, 0.0f, InDamage);

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		// Dead
	}
	return ActualDamage;
}



