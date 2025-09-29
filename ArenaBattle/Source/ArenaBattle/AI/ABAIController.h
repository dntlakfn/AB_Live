// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ABAIController.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API AABAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AABAIController();
public:
	


protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	void RunAI();
	void StopAI();

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBehaviorTree> BTAsset;
};
