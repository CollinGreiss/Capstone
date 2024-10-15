#include "Blueprints/GetPlayerQuestDataById.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UGetPlayerQuestDataById* UGetPlayerQuestDataById::GetPlayerQuestDataById( UObject* WorldContextObject, int32 PlayerId, const FString& QuestName ) {

	UGetPlayerQuestDataById* Node = NewObject<UGetPlayerQuestDataById>();
	Node->WorldContextObject = WorldContextObject;
	Node->PlayerId = PlayerId;
	Node->QuestName = QuestName;
	return Node;

}

void UGetPlayerQuestDataById::Activate() {

	FString URL = FString::Printf( TEXT( "%s/player-quest/get/id/%d/%s" ), *BaseURL, PlayerId, *QuestName );
	UDatabaseManager::SendHttpRequest( URL, FHttpRequestCompleteDelegate::CreateUObject( this, &UGetPlayerQuestDataById::OnHttpResponseReceived ) );

}

void UGetPlayerQuestDataById::OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful ) {

	FPlayerQuestData Data;

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

	Data.PlayerId = FCString::Atoi( *JsonObject->GetStringField( TEXT( "playerid" ) ) );
	Data.QuestName = JsonObject->GetStringField( TEXT( "questname" ) );
	Data.Step = FCString::Atoi( *JsonObject->GetStringField( TEXT( "step" ) ) );
	Data.Active = JsonObject->GetBoolField( TEXT( "active" ) );

	Completed.Broadcast( Data, true );

}
