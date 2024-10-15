#pragma once

#include "CoreMinimal.h"
#include "PlayerSkillData.generated.h"

USTRUCT( BlueprintType )
struct FPlayerSkillData {

	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite )
	int32 PlayerId;

	UPROPERTY( BlueprintReadWrite )
	FString SkillName;

	UPROPERTY( BlueprintReadWrite )
	int32 Level;

	UPROPERTY( BlueprintReadWrite )
	int32 Experience;

};