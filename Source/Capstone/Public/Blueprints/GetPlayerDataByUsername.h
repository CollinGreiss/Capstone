#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "DatabaseManager.h"

#include "GetPlayerDataByUsername.generated.h"

UCLASS()
class CAPSTONE_API UGetPlayerDataByUsername : public UBlueprintAsyncActionBase {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, Category = "Database", meta = ( BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject" ), Category = "Database" )
    static UGetPlayerDataByUsername* GetPlayerDataByUsername( UObject* WorldContextObject, const FString& Username );

protected:

    virtual void Activate() override;

    UPROPERTY( BlueprintAssignable )
    FPlayerDataCompleted Completed;

private:

    void OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful );

    UObject* WorldContextObject;
    FString BaseURL = TEXT( "http://127.0.0.1:18080" );
    FString Username;

};
