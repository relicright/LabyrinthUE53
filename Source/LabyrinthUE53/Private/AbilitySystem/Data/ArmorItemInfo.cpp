// Copyright Relic Rights Studio


#include "AbilitySystem/Data/ItemInfo.h"
#include "GameplayTagContainer.h"

FItemDefaultInfo UArmorItemInfo::GetArmorItemInfo(FGameplayTag Tag)
{
	return ArmorItemInformation.FindChecked(Tag);
}
