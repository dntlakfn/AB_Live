// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CharacterData/ABCharacterStat.h"
#include "CharacterStat/ABStatComponent.h"
#include "UI/ABPlayerHUDWidget.h"
#include "Item/ABPotionItemData.h"
#include "Item/ABScrollItemData.h"
#include "Item/ABWeaponItemData.h"


AABCharacterPlayer::AABCharacterPlayer()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 550.0f;
	SpringArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArm);
	FollowCamera->bUsePawnControlRotation = false;

	static ConstructorHelpers::FClassFinder<UABPlayerHUDWidget> ABPlayerHUDWidgetAssetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_PlayerHUD.WBP_PlayerHUD_C'"));
	if(ABPlayerHUDWidgetAssetRef.Succeeded())
	{
		ABPlayerHUDWidgetAsset = ABPlayerHUDWidgetAssetRef.Class;
	}

	TakeItemActions.Add(EItemType::Potion, FOnTakeItemDelegate::CreateUObject(this, &AABCharacterPlayer::DrinkPotion));
	TakeItemActions.Add(EItemType::Scroll, FOnTakeItemDelegate::CreateUObject(this, &AABCharacterPlayer::ReadScroll));
	TakeItemActions.Add(EItemType::Weapon, FOnTakeItemDelegate::CreateUObject(this, &AABCharacterPlayer::EquipWeapon));
}

void AABCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	if(Subsystem)
	{
		Subsystem->AddMappingContext(IMCDefault, 0);
	}

	ABPlayerHUDWidget = CreateWidget<UABPlayerHUDWidget>(PlayerController, ABPlayerHUDWidgetAsset);
	if(ABPlayerHUDWidget)
	{
		ABPlayerHUDWidget->AddToViewport();
		
	}
	if(ABPlayerHUDWidget && StatComponent)
	{
		ABPlayerHUDWidget->UpdateHp(StatComponent->GetTotalStat().MaxHp);
		ABPlayerHUDWidget->UpdateStat(StatComponent->GetBaseStat(), StatComponent->GetModifierStat());

		StatComponent->OnHpChanged.AddUObject(ABPlayerHUDWidget, &UABPlayerHUDWidget::UpdateHp);
		StatComponent->OnStatChanged.AddUObject(ABPlayerHUDWidget, &UABPlayerHUDWidget::UpdateStat);
		
	}
}

void AABCharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AABCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(IAJump, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(IAJump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(IALook, ETriggerEvent::Triggered, this, &AABCharacterPlayer::Look);
	EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Triggered, this, &AABCharacterPlayer::Move);
	EnhancedInputComponent->BindAction(IAAttack, ETriggerEvent::Triggered, this, &AABCharacterPlayer::Attack);

}

void AABCharacterPlayer::TakeItem(UABItemData* ItemData)
{
	if (ItemData)
	{
		TakeItemActions[ItemData->Type].ExecuteIfBound(ItemData);
	}
}

void AABCharacterPlayer::DrinkPotion(UABItemData* InItemData)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, TEXT("Drink Potion"));

	UABPotionItemData* PotionItemData = Cast<UABPotionItemData>(InItemData);
	if (PotionItemData)
	{
		if(StatComponent)
		{
			StatComponent->AddHp(PotionItemData->HealAmount);
		}
	}
}

void AABCharacterPlayer::ReadScroll(UABItemData* InItemData)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, TEXT("Read Scroll"));

	UABScrollItemData* ScrollItemData = Cast<UABScrollItemData>(InItemData);
	if (ScrollItemData)
	{
		if (StatComponent)
		{
			StatComponent->AddBaseStat(ScrollItemData->BaseStat);
		}
	}
}

void AABCharacterPlayer::EquipWeapon(UABItemData* InItemData)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, TEXT("Equip Weapon"));

	
}

void AABCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void AABCharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardVertor = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVertor, MovementVector.X);
	AddMovementInput(RightVector, MovementVector.Y);
}

void AABCharacterPlayer::Attack(const FInputActionValue& Value)
{
	ComboCommand();
}
