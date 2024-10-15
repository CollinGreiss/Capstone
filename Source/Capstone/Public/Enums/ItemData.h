#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

USTRUCT( BlueprintType )
struct FItemData {

	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite )
	FString Name;

	UPROPERTY( BlueprintReadWrite )
	int32 MaxQuantity;

};