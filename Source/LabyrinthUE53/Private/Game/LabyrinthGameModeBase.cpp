// Copyright Relic Rights Studio


#include "Game/LabyrinthGameModeBase.h"

#include "Kismet/GameplayStatics.h"

// void ALabyrinthGameModeBase::SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex)
// {
// 	if (UGameplayStatics::DoesSaveGameExist(LoadSlot->GetLoadSlotName(), SlotIndex))
// 	{
// 		UGameplayStatics::DeleteGameInSlot(LoadSlot->GetLoadSlotName(), SlotIndex);
// 	}
// 	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
// 	ULoadScreenSaveGame* LoadScreenSaveGame = Cast<ULoadScreenSaveGame>(SaveGameObject);
// 	LoadScreenSaveGame->PlayerName = LoadSlot->GetPlayerName();
// 	LoadScreenSaveGame->SaveSlotStatus = Taken;
// 	LoadScreenSaveGame->MapName = LoadSlot->GetMapName();
// 	LoadScreenSaveGame->MapAssetName = LoadSlot->MapAssetName;
// 	LoadScreenSaveGame->PlayerStartTag = LoadSlot->PlayerStartTag;
//
// 	UGameplayStatics::SaveGameToSlot(LoadScreenSaveGame, LoadSlot->GetLoadSlotName(), SlotIndex);
// }
//
// ULoadScreenSaveGame* ALabyrinthGameModeBase::GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const
// {
// 	USaveGame* SaveGameObject = nullptr;
// 	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
// 	{
// 		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SlotName, SlotIndex);
// 	}
// 	else
// 	{
// 		SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
// 	}
// 	ULoadScreenSaveGame* LoadScreenSaveGame = Cast<ULoadScreenSaveGame>(SaveGameObject);
// 	return LoadScreenSaveGame;
// }
//
// void ALabyrinthGameModeBase::DeleteSlot(const FString& SlotName, int32 SlotIndex)
// {
// 	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
// 	{
// 		UGameplayStatics::DeleteGameInSlot(SlotName, SlotIndex);
// 	}
// }
//
// ULoadScreenSaveGame* ALabyrinthGameModeBase::RetrieveInGameSaveData()
// {
// 	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance());
//
// 	const FString InGameLoadSlotName = AuraGameInstance->LoadSlotName;
// 	const int32 InGameLoadSlotIndex = AuraGameInstance->LoadSlotIndex;
//
// 	return GetSaveSlotData(InGameLoadSlotName, InGameLoadSlotIndex);
// }
//
// void ALabyrinthGameModeBase::SaveInGameProgressData(ULoadScreenSaveGame* SaveObject)
// {
// 	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance());
//
// 	const FString InGameLoadSlotName = AuraGameInstance->LoadSlotName;
// 	const int32 InGameLoadSlotIndex = AuraGameInstance->LoadSlotIndex;
// 	AuraGameInstance->PlayerStartTag = SaveObject->PlayerStartTag;
//
// 	UGameplayStatics::SaveGameToSlot(SaveObject, InGameLoadSlotName, InGameLoadSlotIndex);
// }
//
// void ALabyrinthGameModeBase::SaveWorldState(UWorld* World, const FString& DestinationMapAssetName) const
// {
// 	FString WorldName = World->GetMapName();
// 	WorldName.RemoveFromStart(World->StreamingLevelsPrefix);
//
// 	UAuraGameInstance* AuraGI = Cast<UAuraGameInstance>(GetGameInstance());
// 	check(AuraGI);
//
// 	if (ULoadScreenSaveGame* SaveGame = GetSaveSlotData(AuraGI->LoadSlotName, AuraGI->LoadSlotIndex))
// 	{
// 		if (DestinationMapAssetName != FString(""))
// 		{
// 			SaveGame->MapAssetName = DestinationMapAssetName;
// 			SaveGame->MapName = GetMapNameFromMapAssetName(DestinationMapAssetName);
// 		}
// 		
// 		if (!SaveGame->HasMap(WorldName))
// 		{
// 			FSavedMap NewSavedMap;
// 			NewSavedMap.MapAssetName = WorldName;
// 			SaveGame->SavedMaps.Add(NewSavedMap);
// 		}
//
// 		FSavedMap SavedMap = SaveGame->GetSavedMapWithMapName(WorldName);
// 		SavedMap.SavedActors.Empty(); // clear it out, we'll fill it in with "actors"
//
// 		for (FActorIterator It(World); It; ++It)
// 		{
// 			AActor* Actor = *It;
//
// 			if (!IsValid(Actor) || !Actor->Implements<USaveInterface>()) continue;
//
// 			FSavedActor SavedActor;
// 			SavedActor.ActorName = Actor->GetFName();
// 			SavedActor.Transform = Actor->GetTransform();
//
// 			FMemoryWriter MemoryWriter(SavedActor.Bytes);
//
// 			FObjectAndNameAsStringProxyArchive Archive(MemoryWriter, true);
// 			Archive.ArIsSaveGame = true;
//
// 			Actor->Serialize(Archive);
//
// 			SavedMap.SavedActors.AddUnique(SavedActor);
// 		}
//
// 		for (FSavedMap& MapToReplace : SaveGame->SavedMaps)
// 		{
// 			if (MapToReplace.MapAssetName == WorldName)
// 			{
// 				MapToReplace = SavedMap;
// 			}
// 		}
// 		UGameplayStatics::SaveGameToSlot(SaveGame, AuraGI->LoadSlotName, AuraGI->LoadSlotIndex);
// 	}
// }
//
// void ALabyrinthGameModeBase::LoadWorldState(UWorld* World) const
// {
// 	FString WorldName = World->GetMapName();
// 	WorldName.RemoveFromStart(World->StreamingLevelsPrefix);
//
// 	UAuraGameInstance* AuraGI = Cast<UAuraGameInstance>(GetGameInstance());
// 	check(AuraGI);
//
// 	if (UGameplayStatics::DoesSaveGameExist(AuraGI->LoadSlotName, AuraGI->LoadSlotIndex))
// 	{
//
// 		ULoadScreenSaveGame* SaveGame = Cast<ULoadScreenSaveGame>(UGameplayStatics::LoadGameFromSlot(AuraGI->LoadSlotName, AuraGI->LoadSlotIndex));
// 		if (SaveGame == nullptr)
// 		{
// 			UE_LOG(LogAura, Error, TEXT("Failed to load slot"));
// 			return;
// 		}
// 		
// 		for (FActorIterator It(World); It; ++It)
// 		{
// 			AActor* Actor = *It;
//
// 			if (!Actor->Implements<USaveInterface>()) continue;
//
// 			for (FSavedActor SavedActor : SaveGame->GetSavedMapWithMapName(WorldName).SavedActors)
// 			{
// 				if (SavedActor.ActorName == Actor->GetFName())
// 				{
// 					if (ISaveInterface::Execute_ShouldLoadTransform(Actor))
// 					{
// 						Actor->SetActorTransform(SavedActor.Transform);
// 					}
//
// 					FMemoryReader MemoryReader(SavedActor.Bytes);
//
// 					FObjectAndNameAsStringProxyArchive Archive(MemoryReader, true);
// 					Archive.ArIsSaveGame = true;
// 					Actor->Serialize(Archive); // converts binary bytes back into variables
//
// 					ISaveInterface::Execute_LoadActor(Actor);
// 				}
// 			}
// 		}
// 	}
// }
//
// void ALabyrinthGameModeBase::TravelToMap(UMVVM_LoadSlot* Slot)
// {
// 	const FString SlotName = Slot->GetLoadSlotName();
// 	const int32 SlotIndex = Slot->SlotIndex;
//
// 	UGameplayStatics::OpenLevelBySoftObjectPtr(Slot, Maps.FindChecked(Slot->GetMapName()));
// }
//
// FString ALabyrinthGameModeBase::GetMapNameFromMapAssetName(const FString& MapAssetName) const
// {
// 	for (auto& Map : Maps)
// 	{
// 		if (Map.Value.ToSoftObjectPath().GetAssetName() == MapAssetName)
// 		{
// 			return Map.Key;
// 		}
// 	}
// 	return FString();
// }
//
// AActor* ALabyrinthGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
// {
// 	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance());
// 	
// 	TArray<AActor*> Actors;
// 	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Actors);
// 	if (Actors.Num() > 0)
// 	{
// 		AActor* SelectedActor = Actors[0];
// 		for (AActor* Actor : Actors)
// 		{
// 			if (APlayerStart* PlayerStart = Cast<APlayerStart>(Actor))
// 			{
// 				if (PlayerStart->PlayerStartTag == AuraGameInstance->PlayerStartTag)
// 				{
// 					SelectedActor = PlayerStart;
// 					break;
// 				}
// 			}
// 		}
// 		return SelectedActor;
// 	}
// 	return nullptr;
// }

void ALabyrinthGameModeBase::PlayerDied(ACharacter* DeadCharacter)
{
	//ULoadScreenSaveGame* SaveGame = RetrieveInGameSaveData();
	//if (!IsValid(SaveGame)) return;

	//UGameplayStatics::OpenLevel(DeadCharacter, FName(SaveGame->MapAssetName));
}

void ALabyrinthGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//Maps.Add(DefaultMapName, DefaultMap);
}