#include "Blueprints/UpdatePlayerItemById.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UUpdatePlayerItemById* UUpdatePlayerItemById::UpdatePlayerItemById( UObject* WorldContextObject, const FPlayerItemData& PlayerItemData ) {
   
    UUpdatePlayerItemById* Node = NewObject<UUpdatePlayerItemById>();
    Node->WorldContextObject = WorldContextObject;
    Node->PlayerItemData = PlayerItemData;
    return Node;

}

void UUpdatePlayerItemById::Activate() {
   
    FString URL = FString::Printf( TEXT( "%s/player/item/update/id/%d/%d/%s/%d" ), *BaseURL, PlayerItemData.PlayerId, PlayerItemData.Slot, *PlayerItemData.ItemName, PlayerItemData.Quantity );
	UDatabaseManager::SendHttpRequest( URL, FHttpRequestCompleteDelegate::CreateUObject( this, &UUpdatePlayerItemById::OnHttpResponseReceived ) );

}

void UUpdatePlayerItemById::OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful ) {
   
    Completed.Broadcast( bWasSuccessful && Response.IsValid() && EHttpResponseCodes::IsOk( Response->GetResponseCode() ) );

}
