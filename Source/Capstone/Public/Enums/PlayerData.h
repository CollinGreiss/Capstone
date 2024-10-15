#pragma once

#include "CoreMinimal.h"
#include "PlayerData.generated.h"

USTRUCT( BlueprintType )
struct FPlayerData {

	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite )
	int32 Id;

	UPROPERTY( BlueprintReadWrite )
	FString Username;

	UPROPERTY( BlueprintReadWrite )
	int32 Level;

	UPROPERTY( BlueprintReadWrite )
	int32 Experience;

	UPROPERTY( BlueprintReadWrite )
	FString Location;

};