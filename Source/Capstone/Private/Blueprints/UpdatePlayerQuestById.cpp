#include "Blueprints/UpdatePlayerQuestById.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UUpdatePlayerQuestById* UUpdatePlayerQuestById::UpdatePlayerQuestById( UObject* WorldContextObject, const FPlayerQuestData& PlayerQuestData ) {
 
    UUpdatePlayerQuestById* Node = NewObject<UUpdatePlayerQuestById>();
    Node->WorldContextObject = WorldContextObject;
    Node->PlayerQuestData = PlayerQuestData;
    return Node;

}

void UUpdatePlayerQuestById::Activate() {
    
    FString URL = FString::Printf( TEXT( "%s/player/quest/update/id/%d/%s/%d/%d" ), *BaseURL, PlayerQuestData.PlayerId, *PlayerQuestData.QuestName, PlayerQuestData.Step, PlayerQuestData.Active );
	UDatabaseManager::SendHttpRequest( URL, FHttpRequestCompleteDelegate::CreateUObject( this, &UUpdatePlayerQuestById::OnHttpResponseReceived ) );

}

void UUpdatePlayerQuestById::OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful ) {
   
    Completed.Broadcast( bWasSuccessful && Response.IsValid() && EHttpResponseCodes::IsOk( Response->GetResponseCode() ) );

}
