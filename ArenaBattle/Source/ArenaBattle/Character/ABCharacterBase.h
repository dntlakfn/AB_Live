// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/ABAttackInterface.h"
#include "ABCharacterBase.generated.h"


UCLASS()
class ARENABATTLE_API AABCharacterBase : public ACharacter, public IABAttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Dead Section
public:
	virtual void SetDead();
	void PlayDeadAnimation();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	TObjectPtr<class UAnimMontage> DeadMontage;

	// Collision Check
public:
	void AttackHitCheck() override;

	// Combo Attack Section
public:
	void ComboCommand();

	virtual void ComboBegin();
	virtual void ComboEnd(class UAnimMontage* TargetMontage, bool IsPropertyEnded);

	virtual void SetComboCheckTimer();
	virtual void ComboCheck();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	TObjectPtr<class UABComboAttackData> ComboAttackData;

	int32 CurrentCombo = 0;

	FTimerHandle ComboTimerHandler;
	bool HasNextComboCommand = false;

};
