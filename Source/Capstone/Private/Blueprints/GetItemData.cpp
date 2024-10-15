#include "Blueprints/GetItemData.h"

#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UGetItemData* UGetItemData::GetItemData( UObject* WorldContextObject, const FString& ItemName ) {

	UGetItemData* Node = NewObject<UGetItemData>();
	Node->WorldContextObject = WorldContextObject;
	Node->ItemName = ItemName;
	return Node;

}

void UGetItemData::Activate() {

	FString URL = FString::Printf( TEXT( "%s/item/get/%s" ), *BaseURL, *ItemName );
	UDatabaseManager::SendHttpRequest( URL, FHttpRequestCompleteDelegate::CreateUObject( this, &UGetItemData::OnHttpResponseReceived ) );

}

void UGetItemData::OnHttpResponseReceived( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful ) {

	FItemData Data;

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

	Data.Name = JsonObject->GetStringField( TEXT( "itemname" ) );
	Data.MaxQuantity = FCString::Atoi( *JsonObject->GetStringField( TEXT( "maxquantity" ) ) );

	Completed.Broadcast( Data, true );

}