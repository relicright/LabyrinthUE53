// Copyright Relic Rights Studio


#include "AbilitySystem/Data/ArmorItemInfo.h"
#include "GameplayTagContainer.h"

FArmorItemDefaultInfo UArmorItemInfo::GetArmorItemInfo(FGameplayTag Tag)
{
	return ArmorItemInformation.FindChecked(Tag);
}
