#include "Blueprints/GetPlayerDataByUsername.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UGetPlayerDataByUsername* UGetPlayerDataByUsername::GetPlayerDataByUsername( UObject* WorldContextObject, const FString& Username ) {

	UGetPlayerDataByUsername* Node = NewObject<UGetPlayerDataByUsername>();
	Node->WorldContextObject = WorldContextObject;
	Node->Username = Username;
	return Node;

}

void UGetPlayerDataByUsername::Activate() {

	FString URL = FString::Printf( TEXT( "%s/player/get/username/%s" ), *BaseURL, *Username );
	UDatabaseManager::SendHttpRequest( URL, FHttpRequestCompleteDelegate::CreateUObject( this, &UGetPlayerDataByUsername::OnHttpResponseReceived ) );

}

void UGetPlayerDataByUsername::OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful ) {

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
