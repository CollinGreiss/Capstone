#include "Blueprints/GetQuestDescriptionData.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UGetQuestDescriptionData* UGetQuestDescriptionData::GetQuestDescriptionData( UObject* WorldContextObject, const FString& QuestName, int32 Step ) {

	UGetQuestDescriptionData* Node = NewObject<UGetQuestDescriptionData>();
	Node->WorldContextObject = WorldContextObject;
	Node->QuestName = QuestName;
	Node->Step = Step;
	return Node;

}

void UGetQuestDescriptionData::Activate() {

	FString URL = FString::Printf( TEXT( "%s/quest-description/get/%s/%d" ), *BaseURL, *QuestName, Step );
	UDatabaseManager::SendHttpRequest( URL, FHttpRequestCompleteDelegate::CreateUObject( this, &UGetQuestDescriptionData::OnHttpResponseReceived ) );

}

void UGetQuestDescriptionData::OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful ) {

	FQuestDescriptionData Data;
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

	Data.QuestName = JsonObject->GetStringField( TEXT( "questname" ) );
	Data.Step = FCString::Atoi( *JsonObject->GetStringField( TEXT( "step" ) ) );
	Data.Description = JsonObject->GetStringField( TEXT( "description" ) );

	Completed.Broadcast( Data, true );

}
