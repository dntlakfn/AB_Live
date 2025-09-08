// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/ABGameSingleton.h"

UABGameSingleton::UABGameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/CharacterData/DT_ABCharacterStat.DT_ABCharacterStat'"));

	if (DataTableRef.Succeeded())
	{
		const UDataTable* DataTable = DataTableRef.Object;

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, CharacterStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FABCharacterStat*>(Value);
			});
	}
}

UABGameSingleton& UABGameSingleton::Get() 
{
	UABGameSingleton* Singleton = CastChecked<UABGameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}
	return *NewObject<UABGameSingleton>();
}
