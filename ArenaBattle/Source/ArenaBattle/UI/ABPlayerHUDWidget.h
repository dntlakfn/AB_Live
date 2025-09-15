// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABPlayerHUDWidget.generated.h"

struct  FABCharacterStat;

UCLASS()
class ARENABATTLE_API UABPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	UABPlayerHUDWidget(const FObjectInitializer& ObjectInitializer);
public:
	void UpdateStat(const FABCharacterStat& BaseStat, const FABCharacterStat& ModifierStat);
	void UpdateHp(float NewCurrentHp);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UABHpBarWidget> WidgetHpBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UABCharacterStatWidget> WidgetCharacterStat;
	
};
