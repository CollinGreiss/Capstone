#pragma once

#include "CoreMinimal.h"
#include "QuestData.generated.h"

USTRUCT( BlueprintType )
struct FQuestData {

	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite )
	FString Name;

	UPROPERTY( BlueprintReadWrite )
	int32 Steps;

};