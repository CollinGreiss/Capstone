#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "DatabaseManager.h"

#include "GetPlayerQuestDataById.generated.h"

UCLASS()
class CAPSTONE_API UGetPlayerQuestDataById : public UBlueprintAsyncActionBase {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, Category = "Database", meta = ( BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject" ) )
    static UGetPlayerQuestDataById* GetPlayerQuestDataById( UObject* WorldContextObject, int32 PlayerId, const FString& QuestName );

protected:

    virtual void Activate() override;

    UPROPERTY( BlueprintAssignable )
    FPlayerQuestDataCompleted Completed;

private:

    void OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful );

    UObject* WorldContextObject;
    FString BaseURL = TEXT( "http://127.0.0.1:18080" );

    int32 PlayerId;
    FString QuestName;
};
