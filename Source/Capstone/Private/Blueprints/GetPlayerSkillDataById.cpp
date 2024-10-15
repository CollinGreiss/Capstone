#include "Blueprints/GetPlayerSkillDataById.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UGetPlayerSkillDataById* UGetPlayerSkillDataById::GetPlayerSkillDataById( UObject* WorldContextObject, int32 PlayerId, const FString& SkillName ) {

	UGetPlayerSkillDataById* Node = NewObject<UGetPlayerSkillDataById>();
	Node->WorldContextObject = WorldContextObject;
	Node->PlayerId = PlayerId;
	Node->SkillName = SkillName;
	return Node;

}

void UGetPlayerSkillDataById::Activate() {

	FString URL = FString::Printf( TEXT( "%s/player/skill/get/id/%d/%s" ), *BaseURL, PlayerId, *SkillName );
	UDatabaseManager::SendHttpRequest( URL, FHttpRequestCompleteDelegate::CreateUObject( this, &UGetPlayerSkillDataById::OnHttpResponseReceived ) );

}

void UGetPlayerSkillDataById::OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful ) {

	FPlayerSkillData Data;

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
	Data.SkillName = JsonObject->GetStringField( TEXT( "skillname" ) );
	Data.Level = FCString::Atoi( *JsonObject->GetStringField( TEXT( "level" ) ) );
	Data.Experience = FCString::Atoi( *JsonObject->GetStringField( TEXT( "experience" ) ) );

	Completed.Broadcast( Data, true );

}
