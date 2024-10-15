#include "Blueprints/GetPlayerDataById.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UGetPlayerDataById* UGetPlayerDataById::GetPlayerDataById( UObject* WorldContextObject, int32 PlayerId ) {

	UGetPlayerDataById* Node = NewObject<UGetPlayerDataById>();
	Node->WorldContextObject = WorldContextObject;
	Node->PlayerId = PlayerId;
	return Node;

}

void UGetPlayerDataById::Activate() {

	FString URL = FString::Printf( TEXT( "%s/player/get/id/%d" ), *BaseURL, PlayerId );
	UDatabaseManager::SendHttpRequest( URL, FHttpRequestCompleteDelegate::CreateUObject( this, &UGetPlayerDataById::OnHttpResponseReceived ) );

}

void UGetPlayerDataById::OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful ) {

	FPlayerData Data;

	if ( !bWasSuccessful || !Response.IsValid() || !EHttpResponseCodes::IsOk( Response->GetResponseCode() ) ) {

		Completed.Broadcast( Data, false );
		return;

	}

	TArray<TSharedPtr<FJsonValue>> JsonArray;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create( Response->GetContentAsString() );

	if ( !FJsonSerializer::Deserialize( Reader, JsonArray ) || JsonArray.Num() <= 0 ) {

		Completed.Broadcast( Data, false );
		return;

	}

	TSharedPtr<FJsonObject> JsonObject = JsonArray[0]->AsObject();

	Data.Id = FCString::Atoi( *JsonObject->GetStringField( TEXT( "playerid" ) ) );
	Data.Username = JsonObject->GetStringField( TEXT( "username" ) );
	Data.Level = FCString::Atoi( *JsonObject->GetStringField( TEXT( "level" ) ) );
	Data.Experience = FCString::Atoi( *JsonObject->GetStringField( TEXT( "experience" ) ) );
	Data.Location = JsonObject->GetStringField( TEXT( "currentlocation" ) );

	Completed.Broadcast( Data, true );

}

