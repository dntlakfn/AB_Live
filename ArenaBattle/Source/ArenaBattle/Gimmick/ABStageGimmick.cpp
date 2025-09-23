// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/ABStageGimmick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/OverlapResult.h"
#include "Character/ABCharacterMonster.h"
#include "Item/ABItemBox.h"

// Sets default values
AABStageGimmick::AABStageGimmick()
{
    StageMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StageMesh"));
    SetRootComponent(StageMesh);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> StageMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ABAssets/Environment/Stages/SM_SQUARE.SM_SQUARE'"));
    if (StageMeshRef.Succeeded())
    {
        StageMesh->SetStaticMesh(StageMeshRef.Object);
    }
    StageTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("StageTrigger"));
    StageTriggerBox->SetupAttachment(GetRootComponent());
    StageTriggerBox->SetBoxExtent(FVector(775.0f, 775.0f, 300.0f));
    StageTriggerBox->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
    StageTriggerBox->SetCollisionProfileName(TEXT("ABTrigger"));
    StageTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AABStageGimmick::OnStageTriggerBeginOverlap);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> GateMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ABAssets/Environment/Props/SM_GATE.SM_GATE'"));

    static FName GateSockets[] = { TEXT("+XGate"), TEXT("-XGate"), TEXT("+YGate"), TEXT("-YGate") };

    for (FName GateSocket : GateSockets)
    {
        UStaticMeshComponent* GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(GateSocket);
        GateMesh->SetStaticMesh(GateMeshRef.Object);
        GateMesh->SetupAttachment(StageMesh, GateSocket);
        GateMesh->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));
        GateMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
        GateMeshs.Add(GateSocket, GateMesh);

        FName TriggerName = *GateSocket.ToString().Append(TEXT("TriggerBox"));
        UBoxComponent* GateTriggerBox = CreateDefaultSubobject<UBoxComponent>(TriggerName);
        GateTriggerBox->SetupAttachment(StageMesh, GateSocket);
        GateTriggerBox->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));
        GateTriggerBox->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
        GateTriggerBox->SetCollisionProfileName(TEXT("ABTrigger"));
        GateTriggerBox->ComponentTags.Add(GateSocket);
        GateTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AABStageGimmick::OnGateTriggerBeginOverlap);
        GateTriggerBoxes.Add(GateTriggerBox);
    }

    CurrentState = EStageState::READY;
    StageStateActions.Add(EStageState::READY, FOnStageChangedDelegate::CreateUObject(this, &AABStageGimmick::SetReady));
    StageStateActions.Add(EStageState::FIGHT, FOnStageChangedDelegate::CreateUObject(this, &AABStageGimmick::SetFight));
    StageStateActions.Add(EStageState::REWARD, FOnStageChangedDelegate::CreateUObject(this, &AABStageGimmick::SetChooseReward));
    StageStateActions.Add(EStageState::NEXT, FOnStageChangedDelegate::CreateUObject(this, &AABStageGimmick::SetChooseNext));


    MonsterSpawnTime = 2.0f;
    static ConstructorHelpers::FClassFinder<AABCharacterMonster> MonsterClassRef(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/BP_ABCharacterMonster.BP_ABCharacterMonster_C'"));
    if (MonsterClassRef.Succeeded())
    {
        MonsterClass = MonsterClassRef.Class;
    }


    //static ConstructorHelpers::FClassFinder<AABItemBox> RewardBoxClassRef(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/BP_ABItemBox.BP_ABItemBox_C'"));
    RewardBoxClass = AABItemBox::StaticClass();

    static FName RewardSockets[] = { TEXT("+XReward"), TEXT("-XReward"), TEXT("+YReward"), TEXT("-YReward") };
    for (const FName RewardSocket : RewardSockets)
    {
        FVector RewardLocation = StageMesh->GetSocketLocation(RewardSocket);
        RewardBoxSpawnLoctions.Add(RewardSocket, RewardLocation);
    }

    CurrentStageNum = 0;
}

void AABStageGimmick::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    SetStageState(CurrentState);
}

void AABStageGimmick::OnStageTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    SetStageState(EStageState::FIGHT);
}

void AABStageGimmick::OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    check(OverlappedComponent->ComponentTags.Num() == 1);
    FName ComponentTag = OverlappedComponent->ComponentTags[0];
    FName SocketName = FName(*ComponentTag.ToString().Left(2));

    FVector NewLocation = StageMesh->GetSocketLocation(SocketName);
    TArray<FOverlapResult> OverlapResults;
    FCollisionQueryParams CollisionQuery;
    CollisionQuery.AddIgnoredActor(this);

    bool bResult = GetWorld()->OverlapMultiByObjectType(
        OverlapResults,
        NewLocation,
        FQuat::Identity,
        FCollisionObjectQueryParams::InitType::AllObjects,
        FCollisionShape::MakeSphere(775.0f),
        CollisionQuery
    );
    if (bResult == false)
    {
        OnStageSpawn(NewLocation);
    }



}

void AABStageGimmick::OpenAllGates()
{
    for (const auto GateMesh : GateMeshs)
    {
        if ((GateMesh.Value))
        {
            (GateMesh.Value)->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
        }
    }
}

void AABStageGimmick::CloseAllGates()
{
    for (const auto GateMesh : GateMeshs)
    {
        if ((GateMesh.Value))
        {
            (GateMesh.Value)->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
        }
    }
}

void AABStageGimmick::SetStageState(EStageState InNewState)
{
    CurrentState = InNewState;
    if (StageStateActions.Contains(InNewState))
    {
        StageStateActions[InNewState].ExecuteIfBound();
    }
}

void AABStageGimmick::SetReady()
{
    StageTriggerBox->SetCollisionProfileName(FName("ABTrigger"));
    for (const auto GateTriggerBox : GateTriggerBoxes)
    {
        GateTriggerBox->SetCollisionProfileName(FName("NoCollision"));
    }
    OpenAllGates();
}

void AABStageGimmick::SetFight()
{
    StageTriggerBox->SetCollisionProfileName(FName("NoCollision"));
    for (const auto GateTriggerBox : GateTriggerBoxes)
    {
        GateTriggerBox->SetCollisionProfileName(FName("NoCollision"));
    }
    CloseAllGates();
    GetWorld()->GetTimerManager().SetTimer(MonsterSpawnTimerHandle, this, &AABStageGimmick::OnMonsterSpawn, MonsterSpawnTime, false);
}

void AABStageGimmick::SetChooseReward()
{
    StageTriggerBox->SetCollisionProfileName(FName("NoCollision"));
    for (const auto GateTriggerBox : GateTriggerBoxes)
    {
        GateTriggerBox->SetCollisionProfileName(FName("NoCollision"));
    }
    CloseAllGates();

    OnSpawnRewardBoxes();
}

void AABStageGimmick::SetChooseNext()
{
    StageTriggerBox->SetCollisionProfileName(FName("NoCollision"));
    for (const auto GateTriggerBox : GateTriggerBoxes)
    {
        GateTriggerBox->SetCollisionProfileName(FName("ABTrigger"));
    }
    OpenAllGates();
}

void AABStageGimmick::OnStageSpawn(FVector NewLocation)
{
    FTransform NewTransform(NewLocation);
    AABStageGimmick* NewGimmick = GetWorld()->SpawnActorDeferred<AABStageGimmick>(AABStageGimmick::StaticClass(), NewTransform);

    if (NewGimmick)
    {
        NewGimmick->SetStageNum(CurrentStageNum + 1);
        NewGimmick->FinishSpawning(NewTransform);
    }

}

void AABStageGimmick::OnMonsterSpawn()
{
    const FTransform SpawnTransform(GetActorLocation() + FVector::UpVector * 88.0f);
    AABCharacterMonster* NewMonster = GetWorld()->SpawnActorDeferred<AABCharacterMonster>(MonsterClass, SpawnTransform);
    if (NewMonster)
    {
        NewMonster->OnDestroyed.AddDynamic(this, &AABStageGimmick::OnMonsterDestroyed);
        NewMonster->SetLevel(CurrentStageNum);
        NewMonster->FinishSpawning(SpawnTransform);
    }
}

void AABStageGimmick::OnMonsterDestroyed(AActor* DestroyedActor)
{
    SetStageState(EStageState::REWARD);
}

void AABStageGimmick::OnSpawnRewardBoxes()
{
    for (const auto& RewardBoxSpawnLocation : RewardBoxSpawnLoctions)
    {
        FTransform SpawnTransform(GetActorLocation() + RewardBoxSpawnLocation.Value + FVector(0.0f, 0.0f, 30.0f));
        AABItemBox* RewardBoxActor = GetWorld()->SpawnActorDeferred<AABItemBox>(RewardBoxClass, SpawnTransform);
        if (RewardBoxActor)
        {
            RewardBoxActor->GetTriggerBox()->OnComponentBeginOverlap.AddDynamic(this, &AABStageGimmick::OnRewardBoxBeginOverlap);

            RewardBoxes.Add(RewardBoxActor);
        }
    }

    for (const auto& RewardBox : RewardBoxes)
    {
        if (RewardBox.IsValid())
        {
            RewardBox.Get()->FinishSpawning(RewardBox.Get()->GetActorTransform());
        }
    }
}

void AABStageGimmick::OnRewardBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    for (const auto& RewardBox : RewardBoxes)
    {
        if (RewardBox.IsValid())
        {
            AABItemBox* VailidItemBox = RewardBox.Get();
            AActor* OverlappedBox = OverlappedComponent->GetOwner();
            if (OverlappedBox != VailidItemBox)
            {
                VailidItemBox->Destroy();
            }
        }
    }
    SetStageState(EStageState::NEXT);
}


