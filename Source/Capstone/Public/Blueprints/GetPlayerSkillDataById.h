#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "DatabaseManager.h"

#include "GetPlayerSkillDataById.generated.h"

UCLASS()
class CAPSTONE_API UGetPlayerSkillDataById : public UBlueprintAsyncActionBase {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, Category = "Database", meta = ( BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject" ) )
    static UGetPlayerSkillDataById* GetPlayerSkillDataById( UObject* WorldContextObject, int32 PlayerId, const FString& SkillName );

protected:

    virtual void Activate() override;

    UPROPERTY( BlueprintAssignable )
    FPlayerSkillDataCompleted Completed;


private:

    void OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful );

    UObject* WorldContextObject;
    FString BaseURL = TEXT( "http://127.0.0.1:18080" );

    int32 PlayerId;
    FString SkillName;

};
