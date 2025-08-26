// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ABCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UABCharacterAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class ACharacter> OwnerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class UCharacterMovementComponent> CharacterMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	float GroundSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	uint8 bIsIdle : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	uint8 bIsFalling : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	uint8 bIsJumping : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float MovingThreshould;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float JumpingThreshould;


};
