// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABCharacterStatWidget.h"
#include "CharacterData/ABCharacterStat.h"
#include "Components/TextBlock.h"


UABCharacterStatWidget::UABCharacterStatWidget(const FObjectInitializer& ObjectInitializer ) : Super(ObjectInitializer)
{

}

void UABCharacterStatWidget::UpdateStat(const FABCharacterStat& BaseStat, const FABCharacterStat& ModifierStat)
{
	MaxHPBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.MaxHp)));
	AttackBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.Attack)));
	AttackRangeBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.AttackRange)));
	AttackRadiusBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.AttackRadius)));
	AttackSpeedBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.AttackSpeed)));
	MovementSpeedBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.MovementSpeed)));

	MaxHPModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.MaxHp)));
	AttackModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.Attack)));
	AttackRangeModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.AttackRange)));
	AttackRadiusModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.AttackRadius)));
	AttackSpeedModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.AttackSpeed)));
	MovementSpeedModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.MovementSpeed)));
}