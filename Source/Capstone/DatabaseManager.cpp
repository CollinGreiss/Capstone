// Fill out your copyright notice in the Description page of Project Settings.


#include "DatabaseManager.h"


FString UDatabaseManager::IsTrueToString( bool Input ) {

    return Input ? TEXT( "true" ) : TEXT( "false" );

}