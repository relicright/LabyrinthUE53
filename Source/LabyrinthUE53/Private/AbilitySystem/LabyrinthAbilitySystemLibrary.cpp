// Copyright Relic Rights Studio


#include "AbilitySystem/LabyrinthAbilitySystemLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "LabyrinthAbilityTypes.h"
#include "LabyrinthGameplayTags.h"
#include "Game/LabyrinthGameModeBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/LabyrinthPlayerState.h"
#include "UI/HUD/LabyrinthHUD.h"
#include "UI/WidgetController/LabyrinthWidgetController.h"

// USpellMenuWidgetController* ULabyrinthAbilitySystemLibrary::GetSpellMenuWidgetController(const UObject* WorldContextObject)
// {
// 	FWidgetControllerParams WCParams;
// 	ALabyrinthHUD* LabyrinthHUD = nullptr;
// 	if (MakeWidgetControllerParams(WorldContextObject, WCParams, LabyrinthHUD))
// 	{
// 		return LabyrinthHUD->GetSpellMenuWidgetController(WCParams);
// 	}
// 	return nullptr;
// }

bool ULabyrinthAbilitySystemLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject,
	FWidgetControllerParams& OutWCParams, ALabyrinthHUD*& OutLabyrinthHUD)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		OutLabyrinthHUD = Cast<ALabyrinthHUD>(PC->GetHUD());
		if (OutLabyrinthHUD)
		{
			ALabyrinthPlayerState* PS = PC->GetPlayerState<ALabyrinthPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			OutWCParams.AttributeSet = AS;
			OutWCParams.AbilitySystemComponent = ASC;
			OutWCParams.PlayerState = PS;
			OutWCParams.PlayerController = PC;
			return true;
		}
	}
	return false;
}

UOverlayWidgetController* ULabyrinthAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	ALabyrinthHUD* LabyrinthHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, LabyrinthHUD))
	{
		return LabyrinthHUD->GetOverlayWidgetController(WCParams);
	}
	return nullptr;
}

UAttributeMenuWidgetController* ULabyrinthAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	ALabyrinthHUD* LabyrinthHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, LabyrinthHUD))
	{
		return LabyrinthHUD->GetAttributeMenuWidgetController(WCParams);
	}
	return nullptr;
}

void ULabyrinthAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();

	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

// void ULabyrinthAbilitySystemLibrary::InitializeDefaultAttributesFromSaveData(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ULoadScreenSaveGame* SaveGame)
// {
// 	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
// 	if (CharacterClassInfo == nullptr) return;
//
// 	const FLabyrinthGameplayTags& GameplayTags = FLabyrinthGameplayTags::Get();
//
// 	const AActor* SourceAvatarActor = ASC->GetAvatarActor();
//
// 	FGameplayEffectContextHandle EffectContexthandle = ASC->MakeEffectContext();
// 	EffectContexthandle.AddSourceObject(SourceAvatarActor);
//
// 	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->PrimaryAttributes_SetByCaller, 1.f, EffectContexthandle);
//
// 	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Primary_Strength, SaveGame->Strength);
// 	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Primary_Intelligence, SaveGame->Intelligence);
// 	// UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Primary_Resilience, SaveGame->Resilience);
// 	// UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Primary_Vigor, SaveGame->Vigor);
//
// 	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
//
// 	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
// 	SecondaryAttributesContextHandle.AddSourceObject(SourceAvatarActor);
// 	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes_Infinite, 1.f, SecondaryAttributesContextHandle);
// 	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());
//
// 	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
// 	VitalAttributesContextHandle.AddSourceObject(SourceAvatarActor);
// 	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, 1.f, VitalAttributesContextHandle);
// 	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
// }

void ULabyrinthAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return;
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
	{
		if (ASC->GetAvatarActor()->Implements<UCombatInterface>())
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, ICombatInterface::Execute_GetPlayerLevel(ASC->GetAvatarActor()));
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

int32 ULabyrinthAbilitySystemLibrary::GetXPRewardForClassAndLevel(const UObject* WorldContextObject, ECharacterClass CharacterClass, int32 CharacterLevel)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return 0;

	const FCharacterClassDefaultInfo& Info = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	const float XPReward = Info.XPReward.GetValueAtLevel(CharacterLevel);

	return static_cast<int32>(XPReward);
}

void ULabyrinthAbilitySystemLibrary::SetIsRadialDamageEffectParam(FDamageEffectParams& DamageEffectParams, bool bIsRadial, float InnerRadius, float OuterRadius, FVector Origin)
{
	DamageEffectParams.bIsRadialDamage = bIsRadial;
	DamageEffectParams.RadialDamageInnerRadius = InnerRadius;
	DamageEffectParams.RadialDamageOuterRadius = OuterRadius;
	DamageEffectParams.RadialDamageOrigin = Origin;
}

void ULabyrinthAbilitySystemLibrary::SetKnockbackDirection(FDamageEffectParams& DamageEffectParams, FVector KnockbackDirection, float Magnitude)
{
	KnockbackDirection.Normalize();
	if (Magnitude == 0.f)
	{
		DamageEffectParams.KnockbackForce = KnockbackDirection * DamageEffectParams.KnockbackForceMagnitude;
	}
	else
	{
		DamageEffectParams.KnockbackForce = KnockbackDirection * Magnitude;
	}
}

void ULabyrinthAbilitySystemLibrary::SetDeathImpulseDirection(FDamageEffectParams& DamageEffectParams, FVector ImpulseDirection, float Magnitude)
{
	ImpulseDirection.Normalize();
	if (Magnitude == 0.f)
	{
		DamageEffectParams.DeathImpulse = ImpulseDirection * DamageEffectParams.DeathImpulseMagnitude;
	}
	else
	{
		DamageEffectParams.DeathImpulse = ImpulseDirection * Magnitude;
	}
}

void ULabyrinthAbilitySystemLibrary::SetTargetEffectParamsASC(FDamageEffectParams& DamageEffectParams,
	UAbilitySystemComponent* InASC)
{
	DamageEffectParams.TargetAbilitySystemComponent = InASC;
}

UCharacterClassInfo* ULabyrinthAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const ALabyrinthGameModeBase* LabyrinthGameMode = Cast<ALabyrinthGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (LabyrinthGameMode == nullptr) return nullptr;
	return LabyrinthGameMode->CharacterClassInfo;
}

UAttributeXPLevelInfo* ULabyrinthAbilitySystemLibrary::GetAttributeSkillXPInfo(const UObject* WorldContextObject)
{
	const ALabyrinthGameModeBase* LabyrinthGameMode = Cast<ALabyrinthGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (LabyrinthGameMode == nullptr) return nullptr;
	return LabyrinthGameMode->AttributeXPLevelInfo;
}

UAbilityInfo* ULabyrinthAbilitySystemLibrary::GetAbilityInfo(const UObject* WorldContextObject)
{
	const ALabyrinthGameModeBase* LabyrinthGameMode = Cast<ALabyrinthGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (LabyrinthGameMode == nullptr) return nullptr;
	return LabyrinthGameMode->AbilityInfo;
}

// ULootTiers* ULabyrinthAbilitySystemLibrary::GetLootTiers(const UObject* WorldContextObject)
// {
// 	const ALabyrinthGameModeBase* LabyrinthGameMode = Cast<ALabyrinthGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
// 	if (LabyrinthGameMode == nullptr) return nullptr;
// 	return LabyrinthGameMode->LootTiers;
// }

bool ULabyrinthAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<const FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return LabyrinthEffectContext->IsBlockedHit();
	}
	return false;
}

bool ULabyrinthAbilitySystemLibrary::IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<const FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return LabyrinthEffectContext->IsSuccessfulDebuff();
	}
	return false;
}

float ULabyrinthAbilitySystemLibrary::GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<const FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return LabyrinthEffectContext->GetDebuffDamage();
	}
	return 0.f;
}

float ULabyrinthAbilitySystemLibrary::GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<const FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return LabyrinthEffectContext->GetDebuffDuration();
	}
	return 0.f;
}

float ULabyrinthAbilitySystemLibrary::GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<const FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return LabyrinthEffectContext->GetDebuffFrequency();
	}
	return 0.f;
}

FGameplayTag ULabyrinthAbilitySystemLibrary::GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<const FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		if (LabyrinthEffectContext->GetDamageType().IsValid())
		{
			return *LabyrinthEffectContext->GetDamageType();
		}
	}
	return FGameplayTag();
}

FVector ULabyrinthAbilitySystemLibrary::GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<const FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return LabyrinthEffectContext->GetDeathImpulse();
	}
	return FVector::ZeroVector;
}

FVector ULabyrinthAbilitySystemLibrary::GetKnockbackForce(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<const FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return LabyrinthEffectContext->GetKnockbackForce();
	}
	return FVector::ZeroVector;
}

bool ULabyrinthAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<const FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return LabyrinthEffectContext->IsCriticalHit();
	}
	return false;
}

bool ULabyrinthAbilitySystemLibrary::IsRadialDamage(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<const FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return LabyrinthEffectContext->IsRadialDamage();
	}
	return false;
}

float ULabyrinthAbilitySystemLibrary::GetRadialDamageInnerRadius(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<const FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return LabyrinthEffectContext->GetRadialDamageInnerRadius();
	}
	return 0.f;
}

float ULabyrinthAbilitySystemLibrary::GetRadialDamageOuterRadius(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<const FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return LabyrinthEffectContext->GetRadialDamageOuterRadius();
	}
	return 0.f;
}

FVector ULabyrinthAbilitySystemLibrary::GetRadialDamageOrigin(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<const FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return LabyrinthEffectContext->GetRadialDamageOrigin();
	}
	return FVector::ZeroVector;
}

void ULabyrinthAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if (FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		LabyrinthEffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void ULabyrinthAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsCriticalHit)
{
	if (FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		LabyrinthEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void ULabyrinthAbilitySystemLibrary::SetIsSuccessfulDebuff(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInSuccessfulDebuff)
{
	if (FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		LabyrinthEffectContext->SetIsSuccessfulDebuff(bInSuccessfulDebuff);
	}
}

void ULabyrinthAbilitySystemLibrary::SetDebuffDamage(FGameplayEffectContextHandle& EffectContextHandle, float InDamage)
{
	if (FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		LabyrinthEffectContext->SetDebuffDamage(InDamage);
	}
}

void ULabyrinthAbilitySystemLibrary::SetDebuffDuration(FGameplayEffectContextHandle& EffectContextHandle, float InDuration)
{
	if (FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		LabyrinthEffectContext->SetDebuffDuration(InDuration);
	}
}

void ULabyrinthAbilitySystemLibrary::SetDebuffFrequency(FGameplayEffectContextHandle& EffectContextHandle, float InFrequency)
{
	if (FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		LabyrinthEffectContext->SetDebuffFrequency(InFrequency);
	}
}

void ULabyrinthAbilitySystemLibrary::SetDamageType(FGameplayEffectContextHandle& EffectContextHandle,
	const FGameplayTag& InDamageType)
{
	if (FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		const TSharedPtr<FGameplayTag> DamageType = MakeShared<FGameplayTag>(InDamageType);
		LabyrinthEffectContext->SetDamageType(DamageType);
	}
}

void ULabyrinthAbilitySystemLibrary::SetDeathImpulse(FGameplayEffectContextHandle& EffectContextHandle,
	const FVector& InImpulse)
{
	if (FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		LabyrinthEffectContext->SetDeathImpulse(InImpulse);
	}
}

void ULabyrinthAbilitySystemLibrary::SetKnockbackForce(FGameplayEffectContextHandle& EffectContextHandle,
	const FVector& InForce)
{
	if (FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		LabyrinthEffectContext->SetKnockbackForce(InForce);
	}
}

void ULabyrinthAbilitySystemLibrary::SetIsRadialDamage(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsRadialDamage)
{
	if (FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		LabyrinthEffectContext->SetIsRadialDamage(bInIsRadialDamage);
	}
}

void ULabyrinthAbilitySystemLibrary::SetRadialDamageInnerRadius(FGameplayEffectContextHandle& EffectContextHandle,
	float InInnerRadius)
{
	if (FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		LabyrinthEffectContext->SetRadialDamageInnerRadius(InInnerRadius);
	}
}

void ULabyrinthAbilitySystemLibrary::SetRadialDamageOuterRadius(FGameplayEffectContextHandle& EffectContextHandle,
	float InOuterRadius)
{
	if (FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		LabyrinthEffectContext->SetRadialDamageOuterRadius(InOuterRadius);
	}
}

void ULabyrinthAbilitySystemLibrary::SetRadialDamageOrigin(FGameplayEffectContextHandle& EffectContextHandle,
	const FVector& InOrigin)
{
	if (FLabyrinthGameplayEffectContext* LabyrinthEffectContext = static_cast<FLabyrinthGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		LabyrinthEffectContext->SetRadialDamageOrigin(InOrigin);
	}
}

void ULabyrinthAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject,
                                                           TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius,
                                                           const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);
	
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		for (FOverlapResult& Overlap : Overlaps)
		{
			if (Overlap.GetActor()->Implements<UCombatInterface>() /*&& !ICombatInterface::Execute_IsDead(Overlap.GetActor())*/)
			{
				OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}
}

void ULabyrinthAbilitySystemLibrary::GetClosestTargets(int32 MaxTargets, const TArray<AActor*>& Actors, TArray<AActor*>& OutClosestTargets, const FVector& Origin)
{
	if (Actors.Num() <= MaxTargets)
	{
		OutClosestTargets = Actors;
		return;
	}

	TArray<AActor*> ActorsToCheck = Actors;
	int32 NumTargetsFound = 0;

	while (NumTargetsFound < MaxTargets)
	{
		if (ActorsToCheck.Num() == 0) break;
		double ClosestDistance = TNumericLimits<double>::Max();
		AActor* ClosestActor;
		for (AActor* PotentialTarget : ActorsToCheck)
		{
			const double Distance = (PotentialTarget->GetActorLocation() - Origin).Length();
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestActor = PotentialTarget;
			}
		}
		ActorsToCheck.Remove(ClosestActor);
		OutClosestTargets.AddUnique(ClosestActor);
		++NumTargetsFound;
	}
}

bool ULabyrinthAbilitySystemLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	const bool bBothArePlayers = FirstActor->ActorHasTag(FName("Player")) && SecondActor->ActorHasTag(FName("Player"));
	const bool bBothAreEnemies = FirstActor->ActorHasTag(FName("Enemy")) && SecondActor->ActorHasTag(FName("Enemy"));
	const bool bFriends = bBothArePlayers || bBothAreEnemies;
	return !bFriends;
}

FGameplayEffectContextHandle ULabyrinthAbilitySystemLibrary::ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams)
{
	const FLabyrinthGameplayTags& GameplayTags = FLabyrinthGameplayTags::Get();
	const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
	
	FGameplayEffectContextHandle EffectContexthandle = DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
	EffectContexthandle.AddSourceObject(SourceAvatarActor);
	SetDeathImpulse(EffectContexthandle, DamageEffectParams.DeathImpulse);
	SetKnockbackForce(EffectContexthandle, DamageEffectParams.KnockbackForce);

	SetIsRadialDamage(EffectContexthandle, DamageEffectParams.bIsRadialDamage);
	SetRadialDamageInnerRadius(EffectContexthandle, DamageEffectParams.RadialDamageInnerRadius);
	SetRadialDamageOuterRadius(EffectContexthandle, DamageEffectParams.RadialDamageOuterRadius);
	SetRadialDamageOrigin(EffectContexthandle, DamageEffectParams.RadialDamageOrigin);
	
	const FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectParams.DamageGameplayEffectClass, DamageEffectParams.AbilityLevel, EffectContexthandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageEffectParams.DamageType, DamageEffectParams.BaseDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Chance, DamageEffectParams.DebuffChance);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Damage, DamageEffectParams.DebuffDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Duration, DamageEffectParams.DebuffDuration);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Frequency, DamageEffectParams.DebuffFrequency);
	
	DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	return EffectContexthandle;
}

TArray<FRotator> ULabyrinthAbilitySystemLibrary::EvenlySpacedRotators(const FVector& Forward, const FVector& Axis, float Spread, int32 NumRotators)
{
	TArray<FRotator> Rotators;
	
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-Spread / 2.f, Axis);
	if (NumRotators > 1)
	{
		const float DeltaSpread = Spread / (NumRotators - 1);
		for (int32 i = 0; i < NumRotators; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			Rotators.Add(Direction.Rotation());
		}
	}
	else
	{
		Rotators.Add(Forward.Rotation());
	}
	return Rotators;
}

TArray<FVector> ULabyrinthAbilitySystemLibrary::EvenlyRotatedVectors(const FVector& Forward, const FVector& Axis, float Spread, int32 NumVectors)
{
	TArray<FVector> Vectors;
	
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-Spread / 2.f, Axis);
	if (NumVectors > 1)
	{
		const float DeltaSpread = Spread / (NumVectors - 1);
		for (int32 i = 0; i < NumVectors; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			Vectors.Add(Direction);
		}
	}
	else
	{
		Vectors.Add(Forward);
	}
	return Vectors;
}
