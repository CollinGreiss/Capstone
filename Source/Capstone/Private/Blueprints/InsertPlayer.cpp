#include "Blueprints/InsertPlayer.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UInsertPlayer* UInsertPlayer::InsertPlayer( UObject* WorldContextObject, const FString& Username, const FString& Password ) {
 
    UInsertPlayer* Node = NewObject<UInsertPlayer>();
    Node->WorldContextObject = WorldContextObject;
    Node->Username = Username;
    Node->Password = Password;
    return Node;

}

void UInsertPlayer::Activate() {

    FString URL = FString::Printf( TEXT( "%s/player/insert/%s/%s" ), *BaseURL, *Username, *Password );
	UDatabaseManager::SendHttpRequest( URL, FHttpRequestCompleteDelegate::CreateUObject( this, &UInsertPlayer::OnHttpResponseReceived ) );

}

void UInsertPlayer::OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful ) {
    
    Completed.Broadcast( bWasSuccessful && Response.IsValid() && EHttpResponseCodes::IsOk( Response->GetResponseCode() ) );

}
