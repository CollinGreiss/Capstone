#include "Blueprints/UpdatePlayerDataById.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UUpdatePlayerDataById* UUpdatePlayerDataById::UpdatePlayerDataById( UObject* WorldContextObject, const FPlayerData& PlayerData ) {
   
    UUpdatePlayerDataById* Node = NewObject<UUpdatePlayerDataById>();
    Node->WorldContextObject = WorldContextObject;
    Node->PlayerData = PlayerData;
    return Node;

}

void UUpdatePlayerDataById::Activate() {

    FString URL = FString::Printf( TEXT( "%s/player/update/id/%d/%d/%d/%s" ), *BaseURL, PlayerData.Id, PlayerData.Level, PlayerData.Experience, *PlayerData.Location );
	UDatabaseManager::SendHttpRequest( URL, FHttpRequestCompleteDelegate::CreateUObject( this, &UUpdatePlayerDataById::OnHttpResponseReceived ) );

}

void UUpdatePlayerDataById::OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful ) {
    
    Completed.Broadcast( bWasSuccessful && Response.IsValid() && EHttpResponseCodes::IsOk( Response->GetResponseCode() ) );

}
