#include "Blueprints/GetPlayerItemDataById.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UGetPlayerItemDataById* UGetPlayerItemDataById::GetPlayerItemDataById( UObject* WorldContextObject, int32 PlayerId, int32 Slot ) {

	UGetPlayerItemDataById* Node = NewObject<UGetPlayerItemDataById>();
	Node->WorldContextObject = WorldContextObject;
	Node->PlayerId = PlayerId;
	Node->Slot = Slot;
	return Node;

}

void UGetPlayerItemDataById::Activate() {

	FString URL = FString::Printf( TEXT( "%s/player/item/get/id/%d/%d" ), *BaseURL, PlayerId, Slot );
	UDatabaseManager::SendHttpRequest( URL, FHttpRequestCompleteDelegate::CreateUObject( this, &UGetPlayerItemDataById::OnHttpResponseReceived ) );

}

void UGetPlayerItemDataById::OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful ) {

	FPlayerItemData Data;

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
	Data.ItemName = JsonObject->GetStringField( TEXT( "itemname" ) );
	Data.Quantity = FCString::Atoi( *JsonObject->GetStringField( TEXT( "quantity" ) ) );


	Completed.Broadcast( Data, true );

}
