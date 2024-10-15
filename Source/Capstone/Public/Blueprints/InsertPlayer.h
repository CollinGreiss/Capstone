#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "DatabaseManager.h"

#include "InsertPlayer.generated.h"

UCLASS()
class CAPSTONE_API UInsertPlayer : public UBlueprintAsyncActionBase {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, Category = "Database", meta = ( BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject" ), Category = "Database" )
    static UInsertPlayer* InsertPlayer( UObject* WorldContextObject, const FString& Username, const FString& Password );

protected:

    virtual void Activate() override;

    UPROPERTY( BlueprintAssignable )
    FBoolCompleted Completed;

private:

    void OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful );

    UObject* WorldContextObject;
    FString BaseURL = TEXT( "http://127.0.0.1:18080" );
    FString Username;
    FString Password;

};
