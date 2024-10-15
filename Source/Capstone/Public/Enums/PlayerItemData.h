#pragma once

#include "CoreMinimal.h"
#include "PlayerItemData.generated.h"

USTRUCT( BlueprintType )
struct FPlayerItemData {

	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite )
	int32 PlayerId;

	UPROPERTY( BlueprintReadWrite )
	int32 Slot;

	UPROPERTY( BlueprintReadWrite )
	FString ItemName;

	UPROPERTY( BlueprintReadWrite )
	int32 Quantity;

};