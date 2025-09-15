// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Item/ABItemBox.h"

// Sets default values
AABItemBox::AABItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);
	TriggerBox->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	TriggerBox->SetCollisionProfileName(FName("ABTrigger"));

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	BoxMesh->SetupAttachment(TriggerBox);
	BoxMesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	BoxMesh->SetCollisionProfileName(FName("NoCollision"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT(""));
}


