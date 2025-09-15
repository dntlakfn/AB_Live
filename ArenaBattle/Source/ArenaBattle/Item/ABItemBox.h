// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABItemBox.generated.h"

UCLASS()
class ARENABATTLE_API AABItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABItemBox();

public:
	TObjectPtr<class UBoxComponent> GetTriggerBox() { return TriggerBox; }
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UBoxComponent> TriggerBox;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UStaticMeshComponent> BoxMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UParticleSystemComponent> Effect;
public:


};
