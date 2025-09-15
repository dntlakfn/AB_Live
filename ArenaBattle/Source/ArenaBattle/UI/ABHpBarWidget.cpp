// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABHpBarWidget.h"
#include "Components/ProgressBar.h"

UABHpBarWidget::UABHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = 0.0f;
	CurrentHp = 0.0f;
}


void UABHpBarWidget::UpdateStat(const FABCharacterStat& BaseStat, const FABCharacterStat& ModifierStat)
{
	MaxHp = (BaseStat + ModifierStat).MaxHp;

	if (HpBar)
	{
		HpBar->SetPercent(CurrentHp / MaxHp);
	}
}

void UABHpBarWidget::UpdateHp(float NewCurrentHp)
{
	CurrentHp = NewCurrentHp;

	if (HpBar)
	{
		HpBar->SetPercent(CurrentHp / MaxHp);
	}
}
