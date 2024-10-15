#pragma once

#include "CoreMinimal.h"
#include "SkillData.generated.h"

USTRUCT( BlueprintType )
struct FSkillData {

    GENERATED_BODY()

public:

    UPROPERTY( BlueprintReadWrite )
    FString Name;

    UPROPERTY( BlueprintReadWrite )
    FString Description;

    UPROPERTY( BlueprintReadWrite )
    int32 MaxLevel;

};
