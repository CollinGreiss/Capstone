#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "DatabaseManager.h"

#include "GetQuestDescriptionData.generated.h"

UCLASS()
class CAPSTONE_API UGetQuestDescriptionData : public UBlueprintAsyncActionBase {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, Category = "Database", meta = ( BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject" ) )
    static UGetQuestDescriptionData* GetQuestDescriptionData( UObject* WorldContextObject, const FString& QuestName, int32 Step );

protected:

    virtual void Activate() override;

    UPROPERTY( BlueprintAssignable )
    FQuestDescriptionDataCompleted Completed;


private:

    void OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful );

    UObject* WorldContextObject;
    FString BaseURL = TEXT( "http://127.0.0.1:18080" );

    int32 Step;
    FString QuestName;

};
