#include "Blueprints/UpdatePlayerSkillById.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UUpdatePlayerSkillById* UUpdatePlayerSkillById::UpdatePlayerSkillById( UObject* WorldContextObject, const FPlayerSkillData& PlayerSkillData ) {
    
    UUpdatePlayerSkillById* Node = NewObject<UUpdatePlayerSkillById>();
    Node->WorldContextObject = WorldContextObject;
    Node->PlayerSkillData = PlayerSkillData;
    return Node;

}

void UUpdatePlayerSkillById::Activate() {

    FString URL = FString::Printf( TEXT( "%s/player/skill/update/id/%d/%s/%d/%d" ), *BaseURL, PlayerSkillData.PlayerId, *PlayerSkillData.SkillName, PlayerSkillData.Level, PlayerSkillData.Experience );
	UDatabaseManager::SendHttpRequest( URL, FHttpRequestCompleteDelegate::CreateUObject( this, &UUpdatePlayerSkillById::OnHttpResponseReceived ) );

}

void UUpdatePlayerSkillById::OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful ) {

    Completed.Broadcast( bWasSuccessful && Response.IsValid() && EHttpResponseCodes::IsOk( Response->GetResponseCode() ) );

}
