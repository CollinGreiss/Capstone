using UnrealBuildTool;
using System.Collections.Generic;
using System;

public class CapstoneServerTarget : TargetRules {

    public CapstoneServerTarget( TargetInfo Target ) : base( Target ) {

        Type = TargetType.Server;
        BuildEnvironment = TargetBuildEnvironment.Shared;
        ExtraModuleNames.Add( "Capstone" );

    }

}
