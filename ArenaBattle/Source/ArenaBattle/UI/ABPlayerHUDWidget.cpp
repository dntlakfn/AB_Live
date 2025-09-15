// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterData/ABCharacterStat.h"
#include "ABHpBarWidget.h"
#include "ABCharacterStatWidget.h"
#include "UI/ABPlayerHUDWidget.h"

UABPlayerHUDWidget::UABPlayerHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UABPlayerHUDWidget::UpdateStat(const FABCharacterStat& BaseStat, const FABCharacterStat& ModifierStat)
{
	if(WidgetHpBar)
		WidgetHpBar->UpdateStat(BaseStat, ModifierStat);

	if (WidgetCharacterStat)
		WidgetCharacterStat->UpdateStat(BaseStat, ModifierStat);
}
void UABPlayerHUDWidget::UpdateHp(float NewCurrentHp)
{

}