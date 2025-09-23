// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABStageGimmick.generated.h"

UENUM(BlueprintType)
enum class EStageState : uint8
{
	READY = 0,
	FIGHT,	
	REWARD,
	NEXT
};

DECLARE_DELEGATE(FOnStageChangedDelegate);

UCLASS()
class ARENABATTLE_API AABStageGimmick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABStageGimmick();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Stage Section
public:
	UFUNCTION()
	void OnStageTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	UPROPERTY(VisibleAnywhere, Category = Stage)
	TObjectPtr<class UStaticMeshComponent> StageMesh;

	UPROPERTY(VisibleAnywhere, Category = Stage)
	TObjectPtr<class UBoxComponent> StageTriggerBox;


public:
	UFUNCTION()
	void OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OpenAllGates();
	void CloseAllGates();

protected:
	UPROPERTY(VisibleAnywhere, Category = Gate)
	TMap<FName, TObjectPtr<class UStaticMeshComponent>> GateMeshs;

	UPROPERTY(VisibleAnywhere, Category = Gate)
	TArray<TObjectPtr<class UBoxComponent>> GateTriggerBoxes;

public:
	void SetStageState(EStageState InNewState);
	void SetReady();
	void SetFight();
	void SetChooseReward();
	void SetChooseNext();

protected:
	UPROPERTY(EditAnywhere, Category = StageState)
	EStageState CurrentState;

	TMap<EStageState, FOnStageChangedDelegate> StageStateActions;

public:
	UFUNCTION()
	void OnStageSpawn(FVector NewLocation);

public:
	UFUNCTION()
	void OnMonsterSpawn();

	UFUNCTION()
	void OnMonsterDestroyed(AActor* DestroyedActor);

protected:
	UPROPERTY(EditAnywhere, Category = Fight)
	TSubclassOf<class AABCharacterMonster> MonsterClass;

	UPROPERTY(EditAnywhere, Category = Fight)
	float MonsterSpawnTime = 2.0f;

	FTimerHandle MonsterSpawnTimerHandle;

public:
	UFUNCTION()
	void OnSpawnRewardBoxes();

	UFUNCTION()
	void OnRewardBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	UPROPERTY(EditAnywhere, Category = Reward)
	TSubclassOf<class AABItemBox> RewardBoxClass;

	UPROPERTY(EditAnywhere, Category = Reward)
	TArray<TWeakObjectPtr<class AABItemBox>> RewardBoxes;

	TMap<FName, FVector> RewardBoxSpawnLoctions;

public:
	FORCEINLINE int32 GetStageNum() const { return CurrentStageNum; }
	FORCEINLINE void SetStageNum(int32 NewStageNum) { CurrentStageNum = NewStageNum; }

protected:
	UPROPERTY(VisibleAnywhere, Category = Stat)
	int32 CurrentStageNum;
};
