#include "DatabaseManager.h"

void UDatabaseManager::SendHttpRequest( const FString& URL, const FHttpRequestCompleteDelegate& Callback ) {

    FHttpModule* Http = &FHttpModule::Get();
    if ( !Http ) return;

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

    Request->OnProcessRequestComplete().BindLambda( [Callback]( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful ) {
        Callback.ExecuteIfBound( Request, Response, bWasSuccessful );
        } );

    Request->SetURL( URL );
    Request->SetVerb( TEXT( "GET" ) );
    Request->ProcessRequest();

}