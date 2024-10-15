#pragma once

#include "CoreMinimal.h"
#include "PlayerQuestData.generated.h"

USTRUCT( BlueprintType )
struct FPlayerQuestData {

	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite )
	int32 PlayerId;

	UPROPERTY( BlueprintReadWrite )
	FString QuestName;

	UPROPERTY( BlueprintReadWrite )
	int32 Step;

	UPROPERTY( BlueprintReadWrite )
	bool Active;

};