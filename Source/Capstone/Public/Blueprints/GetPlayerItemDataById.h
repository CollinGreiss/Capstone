#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "DatabaseManager.h"

#include "GetPlayerItemDataById.generated.h"


UCLASS()
class CAPSTONE_API UGetPlayerItemDataById : public UBlueprintAsyncActionBase {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, Category = "Database", meta = ( BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject" ), Category = "Database" )
    static UGetPlayerItemDataById* GetPlayerItemDataById( UObject* WorldContextObject, int32 PlayerId, int32 Slot );

protected:

    virtual void Activate() override;

    UPROPERTY( BlueprintAssignable )
    FPlayerItemDataCompleted Completed;


private:

    void OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful );

    UObject* WorldContextObject;
    FString BaseURL = TEXT( "http://127.0.0.1:18080" );

    int32 PlayerId;
    int32 Slot;

};
