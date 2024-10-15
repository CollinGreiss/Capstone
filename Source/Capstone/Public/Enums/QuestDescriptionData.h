#pragma once

#include "CoreMinimal.h"
#include "QuestDescriptionData.generated.h"

USTRUCT( BlueprintType )
struct FQuestDescriptionData {

	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite )
	FString QuestName;

	UPROPERTY( BlueprintReadWrite )
	FString Description;

	UPROPERTY( BlueprintReadWrite )
	int32 Step;

};