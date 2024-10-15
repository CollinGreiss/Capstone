#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "DatabaseManager.h"

#include "UpdatePlayerQuestById.generated.h"

UCLASS()
class CAPSTONE_API UUpdatePlayerQuestById : public UBlueprintAsyncActionBase {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, Category = "Database", meta = ( BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject" ) )
    static UUpdatePlayerQuestById* UpdatePlayerQuestById( UObject* WorldContextObject, const FPlayerQuestData& PlayerQuestData );

protected:

    virtual void Activate() override;

    UPROPERTY( BlueprintAssignable )
    FBoolCompleted Completed;

private:

    void OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful );

    UObject* WorldContextObject;
    FString BaseURL = TEXT( "http://127.0.0.1:18080" );

    FPlayerQuestData PlayerQuestData;

};
