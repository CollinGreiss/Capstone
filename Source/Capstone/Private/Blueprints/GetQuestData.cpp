#include "Blueprints/GetQuestData.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UGetQuestData* UGetQuestData::GetQuestData( UObject* WorldContextObject, const FString& QuestName ) {

	UGetQuestData* Node = NewObject<UGetQuestData>();
	Node->WorldContextObject = WorldContextObject;
	Node->QuestName = QuestName;
	return Node;

}

void UGetQuestData::Activate() {

	FString URL = FString::Printf( TEXT( "%s/quest/get/%s" ), *BaseURL, *QuestName );
	UDatabaseManager::SendHttpRequest( URL, FHttpRequestCompleteDelegate::CreateUObject( this, &UGetQuestData::OnHttpResponseReceived ) );

}

void UGetQuestData::OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful ) {

	FQuestData Data;

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

	Data.Name = JsonObject->GetStringField( TEXT( "questname" ) );
	Data.Steps = FCString::Atoi( *JsonObject->GetStringField( TEXT( "steps" ) ) );

	Completed.Broadcast( Data, true );

}
