#include "Blueprints/GetSkillData.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UGetSkillData* UGetSkillData::GetSkillData( UObject* WorldContextObject, const FString& SkillName ) {

	UGetSkillData* Node = NewObject<UGetSkillData>();
	Node->WorldContextObject = WorldContextObject;
	Node->SkillName = SkillName;
	return Node;

}

void UGetSkillData::Activate() {

	FString URL = FString::Printf( TEXT( "%s/skill/get/%s" ), *BaseURL, *SkillName );
	UDatabaseManager::SendHttpRequest( URL, FHttpRequestCompleteDelegate::CreateUObject( this, &UGetSkillData::OnHttpResponseReceived ) );

}

void UGetSkillData::OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful ) {

	FSkillData Data;
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

	Data.Name = JsonObject->GetStringField( TEXT( "skillname" ) );
	Data.Description = JsonObject->GetStringField( TEXT( "description" ) );
	Data.MaxLevel = FCString::Atoi( *JsonObject->GetStringField( TEXT( "maxlevel" ) ) );

	Completed.Broadcast( Data, true );

}
