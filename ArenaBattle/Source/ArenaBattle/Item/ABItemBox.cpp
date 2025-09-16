// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Item/ABItemBox.h"
#include "Interface/ABItemInterface.h"

// Sets default values
AABItemBox::AABItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);
	TriggerBox->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	TriggerBox->SetCollisionProfileName(FName("ABTrigger"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AABItemBox::OnItemBoxBeginOverlap);

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	BoxMesh->SetupAttachment(TriggerBox);
	BoxMesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	BoxMesh->SetCollisionProfileName(FName("NoCollision"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ABAssets/Environment/Props/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'"));
	if(BoxMeshRef.Succeeded())
	{
		BoxMesh->SetStaticMesh(BoxMeshRef.Object);
		
	}

	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));
	Effect->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UParticleSystem> EffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/ABAssets/Effect/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh'"));

	if(EffectRef.Succeeded())
	{
		Effect->SetTemplate(EffectRef.Object);
		Effect->bAutoActivate = false;
	}

}

void AABItemBox::OnItemBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ITemData == nullptr)
	{
		Destroy();
		return;
	}

	IABItemInterface* OverlappingPawn = Cast<IABItemInterface>(OtherActor);
	if (OverlappingPawn)
	{
		OverlappingPawn->TakeItem(ITemData);
	}

	BoxMesh->SetHiddenInGame(true);
	SetActorEnableCollision(false);
	Effect->Activate(true);
	Effect->OnSystemFinished.AddDynamic(this, &AABItemBox::OnEffectFinished);
}

void AABItemBox::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}


