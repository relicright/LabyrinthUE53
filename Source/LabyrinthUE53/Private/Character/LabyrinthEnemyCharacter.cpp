// Copyright Relic Rights Studio


#include "Character/LabyrinthEnemyCharacter.h"
#include "LabyrinthUE53/LabyrinthUE53.h"
#include "AbilitySystemComponent.h"
#include "LabyrinthGameplayTags.h"
#include "AbilitySystem/LabyrinthAbilitySystemComponent.h"
#include "AbilitySystem/LabyrinthAbilitySystemLibrary.h"
#include "AbilitySystem/LabyrinthAttributeSet.h"
#include "AI/LabyrinthAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ALabyrinthEnemyCharacter::ALabyrinthEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<ULabyrinthAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	AttributeSet = CreateDefaultSubobject<ULabyrinthAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->MarkRenderStateDirty();
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->MarkRenderStateDirty();
	
	BaseWalkSpeed = 250.f;
}

void ALabyrinthEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	AuraAIController = Cast<ALabyrinthAIController>(NewController);
	AuraAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	AuraAIController->RunBehaviorTree(BehaviorTree);
	AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), CharacterClass != ECharacterClass::WarTemplar);
}

void ALabyrinthEnemyCharacter::HighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void ALabyrinthEnemyCharacter::UnHighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void ALabyrinthEnemyCharacter::SetMoveToLocation_Implementation(FVector& OutDestination)
{
	// Do not change OutDestination
}

int32 ALabyrinthEnemyCharacter::GetPlayerLevel_Implementation()
{
	return Level;
}

void ALabyrinthEnemyCharacter::Die(const FVector& DeathImpulse)
{
	SetLifeSpan(LifeSpan);
	if (AuraAIController) AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("Dead"), true);
	SpawnLoot();
	Super::Die(DeathImpulse);
}

void ALabyrinthEnemyCharacter::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* ALabyrinthEnemyCharacter::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

void ALabyrinthEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();
	if (HasAuthority())
	{
		ULabyrinthAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);	
	}

	
	// if (UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject()))
	// {
	// 	AuraUserWidget->SetWidgetController(this);
	// }
	
	// if (const ULabyrinthAttributeSet* AuraAS = Cast<ULabyrinthAttributeSet>(AttributeSet))
	// {
	// 	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(
	// 		[this](const FOnAttributeChangeData& Data)
	// 		{
	// 			OnHealthChanged.Broadcast(Data.NewValue);
	// 		}
	// 	);
	// 	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(
	// 		[this](const FOnAttributeChangeData& Data)
	// 		{
	// 			OnMaxHealthChanged.Broadcast(Data.NewValue);
	// 		}
	// 	);
	// 	
		AbilitySystemComponent->RegisterGameplayTagEvent(FLabyrinthGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&ALabyrinthEnemyCharacter::HitReactTagChanged
		);
	//
	// 	OnHealthChanged.Broadcast(AuraAS->GetHealth());
	// 	OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
	// }
}

void ALabyrinthEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	if (AuraAIController && AuraAIController->GetBlackboardComponent())
	{
		AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
}

void ALabyrinthEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<ULabyrinthAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AbilitySystemComponent->RegisterGameplayTagEvent(FLabyrinthGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ALabyrinthEnemyCharacter::StunTagChanged);


	if (HasAuthority())
	{
		InitializeDefaultAttributes();		
	}
	OnAscRegistered.Broadcast(AbilitySystemComponent);
}

void ALabyrinthEnemyCharacter::InitializeDefaultAttributes() const
{
	ULabyrinthAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void ALabyrinthEnemyCharacter::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	Super::StunTagChanged(CallbackTag, NewCount);
	
	if (AuraAIController && AuraAIController->GetBlackboardComponent())
	{
		AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("Stunned"), bIsStunned);
	}
}

