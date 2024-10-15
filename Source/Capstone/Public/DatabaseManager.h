#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "Enums/PlayerData.h"
#include "Enums/QuestData.h"
#include "Enums/QuestDescriptionData.h"
#include "Enums/PlayerQuestData.h"
#include "Enums/SkillData.h"
#include "Enums/PlayerSkillData.h"
#include "Enums/ItemData.h"
#include "Enums/PlayerItemData.h"

#include "DatabaseManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FPlayerDataCompleted, FPlayerData, PlayerData, bool, bSuccess );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FQuestDataCompleted, FQuestData, QuestData, bool, bSuccess );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FQuestDescriptionDataCompleted, FQuestDescriptionData, QuestDescriptionData, bool, bSuccess );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FPlayerQuestDataCompleted, FPlayerQuestData, PlayerQuestData, bool, bSuccess );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FSkillDataCompleted, FSkillData, SkillData, bool, bSuccess );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FPlayerSkillDataCompleted, FPlayerSkillData, PlayerSkillData, bool, bSuccess );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FItemDataCompleted, FItemData, ItemData, bool, bSuccess );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FPlayerItemDataCompleted, FPlayerItemData, PlayerItemData, bool, bSuccess );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FBoolCompleted, bool, bSuccess );

UCLASS()
class CAPSTONE_API UDatabaseManager : public UBlueprintAsyncActionBase {

    GENERATED_BODY()

public:

    static void SendHttpRequest( const FString& URL, const FHttpRequestCompleteDelegate& Callback );

};
